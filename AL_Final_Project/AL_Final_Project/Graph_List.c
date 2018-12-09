#include "Headers.h"
#define _CRT_SECURE_NO_WARNINGS

// �׷����� �ʱ�ȭ�ϸ� ���� ������ �Է��ϴ� �Լ� //
void graph_init(GraphType *g) {
	srand((unsigned)time(NULL));
	int dup;
	int vertex, edge;
	int src, dst;
	int cost;
	GraphNode *tempnode;
	g->n = MAX_VERTICES;

	// Graph�� Adjacency List�� ǥ���ϸ�, ������ ���� �ʱ�ȭ���ش�. //
	for (vertex = 0; vertex < MAX_VERTICES; vertex++) {
		g->adj_list[vertex] = NULL;
	}

	// ������ �����ϰ� �����Ѵ�.  //
	srand((unsigned)time(NULL));
	for (edge = 0; edge < MAX_EDGES; edge++) {

		src = rand() % MAX_VERTICES;
		dst = rand() % MAX_VERTICES;
		while (src == dst)
			dst = rand() % MAX_VERTICES;

		// �ߺ� Ȯ�� //
		dup = 0;

		tempnode = g->adj_list[src];
		while (tempnode != NULL) {
			if (tempnode->vertex == dst) {
				dup = 1;
				break;
			}
			else {
				tempnode = tempnode->link;
			}
		}

		// Edge ���� // 
		if (dup == 0) {
			cost = (rand() % 300) + 100; // 100 ~ 399 ����
			insert_edge(g, src, dst, cost);
		}
		else {
			// ������ �ߺ��Ǵ� ��� �ٽ� �������� �����ϵ��� edge�� 1 ���ҽ�Ų��. // 
			edge = edge - 1;
		}
	}

	// �� City�� ���� ȣ�� ������ ������ش�. ����� �ش�. //
	for (vertex = 0; vertex < MAX_VERTICES; vertex++) {
		if (g->adj_list[vertex] != NULL) {
			Node *T = (Node*)malloc(sizeof(Node));
			T->right = NULL;
			T->left = NULL;
			T->color = 0; ;
			T->parent = NULL;
			RBTree_init(T);
			g->adj_list[vertex]->hotel_Info = T;
		}
	}

	return;
}

// ������ �߰����ִ� �Լ� //
void insert_edge(GraphType *g, int u, int v, int cost) {
	char temp[10] = { 0 };
	GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
	GraphNode *vnode = (GraphNode *)malloc(sizeof(GraphNode));

	// Directed Graph �̹Ƿ� ���� ���⿡ edge���� �߰�(u) // 
	node->vertex = v;
	node->cost = cost;
	strcpy(node->cityname, "site-");
	_itoa(v, temp, 10);
	strcat(node->cityname, temp);
	node->link = g->adj_list[u];
	g->adj_list[u] = node;

	// Undirected Graph �̹Ƿ� ���� ���⿡ edge���� �߰�(v) // 
	/*
	vnode->vertex = u;
	vnode->cost = cost;
	strcpy(vnode->cityname, "site-");
	_itoa(u, temp, 10);
	strcat(vnode->cityname, temp);
	vnode->link = g->adj_list[v];
	g->adj_list[v] = vnode;
	*/

	return;
}

// Test�� ���� �Լ� //
void Graph_Display(GraphType *g) {
	int i;
	GraphNode *tmp;
	for (i = 0; i < MAX_VERTICES; i++) {
		printf("���� %d�� ��������Ʈ: ", i);
		tmp = g->adj_list[i];
		if (tmp == NULL) printf("NULL");
		while (tmp != NULL) {
			printf("->%d ", tmp->vertex);
			tmp = tmp->link;
		}
		printf("\n");
	}
	return;
}