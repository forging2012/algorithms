#include <iostream>
#include <limits>

using namespace std;

// <<Introduction to Algorithms>> P197.


/*
A0: 30*35
A1: 35*15
A2: 15*5
A3: 5*10
A4: 10*20
A5: 20*25
*/

const int MATRIX_NUM = 6;
int p[MATRIX_NUM + 1] = {30, 35, 15, 5, 10, 20, 25};
int m[MATRIX_NUM][MATRIX_NUM] = {{0}, {0}, {0}, {0}, {0}, {0}};
int s[MATRIX_NUM][MATRIX_NUM] = {{0}, {0}, {0}, {0}, {0}, {0}};

int recursionChainOrder(int i, int j) {

    if (i == j) {
        return 0;
    }

    if (i > j) {
        cout << "Error!" << endl;
        return -1;
    }

    if (i < j) {
        int min = numeric_limits<int>::max();
        for (int k = i; k < j; k++) {
            int tmp = recursionChainOrder(i, k) + recursionChainOrder(k + 1, j) + p[i] * p[k + 1] * p[j + 1];
            if (tmp < min) {
                min = tmp;
            }
        }

        return min;

    }

    return 0;

}


void dpChainOrder() {

    for (int i = 0; i < MATRIX_NUM; i++) {
        m[i][i] = 0;
    }

    // l is the chain length.
    for (int l = 2; l <= MATRIX_NUM; l++) {
        for (int i = 0; i <= MATRIX_NUM - l; i++) {
            int j = i + l - 1;
            m[i][j] = numeric_limits<int>::max();
            for (int k = i; k <= j - 1; k++) {
                int tmp = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (tmp < m[i][j]) { 
                    m[i][j] = tmp;
                    s[i][j] = k;
                }
            }
        } 
    }

}


void dpPrintChainOrder(int i, int j) {

    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
        dpPrintChainOrder(i, s[i][j]);
        dpPrintChainOrder(s[i][j] + 1, j);
        cout << ")";
    }

}


int main() {

    // Recursion way.
    //cout << recursionChainOrder(0, 5) << endl;

    // DP way.
    dpChainOrder();
    cout << m[0][5] << endl;
    dpPrintChainOrder(0, 5);
    cout << endl;

    return 0;

}
