#include "Headers.h"

// Stack_Array에 값을 넣어주는 함수 //
void Push(int data) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (Stack_Array[i] == -1) {
			Stack_Array[i] = data;
			return;
		}
	}
	return;
}

// Stack_Array에 값을 빼주는 함수 //
int Pop() {
	int result;
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (Stack_Array[i] == -1) {
			if (i == 0) {
				return -1;
			}
			else {
				result = Stack_Array[i - 1];
				Stack_Array[i - 1] = -1;
				return result;
			}
		}
	}
	return -1;
}

// 해당 Path가 가지고 있는 예산 안에 갈 수 있는지 확인하는 함수 //
int Check_Path(GraphType *g, UserInfo * user) {
	GraphNode * tempNode;
	int transport_cost;
	int hotel_cost;
	int budget = user->budget;
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_VERTICES; i++) {
		if ((Stack_Array[i] != -1) && (Stack_Array[i + 1] != -1)) {
			tempNode = g->adj_list[Stack_Array[i]];
			while (tempNode->vertex != Stack_Array[i + 1]) {
				tempNode = tempNode->link;
			}
			transport_cost = tempNode->cost;
			budget = budget - transport_cost;

			switch (user->star) {
			case 0:
				hotel_cost = (rand() % 100) * 10 + 50; // 50 ~ 1040
				break;
			case 1:
				hotel_cost = (rand() % 11) * 10 + 50; // 50 ~ 150
				break;
			case 2:
				hotel_cost = (rand() % 15) * 10 + 160; // 160 ~ 300
				break;
			case 3:
				hotel_cost = (rand() % 25) * 10 + 310; // 310 ~ 550
				break;
			case 4:
				hotel_cost = (rand() % 25) * 10 + 560; // 560 ~ 800
				break;
			default:
				hotel_cost = (rand() % 24) * 10 + 810; // 810 ~ 1040
				break;
			}
			user->hotel[i] = hotel_cost;
			budget = budget - hotel_cost;
		}
	}

	if (budget > 0) {
		for (int i = 0; i < GetStackSize(); i++) {
			user->Path_Array[i] = Stack_Array[i];
		}
		DFS_EXIT = 1;
		return 1;
	}
	else {
		return 0;
	}
}

// 스택의 사이즈를 반환해준느 함수 //
int GetStackSize() {
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (Stack_Array[i] == -1) {
			return i;
		}
	}
	return MAX_VERTICES;
}

// Depth First Search //
void DFS(GraphType *g, int v, UserInfo * user) {
	// 이미 결과가 나왔다면 탐색을 중지한다. //
	if (DFS_EXIT == 1) {
		return;
	}
	visit[v] = 1;
	Push(v);

	// 목적지에 도착하면 Check_Path 함수를 통해 예산에 알맞는지 확인한다. //
	if (v == user->dst) {
		if (GetStackSize() == user->period) {
			Check_Path(g, user);
		}
		Pop();
		return;
	}

	// 하루에 한 도시만 방문하므로 방문할 수 있는 최대 // 
	// 도시의 수를 넘어가면 더 깊은 탐색을 중지한다..  //
	if (GetStackSize() > user->period) {
		Pop();
		return;
	}

	// 방문하지 않은 이어진 노드면 깊이 우선 탐색을 실행한다.//
	GraphNode * tempNode = g->adj_list[v];
	for (int i = 0; tempNode != NULL; i++) {
		if (visit[tempNode->vertex] == 0) {
			DFS(g, tempNode->vertex, user);
			// DFS 함수에서 탈출하면 해당 노드의 visit는 다시 0으로 변경한다.//
			visit[tempNode->vertex] = 0;
		}
		tempNode = tempNode->link;
	}

	Pop();
	return;
}