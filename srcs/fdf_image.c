/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 01:01:54 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/27 00:21:20 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_clear_img(t_img *img)
{
	ft_bzero(img->addr, WIN_HEIGHT * WIN_WIDTH * img->bits_per_pixel / 8);
}

static void	ft_draw_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	delta;

	delta = mlx->map.delta;
	j = 0;
	while (j < mlx->map.ymax)
	{
		i = 0;
		if (j + delta < mlx->map.ymax)
			ft_putline(&mlx->img, &mlx->map2d[j * mlx->map.xmax + i],
				&mlx->map2d[(j + delta) * mlx->map.xmax + i]);
		i += delta;
		while (i < mlx->map.xmax)
		{
			ft_putline(&mlx->img, &mlx->map2d[j * mlx->map.xmax + i - delta],
				&mlx->map2d[j * mlx->map.xmax + i]);
			if (j + delta < mlx->map.ymax)
				ft_putline(&mlx->img, &mlx->map2d[j * mlx->map.xmax + i],
					&mlx->map2d[(j + delta) * mlx->map.xmax + i]);
			i += delta;
		}
		j += delta;
	}
}

int	color_part(int	color, float p)
{
	int	r;
	int	g;
	int	b;

	if (color == 0)
		return (color);
	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	r = (int) (((float) r) * p);
	g = (int) (((float) g) * p);
	b = (int) (((float) b) * p);
	return (r << 16 | g << 8 | b);
}

static void	ft_shader(t_img *img)
{
	int	i;
	char	*dst;

	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		dst = img->addr + (i * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color_part(*(unsigned int *)dst, 0.95);
		i++;
	}
}

void	ft_render(t_mlx *mlx)
{
	if (mlx->display_menu)
		return (ft_render_menu(mlx));
	if (mlx->shader)
		ft_shader(&mlx->img);
	else
		ft_clear_img(&mlx->img);
	if (mlx->autorot)
	{
		usleep(AUTOROT_FREQ);
		ft_camrot(&mlx->cam, 1, 0);
	}
	ft_project_map(mlx);
	ft_draw_map(mlx);
	if (mlx->display_deco)
		ft_draw_deco(mlx, DECO_WIDTH, DECO_BLUE);
	if (mlx->display_ref)
		ft_drawref(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	if (mlx->display_info)
		ft_put_info(mlx);
	if (mlx->display_ref == 1)
		ft_put_mapinfo(mlx);
}
