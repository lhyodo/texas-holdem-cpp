#ifndef QUICKSORT
#define QUICKSORT


#include <stdio.h>
#include <iostream>
#include <array>
#include "Card.cpp"


int Partition(Card *arr, int low, int high)
{
    int pivot = low;
    int item_from_left = low;
    int item_from_right = high;

    while (item_from_left <= item_from_right)
    {
        while (arr[item_from_left] <= arr[pivot])
        {
            ++item_from_left;
        }
        while (arr[item_from_right] > arr[pivot])
        {
            --item_from_right;
        }
        if (item_from_left < item_from_right)
        {
            Card temp = arr[item_from_left];
            arr[item_from_left] = arr[item_from_right];
            arr[item_from_right] = temp;
            ++item_from_left;
            --item_from_right;
        }
    }
    // item_from_left has crossed item_from_right
    Card temp = arr[pivot];
    arr[pivot] = arr[item_from_right];
    arr[item_from_right] = temp;

    return item_from_right; // returns the element that has found its definite position
}

void quickSort(Card *arr, int low, int high)
{
    if (low >= high) // base case there is only one element
        return;
    else
    {
        // recursive case
        int index = Partition(arr, low, high); // partition returns the element that has found its definite position
        quickSort(arr, low, index - 1);        // sort the group that is less than arr[index]
        quickSort(arr, index + 1, high);       // sort the group that is greater than arr[index]
    }
    return;
}
#endif