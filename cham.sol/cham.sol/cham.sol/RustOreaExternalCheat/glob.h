#pragma once


namespace colors {
	float boxcolor1 = 0.00f;
	float boxcolor2 = 0.00f;
	float boxcolor3 = 0.00f;
}

namespace functionbase {
	uintptr_t g_assembly;
	uintptr_t g_unityplayer;
	uintptr_t Local_Player;

}

namespace menu {
	bool ESP = false;
	bool Aimbot = false;
	bool Settings = false;
	bool misc = false;
	bool Config = false;
	bool info = false;
	bool esps = false;
}
namespace miscoptions {
	bool norecoil = true;
	bool nosway = false;
	bool Admin = false;
	bool Automatic = true;
	bool fovChanger = false;
	bool debug = false;
	bool viewplayers = false;
	bool thirdperson = false;
	bool zoom = false;
}
namespace espoptions {
	bool NoramlBox = false;
	bool CornorBox = false;
	bool LinesFromCrossHair = false;
	bool LinesFromBottem = false;
	bool PlayerHealth = false;
	bool PlayerName = false;
	bool PlayerWeapon = false;
	bool PlayerHeadDot = false;
	bool PlayerChams = false;
	bool SleeperEsp = false;
}

namespace exploits {
	bool SpiderMan = false;
	bool supereoka = true;
	bool FatBullet = false;
	bool superknife = false;
	bool instabow = false;
	bool flyhacks = false;
	bool flybypass = false;
	bool speedhacks = false;
	bool infjump = false;
	bool jesus = false;
	bool climb = true;
	bool instasuicide = false;
	bool timechanger = false;
	bool nightime = false;
	float flyhackspeed = 0.f;
	bool spingbot = false;
	bool gravity = false;
	bool longneck = false;
	bool alwaysshoot = true;
	float neckamount = 3.f;
}
namespace KeyBinds 
{
	static int aimbot;
	static int silentaim;
	static int longneck;
	static int fly;
	static int gravity;
	static int clumb;

}
namespace aimbot {
	bool pSilent = false;
	bool aimbot = false;
	bool prediction = false;
	bool ciclefov = true;
	bool HeadOnly = false;
	bool LockOn = false;
	bool Smoothing = false;
	bool AntiTeam = false;
	bool AntiDown = false;
}

namespace oreesp {
	bool Stone = false;
	bool Metal = false;
	bool sulf = false;
	bool cloth = false;
	bool pickable = false;
	bool wood = false;
}

namespace floatsliders
{
	float lootdistance = 100.0f;
	float espdistance = 100.0f;
	float FovSlider = 90.0f;
	float aimbotdistance = 100.0f;
	float aimbotsmoothing = 1.0f;
	float Time = 10.0f;
	float gravity_distancee = 5.0f;
}
namespace lootesp {
	bool creates = false;
	bool barrel = false;
	bool elitecrate = false;
	bool greencrate = false;
	bool droppeditems = false;
	bool Mini = false;
	bool boat = false;
}

uintptr_t objectList;
uintptr_t objectListSize;

namespace recoil
{
	float xrecoil = 0.0f;
	float yrecoil = 0.0f;
}
namespace offsets {
	//client offsets
	auto BaseEntity_TypeInfo = 0x35FF4B8; // [Script] LocalPlayer_TypeInfo
	auto GameObjectMangier = 0x3600388;
	//BasePlayer class offsets
	auto playerModel = 0x4D0; // PlayerModel
	auto Movement = 0x4F8; // BaseMovement
	auto collision = 0x500; // BaseCollision
	auto _lookingAt = 0x508; //GameObject
	auto _lookingAtEntity = 0x510; //baseEntity
	auto wasSleeping = 0x531; //bool
	auto currentTeam = 0x5A0; // ulong baseEntity
	auto clientTeam = 0x5A8; // PlayerTeam
	auto clActiveItem = 0x5D8; //item id correct
	auto modelState = 0x600; //module state
	auto mounted = 0x608; // EntityRef
	auto maxProjectileID = 0x640; //int weapon projectile 
	auto serverTickRate = 0x64C; // int
	auto clientTickRate = 0x650; // int
	auto serverTickInterval = 0x654; //float
	auto clientTickInterval = 0x658; // float
	auto drownEffect = 0x688; // Game Object Reference
	auto playerFlags = 0x690; // BasePlayer.PlayerFlags
	auto invintory = 0x6A0;  //Player Invintory
	auto playerCollider = 0x6C0; // Capsule Collider
	auto Held = 0x98; // Player belt
	auto userID = 0x6D8; // ulong base player
	auto UserIDString = 0x6E0; //string user
	auto clothingBlocksAiming = 0x760; //bool
	auto clothingMoveSpeedReduction = 0x764; //float
	auto clothingWaterSpeedBonus = 0x768; // flaot 
	auto clothingAccuracyBonus = 0x76C; //float
	auto containerBelt = 0x28;
	auto itemList = 0x38;
	//BaseProjectile Class Offsets
	auto RecoliPropitys = 0x78;
}


namespace functions
{
	uintptr_t localPlayer_nigger;
	uintptr_t Assembly_GOM;
	uintptr_t localPlayer_Movement;
	uintptr_t localPlayer_Projectile;
	uintptr_t localPlayer_health;
	uintptr_t LocalPlayer_ItemInHand;

}

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};
