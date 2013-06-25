#include <stdio.h>

void swap(int* x, int* y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
int partition(int* a, int p, int r) {
	int i = p - 1;
	int j = 0;
	for (j = p; j <= r-1; j++) {
		if (a[j] <= a[r]) {
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i+1], &a[r]);

	return i+1;
}
void quickSort(int* a, int p, int r) {
	if (p < r) {
		int q = partition(a, p, r);
		quickSort(a, p, q-1);
		quickSort(a, q+1, r);
	}
}
int main() {
	int a[10] = {1, 2, 10, 9, 8, 4, 5, 6, 3, 7};
	quickSort(a, 0, 9);
	int i = 0;
	for (i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
