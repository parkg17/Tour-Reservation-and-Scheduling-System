#include "Headers.h"

int main() {
	// 코드에 사용되는 각종 변수 //
	char buffer[1024];
	int index = 0;
	int nKey;
	int step = 0;
	int cursor = 1;
	int cursor_step0 = 1;
	int cursor_step1 = 1;
	int cursor_step2 = 1;
	int cursor_step3 = 1;

	// 콘솔창의 화면 크기를 설정하는 부분 //
	system("mode con:cols=65 lines=25");

	// 화면 초기화 //
	ScreenInit();
	Init();

	// 도시(Graph) 초기화 및 값 넣어주는 부분 //

	GraphType Cities;
	graph_init(&Cities);
	//Graph_Display(&Cities);

	// -------------------------------------- //



	// UserInfo 만들고 User 정보를 입력하는 부분 //

	UserInfo * root = (UserInfo *)malloc(sizeof(UserInfo));
	root->next = NULL;

	CreateUserInfo(&Cities, root, "Gyeol", 100000, 15, 65, 5, 3);
	CreateUserInfo(&Cities, root, "Seungyn", 20000, 25, 35, 7, 4);
	CreateUserInfo(&Cities, root, "Jongwon", 30000, 86, 2, 6, 2);
	CreateUserInfo(&Cities, root, "SKKU", 60000, 12, 97, 8, 3);
	CreateUserInfo(&Cities, root, "COLA", 80000, 76, 5, 7, 0);
	CreateUserInfo(&Cities, root, "BONO", 20000, 22, 15, 3, 4);
	CreateUserInfo(&Cities, root, "TOEIC", 999999, 76, 1, 10, 5);
	CreateUserInfo(&Cities, root, "Network", 76946, 65, 3, 6, 2);
	CreateUserInfo(&Cities, root, "Doctor", 80000, 37, 13, 9, 4);
	CreateUserInfo(&Cities, root, "KOREAN", 40000, 98, 25, 7, 3);
	CreateUserInfo(&Cities, root, "Teacher", 5000, 43, 55, 2, 1);

	// ----------------------------------------- //

	while (1) {
		if (step == 1) {
			if (_kbhit()) {
				nKey = _getch();
				switch (nKey) {
				case UP:
					if (cursor_step1 != 1) {
						cursor_step1--;
					}
					break;
				case DOWN:
					if (cursor_step1 != 5) {
						cursor_step1++;
					}
					break;
				case LEFT:
					cursor_step0 = 1;
					cursor_step1 = 1;
					step = 0;
					break;
				default:
					break;
				}
			}
			cursor = cursor_step1;
		}
		else if (step == 2) {
			if (_kbhit()) {
				nKey = _getch();
				switch (nKey) {
				case UP:
					if (cursor_step2 != 1) {
						cursor_step2--;
					}
					break;
				case DOWN:
					if (cursor_step2 != getUserNumber(root)) {
						cursor_step2++;
					}
					break;
				case LEFT:
					cursor_step0 = 1;
					cursor_step2 = 1;
					step = 0;
					break;
				case ENTER:
					/*
					index = 0;
					while (1) {
					if (_kbhit()) {
					nKey = _getch();
					if (nKey == ENTER) break;
					else {
					buffer[index] = nKey;
					}
					}
					}*/
				default:
					break;
				}
			}
			cursor = cursor_step2;
		}
		else if (step == 3) {
			if (_kbhit()) {
				nKey = _getch();
				switch (nKey) {
				case LEFT:
					cursor_step0 = 1;
					cursor_step3 = 1;
					step = 0;
				default:
					break;
				}
			}
			cursor_step3 = 1;
		}
		else {
			if (_kbhit()) {
				step = 0;
				nKey = _getch();
				if (nKey == 'q') {
					break;
				}

				switch (nKey) {
				case UP:
					if (cursor_step0 != 1) {
						cursor_step0--;
					}
					break;
				case DOWN:
					if (cursor_step0 != 3) {
						cursor_step0++;
					}
					break;
				case ENTER:
					if (cursor_step0 == 1) {
						step = 1;
					}
					else if (cursor_step0 == 2) {
						cursor_step0 = 1;
						step = 2;
					}
					else if (cursor_step0 == 3) {
						cursor_step0 = 1;
						step = 3;
					}
					break;
				default:
					break;
				}
			}
			cursor = cursor_step0;
		}

		Update();
		// 화면 출력 //
		Render(step, cursor, root);
	}

	// 화면 해제 //
	Release();
	ScreenRelease();
	return 0;
}