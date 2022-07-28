#include <stdio.h>
#include <ruby.h>

#include "toml.h"

static ID id_new;

static VALUE mTomlib;
static VALUE cParserError;

static VALUE cDate;

static VALUE toml_table_key_to_rb_value(const toml_table_t *table, const char *key);
static VALUE toml_array_index_to_rb_value(const toml_array_t *array, int index);

/**
 * Convert TOML table (aka hash) to Ruby hash
 */
static VALUE toml_table_to_rb_hash(const toml_table_t *table) {
  VALUE rb_hash = rb_hash_new();

  for (int i = 0; ; i++) {
    const char *key = toml_key_in(table, i);

    if (!key) break;

    VALUE rb_key = rb_utf8_str_new_cstr(key);
    VALUE rb_value = toml_table_key_to_rb_value(table, key);

    rb_hash_aset(rb_hash, rb_key, rb_value);
  }

  return rb_hash;
}

/**
 * Convert TOML array to Ruby array
 */
static VALUE toml_array_to_rb_array(const toml_array_t *array) {
  int length = toml_array_nelem(array);

  VALUE rb_array = rb_ary_new2(length);

  for (int i = 0; i < length; i++) {
    VALUE rb_value = toml_array_index_to_rb_value(array, i);
    rb_ary_push(rb_array, rb_value);
  }

  return rb_array;
}

/**
 * Convert TOML timestamp to Ruby Date/Time/String depending on timestamp format
 */
static VALUE toml_timestamp_to_rb_value(const toml_timestamp_t *ts) {
  if (ts->month && (*ts->month < 1 || *ts->month > 12)) {
    rb_raise(cParserError, "invalid month: %d", *ts->month);
  }

  if (ts->day && (*ts->day < 1 || *ts->day > 31)) {
    rb_raise(cParserError, "invalid day: %d", *ts->day);
  }

  if (ts->hour && (*ts->hour < 0 || *ts->hour > 23)) {
    rb_raise(cParserError, "invalid hour: %d", *ts->hour);
  }

  if (ts->minute && (*ts->minute < 0 || *ts->minute > 59)) {
    rb_raise(cParserError, "invalid minute: %d", *ts->minute);
  }

  if (ts->second && (*ts->second < 0 || *ts->second > 59)) {
    rb_raise(cParserError, "invalid second: %d", *ts->second);
  }

  if (ts->year && ts->hour) {
    double second = *ts->second * 1000;

    if (ts->millisec) {
      second += *ts->millisec;
    }

    VALUE rb_time;

    VALUE rb_year = INT2FIX(*ts->year);
    VALUE rb_month = INT2FIX(*ts->month);
    VALUE rb_day = INT2FIX(*ts->day);
    VALUE rb_hour = INT2FIX(*ts->hour);
    VALUE rb_minute = INT2FIX(*ts->minute);
    VALUE rb_second = rb_rational_raw(DBL2NUM(second), INT2FIX(1000));

    if (ts->z) {
      VALUE rb_tz = rb_str_new2(ts->z);
      rb_time = rb_funcall(
        rb_cTime,
        id_new,
        7,
        rb_year,
        rb_month,
        rb_day,
        rb_hour,
        rb_minute,
        rb_second,
        rb_tz
      );
    } else {
      rb_time = rb_funcall(
        rb_cTime,
        id_new,
        6,
        rb_year,
        rb_month,
        rb_day,
        rb_hour,
        rb_minute,
        rb_second
      );
    }

    return rb_time;
  }

  if (ts->year && !ts->hour) {
    VALUE rb_year = INT2FIX(*ts->year);
    VALUE rb_month = INT2FIX(*ts->month);
    VALUE rb_day = INT2FIX(*ts->day);

    return rb_funcall(cDate, id_new, 3, rb_year, rb_month, rb_day);
  }

  if (!ts->year && ts->hour) {
    const char *str;

    int hour = *ts->hour;
    int minute = *ts->minute;
    int second = *ts->second;

    if (ts->millisec) {
      char buf[13];
      sprintf(buf, "%02d:%02d:%02d.%03d", hour, minute, second, *ts->millisec);
      str = buf;
    } else {
      char buf[9];
      sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
      str = buf;
    }

    return rb_str_new2(str);
  }

  return Qnil;
}

