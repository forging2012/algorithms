#include <stdio.h>

void maxHeapify(int* a, int i, int N) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;

	if (left < N && a[left] > a[i]) {
		largest = left;
	}
	else {
		largest = i;
	}

	if (right < N && a[right] > a[largest]) {
		largest = right;
	}

	if (largest != i) {
		int tmp = a[i];
		a[i] = a[largest];
		a[largest] = tmp;

		maxHeapify(a, largest, N);
	}
}

void buildMaxHeap(int* a, int N) {
	int i = 0;
	for (i = (N-1)/2; i >= 0; i--) {
		maxHeapify(a, i, N);
	}
}

void heapSort(int* a, int N) {
	buildMaxHeap(a, N);

	int i = 0;
	for (i = N - 1; i >= 1; i--) {
		int tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;

		maxHeapify(a, 0, i);
	}
}

int main() {
	int a[10] = {10, 2, 10, 9, 7, 8, 6, 5, 3, 4};
	heapSort(a, 10);

	int i = 0;
	for (i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
