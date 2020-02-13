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
** Create new element of linked list
*/

t_map_lst	*create_new_elem(void)
{
	t_map_lst *elem;

	if (!(elem = malloc(sizeof(t_map_lst))))
		return (NULL);
	elem->x = 0;
	elem->y = 0;
	elem->alt = 0;
	elem->up = NULL;
	elem->down = NULL;
	elem->right = NULL;
	elem->left = NULL;
	return (elem);
}

/*
** Insert character into linked list
*/

int		insert_char(t_map *map, char *lines, size_t x, size_t y)
{
	t_map_lst *map_elem;

	map_elem = create_new_elem();
	if (!(map_elem->alt = ft_atoi(lines)))
	{
		ft_dprintf(2, "Apparently, %s is not a valid integer\n", lines);
		return (1);
	}
	map_elem->x = x;
	map_elem->y = y;
	return (0);
}

/*
** Split line via spaces before insertion into linked list
*/

int		format_line(t_map *map, char *line)
{
	char		**splitted_line;
	static int	i = 0;
	int			j;

	j = 0;
	if (!i)
	{
		map->lst = create_new_elem();
		map->last = map->lst;
		i++;
	}
	splitted_line = ft_strsplit(line, ' ');
	while (splitted_line[j])
		insert_char(fdf, splitted_line[j++], j, 0);
	return (0);
}

/*
** Will read the file passed in argument
*/

int		get_map(t_fdf *fdf, int nbr_files, char **files)
{
	int fd;
	char *lines;

	if (nbr_files > 2 || nbr_files == 1)
	{
		ft_dprintf(2, "Error, usage: ./fdf map\n");
		return (1);
	}
	else
	{
		fd = open(files[1], O_RDONLY);
		if (!(fdf = malloc(sizeof(t_fdf)))
		|| !(fdf->map = malloc(sizeof(t_map))))
			return (1);
		//check_map();
		while (get_next_line(fd, &lines) > 0)
			format_line(fdf->map, lines);
		close(fd);
		return (0);
	}
}
