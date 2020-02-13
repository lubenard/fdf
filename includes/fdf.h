/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 23:57:40 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/13 17:35:42 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FDF_H
# define FDF_H

#include "../libft/includes/ft_printf.h"
#include "../libft/includes/get_next_line.h"

typedef struct			s_map_lst
{
	int					x;
	int					y;
	int					alt;
	struct s_map_lst	*up;
	struct s_map_lst	*down;
	struct s_map_lst	*right;
	struct s_map_lst	*left;
}						t_map_lst;

typedef struct			s_map
{
	size_t				size;
	struct s_map_lst	*lst;
	struct s_map_lst	*last;
}						t_map;

typedef struct			s_fdf
{
	void				*mlx_ptr;
	void				*mlx_win;
	struct s_map		*map;
}						t_fdf;

int						get_map(t_fdf *fdf, int nbr_files, char **files);
int						init_mlx(t_fdf *fdf);
void					free_structs(t_fdf *fdf);
# endif
