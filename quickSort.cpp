#include <bits/stdc++.h>
using namespace std;

void print(vector<int> arr){
    for(int i=0; i<arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

// NOTE TO SELF: This method of swapping may produce 0 if both A and B have same values.
void swap(vector<int>& arr, int a, int b){
    if(arr[a] == arr[b]) return;
    arr[a] = arr[a] + arr[b];
    arr[b] = arr[a] - arr[b];
    arr[a] = arr[a] - arr[b];
}

int normalize(vector<int>& arr, int a, int b){
    int mid = (int) ((a+b)/2);
    if (arr[a] > arr[mid])
        swap(arr, a, mid);
    if (arr[a] > arr[b])
        swap(arr, a, b);
    if (arr[b] < arr[mid])
        swap(arr, b, mid);
    return mid;
}


/* UPDATED FOR MID ELEMENT OPTIMIZATION

1. mid = (low + high) / 2
2. pivot = A[mid]
3. left = low
4. right = high
5. While ( left <= right )
6.     While ( A[left] < pivot )
7.         left = left + 1
8.     While ( A[right] > pivot )
9.         right = right - 1
10.    If ( left <= right )
11.        swap(A[left], A[right])
12.        left = left + 1
13.        right = right - 1

*/

void quickSort(vector<int>& arr, int start, int stop){
    if(start>=stop) return;
    
    int mid = normalize(arr, start, stop);
    int pivot = arr[mid];
    int left = start;
    int right = stop;

    while (left <= right){
        while(arr[left] < pivot)
            left++;
        while(arr[right] > pivot)
            right--;
        if (left <= right){
            swap(arr, left, right);
            left++;
            right--;
        }
    }

    quickSort(arr, start, left-1);
    quickSort(arr, left, stop);
}

int main(){
    vector<int> vals {12,4,5,3,1,6,8,4,3,6,8,5,9};
    print(vals);

    quickSort(vals, 0, vals.size() - 1);
    print(vals);
}