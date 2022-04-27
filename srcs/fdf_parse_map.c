/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 03:04:16 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/27 19:50:17 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_getcolor(char *s)
{
	if (*s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s != ',')
		return (COLORDEF);
	if (s[0] == ',' && s[1] == '0' && (s[2] == 'x' || s[2] == 'X'))
		s += 3;
	return (ft_hextoi(s));
}

static void	ft_lines_to_map(t_list *lines, t_map *map)
{
	int		y;
	int		x;
	int		width;
	char	**split_line;

	y = 0;
	width = map->xmax;
	while (y < map->ymax)
	{
		split_line = ft_splitset(lines->content, " \n");
		x = 0;
		while (x < width)
		{
			(map->map3d)[y * width + x].x = (double) 500 / width * (x - width / 2);
			(map->map3d)[y * width + x].y = (double) 500 / width * (y - map->ymax / 2);
			(map->map3d)[y * width + x].z = (double)ft_atoi(split_line[x]);
			(map->map3d)[y * width + x].color = ft_getcolor(split_line[x]);
			x++;
		}
		ft_clearsplit(split_line);
		free(split_line);
		lines = lines->next;
		y++;
	}
	ft_lstclear(&lines, free);
}

static t_list	*ft_getmaplines(int fd, t_mlx *mlx)
{
	t_list	*lines;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	lines = ft_lstnew(line);
	line = get_next_line(fd);
	mlx->map.xmax = ft_count_wordset(line, " \n");
	while (line)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	free(line);
	mlx->map.ymax = ft_lstsize(lines);
	mlx->map.size = mlx->map.xmax * mlx->map.ymax;
	mlx->map.map3d = malloc(sizeof(t_3dpoint) * mlx->map.xmax * mlx->map.ymax);
	mlx->map2d = malloc(sizeof(t_2dpoint) * mlx->map.xmax * mlx->map.ymax);
	if (mlx->map.size > 250000 && mlx->cam.scale < 2)
		mlx->map.delta = (int) pow(1 - log2(mlx->cam.scale), 1.5);
	else
		mlx->map.delta = 1;
	return (lines);
}

void	ft_get_map(t_mlx *mlx, int fd)
{
	t_list	*lines;
	int		i;
	double	tmp[2];

	lines = ft_getmaplines(fd, mlx);
	if (mlx->map.map3d)
		ft_lines_to_map(lines, &mlx->map);
	ft_lstclear(&lines, free);
	i = -1;
	mlx->map.hmin = mlx->map.map3d[0].z;
	mlx->map.hmax = mlx->map.map3d[0].z;
	while (++i < mlx->map.size)
	{
		if (mlx->map.hmin > mlx->map.map3d[i].z)
			mlx->map.hmin = mlx->map.map3d[i].z;
		else if (mlx->map.hmax < mlx->map.map3d[i].z)
			mlx->map.hmax = mlx->map.map3d[i].z;
	}
	while (--i >= 0 && mlx->map.hmax - mlx->map.hmin)
		mlx->map.map3d[i].z *= 20 / (mlx->map.hmax - mlx->map.hmin);
	tmp[0] = mlx->map.hmax;
	tmp[1] = mlx->map.hmin;
	mlx->map.hmin *= 20 / (tmp[0] - tmp[1]);
	mlx->map.hmax *= 20 / (tmp[0] - tmp[1]);
	mlx->cam.r = mlx->map.xmax * 5;
}

void	ft_recharge(t_mlx *mlx)
{
	int	fd;
	
	free(mlx->map2d);
	free(mlx->map.map3d);
	mlx->cam.offsetx = WIN_WIDTH / 2;
	mlx->cam.offsety = WIN_HEIGHT / 2;
	mlx->cam.scale = 1;
	mlx->cam.hscale = 1;
	fd = open(mlx->path, O_RDONLY);
	ft_get_map(mlx, fd);
	close(fd);
}
