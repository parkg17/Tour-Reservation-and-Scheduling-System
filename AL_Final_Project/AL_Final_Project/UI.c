#include "Headers.h"

static int g_nScreenIndex;
static HANDLE g_hScreen[2];
char *FPSTextBuffer;

void readyUI() {
	ScreenPrint(5, 1, "***************************************************");
	ScreenPrint(5, 2, "*                                                 *");
	ScreenPrint(5, 3, "*                                                 *");
	ScreenPrint(5, 4, "*          Waiting for Bring the Data...          *");
	ScreenPrint(5, 5, "*                                                 *");
	ScreenPrint(5, 6, "*                                                 *");
	ScreenPrint(5, 7, "***************************************************");
}

void mainUI(int cursor) {
	ScreenPrint(5, 1, "***************************************************");
	ScreenPrint(5, 2, "*                                                 *");
	ScreenPrint(5, 3, "*                                                 *");
	ScreenPrint(5, 4, "*           Tour System And Reservation           *");
	ScreenPrint(5, 5, "*                                                 *");
	ScreenPrint(5, 6, "*                                                 *");
	ScreenPrint(5, 7, "***************************************************");
	ScreenPrint(5, 10, "1. Reservation");
	ScreenPrint(5, 11, "2. Checking the Reservation");
	ScreenPrint(5, 12, "3. How do I use the reservation system?");
	ScreenPrint(3, 9 + cursor, "¢º");
}

void ReservationUI(int cursor) {
	ScreenPrint(5, 1, "***************************************************");
	ScreenPrint(5, 2, "*                                                 *");
	ScreenPrint(5, 3, "*                                                 *");
	ScreenPrint(5, 4, "*             Reservation Information             *");
	ScreenPrint(5, 5, "*                                                 *");
	ScreenPrint(5, 6, "*                                                 *");
	ScreenPrint(5, 7, "***************************************************");
	ScreenPrint(7, 9, "Example:");
	ScreenPrint(10, 10, "Id:             skkulove12");
	ScreenPrint(10, 11, "budget($):      10000");
	ScreenPrint(10, 12, "Starting Point: 13");
	ScreenPrint(10, 13, "Destination:    43");
	ScreenPrint(10, 14, "Period(Days):   12");
	ScreenPrint(7, 16, "Please Enter your data for Reservation:");
	ScreenPrint(10, 17, "Id:             ");
	ScreenPrint(10, 18, "budget($):      ");
	ScreenPrint(10, 19, "Starting Point: ");
	ScreenPrint(10, 20, "Destination:    ");
	ScreenPrint(10, 21, "Period(Days):   ");
	ScreenPrint(8, 16 + cursor, "¢º");
}


void ReservationCheckUI(int cursor, UserInfo * userinfo) {
	char tempbuffer[100];
	int user_number = getUserNumber(userinfo);
	UserInfo * temp = userinfo;
	for (int index = 0; index < cursor; index++) {
		temp = temp->next;
	}
	ScreenPrint(5, 1, "***************************************************");
	ScreenPrint(5, 2, "*                                                 *");
	ScreenPrint(5, 3, "*                                                 *");
	ScreenPrint(5, 4, "*          Reservation  Check Information         *");
	ScreenPrint(5, 5, "*                                                 *");
	ScreenPrint(5, 6, "*                                                 *");
	ScreenPrint(5, 7, "***************************************************");

	ScreenPrint(5, 9, "   Id      Budget     src     dst    period    star");
	ScreenPrint(7, 10, temp->id); _itoa(temp->budget, tempbuffer, 10);
	ScreenPrint(16, 10, tempbuffer); _itoa(temp->src, tempbuffer, 10);
	ScreenPrint(27, 10, tempbuffer); _itoa(temp->dst, tempbuffer, 10);
	ScreenPrint(36, 10, tempbuffer); _itoa(temp->period, tempbuffer, 10);
	ScreenPrint(44, 10, tempbuffer); _itoa(temp->star, tempbuffer, 10);
	ScreenPrint(54, 10, tempbuffer);

	for (int i = 0; i < MAX_VERTICES; i++) {
		if (temp->Path_Array[i] == -1) {
			if (i == 0) {
				ScreenPrint(5, 13, "Not Found.");
				ScreenPrint(5, 14, "There is no Route that is suitable considering your");
				ScreenPrint(5, 15, "Budget and Itinerary.");
			}
			break;
		}
		else {
			_itoa(i + 1, tempbuffer, 10);
			ScreenPrint(6, 13 + i, ") ");
			ScreenPrint(5, 13 + i, tempbuffer);
			ScreenPrint(8, 13 + i, "City-");
			_itoa(temp->Path_Array[i], tempbuffer, 10);
			ScreenPrint(13, 13 + i, tempbuffer);
			if (temp->hotel[i] != 0) {
				ScreenPrint(16, 13 + i, "and Hotel Price is $");
				_itoa(temp->hotel[i], tempbuffer, 10);
				ScreenPrint(36, 13 + i, tempbuffer);
			}
		}
	}
	_itoa(cursor, tempbuffer, 10);
	ScreenPrint(26, 23, "¢¸"); ScreenPrint(29, 23, tempbuffer); ScreenPrint(30, 23, "/");
	_itoa(user_number, tempbuffer, 10);
	ScreenPrint(31, 23, tempbuffer); ScreenPrint(33, 23, "¢º");
}

void HelpUI(int cursor) {
	ScreenPrint(5, 1, "***************************************************");
	ScreenPrint(5, 2, "*                                                 *");
	ScreenPrint(5, 3, "*                                                 *");
	ScreenPrint(5, 4, "*                      Help                       *");
	ScreenPrint(5, 5, "*                                                 *");
	ScreenPrint(5, 6, "*                                                 *");
	ScreenPrint(5, 7, "***************************************************");
	ScreenPrint(7, 9, "Key");
	ScreenPrint(10, 10, "¢º : New Window which Cursor points to");
	ScreenPrint(10, 11, "¢¸ : Previous Window");
	ScreenPrint(10, 12, "¡å : Scroll Down");
	ScreenPrint(10, 13, "¡ã : Scroll Up");
	ScreenPrint(10, 14, "Enter : Selection");
	ScreenPrint(7, 16, "Help");
	ScreenPrint(9, 17, "This system helps you to schedule and book travel");
	ScreenPrint(9, 18, "information.  First, Enter your ID, Budget, Source,");
	ScreenPrint(9, 19, "Destination, Period, and hotel information you want.");
	ScreenPrint(9, 20, "If the path exists, it will print the information.");
	ScreenPrint(9, 21, "Else If not, it will print \"Not Found\".");
}

void Init() {
	ScreenClear();
	readyUI();
	ScreenFlipping();
}

void Update() {

}

void Render(int step, int cursor, UserInfo * userinfo) {
	ScreenClear();

	switch (step) {
	case 0:
		mainUI(cursor);
		break;
	case 1:
		ReservationUI(cursor);
		break;
	case 2:
		ReservationCheckUI(cursor, userinfo);
		break;
	case 3:
		HelpUI(cursor);
		break;
	default:
		break;
	}

	ScreenFlipping();
}

void Release() {
	free(FPSTextBuffer);
}

void ScreenInit() {
	CONSOLE_CURSOR_INFO cci;
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping() {
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear() {
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void ScreenRelease() {
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void ScreenPrint(int x, int y, char* string) {
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void SetColor(unsigned short color) {
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}