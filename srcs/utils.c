/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:40:47 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/24 18:39:27 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	//ft_memdel(&fdf->mlx->mlx_ptr);
	//ft_memdel(&fdf->mlx->mlx_win);
	//ft_memdel(&fdf->mlx->img_ptr);
	ft_memdel((void**)&fdf->mlx);
	ft_memdel((void**)&fdf);
	return (return_code);
}
