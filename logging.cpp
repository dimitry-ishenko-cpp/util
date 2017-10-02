////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "util/debug.hpp"
#include "util/logging.hpp"

#include <iostream>
#include <syslog.h>

////////////////////////////////////////////////////////////////////////////////
namespace util
{

////////////////////////////////////////////////////////////////////////////////
namespace { bool console = true; }
bool send_to_console() noexcept { return console; }
void send_to_console(bool x) noexcept { console = x; }

////////////////////////////////////////////////////////////////////////////////
namespace { bool syslog = false; }
bool send_to_syslog() noexcept { return syslog; }
void send_to_syslog(bool x) noexcept { syslog = x; }

////////////////////////////////////////////////////////////////////////////////
stream::stream(const std::string& name, level l) : level_(l)
{ if(name.size()) *this << name << ": "; }

////////////////////////////////////////////////////////////////////////////////
stream::~stream()
{
    std::ostream* os; int pri;

    switch(level_)
    {
    case level::dbg:
        if(!debug()) return;
        os = &std::cout; pri = LOG_DEBUG;
        break;

    case level::info: os = &std::cout; pri = LOG_INFO; break;
    case level::warn: os = &std::cerr; pri = LOG_WARNING; break;
    case level::err : os = &std::cerr; pri = LOG_ERR; break;

    default: return;
    }

    auto s = str();
    if(send_to_console()) (*os) << s << std::endl;
    if(send_to_syslog()) ::syslog(pri, "%s", s.data());
}

////////////////////////////////////////////////////////////////////////////////
}
