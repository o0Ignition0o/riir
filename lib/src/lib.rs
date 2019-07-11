#![crate_type = "staticlib"]

use std::os::raw::c_char;

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn net_to_lower_case(str_ptr: *mut c_char, len: usize) {
    let slice = unsafe { std::slice::from_raw_parts_mut(str_ptr, len) };
    for n in 0..len {
        slice[n] = (slice[n] as u8).to_ascii_lowercase() as c_char;
    }
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn external_rust_to_lower(c: &mut u8) {
    c.make_ascii_lowercase();
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn to_lower(c: *mut c_char) {
    rust_to_lower(unsafe { &mut *(c as *mut i8 as *mut u8) });
}

#[inline(always)]
pub fn rust_to_lower(c: &mut u8) {
    c.make_ascii_lowercase();
}

mod tests {
    use super::*;

    #[test]
    fn test_net_to_lower_case() {
        let mut actual_slice = b"HeLlO WoRlD".to_vec();
        let expected_slice = b"hello world";
        net_to_lower_case(actual_slice.as_mut_ptr() as *mut c_char, actual_slice.len());

        assert_eq!(actual_slice, expected_slice);
    }

    #[test]
    fn test_valid_upper_case_character() {
        let mut c = b'C';
        let expected_result = b'c';

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
        let mut c = b'e';
        let expected_result = b'e';

        rust_to_lower(&mut c);

        assert_eq!(c, expected_result, "Lowercase c is supposed to be c");
    }

    #[test]
    fn test_invalid_character() {
        let mut c = b'1';
        let expected_result = b'1';

        rust_to_lower(&mut c);

        assert_eq!(c, expected_result, "Lowercase 1 is supposed to be 1");
    }
}
