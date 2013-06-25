#include <iostream>

using namespace std;

// <<Introduction to Algorithms>> P223.


const int N = 11;

// a[0] and a[n+1] is virtual. f[0]=0 and s[n+1]=MAX.
int s[N + 2] = {-1, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, 9999};
int f[N + 2] = {0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1};
int c[N + 2][N + 2];

int recurionActivitySelector(int i, int j) {

    if (i >= j) {
        return 0;
    } 

    if (i < j) {
        int max = 0;
        for (int k = i + 1; k < j; k++) {
            if (f[i] <= s[k] && s[k] < f[k] && f[k] <= s[j]) {
                int tmp = recurionActivitySelector(i, k) + recurionActivitySelector(k, j) + 1;
                if (tmp > max) {
                    max = tmp;
                }
            }
        }

        return max;
    }


    return 0;
}


void dpActivitySelector() {
    
    // Initialize.
    for (int i = 1; i <= N; i++) {
	for (int j = i; j <= N; j++) {
	    c[i][j] = 1; 
	}

    }

    // When length is 1, the c[i][i]=1.
    // Initialize has done this.
    //for (int i = 1; i <= N; i++) {
    //	c[i][i] = 1;
    //}
 

    // When length is 2.
    for (int i = 1; i <= N - 1; i++) {
	if (f[i] <= s[i + 1]) {
	    c[i][i + 1] = 2;
	}
	else {
	    c[i][i + 1] = 1;
	}
    }

    // When length is 3 to N.
    for (int l = 3; l <= N; l++) {
        for (int i = 1; i <= N - l + 1; i++) {
            int j = i + l - 1;
            for (int k = i + 1; k < j; k++) {
                if (f[i] <= s[k] && s[k] < f[k] && f[k] <= s[j]) {
                    int tmp = c[i][k - 1] + c[k + 1][j] + 1;
                    if (tmp > c[i][j]) {
                        c[i][j] = tmp;
                    }
                }
            }
        }
    }

    // Print.
    for (int i = 1; i <= N; i++) {
	for (int j = i; j <= N; j++) {
	    cout << "c[" << i << "][" << j << "]=" << c[i][j] << ", "; 
	}

    }

}


// Greedy strategy: Always select the activity which can finish first in the rest activities.
int greedyActivitySelector() {

    int count = 1; // a1
    cout << "a[1] ";
    int i = 1;
    for (int m = 2; m <= N; m++) {
        if (s[m] >= f[i]) {
            count++;
            i = m;
            cout << "a[" << m << "] ";
        }
    
    }

    return count;

}


int main() {
    
    // Recursion way.
    //cout << recurionActivitySelector(0, N + 1) << endl; 

    // DP way.
    dpActivitySelector();
    cout << c[1][N] << endl;

    // Greedy way.
    //cout << greedyActivitySelector() << endl;
   

    return 0;
}
