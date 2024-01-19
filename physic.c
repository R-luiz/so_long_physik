/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 17:02:49 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

// for the position of the player check everywhere around him if there is a wall, if there is a wall, reverse the speed
void	check_collisions_walls(t_game *game)
{
	if ((game->player->pos.x + 25) / 50 >= game->map_width
		|| (game->player->pos.x - 25) / 50 < 0)
		game->player->speed.x *= -1;
	if ((game->player->pos.y + 25) / 50 >= game->map_height
		|| (game->player->pos.y - 25) / 50 < 0)
		game->player->speed.y *= -1;
	if (game->map[(game->player->pos.y + 25) / 50][(game->player->pos.x + 25)
		/ 50] == '1')
		game->player->speed.x *= -1;
	if (game->map[(game->player->pos.y - 25) / 50][(game->player->pos.x + 25)
		/ 50] == '1')
		game->player->speed.x *= -1;
	if (game->map[(game->player->pos.y + 25) / 50][(game->player->pos.x - 25)
		/ 50] == '1')
		game->player->speed.x *= -1;
	if (game->map[(game->player->pos.y - 25) / 50][(game->player->pos.x - 25)
		/ 50] == '1')
		game->player->speed.x *= -1;
	if (game->map[(game->player->pos.y + 25) / 50][(game->player->pos.x + 25)
		/ 50] == '1')
		game->player->speed.y *= -1;
	if (game->map[(game->player->pos.y - 25) / 50][(game->player->pos.x + 25)
		/ 50] == '1')
		game->player->speed.y *= -1;
	if (game->map[(game->player->pos.y + 25) / 50][(game->player->pos.x - 25)
		/ 50] == '1')
		game->player->speed.y *= -1;
	if (game->map[(game->player->pos.y - 25) / 50][(game->player->pos.x - 25)
		/ 50] == '1')
		game->player->speed.y *= -1;
}
