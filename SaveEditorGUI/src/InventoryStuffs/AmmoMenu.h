#pragma once

#include "typedef.h"
#include <map>
#include <wtypes.h>
#include "imgui.h"

#include "../memedit/MemoryViewer.h"

enum Category
{
    Inventory = 0, InGame, EndGameResults
};

struct ItemData
{
    const char* name;
    Category category;
    int maxAmmo;
    DWORD* address;
};

class AmmoMenu : public MemoryViewer
{
private:

public:
    void AmmoEditWindow();
    void LoadAmmo();
};
