#include <string>
#include <memory>

#include "DecryptSave.h"

bool check_file(GameMemory gameMemory)
{
    bool isValid =
        gameMemory.saveType == 5 &&
        static_cast<uint8_t>(gameMemory.field13_0x2c) < 0x3b &&
        gameMemory.play_time >= 0.0 &&
        gameMemory.field25_0x44 >= 0.0 &&
        gameMemory.field26_0x48 >= 0.0 &&
        gameMemory.field27_0x4c >= 0.0 &&
        gameMemory.field28_0x50 >= 0.0 &&
        static_cast<uint8_t>(gameMemory.field16_0x32) < 0x65 &&
        gameMemory.field33_0x9c >= 0.0 &&
        static_cast<char>(gameMemory.field18_0x35) > -2 &&
        static_cast<char>(gameMemory.field18_0x35) < 0x03 &&
        gameMemory.field29_0x54 >= 0.0 &&
        gameMemory.field30_0x58 >= 0.0 &&
        gameMemory.field31_0x5c >= 0.0 &&
        gameMemory.maria_stuff_i_guess[0] < 5 &&
        gameMemory.maria_stuff_i_guess[1] < 4 &&
        gameMemory.item_ammos[0] < 1000 &&
        gameMemory.item_ammos[1] < 1000 &&
        gameMemory.item_ammos[2] < 1000 &&
        gameMemory.item_ammos[3] < 11 &&
        gameMemory.item_ammos[4] < 1000 &&
        gameMemory.item_ammos[5] < 7 &&
        gameMemory.item_ammos[6] < 1000 &&
        gameMemory.item_ammos[7] < 5 &&
        gameMemory.item_ammos[8] < 1000 &&
        gameMemory.item_ammos[11] < 9;

    return !isValid;
}

bool DecryptSH2Save(SaveFileBlocks& file_data, SaveFileThings& saveThings)
{
    if (check_file(file_data.gameMemory))
    {
        const auto decrypt = std::make_unique<Decrypt>(file_data, &saveThings);
        decrypt->run_process();
        return true;
    }

    return false;
}

bool EncryptSH2Save(SaveFileBlocks& file_data, SaveFileThings& saveThings)
{
    if (!check_file(file_data.gameMemory))
    {
        const auto encrypt = std::make_unique<Encrypt>(file_data, &saveThings);
        const auto decrypt = std::make_unique<Decrypt>(file_data, &saveThings);

        encrypt->run_process();
        decrypt->run_process();
        encrypt->run_process();

        return true;
    }

    return false;
}