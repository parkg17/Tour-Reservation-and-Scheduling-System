#pragma once

#define NUMBER_OF_HOTEL 100

typedef struct _node {
	int key;
	int color; // color ==0 -> black , color ==1 -> white
	struct _node *parent;
	struct _node *left;
	struct _node *right;
} Node;

void print_BST(Node*T, int indent);
void randomized(int *list);
void LEFT_ROTATE(Node *P, Node* x);
void RIGHT_ROTATE(Node *P, Node* x);
Node *Minimum(Node *T);
Node *Maximum(Node *T);
Node *Successor(Node *T);
Node *Predecessor(Node *T);
void RB_DELETE_FIXUP(Node *T, Node *x);
Node* RB_DELETE(Node * T, int k);
void RB_INSERT_FIXUP(Node *T, Node *z);
Node* RB_INSERT(Node *T, int k);
int height(Node *T);
Node* RBTree_init(Node * T);