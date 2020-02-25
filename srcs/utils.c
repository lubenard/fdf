/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:40:47 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/25 14:34:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	quit_fdf(t_fdf *fdf)
{
	write(1, "Exiting Fdf...\n", 16);
	free_structs(fdf, 0);
	exit(0);
}

int		error(char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	return (1);
}

/*
** Free structs before exit or if problem is encountered
*/

int		free_structs(t_fdf *fdf, int return_code)
{
	t_map_lst	*tmp_lst;

	while (fdf->map->lst)
	{
		tmp_lst = fdf->map->lst;
		fdf->map->lst = fdf->map->lst->next;
		ft_memdel((void **)&tmp_lst);
	}
	ft_memdel((void**)&fdf->map);
	ft_memdel(&fdf->mlx->mlx_ptr);
	ft_memdel(&fdf->mlx->mlx_win);
	ft_memdel(&fdf->mlx->img_ptr);
	ft_memdel((void**)&fdf->mlx);
	ft_memdel((void**)&fdf);
	return (return_code);
}
