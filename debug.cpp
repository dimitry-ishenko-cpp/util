////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "util/debug.hpp"
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////
namespace util
{

////////////////////////////////////////////////////////////////////////////////
namespace { bool debug_mode = false, debug_set = false; }

bool debug() noexcept
{
    if(!debug_set)
    {
        debug_mode = std::getenv("DEBUG");
        debug_set = true;
    }
    return debug_mode;
}

void debug(bool new_mode) noexcept { debug_mode = new_mode; debug_set = true; }

////////////////////////////////////////////////////////////////////////////////
namespace { bool trace_mode = false, trace_set = false; }

bool trace() noexcept
{
    if(!trace_set)
    {
        trace_mode = std::getenv("TRACE");
        trace_set = true;
    }
    return trace_mode;
}

void trace(bool new_mode) noexcept { trace_mode = new_mode; trace_set = true; }

////////////////////////////////////////////////////////////////////////////////
}
