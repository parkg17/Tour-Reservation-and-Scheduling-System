#include "Headers.h"
#define _CRT_SECURE_NO_WARNINGS

// 그래프를 초기화하며 여러 값들을 입력하는 함수 //
void graph_init(GraphType *g) {
	srand((unsigned)time(NULL));
	int dup;
	int vertex, edge;
	int src, dst;
	int cost;
	GraphNode *tempnode;
	g->n = MAX_VERTICES;

	// Graph를 Adjacency List로 표현하며, 각각의 행을 초기화해준다. //
	for (vertex = 0; vertex < MAX_VERTICES; vertex++) {
		g->adj_list[vertex] = NULL;
	}

	// 간선을 랜덤하게 생성한다.  //
	srand((unsigned)time(NULL));
	for (edge = 0; edge < MAX_EDGES; edge++) {

		src = rand() % MAX_VERTICES;
		dst = rand() % MAX_VERTICES;
		while (src == dst)
			dst = rand() % MAX_VERTICES;

		// 중복 확인 //
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

		// Edge 삽입 // 
		if (dup == 0) {
			cost = (rand() % 300) + 100; // 100 ~ 399 가격
			insert_edge(g, src, dst, cost);
		}
		else {
			// 간선이 중복되는 경우 다시 랜덤으로 생성하도록 edge를 1 감소시킨다. // 
			edge = edge - 1;
		}
	}

	// 각 City에 대해 호텔 정보도 만들어준다. 만들어 준다. //
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

// 간선을 추가해주는 함수 //
void insert_edge(GraphType *g, int u, int v, int cost) {
	char temp[10] = { 0 };
	GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
	GraphNode *vnode = (GraphNode *)malloc(sizeof(GraphNode));

	// Directed Graph 이므로 한쪽 방향에 edge정보 추가(u) // 
	node->vertex = v;
	node->cost = cost;
	strcpy(node->cityname, "site-");
	_itoa(v, temp, 10);
	strcat(node->cityname, temp);
	node->link = g->adj_list[u];
	g->adj_list[u] = node;

	// Undirected Graph 이므로 양쪽 방향에 edge정보 추가(v) // 
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

// Test를 위한 함수 //
void Graph_Display(GraphType *g) {
	int i;
	GraphNode *tmp;
	for (i = 0; i < MAX_VERTICES; i++) {
		printf("정점 %d의 인접리스트: ", i);
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