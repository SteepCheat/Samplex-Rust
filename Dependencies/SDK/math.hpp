#pragma once
#include <Windows.h>
#include <iostream>
#include <psapi.h>
#include <emmintrin.h>
#include "winternl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <vector>
// dont even know where I found this file from in my hard drive, good to know this garbage is in this project.


#define ToLower(Char) ((Char >= 'A' && Char <= 'Z') ? (Char + 32) : Char)
namespace M {

	uintptr_t UnityPlayer, GameAssembly;

	inline void init()
	{
		M::GameAssembly = LI_MODULE_SAFE_(_("GameAssembly.dll"));
		M::UnityPlayer = LI_MODULE_SAFE_(_("UnityPlayer.dll"));
	}

	template<typename T>
	inline T read(uintptr_t const address)
	{
		return *reinterpret_cast<T*>(address);
	}
	template <typename T>
	inline void write(uintptr_t const address, T data)
	{
		*reinterpret_cast<T*>(address) = data;
	}

	struct LDR_DATA_TABLE_ENTRY_FIX
	{
		PVOID Reserved1[2];
		LIST_ENTRY InMemoryOrderLinks;
		PVOID Reserved2[2];
		PVOID DllBase;
		PVOID Reserved3[1];
		ULONG64 SizeOfImage;
		UNICODE_STRING FullDllName;
		UNICODE_STRING BaseDllName;
		PVOID Reserved5[2];
#pragma warning(push)
#pragma warning(disable: 4201)
		union {
			ULONG CheckSum;
			PVOID Reserved6;
		} DUMMYUNIONNAME;
#pragma warning(pop)
		ULONG TimeDateStamp;
	};

	template <typename StrType>
	__declspec(noinline) constexpr unsigned short HashStr(StrType Data, int Len) {
		unsigned short CRC = 0xFFFF;
		while (Len--) {
			auto CurChar = *Data++;
			if (!CurChar) {
				break;
			}

			CRC ^= ToLower(CurChar) << 8;

			for (int i = 0; i < 8; i++) {
				CRC = CRC & 0x8000 ? (CRC << 1) ^ 0x8408 : CRC << 1;
			}
		}

		return CRC;
	}
	#define ConstStrLen(Str) ((sizeof(Str) - sizeof(Str[0])) / sizeof(Str[0]))
	#define ConstHashStr(Str) [](){ constexpr unsigned short CRC = HashStr(Str, ConstStrLen(Str)); return CRC; }()
	template <typename PtrType>
	__forceinline PtrType ptrEnc(PtrType Ptr) {//take a guess what this does
		typedef union { struct { USHORT Key1; USHORT Key2; USHORT Key3; USHORT Key4; }; ULONG64 Key; } CryptData;

		CryptData Key{ ConstHashStr(__TIME__), ConstHashStr(__DATE__), ConstHashStr(__TIMESTAMP__), ConstHashStr(__TIMESTAMP__) };

		return (PtrType)((DWORD64)Ptr ^ Key.Key);
	}

	namespace MFunc {
		inline char* m_strstr(char* input, const char* find)
		{
			do {
				const char* p, * q;
				for (p = input, q = find; *q != '\0' && *p == *q; p++, q++) {}
				if (*q == '\0') {
					return input;
				}
			} while (*(input++) != '\0');
			return 0;
		}

		inline bool m_strcmp(char* a, char* b) {
			if ((uintptr_t)a == 0x00000000ffffffff || (uintptr_t)b == 0x00000000ffffffff)
				return false;
			if ((uintptr_t)a == 0x000000000000007d || (uintptr_t)b == 0x000000000000007d)
				return false;

			if (!a || !b) return !a && !b;

			int ret = 0;
			unsigned char* p1 = (unsigned char*)a;
			unsigned char* p2 = (unsigned char*)b;
			while (!(ret = *p1 - *p2) && *p2)
				++p1, ++p2;

			return ret == 0;
		}

		float sqrtf(float number) {
			long i;
			float x, y;
			const float f = 1.5F;

			x = number * 0.5F;
			y = number;
			i = *(long*)&y;
			i = 0x5f3759df - (i >> 1);
			y = *(float*)&i;
			y = y * (f - (x * y * y));
			y = y * (f - (x * y * y));
			return number * y;
		}

		float pow(float base, float ex);
		float nth_root(float A, int n) {
			const int K = 6;
			float x[K] = { 1 };
			for (int k = 0; k < K - 1; k++)
				x[k + 1] = (1.0 / n) * ((n - 1) * x[k] + A / pow(x[k], n - 1));
			return x[K - 1];
		}
		float pow(float base, float ex) {
			if (base == 0)
				return 0;
			// power of 0
			if (ex == 0) {
				return 1;
				// negative exponenet
			}
			else if (ex < 0) {
				return 1 / pow(base, -ex);
				// fractional exponent
			}
			else if (ex > 0 && ex < 1) {
				return nth_root(base, 1 / ex);
			}
			else if ((int)ex % 2 == 0) {
				float half_pow = pow(base, ex / 2);
				return half_pow * half_pow;
				//integer exponenet
			}
			else {
				return base * pow(base, ex - 1);
			}
		}
	}
}

class Vector3
{
public:
	float x, y, h;

	inline Vector3() {
		x = y = h = 0.0f;
	}

	inline Vector3(float X, float Y, float Z) {
		x = X; y = Y; h = Z;
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline Vector3& operator-=(float v) {
		x -= v; y -= v; h -= v; return *this;
	}

	inline Vector3 operator*(float v) const {
		return Vector3(x * v, y * v, h * v);
	}

	inline Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, h / v);
	}

	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; h += v.h; return *this;
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, h - v.h);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, h + v.h);
	}

	float Dot(const Vector3& vector)
	{
		return x * vector.x + y * vector.y + h * vector.h;
	}

	inline float Distance(Vector3 v)
	{
		return float(M::MFunc::sqrtf(M::MFunc::pow(v.x - x, 2.0) + M::MFunc::pow(v.y - y, 2.0) + M::MFunc::pow(v.h - h, 2.0)));
	}

	inline float Length() {
		return M::MFunc::sqrtf(x * x + y * y + h * h);
	}

	inline bool operator==(const Vector3& v) const {
		if (this->x == v.x && this->y == v.y && this->h == v.h)
			return true;
		else
			return false;
	}

	inline bool operator!=(const Vector3& v) const {
		if (this->x == v.x && this->y == v.y && this->h == v.h)
			return false;
		else
			return true;
	}
};

class Vector2 {
public:
	float x, y;

	inline Vector2() {
		x = y = 0.0f;
	}

	inline Vector2(float f1, float f2) {
		x = f1;
		y = f2;
	}

	inline Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}

	void operator -= (Vector2 other)
	{
		// Update this vector's values
		x -= other.x;
		y -= other.y;
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	inline bool Zero() const {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}
};

class Vector4 {
public:
	float x;
	float y;
	float w;//width
	float h;//height
};

struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		}; float m[4][4];
	};
};