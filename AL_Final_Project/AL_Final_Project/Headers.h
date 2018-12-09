#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <malloc.h>

#include "RBTree.h"
#include "Graph_List.h"
#include "UserInfo.h"
#include "UI.h"

int visit[MAX_VERTICES];
int Stack_Array[MAX_VERTICES];
int DFS_EXIT;

int Check_Path(GraphType *g, UserInfo * user);
void DFS(GraphType *g, int v, UserInfo * user);