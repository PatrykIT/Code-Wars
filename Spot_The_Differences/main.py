def spot_diff(s1, s2):
    if s1 == s2:
        return []

    differences = []
    counter = 0
    for letter in s1:
        if letter == s2[counter]:
            pass
        else:
            differences.append(counter)
        counter += 1

    return differences

print (spot_diff('abcdefg', 'abcqetg'))