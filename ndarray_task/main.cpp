#include "ndarray.h"
#include <iostream>

using namespace std;

template <typename T>
void print(T* arr, int sp) {
    cout << "(";
    cout << arr[0];
    for (int i = 1; i < sp; i++) {
        cout << "; " << arr[i];
    }
    cout << ")\n";
}

template <typename T>
void printMatr(T** arr, int x, int y) {
    for (int i = 0; i < y; i++) {
        cout << "|";
        for (int j = 0; j < x; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << "|\n";
    }
}

int main () {
    cout << "\n<int> Empty array" << endl;
    NDArray<int> Sarr(2);
    cout << "(0) = " << Sarr[0][0] << endl;
    cout << "(1) = " << Sarr[0][1] << endl;
    cout << "(0) + (1) = " << Sarr[0][0] + Sarr[0][1] << endl;

    cout << "\n<int> Null array" << endl;
    NDArray<int> Narr(2, 'n');
    cout << "(0) = " << Narr[0][0] << endl;
    cout << "(1) = " << Narr[0][1] << endl;
    cout << "(0) + (1) = " << Narr[0][0] + Narr[0][1] << endl;

    cout << "\n<int> Ones array" << endl;
    NDArray<int> Oarr(2, 'o');
    cout << "(0) = " << Oarr[0][0] << endl;
    cout << "(1) = " << Oarr[0][1] << endl;
    cout << "(0) + (1) = " << Oarr[0][0] + Oarr[0][1] << endl;

    cout << "\n<float> Random array from 0 to 10" << endl;
    NDArray<float> Rarr(2, 2, 'r');
    printMatr(Rarr.arr, Rarr.x, Rarr.y);
    cout << endl;

    cout << "Min = " << Rarr.arrMin() << endl;
    cout << "Max = " << Rarr.arrMax() << endl;
    cout << "Avg = " << Rarr.arrAvg() << endl;
    cout << "Min rows = ";
    print(Rarr.arrMin(0), 2);
    cout << "Min columns = ";
    print(Rarr.arrMin(1), 2);
    cout << "Max rows = ";
    print(Rarr.arrMax(0), 2);
    cout << "Max columns = ";
    print(Rarr.arrMax(1), 2);
    cout << "Avg rows = ";
    print(Rarr.arrAvg(0), 2);
    cout << "Avg columns = ";
    print(Rarr.arrAvg(1), 2);

    cout << "\n(0)(0) + 0.2 = " << Rarr[0][0] + 0.2 << endl;
    cout << ">> Rarr[0][0] = 0.1;" << endl;
    Rarr[0][0] = 0.1;
    cout << "(0)(0) + 0.2 = " << Rarr[0][0] + 0.2 << "\n\n";

    cout << ">> Rarr += 3.3;" << endl;
    Rarr += 3.3;
    printMatr(Rarr.arr, Rarr.x, Rarr.y);
    cout << endl;

    cout << ">> Rarr -= 1;" << endl;
    Rarr -= 1;
    printMatr(Rarr.arr, Rarr.x, Rarr.y);
    cout << endl;

    cout << ">> Rarr *= 3.3;" << endl;
    Rarr *= 1.7;
    printMatr(Rarr.arr, Rarr.x, Rarr.y);
    cout << endl;

    cout << ">> Rarr /= 3.3;" << endl;
    Rarr /= 1.7;
    printMatr(Rarr.arr, Rarr.x, Rarr.y);
    cout << endl;

    cout << ">> NDArray<float> copy(2, 2);" << endl;
    NDArray<float> copy(2, 2);
    cout << ">> copy = Rarr;" << endl;
    copy = Rarr;
    printMatr(copy.arr, copy.x, copy.y);
    cout << endl;

    cout << "Matrix Mult" << endl;
    NDArray<int> A(2, 3, 'r');
    cout << "A" << endl;
    printMatr(A.arr, A.x, A.y);
    cout << endl;

    NDArray<int> B(3, 2, 'r');
    cout << "B" << endl;
    printMatr(B.arr, B.x, B.y);
    cout << endl;

    NDArray<int> C(3, 3);
    C.matrMult(A, B);
    cout << "C = A * B" << endl;
    printMatr(C.arr, C.x, C.y);
    cout << endl;

    cout << "Matrix Transpolation" << endl;
    cout << "A" << endl;
    printMatr(A.arr, A.x, A.y);
    cout << endl;

    A.matrTrans();

    cout << "A^T" << endl;
    printMatr(A.arr, A.x, A.y);
    cout << endl;

    return 0;
}