/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:03:08 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/20 20:02:57 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int			xi(t_map_lst *lst)
{
	int x;
	int dx;

	x = ((lst->x - lst->y) * 64) + 10; //v.bx
	dx = x - 960;
	x = 960 + (dx * 1); //v.z
	//ft_printf("Je return x = %d\n", x);
	return (x);
}

int			yi(t_map_lst *lst)
{
	int y;
	int dy;

	(void)lst;
	y = ((lst->y + lst->x) * 32 + 10) - lst->alt * 5; //v.by v.h
	//ft_printf("y = %d\n", y);
	dy = y - 540;
	//ft_printf("dy = %d\n", dy);
	y = 540 + (dy * 1); //v.z
	//ft_printf("Je return y = %d\n", y);
	return (y);
}

t_map_lst	*pai(t_map_lst *lst)
{
	int x;
	int y;

	x = xi(lst);
	y = yi(lst);
	ft_printf("Old coords are {y:%d x:%d alt:%d}\n", lst->y, lst->x, lst->alt);
	lst->x = x;
	lst->y = y;
	ft_printf("new coords are {y:%d x:%d}\n", lst->y, lst->x);
	return (lst);
}

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
	if (map_elem->alt <= -10)
		map_elem->color = 0x0000FF;
	else if (map_elem->alt >= 10)
		map_elem->color = 0x00FF0000;
	//ft_printf("generated %#x\n", 0x00FFFFFF);
	map_elem->x = x;
	map_elem->y = y;
	//pai(map_elem);
	curr = map_elem;
	map->last = map_elem;
	int		test = 0;
	if (map_elem->y > 0)
	{
		//ft_printf("Je suis sur le maillon {y:%d x:%d alt:%d}\n", curr->y, curr->x, curr->alt);
		while (curr && test != (int)map->line_size)
		{
			//ft_printf("Je remonte de %d maillons\n", test);
			curr = curr->prev;
			test++;
		}
		//ft_printf("Je viens d'arriver sur le maillon {y:%d x:%d alt:%d}\n", curr->y, curr->x, curr->alt);
		map_elem->up = curr;
		//ft_printf("Je map->up pointe vers %p, soit {y:%d x:%d alt:%d}\n", map_elem->up , map_elem->up->y, map_elem->up->x, map_elem->up->alt);
	}
	return (0);
}

/*
** Split line via spaces before insertion into linked list
*/

int		format_line(t_map *map, char *line, int y)
{
	char		**splitted_line;
	int			j;
	t_map_lst	*tmp;

	j = 0;
	splitted_line = ft_strsplit(line, ' ');
	map->line_size = ft_2dstrlen(splitted_line);
	ft_printf("length of my line is %d\n", map->line_size);
	while (splitted_line[j])
	{
		//ft_printf("J'envoie %s a insert_char\n", splitted_line[j]);
		insert_char(map, splitted_line[j], j, y);
		j++;
	}
	ft_2dstrdel(&splitted_line);
	//ft_printf("Premiere ligne --------------------------------\n");
	tmp = map->lst;
	while (tmp)
	{
		//ft_printf("{y:%d x:%d alt:%d}\n", tmp->y, tmp->x,tmp->alt);
		tmp = tmp->next;
	}
	//ft_printf("\n");
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
		if ((fd = open(files[1], O_RDONLY)) == -1)
			return (error("Could not open the file\n"));
		if (!(*fdf = init_fdf_structs()))
			return (error("Malloc failed when initialising lstcts\n"));
		//check_map();
		while (get_next_line(fd, &lines) > 0)
		{
			format_line((*fdf)->map, lines, y++);
			//break ; //DEBUG
		}
		close(fd);
		return (0);
	}
}
