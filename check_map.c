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
