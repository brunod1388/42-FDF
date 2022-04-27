/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .fdf_testutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 23:11:35 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/01/29 15:51:08 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_3dpoint(t_3dpoint *coord)
{
	ft_printf("x : %f\n", coord->x);
	ft_printf("y : %f\n", coord->y);
	ft_printf("z : %f\n", coord->z);
	ft_printf("color : %#x\n", coord->color);
}

void	print_2dpoint(t_2dpoint *coord)
{
	ft_printf("x : %f\n", coord->x);
	ft_printf("y : %f\n", coord->y);
	ft_printf("color : %#x\n", coord->color);}

void	print_map(t_map *map, t_2dpoint *map2d)
{
	int	x;
	int	y;

	ft_printf("Map :\n");
	ft_printf("map->xmax : %i\n", map->xmax);
	ft_printf("map->ymax : %i\n", map->ymax);
	if (!map || !map2d)
	{
		ft_printf("map : %s\n", !map ? "vide" : "qqch");
		ft_printf("map2d : %s\n", !map2d ? "vide" : "qqch");
	}
	y = -1;
	while (++y < map->ymax)
	{
		x = -1;
		while (++x < map->xmax)
			ft_printf("%2i ", (int) map->map3d[y * map->xmax + x].z);
		ft_putchar('\n');
	}
	x = 0;
	while (x < map->xmax * map->ymax)
	{
		ft_printf("coord %i\n", x);
		print_3dpoint(&map->map3d[x]);
		ft_printf("+++++++++++++++++++++++++\n");
		print_2dpoint(&map2d[x++]);
		ft_printf("+++++++++++++++++++++++++\n");
		x++;
	}
}
