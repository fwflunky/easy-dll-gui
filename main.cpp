
#include <string>
#include <mutex>
#include "imgui.h"
#include "src/glStaff/glStaff.h"
#include "src/guiStaff/guiStaff.h"
#include "json.h"

// example data
struct data {
    std::string time, method, status, url;
};
std::vector<data> rows = {};
std::mutex mux;

bool init(HMODULE hModule) {
    if(glStaff::initWindow(hModule, L"Easy DLL GUI", 520, 400)) {
        guiStaff::initImGui();
        guiStaff::loop([](){
            ImGui::SetNextWindowPos({2,2});
            ImGui::SetNextWindowSize({500, 400 - 42});
            ImGui::Begin("##win1", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
            {
                if (ImGui::BeginTable("datas", 4, ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollX)) {
                    ImGui::TableSetupColumn("Time");
                    ImGui::TableSetupColumn("Method");
                    ImGui::TableSetupColumn("Response");
                    ImGui::TableSetupColumn("Link");
                    ImGui::TableHeadersRow();

                    std::scoped_lock<std::mutex> lock(mux);
                    {
                        for (auto &kData: rows) {
                            ImGui::TableNextRow();

                            ImGui::TableSetColumnIndex(0);
                            ImGui::Text("%s", kData.time.data());
                            ImGui::TableSetColumnIndex(1);
                            ImGui::Text("%s", kData.method.data());
                            ImGui::TableSetColumnIndex(2);
                            ImGui::Text("%s", kData.status.data());
                            ImGui::TableSetColumnIndex(3);
                            ImGui::Text("%s", kData.url.data());
                        }
                    }
                    ImGui::EndTable();
                }

            }
            ImGui::End();

            std::this_thread::sleep_for(std::chrono::microseconds(5000));
        });
    }

    return true;
}

extern "C" void __declspec(dllexport) addData(char* json, int jsonSize){
    auto jMap = nlohmann::json::parse(json, json + jsonSize);
    std::scoped_lock<std::mutex> lock(mux);
    {
        rows.emplace_back(jMap["time"], jMap["method"], jMap["status"], jMap["url"]);
    }
}

extern "C" bool __declspec(dllexport) clearData(){
    std::scoped_lock<std::mutex> lock(mux);
    {
        rows.clear();
    }
    return true;
}

extern "C" bool __declspec(dllexport) startGui(){
    if(guiStaff::isRunning)
        return false;
    std::thread([](){
        init(nullptr);
    }).detach();
    return true;
}

extern "C" bool __declspec(dllexport) stopGui(){
    if(!guiStaff::isRunning)
        return false;
    guiStaff::isDone = true;
    return true;
}


[[maybe_unused]] BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, DWORD lpReserved) {
    if(ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // startGui();
        return TRUE;
    }
    return FALSE;
}