#TODO: TEST IT!!!!


def quicksort(array):
    left_index = 0;
    right_index = len(array) - 1;
    quicksort_rec(array, left_index, right_index)


def quicksort_rec(array, left_bound, right_bound):
    if (left_bound >= right_bound):
        return
    
    left_index = left_bound
    right_index = right_bound

    pivot_index = left_bound
    pivot_value = array[pivot_index]

    while (left_index < right_index):
        if (left_index > right_index):
            break
        while (array[left_index] <= pivot_value):
            left_index += 1
            if (left_index >= right_bound or left_index > right_index):
                break
        if (array[left_index] > pivot_value):
            while (array[right_index] > pivot_value):
                right_index -= 1
                if (right_index <= left_bound or right_index < left_index):
                    break
            if (right_index > left_index):
                switch(array, left_index, right_index)
    if (right_index == left_index):
        right_index -= 1

    switch(array, pivot_index, right_index)
    quicksort_rec(array, left_bound, right_index - 1)
    quicksort_rec(array, left_index, right_bound)


def switch(array, index1, index2):
    temp = array[index1];
    array[index1] = array[index2]
    array[index2] = temp


array = [15, 3, 7, 4, 25, 3, 26, 9, 11]
print(array)

quicksort(array)
print(array)
    
