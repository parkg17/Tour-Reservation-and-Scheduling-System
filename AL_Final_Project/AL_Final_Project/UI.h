#pragma once
#define LINE_MAXIMUM_SIZE 1000
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

void readyUI();
void mainUI(int cursor);
void ReservationUI(int cursor);
void ReservationCheckUI(int cursor, UserInfo * userinfo);
void HelpUI(int cursor);
void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, char* string);
void SetColor(unsigned short color);
void Init();
void Update();
void Render(int step, int cursor, UserInfo * userinfo);
void Release();