#pragma once

///////////////////						   ///////////////////
///////////////////						   ///////////////////
///////////////////    For Graph_List.c    ///////////////////
///////////////////						   ///////////////////
///////////////////						   ///////////////////

// 과제 조건에서 City(Vertex)는 100개, 경로(Edge)는 300개 //
#define MAX_VERTICES 100
#define MAX_EDGES 300
#define CITY_NAME_SIZE 50

typedef struct GraphNode {
	int vertex;
	int cost;
	char cityname[CITY_NAME_SIZE];
	Node * hotel_Info;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;  // 정점의 개수
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g);
void insert_edge(GraphType *g, int u, int v, int cost);
void Graph_Display(GraphType *g);

///////////////////                 ///////////////////
///////////////////                 ///////////////////
///////////////////    For DFS.c    ///////////////////
///////////////////                 ///////////////////
///////////////////                 ///////////////////

void Push(int data);
int Pop();
int GetStackSize();