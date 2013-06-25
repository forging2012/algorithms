#include <stdio.h>
#include <stdlib.h>

void countingSort(int* a, int* b, int k, int N) {
	int* c = (int*) malloc((k+1) * sizeof(int));
	int i = 0;
	for (i = 0; i <= k; i++) {
		c[i] = 0;
	}	

	for (i = 0; i < N; i++) {
		c[a[i]]++;
	}

	for (i = 1; i <= k; i++) {
		c[i] = c[i-1] + c[i];
	}

	for (i = 0; i < N; i++) {
		b[c[a[i]]-1] = a[i];
		c[a[i]]--;
	}
}

int main() {
	// All elements are in [0, 9].
	int a[10] = {9, 8, 9, 0, 7, 2, 3, 5, 3, 9};
	int b[10] = {0};

	countingSort(a, b, 9, 10);

	int i = 0;
	for (i = 0; i < 10; i++) {
		printf("%d ", b[i]);
	} 
	printf("\n");
	
	return 0;
}
