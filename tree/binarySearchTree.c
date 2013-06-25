#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node {
	int value;
	Node* parent;
	Node* left;
	Node* right;
};

Node* nodeAlloc() {
	return (Node*) malloc(sizeof(Node));
}

// Walk Tree.
void inorderTreeWalk(Node* root) {
	if (root != NULL) {
		inorderTreeWalk(root->left);
		printf("%d ", root->value);
		inorderTreeWalk(root->right);
	}
}

// Search Tree.
Node* recursionSearch(Node* root, int key) {
	if (root == NULL || key == root->value) {
		return root;
	}
	else if (key < root->value) {
		return recursionSearch(root->left, key);
	}
	else {
		return recursionSearch(root->right, key);
	}
}
Node* nonrecursionSearch(Node* root, int key) {
	while (root != NULL && key != root->value) {
		if (key < root->value) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}

	return root;
}

// Min value.
Node* treeMinimum(Node* x) {
	while (x->left != NULL) {
		x = x->left;
	}

	return x;
}
// Max value.
Node* treeMaximum(Node* x) {
	while (x->right != NULL) {
		x = x->right;
	}

	return x;
}

// Successor of x.
Node* treeSuccessor(Node* x) {
	if (x->right != NULL) {
		return treeMinimum(x->right);
	}
	else {
		Node* y = x->parent;
		while (y != NULL && x == y->right) {
			x = y;
			y = y->parent;
		}

		return y;
	}
}
// Predecessor of x.
Node* treePredecessor(Node* x) {
	if (x->left != NULL) {
		return treeMaximum(x->left);
	}
	else {
		Node* y = x->parent;
		while (y != NULL && x != y->right) {
			x = y;
			y = y->parent;
		}

		return y;
	}
}

// Insert a node.
void treeInsert(Node* root, Node* z) {
	Node* y = NULL;
	Node* x = root;
	while (x != NULL) {
		y = x;
		if (z->value < x->value) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	z->parent = y;

	if (y == NULL) {
		root = z;
	}
	else {
		if (z->value < y->value) {
			y->left = z;
		}
		else {
			y->right = z;
		}
	}
}
// Delete a node.
Node* treeDelete(Node* root, Node* z) {
	Node* x = NULL;
	Node* y = NULL;
	if (z->left == NULL || z->right == NULL) {
		y = z;
	}
	else {
		y = treeSuccessor(z);
	}

	if (y->left != NULL) {
		x = y->left;
	}
	else {
		x = y->right;
	}

	if (x != NULL) {
		x->parent = y->parent;
	}

	if (y->parent == NULL) {
		root = x;
	}
	else {
		if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = y;
		}
	}

	if (y != z) {
		z->value = y->value;
	}

	return y;
}

int main() {
	// Create tree.
	Node* n4 = nodeAlloc();
	n4->value = 2;
	n4->left = NULL;
	n4->right = NULL;

	Node* n5 = nodeAlloc();
	n5->value = 4;
	n5->left = NULL;
	n5->right = NULL;

	Node* n2 = nodeAlloc();
	n2->value = 3;
	n2->left = n4;
	n2->right = n5;

	Node* n6 = nodeAlloc();
	n6->value = 8;
	n6->left = NULL;
	n6->right = NULL;

	Node* n3 = nodeAlloc();
	n3->value = 7;
	n3->left = NULL;
	n3->right = n6;

	Node* root = nodeAlloc();
	root->value = 5;
	root->left = n2;
	root->right = n3;

	root->parent = NULL;
	n2->parent = root;
	n3->parent = root;
	n4->parent = n2;
	n5->parent = n2;
	n6->parent = n3;


	// Walk tree.
	inorderTreeWalk(root);
	printf("\n");

	// Recursion search.
	Node* resultNode = recursionSearch(root, 8);
	printf("Recursion search result: %d\n", resultNode->value);
	// Nonrecursion search.
	resultNode = nonrecursionSearch(root, 8);
	printf("Nonrecursion search result: %d\n", resultNode->value);

	// Min value.
	resultNode = treeMinimum(root);
	printf("Minimum: %d\n", resultNode->value);
	// Max value.
	resultNode = treeMaximum(root);
	printf("Maximum: %d\n", resultNode->value);
	
	// Tree successor.
	resultNode = treeSuccessor(n3); 
	printf("Successor of %d is %d\n", n3->value, resultNode->value);
	// Tree predecessor.
	resultNode = treePredecessor(n3);
	printf("Predecessor of %d is %d\n", n3->value, resultNode->value);

	// Insert node.
	Node* n7 = nodeAlloc();
	n7->value = 6;
	treeInsert(root, n7);
	inorderTreeWalk(root);
	printf("\n");

	// Delete node.
	treeDelete(root, n7);
	inorderTreeWalk(root);
	printf("\n");
	free(n7);


	free(root);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	free(n6);	

	return 0;
}
