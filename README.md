# Library of utility C++ classes

## Getting Started

### Prerequisites

None.

### Installation

Add as a submodule into an existing project:
```
git submodule add https://github.com/dimitry-ishenko/util.git
```

### Usage

Logging example 1:
```c++
#include "util/debug.hpp"
#include "util/logging.hpp"

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        std::string arg = argv[1];
        if(arg == "-d" || arg == "--debug") util::debug(true);
        if(arg == "-q" || arg == "--quiet") util::send_to_console(false);
    }

    using namespace util::logging;

    info() << "Starting " << argv[0];

    if(!util::debug())
    {
        info() << "Add -d or --debug parameter to show debug messages.";
        info() << "Or define the DEBUG environment variable.";
    }

    for(int n = 0; n < 10; ++n) dbg() << "Message " << '#' << n;

    if(util::send_to_console())
    {
        info() << "Add -q or --quiet to run in quiet mode.";
    }

    warn() << "Exiting now!";
    return 0;
}
```
Output with no args:
```
Starting ./runme
Add -d or --debug parameter to show debug messages.
Or define the DEBUG environment variable.
Add -q or --quiet to run in quiet mode.
Exiting now!
```
Output with --debug:
```
Starting ./runme
Message #0
Message #1
Message #2
Message #3
Message #4
Message #5
Message #6
Message #7
Message #8
Message #9
Add -q or --quiet to run in quiet mode.
Exiting now!
```

Logging example 2:
```c++
#include "util/debug.hpp"
#include "util/logging.hpp"

class foo : private util::logger
{
public:
    foo() : util::logger("foo")
    {
        dbg() << "Constructing";
        // do something
    }

    ~foo()
    {
        dbg() << "Destructing";
        // do something
    }

    void bar(int baz)
    {
        info() << "Running bar(" << baz << ")";
        // do something
        if(baz < 0) err() << "Negative baz";
    }
};

int main(int argc, char* argv[])
{
    using namespace util::logging;
    util::debug(true);
    util::send_to_syslog(true);

    info() << "Starting " << argv[0];

    foo instance;
    instance.bar(-1);

    warn() << "Exiting now!";
    return 0;
}
```
Output:
```
Starting ./runme
foo: Constructing
foo: Running bar(-1)
foo: Negative baz
Exiting now!
foo: Destructing
```

## Authors

* **Dimitry Ishenko** - dimitry (dot) ishenko (at) (gee) mail (dot) com

## License

This project is distributed under the GNU GPL license. See the
[LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
