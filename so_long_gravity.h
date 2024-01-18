/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_gravity.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:36:52 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 16:49:00 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_GRAVITY_H
# define SO_LONG_GRAVITY_H

# include "arena_internal.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
}					t_game;

t_game				*game_init(void);
int					safeexit(t_game *game);
#endif