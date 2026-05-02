#pragma once
#include<Windows.h>
#include <algorithm>
#include<graphics.h>
#include<stdio.h>
#include <conio.h>
#include <MMSystem.h>
#include"skills.h"
#pragma comment(lib, "winmm.lib")
#define WinGao 800
#define WinKuan 1000
#include"background.h"
#include"mouse.h"
#include <shellapi.h>
// ========================= 修复视频播放函数 =========================
void playVideo(const wchar_t* videoPath)
{
	// 先关闭之前的所有媒体
	mciSendString(L"close video", NULL, 0, NULL);

	wchar_t cmd[512];
	// 打开视频，指定别名
	swprintf(cmd, 512, L"open \"%s\" alias video style popup", videoPath);
	mciSendString(cmd, NULL, 0, NULL);

	// 设置视频窗口居中、可显示
	mciSendString(L"set video window style popup", NULL, 0, NULL);
	mciSendString(L"put video window at 100 100 800 600", NULL, 0, NULL);

	// 开始播放
	mciSendString(L"play video", NULL, 0, NULL);
}

void stopVideo()
{
	mciSendString(L"stop video", NULL, 0, NULL);
	mciSendString(L"close video", NULL, 0, NULL);
}

// ========================== 音乐 ==========================
void playMP3(const wchar_t* filePath, bool loop = false) {
	wchar_t cmd[256];
	mciSendString(L"stop all", NULL, 0, NULL);
	mciSendString(L"close all", NULL, 0, NULL);
	swprintf(cmd, 256, L"open \"%s\" alias bgm", filePath);
	mciSendString(cmd, NULL, 0, NULL);
	if (loop) {
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
	}
	else {
		mciSendString(L"play bgm", NULL, 0, NULL);
	}
}

void stopAllSound() {
	mciSendString(L"stop all", NULL, 0, NULL);
	mciSendString(L"close all", NULL, 0, NULL);
}

// ========================== 透明贴图 ==========================
void putimageTransparent(int x, int y, IMAGE* img) {
	DWORD* pBuffer = GetImageBuffer();
	DWORD* pImg = GetImageBuffer(img);
	int nWidth = img->getwidth();
	int nHeight = img->getheight();

	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			DWORD color = pImg[j * nWidth + i];
			if ((color & 0xff000000) != 0) {
				if (x + i >= 0 && x + i < WinKuan && y + j >= 0 && y + j < WinGao) {
					pBuffer[(y + j) * WinKuan + (x + i)] = color;
				}
			}
		}
	}
}

// ========================== 开始游戏 ==========================
void startgame()
{
	initgraph(WinKuan, WinGao);
	loadimage(&maodiekaiqi, L"./rec/maodiekaiqi.jpg", WinKuan, WinGao);
	loadimage(&dianjimaodie, L"./rec/dianjimaodie.png", WinKuan, WinGao);
	loadimage(&dameng1, L"./rec/dameng1.png", WinKuan, WinGao);
	loadimage(&changtaimaodie, L"./rec/changtaimaodie/changtaimaodie.png", 250, 300);
	loadimage(&momaodie, L"./rec/tubiao/momaodie.png", 100, 100);
	loadimage(&maodiebiyan, L"./rec/changtaimaodie/maodiebiyan.png", 250, 300);
	loadimage(&ninenine, L"./rec/tubiao/ninenine.png", 100, 100);
	loadimage(&handImg, L"./rec/tubiao/handImg.png", 100, 40);
	loadimage(&tiquqi, L"./rec/tubiao/tiquqi.jpg", 100, 100);
	loadimage(&maobohe, L"./rec/tubiao/maobohe.png", 40, 40);
	loadimage(&chibohe, L"./rec/changtaimaodie/chibohe.png", 250, 300);
	loadimage(&tiqu, L"./rec/tubiao/tiqu.png", 200, 200);
	loadimage(&hohoho, L"./rec/tubiao/hohoho.png", 80, 60);
	loadimage(&beitiqu, L"./rec/changtaimaodie/beitiqu.png", 250, 300);

	putimage(0, 0, &dameng1);
	playMP3(L"./rec/music/qidong1.mp3", false);

	while (true) {
		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) break;
		}
	}

	Sleep(1000);
	putimage(0, 0, &dameng1);
	Sleep(2000);

	int x = 500, y = 0, i = 5;
	while (y <= 400) {
		cleardevice();
		putimage(0, 0, &dameng1);
		putimageTransparent(x, y, &changtaimaodie);
		i += 2; y += i;
		Sleep(10);
	}

	playMP3(L"./rec/music/gangguanluodi.mp3", false);
	Sleep(1000);
	playMP3(L"./rec/music/maodiehaqi.mp3", false);

	while (true) {
		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) break;
		}
	}
	playMP3(L"./rec/music/biedangwodelu.mp3", false);
}

