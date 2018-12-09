#pragma once
#define MAX_ID_LENGTH 100

typedef struct userinfo {
	char id[MAX_ID_LENGTH];				// ID
	int budget;							// ����
	int src;							// �����
	int dst;							// ������
	int period;							// �Ⱓ
	int star;							// ���ϴ� ȣ�� ����
	int Path_Array[MAX_VERTICES];
	int hotel[MAX_VERTICES];
	int found;
	struct userinfo * next;
} UserInfo;

void CreateUserInfo(GraphType *g, UserInfo * root, char *id, int budget, int src, int dst, int period, int star);
int getUserNumber(UserInfo * root);
void freeUserInfo(UserInfo * root);