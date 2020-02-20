/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:38:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/20 20:06:59 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>
# define ABS(Value) ((Value) < 0 ? -(Value) : (Value))

int		fill_pixel(t_mlx *mlx, int color, int y, int x, char *DEBUG)
{
	(void)DEBUG;
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	ft_printf("{y:%d x:%d}\n", y, x);

	//ft_printf("Je dessine un point pour %s a ((%d * %d * 1) + 20 + (%d * 100) = %d\n", DEBUG , mlx->size_line, y, x * 100, (mlx->size_line * y * 5) + 20 + (x * 100));
	(void)mlx;
	(void)color;
	mlx->data[mlx->size_line * y + x] = mlx_get_color_value(mlx->mlx_ptr, color);
	return (0);
}

void	linebhi(t_fdf *fdf, t_map_lst *p1, t_map_lst *p2)
{
	int dx;
	int dy;
	int cumul;
	int x;
	int y;

	x = p1->x;
	y = p1->y;
	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	fill_pixel(fdf->mlx, p1->color, x, y, "LIGNE");
	y = p1->y + 1;
	cumul = dy / 2;
	while (y <= p2->y)
	{
		cumul += dx;
		if (cumul >= dy)
		{
			cumul -= dy;
			x += 1;
		}
		fill_pixel(fdf->mlx, p1->color, x, y, "LIGNE");
		y++;
	}
}

void	linebli(t_fdf *fdf, t_map_lst *p1, t_map_lst *p2)
{
	int dx;
	int dy;
	int cumul;
	int x;
	int y;

	x = p1->x;
	y = p1->y;
	dx = p2->x - p1->x;
	dy = (p2->y - p1->y);
	fill_pixel(fdf->mlx,p1->color, x, y, "LIGNE");
	x = p1->x + 1;
	cumul = dx / 2;
	while (x <= p2->x)
	{
		cumul += dy;
		if (cumul >= dx)
		{
			cumul -= dx;
			y += 1;
		}
		fill_pixel(fdf->mlx, p1->color, x, y, "LIGNE");
		x++;
	}
}

void	linehli(t_fdf *fdf, t_map_lst *p1, t_map_lst *p2)
{
	int dx;
	int dy;
	int cumul;
	int x;
	int y;

	x = p1->x;
	y = p1->y;
	dx = ABS(p2->x - p1->x);
	dy = ABS(p2->y - p1->y);
	fill_pixel(fdf->mlx, p1->color, x, y, "LINE");
	x = p1->x + 1;
	cumul = dx / 2;
	while (x <= p2->x)
	{
		cumul += dy;
		if (cumul >= dx)
		{
			cumul -= dx;
			y -= 1;
		}
		fill_pixel(fdf->mlx, p1->color, x, y, "LINE");
		x++;
	}
}

void	linehhi(t_map_lst *p1, t_map_lst *p2, t_fdf *fdf)
{
	int dx;
	int dy;
	int cumul;
	int x;
	int y;

	x = p1->x;
	y = p1->y;
	dx = ABS(p2->x - p1->x);
	dy = ABS(p2->y - p1->y);
	fill_pixel(fdf->mlx, p1->color, x, y, "LINE");
	y = p1->y + 1;
	cumul = dy / 2;
	while (y >= p2->y)
	{
		cumul += dx;
		if (cumul >= dy)
		{
			cumul -= dy;
			x += 1;
		}
		fill_pixel(fdf->mlx, p1->color, x, y, "LINE");
		y--;
	}
}

void	linei(t_map_lst *p1, t_map_lst *p2, t_fdf *fdf)
{
	t_map_lst	*elem;
	int			dx;
	int			dy;

	if (p1->x > p2->x)
	{
		elem = p1;
		p1 = p2;
		p2 = elem;
	}
	dx = ABS(p2->x - p1->x);
	dy = ABS(p2->y - p1->y);
	if (p1->y > p2->y)
	{
		if (dx > dy)
			linehli(fdf, p1, p2);
		else
			linehhi(p1, p2, fdf);
	}
	else if (dx > dy)
		linebli(fdf, p1, p2);
	else
		linebhi(fdf, p1, p2);
}

int			x(t_map_lst *lst)
{
	int x;
	int dx;

	x = (lst->x * 80) + 10;
	dx = x - 960;
	x = 960 + (dx * 1);
	return (x);
}

