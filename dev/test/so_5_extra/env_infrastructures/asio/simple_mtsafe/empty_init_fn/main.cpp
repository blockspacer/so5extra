#include <so_5_extra/env_infrastructures/asio/simple_mtsafe.hpp>

#include <so_5/all.hpp>

#include <test/3rd_party/various_helpers/time_limited_execution.hpp>

int main()
{
	run_with_time_limit( [] {
			asio::io_context io_svc;

			so_5::launch( [](so_5::environment_t & /*env*/) {},
					[&io_svc](so_5::environment_params_t & params) {
						using namespace so_5::extra::env_infrastructures::asio::simple_mtsafe;

						params.infrastructure_factory( factory(io_svc) );
					} );
		},
		5 );

	return 0;
}

