
# cub3d
by [@vsanin42](https://www.github.com/vsanin42) & [@olgalomova](https://github.com/olgalomova)

3D visualization from the inside of a 2D maze using the raycasting technology for 42 School, written in C.

Raycasting was first applied in the development of a classic videogame [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) which pioneered and popularized the first-person shooter genre. Sometimes referred to as "2.5D", this technique rendered 2D textures in a way that resembled the 3D view, making it seem like the 3rd (height) dimension was present.

For the purposes of the 42 project it was mandatory to use the MinilibX graphical library for rendering the visuals. Each ray casted using the DDA algorithm provided information about the distance from the player to the wall, its side and the position on the texture that the ray landed on. This information was used to create a correlation between the window pixels and the texture pixels, as well as the height of the wall to be drawn. This allowed drawing the right part of the texture on a vertical pixel column of the window, along with the floor and ceiling. Once this process has been repeated for the entire width of the window and the image buffer pixels were filled with the correct values, the image was pushed to the window, rendering one frame.

To keep the movement smooth, the MinilibX is constantly running a loop, rendering the frames and simultaneously waiting for any changes in the configurations caused by the mouse and key press/release events.

## Use

Compilation:
```bash
  make
```

Launch the executable:
```bash
  ./cub3d [map]
```

A valid map file must end with ```.cub``` and contain the following elements (in any order with the exception of the map being the last element):
- ```NO```: path to the north texture.
- ```SO```: path to the south texture.
- ```WE```: path to the west texture.
- ```EA```: path to the east texture.
- ```DO```: path to the door texture. *(optional)*
- ```F```: RGB value of the floor color.
- ```C```: RGB value of the ceiling color.
- Map comprised of ```1``` for the wall tiles and ```0``` for the floor tiles, with a single letter (```NSWE```) defining the starting position and view direction.

All valid maps can be found in the ```maps/good/``` folder.

## Controls
- Use ```WASD``` keys to move around the maze.
- Use left and right arrow keys to rotate the camera angle.
- Use mouse (within the window) to rotate the camera angle. *(optional)*
- Use ```Esc``` or cross in the corner to close the window.
- Refer to the minimap in the upper left corner for assistance with the navigation in the maze.
- Approach the door to automatically open it; the door closes behind you once you're out of range.
