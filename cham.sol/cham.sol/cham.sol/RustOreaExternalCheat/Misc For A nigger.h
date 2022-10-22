#pragma once
#include "include.hpp"
#include "HedlItems.h"
#include "mainfun.h"
#include "glob.h"
#include "driver.hpp"
#include "function.hpp"
auto OcclusionCulling = driver.read<uintptr_t>(functionbase::g_assembly + 52992672);
auto CullingDebugOnOff = driver.read<uintptr_t>(OcclusionCulling + 0xB8);
auto OcclusionCullingEditted = driver.read_chain<uintptr_t>(OcclusionCulling, { 0xB8, 128, 0x18 });
auto ConvarCulling = driver.read<uintptr_t>(functionbase::g_assembly + 52992632); // 	"Signature": "ConVar_Culling_c*"
auto ConvarCulling2 = driver.read<uintptr_t>(ConvarCulling + 0xB8);
auto klass = driver.read<uintptr_t>(functionbase::g_assembly + 52982424); // convar_admin_c*
auto static_fields = driver.read<uintptr_t>(klass + 0xb8);

#define groundAngle 0xC4 // groundAngle
#define groundAngleNew 0xC8 // groundAngleNew
#define oGravityMultiplier 0x84 // public float gravityMultiplier;
#define oclothingWaterSpeedBonus 0x768 // public float clothingWaterSpeedBonus;
#define clothingMoveSpeedReduction 0x764 // public float clothingMoveSpeedReduction;
#define gravityTestRadius 0x80// public float gravityTestRadius
#define PlayerEyes 0x698 // public PlayerEyes eyes; 
#define modelState 0x600 //baseplayer
#define automatic  0x290 //Projectile //auto
#define FlagOnGround 4 // public const ModelState.Flag OnGround = 4;
#define RecoilYawMin 0x18  // public float recoilYawMin;
#define RecoilYawMax 0x1C  // public float recoilYawMax;
#define RecoilPitchMin 0x20 // public float recoilPitchMin;
#define RecoilPitchMax 0x24 // public float recoilPitchMax; 
#define capsuleHeight 0x68 // public float capsuleHeight
#define capsuleCenter 0x6C // public float capsuleCenter
#define Held 0xA0  // private EntityRef heldEntity

