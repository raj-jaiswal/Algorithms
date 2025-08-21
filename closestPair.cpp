#include <bits/stdc++.h>
using namespace std;

void print(vector<vector<int>>& points){
    for(auto& point: points){
        cout << point[0] << ", " << point[1] << endl;
    }
}

void swap(vector<vector<int>>& points, int a, int b){
    vector<int> temp = points[a];
    points[a] = points[b];
    points[b] = temp;
}

void normalize(vector<vector<int>>& points, int start, int end){
    int a = start;
    int b = end;
    int mid = (int)((start+end)/2);

    if(points[a][0] > points[b][0])
        swap(points, a, b);

    if(points[a][0] > points[mid][0])
        swap(points, a, mid);
    
    if(points[mid][0] > points[b][0])
        swap(points, mid, b);
    
    swap(points, mid, a);
}

void quicksort(vector<vector<int>>& points, int start, int end){
    if(start >= end) return;

    normalize(points, start, end);
    int pivot = points[start][0];

    int left = start + 1;
    int right = end;
    while(left <= right){
        while(points[left][0] <= pivot){
            left++;
        }
        while(points[right][0] >= pivot){
            right--;
        }
        if(left < right){
            swap(points, left, right);
        }
    }
    swap(points, start, right);
    quicksort(points, start, right - 1);
    quicksort(points, right + 1, end);
}

vector<vector<int>> closestPair(vector<vector<int>> points, int start, int end){

}

int main() {
    vector<vector<int>> points = {
        {2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10},
        {3, 4}, {18, 7}, {25, 20}, {30, 15}, {50, 25},
        {7, 9}, {14, 5}, {9, 14}, {35, 40}, {45, 12},
        {20, 30}, {22, 8}, {28, 18}, {33, 25}, {38, 35}
    };

    quicksort(points, 0, points.size() - 1);
    vector<vector<int>> closest = closestPair(points, 0, points.size() - 1);
    print(points);
}