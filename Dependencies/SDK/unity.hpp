
namespace Unity//This namespace is a mess.
{
	class string {
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static string* newString(const char* str);
	};

	using il2cpp_string_new_wrapper = string*(*)(const char*);
	static auto UnityString = LI_FIND_DEF(il2cpp_string_new_wrapper);

	inline string* string::newString(const char* str)
	{
		return SpoofReturn(UnityString, str);
	}

	enum class EventType : int {
		MouseDown = 0,
		MouseUp = 1,
		MouseDrag = 3,
		KeyDown = 4,
		KeyUp = 5,
		Repaint = 7
	};

	enum class ModelStateFLAG
	{
		Ducked = 1,
		Jumped = 2,
		OnGround = 4,
		Sleeping = 8,
		Sprinting = 16,
		OnLadder = 32,
		Flying = 64,
		Aiming = 128,
		Prone = 256,
		Mounted = 512,
		Relaxed = 1024,
	};

	enum class KeyCode
	{
		Backspace = 8,
		Delete = 127,
		Tab = 9,
		Clear = 12,
		Return = 13,
		Pause = 19,
		Escape = 27,
		Space = 32,
		Keypad0 = 256,
		Keypad1 = 257,
		Keypad2 = 258,
		Keypad3 = 259,
		Keypad4 = 260,
		Keypad5 = 261,
		Keypad6 = 262,
		Keypad7 = 263,
		Keypad8 = 264,
		Keypad9 = 265,
		KeypadPeriod = 266,
		KeypadDivide = 267,
		KeypadMultiply = 268,
		KeypadMinus = 269,
		KeypadPlus = 270,
		KeypadEnter = 271,
		KeypadEquals = 272,
		UpArrow = 273,
		DownArrow = 274,
		RightArrow = 275,
		LeftArrow = 276,
		Insert = 277,
		Home = 278,
		End = 279,
		PageUp = 280,
		PageDown = 281,
		F1 = 282,
		F2 = 283,
		F3 = 284,
		F4 = 285,
		F5 = 286,
		F6 = 287,
		F7 = 288,
		F8 = 289,
		F9 = 290,
		F10 = 291,
		F11 = 292,
		F12 = 293,
		F13 = 294,
		F14 = 295,
		F15 = 296,
		Alpha0 = 48,
		Alpha1 = 49,
		Alpha2 = 50,
		Alpha3 = 51,
		Alpha4 = 52,
		Alpha5 = 53,
		Alpha6 = 54,
		Alpha7 = 55,
		Alpha8 = 56,
		Alpha9 = 57,
		Exclaim = 33,
		DoubleQuote = 34,
		Hash = 35,
		Dollar = 36,
		Percent = 37,
		Ampersand = 38,
		Quote = 39,
		LeftParen = 40,
		RightParen = 41,
		Asterisk = 42,
		Plus = 43,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Colon = 58,
		Semicolon = 59,
		Less = 60,
		Equals = 61,
		Greater = 62,
		Question = 63,
		At = 64,
		LeftBracket = 91,
		Backslash = 92,
		RightBracket = 93,
		Caret = 94,
		Underscore = 95,
		BackQuote = 96,
		A = 97,
		B = 98,
		C = 99,
		D = 100,
		E = 101,
		F = 102,
		G = 103,
		H = 104,
		I = 105,
		J = 106,
		K = 107,
		L = 108,
		M = 109,
		N = 110,
		O = 111,
		P = 112,
		Q = 113,
		R = 114,
		S = 115,
		T = 116,
		U = 117,
		V = 118,
		W = 119,
		X = 120,
		Y = 121,
		Z = 122,
		LeftCurlyBracket = 123,
		Pipe = 124,
		RightCurlyBracket = 125,
		Tilde = 126,
		Numlock = 300,
		CapsLock = 301,
		ScrollLock = 302,
		RightShift = 303,
		LeftShift = 304,
		RightControl = 305,
		LeftControl = 306,
		RightAlt = 307,
		LeftAlt = 308,
		LeftCommand = 310,
		LeftApple = 310,
		LeftWindows = 311,
		RightCommand = 309,
		RightApple = 309,
		RightWindows = 312,
		AltGr = 313,
		Help = 315,
		Pr = 316,
		SysReq = 317,
		Break = 318,
		Menu = 319,
		Mouse0 = 323,
		Mouse1 = 324,
		Mouse2 = 325,
		Mouse3 = 326,
		Mouse4 = 327,
		Mouse5 = 328,
		Mouse6 = 329
	};

