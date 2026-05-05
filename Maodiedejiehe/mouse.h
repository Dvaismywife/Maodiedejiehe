#pragma once
#include<graphics.h>
#include<stdio.h>
#define WinGao 800
#define WinKuan 1000
IMAGE mymouse;
bool cursorVisible = true;
bool skillPetOpen = false;
void putimageTransparent(int x, int y, IMAGE* img);
void initCustomCursor(const wchar_t* imgPath, int width = 32, int height = 32) {
    loadimage(&mymouse, imgPath, width, height);
    while (ShowCursor(false) >= 0);
}

    void drawCustomCursor() {
        if (!cursorVisible) return;

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(GetHWnd(), &pt);
        
        if (skillPetOpen)
        {
            
            putimageTransparent(pt.x, pt.y, &mymouse);
        }
        else
        {
         
            putimageTransparent(pt.x, pt.y, &mymouse);
        }
    }

void restoreSystemCursor() {
    while (ShowCursor(true) < 0);
}