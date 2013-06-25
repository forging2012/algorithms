#include <iostream>
#include <limits>

using namespace std;

// <<Introduction to Algorithms>> P215.

const int N = 5;
double p[N + 1] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
double q[N + 1] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

double e[N + 2][N + 1];
double w[N + 2][N + 1];
int root[N + 1][N + 1];


double computeW(int i, int j) {

    double result = q[i - 1];
    for (int k = i; k <= j; k++) {
        result += p[k] + q[k]; 
    }

    return result;
}


double recursionOptimalBST(int i, int j) {
    
    if (j == i - 1) {
        return q[i - 1];
    }

    if (i <= j) {
        double min = numeric_limits<double>::max();
        for (int r = i; r <= j; r++) {
            double tmp = recursionOptimalBST(i, r - 1) + recursionOptimalBST(r + 1, j) + computeW(i, j);
            if (tmp < min) {
                min = tmp;
            }
        }

        return min;
    }



    return 0.0;
}


void dpOptimalBST() {
    
    for (int i = 1; i <= N + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];   
    } 

    for (int l = 1; l <= N; l++) {
        
        for (int i = 1; i <= N - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = numeric_limits<double>::max();
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                double tmp = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (tmp < e[i][j]) {
                    e[i][j] = tmp;
                    root[i][j] = r;
                }
            }
   
        }

    }


}


int main() {

    // Recursion way.
    cout << recursionOptimalBST(1, 5) << endl;

    // DP way.
    dpOptimalBST();
    cout << e[1][5] << endl;


    return 0;
}
