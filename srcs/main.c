/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:05:44 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/05 12:52:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		return_parsing;

	fdf = NULL;
	return_parsing = get_map(&fdf, argc, argv);
	if (return_parsing == 1)
		return (1);
	else if (return_parsing == 2)
		return (free_structs(fdf, 1));
	if (init_mlx(fdf) == 1)
		return (1);
	draw(fdf);
	return (free_structs(fdf, 0));
}
