def two_by_two(animals):
    if not animals:
        return False

    result = {}
    for animal in animals:
        if animal in result:
            result[animal] = result[animal] + 1
        else:
            result[animal] = 1

    for animal, occurences in list(result.items()):
        if occurences < 2:
            result.pop(animal)
        else:
            result[animal] = 2

    return result




print (two_by_two([]))
