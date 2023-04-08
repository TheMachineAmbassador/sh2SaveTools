#pragma once

#include "src/ImGuiFileBrowser.h"
#include <DecryptSave.h>


extern SaveFileBlocks fileBlock;

class BrowseFile : private imgui_addons::ImGuiFileBrowser
{
public:
	void showFileMenu();
};

