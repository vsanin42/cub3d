# cub3d

12.02 - V

did some figuring out what's going on, still checking things, will be adding raycasting math soon. 

- restructure: added specific folders (for maps, sources, etc), added gnl to libft, some renames, header has functions organized by file not to lose them + easier norm management when rearranging.

- had an error when including mlx's header because it's a submodule. maybe it's ok when compilig but i don't know how to do it properly xd.. so it's copied there in full inside the mlx folder.

- situation: in main, 3 mallocs are called one after another, if any of them fails - free_game. let's say that textures are alloced fine, but malloc fails on allocating floor color - we go into free_game. however, in free_game, check "if textures[i]" results into undefined behaviour, potentially freeing garbage values. because char **textures has been alloced, but not its individual members and we can't check if they're null. i also think memset zeroes only the game members, not what's inside those members. i hope you get what i'm saying..

- solution: alloc all at once, instantly check for malloc fails and free all 3 - we can do it safely since we used memset above and all game members are either alloced (freeable) or null (freeing doesn't do anything so it's safe). then thanks to saved space we can set textures[i], etc.. to null or 0 in the same function - alloc_and_nullify. we'll also need more space in main for mlx functions, so that's another plus. btw thanks for showing me memset, i've never used it before :D cool thing. i know this is probably overkill and we 99% won't run into an issue like this irl, but i'm trying to polish it now so we don't run into issues related to this later.

- for my gnl if gnl returned mid-file before finishing it whole, the buffer would be stuck, so i added -1 option to free the buffer afterwards.

- if map name is abc.cub.cub it will be considered invalid - correct? i agree logically because we never see such files but theoretically it's possible to have such names, extension = everything after the last dot. probably doesn't matter but i'll adjust it.

- when checking map name, it's accessing i - 1, i - 2, i - 3 - what if the name is like b.cub? or any name really - the first index is being checked, at i = 0 while checking "b" it will check for i - 1 (i == -1) and probably cause segfault. i'd replace one of those checks with checking if previous indexes exist, will test too. (did it with strncmp)

- **question:** is offset/skip_whitespace only for spaces + \t + \r and not \n? so just within one line?

- added int max overflow check in atoi just in case. if overflow, atoi returns -1.

- added a small rgb value check 0 to 255 which also excludes negative values. this is longggggg bzbzbzbzbz

13.02 - V

done checking up to game start, math next

- if_line_1: swapped flag check with line allocation - if textures/floor/ceiling wasn't allocated, return and don't allocate the grid and grid lines.

- valid_map: after close(fd), there's a check for nswefc flags + map flag. if map_flag == 0, map wasn't found/something went wrong, this is ok. what if it's -1 or 1 and something happened mid parsing? just making sure the check is enough, i think it looks right.

- init_map_data: why "+ 1" in "ft_strlen(map[i]) + 1"? doesn't that add an extra column?

- changed free_map_data: we don't want to free all visited[i] rows from 0 to rows if it failed in the middle, must only free up the last allocated index.

- is_valid_char: is checking for spaces only enough? maybe tabs/\r, others? idk probably doesn't matter

- trim_spaces: made it return the updates pointer, as a void function the pointer shift was local and texture stayed the same.

- UPDATE: trim_spaces replaced with ft_strtrim. original version didn't change the string, my updated version messed up the pointer (we'd have issues when freeing because it's no longer the same pointer, doesn't point to the same place that was allocated initially). ft_strtrim trims and allocates a new trimmed string, just had to free the old one in the wrapper. set up error messages accordingly because it could be null or empty string. should be ok now. + textures[i] has the output of gnl, which always ends in a newline, so right after newline is \0. but still gotta check for things like: "NO   *spaces*    \n\0"

14.02 - V

i in fact wasn't done checking :D now validation should be pretty robust, just double check later.

- added srcs subfolders, everything works after my changes too.

- what is forbidden.cub supposed to test? assuming it's for file permissions, i added another check there for 1. files with no permissions 2. non-existent files (wrong names) based on error number (errno), all works fine. for xpm paths too.

- improved messages depending on what failed during validation

- slightly changed err() to use write instead of printf and print to stderr instead of stdout

- all bad maps verified with new messages, some may be a bit off - test again later to be 100% sure. goods and weirds also tested, all good:)

- test_map_hole.cub moved to bad, open unguarded space - we can handle it how we want according to subject.

- to test textures_forbidden.cub + texture_forbidden.xpm and forbidden.cub, reset rights with chmod to all 0 or smth

---------------------------------

https://lodev.org/cgtutor/raycasting.html main tutorial i'm following, ref.cpp is from there.
https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf this has some good pictures to visualize geometry and direction of vectors
https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx useful for drawing pixels later

- check_player: when we find NSWE, we also update the starting position in the game struct with its coordinates + the orientation with its value to know which way we're facing and how to define the starting vector. also define a camera plane perpendicular to the direction vector. the best way to understand it is to visualize it, links above are good.

15.02 - V

working on raycaster math - everything is documented in the functions.

possible issues: despite trying to understand the coordinate system, i'm not sure that things won't be flipped, if any related issue arises - it's likely because of coordinates. so try to flip some x/y values until it works (solid plan :D).

current weak points that could be problematic:

- map_check.c set_start_pos - may need to swap/completely remove negative values of 0.66.
- related to that is the calculation of ray_dir values in set_ray_variables.
- dda algorithm - we check grid[y][x], the reference has it the other way so idk what he meant by which coordinate.

16.02 - V

raycasting math is +- complete. we now have almost all info we need to draw vertical lines.
TODO: textures - find something (think of size) convert to xpm, save somewhere, ...
TODO: mlx - work with images and all those functions to draw things.

next goal: have at least one static frame render.

18.02 - V

doing more research on how to draw everything.

- added TRGB conversion functions to create colors as integers from each TRGB component and getting them from the texture pixels.
- loading + destroying textures (no textures yet), figuring out which side (NSWE) was hit by the ray
- some extra variables for raycasting to tell 1. where on the GRID SQUARE the ray hit the  wall (0 to 1 - left to right value) and 2. where on the TEXTURE that is relative to its width. now we know which stripe of the texture we need to use to draw under each ray.