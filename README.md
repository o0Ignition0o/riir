### RIIR

This library allows me to benchmark and test C++ and Rust code before submitting pull requests.

More information on how to use it can be found on Youtube: https://www.youtube.com/watch?v=dUnGnZMPIuE

Using it requires a working version of [Rust](https://www.rust-lang.org/learn/get-started), a recent c++ compiler, as well as [Google Test](https://github.com/google/googletest) and [Google Benchmarks](https://github.com/google/benchmark).

### Usage

```bash
make test # runs all the tests
make bencher # runs all the benchmarks
```
