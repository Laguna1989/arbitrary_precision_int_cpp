# Arbitrary Precision Integer
[![Build Status](https://github.com/Laguna1989/arbitrary_precision_int_cpp/actions/workflows/test_verification.yml/badge.svg)](https://github.com/Laguna1989/arbitrary_precision_int_cpp/actions/workflows/unittests.yml)
## How to run unittests

```shell
mkdir build
cd build
cmake ..
cmake --build .
./unittests
```


## Code usage

```c++
#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <iostream>

int main(){
    auto const api_1 = api::from_uint64(100*2);
    auto const api_2 = api::from_uint64(123456);
    
    auto const api_3 = api_1 * api_2 * api_2;
    
    std::cout << api_3.to_string() << std::endl;
}
```
