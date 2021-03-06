// SKC-KiS3.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "resource.h"
#include "..\skc-mod-loader\SKCModLoader\SKCModLoader.h"

DataPointer(short, Camera_target_max_Y_pos, 0x8FFEE12);
DataPointer(short, Camera_max_Y_pos, 0x8FFEE1A);
DataPointer(short, Dynamic_resize_routine, 0x8FFEE33);
DataPointer(short, Camera_X_pos, 0x8FFEE78);
VoidFunc(StartNewLevel, 0x6F2A3C);
VoidFunc(Delete_Current_Sprite, 0x41EACF);

HMODULE moduleHandle;

void StartS3Credits()
{
	if (GameSelection == 2)
		Game_mode = GameModeID_S3Credits;
	else
	{
		reg_d0.Word = mushroom_hill_zone_act_1;
		StartNewLevel();
	}
	Delete_Current_Sprite();
}

void __cdecl AIZ2_KnuxResize3()
{
	if ((unsigned __int16)Camera_X_pos >= 0x11A0u)
	{
		Camera_target_max_Y_pos = 0x820;
		Camera_max_Y_pos = 0x820;
		Dynamic_resize_routine += 2;
	}
}

struct PLCList
{
	short count;
#pragma warning(suppress: 4200)
	PLC PLCs[];
};

PLCList PLC_EndSignStuff = {
	2,
	(const void*)0x510234, 0x9280,
	(const void*)0x532CDC, 0xD3C0,
	(const void*)0x50E508, 0x9880,
};

int objfiles[] = {
	IDR_OBJECTS_AIZ1,
	IDR_OBJECTS_AIZ2,
	IDR_OBJECTS_HCZ1,
	IDR_OBJECTS_HCZ2,
	IDR_OBJECTS_MGZ1,
	IDR_OBJECTS_MGZ2,
	IDR_OBJECTS_CNZ1,
	IDR_OBJECTS_CNZ2,
	0,
	0,
	IDR_OBJECTS_ICZ1,
	IDR_OBJECTS_ICZ2,
	IDR_OBJECTS_LBZ1,
	IDR_OBJECTS_LBZ2
};

int rngfiles[] = {
	IDR_RINGS_AIZ1,
	IDR_RINGS_AIZ2,
	IDR_RINGS_HCZ1,
	IDR_RINGS_HCZ2,
	IDR_RINGS_MGZ1,
	IDR_RINGS_MGZ2,
	IDR_RINGS_CNZ1,
	IDR_RINGS_CNZ2,
	0,
	0,
	IDR_RINGS_ICZ1,
	IDR_RINGS_ICZ2,
	IDR_RINGS_LBZ1,
	IDR_RINGS_LBZ2
};

extern "C"
{
	__declspec(dllexport) void Init(const wchar_t *path, const HelperFunctions &helperFunctions)
	{
		WriteData((char*)0x6EB507, (char)3);
		WriteData((char*)0x6EB542, (char)3);
		WriteJump((void*)0x450096, AIZ2_KnuxResize3);
		WriteJump((void*)0x72FB3C, StartS3Credits);
		WriteData((PLCList**)0x6F2323, &PLC_EndSignStuff);
		void **objptr = SpriteLocPtrs3;
		void **rngptr = RingLocPtrs3;
		for (size_t i = 0; i < LengthOfArray(objfiles); i++)
		{
			if (objfiles[i])
			{
				HRSRC handle = FindResource(moduleHandle, MAKEINTRESOURCE(objfiles[i]), TEXT("Objects"));
				*objptr = LockResource(LoadResource(moduleHandle, handle));
				handle = FindResource(moduleHandle, MAKEINTRESOURCE(rngfiles[i]), TEXT("Rings"));
				*rngptr = LockResource(LoadResource(moduleHandle, handle));
			}
			++objptr;
			++rngptr;
		}
	}

	__declspec(dllexport) ModInfo SKCModInfo = { ModLoaderVer };
}