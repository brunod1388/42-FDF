/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 02:59:33 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:51:08 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_putpixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < WIN_WIDTH && 0 <= y && y < WIN_HEIGHT)
	{
		dst = img->addr
			+ (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	ft_putlinex(t_img *img, t_2dpoint *a1, t_2dpoint *a2)
{
	int		x;
	int		y;
	int		dif;
	double	m;
	double	percent;

	dif = 1;
	if (a1->x > a2->x)
		dif = -1;
	x = 0;
	m = (double)(a2->y - a1->y) / (a2->x - a1->x);
	y = a1->y;
	percent = (double) 1 / ft_abs(a2->x - a1->x);
	while (ft_abs(x) < ft_abs(a2->x - a1->x))
	{
		y = (int)(m * x) + a1->y;
		ft_putpixel(img, x + a1->x, y, ft_get_color(a1->color, a2->color,
				(double) percent * ft_abs(x)));
		x += dif;
	}
}

static void	ft_putliney(t_img *img, t_2dpoint *a1, t_2dpoint *a2)
{
	int		x;
	int		y;
	int		dif;
	double	m;
	double	percent;

	dif = 1;
	if (a1->y > a2->y)
		dif = -1;
	y = 0;
	m = (double)(a2->x - a1->x) / (a2->y - a1->y);
	percent = (double) 1 / ft_abs(a2->y - a1->y);
	while (ft_abs(y) < ft_abs(a2->y - a1->y))
	{
		x = (int)(m * y) + a1->x;
		ft_putpixel(img, x, y + a1->y, ft_get_color(a1->color, a2->color,
				(double) percent * ft_abs(y)));
		y += dif;
	}
}

void	ft_putline(t_img *img, t_2dpoint *a1, t_2dpoint *a2)
{
	int		xdif;
	int		ydif;

	if ((a1->x < 0 && a2->x < 0) || (a1->y < 0 && a2->y < 0)
		|| (a1->x > WIN_WIDTH && a2->x > WIN_WIDTH)
		|| (a1->y > WIN_HEIGHT && a2->y > WIN_HEIGHT))
		return ;
	xdif = ft_abs(a2->x - a1->x);
	ydif = ft_abs(a2->y - a1->y);
	if (xdif && xdif > ydif)
		ft_putlinex(img, a1, a2);
	else if (ydif)
		ft_putliney(img, a1, a2);
}
