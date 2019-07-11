#[macro_use]
extern crate bencher;
use bencher::Bencher;


#[inline(always)]
pub fn rust_to_lower(c: &mut char) {
    c.make_ascii_lowercase();
}

fn to_lower_benchmark(bench: &mut Bencher) {
    bench.iter(|| {
        bencher::black_box({
            let mut my_char = 'C';
            rust_to_lower(&mut my_char);
        })
    })
}

benchmark_group!(benches, to_lower_benchmark);
benchmark_main!(benches);
