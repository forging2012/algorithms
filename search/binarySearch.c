#include <stdio.h>

int binarySearch(int* a, int key, int N) {
	int low = 0;
	int high = N - 1;
	int mid = (low + high) / 2;
	while (low <= high) {
		mid = (low + high) / 2;
		if(a[mid] == key) {
			return mid;
		}
		else if (a[mid] > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return -1;
}

int main() {
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	int index = binarySearch(a, 3, 10);
	printf("Index of search result: %d\n", index);	

	return 0;
}
