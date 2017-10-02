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

## Authors

* **Dimitry Ishenko** - dimitry (dot) ishenko (at) (gee) mail (dot) com

## License

This project is distributed under the GNU GPL license. See the
[LICENSE.md](LICENSE.md) file for details.

## Acknowledgments
