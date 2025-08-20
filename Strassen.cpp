#include <bits/stdc++.h>
using namespace std;

class Matrix{
public:
    vector<vector<int>> vals;
    int n;

    Matrix(int size){
        this -> n = size;
        for(int i=0; i<size; i++){
            vector<int> a;
            this -> vals.push_back(a);
            for(int j=0; j<size; j++){
                this -> vals[i].push_back(0);
            }
        }
    }
    
    void input(){
        for(int i=0; i < this -> n; i++){
            for(int j=0; j<this -> n; j++){
                int c;
                cin >> c;
                this -> vals[i][j] = c;
            }
        }
    }

    void print(){
        cout << "\n";
        for(int i=0; i < this -> n; i++){
            for(int j=0; j < this -> n; j++){
                cout << this -> vals[i][j] << " ";
            }
            cout << endl;
        }
    }

    
    Matrix operator+(Matrix& other){
        if (this -> n != other.n) return NULL;

        Matrix sum(this -> n);
        for(int i=0; i < this -> n; i++){
            for(int j=0; j < this -> n; j++){
                sum.vals[i][j] = this->vals[i][j] + other.vals[i][j];
            }
        }

        return sum;
    }

    Matrix operator-(Matrix& other){
        if (this -> n != other.n) return NULL;

        Matrix diff(this -> n);
        for(int i=0; i < this -> n; i++){
            for(int j=0; j < this -> n; j++){
                diff.vals[i][j] = this->vals[i][j] - other.vals[i][j];
            }
        }

        return diff;
    }

    Matrix operator*(const Matrix& other){
        if (this -> n != other.n) return NULL;

        Matrix prod(this -> n);
        for(int i=0; i < this->n; i++){
            for(int j=0; j<this->n; j++){
                int sum=0;
                for(int k=0; k<this->n; k++){
                    sum += this -> vals[i][k] * other.vals[k][j];
                }
                prod.vals[i][j] = sum;
            }
        }

        return prod;
    }
};

Matrix split(Matrix mat, int x1, int x2, int y1, int y2){
    Matrix A(x2-x1);
    for(int i=y1; i<y2; i++){
        for(int j=x1; j<x2; j++){
            A.vals[i-y1][j-x1] = mat.vals[i][j];
        }
    }
    return A;
}

Matrix merge(Matrix mat1, Matrix mat2, Matrix mat3, Matrix mat4){
    int n = mat1.n;
    Matrix A(n * 4);
    for(int i=0; i<n*2; i++){
        for(int j=0; j<n*2; j++){
            if(i<n && j<n){
                A.vals[i][j] = mat1.vals[i][j];
            }
            else if(i<n && j>=n){
                A.vals[i][j] = mat2.vals[i][j-n];
            }
            else if(i>=n && j<n){
                A.vals[i][j] = mat3.vals[i-n][j];
            }
            else if(i>=n && j>=n){
                A.vals[i][j] = mat4.vals[i-n][j-n];
            }
        }
    }
    return A;
}

Matrix strassen(Matrix A, Matrix B){
    if(A.n <= 2){
        return A * B;
    }

    int mid = A.n / 2;
    Matrix A11 = split(A, 0,   mid, 0,   mid);
    Matrix A12 = split(A, mid, A.n, 0,   mid);
    Matrix A21 = split(A, 0,   mid, mid, A.n);
    Matrix A22 = split(A, mid, A.n, mid, A.n);

    Matrix B11 = split(B, 0,   mid, 0,   mid);
    Matrix B12 = split(B, mid, B.n, 0,   mid);
    Matrix B21 = split(B, 0,   mid, mid, B.n);
    Matrix B22 = split(B, mid, B.n, mid, B.n);

    Matrix P1 = strassen(A11, B12 - B22);
    Matrix P2 = strassen(A11 + A12, B22);
    Matrix P3 = strassen(A21 + A22, B11);
    Matrix P4 = strassen(A22, B21 - B11);
    Matrix P5 = strassen(A11 + A22, B11 + B22);
    Matrix P6 = strassen(A12 - A22, B21 + B22);
    Matrix P7 = strassen(A11 - A21, B11 + B12);

    Matrix C11 = P5 + P4 - P2 + P6;
    Matrix C12 = P1 + P2;
    Matrix C21 = P3 + P4;
    Matrix C22 = P5 + P1 - P3 - P7;

    Matrix prod = merge(C11, C12, C21, C22);
    return prod;
}

int main(){
    int n;
    cout << "Enter Size: ";
    cin >> n;

    Matrix A(n);
    Matrix B(n);

    cout << "\nEnter A: " << endl;
    A.input();
    cout << "\nEnter B: " << endl;
    B.input();

    cout << "Product: ";
    strassen(A,B).print();
    // vector<vector<int>> prod = multiply(A, B);
    // print(prod);
}