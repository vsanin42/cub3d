#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"

int ft_atoi(const char *str);

typedef struct s_map 
{
	char **grid;
	int height;
} t_map;

typedef struct s_game
{
	t_map *map;
	char *textures[5];
	int floor_color[3];
	int ceiling_color[3];
	int flag_n;
	int flag_e;
	int flag_w;
	int flag_s;
	int flag_f;
	int flag_c;
} t_game;

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char *ft_strdup_without_newline(const char *str)
{
    size_t len = ft_strlen(str);

    /* Если последний символ — '\n', уменьшаем длину на 1 */
    if (len > 0 && str[len - 1] == '\n')
        len--;

    char *dup = malloc(len + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, str, len);
    dup[len] = '\0';
    return dup;
}

int add_map_line(t_map *map, const char *line)
{
    char **new_grid;
    int i;

    new_grid = malloc(sizeof(char *) * (map->height + 2));
    if (!new_grid)
    {
        printf("Memory allocation failed.\n");
        return (0);
    }
    i = 0;
    while (i < map->height)
    {
        new_grid[i] = map->grid[i];
        i++;
    }
    new_grid[map->height] = ft_strdup_without_newline(line);
    if (!new_grid[map->height])
    {
        printf("String duplication failed.\n");
        return (0);
    }
    new_grid[map->height + 1] = NULL;
    free(map->grid);
    map->grid = new_grid;
    map->height++;
    return (1);
}


void free_map(t_map *map) {
    if (!map) return;
    for (int i = 0; i < map->height; i++) {
        free(map->grid[i]);  // Освобождаем каждую строку карты
    }
    free(map->grid);  // Освобождаем массив указателей
    free(map);        // Освобождаем структуру карты
}

