/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ref.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 03:00:15 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/26 23:47:56 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_mapinfo(t_mlx *mlx)
{
	char	*num;
	int		a;
	int		b;

	a = WIN_WIDTH - 100 - 60;
	b = 100 + 50;
	if (mlx->display_deco)
		b += DECO_WIDTH;
	num = ft_itoa(mlx->map.size);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 20, COLORDEF, "Size :");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 70, b + 20, COLORDEF, num);
	free(num);
	num = ft_itoa(mlx->map.xmax);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 40, COLORDEF, "Width :");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 80, b + 40, COLORX, num);
	free (num);
	num = ft_itoa(mlx->map.ymax);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 60, COLORDEF, "Height:");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 80, b + 60, COLORY, num);
	free(num);
	num = ft_ftoa(mlx->cam.scale, 3);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 80, COLORDEF, "Scale:");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 80, b + 80, COLORDEF, num);
	free(num);
	num = ft_ftoa(mlx->cam.hscale, 3);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 100, COLORDEF, "Hscale:");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 80, b + 100, COLORDEF, num);
	free(num);
	num = ft_itoa(mlx->map.delta);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 120, COLORDEF, "delta:");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 80, b + 120, COLORDEF, num);
	free(num);
	num = ft_itoa(mlx->cam.offsetx);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 140, COLORDEF, "offsetx:");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 80, b + 140, COLORDEF, num);
	free(num);
	num = ft_itoa(mlx->cam.offsety);
	mlx_string_put(mlx->mlx, mlx->mlx_win, a, b + 160, COLORDEF, "offsety:");
	mlx_string_put(mlx->mlx, mlx->mlx_win, a + 80, b + 160, COLORDEF, num);
	free(num);
}

static void	ft_putsquare(t_img *img, t_2dpoint *a1, t_2dpoint *a2, int op)
{
	int		x;
	int		y;
	char	*dst;

	y = a1->y;
	while (y < a2->y)
	{
		x = a1->x;
		while (x < a2->x)
		{
			dst = img->addr
				+ (y * img->line_length + x * (img->bits_per_pixel / 8));
			if (*(unsigned int *)dst & 0xFFFFFF)
				*(unsigned int *)dst |= op << 24;
			else
				ft_putpixel(img, x, y, a1->color);
			x++;
		}
		y++;
	}
}

static void	ft_refdeco(t_mlx *mlx, int offsetx, int offsety, int color)
{
	t_2dpoint	a;
	t_2dpoint	b;
	int			size;

	size = REF_SIZE;
	a.x = offsetx - size;
	a.y = offsety - size;
	a.color = color;
	b.x = offsetx + size;
	b.y = offsety + size;
	b.color = color;
	ft_putsquare(&mlx->img, &a, &b, 200);
}

void	ft_drawref(t_mlx *mlx)
{
	t_2dpoint	pt[4];
	double		*xproj;
	double		*yproj;
	int			offy;

	offy = 0;
	if (mlx->display_deco)
		offy = DECO_WIDTH;
	xproj = mlx->cam.persp[0];
	yproj = mlx->cam.persp[1];
	ft_refdeco(mlx, WIN_WIDTH - 100, offy + 100, COLORDECO);
	pt[0].x = WIN_WIDTH - 100;
	pt[0].y = offy + 100;
	pt[1].x = WIN_WIDTH - 100 + xproj[0] * (REF_SIZE - 10);
	pt[1].y = offy + 100 + yproj[0] * (REF_SIZE - 10);
	pt[2].x = WIN_WIDTH - 100 + xproj[1] * (REF_SIZE - 10);
	pt[2].y = offy + 100 + yproj[1] * (REF_SIZE - 10);
	pt[3].x = WIN_WIDTH - 100 + xproj[2] * (REF_SIZE - 10);
	pt[3].y = offy + 100 + yproj[2] * (REF_SIZE - 10);
	pt[0].color = 0xFFFFFF;
	pt[1].color = COLORX;
	ft_putline(&mlx->img, &pt[1], &pt[0]);
	pt[2].color = COLORY;
	ft_putline(&mlx->img, &pt[2], &pt[0]);
	pt[3].color = COLORZ;
	ft_putline(&mlx->img, &pt[3], &pt[0]);
}
