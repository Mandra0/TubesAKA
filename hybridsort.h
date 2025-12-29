#ifndef HYBRIDSORT_H_INCLUDED
#define HYBRIDSORT_H_INCLUDED
#include <vector>
#include <iostream>
using namespace std;

void insertionSort(std::vector<int>& arr, int left, int right);
void mergeSort(std::vector<int>& arr, int left, int right);
void hybridSort(std::vector<int>& arr, int left, int right, int k);

#endif // HYBRIDSORT_H_INCLUDED
