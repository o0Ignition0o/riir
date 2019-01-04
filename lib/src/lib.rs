#![crate_type = "staticlib"]

#[inline(always)]
fn try_apply_digit(current_octet: u8, digit_to_apply: u8) -> Option<u8> {
    current_octet.checked_mul(10)?.checked_add(digit_to_apply)
}

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn rust_net_is_valid_ipv4_addr<'a>(addr: &'a u8, addrLen: i32) -> bool {
    let address = unsafe { std::slice::from_raw_parts(addr, addrLen as usize) };
    is_valid_ipv4_addr(address)
}

#[inline(always)]
pub fn is_valid_ipv4_addr<'a>(addr: &'a [u8]) -> bool {
    let mut current_octet: Option<u8> = None;
    let mut dots: u8 = 0;
    for c in addr {
        let c = *c as char;
        match c {
            '.' => {
                if current_octet.take().is_some() {
                    dots += 1;
                } else {
                    // Starting with a . is not allowed
                    return false;
                }
            }
            // The character is not a digit
            _ if !c.is_digit(10) => {
                return false;
            }
            digit => {
                match current_octet.take() {
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

#[no_mangle]
#[allow(non_snake_case)]
pub extern "C" fn rust_net_is_valid_ipv6_addr<'a>(addr: &'a u8, addrLen: i32) -> bool {
    let address = unsafe { std::slice::from_raw_parts(addr, addrLen as usize) };
    is_valid_ipv6_addr(address)
}

#[inline(always)]
fn is_hex_digit(c: char) -> bool {
    match c {
        '0'..='9' => true,
        'a'..='f' => true,
        'A'..='F' => true,
        _ => false,
    }
}
#[inline(always)]
pub fn is_valid_ipv6_addr<'a>(addr: &'a [u8]) -> bool {
    let mut double_colon = false;
    let mut colon_before = false;
    let mut digits: u8 = 0;
    let mut blocks: u8 = 0;

    // The smallest ipv6 is unspecified (::)
    // The IP starts with a single colon
    if addr.len() < 2 || addr[0] == b':' && addr[1] != b':' {
        return false;
    }
    //Enumerate with an u8 for cache locality
    for (i, c) in (0u8..).zip(addr) {
        match c {
            _ if is_hex_digit(*c as char) => {
                //(*maybe_digit as char).is_digit(16) => {
                // Too many digits in the block
                if digits == 4 {
                    return false;
                }
                colon_before = false;
                digits += 1;
            }
            b':' => {
                // Too many columns
                if double_colon && colon_before || blocks == 8 {
                    return false;
                }
                if !colon_before {
                    if digits != 0 {
                        blocks += 1;
                    }
                    digits = 0;
                    colon_before = true;
                } else if !double_colon {
                    double_colon = true;
                }
            }
            b'.' => {
                // IPv4 from the last block
                if is_valid_ipv4_addr(&addr[(i - digits) as usize..]) {
                    return double_colon && blocks < 6 || !double_colon && blocks == 6;
                }
                return false;
            }
            _ => {
                // Invalid character
                return false;
            }
        }
    }
    if colon_before && !double_colon {
        // The IP ends with a single colon
        return false;
    }
    if digits != 0 {
        blocks += 1;
    }

    double_colon && blocks < 8 || !double_colon && blocks == 8
}
