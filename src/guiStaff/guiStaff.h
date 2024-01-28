//
// Created by user on 27.01.2024.
//

#ifndef KUMA_GUISTAFF_H
#define KUMA_GUISTAFF_H


#include <functional>
#include <atomic>

class guiStaff {
public:
    static void initImGui();

    static void loop(const std::function<void()>& render);

    static inline float bgColor[4] = {0, 0, 0, 1.00f};
    static inline std::atomic_bool isDone = false;
    static inline std::atomic_bool isRunning = false;
};


#endif //KUMA_GUISTAFF_H