	enum class Layers
	{
		Terrain = 8388608,
		World = 65536,
		Ragdolls = 512,
		Construction = 2097152,
		ConstructionSocket = 4194304,
		Craters = 1,
		GameTrace = 16384,
		Trigger = 262144,
		VehiclesDetailed = 8192,
		RainFall = 1101070337,
		Deploy = 1235288065,
		DefaultDeployVolumeCheck = 537001984,
		BuildLineOfSightCheck = 2097152,
		ProjectileLineOfSightCheck = 2162688,
		ProjectileLineOfSightCheckTerrain = 10551296,
		MeleeLineOfSightCheck = 2162688,
		EyeLineOfSightCheck = 2162688,
		EntityLineOfSightCheck = 1218519041,
		PlayerBuildings = 18874624,
		PlannerPlacement = 161546496,
		Solid = 1218652417,
		VisCulling = 10551297,
		AltitudeCheck = 1218511105,
		HABGroundEffect = 1218511105,
		AILineOfSight = 1218519297,
		DismountCheck = 1486946561,
		AIPlacement = 278986753,
		WheelRay = 1235321089,
	};

	enum class PlayerFlags
	{
		Unused1 = 1,
		Unused2 = 2,
		IsAdmin = 4,
		ReceivingSnapshot = 8,
		Sleeping = 16,
		Spectating = 32,
		Wounded = 64,
		IsDeveloper = 128,
		Connected = 256,
		ThirdPersonViewmode = 1024,
		EyesViewmode = 2048,
		ChatMute = 4096,
		NoSprint = 8192,
		Aiming = 16384,
		DisplaySash = 32768,
		Relaxed = 65536,
		SafeZone = 131072,
		ServerFall = 262144,
		Workbench1 = 1048576,
		Workbench2 = 2097152,
		Workbench3 = 4194304,
	};

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

	class Color {
	public:
		float r;
		float g;
		float b;
		float a;
		Color(float rr, float gg, float bb, float aa) : r(rr), g(gg), b(bb) { }//people need to make contructors like this more often
	};

	template<typename T>
	class list {
	public:
		T get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T getValue(uint32_t idx)
		{
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T operator[](uint32_t idx) { return get(idx); }

		const uint32_t getSize() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

		template<typename F>
		void forEach(const F callback)
		{
			for (auto i = 0; i < getSize(); i++) {
				auto object = this->get(i);
				if (!object)
					continue;
				callback(object, i);
			}
		}
	};


	typedef Vector3 (__stdcall* GetPosition)(uintptr_t);
	GetPosition getPosition = *reinterpret_cast<GetPosition*>(il2cpp::method(_("Transform"), _("get_position"), _("UnityEngine"), 0));

	class Transform {
	public:
		Vector3 GetPosition() {
			if (!(uintptr_t)this)
				return {};

			return getPosition((uintptr_t)this);
		}
	};

	typedef void* (__stdcall* DrawTexture)(Vector4, uintptr_t);
	DrawTexture drawTexture = *reinterpret_cast<DrawTexture*>(il2cpp::method(_("GUI"), _("DrawTexture"), _("UnityEngine"), 2, _("image"), 2));
	
	typedef float (__stdcall* Clamp)(float, float, float);
	Clamp clamp = *reinterpret_cast<Clamp*>(il2cpp::method(_("Mathf"), _("Clamp"), _("UnityEngine"), 3));

	typedef uintptr_t(__stdcall* GetTextureBlack)();
	GetTextureBlack getTextureBlack = *reinterpret_cast<GetTextureBlack*>(il2cpp::method(_("Texture2D"), _("get_blackTexture"), _("UnityEngine"), 0));

	typedef bool(__stdcall* tLineOfSight)(Vector3, Vector3, Layers, float);
	tLineOfSight LineOfSight = *reinterpret_cast<tLineOfSight*>(il2cpp::method(_("GamePhysics"), _("LineOfSight"), _(""), 4));

	typedef void* (__stdcall* SetAlignment)(uintptr_t, uintptr_t);
	SetAlignment setAlignment = *reinterpret_cast<SetAlignment*>(il2cpp::method(_("GUIStyle"), _("set_alignment"), _("UnityEngine"), -1));

	typedef uintptr_t(__stdcall* GetSkin)();
	GetSkin getSkin = *reinterpret_cast<GetSkin*>(il2cpp::method(_("GUI"), _("get_skin"), _("UnityEngine"), 0));

	typedef void* (__stdcall* SetColor)(Color);
	SetColor setColor = *reinterpret_cast<SetColor*>(il2cpp::method(_("GUI"), _("set_color"), _("UnityEngine"), -1));
	
