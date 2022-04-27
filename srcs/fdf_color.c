/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 23:31:16 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/25 00:16:09 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_getrelp(int a, int b, double p)
{
	if (a == b)
		return (a);
	return ((int) a + (b - a) * p);
}

int	ft_get_color(int c1, int c2, double p)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (c1 == c2)
		return (c1);
	r = ft_getrelp((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	g = ft_getrelp((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	b = ft_getrelp(c1 & 0xFF, c2 & 0xFF, p);
	return (r << 16 | g << 8 | b);
}

static void	ft_colormap(t_mlx *mlx, int c1, int c2)
{
	int		i;
	double	delta;

	i = -1;
	delta = mlx->map.hmax - mlx->map.hmin;
	while (++i < mlx->map.size)
		mlx->map.map3d[i].color = ft_get_color(c1, c2,
				(mlx->map.map3d[i].z - mlx->map.hmin) / delta);
}

static void	ft_colorworldmap(t_mlx *mlx)
{
	int		i;

	i = -1;
	while (++i < mlx->map.size)
	{
		if (mlx->map.map3d[i].z < 0)
			mlx->map.map3d[i].color = ft_get_color(0x070F20, 0x57A4FC,
					(mlx->map.map3d[i].z - mlx->map.hmin) / (-mlx->map.hmin));
		else if (mlx->map.map3d[i].y >= 4500 || mlx->map.map3d[i].y <= -4500)
			mlx->map.map3d[i].color = 0xFFFFFF;
		else if (mlx->map.map3d[i].z < 100)
			mlx->map.map3d[i].color = ft_get_color(0xFFF078, 0x05821A,
					mlx->map.map3d[i].z / 200);
		else if (mlx->map.map3d[i].z < 3500)
			mlx->map.map3d[i].color = ft_get_color(0x127000, 0x032600,
					(mlx->map.map3d[i].z - 200) / 3300);
		else
			mlx->map.map3d[i].color = 0xFFFFFF;
		if (mlx->map.map3d[i].z > 0 && mlx->map.map3d[i].y < -3000
			&& mlx->map.map3d[i].y > -4500)
			mlx->map.map3d[i].color = ft_get_color(mlx->map.map3d[i].color,
					0xFFFFFF, (mlx->map.map3d[i].y + 3000) / -1500);
	}
}

void	ft_colorhigh(t_mlx *mlx)
{
	static int	i = 0;
	int			max;

	i++;
	max = 8;
	if (i % max == 0)
		ft_colormap(mlx, 0, 0xFFFFFF);
	if (i % max == 1)
		ft_colormap(mlx, COLORDEF, 0xFFFFFF);
	if (i % max == 2)
		ft_colormap(mlx, COLORX, COLORY);
	if (i % max == 3)
		ft_colormap(mlx, 0xff0080, 0x25f431);
	if (i % max == 4)
		ft_colormap(mlx, DECO_BLUE, 0xFFFFFF);
	if (i % max == 5)
		ft_colormap(mlx, DECO_BLUE, COLORY);
	if (i % max == 6)
		ft_colormap(mlx, COLORZ, COLORY);
	if (i % max == 7)
		ft_colorworldmap(mlx);
}
