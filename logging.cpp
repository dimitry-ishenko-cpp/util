////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "logging.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <syslog.h>

////////////////////////////////////////////////////////////////////////////////
namespace util
{

////////////////////////////////////////////////////////////////////////////////
static bool debug_ = false, set_debug_ = true;

bool send_debug() noexcept
{
    if(set_debug_)
    {
        debug_ = std::getenv("DEBUG");
        set_debug_ = false;
    }
    return debug_;
}

void send_debug(bool x) noexcept { debug_ = x; set_debug_ = false; }

////////////////////////////////////////////////////////////////////////////////
static bool console_ = true;
bool send_to_console() noexcept { return console_; }
void send_to_console(bool x) noexcept { console_ = x; }

////////////////////////////////////////////////////////////////////////////////
static bool syslog_ = false;
bool send_to_syslog() noexcept { return syslog_; }
void send_to_syslog(bool x) noexcept { syslog_ = x; }

////////////////////////////////////////////////////////////////////////////////
stream::stream(const std::string& name, level l) : level_(l)
{ if(name.size()) *this << name << ": "; }

////////////////////////////////////////////////////////////////////////////////
stream::~stream()
{
    std::ostream* os; int pri;

    switch(level_)
    {
    case level::debug:
        if(!send_debug()) return;
        os = &std::cout; pri = LOG_DEBUG;
        break;

    case level::info : os = &std::cout; pri = LOG_INFO; break;
    case level::warn : os = &std::cerr; pri = LOG_WARNING; break;
    case level::error: os = &std::cerr; pri = LOG_ERR; break;

    default: return;
    }

    auto s = str();
    if(send_to_console()) (*os) << s << std::endl;
    if(send_to_syslog())
#ifndef _WIN32
        syslog(pri, "%s", s.data());
#else
        throw std::logic_error("Not implemented");
#endif
}

////////////////////////////////////////////////////////////////////////////////
}
