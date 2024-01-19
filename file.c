/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:23:39 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 16:19:58 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

int	is_rectangular(t_game *data)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	j = 0;
	k = ft_strlen(data->map[i]);
	while (++i < ft_strstrlen(data->map))
	{
		while (j < ft_strlen(data->map[i]))
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'C' && data->map[i][j] != 'E'
				&& data->map[i][j] != 'P' && data->map[i][j] != 'X')
				return (0);
			j++;
		}
		j = 0;
		if (k != ft_strlen(data->map[i]) || i == ft_strstrlen(data->map) - 1)
		{
			if (i == ft_strstrlen(data->map) - 1 && (k
					- 1 == ft_strlen(data->map[i])))
				return (1);
			else
				return (0);
		}
	}
	return (1);
}

int	check_border_wall(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(data->map[0]))
	{
		if (data->map[0][i] != '1')
			return (0);
		i++;
	}
	while (data->map[j])
	{
		if (data->map[j][0] != '1')
			return (0);
		j++;
	}
	i = 0;
	while (i < ft_strlen(data->map[0]))
	{
		if (data->map[j - 1][i] != '1')
			return (0);
		i++;
	}
	j = 0;
	while (data->map[j])
	{
		if (data->map[j][ft_strlen(data->map[0]) - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	is_solvable(t_game *data)
{
	t_point	pos;
	int		i;
	int		j;

	pos = find_player(data);
	// check if there is a void around the player
	i = pos.y / 50;
	j = pos.x / 50;
	if (data->map[i - 1][j] == '0' || data->map[i + 1][j] == '0'
		|| data->map[i][j - 1] == '0' || data->map[i][j + 1] == '0')
		return (1);
	if (data->map[i - 1][j] == 'C' || data->map[i + 1][j] == 'C'
		|| data->map[i][j - 1] == 'C' || data->map[i][j + 1] == 'C')
		return (1);
	if (data->map[i - 1][j] == 'X' || data->map[i + 1][j] == 'X'
		|| data->map[i][j - 1] == 'X' || data->map[i][j + 1] == 'X')
		return (1);
	return (0);
}

void	check_map(t_game *data)
{
	if (is_rectangular(data) == 0)
	{
		ft_printf("Error\n");
		exit(0);
	}
	if (data->map == NULL)
	{
		ft_printf("Error\n");
		exit(0);
	}
	if (check_border_wall(data) == 0)
	{
		ft_printf("Error\n");
		exit(0);
	}
	if (is_solvable(data) == 0)
	{
		ft_printf("Error\n");
		exit(0);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:52:19 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 19:03:46 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

int key_press(int keycode, t_game *game) {
    if (keycode == KEY_ESC)
        safeexit((void *)game);
    if (keycode == KEY_W)
        game->player->accel.y = -15;
    if (keycode == KEY_A)
        game->player->accel.x = -15;
    if (keycode == KEY_S)
        game->player->accel.y = 15;
    if (keycode == KEY_D)
        game->player->accel.x = 15;
    if (keycode == KEY_SPACE) {
        game->player->accel.x = 0;
        game->player->accel.y = 0;
    }
    return (0);
}

int key_release(int keycode, t_game *game) {
    // Reset acceleration on key release
    if (keycode == KEY_W || keycode == KEY_S)
        game->player->accel.y = 0;
    if (keycode == KEY_A || keycode == KEY_D)
        game->player->accel.x = 0;
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:48:08 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 18:02:11 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void    free_imgs(t_game *game)
{
    mlx_destroy_image(game->mlx, game->player_img);
    // mlx_destroy_image(game->mlx, game->playerm_img);
    // mlx_destroy_image(game->mlx, game->wall_img);
    // mlx_destroy_image(game->mlx, game->enemy_img);
    // mlx_destroy_image(game->mlx, game->enemym_img);
    // mlx_destroy_image(game->mlx, game->exit_img);
    // mlx_destroy_image(game->mlx, game->collectible_img);
    mlx_destroy_image(game->mlx, game->background_img);
}

int    safeexit(void *data)
{
    t_game    *game;

    game = (t_game *)data;
    free_imgs(game);
    mlx_clear_window(game->mlx, game->win);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    arena_destroy(game->arena);
    exit(0);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:37:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 16:20:28 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void	ft_putchar(char c)
{
	ssize_t	bytes_written;

	bytes_written = write(1, &c, 1);
	if (bytes_written == -1)
		perror("write failed");
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return ;
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i - 1);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i] || str[i][0] != '\n')
		i++;
	return (i);
}

void	ft_putnbr(int nb)
{
	ssize_t	bytes_written;

	bytes_written = 0;
	if (nb == -2147483648)
	{
		bytes_written = write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		bytes_written = write(1, "-", 1);
		nb = -nb;
	}
	if (bytes_written == -1)
		perror("write failed");
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
	return ;
}

void	ft_putnbr_base(unsigned int nb, char *base, unsigned int size)
{
	if (nb >= size)
		ft_putnbr_base(nb / size, base, size);
	ft_putchar(base[nb % size]);
	return ;
}

void	ft_pourcent(const char *src, va_list list, int i)
{
	if (src[i] == 's')
		ft_putstr(va_arg(list, char *));
	else if (src[i] == 'd')
		ft_putnbr(va_arg(list, int));
	return ;
}

int	ft_printf(const char *src, ...)
{
	int		i;
	va_list	list;

	i = -1;
	va_start(list, src);
	while (src[++i])
	{
		if (src[i] == '%')
			ft_pourcent(src, list, ++i);
		else
			ft_putchar(src[i]);
	}
	va_end(list);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:17:07 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 18:43:10 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void	init_imgs(t_game *game)
{
	int	width;
	int	height;

	game->player_img = mlx_xpm_file_to_image(game->mlx, "./imgs/player2.xpm",
		&width, &height);
    game->playerm_img = mlx_xpm_file_to_image(game->mlx, "./imgs/playerm.xpm",
		&width, &height);
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "./imgs/wall.xpm",
        &width, &height);
    game->enemy_img = mlx_xpm_file_to_image(game->mlx, "./imgs/enemy.xpm",
        &width, &height);
    game->enemym_img = mlx_xpm_file_to_image(game->mlx, "./imgs/enemym.xpm",
        &width, &height);
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "./imgs/exit.xpm",
        &width, &height);
    game->collectible_img = mlx_xpm_file_to_image(game->mlx, "./imgs/collect.xpm",
        &width, &height);
    game->background_img = mlx_xpm_file_to_image(game->mlx, "./imgs/void.xpm",
        &width, &height);
}

t_point find_player(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == 'P')
            {
                game->map[i][j] = '0';
                return ((t_point){j * 50, i * 50});
            }
            j++;
        }
        i++;
    }
    return ((t_point){0, 0});
}

