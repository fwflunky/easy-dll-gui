//
// Created by user on 27.01.2024.
//

#include <Windows.h>
#include <gl/GL.h>
#include <iostream>
#include "guiStaff.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_win32.h"
#include "../glStaff/glStaff.h"

void guiStaff::initImGui() {
    isRunning = true;
    isDone = false;

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_InitForOpenGL(glStaff::windowHWND);
    ImGui_ImplOpenGL2_Init();

    ImFontConfig font_config;
    font_config.OversampleH = 1;
    font_config.OversampleV = 1;
    font_config.PixelSnapH = true;

    static const ImWchar ranges[] = { 0x0020, 0x00FF, 0x0400, 0x044F, 0};
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 14.0f, &font_config, ranges);
}

void guiStaff::loop(const std::function<void()>& render) {
    while (!isDone) {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                isDone = true;
        }
        if (isDone)
            break;

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        render();

        ImGui::Render();
        glViewport(0, 0, glStaff::windowSize[0], glStaff::windowSize[1]);
        glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        ::SwapBuffers(glStaff::g_MainWindow.hDC);
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    glStaff::destroyWindow();
    isRunning = false;
}
