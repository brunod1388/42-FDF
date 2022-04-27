/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:43:02 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/26 03:37:27 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_quit(char *message)
{
	ft_putendl(message);
	return (0);
}

int	render(t_mlx *mlx)
{
	ft_render(mlx);
	return (0);
}

void	hook_init(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, handle_no_event, mlx);
	mlx_loop_hook(mlx->mlx, render, mlx);
	mlx_hook(mlx->mlx_win, ON_KEYDOWN, 0, ft_keydown, mlx);
	mlx_hook(mlx->mlx_win, ON_KEYUP, 0, ft_keyup, mlx);
	mlx_hook(mlx->mlx_win, ON_MOUSEDOWN, 0, ft_mousedown, mlx);
	mlx_hook(mlx->mlx_win, ON_MOUSEUP, 0, ft_mouseup, mlx);
	mlx_hook(mlx->mlx_win, ON_MOUSEMOVE, 0, ft_mousemove, mlx);
	mlx_hook(mlx->mlx_win, ON_DESTROY, 0, ft_exit, mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		fd;

	if (argc != 2)
		return (ft_quit("error : please enter a map path as arg!"));
	mlx = ft_get_mlx(argv[1]);
	if (!mlx)
		return (ft_quit("error : mlx init did not succeed"));
	fd = open(mlx->path, O_RDONLY);
	if (fd > 0)
		ft_get_map(mlx, fd);
	close(fd);
	if (!mlx->map.map3d)
	{
		ft_mlxclear(&mlx);
		return (ft_quit("error : cannot parse file"));
	}
	ft_render(mlx);
	hook_init(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
