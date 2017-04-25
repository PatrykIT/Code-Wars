def split_workload(workload):
    if not workload:
        return None, None

    left = 0
    right = sum(workload)

    ratio = abs(left - right)
    closest_match = ratio
    best_split_place = 0
    counter = 0

    for number in workload:
        counter += 1

        left = left + number
        right = right - number
        ratio = abs(left - right)

        if ratio < closest_match:
            closest_match = ratio
            best_split_place = counter

    return best_split_place, closest_match




split_workload([1, 6, 2, 3, 5, 4, 1])