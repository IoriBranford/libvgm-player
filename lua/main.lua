local libvgm = require("libvgm")
function love.load(args)
    local file=args[1]
    if file then
        libvgm.new(file):play()
    else
        love.event.quit()
    end
end