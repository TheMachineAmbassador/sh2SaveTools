#include <Windows.h>
#include <map>

#include "imgui.h"
#include "imgui_internal.h"
#include "backendfile/imgui_impl_glfw.h"
#include "backendfile/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "WindowBuffers.hpp"

#define item_ammo_offset offsetof(SaveFileBlocks, gameMemory.item_ammos)

const char* items[] = { "Health Drink","First-aid kit","Ampoule","Handgun clip","Handgun Bullet","Shotgun clip","Shotgun shell","Hunting Riffle clip","Riffle shell" };

enum Category
{
    Inventory = 0, InGame,EndGameResults
};

// Temporary Thing
u32 ammoThings(const char* currentItem)
{
    int maxAmmo;

    if (currentItem == "Handgun clip")
        maxAmmo = 10;
    else if (currentItem == "Shotgun clip")
        maxAmmo = 6;
    else if (currentItem == "Hunting Riffle clip")
        maxAmmo = 4;
    else
        maxAmmo = 999;
    return maxAmmo;
}

INT WINAPI WinMain
    (
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        PSTR lpCmdLine,
        INT nCmdShow
    )
{
    // Setup window
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Silent Hill 2 Save Editor", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::map<const char*, u16*> sd;

    int counter = 0;
    for (auto n : items)
    {
        sd[n] = &fileBlock.gameMemory.item_ammos[counter];
        counter++;
    }

    static const char* current_item = "Please choose something...";
    u16 maxVal = 0;
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        showFileMenu();

        DockingEnable(new bool(true));
        
        {
            ImGui::Begin("Ammo Edit");

            ImGui::SetNextItemWidth(250.0f);
            if (ImGui::BeginCombo("##combo", current_item,ImGuiComboFlags_HeightLarge))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (current_item == items[n]);
                    if (ImGui::Selectable(items[n], is_selected))
                    {
                        current_item = items[n];
                        if (is_selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                        mem_edit.PreviewDataType = getDataTypeBySize(*sd[current_item]);
                        mem_edit.GotoAddrAndHighlight(item_ammo_offset + n*2, item_ammo_offset + n*2+2);
                        maxVal = ammoThings(current_item);
                    }
                }
                ImGui::EndCombo();
            }
            ImGui::SameLine();
            auto find = sd.find(current_item);
            if (find != sd.end())
            {
                addMenu(Inventory, *sd[current_item], current_item, maxVal);

            }
            ImGui::End();
        }

        DrawMemoryEditor();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}