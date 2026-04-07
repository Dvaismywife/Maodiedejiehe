#pragma once

#include<Windows.h>
#include <algorithm>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#define WinGao 480
#define WinKuan 640
#include"background.h"
void playMP3(const wchar_t* filePath, bool loop = false) {
	wchar_t cmd[256];
	// 先停止之前的播放
	mciSendString(L"stop all", NULL, 0, NULL);
	mciSendString(L"close all", NULL, 0, NULL);
	// 打开并播放
	swprintf(cmd, 256, L"open \"%s\" alias bgm", filePath);
	mciSendString(cmd, NULL, 0, NULL);
	if (loop) {
		mciSendString(L"play bgm repeat", NULL, 0, NULL); // 循环播放
	}
	else {
		mciSendString(L"play bgm", NULL, 0, NULL); // 单次播放
	}
}

// 停止所有音效
void stopAllSound() {
	mciSendString(L"stop all", NULL, 0, NULL);
	mciSendString(L"close all", NULL, 0, NULL);
}


void startgame()
{
	initgraph(WinKuan, WinGao);
	loadimage(&maodiekaiqi, L"./rec/maodiekaiqi.jpg", WinKuan, WinGao);
	loadimage(&dianjimaodie, L"./rec/dianjimaodie.png", WinKuan, WinGao);
	putimage(0, 0, &dianjimaodie);
	setbkmode(TRANSPARENT);    // 文字背景透明（解决黑块）
	settextcolor(WHITE);       // 白色文字
	outtextxy(WinKuan/2, WinGao/2, L"点击任意键开始游戏！");
	while (true) {
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				break;
			}


		}
		
	}
	putimage(0, 0, &maodiekaiqi);
	playMP3(L"./rec/maodiehaqi.mp3", true);
	playMP3(L"./rec/maodiehaqi.mp3", false);
	Sleep(1000);
}
void endgame() {
	stopAllSound();
	closegraph();
}