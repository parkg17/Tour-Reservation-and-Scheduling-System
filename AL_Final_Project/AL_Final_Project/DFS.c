#include "Headers.h"

// Stack_Array�� ���� �־��ִ� �Լ� //
void Push(int data) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (Stack_Array[i] == -1) {
			Stack_Array[i] = data;
			return;
		}
	}
	return;
}

// Stack_Array�� ���� ���ִ� �Լ� //
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

// �ش� Path�� ������ �ִ� ���� �ȿ� �� �� �ִ��� Ȯ���ϴ� �Լ� //
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

// ������ ����� ��ȯ���ش� �Լ� //
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
	// �̹� ����� ���Դٸ� Ž���� �����Ѵ�. //
	if (DFS_EXIT == 1) {
		return;
	}
	visit[v] = 1;
	Push(v);

	// �������� �����ϸ� Check_Path �Լ��� ���� ���꿡 �˸´��� Ȯ���Ѵ�. //
	if (v == user->dst) {
		if (GetStackSize() == user->period) {
			Check_Path(g, user);
		}
		Pop();
		return;
	}

	// �Ϸ翡 �� ���ø� �湮�ϹǷ� �湮�� �� �ִ� �ִ� // 
	// ������ ���� �Ѿ�� �� ���� Ž���� �����Ѵ�..  //
	if (GetStackSize() > user->period) {
		Pop();
		return;
	}

	// �湮���� ���� �̾��� ���� ���� �켱 Ž���� �����Ѵ�.//
	GraphNode * tempNode = g->adj_list[v];
	for (int i = 0; tempNode != NULL; i++) {
		if (visit[tempNode->vertex] == 0) {
			DFS(g, tempNode->vertex, user);
			// DFS �Լ����� Ż���ϸ� �ش� ����� visit�� �ٽ� 0���� �����Ѵ�.//
			visit[tempNode->vertex] = 0;
		}
		tempNode = tempNode->link;
	}

	Pop();
	return;
}