	typedef void* (__stdcall* GuiContentTemp)(string*);
	GuiContentTemp guiContentTemp = *reinterpret_cast<GuiContentTemp*>(il2cpp::method(_("GUIContent"), _("Temp"), _("UnityEngine"), 1, _("t"), 1));
	
	typedef void* (__stdcall* SetFontSize)(uintptr_t, int);
	SetFontSize setFontSize = *reinterpret_cast<SetFontSize*>(il2cpp::method(_("GUIStyle"), _("set_fontSize"), _("UnityEngine"), 1));
	
	typedef void* (__stdcall* GetType)(uintptr_t);
	SetFontSize getType = *reinterpret_cast<SetFontSize*>(il2cpp::method(_("Event"), _("get_type"), _("UnityEngine"), 0));
	
	typedef void* (__stdcall* GetCurrent)();
	GetCurrent getCurrent = *reinterpret_cast<GetCurrent*>(il2cpp::method(_("Event"), _("get_current"), _("UnityEngine"), 0));
	
	typedef void* (__stdcall* GetKeyCode)(uintptr_t);
	GetKeyCode getKeyCode = *reinterpret_cast<GetKeyCode*>(il2cpp::method(_("Event"), _("get_keyCode"), _("UnityEngine"), 0));
	
	typedef void* (__stdcall* Label)(Vector4, uintptr_t, uintptr_t);
	Label label = *reinterpret_cast<Label*>(il2cpp::method(_("GUI"), _("Label"), _("UnityEngine"), 3, _("content"), 2));

	typedef int(__stdcall* GetScreenX)();
	GetScreenX getScreenX = *reinterpret_cast<GetScreenX*>(il2cpp::method(_("Screen"), _("get_width"), _("UnityEngine"), 0));

	typedef int(__stdcall* GetScreenY)();
	GetScreenY getScreenY = *reinterpret_cast<GetScreenY*>(il2cpp::method(_("Screen"), _("get_height"), _("UnityEngine"), 0));


	//was to lazy to convert all to typedefs, why I made them typedefs in the firstplace? because I thought they looked neat. suck it bozo's
	static auto getRenderers = reinterpret_cast<list<uintptr_t>*(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("SkinnedMultiMesh"), _("get_Renderers"), _(""), 0)));
	static auto getMainCamera = reinterpret_cast<uintptr_t(*)()>(il2cpp::methods::resolve_icall(_("UnityEngine.Camera::get_main()")));
	static auto getTransform = reinterpret_cast<Transform * (*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Component"), _("get_transform"), _("UnityEngine"), 0)));
	static auto getTextureWhite = reinterpret_cast<uintptr_t(*)()>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Texture2D"), _("get_whiteTexture"), _("UnityEngine"), 0, _(""))));
	static auto getMaterial = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Renderer"), _("get_material"), _("UnityEngine"), 0)));
	static auto getKeyUp = reinterpret_cast<bool(*)(KeyCode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyUp"), _("UnityEngine"), 1)));
	static auto getKeyDown = reinterpret_cast<bool(*)(KeyCode)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Input"), _("GetKeyDown"), _("UnityEngine"), 1, _("key"), 1)));
	static auto loadAssetFromFileInternal = reinterpret_cast<uintptr_t(*)(Unity::string*, std::uint32_t, std::uint64_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadFromFile_Internal"), _("UnityEngine"), 3)));
	static auto loadAssetInternal = reinterpret_cast<uintptr_t(*)(uintptr_t, Unity::string*, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("AssetBundle"), _("LoadAsset_Internal"), _("UnityEngine"), 3)));
	static auto setShader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(_("UnityEngine.Material::set_shader()")));
	static auto getShader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("get_shader"), _("UnityEngine"), 0)));
	static auto shaderFind = reinterpret_cast<uintptr_t(*)(string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Shader"), _("Find"), _("UnityEngine"), 1)));
	static auto materialSetColor = reinterpret_cast<void(*)(uintptr_t material, string* name, Color value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("SetColor"), _("UnityEngine"), 2, _("name"), 1)));
	static auto materialSetInt = reinterpret_cast<void(*)(uintptr_t material, string name, int value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("SetInt"), _("UnityEngine"), 2, _("name"), 1)));
	static auto materialSetFloat = reinterpret_cast<void(*)(uintptr_t material, string name, float value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(_("Material"), _("SetFloat"), _("UnityEngine"), 2, _("name"), 1)));
	
}