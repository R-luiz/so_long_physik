/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:52:19 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/18 17:34:00 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"

int	key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        safeexit((void *)game);
    if (keycode == KEY_W)
        game->player->speed.y = -1;
    if (keycode == KEY_A)
        game->player->speed.x = -1;
    if (keycode == KEY_S)
        game->player->speed.y = 1;
    if (keycode == KEY_D)
        game->player->speed.x = 1;
    if (keycode == KEY_SPACE)
    {
        game->player->speed.x = 0;
        game->player->speed.y = 0;
    }
    return (0);
}
