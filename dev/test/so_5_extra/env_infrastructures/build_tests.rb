#!/usr/bin/ruby
require 'mxx_ru/cpp'

MxxRu::Cpp::composite_target {
	path = 'test/so_5_extra/env_infrastructures'

	required_prj( "#{path}/asio/build_tests.rb" )
}
