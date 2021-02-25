# Miniclip Task

## Game
The objective of the game is to achive the maximium of points. These points can be achived by clicking in a group of blocks, the larger the group more points will be obtained, these increase exponencialy.
If a combo is superior to `BOMBSPAWN` a bomb will spawn. Three types of bombs are available, a bomb of radius `BOMBEFFECT` that destroys all block under this radius. A row bomb and a column bomb, like the name sugests one clear an entire row, and the other an entire collumn. At the end of the game a scoreboard is displayed showing the number of blocks destroy of each color, alongside the time that was taken and the final score.

It is possibel to pause the game either with by pressing `p` or `esc`.

There number of levels is infinite, and the game will only end if a block reaches the end line.

## Assets
Folder containing all the images and sounds use to make this task. All the sounds were downloaded. All the images except for the background were created in [PixelArt](https://www.pixilart.com/).

## Dependencies:
The folder dependencies contain all the SDL libs used:
* SDL2-2.0.14 main SDL
* SDL2_image-2.0.5 to convert images to textures
* SDL2_ttf-2.0.15 to convert text to textures
* SDL2_mixer-2.0.4 for music/sounds

## Files:
### Configurations
Under `include` there is a file called `Configurations.h` this is where all the configurations for the game and render are declared
### Main
`Main.cpp` cicle to have game running until the boolean `isGameRunning` of `Game.cpp` turns `False`.
### Game
`Game.cpp` is the file responsible for the gameplay of the game.
### Render Manager
`RenderManger.cpp` is the file responsible to render all the textures and text for the game.
### Music Manager
`RenderManger.cpp` is the file responsible for the music and sound effects (chunks)
### Texture Manager
`RenderManger.cpp` is the file responsible for all the texture used, being these generated from images or from text.

More detail information about each function is inside the source code and headers.