/**
 * Convert TOML table's value to Ruby object
 */
static VALUE toml_table_key_to_rb_value(const toml_table_t *table, const char *key) {
  toml_datum_t datum;

  datum = toml_string_in(table, key);

  if (datum.ok) {
    VALUE rb_value = rb_utf8_str_new_cstr(datum.u.s);
    free(datum.u.s);
    return rb_value;
  }

  datum = toml_int_in(table, key);

  if (datum.ok) {
    return LL2NUM(datum.u.i);
  }

  datum = toml_double_in(table, key);

  if (datum.ok) {
    return DBL2NUM(datum.u.d);
  }

  datum = toml_bool_in(table, key);

  if (datum.ok) {
    return datum.u.b ? Qtrue : Qfalse;
  }

  datum = toml_timestamp_in(table, key);

  if (datum.ok) {
    VALUE rb_value = toml_timestamp_to_rb_value(datum.u.ts);
    free(datum.u.ts);
    return rb_value;
  }

  toml_table_t *sub_table = toml_table_in(table, key);

  if (sub_table) {
    return toml_table_to_rb_hash(sub_table);
  }

  toml_array_t *array = toml_array_in(table, key);

  if (array) {
    return toml_array_to_rb_array(array);
  }

  rb_raise(cParserError, "invalid value");
}

/**
 * Convert TOML array element to Ruby object
 */
static VALUE toml_array_index_to_rb_value(const toml_array_t *array, int index) {
  toml_datum_t datum;

  datum = toml_string_at(array, index);

  if (datum.ok) {
    VALUE rb_value = rb_utf8_str_new_cstr(datum.u.s);
    free(datum.u.s);
    return rb_value;
  }

  datum = toml_int_at(array, index);

  if (datum.ok) {
    return INT2FIX(datum.u.i);
  }

  datum = toml_double_at(array, index);

  if (datum.ok) {
    return DBL2NUM(datum.u.d);
  }

  datum = toml_bool_at(array, index);

  if (datum.ok) {
    return datum.u.b ? Qtrue : Qfalse;
  }

  datum = toml_timestamp_at(array, index);

  if (datum.ok) {
    VALUE rb_value = toml_timestamp_to_rb_value(datum.u.ts);
    free(datum.u.ts);
    return rb_value;
  }

  toml_table_t *table = toml_table_at(array, index);

  if (table) {
    return toml_table_to_rb_hash(table);
  }

  toml_array_t *sub_array = toml_array_at(array, index);

  if (sub_array) {
    return toml_array_to_rb_array(sub_array);
  }

  rb_raise(cParserError, "invalid value");
}

/**
 * Parse TOML string and convert it into Ruby hash
 */
static VALUE tomlib_load_do(VALUE rb_str) {
  char *str = StringValueCStr(rb_str);
  char errbuf[200] = "";

  toml_table_t *table = toml_parse(str, errbuf, sizeof(errbuf));

  if (!table) {
    rb_raise(cParserError, "%s", errbuf);
  }

  VALUE rb_value = toml_table_to_rb_hash(table);

  toml_free(table);

  return rb_value;
}

/**
 * Rescue from argument errors
 */
static VALUE tomlib_load_rescue(VALUE rb_arg, VALUE rb_error) {
  rb_set_errinfo(Qnil);
  rb_raise(cParserError, "string contains null byte");
  return Qnil;
}

/**
 * Function exposed to Ruby's world as Tomlib.load(data)
 */
static VALUE tomlib_load(VALUE self, VALUE rb_str) {
  return rb_rescue2(tomlib_load_do, rb_str, tomlib_load_rescue, Qnil, rb_eArgError, 0);
}

/**
 * Ruby's extension entry point
 */
void Init_tomlib(void) {
  id_new = rb_intern("new");

  rb_require("date");
  cDate = rb_const_get(rb_cObject, rb_intern("Date"));

  mTomlib = rb_define_module("Tomlib");
  cParserError = rb_define_class_under(mTomlib, "ParseError", rb_eStandardError);

  rb_define_module_function(mTomlib, "load", tomlib_load, 1);
}
