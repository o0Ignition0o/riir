#![crate_type = "staticlib"]
//#![feature(test)]
//extern crate test;

use std::slice;
use std::str;

#[inline]
fn try_apply_digit(current_octet: u8, digit_to_apply: u8) -> Option<u8> {
    current_octet.checked_mul(10)?.checked_add(digit_to_apply)
}

pub fn is_valid_ipv4_addr<'a>(addr: &'a [u8]) -> bool {
    let mut current_octet: Option<u8> = None;
    let mut dots: u8 = 0;
    for c in addr {
        let c = *c as char;
        match c {
            '.' => {
                match current_octet {
                    None => {
                        // starting an octet with a . is not allowed
                        return false;
                    }
                    Some(_) => {
                        dots = dots + 1;
                        current_octet = None;
                    }
                }
            }
            // The caracter is not a digit
            no_digit if no_digit.to_digit(10).is_none() => {
                return false;
            }
            digit => {
                match current_octet {
                    None => {
                        // Unwrap is sound because it has been checked in the previous arm
                        current_octet = Some(digit.to_digit(10).unwrap() as u8);
                    }
                    Some(octet) => {
                        if let Some(0) = current_octet {
                            // Leading 0 is not allowed
                            return false;
                        }
                        if let Some(applied) =
                            try_apply_digit(octet, digit.to_digit(10).unwrap() as u8)
                        {
                            current_octet = Some(applied);
                        } else {
                            // Multiplication or Addition overflowed
                            return false;
                        }
                    }
                }
            }
        }
    }
    dots == 3 && current_octet.is_some()
}

#[inline]
fn try_apply_opt_digit(current_octet: Option<u8>, digit_to_apply: u8) -> Option<u8> {
    if current_octet.is_none() {
        return Some(digit_to_apply);
    }
    current_octet.unwrap().checked_mul(10)?.checked_add(digit_to_apply)
}

#[inline]
fn try_parse_digit<'a>(digit: &'a str) -> Option<u8> {
    let mut res: Option<u8> = None;
    for d in digit.chars() {
        if let Some(applied) = try_apply_opt_digit(res, d as u8) {
            res = Some(applied);
        } else {
            return None;
        }
    }
    res
}

pub fn is_valid_ipv4_addr_readable<'a>(addr: &'a str) -> bool {
    let mut n = 0;
    for digit in addr.split('.') {
        n += 1;
        if n > 4 {
            return false;
        }

        // Starting an octet with a . is not allowed.
        if digit.len() == 0 {
            return false;
        }

        if let Some(_) = try_parse_digit(digit) {
            continue;
        } else {
            // Parsed garbage, out-of-range, or otherwise invalid number.
            return false;
        }
    }
    n == 4
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn rust_net_is_valid_ipv4_addr<'a>(addr: &'a u8, addrLen: i32) -> bool {
    let address = unsafe { slice::from_raw_parts(addr, addrLen as usize) };
    is_valid_ipv4_addr(address)
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn rust_net_is_valid_ipv4_addr_readable<'a>(addr: &'a u8, addrLen: i32) -> bool {
    let address = str::from_utf8(unsafe { slice::from_raw_parts(addr, addrLen as usize) });
    if address.is_err() {
        return false;
    }
    is_valid_ipv4_addr_readable(address.unwrap())
}
/*
#[cfg(test)]
mod tests {
    use is_valid_ipv4_addr;
    use is_valid_ipv4_addr_readable;
    use test::{black_box, Bencher};


    #[bench]
    fn bench_is_valid_ipv4_address_full_digits_more_readable(bench: &mut Bencher) {
        let ip: &str = "192.168.101.117";
        bench.iter(|| black_box(is_valid_ipv4_addr_readable(ip)));
    }

    #[bench]
    fn bench_is_valid_ipv4_address_full_digits(bench: &mut Bencher) {
        let ip: [u8; 15] = [
            '1' as u8, '9' as u8, '2' as u8, '.' as u8, '1' as u8, '6' as u8, '8' as u8, '.' as u8,
            '1' as u8, '0' as u8, '1' as u8, '.' as u8, '1' as u8, '1' as u8, '7' as u8,
        ];
        bench.iter(|| black_box(is_valid_ipv4_addr(&ip)));
    }
}
*/