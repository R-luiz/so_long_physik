/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:56 by rluiz             #+#    #+#             */
/*   Updated: 2024/01/19 19:07:23 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_gravity.h"
bool aabb_collision(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
    if (ax + aw < bx || ax > bx + bw) return false; // No overlap on x-axis
    if (ay + ah < by || ay > by + bh) return false; // No overlap on y-axis
    return true; // Overlap exists
}

void resolve_collision(t_game *game, int wall_x, int wall_y, int tile_size, int player_width, int player_height) {
    // Adjust position and speed to prevent overlap
    if (game->player->pos.x < wall_x + tile_size && 
        game->player->pos.x + player_width > wall_x) {
        // Horizontal collision
        if (game->player->speed.x > 0) { // Moving right
            game->player->pos.x = wall_x - player_width;
        } else if (game->player->speed.x < 0) { // Moving left
            game->player->pos.x = wall_x + tile_size;
        }
        game->player->speed.x = 0; // Stop horizontal movement
    }

    if (game->player->pos.y < wall_y + tile_size && 
        game->player->pos.y + player_height > wall_y) {
        // Vertical collision
        if (game->player->speed.y > 0) { // Moving down
            game->player->pos.y = wall_y - player_height;
        } else if (game->player->speed.y < 0) { // Moving up
            game->player->pos.y = wall_y + tile_size;
        }
        game->player->speed.y = 0; // Stop vertical movement
    }
}

void check_collisions_walls(t_game *game) {
    int player_width = 50; // Player's width
    int player_height = 50; // Player's height
    int tile_size = 50; // Tile size

    for (int i = 0; i < game->map_height; i++) {
        for (int j = 0; j < game->map_width; j++) {
            if (game->map[i][j] == '1') {
                if (aabb_collision(
                    game->player->pos.x, game->player->pos.y,
                    player_width, player_height,
                    j * tile_size, i * tile_size, tile_size, tile_size)) {
                    // Resolve collision
                    resolve_collision(game, j * tile_size, i * tile_size, tile_size, player_width, player_height);
                }
            }
        }
    }
}
