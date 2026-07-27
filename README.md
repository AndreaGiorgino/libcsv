# libcsv

CSV interface library in Cpp23

> [!IMPORTANT]
> Since this library is still in development, it may not work correctly or some
> functionalities might be missing

## Build

### Requirements

- [CMake](https://cmake.org/)

### Compilation

```bash
git clone https://github.com/giorgi.page/libcsv
cd libtokenizer

./build.sh
```

### Testing

```bash
cmake -B build \
    -DCSV_BUILD_TESTING=ON \
    && cmake --build build --parallel $(($(nproc) - 1)) \
    && ctest --test-dir build 
```

### Example

```bash
cmake -B build \
    -DCSV_BUILD_EXAMPLE=ON \
    && cmake --build build --parallel $(($(nproc) - 1))

cd example
./build/example
```


## Usage

```cpp
/*
 * main.cxx
 */

#include <iostream>

auto main(void) -> int {
    return 0;
}
```

> Look at [example](example) for more
