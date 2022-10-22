#pragma once
#include "include.hpp"
#include "driver.hpp"
#include "mainfun.h"
#include "function.hpp"
#include "base.hpp"
#include "glob.h"
#include <string>
#include <sstream>
#include <winstring.h>

unsigned short lfsr = 0xACE1u;

unsigned int bit = 0;

unsigned my_rand()
{
    if (!lfsr) {
        lfsr = 0xACE1u; bit = 0;
    }
    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    return lfsr = (lfsr >> 1) | (bit << 15);
}

std::string get_item_name(uintptr_t item)
{
    auto unk = driver.read<UINT64>(item + 0x20);

    unk = driver.read<UINT64>(unk + 0x20);

    return  driver.read_wstr(unk + 0x14);
}

bool is_weapon(uintptr_t helditem)
{
    auto ItemName = get_item_name(helditem);
    if (ItemName.find("rifle") != std::string::npos) return true;
    if (ItemName.find("pistol") != std::string::npos) return true;
    if (ItemName.find("bow") != std::string::npos) return true;
    if (ItemName.find("lmg") != std::string::npos) return true;
    if (ItemName.find("shotgun") != std::string::npos) return true;
    if (ItemName.find("smg") != std::string::npos) return true;
    else return false;
}

bool is_meele(uintptr_t helditem)
{
    auto ItemName = get_item_name(helditem);
    if (ItemName.find("rock") != std::string::npos) return true;
    if (ItemName.find("hatchet") != std::string::npos) return true;
    if (ItemName.find("stone.pickaxe") != std::string::npos) return true;
    if (ItemName.find("stonehatchet") != std::string::npos) return true;
    if (ItemName.find("pickaxe") != std::string::npos) return true;
    if (ItemName.find("hammer.salvage") != std::string::npos) return true;
    if (ItemName.find("icepick.salvag") != std::string::npos) return true;
    if (ItemName.find("axe.salvaged") != std::string::npos) return true;
    if (ItemName.find("pitchfork") != std::string::npos) return true;
    if (ItemName.find("mace") != std::string::npos) return true;
    if (ItemName.find("spear.stone") != std::string::npos) return true;
    if (ItemName.find("spear.wooden") != std::string::npos) return true;
    if (ItemName.find("machete") != std::string::npos) return true;
    if (ItemName.find("bone.club") != std::string::npos) return true;
    if (ItemName.find("paddle") != std::string::npos) return true;
    if (ItemName.find("salvaged.sword") != std::string::npos) return true;
    if (ItemName.find("salvaged.cleav") != std::string::npos) return true;
    if (ItemName.find("knife.combat") != std::string::npos) return true;
    if (ItemName.find("knife.butcher") != std::string::npos) return true;
    if (ItemName.find("jackhammer") != std::string::npos) return true;
    if (ItemName.find("chainsaw") != std::string::npos) return true;
    if (ItemName.find("knife.bone") != std::string::npos) return true;
    if (ItemName.find("torch") != std::string::npos) return true;
    if (ItemName.find("hammer") != std::string::npos) return true;
    if (ItemName.find("sickle") != std::string::npos) return true;
    else return false;
}

UINT64 GetHeldItem(UINT64 LocalPlayer)
{
    const auto base_player = LocalPlayer;

    const auto active_item_id = driver.read<UINT64>(base_player + offsets::clActiveItem);


    const auto player_inventory = driver.read<UINT64>(base_player + offsets::invintory);

    const auto inventory_belt = driver.read<UINT64>(player_inventory + offsets::containerBelt);

    const auto belt_contents_list = driver.read<UINT64>(inventory_belt + offsets::itemList);

    const auto belt_contents_sz = driver.read<uint32_t>(belt_contents_list + 0x14);

    const auto belt_contents = driver.read<UINT64>(belt_contents_list + 0x10);

    int active_weapon_id = driver.read<int>(LocalPlayer + 0x5D8); //private uint clActiveItem;

    uint64_t items = driver.read_chain<uint64_t>(LocalPlayer, { (uint64_t)0x6A0, (uint64_t)0x28, (uint64_t)0x38, 0x10 }); //public PlayerInventory inventory;

    std::cout << "Held weapon: found :" << items << std::endl;

    for (auto i = 0; i <= 6; i++)
    {
        if (belt_contents != 0)
        {
            const auto current_item = driver.read<UINT64>(belt_contents + (0x20 + (i * 8)));

            if (!current_item) continue;
            if (active_item_id == driver.read<uint32_t>(current_item + 0x28)) 

            return current_item;
        }
    }
}

