return function(filedata, track, buffersamples, rate, input, volume)
    local has_ffi, ffi = pcall(require, "ffi")
    if not has_ffi then
        return
    end
    local libvgm = require "libvgm.ffi"
    if not libvgm then
        return
    end

    local render = libvgm.PlayerC_Render

    love.sound = require "love.sound"
    love.audio = require "love.audio"
    love.timer = require "love.timer"

    local sleep = love.timer.sleep

    local sounddata = love.sound.newSoundData(buffersamples, rate)
    local soundbytes = sounddata:getSize()
    local pointer = sounddata:getFFIPointer()
    local source = love.audio.newQueueableSource(rate, 16, 2)
    source:setVolume(volume or 1)

    local musicemu = libvgm.PlayerC_NewVGM()
    libvgm.PlayerC_SetOutputSettings(musicemu, rate, 2, 16, buffersamples)
    libvgm.PlayerC_LoadMemory(musicemu, filedata:getFFIPointer(), filedata:getSize())
    musicemu = musicemu[0]

    local function queueBuffers(n)
        n = math.min(n, source:getFreeBufferCount())
        for _ = 1, n do
            render(musicemu, soundbytes, pointer)
            source:queue(sounddata)
        end
    end

    libvgm.PlayerC_Start(musicemu)
    queueBuffers(source:getFreeBufferCount())
    source:play()

    local paused = false
    while true do
        local cmd = input:pop()
        if cmd == "play" then
            paused = false
        elseif cmd == "pause" then
            paused = true
        elseif cmd == "stop" then
            break
        elseif cmd == "volume" then
            volume = input:demand()
            source:setVolume(volume)
        elseif cmd == "fade" then
            libvgm.PlayerC_FadeOut()
        end

        queueBuffers(1)
        if paused then
            source:pause()
        else
            source:play()
        end
        sleep(0.001953125)
    end

    source:stop()
end