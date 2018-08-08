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
#include "util/logging.hpp"
using namespace util::logging;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        std::string arg = argv[1];
        if(arg == "-d" || arg == "--debug") util::debug(true);
        if(arg == "-q" || arg == "--quiet") util::send_to_console(false);
    }

    info() << "Starting " << argv[0];

    if(!util::debug())
    {
        info() << "Add -d or --debug parameter";
        info() << "or define DEBUG environment variable";
        info() << "to show debug messages.";
    }

    for(int n = 0; n < 10; ++n) dbg() << "Debug " << '#' << n;

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
Add -d or --debug parameter
or define DEBUG environment variable
to show debug messages.
Add -q or --quiet to run in quiet mode.
Exiting now!
```
Output with --debug:
```
Starting ./runme
Debug #0
Debug #1
Debug #2
Debug #3
Debug #4
Debug #5
Debug #6
Debug #7
Debug #8
Debug #9
Add -q or --quiet to run in quiet mode.
Exiting now!
```

Logging example 2:
```c++
#include "util/logging.hpp"
using namespace util::logging;

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
