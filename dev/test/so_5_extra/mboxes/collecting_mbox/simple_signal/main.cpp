#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include <doctest/doctest.h>

#include <so_5_extra/mboxes/collecting_mbox.hpp>

#include <so_5/all.hpp>

#include <test/3rd_party/various_helpers/time_limited_execution.hpp>

namespace collecting_mbox_ns = so_5::extra::mboxes::collecting_mbox;

struct hello final : public so_5::signal_t {};

struct constexpr_case
{
	using collecting_mbox_t = collecting_mbox_ns::mbox_template_t<
			hello,
			collecting_mbox_ns::constexpr_size_traits_t<3> >;

	static auto
	make( const so_5::mbox_t & target )
	{
		return collecting_mbox_t::make( target );
	}
};

struct runtime_case
{
	using collecting_mbox_t = collecting_mbox_ns::mbox_template_t<
			hello,
			collecting_mbox_ns::runtime_size_traits_t >;

	static auto
	make( const so_5::mbox_t & target )
	{
		return collecting_mbox_t::make( target, 3u );
	}
};

template< typename Case >
class a_test_case_t final : public so_5::agent_t
{
	using collecting_mbox_t = typename Case::collecting_mbox_t;

public :
	a_test_case_t(
		context_t ctx,
		std::string & dest )
		:	so_5::agent_t( std::move(ctx) )
		,	m_dest( dest )
		,	m_mbox( Case::make( so_direct_mbox() ) )
	{}

	virtual void
	so_define_agent() override
	{
		so_subscribe_self().event( &a_test_case_t::on_messages_collected );
	}

	virtual void
	so_evt_start() override
	{
		so_5::send< hello >( m_mbox );
		so_5::send< hello >( m_mbox );
		so_5::send< hello >( m_mbox );
	}

private :
	std::string & m_dest;

	const so_5::mbox_t m_mbox;

	void
	on_messages_collected( mhood_t<typename collecting_mbox_t::messages_collected_t> cmd)
	{
		m_dest = std::to_string( cmd->size() );

		so_deregister_agent_coop_normally();
	}
};

TEST_CASE( "constexpr case" )
{
	run_with_time_limit( [] {
			std::string scenario;

			so_5::launch( [&](so_5::environment_t & env) {
						env.register_agent_as_coop(
								env.make_agent< a_test_case_t< constexpr_case > >(
										std::ref(scenario) ) );
					},
					[](so_5::environment_params_t & params) {
						params.message_delivery_tracer(
								so_5::msg_tracing::std_cout_tracer() );
					} );

			REQUIRE( scenario == "3" );
		},
		5 );
}

TEST_CASE( "runtime case" )
{
	run_with_time_limit( [] {
			std::string scenario;

			so_5::launch( [&](so_5::environment_t & env) {
						env.register_agent_as_coop(
								env.make_agent< a_test_case_t< runtime_case > >(
										std::ref(scenario) ) );
					},
					[](so_5::environment_params_t & params) {
						params.message_delivery_tracer(
								so_5::msg_tracing::std_cout_tracer() );
					} );

			REQUIRE( scenario == "3" );
		},
		5 );
}

