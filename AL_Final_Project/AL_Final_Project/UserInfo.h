#pragma once
#define MAX_ID_LENGTH 100

typedef struct userinfo {
	char id[MAX_ID_LENGTH];				// ID
	int budget;							// 예산
	int src;							// 출발지
	int dst;							// 도착지
	int period;							// 기간
	int star;							// 원하는 호텔 성급
	int Path_Array[MAX_VERTICES];
	int hotel[MAX_VERTICES];
	int found;
	struct userinfo * next;
} UserInfo;

void CreateUserInfo(GraphType *g, UserInfo * root, char *id, int budget, int src, int dst, int period, int star);
int getUserNumber(UserInfo * root);
void freeUserInfo(UserInfo * root);