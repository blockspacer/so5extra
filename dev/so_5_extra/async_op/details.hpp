/*!
 * \file
 * \brief Various details for implementation of async operations.
 *
 * \since
 * v.1.0.4
 */

#pragma once

#include <so_5/rt/h/agent.hpp>
#include <so_5/rt/h/adhoc_agent_wrapper.hpp>

namespace so_5 {

namespace extra {

namespace async_op {

namespace details {

/*!
 * \name Helper functions for translation various type of message targets to message boxes.
 * \{
 */

inline const ::so_5::mbox_t &
target_to_mbox( const ::so_5::mbox_t & mbox )
	{ return mbox; }

inline const ::so_5::mbox_t &
target_to_mbox( const ::so_5::agent_t & agent )
	{ return agent.so_direct_mbox(); }

inline const ::so_5::mbox_t &
target_to_mbox( const ::so_5::adhoc_agent_definition_proxy_t & agent )
	{ return agent.direct_mbox(); }

/*!
 * \}
 */

} /* namespace details */

} /* namespace async_op */

} /* namespace extra */

} /* namespace so_5 */