int			y(t_map_lst *stru)
{
	int y;
	int dy;

	y = (stru->y * 64 + 10) - stru->alt * 5;
	dy = y - 540;
	y = 540 + (dy * 1);
	return (y);
}

void		pa(t_map_lst *lst)
{
	int x_var;
	int y_var;

	x_var = x(lst);
	y_var = y(lst);
	lst->y = y_var;
	lst->x = x_var;
	return ;
}

void	map(t_map_lst *p, t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win);
	if (1 == 0)
	{
		/*while (p != NULL)
		{
			if (p->link_h != NULL)
				linei(pa(p), pa(p->link_h), m);
			if (p->link_v != NULL)
				linei(pa(p), pa(p->link_v), m);
			p = p->next;
				
		}*/
	}
	else
	{
		while (p)
		{
			//if (p->link_h != NULL)
			//	linei(pai(p), pai(p->link_h), m);
			if (p->up != NULL)
				linei(pai(p), pai(p->up), fdf);
			p = p->next;
		}
	}
	mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win, fdf->mlx->img_ptr, 0, 0);
	ft_bzero(fdf->mlx->data, 8294400);
}

/*
** Create new image and set it ready to draw
*/

int		set_image(t_fdf *fdf)
{
	int			k;
	t_map_lst	*lst;

	k = 0;
	lst = fdf->map->lst;
	fdf->mlx->img_ptr = mlx_new_image(fdf->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->mlx->data = malloc(sizeof(unsigned char) * 8294400);
	fdf->mlx->data = (unsigned int *)mlx_get_data_addr(fdf->mlx->img_ptr, &fdf->mlx->bpp, &fdf->mlx->size_line, &fdf->mlx->endian);
	map(lst, fdf);
	/*while (lst)
	{
		pai(lst);
		//fill_pixel(fdf->mlx, lst->color, lst->y, lst->x , "POINT");
		//fill_pixel(fdf->mlx, lst->color, lst->y * 5 - lst->alt * 2, lst->x * 100 + 20 + lst->alt, "POINT");
		if (lst->next && lst->y == lst->next->y)
		{
			ft_printf("Je trace une ligne entre %d {y:%d x:%d alt:%d} et %d {y:%d x:%d alt:%d}\n", (fdf->mlx->size_line * lst->y * 5) + 20 + (lst->x * 100) + k, lst->y, lst->x, lst->alt, (fdf->mlx->size_line * lst->next->y * 5) + 20 + (lst->next->x * 100), lst->next->y, lst->next->x, lst->next->alt);

				while (fdf->mlx->size_line * lst->y * 5 - lst->alt * 2 + lst->x * 100 + 20 + lst->alt + k <
				fdf->mlx->size_line * lst->next->y * 5 - lst->alt * 2 + lst->next->x * 100 + 20 + lst->alt)
					fill_pixel(fdf->mlx, 0x00FFFFFF, lst->y * 5 - lst->alt * 2, lst->x * 100 + 20 + lst->alt + k++, "LIGNE VERTICALE");
				k = 0;
		}
		k = 0;
		if (lst->up)
		{
			k = -5;
			//ft_printf("%d - %d = %d\n", fdf->mlx->size_line * lst->y * 5 + lst->x * 100 + 20,fdf->mlx->size_line * lst->up->y * 5 + lst->up->x * 100 + 20 , (fdf->mlx->size_line * lst->up->y * 5 + lst->up->x * 100 + 20) - (fdf->mlx->size_line * lst->y * 5 + lst->x * 100 + 20));
			while (k != 0)
			{
				fill_pixel(fdf->mlx, 0x00FFFFFF, lst->y * 5 - lst->alt * 2 + k, lst->x * 100 + 20 + lst->alt, "LIGNE HORIZONTAL");
				k++;
			}
			k = 0;
		}
		lst = lst->next;
	}*/
	///mlx_put_image_to_window(fdf->mlx->mlx_ptr, fdf->mlx->mlx_win, fdf->mlx->img_ptr, 0, 50);
	mlx_loop(fdf->mlx->mlx_ptr);
	return (0);
}

/*
** Handle image creation and drawing
*/

int		draw(t_fdf *fdf)
{
	set_image(fdf);
	//mlx_destroy_image(fdf->mlx->mlx_ptr, fdf->mlx->data);
	return (0);
}
