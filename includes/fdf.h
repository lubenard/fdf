/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 23:57:40 by lubenard          #+#    #+#             */
/*   Updated: 2020/03/04 09:39:47 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

typedef struct			s_point
{
	double				x;
	double				y;
	double				alt;
}						t_point;

typedef struct			s_map_lst
{
	int					x;
	int					y;
	int					alt;
	int					color;
	int					manual_alt;
	struct s_map_lst	*up;
	struct s_map_lst	*down;
	struct s_map_lst	*next;
	struct s_map_lst	*prev;
}						t_map_lst;

typedef struct			s_map
{
	size_t				size;
	size_t				line_size;
	size_t				height_size;
	struct s_map_lst	*lst;
	struct s_map_lst	*last;
	int					zoom_level;
	int					vue;
}						t_map;

typedef struct			s_mlx
{
	void				*mlx_ptr;
	void				*mlx_win;
	void				*img_ptr;
	unsigned int		*data;
	int					bpp;
	int					colors;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct			s_fdf
{
	struct s_mlx		*mlx;
	struct s_map		*map;
}						t_fdf;

/*
** init structs
*/

t_fdf					*init_fdf_structs(void);
t_map_lst				*create_new_elem(void);

/*
** Get map
*/

int						get_map(t_fdf **fdf, int nbr_files, char **files);

/*
** Graphical part
*/

int						init_mlx(t_fdf *fdf);
int						draw(t_fdf *fdf);
int						colors(t_map_lst *lst, t_map_lst *lst_next, int colors);
void					draw_line(t_fdf *ptr, t_point one, t_point two,
int color);
int						fill_pixel(t_fdf *fdf, int color, int y, int x);
t_point					ft_ret_coord(t_map_lst iso);

/*
** Utils
*/

int						error(char *error_message);
int						free_structs(t_fdf *fdf, int return_code);
void					quit_fdf(t_fdf *fdf);

/*
** Dealing with keys
*/

int						move_x(t_fdf *map, int index);
int						move_y(t_fdf *map, int index);
int						zoom(t_fdf *map, int index);
int						change_vue(t_fdf *fdf);
int						change_alt(t_fdf *map, int index);
int						change_colors(t_fdf *fdf);

#endif
