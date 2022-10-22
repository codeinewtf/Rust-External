#pragma once
#include "driver.hpp"
#include "base.hpp"
#include "function.hpp"
#include "glob.h"
#include "include.hpp"
#include "glob.h"
#include "mathamatics.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "HedlItems.h"
#include "Misc For A nigger.h"

void FunctionsMain()
{
	functions::Assembly_GOM = driver.read<uintptr_t>(functionbase::g_assembly + offsets::BaseEntity_TypeInfo); // 0x3600388

	functions::localPlayer_nigger = driver.read_chain<uintptr_t>(functionbase::g_assembly, { 0x3601F70, 0xB8, 0x0 }); //0x35FE858

	int flags = driver.read<uintptr_t>(functions::localPlayer_nigger + 0x690);

	functions::localPlayer_Movement = driver.read<uintptr_t>(functions::localPlayer_nigger + offsets::Movement);

	auto klass = driver.read<uintptr_t>(functionbase::g_assembly + 52987032);

	auto static_fields = driver.read<uintptr_t>(klass + 0xB8);

	uintptr_t current_item = GetHeldItem(functions::localPlayer_nigger); // our hand held item used for no recoil to check the gun [This is using our functionbase::Local_Player Defined as our self] 

	functions::LocalPlayer_ItemInHand = GetHeldItem(functions::localPlayer_nigger);

	functions::localPlayer_Projectile = driver.read<uintptr_t>(functions::LocalPlayer_ItemInHand + Held);

	//checks if offsets right or wrong
	std::cout << "::::::::  :::::::::: :::::::::: ::::::::  :::::::::: ::::::::::: ::::::::  \n";
	std::cout << ":+:    :+: :+:        :+:       :+:    :+: :+:            :+:    :+:    :+: \n";
	std::cout << "+:+    +:+ +:+        +:+       +:+        +:+            +:+    +:+        \n";
	std::cout << "+#+    +:+ :#::+::#   :#::+::#  +#++:++#++ +#++:++#       +#+    +#++:++#++ \n";
	std::cout << "+#+    +#+ +#+        +#+              +#+ +#+            +#+           +#+ \n";
	std::cout << "#+#    #+# #+#        #+#       #+#    #+# #+#            #+#    #+#    #+# \n";
	std::cout << " ########  ###        ###        ########  ##########     ###     ########  \n\n\n";

	std::cout << "Assembly_GOM [ 0x" << std::hex << functions::Assembly_GOM << " ] \n\n\n";

	std::cout << "assembly [ 0x" << std::hex << functionbase::g_assembly << " ] \n";

	std::cout << "offsets Movement [ 0x" << std::hex << offsets::Movement << " ] \n";

	std::cout << "functions localPlayer_Projectile [ 0x" << std::hex << functions::localPlayer_Projectile << " ] \n";

	std::cout << "RecoilYawMin [ 0x" << std::hex << RecoilYawMin << " ] \n";

	std::cout << "RecoilYawMax [ 0x" << std::hex << RecoilYawMax << " ] \n";

	std::cout << "RecoilPitchMin [ 0x" << std::hex << RecoilPitchMin << " ] \n";

	std::cout << "RecoilPitchMax [ 0x" << std::hex << RecoilPitchMax << " ] \n";

	std::cout << "RecoliPropitys [ 0x" << std::hex << offsets::RecoliPropitys << " ] \n";

	std::cout << "Weapon Id [ 0x" << std::hex << functions::LocalPlayer_ItemInHand << " ] \n";

	if (miscoptions::norecoil)
	{
		driver.write<float>(offsets::RecoliPropitys + RecoilYawMin, recoil::yrecoil);
		driver.write<float>(offsets::RecoliPropitys + RecoilYawMax, recoil::yrecoil);
		driver.write<float>(offsets::RecoliPropitys + RecoilPitchMin, recoil::xrecoil);
		driver.write<float>(offsets::RecoliPropitys + RecoilPitchMax, recoil::xrecoil);
	}


	std::thread(miscloop).detach();
}






