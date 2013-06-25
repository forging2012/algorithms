#include <iostream>

using namespace std;

// <<Introduction to Algorithms>> P211.

const int M = 7;
char x[M + 1] = {' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
const int N = 6;
char y[N + 1] = {' ', 'B', 'D', 'C', 'A', 'B', 'A'};
int c[M + 1][N + 1];

int recursionLCS(int m, int n) {

    if (m == 0 || n == 0) {
        return 0;
    }

    if (m > 0 && n > 0 && x[m] == y[n]) {
        return recursionLCS(m - 1, n - 1) + 1;
    }

    if (m > 0 && n > 0 && x[m] != y[n]) {
        int tmp1 = recursionLCS(m, n - 1);
        int tmp2 = recursionLCS(m - 1, n);
        if (tmp1 > tmp2) {
            return tmp1;
        }
        else {
            return tmp2;
        }
    }



    return -1;
}


void dpLCS() {

    for (int i = 1; i <= M; i++) {
        c[i][0] = 0;
    }

    for (int j = 0; j <= N; j++) {
        c[0][j] = 0;
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
            }
            else {
                c[i][j] = c[i][j - 1];
            }
        }

    }

}


void dpPrintLCS(int i, int j) {

    if (i == 0 || j == 0) {
        return;
    }

    if (x[i] == y[j]) {
        dpPrintLCS(i - 1, j - 1);
        cout << x[i] << " ";
    }
    else if (c[i - 1][j] >= c[i][j - 1]) {
        dpPrintLCS(i - 1, j);
    }
    else {
        dpPrintLCS(i, j - 1);
    }
 
}

int main() {


    cout << recursionLCS(M, N) << endl;
    
    
    dpLCS();
    cout << c[M][N] << endl;
    dpPrintLCS(M, N);
    cout << endl;

    return 0;

}
