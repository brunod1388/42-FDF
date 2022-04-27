/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 01:04:55 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/26 22:40:47 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define COS30 0.86602540378

void	ft_slide(t_mlx *mlx, int x, int y)
{
	mlx->cam.offsetx += x;
	mlx->cam.offsety += y;
}

void	ft_zoom(t_mlx *mlx, int dy)
{
	mlx->cam.scale *= 1 - 0.01 * dy;
	if (mlx->cam.scale < 0.5)
		mlx->cam.scale = 0.5;
	if (mlx->cam.scale > log10(mlx->map.size) * 5)
		mlx->cam.scale = log10(mlx->map.size) * 5;
	return ;
}

void	ft_hscale(t_mlx *mlx, int dy)
{
	mlx->cam.hscale *= 1 - 0.1 * dy;
	if (mlx->cam.hscale < 0.001)
		mlx->cam.hscale = 0.001;
	if (mlx->cam.hscale > 20)
		mlx->cam.hscale = 20;
	return ;
}

void	ft_cam_init(t_mlx *mlx, int id)
{
	static double	proj[3][2][3] = {{{COS30, -COS30, 0.0}, {0.5, 0.5, -1.0}},
	{{1.0, 0.0, -0.5}, {0.0, 1.0, 0.5}},
	{{COS30, 0.0, -COS30}, {0.5, 1.0, COS30}}};

	mlx->cam.persp_id = id;
	mlx->cam.persp[0][0] = proj[mlx->cam.persp_id][0][0];
	mlx->cam.persp[0][1] = proj[mlx->cam.persp_id][0][1];
	mlx->cam.persp[0][2] = proj[mlx->cam.persp_id][0][2];
	mlx->cam.persp[1][0] = proj[mlx->cam.persp_id][1][0];
	mlx->cam.persp[1][1] = proj[mlx->cam.persp_id][1][1];
	mlx->cam.persp[1][2] = proj[mlx->cam.persp_id][1][2];
}

void	ft_camrot(t_cam *cam, int dx, int dy)
{
	double		*ref[2];
	double		tmp[2][3];

	ref[0] = cam->persp[0];
	ref[1] = cam->persp[1];
	tmp[0][0] = ref[0][0];
	tmp[0][1] = ref[0][1];
	tmp[0][2] = ref[0][2];
	tmp[1][0] = ref[1][0];
	tmp[1][1] = ref[1][1];
	tmp[1][2] = ref[1][2];
	ref[0][0] = tmp[0][0] * cos(0.01 * dx) + tmp[0][1] * sin(0.01 * dx);
	ref[0][1] = -tmp[0][0] * sin(0.01 * dx) + tmp[0][1] * cos(0.01 * dx);
	ref[1][0] = tmp[1][0] * cos(0.01 * dx) + tmp[1][1] * sin(0.01 * dx);
	ref[1][1] = -tmp[1][0] * sin(0.01 * dx) + tmp[1][1] * cos(0.01 * dx);
	tmp[0][0] = ref[0][0];
	tmp[0][1] = ref[0][1];
	tmp[0][2] = ref[0][2];
	tmp[1][0] = ref[1][0];
	tmp[1][1] = ref[1][1];
	tmp[1][2] = ref[1][2];
	ref[0][1] = tmp[0][1] * cos(ROT_ANG * dy) + tmp[0][2] * sin(ROT_ANG * dy);
	ref[0][2] = -tmp[0][1] * sin(ROT_ANG * dy) + tmp[0][2] * cos(ROT_ANG * dy);
	ref[1][1] = tmp[1][1] * cos(ROT_ANG * dy) + tmp[1][2] * sin(ROT_ANG * dy);
	ref[1][2] = -tmp[1][1] * sin(ROT_ANG * dy) + tmp[1][2] * cos(ROT_ANG * dy);
}
