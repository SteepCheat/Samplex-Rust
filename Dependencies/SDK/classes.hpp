#pragma once

namespace Offsets {	//my eye's bleed
	uintptr_t playerModel = il2cpp::value(_("BasePlayer"), _("playerModel"));
	uintptr_t isLocalPlayer = il2cpp::value(_("PlayerModel"), _("isLocalPlayer"));
	uintptr_t health = il2cpp::value(_("BaseCombatEntity"), _("_health"));
	uintptr_t maxHealth = il2cpp::value(_("BaseCombatEntity"), _("_maxHealth"));
	uintptr_t model = il2cpp::value(_("BaseEntity"), _("model"));
	uintptr_t displayName = il2cpp::value(_("BasePlayer"), _("_displayName"));
	uintptr_t skinnedMultimesh = il2cpp::value(_("PlayerModel"), _("_multiMesh"));
	uintptr_t currentTeam = il2cpp::value(_("BasePlayer"), _("currentTeam"));
	uintptr_t playerFlags = il2cpp::value(_("BasePlayer"), _("playerFlags"));
	uintptr_t capsuleHeight = il2cpp::value(_("PlayerWalkMovement"), _("capsuleHeight"));
	uintptr_t capsuleWidth = il2cpp::value(_("PlayerWalkMovement"), _("capsuleWidth"));
	uintptr_t gravityMultiplier = il2cpp::value(_("PlayerWalkMovement"), _("gravityMultiplier"));
	uintptr_t flying = il2cpp::value(_("PlayerWalkMovement"), _("flying"));
	uintptr_t baseMovement = il2cpp::value(_("BasePlayer"), _("movement"));
	uintptr_t activeItem = il2cpp::value(_("BasePlayer"), _("clActiveItem"));
	uintptr_t inventory = il2cpp::value(_("BasePlayer"), _("inventory"));
	uintptr_t info = il2cpp::value(_("Item"), _("info"));
	uintptr_t itemDisplayName = il2cpp::value(_("ItemDefinition"), _("displayName"));
	uintptr_t modelState = il2cpp::value(_("BasePlayer"), _("modelState"));
	uintptr_t Recoil = il2cpp::value(_("BaseProjectile"), _("recoil"));
}

typedef struct Str
{
	char stub[0x10];
	int len;
	wchar_t str[1];
} *str;

class modelState {
public:
	VOID setWaterLevel(float level) {
		*reinterpret_cast<float*>((uintptr_t)this + 0x14) = level;
	}

	VOID RemoveFlag(Unity::ModelStateFLAG flag) {
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);
		flags &= ~(int)flag;

		*reinterpret_cast<int*>((uintptr_t)this + 0x24) = flags;
	}

	VOID SetFlag(Unity::ModelStateFLAG flag) {
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);

		*reinterpret_cast<int*>((uintptr_t)this + 0x24) = flags |= (int)flag;
	}

	BOOL HasFlag(Unity::ModelStateFLAG flag)
	{
		int& flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);

		return (flags & (int)flag) == (int)flag;
	}
};

class playerModel {
public:
	bool IsLocalPlayer() {
		return *reinterpret_cast<bool*>(this + Offsets::isLocalPlayer);
	}
	uintptr_t MultiMesh()
	{
		return *reinterpret_cast<uintptr_t*>(this + Offsets::skinnedMultimesh);
	}
};

class RecoilProperties {
public:
	bool SetRecoilProperties(Vector2 Pitch, Vector2 Yaw, float recoilPercent) {
		if (!this)
			return false;
		float recoilYawMin = *reinterpret_cast<float*>(this + 0x18);
		Vector2 pitch, yaw;
		if (recoilPercent > 0)
		{
			const auto mod = Unity::clamp(static_cast<float>(recoilPercent) / 100.f, 0.f, 1.f);

			M::write<float>((uintptr_t)this + 0x18, Yaw.x * mod);
			M::write<float>((uintptr_t)this + 0x1C, Yaw.y * mod);
			M::write<float>((uintptr_t)this + 0x20, Pitch.x * mod);
			M::write<float>((uintptr_t)this + 0x24, Pitch.y * mod);
		}
		
		return true;
	}

};

class BaseProjectile {

public:
	RecoilProperties* GetRecoilProperties() {
		if (!this)
			return {};
		return *reinterpret_cast<RecoilProperties**>(this + Offsets::Recoil);
	}

};

class Item {
public:
	wchar_t* GetItemName() {

		if (!this)
			return _(L"none");

			auto item_def = *reinterpret_cast<uintptr_t*>(this + Offsets::info);
			if (!item_def)
				return {};

			auto display_name = *reinterpret_cast<uintptr_t*>(item_def + Offsets::itemDisplayName);
			if (!display_name)
				return {};

			auto weapon_name = (str)(*reinterpret_cast<uintptr_t*>(display_name + 0x18));
			return weapon_name->str;
	}

