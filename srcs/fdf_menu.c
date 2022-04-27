/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:36:48 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/04/27 19:56:59 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <dirent.h>

#define BOX_HEIGH 50
#define BOX_WIDTH 250
#define BOX_INTER 15
#define BOX_COLOR 0x23385E
#define TXT_COLOR 0xffffff
#define SEL_COLOR 0x444444
#define STX_COLOR 0xffffff
#define NB_ROW 3

typedef struct s_menu
{
	t_list	*files;
	int		size;
	int		selection;
	int		nb_line;
}	t_menu;

void	ft_get_files(t_menu *m)
{
	DIR				*d;
	struct dirent	*dir;
	char			*fname;

	d = opendir("./maps");
	if (!d)
		return ;
	dir = readdir(d);
	m->size = 0;
	while (dir != NULL)
	{
		fname = ft_strdup(dir->d_name);
		if (fname[0] == '.')
			free(fname);
		else
			ft_lstadd_back(&m->files, ft_lstnew((void *) fname));
		dir = readdir(d);
	}
	m->size = ft_lstsize(m->files);
	closedir(d);
	m->selection = 0;
	m->nb_line = m->size / NB_ROW;
	if (m->size % NB_ROW)
		++m->nb_line;
}

void	ft_draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	ymax;
	int	xmax;
	int	ymin;
	int	xmin;

	xmax = x + BOX_WIDTH / 2;
	ymax = y + BOX_HEIGH / 2;
	xmin = x - BOX_WIDTH / 2;
	ymin = y - BOX_HEIGH / 2;
	y = ymin;
	x += BOX_WIDTH / 2;
	while (y < ymax)
	{
		x -= BOX_WIDTH;
		while (x < xmax)
		{
			ft_putpixel(&mlx->img, x, y, color);
			if (x == xmax - 1 || x == xmin
				|| y == ymax - 1 || y == ymin)
				ft_putpixel(&mlx->img, x, y, 0xffffff);
			++x;
		}
		++y;
	}
}

void	ft_put_squares(t_mlx *mlx, t_menu *m)
{
	int			i;
	t_list		*f;
	int			x;
	int			y;

	i = 0;
	f = m->files;
	x = WIN_WIDTH / 2 - ((NB_ROW - 1) * BOX_WIDTH + (NB_ROW - 1) * BOX_INTER) / 2;
	y = WIN_HEIGHT / 2 - ((m->nb_line - 1) * BOX_HEIGH + (m->nb_line - 1) * BOX_INTER) / 2;
	while (i < m->size && f)
	{
		if (i == m->selection)
			ft_draw_square(mlx, x, y, SEL_COLOR);
		else
			ft_draw_square(mlx, x, y, BOX_COLOR);
		f = f->next;
		i++;
		if (i % NB_ROW == 0)
		{
			x -= (NB_ROW - 1) * (BOX_WIDTH + BOX_INTER);
			y += BOX_HEIGH + BOX_INTER;
		}
		else
			x += BOX_WIDTH + BOX_INTER;
	}
}

void	ft_put_filenames(t_mlx *mlx, t_menu *m)
{
	int			i;
	t_list		*f;
	int			x;
	int			y;

	i = 0;
	f = m->files;
	x = WIN_WIDTH / 2 - ((NB_ROW - 1) * BOX_WIDTH + (NB_ROW - 1) * BOX_INTER) / 2 - BOX_WIDTH * 0.25;
	y = WIN_HEIGHT / 2 - ((m->nb_line - 1) * BOX_HEIGH + (m->nb_line - 1) * BOX_INTER) / 2 - BOX_HEIGH * 0.25;
	while (i < m->size && f)
	{
		if (i == m->selection)
			mlx_string_put(mlx->mlx, mlx->mlx_win, x, y, STX_COLOR, f->content);
		else
			mlx_string_put(mlx->mlx, mlx->mlx_win, x, y, TXT_COLOR, f->content);
		f = f->next;
		i++;
		if (i % NB_ROW == 0)
		{
			x -= (NB_ROW - 1) * (BOX_WIDTH + BOX_INTER);
			y += BOX_HEIGH + BOX_INTER;
		}
		else
			x += BOX_WIDTH + BOX_INTER;
	}
}

void	ft_menu(t_mlx *mlx)
{
	mlx->display_menu = 1;
	mlx->menu = malloc(sizeof(t_menu));
	if (!mlx->menu)
		return ;
	ft_clear_img(&mlx->img);
	if (mlx->map2d)
		ft_memdel((void **)&mlx->map2d);
	if (mlx->map.map3d)
		ft_memdel((void **)&mlx->map.map3d);
	ft_get_files((t_menu *) mlx->menu);
	ft_render_menu(mlx);
}

void	ft_new_map(t_mlx *mlx, t_menu *m)
{
	int	fd;
	t_list	*l;

	l = m->files;
	while (m->selection--)
	{
		l = l->next;
		free(m->files->content);
		free(m->files);
		m->files = l;
	}
	mlx->path = ft_strjoin("maps/", ((char *) m->files->content));
	fd = open(mlx->path, O_RDONLY);
	if (fd > 0)
		ft_get_map(mlx, fd);
	close(fd);
	ft_lstclear(&m->files, free);
	ft_memdel((void **) &mlx->menu);
	if (mlx->map.map3d)
		mlx->display_menu = 0;
}

void	ft_menu_move(t_mlx *mlx, int key)
{
	t_menu *m;

	m = (t_menu *) mlx->menu;
	if (key == 123)
		if (--m->selection < 0)
			m->selection = m->size - 1;
	if (key == 124)
		if (++m->selection >= m->size)
			m->selection = 0;
	if (key == 126)
	{
		m->selection -= NB_ROW;
		if (m->selection < 0)
			m->selection = m->size - 1 - m->selection;
	}
	if (key == 125)
	{
		m->selection += NB_ROW;
		if (m->selection >= m->size)
			m->selection = m->selection - m->size;
	}
	if (key == 36)
		ft_new_map(mlx, (t_menu *) mlx->menu);
	if (key == 53)
		ft_exit(mlx);
}

void	ft_render_menu(t_mlx *mlx)
{
	t_menu	*m;
	
	m = (t_menu *) mlx->menu;
	ft_draw_deco(mlx, DECO_WIDTH, DECO_BLUE);
	ft_put_squares(mlx, (t_menu *) mlx->menu);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->mlx_win, WIN_WIDTH / 2 - 250, DECO_WIDTH + 30,
		0xffffff, "Choose a map with directionnal arrows and press enter");
	ft_put_filenames(mlx, m);
}
