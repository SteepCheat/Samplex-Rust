#pragma once
#include "../common.hpp"
#include "../Render/Render.hpp"
#define VOID void	//Cry about it

namespace Hooks		{
	inline VOID hkBasePlayerClientInput(uintptr_t player, uintptr_t input);
	R::UnityRending* menu = new R::UnityRending;
	uintptr_t PlayerWalk = NULL;
	typedef void* (__stdcall* fnDDrawGet)();
	fnDDrawGet oDDrawGet = *reinterpret_cast<fnDDrawGet*>(il2cpp::method(_("DDraw"), _("Get"), _("UnityEngine"), 0));
	
	inline VOID hkDDrawOnGui(uintptr_t DDrawInsance)	{
		
		menu->Text(Vector4{ float(menu->ScreenSizeX - 250), 20 - 4 + 1, 300, 50 }, _(L"Samplex Rust - Internal"), Unity::Color(255, 255, 255, 255), 14);
		menu->RunESP();
		if (R::bMenuOpen)
		{

			Unity::Color colSelected = {0, 0, 200, 1}, colEnabled = { 255, 0, 0, 1 };
			menu->Text(Vector4{ 8, 5, 300, 50 },  _(L"BOX ESP"), Config::bBoxESP ? colEnabled : colSelected, 16);
			menu->Text(Vector4{ 8, 20, 300, 50 }, _(L"HEALTH ESP"), Config::bHealthESP ? colEnabled : colSelected, 16);
			menu->Text(Vector4{ 8, 35, 300, 50 }, _(L"NAME ESP"), Config::bNameESP ? colEnabled : colSelected, 16);
			menu->Text(Vector4{ 8, 50, 300, 50 }, _(L"CHAMS ESP"), Config::bChamsESP ? colEnabled : colSelected, 16);
			menu->Text(Vector4{ 8, 65, 300, 50 }, _(L"WEAPON ESP"), Config::bWeaponESP ? colEnabled : colSelected, 16);
			menu->Text(Vector4{ 8, 80, 300, 50 }, _(L"SLEEPER ESP"), Config::bSleeperESP ? colEnabled : colSelected, 16);
			menu->Text(Vector4{ 8, 95, 300, 50 }, _(L"FAKE ADMIN"), Config::bFakeAdmin ? colEnabled : colSelected, 16);
			menu->Text(Vector4{ 8, 110, 300, 50 }, _(L"RECOIL SLIDER"), colEnabled, 16);
			char draw_buffer[sizeof(Config::fRecoilPercent) * 2];
			sprintf_s(draw_buffer, _("%d"), (int)Config::fRecoilPercent);
			std::string distance_string = _("<----") + std::string(draw_buffer) + _("% ---->");
			menu->Text(Vector4{ 8, 125, 300, 50 }, Unity::string::newString(distance_string.c_str()), colEnabled, 16);

			switch (menu->TabIndex)
			{
			case 1:
				menu->FilledRectangle(Vector4{ 2, 8, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			case 2:
				menu->FilledRectangle(Vector4{ 2, 23, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			case 3:
				menu->FilledRectangle(Vector4{ 2, 38, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			case 4:
				menu->FilledRectangle(Vector4{ 2, 53, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			case 5:
				menu->FilledRectangle(Vector4{ 2, 68, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			case 6:
				menu->FilledRectangle(Vector4{ 2, 83, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			case 7:
				menu->FilledRectangle(Vector4{ 2, 95, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			case 8:
				menu->FilledRectangle(Vector4{ 2, 110, 3, 18 }, Unity::Color(255, 0, 0, 255));
				break;
			}
			
		}
		
	}

	inline VOID HandleMenu() {//too lazy to make this dynamic, so suffer with me
		if (Unity::getKeyDown(Unity::KeyCode::Insert))
			R::bMenuOpen = !R::bMenuOpen;

		if (R::bMenuOpen)
		{
			if (menu->TabIndex < 1)
				menu->TabIndex = 1;

			if (menu->TabIndex > 8)
				menu->TabIndex = 8;

			if (Unity::getKeyDown(Unity::KeyCode::DownArrow))
				menu->TabIndex += 1;

			if (Unity::getKeyDown(Unity::KeyCode::UpArrow))
				menu->TabIndex -= 1;

			switch (menu->TabIndex)
			{
			case 1:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow))
					Config::bBoxESP = TRUE;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow))
					Config::bBoxESP = FALSE;
				break;
			case 2:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow))
					Config::bHealthESP = TRUE;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow))
					Config::bHealthESP = FALSE;
				break;
			case 3:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow))
					Config::bNameESP = TRUE;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow))
					Config::bNameESP = FALSE;
				break;
			case 4:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow))
					Config::bChamsESP = TRUE;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow))
					Config::bChamsESP = FALSE;
				break;
			case 5:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow))
					Config::bWeaponESP = TRUE;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow))
					Config::bWeaponESP = FALSE;
				break;
			case 6:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow))
					Config::bSleeperESP = TRUE;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow))
					Config::bSleeperESP = FALSE;
				break;
			case 7:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow))
					Config::bFakeAdmin = TRUE;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow))
					Config::bFakeAdmin = FALSE;
				break;
			case 8:
				if (Unity::getKeyDown(Unity::KeyCode::RightArrow) && Config::fRecoilPercent < 100)
					Config::fRecoilPercent = Config::fRecoilPercent + 10;
				if (Unity::getKeyDown(Unity::KeyCode::LeftArrow) && Config::fRecoilPercent > 10)
					Config::fRecoilPercent = Config::fRecoilPercent - 10;
				break;
			}
		}
	}

	static auto oPlayerWalkMovementClientInput = reinterpret_cast<void (*)(uintptr_t, uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("PlayerWalkMovement"), _("ClientInput"), _(""), -1)));
	inline VOID hkPlayerWalkMovement(uintptr_t playerwalkmovement, uintptr_t input, uintptr_t modelstate) {
		SpoofReturn(oPlayerWalkMovementClientInput, playerwalkmovement, input, modelstate);

		if ((uintptr_t)localPlayer > 0xfff) {
			if (Config::bFakeAdmin)
			{
				localPlayer->GetModelState()->RemoveFlag(Unity::ModelStateFLAG::Flying);
				*reinterpret_cast<bool*>((uintptr_t)localPlayer + Offsets::flying) = false;
			}
		}
	}
	
	static auto oBasePlayerClientInput = reinterpret_cast<void (*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), _(""), -1)));
	inline VOID hkBasePlayerClientInput(uintptr_t player, uintptr_t input)	{
  		if(!PlayerWalk)
  			PlayerWalk = il2cpp::hookVFunc(_("PlayerWalkMovement"), _("ClientInput"), &hkPlayerWalkMovement, -1);
		
		HandleMenu();
		oDDrawGet();

		Misc::DoMisc(localPlayer);
		SpoofReturn(oBasePlayerClientInput, player, input);//to those with keen eyes, this version of return spoofer is incomplete, for obvious reasons.
	}

	inline VOID init()	{

		M::init();
		auto BPCI = il2cpp::hookVFunc(_("BasePlayer"), _("ClientInput"), &hkBasePlayerClientInput, -1, _(""));
		auto DDOG = il2cpp::hook(&hkDDrawOnGui, _("OnGUI"), _("DDraw"), _("UnityEngine"), -1);
		menu->customShader = Unity::loadAssetFromFileInternal(Unity::string::newString(_("C:\\Shader.assets")), 0, 0);
		menu->ScreenSizeX = Unity::getScreenX();
		menu->ScreenSizeY = Unity::getScreenY();

		if (DEBUG)
		{
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			printf("DDraw OnGui Hooked            -> %p\n", DDOG);
			printf("BasePlayer ClientInput Hooked -> %p\n", BPCI);
			printf("loadAssetFromFileInternal ->     %p\n", Unity::loadAssetFromFileInternal);
			printf("customShader Asset            -> %p\n", menu->customShader);//	credit to @krispyyfr for the shader
			LuaEnv::setupEnvironment();//Yes I was going to do lua stuff
		}
	}
}