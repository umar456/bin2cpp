BIN2CPP
=======

Converts files from a binary to C++ headers. It is similar to bin2c and xxd 
but adds support for namespaces. Created this to convert OpenCL kernels to
C++ headers.

Usage
-----


| Option        | Description                                                       |
|---------------|-------------------------------------------------------------------|
| --name        | name of the variable (default: var)                               |
| --file        | input file                                                        |
| --output      | output file (If no output is specified then it prints to stdout   |
| --type        | Type of variable (default: char)                                  |
| --namespace   | A space seperated list of namespaces                              |
| --formatted   | Tabs for formatting                                               |
| --version     | Prints my name                                                    |
| --help        | Prints usage info                                                 |

Example
-------

Input File:
```
// blah.txt
blah blah blah
```

Command:
```
./bin2cpp --file blah.txt --namespace blah detail --formatted --name blah_var
```

Will produce:

```cpp
#include <cstddef>
namespace blah {
	namespace detail {
		static const char blah_var[] = {
			0x2f,	0x2f,	0x20,	0x62,	0x6c,	0x61,	0x68,	0x2e,	0x74,	0x78,
			0x74,	0xa,	0x62,	0x6c,	0x61,	0x68,	0x20,	0x62,	0x6c,	0x61,
			0x68,	0x20,	0x62,	0x6c,	0x61,	0x68,	0xa,	};
		static const size_t blah_var_len = 27;
	}
}
```

