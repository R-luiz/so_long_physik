/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 18:42:28 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"
bool aabb_collision(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
    if (ax + aw < bx || ax > bx + bw) return false; // No overlap on x-axis
    if (ay + ah < by || ay > by + bh) return false; // No overlap on y-axis
    return true; // Overlap exists
}

void resolve_collision(t_game *game, int wall_x, int wall_y, int tile_size, int player_width, int player_height) {
    float bounce_factor = -0.7; // Negative for bounce effect

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
