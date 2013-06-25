#include <stdio.h>
#include <stdlib.h>

void merge(int* a, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;

	int* L = (int*) malloc(n1 * sizeof(int));
	int* R = (int*) malloc(n2 * sizeof(int));

	int i = 0;
	int j = 0;

	for (i = 0; i < n1; i++) {
		L[i] = a[p+i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = a[q+1+j];
	}

	i = j = 0;
	int k = 0;
	for (k = p; k <= r; k++) {
		if (i >= n1 && j < n2) {
			a[k] = R[j];
			j++;
		}
		else if (j >= n2 && i < n1) {
			a[k] = L[i];
			i++;
		}
		else {
			if (L[i] < R[j]) {
				a[k] = L[i];
				i++;
			}
			else {
				a[k] = R[j];
				j++;
			}
		}
	}

	free(L);
	free(R);
}
void mergeSort(int* a, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(a, p, q);
		mergeSort(a, q+1, r);
		merge(a, p, q, r);
	}
}

int main() {
	int a[10] = {1, 10, 9, 7, 8, 6, 5, 2, 3, 4};
	mergeSort(a, 0, 9);
	int i = 0;
	for (i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
