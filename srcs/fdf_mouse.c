/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 01:04:50 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/24 22:05:44 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mousedown(int button, int x, int y, t_mlx *mlx)
{
	(void) x;
	if (y < 0)
		return (0);
	mlx->event.isdown |= (1 << button);
	return (0);
}

int	ft_mouseup(int button, int x, int y, t_mlx *mlx)
{
	(void) x;
	(void) y;
	mlx->event.isdown &= ~(1 << button);
	return (0);
}

int	ft_mousemove(int x, int y, t_mlx *mlx)
{
	int	dx;
	int	dy;

	mlx->event.lastx = mlx->event.x;
	mlx->event.lasty = mlx->event.y;
	mlx->event.x = x;
	mlx->event.y = y;
	dx = mlx->event.x - mlx->event.lastx;
	dy = mlx->event.y - mlx->event.lasty;
	if (mlx->event.isdown & (1 << 1) && mlx->event.key[15])
		ft_camrot(&mlx->cam, dx, 0);
	else if (mlx->event.isdown & (1 << 2) && mlx->event.key[15])
		ft_camrot(&mlx->cam, 0, dy);
	else if (mlx->event.isdown & (1 << 1) && mlx->event.isdown & (1 << 2))
		ft_camrot(&mlx->cam, dx, dy);
	else if (mlx->event.isdown & (1 << 1) && mlx->event.key[4])
		ft_hscale(mlx, dy);
	else if (mlx->event.isdown & (1 << 1) && mlx->event.key[17])
		mlx->cam.r += dy;
	else if (mlx->event.isdown & (1 << 1))
		ft_slide(mlx, dx, dy);
	else if (mlx->event.isdown & (1 << 2))
		ft_zoom(mlx, dy);
	if (mlx->event.isdown)
		ft_render(mlx);
	return (0);
}
