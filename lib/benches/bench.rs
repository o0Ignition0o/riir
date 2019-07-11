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

#[inline(always)]
pub fn rust_to_lower(c: &mut char) {
    c.make_ascii_lowercase();
}

fn two_plus_two_benchmark(bench: &mut Bencher) {
    bench.iter(|| slow_fibonacci(40))
}

fn to_lower_benchmark(bench: &mut Bencher) {
    bench.iter(|| {
        bencher::black_box({
            let mut my_char = 'C';
            rust_to_lower(&mut my_char);
        })
    })
}

benchmark_group!(benches, two_plus_two_benchmark, to_lower_benchmark);
benchmark_main!(benches);
