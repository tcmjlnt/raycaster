/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:10:58 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/30 22:02:39 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>

# define TILE_SIZE 64
# define PLAYER_SIZE 8

# define WNDW_W 1920
# define WNDW_H 1080

# define RGB_WHT 0xFFFFFF
# define RGB_RED 0xdb4437
# define RGB_BLUE 0x4285f4
# define RGB_YLW 0xf4b400
# define RGB_GRN 0x0f9d58
# define RGB_SKY 0x8786C0
// # define RGB_FLR 0x927A8B
# define RGB_FLR 0xC08786

# define P_FLOOR "textures/green_texture.xpm"
# define P_WALL "textures/red_texture.xpm"
# define P_EP "textures/yellowE_texture.xpm"
# define P_SP "textures/yellowS_texture.xpm"
# define P_WP "textures/yellowW_texture.xpm"
# define P_NP "textures/yellowN_texture.xpm"
# define P_EXTRA "textures/blue_texture.xpm"
# define P_GRASS "textures/floor_texture.xpm"
# define P_SKY "textures/sky_texture.xpm"

# define FOV 66


typedef enum	e_tile
{
	E_FLOOR,
	E_WALL,
	E_EP,
	E_SP,
	E_WP,
	E_NP,
	E_EXTRA
}			t_tile;

typedef struct s_map
{
	char		grid[8][8];
	size_t		rows;
	size_t		cols;
}				t_map;

typedef struct	s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp; /* bits per pixel */
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_key_inpt
{
	bool		key_w;
	bool		key_s;
	bool		key_a;
	bool		key_d;
	bool		key_left;
	bool		key_right;
	bool		key_m;

}				t_key_inpt;


typedef struct s_mlx_data
{
	void		*mlx_pointer;
	void		*mlx_window;
	// void		*mlx_minimap;
	void		*textures[7];
	void		*bckgr_txtr[2];
	int			img_height;
	int			img_width;
	int			window_height;
	int			window_width;
	int			moves;
	t_map		map;
	bool		display_map;


	t_img		map_img;
	// t_img		background_img;
	t_img		game_img;

	// void		*ray_image; 		// en gros ce bloc a ete bouge dans t_img
	// char		*ray_data;
	// int		ray_bits_per_pixel;
	// int		ray_line_length;
	// int		ray_endian;

	// t_elements	*elts;
}			t_mlx_data;

typedef struct s_wall
{
	bool		west;
	bool		east;
	bool		north;
	bool		south;
}				t_wall;

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;


typedef struct s_player_data
{
	//t_coord		pos;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		start_time;
	double		time;
	double		old_time;
	double		frameTime;
	double		cameraX;

	// more like ray data
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;

	double		moveSpeed;
	double		rotSpeed;

	bool		print_debug;	// debug
	bool		game_init;		// debug

	t_wall		w_side;

	t_key_inpt	kbrd;


	t_mlx_data	*mlx_data_pointer;

}			t_player_data;

typedef struct s_sqr
{
	int			x;
	int			y;
	int			side;
	int			color;
}				t_sqr;

typedef struct s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			color;
}				t_rect;


// init_stuff
void		init_textures(t_mlx_data *data);
void		init_data(t_mlx_data *data);
int			init_player(t_player_data *player, t_mlx_data *data);
void		init_images(t_mlx_data *data);



// mlx_stuff
int			close_window(t_mlx_data *data);
// void		clear_ray_image(t_mlx_data *data);
void		clear_img(t_img *img, int width, int height);
void		clear_img_fast(t_img *img, int width, int height);
void		clear_all_img_buffers(t_player_data *player);





// render_stuff
void		render_map(t_mlx_data *data, t_player_data *player);
bool		render(t_mlx_data *data, t_player_data *player);

// game_stuff
int			key_hook(int keycode, t_player_data *player);
void		toggle_minimap(t_mlx_data *data, t_player_data *player);
int			key_press_hook(int keysym, t_player_data *data);
int			key_release_hook(int keysym, t_player_data *player);
void		handle_move(t_player_data *player);
void		print_ray_info(t_player_data *player, int x, FILE *fp);
void		print_updated_pos(t_player_data *player);







// utils
t_tile		char_to_tile(char c);
void		print_map(t_map *map);
double		date_in_s(void);
double		date_in_ms(void);

// render utils
void		img_pix_put(t_img *img, int x, int y, int color);
int			render_empty_sqr(t_img *img, t_sqr sqr);
int			render_sqr(t_img *img, t_sqr sqr);
int			render_rect(t_img *img, t_rect rect);






#endif