void free_game(t_game *game) {
    for (int i = 0; i < 4; i++) {
        if (game->textures[i]) {
            free(game->textures[i]);  // Освобождаем текстуры
        }
    }
    if (game->map) {
        free_map(game->map);  // Освобождаем карту
    }
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

// Проверка допустимых символов
int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

// Проверяет, является ли символ "вне границ" карты или пробелом
int is_out_of_bounds(char **map, int x, int y, int rows)
{
    return (x < 0 || y < 0 || x >= rows || y >= (int)ft_strlen(map[x]) || map[x][y] == ' ');
}

// Flood-fill для проверки замкнутости карты
int flood_fill(char **map, int x, int y, int rows, int **visited)
{
    if (is_out_of_bounds(map, x, y, rows) || map[x][y] == '1' || visited[x][y])
        return (1);

    visited[x][y] = 1;

    // Проверка "дырок" вокруг проходных символов
    if (map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
    {
        if (is_out_of_bounds(map, x - 1, y, rows) ||
            is_out_of_bounds(map, x + 1, y, rows) ||
            is_out_of_bounds(map, x, y - 1, rows) ||
            is_out_of_bounds(map, x, y + 1, rows))
        {
            return (0);
        }
    }

    // Рекурсивный обход всех направлений
    return flood_fill(map, x - 1, y, rows, visited) &&
           flood_fill(map, x + 1, y, rows, visited) &&
           flood_fill(map, x, y - 1, rows, visited) &&
           flood_fill(map, x, y + 1, rows, visited);
}

int check_walls(char **map, int rows)
{
    // Инициализация массива посещений
    int **visited = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        visited[i] = (int *)ft_calloc(ft_strlen(map[i]) + 1, sizeof(int));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < (int)ft_strlen(map[i]); j++)
        {
            char c = map[i][j];

            // Проверка допустимых символов
            if (!is_valid_char(c))
            {
                printf("Недопустимый символ на позиции [%d, %d] |%c|\n", i, j, c);
                return 0;
            }

            // Проверка замкнутости пространства с помощью flood fill
            if ((c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W') && !visited[i][j])
            {
                if (!flood_fill(map, i, j, rows, visited))
                {
                    printf("Открытая область обнаружена на позиции [%d, %d]\n", i, j);
                    return 0;
                }
            }
        }
    }

    // Освобождение памяти
    for (int i = 0; i < rows; i++)
    {
        free(visited[i]);
    }
    free(visited);

    return 1;
}


void print_colors(t_game *game) {
    // Выводим цвета пола и потолка
    printf("Floor Color (RGB): %d, %d, %d\n", game->floor_color[0], game->floor_color[1], game->floor_color[2]);
    printf("Ceiling Color (RGB): %d, %d, %d\n", game->ceiling_color[0], game->ceiling_color[1], game->ceiling_color[2]);
}

void print_textures(t_game *game) {
    // Выводим текстуры
    printf("Textures:\n");
    printf("North Texture: %s\n", game->textures[0]);
    printf("South Texture: %s\n", game->textures[1]);
    printf("West Texture: %s\n", game->textures[2]);
    printf("East Texture: %s\n", game->textures[3]);
}

void print_map(t_game *game) {
    // Выводим карту
    printf("Map:\n");
    for (int i = 0; i < game->map->height; i++) {
        for (int j = 0; j < ft_strlen(game->map->grid[i]); j++) {
            putchar(game->map->grid[i][j]);  // Выводим символ из карты
        }
        putchar('\n');  // Переходим на новую строку после каждой строки карты
    }
}

/*int	add_map_line(t_map *map, const char *line)
{
    char	**new_grid;
    int		i;
    
    new_grid = malloc(sizeof(char *) * (map->height + 1));
    if (!new_grid)
    {
        printf("Memory allocation failed.\n");
        return (0);
    }
    i = 0;
    while (i < map->height)
    {
        new_grid[i] = map->grid[i];
	i++;
    }
    new_grid[map->height] = ft_strdup(line);
    if (!new_grid[map->height])
    {
        printf("String duplication failed.\n");
        return (0);
    }
    free(map->grid);
    map->grid = new_grid;
    map->height++;
    return (1);
} */

void	*ft_memset(void *s, int c, size_t n)
{
	char	*s1;

	s1 = (char *)s;
	while (n > 0)
	{
		s1[n - 1] = c;
		n--;
	}
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	if (n == i)
		return (0);
	return (s1[i] - s2[i]);
}

int	err(char *text_err)
{
	printf("%s\n", text_err);
	return (-1);
}

int	check_format(char *argv)
{
	int	i;

	i = 0;
	if (ft_strlen(argv) <= 4)
		return (0);
	while (argv[i])
	{
		if (!((argv[i] >= '0' && argv[i] <= '9') || (argv[i] >= 'a' && argv[i] <= 'z') || (argv[i] >= 'A' && argv[i] <= 'Z') || argv[i] == '.' 
				|| argv[i] == '-' || argv[i] == '_' || argv[i] == '/'))
			return (0);
		if (argv[i + 1] != 0 && argv[i] == 'b' && argv[i - 1] == 'u' &&
			argv[i - 2] == 'c' && argv[i - 3] == '.')
			return (0);
		if (!argv[i + 1] && argv[i] == 'b' && argv[i - 1] == 'u' &&
			argv[i - 2] == 'c' && argv[i - 3] == '.')
			return (1);
		i++;
	}
	return (0);
}

void	flag_init(t_game *game)
{
	game->flag_n = 0;
	game->flag_e = 0;
	game->flag_w = 0;
	game->flag_s = 0;
	game->flag_f = 0;
	game->flag_c = 0;
}

int	save_color_floor(char *line, t_game *game)
{
	int	i;
	int	j;
	int	counter;

	i = 2;
	j = 0;
	counter = 0;
	while (line[i] && line[i] != '\n')
	{
		printf("%c", line[i]);
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			i++;
		printf("%c!", line[i]);
		if (line[i] <= '9' && line[i] >= '0')
		{
			game->floor_color[j] = ft_atoi(&line[i]);
			while (line[i] <= '9' && line[i] >= '0')
				i++;
			j++;
		}
		if (line[i] == '\n')
			break ;
		if (line[i] == ',')
			counter++;
		else
			return (0);
		i++;
	}
	printf("cdafef");
	if (game->floor_color[0] > 255 || game->floor_color[1] > 255 || game->floor_color[2] > 255 || counter != 2 || j != 3)
		return (0);
	return (1);
}

int skip_whitespace(const char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
		i++;
	return (i);
}

int	save_color(char *line, t_game *game)
{
	int	i;
	int	j;
	int	counter;

	i = 2;
	j = 0;
	counter = 0;
	while (line[i] && line[i] != '\n')
	{
		printf("%c", line[i]);
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			i++;
		if (line[i] <= '9' && line[i] >= '0')
		{
			game->ceiling_color[j] = ft_atoi(&line[i]);
			while (line[i] <= '9' && line[i] >= '0')
				i++;
			j++;
		}
		if (line[i] == '\n')
			break ;
		if (line[i] == ',')
			counter++;
		else
			return (0);
		i++;
	}
	if (game->ceiling_color[0] > 255 || game->ceiling_color[1] > 255 || game->ceiling_color[2] > 255 || counter != 2 || j != 3)
		return (0);
	return (1);
}

int	check_player(char **grid)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (grid[i])
	{
		j = 0;
		while(grid[i][j])
		{
			if (grid[i][j] == 'S' || grid[i][j] == 'W' || grid[i][j] == 'N' || grid[i][j] == 'E')
				flag++;
			j++;
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	my_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

void	trim_spaces(char *str)
{
	char	*end;
	
	while (my_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return ;
	end = str + ft_strlen(str) - 1;
	while (end > str && my_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
}

int	edit_paths(char **textures)
{
	int	i;
	int	len;
	
	i = 0;
	if (!textures)
		return (0);
	while (textures[i])
	{
		trim_spaces(textures[i]);
		len = ft_strlen(textures[i]);
		if (len < 5 || textures[i][len - 1] != 'm' || textures[i][len - 2] != 'p' || textures[i][len - 3] != 'x' || textures[i][len - 4] != '.')
			return (0);
		i++;
	}
	return (1);
}

int	valid_map(char *argv, t_game *game)
{
	int		fd;
	char	*line;
	t_map	*map;
	int	map_flag;
	int	offset;

	if (!check_format(argv))
		return (0);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (0);
	map = malloc(sizeof(t_map));
	if (!map)
		return (0);
	map->grid = NULL;
	map->height = 0;
	game->map = map;
	flag_init(game);
	map_flag = 0;
	game->textures[4] = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		offset = skip_whitespace(line);
		printf("%d", offset);
		if (ft_strncmp(line + offset, "NO", 2) == 0 && line[offset + 2] == ' ')
		{
			game->textures[0] = ft_strdup(line + 3 + offset);
			game->flag_n++;
		}
		else if (ft_strncmp(line + offset, "SO", 2) == 0 && line[offset + 2] == ' ')
		{
			game->textures[1] = ft_strdup(line + 3 + offset);
			game->flag_s++;
		}
		else if (ft_strncmp(line + offset, "WE", 2) == 0 && line[offset + 2] == ' ')
		{
			game->textures[2] = ft_strdup(line + 3 + offset);
			game->flag_w++;
		}
		else if (ft_strncmp(line + offset, "EA", 2) == 0 && line[offset + 2] == ' ')
		{
			game->textures[3] = ft_strdup(line + 3 + offset);
			game->flag_e++;
		}
		else if (ft_strncmp(line + offset, "F ", 2) == 0)
		{
			 if (!save_color_floor(line + offset, game))
			 {
				 printf("fffffffffffffffffffffffffffffffffffffffffffff");
				 free(line);
				 return (0);
			 }
			game->flag_f++;
		}
		else if (ft_strncmp(line + offset, "C ", 2) == 0)
		{
			if (!save_color(line + offset, game))
			{
				printf("fffffffffffffffffffffffffffffffffffffffffffff");
				free(line);
				return (0);
			}
			game->flag_c++;
		}
		else if (map_flag == -1 && (line[offset] > 32 && line[offset] < 127))
		{
			free(line);
			return (0);
		}
		else if (line[offset] == '1')
		{
			map_flag = 1;
			if (!add_map_line(map, line))
			{
				free(line);
				return (0);
			}
			if (game->flag_n != 1 || game->flag_w != 1 || game->flag_e != 1 || game->flag_s != 1 || game->flag_f != 1 || game->flag_c != 1)
				return (0);
		}
		else if (map_flag == 1 && line[offset] == '\n')
			map_flag = -1;
		else if (line[offset] == '\n') ;
		else
		{
			free(line);
			return (0);
		}
		free(line);
	}
	close(fd);
	if (game->flag_n != 1 || game->flag_w != 1 || game->flag_e != 1 || game->flag_s != 1 || game->flag_f != 1 || game->flag_c != 1 || map_flag == 0)
		return (0);
	else
		printf("OKKKK\n");
	if (map->height < 3)
		return (0);
	if (!check_player(map->grid))
		return (0);
	if (!check_walls(map->grid, map->height))
		return (0);
	if (!edit_paths(game->textures))
		return (0);
	print_textures(game);
	printf("\n");
	print_colors(game);
	printf("\n");
	print_map(game);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	
	ft_memset(&game, 0, sizeof(t_game));
	if (argc == 2)
	{
		if (!valid_map(argv[1], &game))
		{
			free_game(&game);
			return (err("Error: not valid map!"));
		}
		free_game(&game);
	}
	else
		return (err("Error: too few or many arguments!"));
}
