#include <iostream>

using namespace std;

// <<Introduction to Algorithms>> P193.

const int LINE_NUM = 2;
const int STATION_NUM = 6;

int e[LINE_NUM][1] = {{2}, {4}};
int x[LINE_NUM][1] = {{3}, {2}};
int a[LINE_NUM][STATION_NUM] = {{7, 9, 3, 4, 8, 4}, {8, 5, 6, 4, 5, 7}};
int t[LINE_NUM][STATION_NUM - 1] = {{2, 3, 1, 3, 4}, {2, 1, 2, 2, 1}};
int f[LINE_NUM][STATION_NUM] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int l[LINE_NUM][STATION_NUM] = {{-1, 0, 0, 0, 0, 0}, {-1, 0, 0, 0, 0, 0}};;
int ff = 0;
int ll = 0;



int recursionFastestLine(int n) {

    static int lineMark = 0;
    int num0 = 0;
    int num1 = 0;
    if (n == 0) {
	num0 = e[0][0] + a[0][0];
	num1 = e[1][0] + a[1][0];
	if (num0 <= num1) {
	    lineMark = 0;
	    return num0;
	}
	else {
	    lineMark = 1;
	    return num1;
	}
    }
    else {
	if (lineMark == 0) {
	    if (n == STATION_NUM - 1) {
		num0 = recursionFastestLine(n - 1) + a[0][n] + x[0][0];
		num1 = recursionFastestLine(n - 1) + t[0][n - 1] + a[1][n] + x[1][0];
	    }
	    else {
		num0 = recursionFastestLine(n - 1) + a[0][n];
		num1 = recursionFastestLine(n - 1) + t[0][n - 1] + a[1][n];
	    }

	    if (num0 <= num1) {
		lineMark = 0;
		return num0;
	    }
	    else {
		lineMark = 1;
		return num1;
	    }
	}

	if (lineMark == 1) {
	    if (n == STATION_NUM - 1) {
		num0 = recursionFastestLine(n - 1) + t[1][n - 1] + a[0][n] + x[0][0];
		num1 = recursionFastestLine(n - 1) + a[1][n] + x[1][0];
	    }
	    else {
		num0 = recursionFastestLine(n - 1) + t[1][n - 1] + a[0][n];
		num1 = recursionFastestLine(n - 1) + a[1][n];
	    }

	    if (num0 <= num1) {
                lineMark = 0;
                return num0;
            }
            else {
                lineMark = 1;
                return num1;
            }
	}	

    }


    // Error.
    return -1;

}


void dpFastestLine() {
    f[0][0] = e[0][0] + a[0][0];
    f[1][0] = e[1][0] + a[1][0];

    for (int j = 1; j < STATION_NUM; j++) {
	if (f[0][j - 1] + a[0][j] <= f[1][j - 1] + t[1][j - 1] + a[0][j]) {
	    f[0][j] = f[0][j - 1] + a[0][j];
	    l[0][j] = 0;
	}
	else {
	    f[0][j] = f[1][j - 1] + t[1][j - 1] + a[0][j];
	    l[0][j] = 1;
	}

	if (f[1][j - 1] + a[1][j] <= f[0][j - 1] + t[0][j - 1] + a[1][j]) {
	    f[1][j] = f[1][j - 1] + a[1][j];
	    l[1][j] = 1;
	}
	else {
	    f[1][j] = f[0][j - 1] + t[0][j - 1] + a[1][j];
	    l[1][j] = 0;
	}
	
    }

    
    if (f[0][STATION_NUM - 1] + x[0][0] <= f[1][STATION_NUM - 1] + x[1][0]) {
	ff = f[0][STATION_NUM - 1] + x[0][0];
	ll = 0;
    }
    else {
	ff = f[1][STATION_NUM - 1] + x[1][0];
	ll = 1;
    }
    
}
    
void dpPrintStation() {
    int i = ll;

    cout << "line " << i << ", station" << STATION_NUM - 1 << endl;

    for (int j = STATION_NUM - 1; j >= 1; j--) {
	i = l[i][j];
	cout << "line " << i << ", station" << j - 1 << endl;
    }

    cout << ff << endl;

}


int main() {

    // Recurvison method.
    //cout << recursionFastestLine(STATION_NUM - 1) << endl;

    // DP method.
    dpFastestLine();
    dpPrintStation();


    return 0;
}
