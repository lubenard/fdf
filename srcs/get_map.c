/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:03:08 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/05 15:23:43 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/*
** Make connections between points, if needed
*/

void	make_connections(t_map *map, t_map_lst *map_elem)
{
	int			i;
	t_map_lst	*curr;

	curr = map_elem;
	i = 0;
	if (map_elem->y > 0)
	{
		while (curr && i != (int)map->line_size)
		{
			curr = curr->prev;
			i++;
		}
		map_elem->up = curr;
		curr->down = map_elem;
	}
}

/*
** Insert character into linked list at the right place
*/

int		insert_char(t_map *map, char *lines, size_t x, size_t y)
{
	t_map_lst	*map_elem;
	size_t		i;

	i = 0;
	map_elem = create_new_elem();
	if (x == 0 && y == 0)
		map->lst = map_elem;
	if (map->last)
	{
		map->last->next = map_elem;
		map_elem->prev = map->last;
	}
	if (ft_strlen(lines) > 11)
		return (ft_printf("OMG, %s it's too big !...\n", lines));
	map_elem->alt = ft_atoi(lines);
	if (map_elem->alt <= -10)
		map_elem->color = 0x0000FF;
	else if (map_elem->alt >= 10)
		map_elem->color = 0x00FF0000;
	map_elem->x = x;
	map_elem->y = y;
	map->last = map_elem;
	make_connections(map, map_elem);
	return (0);
}

/*
** Split line via spaces before insertion into linked list
*/

int		format_line(t_map *map, char *line, int y)
{
	char		**splitted_line;
	int			j;
	int			map_size_x;

	j = 0;
	splitted_line = ft_strsplit(line, ' ');
	map_size_x = ft_2dstrlen(splitted_line);
	if (y > 0 && map_size_x != (int)map->line_size)
	{
		write(2, "Hum, the map seems incorrect...\n", 32);
		ft_2dstrdel(&splitted_line);
		ft_strdel(&line);
		return (1);
	}
	map->line_size = map_size_x;
	while (splitted_line[j])
	{
		if (insert_char(map, splitted_line[j], j, y) != 0)
			return (1);
		j++;
	}
	ft_2dstrdel(&splitted_line);
	ft_strdel(&line);
	return (0);
}

/*
** Will read the file passed in argument
*/

int		get_map(t_fdf **fdf, int nbr_files, char **files)
{
	int		fd;
	char	*lines;
	int		y;

	y = 0;
	if (nbr_files > 2 || nbr_files == 1)
		return (error("Error: usage: ./fdf map\n"));
	else
	{
		if ((fd = open(files[1], O_DIRECTORY)) != -1)
		{
			close(fd);
			return (error("You tried to put a folder inside...\n"));
		}
		else if ((fd = open(files[1], O_RDONLY)) == -1)
			return (error("Could not open the file\n"));
		if (!(*fdf = init_fdf_structs()))
			return (error("Malloc failed when initialising structs\n"));
		while (get_next_line(fd, &lines) > 0)
			if (format_line((*fdf)->map, lines, y++) == 1)
				return (2);
		(*fdf)->map->height_size = y - 1;
		close(fd);
		return ((y == 0) ? 2 : 0);
	}
}
