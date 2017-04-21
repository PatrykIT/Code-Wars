def is_bouncy(number):
    if(number < 101):
        return False

    increasing_counter = 0
    decreasing_counter = 0
    same_number_counter = 0

    digits = list(str(number))  # Split number into single digits.
    first_digit = digits[0]

    for digit in digits[1:]:
        if digit > first_digit:
            increasing_counter += 1
        elif digit < first_digit:
            decreasing_counter += 1
        else:
            same_number_counter += 1

        first_digit = digit

    increasing_counter = increasing_counter + same_number_counter
    decreasing_counter = decreasing_counter + same_number_counter

    if increasing_counter == len(digits) -1:
        return False;
    if decreasing_counter == len(digits) -1:
        return False;
    return True;





print (is_bouncy(101))