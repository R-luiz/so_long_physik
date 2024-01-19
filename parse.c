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
