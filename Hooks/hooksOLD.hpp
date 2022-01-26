#pragma once
#pragma warning(disable:4996)
#include "../common.hpp"
#include "../Render/render.hpp"
#include <lazy_importer.hpp>
#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmpRdx[] = { 0xFF, 0x27 };//ReturnSpoof
#define Debug 1

namespace H {
	bool bMenu = FALSE;
	/*
	static auto oDDrawOnGui = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("OnGUI"), _("UnityEngine"), 0)));
	inline void hkDDrawOnGui(uintptr_t ddraw)
	{
		if (Unity::GetKeyDown(Unity::KeyCode::Insert))
			bMenu = !bMenu;

		auto mouse = Unity::GetMousePosition();
		auto screenX = Unity::GetScreenX;
		auto screenY = Unity::GetScreenY;

		if (!R::label || !R::skin)
		{
			R::skin = Unity::getSkin();
			R::label = M::read<uintptr_t>(R::skin + 0x38);

			Unity::setAlignment(R::label, 0);
			Unity::setFontSize(R::label, 12);
			Unity::setColor(Unity::Color(1, 1, 1, 1));
		}

		


		if (bMenu)
		{
			R::Text(Vector4{ 10 + 2.0f + 1, 20 - 4 + 1, 300, 50 }, _(L"samplex Rust - Internal"), Unity::Color(0, 0, 0, 120), false, 16);
		}

		SpoofReturn(oDDrawOnGui);
	}

	static auto oBasePlayerClientInput = reinterpret_cast<void (*)(basePlayer*, inputState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), _(""), 1)));
	inline void hkBasePlayerClientInput(basePlayer* player, inputState* input)
	{
		//inputHandler();
		if (Unity::GetKeyDown(Unity::KeyCode::Insert))
		{
			printf("unmappin\n");
		}
		if (player->isLocalPlayer())//Run Features
		{
			printf("%p\n", (uintptr_t)player);
		}
		SpoofReturn(oBasePlayerClientInput, player, input);
	}

	inline BOOLEAN initalize()
	{
		

		//init render
		//auto PresentScene = M::PatternScan((uintptr_t)M::getModuleBase(_("GameOverlayRenderer64.dll")), _("41 5E 48 FF 25 ? ? ? ? 48"), 2);//.data PresentScene, sortof lol
		//oPresent = *reinterpret_cast<Present*>(PresentScene);
		//*reinterpret_cast<Present*>(PresentScene) = &hkPresentScene;

		//init unity hooks
		oBasePlayerClientInput = reinterpret_cast<void (*)(basePlayer*, inputState*)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("BasePlayer"), _("ClientInput"), _(""), 1)));
		il2cpp::hookVFunc(_("BasePlayer"), _("ClientInput"), &hkBasePlayerClientInput, 1, _(""));
		
		oDDrawOnGui = reinterpret_cast<void (*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("DDraw"), _("OnGUI"), _("UnityEngine"), 0))); 
		il2cpp::hook(&hkDDrawOnGui, _("OnGUI"), _("DDraw"), _("UnityEngine"), 0);

		if (Debug)
		{
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			printf("BasePlayer ClientInput Original -> %p\n", oBasePlayerClientInput);
			printf("BasePlayer ClientInput Hooked -> %p\n", &hkBasePlayerClientInput);
			printf("DDraw OnGui Original -> %p\n", oDDrawOnGui);
			printf("DDraw OnGui Hooked -> %p\n", &hkDDrawOnGui);
		}
		
		return true;
	}*/
}