#pragma once

#include "src/ImGuiFileBrowser.h"
#include <DecryptSave.h>

class BrowseFile : private imgui_addons::ImGuiFileBrowser
{
public:
	void showFileMenu();
};

