#include <iostream>
#include <cstdlib> 
#include <ctime> 

using namespace std;

template <typename T>
class NDArray {
public:
    int x, y;
    T** arr;

    void how_fill_array(char c) {
        if (c == 'n') {
            create_array();
            null_array();
        } else if (c == 'o') {
            create_array();
            ones_array();
        } else if (c == 'r') {
            create_array();
            random_array();
        } else {
            create_array();
        }
    }

    void create_array() {
        arr = new T*[y];
        for (int i = 0; i < y; i++) {
            arr[i] = new T[x];
        }
    }

    void null_array() {
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                arr[i][j] = 0;
            }
        }
    }

    void ones_array() {
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                arr[i][j] = 1;
            }
        }
    }

    void random_array() {
        srand((unsigned)time(0));
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                arr[i][j] = rand() % 10;
            }
        }
    }

    void del_array() {
        for (int i = 0; i < y; i++) {
            delete[] arr[i];
        }
    }
    
    NDArray(int _x) { 
        x = _x; y = 1;
        how_fill_array('s');
    }
    NDArray(int _x, char _c) { 
        x = _x; y = 1;
        how_fill_array(_c);
    }
    NDArray(int _x, int _y) { 
        x = _x; y = _y;
        how_fill_array('s');
    }
	NDArray(int _x, int _y, char _c) { 
        x = _x; y = _y;
        how_fill_array(_c);
    }
    
    T* operator [](const int& i) const {return arr[i];}
    NDArray operator =(const NDArray& a) const {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                arr[i][j] = a[i][j];
            }
        }
    }
    NDArray operator +=(const T& num) const {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                arr[i][j] += num;
            }
        }
    }
    NDArray operator -=(const T& num) const {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                arr[i][j] -= num;
            }
        }
    }
    NDArray operator *=(const T& num) const {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                arr[i][j] *= num;
            }
        }
    }
    NDArray operator /=(const T& num) const {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                arr[i][j] /= num;
            }
        }
    }

    T arrMin() {
        T min = arr[0][0];
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (arr[i][j] < min) {
                    min = arr[i][j];
                }
            }
        }
        return min;
    }
    T* arrMin(int shape) {
        if (shape == 0) {
            T* min = new T[y];
            for (int i = 0; i < y; i++) {
                min[i] = arr[i][0];
                for (int j = 0; j < x; j++) {
                    if (arr[i][j] < min[i]) {
                        min[i] = arr[i][j];
                    }
                }
            }
            return min;
        } else if (shape == 1) {
            T* min = new T[x];
            for (int i = 0; i < x; i++) {
                min[i] = arr[0][i];
                for (int j = 0; j < y; j++) {
                    if (arr[j][i] < min[i]) {
                        min[i] = arr[j][i];
                    }
                }
            }
            return min;
        }
    }

    T arrMax() {
        T max = arr[0][0];
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (arr[i][j] > max) {
                    max = arr[i][j];
                }
            }
        }
        return max;
    }
    T* arrMax(int shape) {
        if (shape == 0) {
            T* max = new T[y];
            for (int i = 0; i < y; i++) {
                max[i] = arr[i][0];
                for (int j = 0; j < x; j++) {
                    if (arr[i][j] > max[i]) {
                        max[i] = arr[i][j];
                    }
                }
            }
            return max;
        } else if (shape == 1) {
            T* max = new T[x];
            for (int i = 0; i < x; i++) {
                max[i] = arr[0][i];
                for (int j = 0; j < y; j++) {
                    if (arr[j][i] > max[i]) {
                        max[i] = arr[j][i];
                    }
                }
            }
            return max;
        }
    }

    float arrAvg() {
        int sum = 0;
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                sum += arr[i][j];
            }
        }
        return sum / (float)(x) / (float)(y);
    }
    float* arrAvg(int shape) {
        if (shape == 0) {
            float* sum = new float[y];
            for (int i = 0; i < y; i++) {
                sum[i] = 0.0;
                for (int j = 0; j < x; j++) {
                    sum[i] += arr[i][j];
                }
                sum[i] /= (float)(y);
            }
            return sum;
        } else if (shape == 1) {
            float* sum = new float[x];
            for (int i = 0; i < x; i++) {
                sum[i] = 0.0;
                for (int j = 0; j < y; j++) {
                    sum[i] += arr[j][i];
                }
                sum[i] /= (float)(x);
            }
            return sum;
        }
    }

    void matrMult(NDArray A, NDArray B) {
        null_array();
        for (int i = 0; i < A.y; i++) {
            for (int j = 0; j < A.y; j++) {
                for (int k = 0; k < A.x; k++) {
                    arr[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    void matrTrans() {
        NDArray M(y, x);
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                M[j][i] = arr[i][j];
            }
        }
        del_array();
        x = M.x;
        y = M.y;
        create_array();
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                arr[i][j] = M[i][j];
            }
        }
    }
};