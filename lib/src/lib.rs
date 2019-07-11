#![crate_type = "staticlib"]
#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn rust_fibonacci(n: i32) -> i32 {
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

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn external_rust_to_lower(c: &mut u8) {
    c.make_ascii_lowercase();
}

#[inline(always)]
pub fn rust_to_lower(c: &mut char) {
    c.make_ascii_lowercase();
}

mod tests {
    use super::*;

    #[test]
    fn test_valid_upper_case_character() {
        let mut c = 'C';
        let expected_result = 'c';

        rust_to_lower(&mut c);

        assert_eq!(c, expected_result, "Lowercase C is supposed to be c");
    }

    #[test]
    fn test_external_valid_upper_case_character() {
        let mut c = 'C' as u8;
        let expected_result = 'c';

        external_rust_to_lower(&mut c);

        assert_eq!(
            c as char, expected_result,
            "Lowercase C is supposed to be c"
        );
    }

    #[test]
    fn test_valid_lower_case_character() {
        let mut c = 'e';
        let expected_result = 'e';

        rust_to_lower(&mut c);

        assert_eq!(c, expected_result, "Lowercase c is supposed to be c");
    }

    #[test]
    fn test_invalid_character() {
        let mut c = '1';
        let expected_result = '1';

        rust_to_lower(&mut c);

        assert_eq!(c, expected_result, "Lowercase 1 is supposed to be 1");
    }

    #[test]
    fn test_fib_40() {
        // SETUP PHASE
        let n = 40;
        let expected_result = 102334155;
        // RUN PHASE
        let actual_result = slow_fibonacci(n);
        // ASSERT PHASE
        assert_eq!(
            expected_result, actual_result,
            "fib(40) is supposed to be 102334155"
        );
    }
}
