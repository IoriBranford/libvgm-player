#ifndef PlayerC_C_H
#define PlayerC_C_H

#include "../stdtype.h"
#include "utils/DataLoader.h"

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PlayerA PlayerA;

typedef struct PlayerC {
    PlayerA *player;
    DATA_LOADER *loader;
} PlayerC;

DLLEXPORT PlayerC* PlayerC_NewVGM();
DLLEXPORT UINT8 PlayerC_SetOutputSettings(PlayerC *p, UINT32 smplRate, UINT8 channels, UINT8 smplBits, UINT32 smplBufferLen);
DLLEXPORT void PlayerC_SetLoopCount(PlayerC *p, UINT32 loopCount);
DLLEXPORT void PlayerC_SetFadeSeconds(PlayerC *p, UINT32 seconds);

DLLEXPORT UINT8 PlayerC_LoadFile(PlayerC *p, const char *filename);
DLLEXPORT UINT8 PlayerC_LoadMemory(PlayerC *p, const UINT8 *data, UINT32 length);

DLLEXPORT UINT8 PlayerC_Start(PlayerC *p);
DLLEXPORT UINT32 PlayerC_Render(PlayerC *p, UINT32 bufSize, void *data);
DLLEXPORT UINT8 PlayerC_FadeOut(PlayerC *p);
DLLEXPORT UINT8 PlayerC_Stop(PlayerC *p);

DLLEXPORT void PlayerC_delete(PlayerC *p);

#ifdef __cplusplus
} // extern "C"
#endif

#endif