local has_ffi, ffi = pcall(require, "ffi")
if not has_ffi then
    return false
end

local vgmplayers = {
    "vgm-player",
    "libvgm-player.so"
}
local ok, vgmplayer
for _, gme in ipairs(vgmplayers) do
    ok, vgmplayer = pcall(ffi.load, gme)
    if ok then
        break
    end
end
if not ok then
    print(vgmplayer)
    return false
end

ffi.cdef[[
typedef struct PlayerA PlayerA;
typedef struct DATA_LOADER DATA_LOADER;

typedef struct PlayerC {
    PlayerA *player;
    DATA_LOADER *loader;
} PlayerC;

PlayerC* PlayerC_NewVGM();
uint8_t PlayerC_SetOutputSettings(PlayerC *p, uint32_t smplRate, uint8_t channels, uint8_t smplBits, uint32_t smplBufferLen);
void PlayerC_SetLoopCount(PlayerC *p, uint32_t loopCount);

uint8_t PlayerC_LoadFile(PlayerC *p, const char *filename);
uint8_t PlayerC_LoadMemory(PlayerC *p, const uint8_t *data, uint32_t length);

uint8_t PlayerC_Start(PlayerC *p);
uint32_t PlayerC_Render(PlayerC *p, uint32_t bufSize, void *data);
uint8_t PlayerC_FadeOut(PlayerC *p);
uint8_t PlayerC_Stop(PlayerC *p);

void PlayerC_delete(PlayerC *p);
]]

ffi.metatype("PlayerC", {
    __gc = function(p)
        vgmplayer.PlayerC_delete(p)
    end
})

return vgmplayer