void miscloop()
{

	if (miscoptions::Admin)
	{
		driver.write<int>(functions::localPlayer_nigger + 0x690, 4); // done 
	}
	if (exploits::alwaysshoot)
	{
		auto mov_flag = driver.read<uintptr_t>(functions::localPlayer_Movement + modelState);
		driver.write<uintptr_t>(mov_flag, FlagOnGround);
		driver.write<float>(functions::localPlayer_Movement + groundAngle, 0.f);
		driver.write<float>(functions::localPlayer_Movement + groundAngleNew, 0.f);
	}

	if (exploits::timechanger)
	{

	}

	if (miscoptions::Automatic)
	{
		if (driver.read<bool>(functions::localPlayer_Projectile + automatic) != miscoptions::Automatic) {
			driver.write<bool>(functions::localPlayer_Projectile + automatic, miscoptions::Automatic);
		}
	}

	if (exploits::SpiderMan) // maybe 
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (driver.read<float>(functions::localPlayer_Movement + groundAngle) != 0.f)
			{
				driver.write<float>(functions::localPlayer_Movement + groundAngle, 0.f);
			}
			if (driver.read<float>(functions::localPlayer_Movement + groundAngleNew) != 2.f)
			{
				driver.write<float>(functions::localPlayer_Movement + groundAngleNew, 0.f);
			}
		}

	}
	if (exploits::climb) 
	{
		if (GetAsyncKeyState(KeyBinds::clumb))
		{

			driver.write<float>(functions::localPlayer_Movement + capsuleHeight, -100);
			driver.write<float>(functions::localPlayer_Movement + capsuleCenter, -100);
		}
		else
		{
			if (driver.read<float>(functions::localPlayer_Movement + capsuleHeight) != 1.79f) {
				driver.write<float>(functions::localPlayer_Movement + capsuleHeight, 1.79f);
				driver.write<float>(functions::localPlayer_Movement + capsuleCenter, 0.899f);
			}
		}
	}
	if (exploits::nightime)
	{

	}


	if (miscoptions::thirdperson)
	{
		driver.write<uintptr_t>(functions::localPlayer_nigger + 0x690, 1024);
	}


	if (exploits::FatBullet)
	{
		driver.write<float>(ConvarCulling2 + 0x0, 1000.f); // culling.entityupdaterate 1000 komutu
		driver.write<uintptr_t>(OcclusionCullingEditted + 0x20, 131072);
		driver.write<uintptr_t>(CullingDebugOnOff + 0x94, 1); // culling.debug 1 komutu
	}



		if (floatsliders::gravity_distancee)
		{
			if (GetAsyncKeyState(KeyBinds::gravity))
			{

				driver.write<float>(functions::localPlayer_Movement + groundAngle, exploits::flyhackspeed);//groundAngle
				driver.write<float>(functions::localPlayer_Movement + groundAngleNew, exploits::flyhackspeed);//groundAngleNew
				driver.write<float>(functions::localPlayer_Movement + oGravityMultiplier, exploits::flyhackspeed);//gravityMultiplier
			}
			else
			{
				if (driver.read<float>(functions::localPlayer_Movement + oGravityMultiplier) != 2.5f) {
					driver.write<float>(functions::localPlayer_Movement + oGravityMultiplier, 2.5f);//gravityMultiplier
				}
			}
		}


	if (exploits::infjump) // done 
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			driver.write<Vector3>(functions::localPlayer_Movement + 0xc8, Vector3(0.0f, 10000000, 0));
			driver.write<Vector3>(functions::localPlayer_Movement + 0xc4, Vector3(99999999, 99999999, 99999999));
		}
	}


	if (exploits::jesus) // done
	{
		if (driver.read<float>(functions::localPlayer_Movement + groundAngle) != 0.f) {
			driver.write<float>(functions::localPlayer_Movement + groundAngle, 0.f);//groundAngle
			driver.write<float>(functions::localPlayer_Movement + groundAngleNew, 0.f);//groundAngleNew
			driver.write<float>(functions::localPlayer_Movement + oGravityMultiplier, 0.f);//gravityMultiplier
		}
	}


	if (KeyBinds::longneck)
	{
		if (GetAsyncKeyState(KeyBinds::longneck))
		{
			auto eyes = driver.read<uintptr_t>(functions::localPlayer_nigger + PlayerEyes);
			driver.write<Vector3>(eyes + 0x38, Vector3(0, exploits::neckamount, 0));
		}
	}


	if (miscoptions::nosway)
	{
		driver.write<float>(functions::localPlayer_Projectile + 0x2D8, 0.f);// public float aimSway;
		driver.write<float>(functions::localPlayer_Projectile + 0x2DC, 0.f);// public float aimSwaySpeed;
	}


	if (exploits::FatBullet)
	{
		auto List = driver.read<uintptr_t>(functions::localPlayer_Projectile + 0x370); //private List<Projectile> createdProjectiles;
		int size = driver.read<uintptr_t>(List + 0x18);
		List = driver.read<uintptr_t>(List + 0x10);
		for (int i = 0; i < size; ++i)
		{
			auto Item = driver.read<uintptr_t>(List + 0x20 + (i * 0x8));
			driver.write<float>(Item + 0x2C, 0.7f);
		}
	}


	if (exploits::supereoka)
	{
		driver.write(functions::localPlayer_Projectile + 0x1E4, 100.0f);
		driver.write<float>(functions::localPlayer_Projectile + 0x378, 100.f);
		driver.write<bool>(functions::localPlayer_Projectile + 0x388, true);

	}


	if (miscoptions::fovChanger) // done
	{
		uint64_t fov = driver.read<UINT64>(functionbase::g_assembly + 0x3600F48); // "Signature": "ConVar_Graphics_c"
		uint64_t instance = driver.read<UINT64>(fov + 0xB8);
		driver.write<float>(instance + 0X18, floatsliders::FovSlider);
	}


	if (miscoptions::zoom)
	{
		if (GetAsyncKeyState(VK_XBUTTON2))
		{
			uint64_t fov = driver.read<UINT64>(functionbase::g_assembly + 0x3600F48); // "Signature": "ConVar_Graphics_c"
			uint64_t instance = driver.read<UINT64>(fov + 0xB8);
			driver.write<float>(instance + 0x18, 25.0f);
		}
	}

	if (!miscoptions::zoom)
	{

		uint64_t fov = driver.read<UINT64>(functionbase::g_assembly + 0x3600F48); // "Signature": "ConVar_Graphics_c"
		uint64_t instance = driver.read<UINT64>(fov + 0xB8);
		driver.write<float>(instance + 0X18, floatsliders::FovSlider);
	}

	if (exploits::flyhackspeed == true)
	{

	}

}