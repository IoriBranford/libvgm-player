#include "vgmplayer.hpp"
#include "vgmplayer.h"

extern "C" {
	VGMPlayer* vgmNewPlayer() {
		return new VGMPlayer();
	}
	void vgmDeletePlayer(VGMPlayer *vgmPlayer) {
		delete vgmPlayer;
	}
	//UINT32 GetPlayerType(void) const;
	//const char* GetPlayerName(void) const;
	UINT8 vgmLoadFile(VGMPlayer *vgmPlayer, const char* fileName) {
		return vgmPlayer->LoadFile(fileName);
	}
	UINT8 vgmLoadData(VGMPlayer *vgmPlayer, size_t fileSize, UINT8* fileData) {
		return vgmPlayer->LoadData(fileSize, fileData);
	}
	UINT8 vgmUnload(VGMPlayer *vgmPlayer) {
		return vgmPlayer->UnloadFile();
	}
	//const VGM_HEADER* GetFileHeader(void) const
	const char* vgmGetSongTitle(VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetSongTitle();
	}
	////UINT32 GetSampleRate(void) const
	UINT8 vgmSetSampleRate(VGMPlayer *vgmPlayer, UINT32 sampleRate) {
		return vgmPlayer->SetSampleRate(sampleRate);
	}
	////UINT8 vgmSetPlaybackSpeed(VGMPlayer *vgmPlayer, double speed) {}
	////void vgmSetCallback(VGMPlayer *vgmPlayer, PLAYER_EVENT_CB cbFunc, void* cbParam) {}
	UINT32 vgmTick2Sample(const VGMPlayer *vgmPlayer, UINT32 ticks) {
		return vgmPlayer->Tick2Sample(ticks);
	}
	UINT32 vgmSample2Tick(const VGMPlayer *vgmPlayer, UINT32 samples) {
		return vgmPlayer->Sample2Tick(samples);
	}
	double vgmTick2Second(const VGMPlayer *vgmPlayer, UINT32 ticks) {
		return vgmPlayer->Tick2Second(ticks);
	}
	////double vgmSample2Second(UINT32 samples) {}
	UINT8 vgmIsPlaying(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetState() & PLAYSTATE_PLAY;
	}
	UINT8 vgmGetState(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetState();
	}
	UINT32 vgmGetCurFileOfs(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetCurFileOfs();
	}
	UINT32 vgmGetCurTick(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetCurTick();
	}
	UINT32 vgmGetCurSample(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetCurSample();
	}
	UINT32 vgmGetTotalTicks(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetTotalTicks();
	}	// get time for playing once in ticks
	UINT32 vgmGetLoopTicks(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetLoopTicks();
	}	// get time for one loop in ticks
	////UINT32 vgmGetTotalPlayTicks(const VGMPlayer *vgmPlayer, UINT32 numLoops) {}	// get time for playing + looping (without fading)
	UINT32 vgmGetCurrentLoop(const VGMPlayer *vgmPlayer) {
		return vgmPlayer->GetCurrentLoop();
	}
	UINT8 vgmStart(VGMPlayer *vgmPlayer) {
		return vgmPlayer->Start();
	}
	UINT8 vgmStop(VGMPlayer *vgmPlayer) {
		return vgmPlayer->Stop();
	}
	UINT8 vgmReset(VGMPlayer *vgmPlayer) {
		return vgmPlayer->Reset();
	}
	UINT32 vgmPlay(VGMPlayer *vgmPlayer, UINT32 smplCnt, INT16* data) {
		static std::vector<WAVE_32BS> samples;
		samples.resize(smplCnt);
		UINT32 n = vgmPlayer->Render(smplCnt, samples.data());
		WAVE_32BS *sample = samples.data();
		for (UINT32 i = 0; i < smplCnt; ++i) {
			sample->L >>= 8;	// 24 bit -> 16 bit
			sample->R >>= 8;
			if (sample->L < -0x8000)
				sample->L = -0x8000;
			else if (sample->L > +0x7FFF)
				sample->L = +0x7FFF;
			if (sample->R < -0x8000)
				sample->R = -0x8000;
			else if (sample->R > +0x7FFF)
				sample->R = +0x7FFF;
			data[0] = (INT16)sample->L;
			data[1] = (INT16)sample->R;
			data += 2;
			++sample;
		}
		return n;
	}
	////UINT8 vgmSeek(...) {} // TODO
}
