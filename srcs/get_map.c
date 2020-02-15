/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:03:08 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/13 19:38:45 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/*
** Insert character into linked list at the right place
*/

int		insert_char(t_map *map, char *lines, size_t x, size_t y)
{
	t_map_lst	*map_elem;
	size_t		i;
	t_map_lst	*curr;

	(void)lines;
	map_elem = create_new_elem();
	i = 0;
	curr = map->lst;
	if (x == 0 && y == 0)
	{
		ft_printf("First elem, is entrypoint\n");
		map->lst = map_elem;
	}
	/*while (i != y && curr->down)
	{
		ft_printf("Je descend de %d dans la liste\n", i);
		curr = curr->down;
		i++;
	}*/
	//while ()
	//ft_printf("map->last = %p\n", map->last);
	if (map->last)
	{
		map->last->next = map_elem;
		map_elem->prev = map->last;
	}
	/*if ((map_elem->alt = ft_atoi(lines)))
	{
		ft_dprintf(2, "Apparently, %s is not a valid integer\n", lines);
		return (1);
	}*/
	map_elem->alt = ft_atoi(lines);
	map_elem->x = x;
	map_elem->y = y;
	map->last = map_elem;
	//map->last = map_elem;
	//ft_printf("x = %d et y = %d, alt = %d\n", map_elem->x, map_elem->y, map_elem->alt);
	return (0);
}

/*
** Split line via spaces before insertion into linked list
*/

int		format_line(t_map *map, char *line, int y)
{
	char		**splitted_line;
	int			j;

	j = 0;
	splitted_line = ft_strsplit(line, ' ');
	while (splitted_line[j])
	{
		//ft_printf("J'envoie %s a insert_char\n", splitted_line[j]);
		insert_char(map, splitted_line[j], j, y);
		j++;
	}
	ft_printf("Premiere ligne --------------------------------\n");
	while (map->lst)
	{
		ft_printf("%d ", map->lst->alt);
		map->lst = map->lst->next;
	}
	ft_printf("\n");
	return (0);
}

/*
** Will read the file passed in argument
*/

int		get_map(t_fdf *fdf, int nbr_files, char **files)
{
	int		fd;
	char	*lines;
	int		y;

	y = 0;
	if (nbr_files > 2 || nbr_files == 1)
	{
		ft_dprintf(2, "Error: usage: ./fdf map\n");
		return (1);
	}
	else
	{
		fd = open(files[1], O_RDONLY);
		fdf = init_fdf_structs();
		//check_map();
		while (get_next_line(fd, &lines) > 0)
		{
			format_line(fdf->map, lines, y++);
			break ; //DEBUG
		}
		close(fd);
		return (0);
	}
}
