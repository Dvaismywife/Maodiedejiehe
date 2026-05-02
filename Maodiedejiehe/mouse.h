#pragma once
#include<graphics.h>
#include<stdio.h>
#include"skills.h"
#define WinGao 800
#define WinKuan 1000
IMAGE mymouse;
bool cursorVisible = true;

void putimageTransparent(int x, int y, IMAGE* img);
void initCustomCursor(const wchar_t* imgPath, int width = 32, int height = 32) {
    loadimage(&mymouse, imgPath, width, height);
    // 隐藏系统鼠标
    while (ShowCursor(false) >= 0);
}

    void drawCustomCursor() {
        if (!cursorVisible) return;

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(GetHWnd(), &pt);

        // ========== 新增逻辑 ==========
        if (skillPetOpen)
        {
            // 这里换成你的 手图片 路径，临时我先用你现有结构
            // 你可以提前加载一张 hand.png 当摸头手
            // putimageTransparent(pt.x, pt.y, &handImg);
            // 暂时先用你现有鼠标图也行，后面换手图我帮你改
            putimageTransparent(pt.x, pt.y, &mymouse);
        }
        else
        {
            // 正常普通鼠标
            putimageTransparent(pt.x, pt.y, &mymouse);
        }
    }

void restoreSystemCursor() {
    while (ShowCursor(true) < 0);
}