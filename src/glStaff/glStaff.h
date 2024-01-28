//
// Created by user on 27.01.2024.
//

#ifndef KUMA_GLSTAFF_H
#define KUMA_GLSTAFF_H

#include <Windows.h>
#include <string>

class glStaff {
public:
    struct WGL_WindowData {
        HDC hDC;
    };

    static bool initWindow(HMODULE hModule, const std::wstring& wName, int w, int h);
    static void destroyWindow();

    static bool createDeviceWGL(HWND hWnd, WGL_WindowData *data);
    static void cleanupDeviceWGL(HWND hWnd, WGL_WindowData *data);

    static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static inline int windowSize[2];
    static inline HGLRC g_hRC;
    static inline WGL_WindowData g_MainWindow;
    static inline HWND windowHWND;
    static inline WNDCLASSEXW wc;
};


#endif //KUMA_GLSTAFF_H
