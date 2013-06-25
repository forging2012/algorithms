#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum Color {
	RED = 0,
	BLACK = 1
}Color;

typedef struct node Node;
struct node {
	Node *left, *right, *parent;
	int key;
	int data;
	Color color;
};

Node* RBNodeAlloc(int key, int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	if (!node) {
		printf("malloc error!\n");
		exit(-1);
	}
	node->key = key, node->data = data;

	return node;
}

void inorderTreeWalk(Node* root) {
    if (root != NULL) {
        inorderTreeWalk(root->left);
        printf("[%d %d] ", root->key, root->color);
        inorderTreeWalk(root->right);
    }
}

Node* RBTreeSearch(Node* root, int value) {
	while (root != NULL && value != root->key) {
        if (value < root->key) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
 
    return root;
}

Node* treeMinimum(Node* x) {
    while (x->left != NULL) {
        x = x->left;
    }
 
    return x;
}

Node* treeMaximum(Node* x) {
    while (x->right != NULL) {
        x = x->right;
    }
 
    return x;
}

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


/*
 * -----------------------------------------------------------
 * |   x                 y
 * |  / \     ==>       / \
 * | a   y             x   c
 * |    / \           / \
 * |   b   c         a   b  
 * -----------------------------------------------------------
*/
Node* leftRotate(Node* root, Node* x) {
	// Set y.
	Node* y = x->right;

	// Turn y's left subtree into x's right subtree.
	x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }

	y->parent = x->parent;

	// Link x's parent to y.
	if (x->parent == NULL) { // When x is root.
        root = y;
    }
    else if (x == x->parent->left) { // When x is its parent's left child.
        x->parent->left = y;
    }
    else { // When x is its parent's right child.
        x->parent->right = y;
    }

	// Put x on y's left.
	y->left = x;
    x->parent = y;

	return root;
}

/*
 * -----------------------------------------------------------
 * |      x              y
 * |     / \    ==>     / \
 * |    y   c          a   x
 * |   / \                / \
 * |  a   b              b   c
 * -----------------------------------------------------------
*/
Node* rightRotate(Node* root, Node* x) {
	// Set y.
	Node* y = x->left;
	
	// Turn y's right subtree into x's left subtree.
	x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
 
    y->parent = x->parent;
	// Link x's parent to y.
	if (x->parent == NULL) { // When x is root.
        root = y;
    }
    else if (x == x->parent->left) { // When x is its parent's left child.
        x->parent->left = y;
    }
    else { // When x is its parent's right child.
        x->parent->right = y;
    }

	// Put x on y's right.
	y->right = x;
    x->parent = y;

	return root;
}

Node* RBTreeInsertFixup(Node* root, Node* z) {
	Node *zp, *zgp, *zu, *tmp; // z's parent, grandparent, uncle.
	while ((zp = z->parent) && zp->color == RED) {
		zgp = zp->parent;
		if (zp == zgp->left) {
			zu = zgp->right;
			if (zu && zu->color == RED) {
				zu->color = BLACK;
				zp->color = BLACK;
				zgp->color = RED;
				z = zgp;
			}
			else {
				if (zp->right == z) {
					root = leftRotate(root, zp);
					tmp = zp;
					zp = z;
					z = tmp;
				}
				zp->color = BLACK;
				zgp->color = RED;
				root = rightRotate(root, zgp);
			}
		}
		else
		{
			zu = zgp->left;
			if (zu && zu->color == RED) {
				zu->color = BLACK;
				zp->color = BLACK;
				zgp->color = RED;
				z = zgp;
			}
			else {
				if (zp->left == z) {
					root = rightRotate(root, zp);
					tmp = zp;
					zp = z;
					z = tmp;
				}
				zp->color = BLACK;
				zgp->color = RED;
				root = leftRotate(root, zgp);
			}
		}
	}
	root->color = BLACK;

	return root;
}

