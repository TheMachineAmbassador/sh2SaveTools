#include <Windows.h>
#include "imgui.h"
#include "FileOperations/FileOperations.h"

#include "DecryptSave.h"
#include "ImGuiFileBrowser/ImGuiFileBrowser.h"
#include "memedit/memedit.h"


SaveFileBlocks fileBlock;
SaveFileThings saveThings;

MemoryEditor mem_edit;

imgui_addons::ImGuiFileBrowser file_dialog; // As a class member or globally

void showFileMenu()
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

        if (file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".dat"))
        {
            file_operations::read_file(fileBlock, file_dialog.selected_path);
            DecryptSH2Save(fileBlock, saveThings);

        }
        if (file_dialog.showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".dat"))
        {
            if (!check_file(fileBlock.gameMemory))
            {
                EncryptSH2Save(fileBlock, saveThings);
                file_operations::write_file(fileBlock, file_dialog.selected_path);
                DecryptSH2Save(fileBlock, saveThings);
            }
            else
            {
                MessageBoxA(0, "Please do not go higher than the given value", "Error", MB_ICONERROR);
            }
        }
    }
}

void DockingEnable(bool* p_open)
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;

    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}

void DrawMemoryEditor()
{
    mem_edit.Cols = 32;
    mem_edit.OptShowDataPreview = true;
    mem_edit.OptGreyOutZeroes = false;

    mem_edit.DrawWindow("MemoryEditor", &fileBlock, sizeof(SaveFileBlocks));
}

template<typename T>
T getDataTypeBySize(T data)
{
    ImGuiDataType_ dataType = ImGuiDataType_U8;

    switch (sizeof(data))
    {
    case 2:
        dataType = ImGuiDataType_U16;
        break;
    case 4:
        dataType = ImGuiDataType_U32;
        break;
    case 8:
        dataType = ImGuiDataType_U64;
        break;
    }
    return dataType;
}

template<typename T>
void addMenu(s8 categoryID, T& data, std::string dataName, u16 max)
{
    u32 min = 0;
    ImGui::Text("Change %s:", dataName.c_str());
    ImGui::SameLine();
    std::string LabelID = "##" + dataName;
    ImGui::SetNextItemWidth(170.0f);
    ImGui::DragScalar(LabelID.c_str(), getDataTypeBySize(data), &data, 1.0F, &min, &max);
}