void    init_entities(t_game *game)
{
    game->player = (t_player *)arena_alloc(game->arena, sizeof(t_player));
    game->player->ent_type = PLAYER;
    game->player->pos = find_player(game);
    game->player->speed.x = 0;
    game->player->speed.y = 0;
    game->player->accel.x = 0;
    game->player->accel.y = 0;
    game->player->mass = 1;
}

float   get_time(t_game *game)
{
    struct timeval  current_time;
    float           time;

    gettimeofday(&current_time, NULL);
    time = (current_time.tv_sec - game->last_frame.tv_sec) * 1000.0;
    time += (current_time.tv_usec - game->last_frame.tv_usec) / 1000.0;
    return (time);
}

t_game	*game_init(int argc, char **argv)
{
	t_arena	*arena;
	t_game	*game;

	arena = arena_init(1000000);
	game = (t_game *)arena_alloc(arena, sizeof(t_game));
	if (!game)
		return (NULL);
	game->arena = arena;
	game->mlx = mlx_init();
    game->nb_map = 2;
	create_file_name(game, argc, argv);
	parse_map(game);
	game->win = mlx_new_window(game->mlx, game->map_width * 50, game->map_height * 50, "so_long_gravity");
    game->gravity = (t_accel *)arena_alloc(game->arena, sizeof(t_accel));
    game->gravity->x = 0;
    game->gravity->y = 0;
    gettimeofday(&game->last_frame, NULL);
    game->time = get_time(game);
	// check_map(game);
    init_imgs(game);
    init_entities(game);
	return (game);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:35:38 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 19:02:40 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void physic(t_game *game) {
    // Update speed based on acceleration
    game->player->speed.x += game->player->accel.x;
    game->player->speed.y += game->player->accel.y;

    // Check collisions with walls
    check_collisions_walls(game);

    // Speed limits
    game->player->speed.x = fmin(fmax(game->player->speed.x, -300), 300);
    game->player->speed.y = fmin(fmax(game->player->speed.y, -300), 300);

    // Update player position
    game->player->pos.x += game->player->speed.x;
    game->player->pos.y += game->player->speed.y;

    // Boundary checks
    game->player->pos.x = fmin(fmax(game->player->pos.x, 0), game->map_width * 50 - 30);
    game->player->pos.y = fmin(fmax(game->player->pos.y, 0), game->map_height * 50 - 30);
}


void	refresh_window(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mlx_clear_window(game->mlx, game->win);
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img, j * 50, i * 50);
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, j * 50, i * 50);
			else if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit_img, j * 50, i * 50);
			else if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->background_img, j * 50, i * 50);
			else if (game->map[i][j] == 'X')
				mlx_put_image_to_window(game->mlx, game->win, game->enemy_img, j * 50, i * 50);
			else if (game->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->background_img, j * 50, i * 50);
			j++;
		}
		i++;
		j = 0;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->player_img, game->player->pos.x, game->player->pos.y);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (get_time(game) > 2)
	{
		gettimeofday(&game->last_frame, NULL);
		//gravity
		physic(game);
		if (game->player->speed.x != 0 || game->player->speed.y != 0)
		{
			refresh_window(game);
			mlx_do_sync(game->mlx);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = game_init(argc, argv);
	if (!game)
		return (1);

	mlx_hook(game->mlx, 33, 1L << 17, safeexit, (void *)game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, (void *)game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	return (safeexit(game));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:36 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 16:46:54 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

int	get_line_count(const char *filename)
{
	FILE	*file;
	int		count;
	char	*buffer;

	file = fopen(filename, "r");
	if (!file)
		return (-1);
	count = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return (-1);
	while (fgets(buffer, BUFFER_SIZE, file) != NULL)
		count++;
	fclose(file);
	free(buffer);
	return (count);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += ((int)str[i] - '0');
		i++;
	}
	return (nb);
}

void	ft_strcpy2(t_game *data, char *map, int i)
{
	while (*map)
	{
		data->map_path[i] = *map;
		map++;
		i++;
	}
}

void	create_file_name(t_game *data, int argc, char **argv)
{
	char	*map;

	if (argc == 1)
	{
		data->map_path = "maps/map5.ber";
		return ;
	}
	if (ft_atoi(argv[1]) == 0 || (ft_atoi(argv[1]) > data->nb_map - 1))
	{
		ft_printf("Error input file\n");
		safeexit(data);
	}
	map = "maps/map";
	data->map_path = (char *)arena_alloc(data->arena, sizeof(char) * 12 + ft_strlen(argv[1]));
	ft_strcpy2(data, map, 0);
	map = argv[1];
	ft_strcpy2(data, map, 8);
	map = ".ber";
	ft_strcpy2(data, map, 9 + ft_strlen(argv[1]));
}

void	parse_map(t_game *data)
{
	int		line_count;
	FILE	*file;
	char	buffer[BUFFER_SIZE];
	int		i;

	if (!data || !data->map_path)
		return ;
	line_count = get_line_count(data->map_path);
	if (line_count <= 0)
		return ;
	data->map = arena_alloc(data->arena, sizeof(char *) * (line_count + 1));
	if (!data->map)
		return ;
	file = fopen(data->map_path, "r");
	if (!file)
		return ;
	i = 0;
	while (fgets(buffer, BUFFER_SIZE, file) != NULL)
	{
		data->map[i] = strdup(buffer);
		if (!data->map[i])
			return ;
		i++;
	}
	data->map[i] = NULL; // Null-terminate the array
    data->map_height = line_count;
    data->map_width = strlen(data->map[0]) - 1;
	fclose(file);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 19:04:28 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"
bool aabb_collision(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
    if (ax + aw < bx || ax > bx + bw) return false; // No overlap on x-axis
    if (ay + ah < by || ay > by + bh) return false; // No overlap on y-axis
    return true; // Overlap exists
}

void resolve_collision(t_game *game, int wall_x, int wall_y, int tile_size, int player_width, int player_height) {
    float bounce_factor = -0.5; // Less strong bounce

    // Horizontal collision
    if (game->player->pos.x + player_width > wall_x && 
        game->player->pos.x < wall_x + tile_size) {
        game->player->speed.x *= bounce_factor;
    }

    // Vertical collision
    if (game->player->pos.y + player_height > wall_y && 
        game->player->pos.y < wall_y + tile_size) {
        game->player->speed.y *= bounce_factor;
    }
}

void check_collisions_walls(t_game *game) {
    int player_width = 50; // Assuming player's width
    int player_height = 50; // Assuming player's height
    int tile_size = 50; // Assuming each tile size

    for (int i = 0; i < game->map_height; i++) {
        for (int j = 0; j < game->map_width; j++) {
            if (game->map[i][j] == '1') { // Wall tile
                if (aabb_collision(
                    game->player->pos.x, game->player->pos.y,
                    player_width, player_height,
                    j * tile_size, i * tile_size, tile_size, tile_size)) {
                    // Collision found, resolve it
                    resolve_collision(game, j * tile_size, i * tile_size, tile_size, player_width, player_height);
                }
            }
        }
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_gravity.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:36:52 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 19:01:36 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_GRAVITY_H
# define SO_LONG_GRAVITY_H

# include "arena/arena_internal.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define KEY_ESCAPE 65307
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_EXIT 17
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_SPACE 32
# define KEY_SHIFT 65505
# define KEY_CTRL 65507
# define KEY_TAB 65289
# define KEY_ENTER 65293
# define KEY_BACKSPACE 65288
# define KEY_DELETE 65535
# define KEY_HOME 65360
# define KEY_END 65367
# define KEY_PAGE_UP 65365
# define KEY_PAGE_DOWN 65366
# define KEY_INSERT 65379
# define KEY_NUMPAD_0 65438
# define KEY_NUMPAD_1 65436
# define KEY_NUMPAD_2 65433
# define KEY_NUMPAD_3 65435
# define KEY_NUMPAD_4 65430
# define KEY_NUMPAD_5 65437
# define KEY_NUMPAD_6 65432
# define KEY_NUMPAD_7 65429
# define KEY_NUMPAD_8 65431
# define KEY_NUMPAD_9 65434
# define PLAYER 0
# define ENEMY 1
# define COLLECTIBLE 2
# define BUFFER_SIZE 1024

typedef struct s_vect_2d
{
	int				x;
	int				y;
}					t_vect;

typedef t_vect		t_point;
typedef t_vect		t_speed;
typedef t_vect		t_accel;

typedef struct s_entity
{
	int				ent_type;
	t_point			pos;
	t_speed			speed;
	t_accel			accel;
	int				mass;
}					t_entity;

typedef t_entity	t_player;
typedef t_entity	t_enemy;
typedef t_entity	t_collectible;

typedef struct s_game
{
	t_player		*player;
	t_accel			*gravity;
	void			*mlx;
	void			*win;
	void			*player_img;
	void			*playerm_img;
	void			*background_img;
	void			*wall_img;
	void			*exit_img;
	void			*collectible_img;
	void			*enemy_img;
	void			*enemym_img;
	t_arena			*arena;
	struct timeval	last_frame;
	float			time;
	char			**map;
	int				map_width;
	int				map_height;
	char			*map_path;
	int				nb_map;
}					t_game;

t_game				*game_init(int argc, char **argv);
int					safeexit(void *data);
int					key_press(int keycode, t_game *game);
int					key_press2(int keycode, t_game *game);
float				get_time(t_game *game);
void				physic(t_game *game);
void				create_file_name(t_game *data, int argc, char **argv);
void				parse_map(t_game *data);
void				check_map(t_game *data);
int					ft_printf(const char *src, ...);
int					ft_strlen(char *str);
int					ft_strstrlen(char **str);
int					ft_atoi(char *str);
void				check_collisions_walls(t_game *game);
t_point				find_player(t_game *data);
int					key_release(int keycode, t_game *game);
#endif