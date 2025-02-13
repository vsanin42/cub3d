# cub3d

12.02 - V

did some figuring out what's going on, still checking things, will be adding raycasting math soon. 

- restructure: added specific folders (for maps, sources, etc), added gnl to libft, some renames, header has functions organized by file not to lose them + easier norm management when rearranging.

- had an error when including mlx's header because it's a submodule. maybe it's ok when compilig but i don't know how to do it properly xd.. so it's copied there in full inside the mlx folder.

- situation: in main, 3 mallocs are called one after another, if any of them fails - free_game. let's say that textures are alloced fine, but malloc fails on allocating floor color - we go into free_game. however, in free_game, check "if textures[i]" results into undefined behaviour, potentially freeing garbage values. because char **textures has been alloced, but not its individual members and we can't check if they're null. i also think memset zeroes only the game members, not what's inside those members. i hope you get what i'm saying..

- solution: alloc all at once, instantly check for malloc fails and free all 3 - we can do it safely since we used memset above and all game members are either alloced (freeable) or null (freeing doesn't do anything so it's safe). then thanks to saved space we can set textures[i], etc.. to null or 0 in the same function - alloc_and_nullify. we'll also need more space in main for mlx functions, so that's another plus. btw thanks for showing me memset, i've never used it before :D cool thing. i know this is probably overkill and we 99% won't run into an issue like this irl, but i'm trying to polish it now so we don't run into issues related to this later.

- **TODO**: may need to replace gnl in my libft with your gnl because of buffer issues, i'll test it. for my gnl if gnl returned mid-file before finishing it whole, the buffer would be stuck, so i added -1 option to free the buffer afterwards. if it causes problems will roll back to your gnl.

- if map name is abc.cub.cub it will be considered invalid - correct? i agree logically because we never see such files but theoretically it's possible to have such names, extension = everything after the last dot. probably doesn't matter but i'll adjust it.

- when checking map name, it's accessing i - 1, i - 2, i - 3 - what if the name is like b.cub? or any name really - the first index is being checked, at i = 0 while checking "b" it will check for i - 1 (i == -1) and probably cause segfault. i'd replace one of those checks with checking if previous indexes exist, will test too. (did it with strncmp)

- **question:** is offset/skip_whitespace only for spaces + \t + \r and not \n? so just within one line?

- added int max overflow check in atoi just in case. if overflow, atoi returns -1.

- added a small rgb value check 0 to 255 which also excludes negative values. this is longggggg bzbzbzbzbz