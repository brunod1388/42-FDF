/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_deco.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:38:50 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/27 03:48:55 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_deco(t_mlx *mlx, int width, int color)
{
	int	i;

	i = -1;
	while (++i < width * WIN_WIDTH)
		*(unsigned int *)(mlx->img.addr
				+ i * mlx->img.bits_per_pixel / 8) = color;
	--i;
	while (++i < (width + 1) * WIN_WIDTH)
		*(unsigned int *)(mlx->img.addr
				+ i * mlx->img.bits_per_pixel / 8) = 0xFFFFFF;
	i = WIN_HEIGHT * WIN_WIDTH - (width + 1) * WIN_WIDTH - 1;
	while (++i < WIN_HEIGHT * WIN_WIDTH - width * WIN_WIDTH)
		*(unsigned int *)(mlx->img.addr
				+ i * mlx->img.bits_per_pixel / 8) = 0xFFFFFF;
	while (++i < WIN_HEIGHT * WIN_WIDTH)
		*(unsigned int *)(mlx->img.addr
				+ i * mlx->img.bits_per_pixel / 8) = color;
}

static void	ft_put_info2(t_mlx *mlx)
{
	int		c;
	void	*m;
	void	*w;
	int		offy;
	
	offy = 0;
	if (mlx->display_deco)
		offy = DECO_WIDTH;
	c = COLORDEF;
	m = mlx->mlx;
	w = mlx->mlx_win;
	mlx_string_put(m, w, 50, offy + 50, c, "Slide  : left click");
	mlx_string_put(m, w, 50, offy + 70, c, "Zoom   : right click");
	mlx_string_put(m, w, 50, offy + 110, c, "Hscale : H + left click");
	mlx_string_put(m, w, 50, offy + 150, c, "Rotation :");
	mlx_string_put(m, w, 50, offy + 170, c, "axe z  : R + left click");
	mlx_string_put(m, w, 50, offy + 190, c, "axe x  : R + right click");
	mlx_string_put(m, w, 50, offy + 210, c, "axe xz : double click");
	mlx_string_put(m, w, 50, offy + 270, c, "A to autorot");
	mlx_string_put(m, w, 50, offy + 290, c, "S to allow shading on moves");
	mlx_string_put(m, w, 50, offy + 310, c, "P to change projection");
	mlx_string_put(m, w, 50, offy + 330, c, "T + left click to change radius");
	mlx_string_put(m, w, 50, offy + 350, c, "O to change perspective");
	mlx_string_put(m, w, 50, offy + 370, c, "K to change Kolors");
	mlx_string_put(m, w, 50, offy + 390, c, "E to change delta");
	mlx_string_put(m, w, 50, offy + 430, c, "M to show references");
	mlx_string_put(m, w, 50, offy + 450, c, "D to hide deco bands");
	mlx_string_put(m, w, 50, offy + 470, c, "I to hide info");
}

void	ft_set_projname(t_mlx *mlx)
{
	if (mlx->cam.proj_id == 0)
		mlx->cam.proj_name = "Plane";
	if (mlx->cam.proj_id == 1)
		mlx->cam.proj_name = "Round";
	if (mlx->cam.proj_id == 2)
		mlx->cam.proj_name = "Spherical";
	if (mlx->cam.persp_id == 0)
		mlx->cam.persp_name = "Isometrique";
	if (mlx->cam.persp_id == 1)
		mlx->cam.persp_name = "Parallele";
	if (mlx->cam.persp_id == 2)
		mlx->cam.persp_name = "Cavaliere";
}

void	ft_put_info(t_mlx *mlx)
{
	int		c;
	void	*m;
	void	*w;
	int		offy;
	int		deco_width;

	deco_width = 0;
	if (mlx->display_deco)
		deco_width = DECO_WIDTH;
	offy = WIN_HEIGHT - 70;
	c = COLORDEF;
	m = mlx->mlx;
	w = mlx->mlx_win;

	ft_set_projname(mlx);
	mlx_string_put(m, w, 50, offy - deco_width - 40, c, "Projection  : ");
	mlx_string_put(m, w, 185, offy - deco_width - 40, c, mlx->cam.proj_name);
	mlx_string_put(m, w, 50, offy - deco_width - 20, c, "Perspective : ");
	mlx_string_put(m, w, 185, offy - deco_width - 20, c, mlx->cam.persp_name);
	mlx_string_put(m, w, 50, offy - deco_width, c, "Path :");
	mlx_string_put(m, w, 120, offy - deco_width, c, mlx->path);
	mlx_string_put(m, w, 50, offy - deco_width + 20, c, "Charge new map wit SPACE bar");
	mlx_string_put(m, w, deco_width - 180, offy + 20, c, "ESC to quit");
	ft_put_info2(mlx);
}
