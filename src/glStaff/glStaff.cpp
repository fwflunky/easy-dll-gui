//
// Created by user on 27.01.2024.
//

#include "glStaff.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "imgui.h"


bool glStaff::initWindow(HMODULE hModule, const std::wstring& wName, int w, int h) {
    wc = {sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, hModule, nullptr, nullptr, nullptr, nullptr, wName.data(), nullptr};
    ::RegisterClassExW(&wc);
    windowHWND = ::CreateWindowW(wc.lpszClassName, wName.data(), WS_SYSMENU & ~WS_CAPTION, 100, 100, w, h, nullptr, nullptr, wc.hInstance, nullptr);

    if (!createDeviceWGL(windowHWND, &g_MainWindow)) {
        cleanupDeviceWGL(windowHWND, &g_MainWindow);
        ::DestroyWindow(windowHWND);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return false;
    }

    windowSize[0] = w;
    windowSize[1] = h;

    wglMakeCurrent(g_MainWindow.hDC, g_hRC);

    ::ShowWindow(windowHWND, SW_SHOWDEFAULT);
    ::UpdateWindow(windowHWND);
    return true;
}

void glStaff::destroyWindow() {
    cleanupDeviceWGL(windowHWND, &g_MainWindow);
    wglDeleteContext(g_hRC);
    ::DestroyWindow(windowHWND);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

bool glStaff::createDeviceWGL(HWND hWnd, WGL_WindowData *data) {
    HDC hDc = ::GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0)
        return false;
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
        return false;
    ::ReleaseDC(hWnd, hDc);

    data->hDC = ::GetDC(hWnd);
    g_hRC = wglCreateContext(data->hDC);
    return true;
}

void glStaff::cleanupDeviceWGL(HWND hWnd, WGL_WindowData *data) {
    wglMakeCurrent(nullptr, nullptr);
    ::ReleaseDC(hWnd, data->hDC);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT glStaff::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED) {
                windowSize[0] = LOWORD(lParam);
                windowSize[1] = HIWORD(lParam);
            }
            return 0;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        default:
            return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }
}


