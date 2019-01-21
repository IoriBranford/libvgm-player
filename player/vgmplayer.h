#ifndef __VGMPLAYER_H__
#define __VGMPLAYER_H__

#include <inttypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

typedef struct VGMPlayer VGMPlayer;

DLLEXPORT VGMPlayer* vgmNewPlayer();
DLLEXPORT void vgmDeletePlayer(VGMPlayer *vgmPlayer);

//uint32_t GetPlayerType(void) const;
//const char* GetPlayerName(void) const;
DLLEXPORT uint8_t vgmLoadFile(VGMPlayer *vgmPlayer, const char* fileName);
DLLEXPORT uint8_t vgmLoadData(VGMPlayer *vgmPlayer, size_t fileSize, uint8_t* fileData);
DLLEXPORT uint8_t vgmUnload(VGMPlayer *vgmPlayer);

//const VGM_HEADER* GetFileHeader(void) const
DLLEXPORT const char* vgmGetSongTitle(VGMPlayer *vgmPlayer);
////uint32_t GetSampleRate(void) const
DLLEXPORT uint8_t vgmSetSampleRate(VGMPlayer *vgmPlayer, uint32_t sampleRate);
////uint8_t vgmSetPlaybackSpeed(VGMPlayer *vgmPlayer, double speed);
////void vgmSetCallback(VGMPlayer *vgmPlayer, PLAYER_EVENT_CB cbFunc, void* cbParam);

DLLEXPORT uint32_t vgmTick2Sample(const VGMPlayer *vgmPlayer, uint32_t ticks);
DLLEXPORT uint32_t vgmSample2Tick(const VGMPlayer *vgmPlayer, uint32_t samples);
DLLEXPORT double vgmTick2Second(const VGMPlayer *vgmPlayer, uint32_t ticks);
////double vgmSample2Second(uint32_t samples);

DLLEXPORT uint8_t vgmGetState(const VGMPlayer *vgmPlayer);
DLLEXPORT uint32_t vgmGetCurFileOfs(const VGMPlayer *vgmPlayer);
DLLEXPORT uint32_t vgmGetCurTick(const VGMPlayer *vgmPlayer);
DLLEXPORT uint32_t vgmGetCurSample(const VGMPlayer *vgmPlayer);
DLLEXPORT uint32_t vgmGetTotalTicks(const VGMPlayer *vgmPlayer);	// get time for playing once in ticks
DLLEXPORT uint32_t vgmGetLoopTicks(const VGMPlayer *vgmPlayer);	// get time for one loop in ticks
////uint32_t vgmGetTotalPlayTicks(const VGMPlayer *vgmPlayer, uint32_t numLoops);	// get time for playing + looping (without fading)
DLLEXPORT uint32_t vgmGetCurrentLoop(const VGMPlayer *vgmPlayer);

DLLEXPORT uint8_t vgmStart(VGMPlayer *vgmPlayer);
DLLEXPORT uint8_t vgmStop(VGMPlayer *vgmPlayer);
DLLEXPORT uint8_t vgmReset(VGMPlayer *vgmPlayer);

DLLEXPORT uint32_t vgmPlay(VGMPlayer *vgmPlayer, uint32_t smplCnt, int16_t* data);
////uint8_t vgmSeek(...); // TODO

#ifdef __cplusplus
}
#endif

#endif
