#include "Headers.h"

void CreateUserInfo(GraphType *g, UserInfo * root, char *id, int budget, int src, int dst, int period, int star) {
	UserInfo * temp = root;
	UserInfo * user = (UserInfo *)malloc(sizeof(UserInfo));
	strcpy(user->id, id);
	user->budget = budget;
	user->src = src;
	user->dst = dst;
	user->period = period;
	user->star = star;
	user->next = NULL;

	for (int i = 0; i < MAX_VERTICES; i++) {
		user->hotel[i] = 0;
		user->Path_Array[i] = -1;
	}

	if (temp->next == NULL) {
		temp->next = user;
	}
	else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = user;
	}

	for (int k = 0; k < 100; k++) {
		visit[k] = 0;
		Stack_Array[k] = -1;
	}
	DFS_EXIT = 0;
	DFS(g, src, user);
	if (DFS_EXIT == 0) {
		user->found = 0;
	}
	else {
		user->found = 1;
	}
	return;
}

int getUserNumber(UserInfo * root) {
	int user_number;
	UserInfo * temp = root;
	for (user_number = 0; temp->next != NULL; user_number++) {
		temp = temp->next;
	}
	return user_number;
}

void freeUserInfo(UserInfo * root) {
	// 추후 넣자.
}