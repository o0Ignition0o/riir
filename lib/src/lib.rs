#![crate_type = "staticlib"]

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn rust_fibonacci<'a>(n: i32) -> i32 {
    slow_fibonacci(n)
}

#[inline(always)]
pub fn slow_fibonacci(n: i32) -> i32 {
    if n < 2 {
        n
    } else {
        slow_fibonacci(n - 1) + slow_fibonacci(n - 2)
    }
}

mod tests {
    use super::*;
    #[test]
    fn test_fib_40() {
        let n = 40;
        let expected_result = 102334155;

        let actual_result = slow_fibonacci(n);

        assert_eq!(
            expected_result, actual_result,
            "fib(40) is supposed to be 102334155"
        );
    }
}
