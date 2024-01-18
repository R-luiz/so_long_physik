/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:52:19 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 19:30:30 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

int	key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        safeexit((void *)game);
    if (keycode == KEY_W)
        game->player->accel.y += -60;
    if (keycode == KEY_A)
        game->player->accel.x += -25;
    if (keycode == KEY_S)
        game->player->accel.y += 15;
    if (keycode == KEY_D)
        game->player->accel.x += 25;
    if (keycode == KEY_SPACE)
    {
        game->player->speed.x = 0;
        game->player->speed.y = 0;
    }
    return (0);
}

int	key_press2(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        safeexit((void *)game);
    if (keycode == KEY_W)
        game->player->accel.y = 0;
    if (keycode == KEY_A)
        game->player->accel.x = 0;
    if (keycode == KEY_S)
        game->player->accel.y = 0;
    if (keycode == KEY_D)
        game->player->accel.x = 0;
    return (0);
}
