/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 01:23:19 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/27 19:12:03 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_switch_var(int *var)
{
	if (*var)
		*var = 0;
	else
		*var = 1;
}

int	ft_exit(t_mlx *mlx)
{
	ft_mlxclear(&mlx);
	exit(EXIT_SUCCESS);
	return (0);
}


void	ft_map_keyboard(t_mlx *mlx, int key)
{
	mlx->event.key[key] = 1;
	if (key == 1)
		ft_switch_var(&mlx->shader);
	else if (key == 35)
		mlx->cam.proj_id = (mlx->cam.proj_id + 1) % 3;
	else if (key == 40)
		ft_colorhigh(mlx);
	else if (key == 0)
		ft_switch_var(&mlx->autorot);
	else if (key == 34)
		ft_switch_var(&mlx->display_info);
	else if (key == 2)
		ft_switch_var(&mlx->display_deco);
	else if (key == 14)
		mlx->map.delta = (mlx->map.delta + 1) % ((int) pow(log10(mlx->map.size),1.3));
	else if (key == 46)
		mlx->display_ref = (mlx->display_ref + 1) % 3;
	else if (key == 53)
		ft_exit(mlx);
	else if (key == 31)
		ft_cam_init(mlx, (mlx->cam.persp_id + 1) % 3);
	ft_render(mlx);
}

int	ft_keydown(int key, t_mlx *mlx)
{
	if (mlx->display_menu)
		ft_menu_move(mlx, key);
	else if (key == 49)
		ft_menu(mlx);
	else
		ft_map_keyboard(mlx, key);
	return (0);
}

int	ft_keyup(int key, t_mlx *mlx)
{
	mlx->event.key[key] = 0;
	return (0);
}
