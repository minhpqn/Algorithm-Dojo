""" Count the number of inversions in the array
    Read integers from
"""

def load():
    filename = 'SmallIntegerArray.txt'
    filename = 'IntegerArray.txt'
    numbers = []
    try:
        with open(filename, 'r') as f:
            for line in f:
                line = line.strip()
                if line == '':
                    continue
                numbers.append(int(line))
    except IOError:
        print('Could not open file IntegerArray.txt to read')

    return numbers    

def brute_force(numbers):
    count = 0
    size = len(numbers)
    for i in range(0, size-1):
        for j in range(i+1, size):
            if numbers[i] > numbers[j]:
                count += 1
                
    return count

def sort_and_count(numbers):
    n = len(numbers)
    if n == 1:
        return (numbers, 0)

    sorted_left, x  = sort_and_count(numbers[0:int(n/2)])
    sorted_right, y = sort_and_count(numbers[int(n/2):n])

    sorted_numbers, z = count_split_inv(sorted_left, sorted_right)

    return (sorted_numbers, x + y + z)

def count_split_inv(b, c):
    """ b and c are two sorted arrays
    """

    BIG_INT = 999999999999
    
    z = 0
    n = len(b) + len(c)
    d = [0 for i in range(n)]
    i = 0
    j = 0
    b.append(BIG_INT)
    c.append(BIG_INT)
    for k in range(n):
        if b[i] < c[j]:
            d[k] = b[i]
            i += 1
        elif c[j] < b[i]:
            d[k] = c[j]
            z += len(b) - i - 1
            j += 1

    return (d, z)        

if __name__ == '__main__':
    numbers = load()
    # count = brute_force(numbers)
    # print('Number of inversions (by brute-force) = %d' % count)
    
    _, count = sort_and_count(numbers)

    print('Number of integers in the array = %d' % len(numbers))

    print('Number of inversions = %d' % count)


