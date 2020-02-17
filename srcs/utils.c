/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:40:47 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/17 15:18:44 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		error(char *error_message)
{
	ft_dprintf(2, error_message);
	return (1);
}

void	free_structs(t_fdf *fdf)
{
	(void)fdf;
}
