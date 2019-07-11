#[macro_use]
extern crate bencher;

use bencher::Bencher;

#[inline(always)]
pub fn slow_fibonacci(n: i32) -> i32 {
    if n < 2 {
        n
    } else {
        slow_fibonacci(n - 1) + slow_fibonacci(n - 2)
    }
}

fn two_plus_two_benchmark(bench: &mut Bencher) {
    bench.iter(|| slow_fibonacci(30))
}

benchmark_group!(benches, two_plus_two_benchmark);
benchmark_main!(benches);
