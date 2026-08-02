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

./build/example/example
```


## Usage

```cpp
using namespace libcsv;

struct person { ... };

template <>
inline auto reader<person, 4>::convert(container data) -> person {
    return { ... };
}

auto main(int, char**) -> int {
    std::stringstream ss {
        R"("Smith, John",30,"New York","Loves coding, reading, and \"coffee\"")"};

    reader<person, 4> r {ss};

    const auto opt {r.get()};
    const auto& p {opt.value_or({})};

    ...

    return 0;
}
```

> Look at [example](example) for more
