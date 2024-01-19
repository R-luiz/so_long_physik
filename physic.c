/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 15:32:47 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

void	physic(t_game *game)
{
	game->player->accel.y *= 0.9;
	game->player->accel.x *= 0.9;
	game->player->accel.y += game->gravity->y;
	game->player->accel.x += game->gravity->x;
	game->player->speed.y += game->player->accel.y;
	game->player->speed.x += game->player->accel.x;
	if (game->player->accel.y > 50)
		game->player->accel.y = 50;
	if (game->player->accel.x > 50)
		game->player->accel.x = 50;
	if (game->player->accel.y < -50)
		game->player->accel.y = -50;
	if (game->player->accel.x < -50)
		game->player->accel.x = -50;
	if (game->player->pos.x < 0)
	{
		game->player->pos.x = 0;
		game->player->speed.x *= -0.9;
		game->player->accel.x *= -1;
	}
	if (game->player->pos.y < 0)
	{
		game->player->pos.y = 0;
		game->player->speed.y *= -0.9;
		game->player->accel.y *= -1;
	}
	if (game->player->pos.x > 950)
	{
		game->player->pos.x = 950;
		game->player->speed.x *= -0.9;
		game->player->accel.x *= -1;
	}
	if (game->player->pos.y > 950)
	{
		game->player->pos.y = 950;
		game->player->speed.y *= -0.5;
		game->player->accel.y *= -0.5;
	}
	if (game->player->speed.x > 700)
		game->player->speed.x = 700;
	if (game->player->speed.y > 700)
		game->player->speed.y = 700;
	if (game->player->speed.x < -700)
		game->player->speed.x = -700;
	if (game->player->speed.y < -700)
		game->player->speed.y = -700;
	if (game->player->pos.y >= 940)
	{
		game->player->speed.x += game->player->speed.x * -0.01;
	}
	game->player->pos.x += game->player->speed.x / 100;
	game->player->pos.y += game->player->speed.y / 100;
}
