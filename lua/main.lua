local VGMPlayer = require("VGMPlayer")
local vgm, err

function love.load(args)
    local file=args[1]
    if file then
        vgm, err = VGMPlayer.new(file)
        if vgm then
            vgm:play()
        else
            error(err)
        end
    else
        error("No file given")
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