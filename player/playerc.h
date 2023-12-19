#ifndef PlayerC_C_H
#define PlayerC_C_H

#include "../stdtype.h"
#include "utils/DataLoader.h"

#ifdef __cplusplus
extern "C" {
#endif

struct PlayerA;

struct PlayerC {
    PlayerA *player;
    DATA_LOADER *loader;
};

PlayerC* PlayerC_NewVGM();
UINT8 PlayerC_SetOutputSettings(PlayerC *p, UINT32 smplRate, UINT8 channels, UINT8 smplBits, UINT32 smplBufferLen);
void PlayerC_SetLoopCount(PlayerC *p, UINT32 loopCount);

UINT8 PlayerC_LoadFile(PlayerC *p, const char *filename);
UINT8 PlayerC_LoadMemory(PlayerC *p, const UINT8 *data, UINT32 length);

UINT8 PlayerC_Start(PlayerC *p);
UINT32 PlayerC_Render(PlayerC *p, UINT32 bufSize, void *data);
UINT8 PlayerC_FadeOut(PlayerC *p);
UINT8 PlayerC_Stop(PlayerC *p);

void PlayerC_delete(PlayerC *p);

#ifdef __cplusplus
} // extern "C"
#endif

#endif