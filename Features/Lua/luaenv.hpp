#pragma once
#include <sol/sol.hpp>
#define BOOL bool //syndrome

namespace LuaEnv
{
	BOOL setupEnvironment()
	{
		/*
		sol::state lua;
		lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::io);

		auto v2 = lua.new_usertype<Vector2>("Vector2", sol::constructors<Vector2(), Vector2(float, float)>());
		v2["x"] = &Vector2::x;
		v2["y"] = &Vector2::y;

		auto v3 = lua.new_usertype<Vector3>("Vector3", sol::constructors<Vector3(), Vector3(float, float, float)>());
		v3["x"] = &Vector3::x;
		v3["y"] = &Vector3::y;
		v3["z"] = &Vector3::h;
		v3["dot"] = &Vector3::Dot;
		v3["distance"] = &Vector3::Distance;
		v3["length"] = &Vector3::Length;

		v3["lambda"] = [](Vector3 vec3, float f1, float f2)
		{
			std::cout << "Lambda f1: " << f1 << std::endl;
			std::cout << "Lambda f2: " << f2 << std::endl;
		};

		auto unity_table = lua.create_table();
		unity_table.set_function("getscreen", []() {
				return Vector2(Unity::getScreenX(), Unity::getScreenY());
			}
		);


		lua["unity"] = unity_table;

		auto game_table = lua.create_table();
		game_table.set_function("get_entities", []() {
			static uintptr_t clientEntities = NULL;

			auto getClientEntities = [&]() {
				clientEntities = il2cpp::value(_("BaseNetworkable"), _("clientEntities"), false);
			};
			if (!clientEntities)
				getClientEntities();

			if (uintptr_t entityRealm = M::read<uintptr_t>(clientEntities + 0x10))
			{
				if (!entityRealm)
					getClientEntities();
				if (uintptr_t bufferList = M::read<uintptr_t>(entityRealm + 0x28))
				{
					if (!bufferList)
						getClientEntities();
					if (uintptr_t objectList = M::read<uintptr_t>(bufferList + 0x18))
					{
						if (!objectList)
							getClientEntities();
						if (uint32_t objectListSize = M::read<uint32_t>(bufferList + 0x10))
						{
							if (!objectListSize)
								getClientEntities();

							for (auto i = 0; i < objectListSize; i++) {
								auto curObject = M::read<uintptr_t>(objectList + (0x20 + (i * 0x8)));
							}
						}
					}
				}
			}
			}
		);

		lua["game"] = game_table;
		//scriptable.get_entity(i);
		Vector3 newvec = Vector3(10, 10, 10);
		std::cout << "newvec Length CPP: " << newvec.Length() << std::endl;
		auto loaded = lua.safe_script("print(unity.getscreen());print(unity.getscreen().x);print(unity.getscreen().y)");
		if (!loaded.valid())
		{
			sol::error e = loaded;
			printf("lua err: %s", e.what());
		}
		return loaded.valid();*/
		return true;
	}
}