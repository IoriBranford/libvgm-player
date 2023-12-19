#ifndef PlayerC_C_H
#define PlayerC_C_H

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
DLLEXPORT uint8_t PlayerC_SetOutputSettings(PlayerC *p, uint32_t smplRate, uint8_t channels, uint8_t smplBits, uint32_t smplBufferLen);
DLLEXPORT void PlayerC_SetLoopCount(PlayerC *p, uint32_t loopCount);
DLLEXPORT void PlayerC_SetFadeSeconds(PlayerC *p, uint32_t seconds);

DLLEXPORT uint8_t PlayerC_LoadFile(PlayerC *p, const char *filename);
DLLEXPORT uint8_t PlayerC_LoadMemory(PlayerC *p, const uint8_t *data, uint32_t length);

DLLEXPORT uint8_t PlayerC_Start(PlayerC *p);
DLLEXPORT uint32_t PlayerC_Render(PlayerC *p, uint32_t bufSize, void *data);
DLLEXPORT uint8_t PlayerC_FadeOut(PlayerC *p);
DLLEXPORT uint8_t PlayerC_Stop(PlayerC *p);

DLLEXPORT void PlayerC_delete(PlayerC *p);

#ifdef __cplusplus
} // extern "C"
#endif

#endif