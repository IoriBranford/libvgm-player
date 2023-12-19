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
    return p;
}

UINT8 PlayerC_SetOutputSettings(PlayerC *p, UINT32 smplRate, UINT8 channels, UINT8 smplBits, UINT32 smplBufferLen) {
    return p->player->SetOutputSettings(smplRate, channels, smplBits, smplBufferLen);
}

void PlayerC_SetLoopCount(PlayerC *p, UINT32 loops) {
    p->player->SetLoopCount(loops);
}

UINT8 PlayerC_LoadData(PlayerC *p, DATA_LOADER *loader) {
    if (!loader)
        return ENOMEM;

    UINT8 error = DataLoader_Load(loader);
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

UINT8 PlayerC_LoadFile(PlayerC *p, const char *filename) {
    return PlayerC_LoadData(p, FileLoader_Init(filename));
}

UINT8 PlayerC_LoadMemory(PlayerC *p, const UINT8 *data, UINT32 length) {
    return PlayerC_LoadData(p, MemoryLoader_Init(data, length));
}

UINT8 PlayerC_Start(PlayerC *p) {
    return p->player->Start();
}

UINT32 PlayerC_Render(PlayerC *p, UINT32 bufSize, void *data) {
    return p->player->Render(bufSize, data);
}

UINT8 PlayerC_FadeOut(PlayerC *p) {
    return p->player->FadeOut();
}

UINT8 PlayerC_Stop(PlayerC *p) {
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