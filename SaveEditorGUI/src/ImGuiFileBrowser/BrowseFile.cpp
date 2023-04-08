#include "BrowseFile.h"
#include <Windows.h>

void BrowseFile::showFileMenu()
{
    bool open = false, save = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            if (ImGui::MenuItem("Open", NULL))
                open = true;
            if (ImGui::MenuItem("Save", NULL))
                save = true;

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();

        if (open)
            ImGui::OpenPopup("Open File");
        if (save)
            ImGui::OpenPopup("Save File");

        if (showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".dat"))
        {
            file_operations::read_file(fileBlock, selected_path);
            DecryptSH2Save(fileBlock);

        }
        if (showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".dat"))
        {
            if (!check_file(fileBlock.gameMemory))
            {
                EncryptSH2Save(fileBlock);
                file_operations::write_file(fileBlock, selected_path);
                DecryptSH2Save(fileBlock);
            }
            else
            {
                MessageBoxA(0, "Please do not go higher than the given value", "Error", MB_ICONERROR);
            }
        }
    }
}

