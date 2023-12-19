#include "playerc.h"
#include "playera.hpp"
#include "vgmplayer.hpp"
#include "utils/FileLoader.h"
#include "utils/MemoryLoader.h"

PlayerC* PlayerC_NewVGM() {
    PlayerC *p = new PlayerC;
    p->player = new PlayerA;
    p->player->RegisterPlayerEngine(new VGMPlayer);
    p->loader = nullptr;
    p->player->SetFadeSamples(p->player->GetSampleRate());
    return p;
}

uint8_t PlayerC_SetOutputSettings(PlayerC *p, uint32_t smplRate, uint8_t channels, uint8_t smplBits, uint32_t smplBufferLen) {
    return p->player->SetOutputSettings(smplRate, channels, smplBits, smplBufferLen);
}

void PlayerC_SetLoopCount(PlayerC *p, uint32_t loops) {
    p->player->SetLoopCount(loops);
}

void PlayerC_SetFadeSeconds(PlayerC *p, uint32_t seconds) {
    p->player->SetFadeSamples(p->player->GetSampleRate() * seconds);
}

uint8_t PlayerC_LoadData(PlayerC *p, DATA_LOADER *loader) {
    if (!loader)
        return ENOMEM;

    uint8_t error = DataLoader_Load(loader);
    if (!error) {
        error = p->player->LoadFile(loader);
    }
    if (!error) {
        p->loader = loader;
    }

    if (error)
        DataLoader_Deinit(loader);
    return error;
}

uint8_t PlayerC_LoadFile(PlayerC *p, const char *filename) {
    return PlayerC_LoadData(p, FileLoader_Init(filename));
}

uint8_t PlayerC_LoadMemory(PlayerC *p, const uint8_t *data, uint32_t length) {
    return PlayerC_LoadData(p, MemoryLoader_Init(data, length));
}

uint8_t PlayerC_Start(PlayerC *p) {
    return p->player->Start();
}

uint32_t PlayerC_Render(PlayerC *p, uint32_t bufSize, void *data) {
    return p->player->Render(bufSize, data);
}

uint8_t PlayerC_FadeOut(PlayerC *p) {
    return p->player->FadeOut();
}

uint8_t PlayerC_Stop(PlayerC *p) {
    return p->player->Stop();
}

void PlayerC_delete(PlayerC *p) {
    if (p != nullptr) {
        if (p->player != nullptr) {
            p->player->Stop();
            p->player->UnloadFile();
            p->player->UnregisterAllPlayers();
            delete p->player;
        }
        if (p->loader != nullptr) {
            DataLoader_Deinit(p->loader);
        }
        delete p;
    }
}