// ========================== 正式游戏 ==========================
void formalgame() {
	FlushBatchDraw();
	Sleep(1000);

	while (true) {
		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) break;
		}
	}

	srand((unsigned)time(NULL));
	int comfortMax = 50 + rand() % 251;

	int maodieX = 500;
	int maodieY = 400;
	int maodieHeadX = maodieX + 125;
	int maodieHeadY = maodieY - 20;
	int range = 90;

	int skill2JudgeX = maodieHeadX;
	int skill2JudgeY = maodieHeadY + 100;

	int maodieMouthX = maodieX + 130;
	int maodieMouthY = maodieY + 120;
	int mouthRange = 70;

	bool isCatClosed = false;
	bool isEating = false;
	DWORD leaveTime = 0;
	DWORD eatTime = 0;
	const int DELAY_RESTORE = 800;
	const int EAT_TIME = 600;

	int curSkill = 0;
	bool tiquOpen = false;
	bool isTiquing = false;
	DWORD tiquRecoverTime = 0;

	static bool key1Pressed = false;
	static bool key2Pressed = false;
	static bool key3Pressed = false;

	bool showHoho = false;
	DWORD hohoTime = 0;
	int hoX = 0, hoY = 0;
	const int HOHO_INTERVAL = 500;

	int comfortValue = 0;
	bool startMove = false;
	bool playMoveSound = false;
	const int MOVE_SPEED = 2;
	int targetMoveDis = 300;
	int hasMoveDis = 0;
	bool canAddComfort = true;

	while (true)
	{
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &dameng1);

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(GetHWnd(), &pt);

		bool isOnHead = (pt.x - maodieHeadX) * (pt.x - maodieHeadX) + (pt.y - maodieHeadY) * (pt.y - maodieHeadY) < range * range;
		bool isOnSkill2Pos = (pt.x - skill2JudgeX) * (pt.x - skill2JudgeX) + (pt.y - skill2JudgeY) * (pt.y - skill2JudgeY) < range * range;

		

		// 【已删除：满值提示文字】

		if (isTiquing) putimageTransparent(maodieX, maodieY, &beitiqu);
		else if (curSkill == 2 && isOnSkill2Pos) putimageTransparent(maodieX, maodieY, &chibohe);
		else if (isEating) putimageTransparent(maodieX, maodieY, &chibohe);
		else if (isCatClosed) putimageTransparent(maodieX, maodieY, &maodiebiyan);
		else putimageTransparent(maodieX, maodieY, &changtaimaodie);

		if (showHoho) {
			putimageTransparent(hoX, hoY, &hohoho);
			if (GetTickCount() - hohoTime > HOHO_INTERVAL) {
				hoX = maodieX + rand() % 180 - 50;
				hoY = maodieY + rand() % 150 - 80;
				hohoTime = GetTickCount();
			}
		}

		putimageTransparent(700, 0, &momaodie);
		putimageTransparent(800, 0, &ninenine);
		putimageTransparent(900, 0, &tiquqi);

		if (GetAsyncKeyState('1') & 0x8000) {
			if (!key1Pressed) {
				key1Pressed = true; curSkill = 1; showHoho = false; isEating = false;
				while (ShowCursor(false) >= 0);
			}
		}
		else key1Pressed = false;

		if (GetAsyncKeyState('2') & 0x8000) {
			if (!key2Pressed) {
				key2Pressed = true; curSkill = 2; showHoho = false; isCatClosed = false;
				while (ShowCursor(false) >= 0);
			}
		}
		else key2Pressed = false;

		if (GetAsyncKeyState('3') & 0x8000) {
			if (!key3Pressed) {
				key3Pressed = true; curSkill = 3; showHoho = false; isEating = false; isCatClosed = false;
				while (ShowCursor(false) >= 0);
			}
		}
		else key3Pressed = false;

		if (comfortValue >= comfortMax && !startMove) {
			startMove = true;
			playMP3(L"./rec/music/dabiao.mp3", false);
			Sleep(1500);
			playMoveSound = true;
		}

		if (startMove && hasMoveDis < targetMoveDis) {
			int off = MOVE_SPEED;
			maodieX -= off;
			maodieHeadX -= off;
			skill2JudgeX -= off;
			maodieMouthX -= off;
			hasMoveDis += off;
		}

		// ====================== 按住回车 → 直接播放视频并进入下一阶段 ======================
		if (GetAsyncKeyState(VK_RETURN) && comfortValue >= comfortMax)
		{
			EndBatchDraw();
			stopAllSound();
			return;
		}

		if (tiquRecoverTime && GetTickCount() - tiquRecoverTime > 800) {
			isTiquing = false; tiquRecoverTime = 0;
		}
		if (isEating && GetTickCount() - eatTime > EAT_TIME) isEating = false;
		if (isCatClosed && !isOnHead && GetTickCount() - leaveTime > DELAY_RESTORE) {
			isCatClosed = false; leaveTime = 0;
		}

		if (curSkill == 1) putimageTransparent(pt.x - 50, pt.y - 20, &handImg);
		else if (curSkill == 2) putimageTransparent(pt.x - 20, pt.y - 10, &maobohe);
		else if (curSkill == 3) {
			putimageTransparent(pt.x - 100, pt.y - 100, &tiqu);
			if (isOnHead) { isTiquing = true; showHoho = true; tiquRecoverTime = GetTickCount(); }
			else showHoho = false;
		}
		else drawCustomCursor();

		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && canAddComfort) {
				if (curSkill == 1 && isOnHead) {
					comfortValue += 2; isCatClosed = true; isEating = false;
					playMP3(L"./rec/music/maodiehulu.mp3", false);
				}
				else if (curSkill == 2 && isOnSkill2Pos) {
					comfortValue += 3; isEating = true; isCatClosed = false; eatTime = GetTickCount();
				}
				else if (curSkill == 3 && isOnHead) {
					comfortValue += 4;
				}
				canAddComfort = false;
			}
		}

		if (!GetAsyncKeyState(VK_LBUTTON)) canAddComfort = true;

		EndBatchDraw();
		Sleep(10);
	}
}
//========================================
void next() {
	stopAllSound();
	playMP3(L"./rec/music/ysqd.mp3", true);

	// 两组动画
	const int FRAME_COUNT2 = 22;	// animation2 22张
	const int FRAME_COUNT1 = 28;	// animation 28张

	IMAGE anim2[FRAME_COUNT2];	// 第二组
	IMAGE anim[FRAME_COUNT1];	// 第一组

	// ======================
	// 加载 animation2（0~21）
	// ======================
	for (int i = 0; i < FRAME_COUNT2; i++) {
		TCHAR path[256];
		wsprintf(path, L"./rec/animation2/%d.png", i);
		loadimage(&anim2[i], path, WinKuan, WinGao);
	}

	// ======================
	// 加载 animation（0~27）
	// ======================
	for (int i = 0; i < FRAME_COUNT1; i++) {
		TCHAR path[256];
		wsprintf(path, L"./rec/animation/%d.png", i);
		loadimage(&anim[i], path, WinKuan, WinGao);
	}

	BeginBatchDraw();

	// ======================
	// 第一步：播放 animation2
	// ======================
	for (int i = 0; i < FRAME_COUNT2; i++) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			EndBatchDraw();
			stopAllSound();
			return;
		}
		cleardevice();
		putimage(0, 0, &anim2[i]);
		FlushBatchDraw();
		Sleep(60);
	}

	// ======================
	// 第二步：播放 animation
	// ======================
	for (int i = 0; i < FRAME_COUNT1; i++) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			EndBatchDraw();
			stopAllSound();
			return;
		}
		cleardevice();
		putimage(0, 0, &anim[i]);
		FlushBatchDraw();
		Sleep(60);
	}

	// ======================
	// 第三步：定格最后一张
	// ======================
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			EndBatchDraw();
			stopAllSound();
			return;
		}
		cleardevice();
		putimage(0, 0, &anim[FRAME_COUNT1 - 1]);
		FlushBatchDraw();
		Sleep(30);
	}
}

void endgame() {
	stopAllSound();
	closegraph();
}