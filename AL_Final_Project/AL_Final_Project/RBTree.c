#include "Headers.h"

void print_BST(Node*T, int indent) {
	Node *newnode = T;
	if (newnode != NULL) {
		if (newnode->right) print_BST(newnode->right, indent + 4);
		if (indent) {
			for (int i = 0; i < indent; i++) printf(" ");
		}
		if (newnode->right) {
			printf("/\n");
			for (int i = 0; i < indent; i++) printf(" ");
		}
		printf("%d: %s\n ", newnode->key, (newnode->color ? "RED" : "BLACK"));
		if (newnode->left) {
			for (int i = 0; i < indent; i++) printf(" ");
			printf("\\\n");
			print_BST(newnode->left, indent + 4);
		}
	}
}

void randomized(int *list) {
	srand((unsigned)time(NULL));
	int random;
	int check = 0;
	for (int i = 0; i < 20; i++) {
		random = rand() % 50;
		for (int a = 0; a < i; a++) {
			if (list[a] == random) {
				i--;
				check = 1;
			}
		}
		if (check == 0)
			list[i] = random;
		else check = 0;
	}
}

void LEFT_ROTATE(Node *P, Node* x) {
	Node* y = (Node*)malloc(sizeof(Node));
	y = x->right;

	x->right = y->left;

	if (y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;


	if (x->parent == NULL) {
		P = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RIGHT_ROTATE(Node *P, Node* x) {
	Node* y = (Node*)malloc(sizeof(Node));
	y = x->left;

	x->left = y->right;

	if (y->right != NULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;


	if (x->parent == NULL) {
		P = y;
	}
	else if (x == x->parent->right) {
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;

}

Node *Minimum(Node *T) {
	Node *x = T;
	while (x->left != NULL) {
		x = x->left;
	}
	return x;
}

Node *Maximum(Node *T) {
	Node *x = T;
	while (x->right != NULL) {
		x = x->right;
	}
	return x;
}

Node *Successor(Node *T) {
	Node *x = T;

	if (x->right != NULL)
		return Minimum(x->right);
	else {
		Node * y = x->parent;
		while (y != NULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}
}

Node *Predecessor(Node *T) {
	Node *x = T;
	Node *y;
	if (x->left != NULL)
		return Maximum(x->left);

	else {
		y = x->parent;
		while (y != NULL && x == y->left) {
			x = y;
			y = y->parent;
		}
		return y;
	}

}

void RB_DELETE_FIXUP(Node *T, Node *x) {
	Node*w;
	while (x != NULL && x != T && x->color == 0) {
		if (x == x->parent->right) {
			w = x->parent->right;
			if (w->color == 1) {
				w->color = 0;
				x->parent->color = 1;
				LEFT_ROTATE(T, x->parent);
				w = x->parent->right;
			}
			if ((w->left == NULL || w->left->color == 0) && (w->right == NULL || w->right->color == 0)) {
				w->color = 1;
				x = x->parent;
			}
			else if (w->right == NULL || w->right->color == 0) {
				w->left->color = 0;
				w->color = 1;
				RIGHT_ROTATE(T, w);
				w = x->parent->right;

			}
			w->color = x->parent->color;
			x->parent->color = 0;
			w->right->color = 0;
			LEFT_ROTATE(T, x->parent);
			x = T;
		}
		else {
			w = x->parent->left;
			if (w->color == 1)
				w->color = 0;
			x->parent->color = 1;
			printf("--%d--\n", w->parent->key);
			RIGHT_ROTATE(T, x->parent);
			w = x->parent->left;
			if (w->right->color = 0 && w->left->color == 0) {
				w->color = 1;
				x = x->parent;
			}
			else if (w->right->color = 0) {
				w->left->color = 0;
				w->color = 1;
				LEFT_ROTATE(T, w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = 0;
			w->right->color = 0;
			RIGHT_ROTATE(T, x->parent);
			x = T;
		}
	}
	if (x != NULL)
		x->color = 0;
}

Node* RB_DELETE(Node * T, int k) {
	Node *z = NULL;
	Node *temp = T; Node *y = NULL;
	Node *x = NULL;
	while (temp != NULL) {
		y = temp;
		if (k < temp->key) {
			temp = temp->left;
		}
		else if (k > temp->key) {
			temp = temp->right;
		}
		else {
			z = temp;
			break;
		}
	}
	if (temp == NULL) return T;

	if (z->left == NULL || z->right == NULL) {
		y = z;
	}
	else {
		y = Successor(z);
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
		T = x;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}

	if (y != z) {
		z->key = y->key;
	}

	if (x == NULL && y->color == 0) {
		RB_DELETE_FIXUP(T, z->parent);
	}
	if (y != NULL && y->color == 0) {
		RB_DELETE_FIXUP(T, x);
	}

	Node *imsi = T;
	while (imsi->parent != NULL) {
		imsi = imsi->parent;
	}
	return imsi;

}

void RB_INSERT_FIXUP(Node *T, Node *z) {

	//Node *y = (Node*)malloc(sizeof(Node));
	//y->color = 1; y->left = NULL; y->right = NULL; y->parent = NULL;
	Node *y = NULL;

	while (z != T && z->parent->color == 1 && z->color != 0) {

		if (z->parent == z->parent->parent->left) {

			y = z->parent->parent->right;

			if (y != NULL &&y->color == 1) {
				z->parent->color = 0;
				y->color = 0;
				z->parent->parent->color = 1;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					LEFT_ROTATE(T, z);
				}

				z->parent->color = 0;
				z->parent->parent->color = 1;
				RIGHT_ROTATE(T, z->parent->parent);
			}

		}
		else {
			y = z->parent->parent->left;

			if (y != NULL && y->color == 1) {
				z->parent->color = 0;
				y->color = 0;
				z->parent->parent->color = 1;
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					RIGHT_ROTATE(T, z);
				}
				z->parent->color = 0;
				z->parent->parent->color = 1;
				LEFT_ROTATE(T, z->parent->parent);
			}
		}

	}
	Node*imsi = T;
	while (imsi->parent != NULL) {
		imsi = imsi->parent;
	}

	imsi->color = 0;
}

Node* RB_INSERT(Node *T, int k) {
	Node *z = (Node*)malloc(sizeof(Node));
	z->key = k; z->left = NULL; z->right = NULL; z->parent = NULL; z->color = 1;

	Node *y;
	Node *x;

	y = NULL;
	x = T;

	while (x != NULL) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else if (z->key == x->key) {
			return T;
		}
		else {
			x = x->right;
		}
	}

	z->parent = y; //z 의 위치를 찾고, parent 의 연결

	if (y == NULL) {// z 가 root 자리로.... 원래의 T는 어디로?
		T = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;
	}

	z->left = NULL;
	z->right = NULL;
	z->color = 1;

	RB_INSERT_FIXUP(T, z);
	Node * imsi = T;
	while (imsi->parent != NULL) {
		imsi = imsi->parent;
	}
	return imsi;

}

int height(Node *T) {
	if (T == NULL) {
		return 0;
	}
	else {
		int leftHeight = height((*T).left);
		int rightHeight = height((*T).right);

		if (leftHeight > rightHeight) {
			return(leftHeight + 1);
		}
		else {
			return (rightHeight + 1);
		}
	}
}

Node* RBTree_init(Node * T) {
	int index;
	int cost[NUMBER_OF_HOTEL];

	// 호텔 가격을 결정하는 부분 //
	for (index = 0; index < NUMBER_OF_HOTEL; index++) {
		cost[index] = 50 + 10 * index;
	}
	T->key = cost[0];
	Node *root = T;

	for (index = 1; index < NUMBER_OF_HOTEL; index++) {
		root = RB_INSERT(root, cost[index]);
	}

	return root;
}