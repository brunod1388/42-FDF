/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:42:49 by bgoncalv          #+#    #+#             */
/*   Updated: 2022/04/27 20:09:53 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <fcntl.h>

#include <stdio.h>     // TO REMOVE

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define DECO_WIDTH 60

# define REF_SIZE 60

# define COLORDEF 0x0081A1C1
# define DECO_BLUE 0x23385E
# define COLORX 0xFF2C3C
# define COLORY 0xBCFF00
# define COLORZ 0x1CBAFF
# define COLORDECO 0x660D172E

# define AUTOROT_FREQ 200
# define ROT_ANG 0.001

enum {
	plane_id,
	round_id,
	sphere_id
};

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_2dpoint
{
	int	x;
	int	y;
	int	color;
}	t_2dpoint;

typedef struct s_3dpoint
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_3dpoint;

typedef struct s_map
{
	int			size;
	int			xmax;
	int			ymax;
	double		hmin;
	double		hmax;
	t_3dpoint	*map3d;
	int			delta;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_cam
{
	int			offsetx;
	int			offsety;
	double		scale;
	double		hscale;
	double		persp[2][3];
	int			persp_id;
	char		*persp_name;
	char		*proj_name;
	int			r;
	float		phi;
	float		theta;
	int			proj_id;
	t_3dpoint	o_proj;
}	t_cam;

typedef struct s_event
{
	int	x;
	int	y;
	int	lastx;
	int	lasty;
	int	isdown;
	int	key[300];
}	t_event;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	char		*path;
	t_2dpoint	*map2d;
	t_img		img;
	t_map		map;
	t_cam		cam;
	t_event		event;
	int			display_info;
	int			display_ref;
	int			display_deco;
	int			display_menu;
	int			autorot;
	int			shader;
	void		*menu;
}	t_mlx;

t_mlx	*ft_get_mlx(char *title);
t_mlx	*ft_mlxclear(t_mlx **mlx);
void	ft_get_map(t_mlx *mlx, int fd);
void	ft_recharge(t_mlx *mlx);

void	ft_project_map(t_mlx *mlx);
void	ft_render(t_mlx *mlx);

void	ft_drawref(t_mlx *mlx);
void	ft_put_info(t_mlx *mlx);
void	ft_put_mapinfo(t_mlx *mlx);
void	ft_draw_deco(t_mlx *mlx, int width, int color);
void	ft_colorhigh(t_mlx *mlx);

void	ft_putpixel(t_img *img, int x, int y, int color);
void	ft_putline(t_img *img, t_2dpoint *a1, t_2dpoint *a2);
int		ft_get_color(int c1, int c2, double p);

int		ft_keydown(int key, t_mlx *mlx);
int		ft_keyup(int key, t_mlx *mlx);

int		ft_mousedown(int button, int x, int y, t_mlx *mlx);
int		ft_mouseup(int button, int x, int y, t_mlx *mlx);
int		ft_mousemove(int x, int y, t_mlx *mlx);

void	ft_cam_init(t_mlx *mlx, int id);
void	ft_zoom(t_mlx *mlx, int dy);
void	ft_slide(t_mlx *mlx, int x, int y);
void	ft_hscale(t_mlx *mlx, int dy);
void	ft_rotatex(t_mlx *mlx, int dy);
void	ft_rotatez(t_mlx *mlx, int dx);
void	ft_camrot(t_cam *cam, int dx, int dy);

void	ft_menu(t_mlx *mlx);
void	ft_menu_move(t_mlx *mlx, int key);
void	ft_render_menu(t_mlx *mlx);

int		handle_no_event(t_mlx *mlx);
void	ft_clear_img(t_img *img);
int		ft_exit(t_mlx *mlx);

char *ft_ftoa(double f, int n_dec);

#endif
