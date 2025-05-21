import random


def test_functions():
    for _ in range(2,25):
        i = random.randint(100,1000)
        print(i)
        print("bit calculation: ", get_closest_value_with_same_weight(i))
        print("brute force: ", brute_force(i))


def get_closest_value_with_same_weight(value: int):
    #find the first two bits that are not the same and then flip them

    mask = 1
    first_bit = value & mask != 0

    mask <<= 1
    next_bit = value & mask != 0

    while first_bit == next_bit:
        mask <<= 1
        first_bit = next_bit
        next_bit = value & mask != 0
        

    mask |= mask >> 1

    return value ^ mask

    

def brute_force(value: int):
    weight = hamming_weight(value)

    step = 1

    while True:
        if hamming_weight(value-step) == weight:
            return value-step
        elif hamming_weight(value+step) == weight:
            return value+step
        step += 1


def hamming_weight(value: int):
    count = 0
    mask = 1

    while mask <= value:
        if value & mask:
            count += 1
        mask <<= 1

    return count
    
if __name__ == '__main__':
    test_functions()
    #print(get_closest_value_with_same_weight(2))