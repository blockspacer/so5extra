require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'so_5/prj_s.rb'
	required_prj 'asio_mxxru/prj.rb'
	required_prj 'test/so_5_extra/env_infrastructures/asio/platform_specific_libs.rb'

	target '_unit.test.so_5_extra.disp.asio_thread_pool.multifile_hello_s'

	cpp_source 'main.cpp'
	cpp_source 'a.cpp'
	cpp_source 'b.cpp'
}