	BaseProjectile* GetBaseProjectile() {
		if (!this)
			return {};
		return *reinterpret_cast<BaseProjectile**>(this + 0x98);
	}

	bool GetRecoilMM(Vector2& pitch_bounds, Vector2& yaw_bounds)
	{
		if (!this)
			return {};
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return false;

		auto item_def = *reinterpret_cast<uintptr_t*>(this + Offsets::info);
		if (!item_def)
			return {};

		unsigned int weapon_id = *reinterpret_cast<int*>(item_def + 0x18);
		switch (weapon_id)
		{
		case 0x5c22b98e/*Assault Rifle*/: {//Thanks @BDITT for the values
			pitch_bounds.x = -4.f;
			pitch_bounds.y = -30.f;
			yaw_bounds.x = -2.f;
			yaw_bounds.y = 8.f;
			return true;
		}
		case 0x5eab82c3/*Bolt Action Rifle*/: {
			pitch_bounds.x = -2.f;
			pitch_bounds.y = -3.f;
			yaw_bounds.x = -4.f;
			yaw_bounds.y = 4.f;
			return true;
		}
		case 0x34b73d71/*Compound Bow*/: {
			pitch_bounds.x = -3.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -3.f;
			yaw_bounds.y = 3.f;
			return true;
		}
		case 0x7523110a/*Crossbow*/: {
			pitch_bounds.x = -3.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -3.f;
			yaw_bounds.y = 3.f;
			return true;
		}
		case 0x6b1731e1/*Custom SMG*/: {
			pitch_bounds.x = -2.f;
			pitch_bounds.y = -15.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 10.f;
			return true;
		}
		case 0xd264397f/*Double Barrel Shotgun*/: {
			pitch_bounds.x = -10.f;
			pitch_bounds.y = -15.f;
			yaw_bounds.x = 8.f;
			yaw_bounds.y = 15.f;
			return true;
		}
		case 0x560b474f/*Hunting Bow*/: {
			pitch_bounds.x = -3.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -3.f;
			yaw_bounds.y = 3.f;
			return true;
		}
		case 0xd19b0ec1/*L96 Rifle*/: {
			pitch_bounds.x = -1.f;
			pitch_bounds.y = -1.f;
			yaw_bounds.x = -2.f;
			yaw_bounds.y = 2.f;
			return true;
		}
		case 0x93f69a57/*LR-300 Assault Rifle*/: {
			pitch_bounds.x = -2.f;
			pitch_bounds.y = -12.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 5.f;
			return true;
		}
		case 0x84a4bb78/*M249*/: {//done continue
			pitch_bounds.x = -5.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0x1ae5371/*M39 Rifle*/: {
			pitch_bounds.x = -5.f;
			pitch_bounds.y = -7.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0xcd2eebb5/*M92 Pistol*/: {
			pitch_bounds.x = -7.f;
			pitch_bounds.y = -8.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0x4e979c37/*MP5A4*/: {
			pitch_bounds.x = -2.f;
			pitch_bounds.y = -10.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 6.f;
			return true;
		}
		case 0xbd092660/*Multiple Grenade Launcher*/: {
			pitch_bounds.x = -15.f;
			pitch_bounds.y = -20.f;
			yaw_bounds.x = 5.f;
			yaw_bounds.y = 10.f;
			return true;
		}
		case 0x74763261/*Nailgun*/: {
			pitch_bounds.x = -3.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0x2f686650/*Pump Shotgun*/: {
			pitch_bounds.x = -10.f;
			pitch_bounds.y = -14.f;
			yaw_bounds.x = 4.f;
			yaw_bounds.y = 8.f;
			return true;
		}
		case 0x51e52593/*Python Revolver*/: {
			pitch_bounds.x = -15.f;
			pitch_bounds.y = -16.f;
			yaw_bounds.x = -2.f;
			yaw_bounds.y = 2.f;
			return true;
		}
		case 0x26bce126/*Revolver*/: {
			pitch_bounds.x = -3.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0x1a65e87c/*Rocket Launcher*/: {
			pitch_bounds.x = -15.f;
			pitch_bounds.y = -20.f;
			yaw_bounds.x = 5.f;
			yaw_bounds.y = 10.f;
			return true;
		}
		case 0x30cf142c/*Semi-Automatic Pistol*/: {
			pitch_bounds.x = -6.f;
			pitch_bounds.y = -8.f;
			yaw_bounds.x = -2.f;
			yaw_bounds.y = 2.f;
			return true;
		}
		case 0xca10e257/*Semi-Automatic Rifle*/: {
			pitch_bounds.x = -5.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0xfd87ab32/*Spas-12 Shotgun*/: {
			pitch_bounds.x = -10.f;
			pitch_bounds.y = -14.f;
			yaw_bounds.x = 4.f;
			yaw_bounds.y = 8.f;
			return true;
		}
		case 0x97315c8b/*Thompson*/: {
			pitch_bounds.x = -2.f;
			pitch_bounds.y = -15.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 10.f;
			return true;
		}
		case 0xae80eeeb/*Waterpipe Shotgun*/: {
			pitch_bounds.x = -10.f;
			pitch_bounds.y = -14.f;
			yaw_bounds.x = 4.f;
			yaw_bounds.y = 8.f;
			return true;
		}
		default: {
			return false;
		}
		}
	}
};

class BaseMovement {
public:
	float GetGravityScale() {
		auto Gravity = *reinterpret_cast<float*>((uintptr_t)this + Offsets::gravityMultiplier);
		return Gravity;
	}
	
	void SetGravityScale(float scale) {
		M::write<float>((uintptr_t)this + Offsets::gravityMultiplier, scale);
	}

	std::pair<float, float> GetCapsule() {
		auto capsuleHeight = *reinterpret_cast<float*>((uintptr_t)this + Offsets::capsuleHeight);
		auto capsuleWidth = *reinterpret_cast<float*>((uintptr_t)this + Offsets::capsuleWidth);
		return std::pair(capsuleHeight, capsuleWidth);
	}

	void SetCapsuleHeight(float height)	{
		*reinterpret_cast<float*>((uintptr_t)this + Offsets::capsuleHeight) = height;
	}
	void SetCapsuleWidth(float width)	{
		*reinterpret_cast<float*>((uintptr_t)this + Offsets::capsuleWidth) = width;
	}
};

class BasePlayer {
public:
	BasePlayer();
	playerModel* GetPlayerModel() {
		return *reinterpret_cast<playerModel**>(this + Offsets::playerModel);
	}

	modelState* GetModelState() {
		return *reinterpret_cast<modelState**>(this + Offsets::modelState);
	}

	Item* GetActiveItem() {
		if (!this)
			return {};

		const auto ActiveItemID = *reinterpret_cast<unsigned int*>((uintptr_t)this + Offsets::activeItem);
		if (!ActiveItemID)
			return {};

		auto Inventory = *reinterpret_cast<uint64_t*>((uintptr_t)this + Offsets::inventory);
		if (!Inventory)
			return {};
		auto containerBelt = *reinterpret_cast<uint64_t*>(Inventory + 0x28);
		if (!containerBelt)
			return {};
		auto itemList = *reinterpret_cast<uint64_t*>(containerBelt + 0x38);
		if (!itemList)
			return {};
		auto items = *reinterpret_cast<uint64_t*>(itemList + 0x10);
		if (!items)
			return {};

		for (int i = 0; i < 6; i++) {
			auto item = *reinterpret_cast<Item**>(items + 0x20 + (i * 0x8));
			if (!item)
				return {};

			auto itemID = *reinterpret_cast<unsigned int*>((uintptr_t)item + 0x28);
			if (!itemID)
				return {}; 

			if (ActiveItemID == itemID)
				return item;
			
		}
		return {};
	}
	VOID SetFlag(Unity::PlayerFlags flag) {
		int PlayerFlag = *reinterpret_cast<int*>((uintptr_t)this + Offsets::playerFlags);
		*reinterpret_cast<int*>((uintptr_t)this + Offsets::playerFlags) = PlayerFlag |= (int)flag;
	}

	bool IsVisible(Vector3 source, Vector3 destination) {
		auto layer = (int)Unity::Layers::ProjectileLineOfSightCheck | (int)Unity::Layers::Terrain;
		return Unity::LineOfSight(source, destination, Unity::Layers(layer), 0);
	}

	float GetHealth() {
		return *reinterpret_cast<float*>(this + Offsets::health);
	}
	
	BaseMovement* GetBaseMovement() {
		return *reinterpret_cast<BaseMovement**>((uintptr_t)this + Offsets::baseMovement);
	}

	float GetMaxHealth() {
		return *reinterpret_cast<float*>(this + Offsets::maxHealth);
	}

	wchar_t* GetName() {
		auto player_name = (str)(*reinterpret_cast<uintptr_t*>((uintptr_t)this + Offsets::displayName));
		return player_name->str;
	}

	bool IsTeamate(BasePlayer* localPlayer) {
		auto localTeam = *reinterpret_cast<uintptr_t*>((uintptr_t)localPlayer + Offsets::currentTeam);
		if (!localTeam)
			return false;

		auto playerTeam = *reinterpret_cast<uintptr_t*>((uintptr_t)this + Offsets::currentTeam);
		if (localTeam == playerTeam)
			return true;
		else
			return false;
	}

	Unity::Transform* GetTransform() {
		return Unity::getTransform(uintptr_t(this));
	}

	Unity::Transform* GetBonePositionID(int bone_id) {
		uintptr_t entity_model = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x128);
		uintptr_t bone_dict = *reinterpret_cast<uintptr_t*>(entity_model + 0x48);
		Unity::Transform* BoneValue = *reinterpret_cast<Unity::Transform**>(bone_dict + 0x20 + bone_id * 0x8);
		return BoneValue;
	}
};