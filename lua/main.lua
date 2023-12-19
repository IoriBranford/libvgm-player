local VGMPlayer = require("VGMPlayer")
local vgm

function love.load(args)
    local file=args[1]
    if file then
        vgm = VGMPlayer.new(file)
        vgm:play()
    else
        love.event.quit()
    end
end

function love.keypressed(k)
    if k=="f" then
        vgm:fade(6)
    end
end

function love.quit()
    if vgm then
        vgm:stop()
    end
    love.audio.stop()
end