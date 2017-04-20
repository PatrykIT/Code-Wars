#https://www.codewars.com/kata/temperature-analysis-ii/train/python

def Check_if_Closer_Positive(number, number2):
    if number - abs(number2) <= 0:
        return True
    else:
        return False

def Check_if_Closer_Negative(number, number2):
    if number - abs(number2) > 0:
        return True
    else:
        return False



def close_to_zero(t):
    print ("String: " + t)
    if not t:
        return 0
    numbers = [int(n) for n in t.split()]
    closest_to_zero = numbers[0]
    if 0 in numbers:
        return 0
    for temperature in numbers:
        #Handle negatives
        if (temperature < 0 ):
            if(temperature > closest_to_zero):
                closest_to_zero = temperature
            elif(Check_if_Closer_Negative(closest_to_zero, temperature)) == True:
                closest_to_zero = temperature
        #Handle positives
        elif(temperature > 0):
            if(temperature < closest_to_zero):
                closest_to_zero = temperature
            if(Check_if_Closer_Positive(temperature, closest_to_zero)) == True:
                closest_to_zero = temperature



    return closest_to_zero



print (close_to_zero("6 2 -1"))