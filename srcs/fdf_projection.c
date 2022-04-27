/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 00:43:40 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/26 11:23:52 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_cam(t_mlx *mlx, double	**x, double **y)
{
	*x = mlx->cam.persp[0];
	*y = mlx->cam.persp[1];
	mlx->cam.o_proj.x = 0;
	mlx->cam.o_proj.y = 0;
	mlx->cam.o_proj.z = -mlx->cam.r;
	mlx->cam.theta = M_PI / (mlx->map.ymax - 1);
	mlx->cam.phi = 2 * M_PI / (mlx->map.xmax - 1);
	if (mlx->map.delta == 0)
		mlx->map.delta = 1;
}


static double	ft_pt_dist(t_3dpoint a, t_3dpoint b)
{
	double	res;
	double	tmp;

	tmp = a.x - b.x;
	tmp *= tmp;
	res = tmp;
	tmp = a.y - b.y;
	tmp *= tmp;
	res += tmp;
	tmp = a.z - b.z;
	tmp *= tmp;
	res += tmp;
	return (sqrt(res));
}

static t_3dpoint	ft_vect_sub(t_3dpoint a, t_3dpoint b)
{
	t_3dpoint c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

static t_3dpoint	ft_p_round_proj(t_mlx *mlx, t_3dpoint p)
{
	t_3dpoint	p0;
	t_3dpoint	dst;
	double		cpd;

	p0 = p;
	p0.z = 0;
	cpd = (double) mlx->cam.r;
	cpd /= ft_pt_dist(p0, mlx->cam.o_proj);
	dst = ft_vect_sub(p, mlx->cam.o_proj);
	dst.x = dst.x * cpd + mlx->cam.o_proj.x;
	dst.y = dst.y * cpd + mlx->cam.o_proj.y;
	dst.z = dst.z * cpd + mlx->cam.o_proj.z;
	dst.color = p.color;
	return (dst);
}
static t_3dpoint	ft_p_sphere_proj(t_mlx *mlx, t_3dpoint p)
{
	t_3dpoint	dst;
	float		phi;
	float		theta;
	float		r;
	
	r = 5 * (mlx->map.hmax - mlx->map.hmin) + p.z;
	p.x = p.x * mlx->map.xmax / 500 + mlx->map.xmax / 2;
	p.y = p.y * mlx->map.xmax / 500 + mlx->map.ymax / 2;
	phi = mlx->cam.phi * p.x;
	theta = mlx->cam.theta * p.y;
	dst.y = r * cos(phi) * sin(theta);
	dst.x = r * sin(phi) * sin(theta);
	dst.z = r * cos(theta);
	dst.color = p.color;
	return (dst);
}

void	ft_project_map(t_mlx *mlx)
{
	int			i;
	int			j;
	int			index;
	t_3dpoint	p;
	double		*xyp[2];

	set_cam(mlx, &xyp[0], &xyp[1]);
	j = 0;
	while (j < mlx->map.ymax)
	{
		i = 0;
		index = j * mlx->map.xmax;
		while (i < mlx->map.xmax)
		{
			p = mlx->map.map3d[index];
			p.z = p.z * mlx->cam.hscale;
			if (mlx->cam.proj_id == round_id)
				p = ft_p_round_proj(mlx, p);
			if (mlx->cam.proj_id == sphere_id)
				p = ft_p_sphere_proj(mlx, p);
			mlx->map2d[index].x = mlx->cam.offsetx + (int)(mlx->cam.scale * (xyp[0][0] * p.x
						+ xyp[0][1] * p.y + xyp[0][2] * p.z));
			mlx->map2d[index].y = mlx->cam.offsety + (int)(mlx->cam.scale * (xyp[1][0] * p.x
						+ xyp[1][1] * p.y + xyp[1][2] * p.z));
			mlx->map2d[index].color = p.color;
			i += mlx->map.delta;
			index += mlx->map.delta;
		}
		j += mlx->map.delta;
	}
}
