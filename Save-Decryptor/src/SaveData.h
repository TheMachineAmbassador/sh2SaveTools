#pragma once

#include "typedef.h"

struct SaveData {
    float read_player_health;
    float read_player_max_health;
    uint save_data_character_create;
    uint save_data_character_create_buffer;
    float field4_0x10;
    float save_data_run_meter_add_counter;
    uint field6_0x18;
    uint field7_0x1c;
    uint field8_0x20;
    short weapon_type;
    short current_weapon_clip;
    short current_weapon_ammo;
    u8 field12_0x2a;
    u8 field13_0x2b;
    uint field14_0x2c;
    uint field15_0x30;
    uint field16_0x34;
    short field17_0x38;
    short field18_0x3a;
    float field19_0x3c;
    float field20_0x40;
    float field21_0x44;
    uint field22_0x48;
    float field23_0x4c;
    float field24_0x50;
    uint field25_0x54;
    uint field26_0x58;
    uint field27_0x5c;
    uint field28_0x60;
    uint field29_0x64;
    uint field30_0x68;
    uint field31_0x6c;
    float field32_0x70;
    uint field33_0x74;
    uint field34_0x78;
    u8 field35_0x7c[12];
    uint field36_0x88;
    u8 field37_0x8c[12];
    uint field38_0x98;
    uint field39_0x9c;
    uint field40_0xa0;
    uint field41_0xa4;
    uint field42_0xa8;
    uint field43_0xac;
    uint field44_0xb0;
    uint field45_0xb4;
    float field46_0xb8;
    float field47_0xbc;
    float field48_0xc0;
    uint field49_0xc4;
    u8 interesting_stuffs_in_here[4840];
};

struct GameMemory {
    uint saveType;
    u16 field1_0x4[2];
    u16 field2_0x8;
    u8 field3_0xa;
    u8 field4_0xb;
    float SaveMariaX;
    float SaveMariaY;
    float SaveMariaZ;
    float SaveMariaHorizontal;
    float SaveJamesZPos;
    float SaveJamesYPos;
    float SaveJamesXPos;
    float SaveJamesRotation;
    short field13_0x2c;
    short field14_0x2e;
    short field15_0x30;
    short field16_0x32;
    u8 field17_0x34;
    u8 field18_0x35;
    short field19_0x36;
    short field20_0x38;
    short field21_0x3a;
    short field22_0x3c;
    short field23_0x3e;
    float play_time;
    float field25_0x44;
    float field26_0x48;
    float field27_0x4c;
    float field28_0x50;
    float field29_0x54;
    float field30_0x58;
    float field31_0x5c;
    u8 field32_0x60[60];
    float field33_0x9c;
    u8 maria_stuff_i_guess[32];
    uint game_flag[296];
    u16 items[7];
    u16 item_ammos[13];
    u16 dunno[10];
    SaveData saveData;
    uint field38_0x194c[24];
    uint field39_0x19ac[389];
};

struct SaveFileBlocks
{
	u32 file_header;
	u32 save_file_after_four_byte;
    GameMemory gameMemory;
    u32 UINT_ARRAY_009361d0[10];
	u32 UINT_009361f8;
	u32 UINT_009361fc;
	u32 last_byte_after_four_byte;
	u32 last_four_byte_of_save;
};

struct SaveFileThings
{
	u32 hash_first_part[6];
	u32 hash_second_part[4];
	u32 INT_0093bff0;
	u32* points_To_Save_File_After_8_Byte;
	u32 counter_for_loops;
	u32 INT_0093c000;
	u32 DAT_0093c004;
	u32 DAT_0093c008;
	u32 junk04;
	u32 DAT_0093c010;
	u32 DAT_0093c014;
	u32 uVar10;
	u32 hash_location;
};