Node* RBTreeInsert(Node* root, Node* z) {
	Node* y = NULL;
    Node* x = root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
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
    else if (z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
 
 
    z->left = NULL;
    z->right = NULL;
    z->color = RED;
 
    return RBTreeInsertFixup(root, z);

}


Node* RBTreeDeleteFixup(Node* root, Node* node, Node* p) {
	Node *other, *oleft, *oright;
	while ((!node || node->color == BLACK) && node != root) {
		if (p->left == node) {
			other = p->right;
			if (other->color == RED) {
				other->color = BLACK;
				p->color = RED;
				root = leftRotate(root, p);
				other = p->right;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK)) {
				other->color = RED;
				node = p;
				p = node->parent;
			}
			else {
				if (!other->right || other->right->color == BLACK) {
					if ((oleft = other->left)) {
						oleft->color = BLACK;
					}
					other->color = RED;
					root = rightRotate(root, other);
					other = p->right;
				}
				other->color = p->color;
				p->color = BLACK;
				if (other->right) {
					other->right->color = BLACK;
				}
				root = leftRotate(root, p);
				node = root;
				break;
			}
		}
		else
		{
			other = p->left;
			if (other->color == RED) {
				other->color = BLACK;
				p->color = RED;
				root = rightRotate(root, p);
				other = p->left;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK)) {
				other->color = RED;
				node = p;
				p = node->parent;
			}
			else {
				if (!other->left || other->left->color == BLACK) {
					if ((oright = other->right)) {
						oright->color = BLACK;
					}
					other->color = RED;
					root = leftRotate(root, other);
					other = p->left;
				}

				other->color = p->color;
				p->color = BLACK;
				if (other->left) {
					other->left->color = BLACK;
				}
				root = rightRotate(root, p);
				node = root;
				break;
			}
		}
	}

	if (node) {
		node->color = BLACK;
	}

	return root;
}

Node* RBTreeDelete(Node* root, Node* z) {
	Node *zc, *zp, *zl; // z's child, parent, left.
	Node* old;
	Color color;

	old = z;

	if (z->left && z->right) {
		z = z->right;
		while ((zl = z->left) != NULL) {
			z = zl;
		}
		zc = z->right;
		zp = z->parent;
		color = z->color;
		if (zc) {
			zc->parent = zp;
		}
		if (zp) {
			if (zp->left == z) {
				zp->left = zc;
			}
			else {
				zp->right = zc;
			}
		}
		else {
			root = zc;
		}
		if (z->parent == old) {
			zp = z;
		}
		z->parent = old->parent;
		z->color = old->color;
		z->right = old->right;
		z->left = old->left;
		if (old->parent) {
			if (old->parent->left == old) {
				old->parent->left = z;
			}
			else {
				old->parent->right = z;
			}
		}
		else {
			root = z;
		}
		old->left->parent = z;
		if (old->right) {
			old->right->parent = z;
		}
	}
	else {
		if (!z->left) {
			zc = z->right;
		}
		else if (!z->right) {
			zc = z->left;
		}
		zp = z->parent;
		color = z->color;
		if (zc) {
			zc->parent = zp;
		}
		if (zp) {
			if (zp->left == z) {
				zp->left = zc;
			}
			else {
				zp->right = zc;
			}
		}
		else {
			root = zc;
		}
	}
	free(old);

	if (color == BLACK) {
		root = RBTreeDeleteFixup(root, zc, zp);
	}

	return root;
}



int main() {

	int i, count = 20;
	int key;
	Node* root = NULL, *node = NULL;
	srand(time(NULL));
	for (i = 1; i < count; ++i) {
		key = rand() % count;
		Node* n = RBNodeAlloc(key, i);
		if ((root = RBTreeInsert(root, n))) {
			printf("[i = %d] insert key %d success!\n", i, key);
		}
		else {
			printf("[i = %d] insert key %d error!\n", i, key);
			exit(-1);
		}
	
		inorderTreeWalk(root);
		printf("\n");

		if ((node = RBTreeSearch(root, key))) {
			printf("[i = %d] search key %d success!\n", i, key);
		}
		else {
			printf("[i = %d] search key %d error!\n", i, key);
			exit(-1);
		}

		if (!(i % 10)) {
			if ((root = RBTreeDelete(root, n))) {
				printf("[i = %d] delete key %d success\n", i, key);
			}
			else {
				printf("[i = %d] delete key %d error\n", i, key);
			}
		}

		inorderTreeWalk(root);
		printf("\n");
	}

	return 0;
}

