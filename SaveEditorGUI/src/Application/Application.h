#pragma once

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "../backendfile/imgui_impl_glfw.h"
#include "../backendfile/imgui_impl_opengl3.h"
#include "../backendfile/imgui_impl_opengl3_loader.h"

#include "../InventoryStuffs/AmmoMenu.h"
#include "../ImGuiFileBrowser/BrowseFile.h"

namespace SH2SaveEdtitor {

    class Application : private AmmoMenu, private BrowseFile
    {

    public:
        static Application& getInstance()
        {
            static Application instance;
            return instance;
        }

    void run();

    private:
        GLFWwindow* window{};
        void DockingEnable(bool* p_open);

        Application();
        ~Application();

        void update();
        void render();

        void handleEvents()
        {
            // Event handling code
            glfwPollEvents();
        }


        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
    };

}