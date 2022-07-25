# frozen_string_literal: true

require 'mkmf'

CONFIG['warnflags'].slice!(/ -Wshorten-64-to-32/)

create_makefile('tomlib/tomlib')
