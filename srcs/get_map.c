/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:03:08 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/13 12:32:40 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

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

int		insert_line(t_map *map, char *line)
{
	char		**splitted_line;
	static int	i = 0;

	if (!i)
	{
		map->lst = create_new_elem();
		map->last = map->lst;
		i++;
	}
	splitted_line = ft_strsplit(line, ' ');
	//while 
	return (0);
}

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
		while (get_next_line(fd, &lines) > 0)
			insert_line(fdf->map, lines);
		close(fd);
		return (0);
	}
}
