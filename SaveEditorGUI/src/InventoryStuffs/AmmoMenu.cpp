#include "AmmoMenu.h"

#include <DecryptSave.h>

extern SaveFileBlocks fileBlock;

#define item_ammo_offset offsetof(SaveFileBlocks, gameMemory.item_ammos)

const char* item_names[] = { "Health Drink","First-aid kit","Ampoule","Handgun clip","Handgun Bullet","Shotgun clip","Shotgun shell","Hunting Riffle clip","Riffle shell" };

// Temporary Thing
u32 maxAmmo(const char* currentItem)
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

std::map<const char*, u16*> item_ammo_map;
static const char* current_item = "Please choose something...";
u16 maxVal = 0;

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


void AmmoMenu::LoadAmmo()
{
        int counter = 0;

        for (auto n : item_names)
        {
            item_ammo_map[n] = &fileBlock.gameMemory.item_ammos[counter];
            counter++;
        }
}

void AmmoMenu::AmmoEditWindow()
{
    ImGui::Begin("Ammo Edit");

    ImGui::SetNextItemWidth(250.0f);
    if (ImGui::BeginCombo("##combo", current_item, ImGuiComboFlags_HeightLarge))
    {
        for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
        {
            bool is_selected = (current_item == item_names[n]);
            if (ImGui::Selectable(item_names[n], is_selected))
            {
                current_item = item_names[n];
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
                PreviewDataType = getDataTypeBySize(*item_ammo_map[current_item]);
                GotoAddrAndHighlight(item_ammo_offset + n * 2, item_ammo_offset + n * 2 + 2);
                maxVal = maxAmmo(current_item);
            }
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    auto find = item_ammo_map.find(current_item);
    if (find != item_ammo_map.end())
    {
        addMenu(Inventory, *item_ammo_map[current_item], current_item, maxVal);

    }
    ImGui::End();
}