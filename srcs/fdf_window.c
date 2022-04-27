/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:18:58 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/27 19:58:27 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_set_default(t_mlx *mlx)
{
	mlx->map2d = NULL;
	mlx->map.map3d = NULL;
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	mlx->cam.offsetx = WIN_WIDTH / 2;
	mlx->cam.offsety = WIN_HEIGHT / 2;
	mlx->cam.scale = 1;
	mlx->cam.hscale = 1;
	mlx->cam.r = 1;
	mlx->cam.proj_id = plane_id;
	ft_cam_init(mlx, 0);
	ft_bzero(mlx->event.key, 300 * sizeof(int));
	mlx->display_info = 0;
	mlx->display_ref = 0;
	mlx->display_deco = 1;
	mlx->autorot = 0;
	mlx->shader = 0;
	mlx->menu = NULL;
}

t_mlx	*ft_get_mlx(char *path)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
	ft_set_default(mlx);
	mlx->path = path;
	if (!mlx->img.img || !mlx->mlx_win)
		return (ft_mlxclear(&mlx));
	return (mlx);
}

int	handle_no_event(t_mlx *mlx)
{
	(void) mlx;
	return (0);
}

t_mlx	*ft_mlxclear(t_mlx **mlx)
{
	if ((*mlx)->menu)
		free((*mlx)->menu);
	if ((*mlx)->mlx_win)
		mlx_destroy_window((*mlx)->mlx, (*mlx)->mlx_win);
	if ((*mlx)->img.img)
		mlx_destroy_image((*mlx)->mlx, (*mlx)->img.img);
	if ((*mlx)->map2d)
		ft_memdel((void **)&(*mlx)->map2d);
	if ((*mlx)->map.map3d)
		ft_memdel((void **)&(*mlx)->map.map3d);
	if ((*mlx)->mlx)
		ft_memdel(&(*mlx)->mlx);
	if ((*mlx)->menu)
		ft_memdel(&(*mlx)->menu);
	ft_memdel((void **)mlx);
	return (*mlx);
}
