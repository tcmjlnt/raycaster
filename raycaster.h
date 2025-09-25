/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:10:58 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/25 19:57:58 by tjacquel         ###   ########.fr       */
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

# define TILE_SIZE 64
# define PLAYER_SIZE 8

# define P_FLOOR "textures/green_texture.xpm"
# define P_WALL "textures/red_texture.xpm"
# define P_EP "textures/yellowE_texture.xpm"
# define P_SP "textures/yellowS_texture.xpm"
# define P_WP "textures/yellowW_texture.xpm"
# define P_NP "textures/yellowN_texture.xpm"
# define P_EXTRA "textures/blue_texture.xpm"

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

typedef struct s_mlx_data
{
	void		*mlx_pointer;
	void		*mlx_window;
	// void		*mlx_minimap;
	void		*textures[7];
	int			img_height;
	int			img_width;
	int			window_height;
	int			window_width;
	int			moves;
	t_map		map;
	bool		display_map;

	void	*ray_image;
	char	*ray_data;
	int		ray_bits_per_pixel;
	int		ray_line_length;
	int		ray_endian;

	// t_elements	*elts;
}			t_mlx_data;

typedef struct s_ray_data
{

}			t_ray_data;

typedef struct s_player_data
{
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


	t_mlx_data	*mlx_data_pointer;

}			t_player_data;


// init_stuff
void		init_textures(t_mlx_data *data);
void		init_data(t_mlx_data *data);
void		init_player(t_player_data *player, t_mlx_data *data);
void		init_ray_image(t_mlx_data *data);



// mlx_stuff
int			close_window(t_mlx_data *data);
void		clear_ray_image(t_mlx_data *data);


// render_stuff
void		render_map(t_mlx_data *data, t_player_data *player);
bool		render(t_mlx_data *data, t_player_data *player);

// game_stuff
int			key_hook(int keycode, t_player_data *player);
void		toggle_minimap(t_mlx_data *data, t_player_data *player);


// utils
t_tile		char_to_tile(char c);
void		print_map(t_map *map);
double		date_in_s(void);
double	date_in_ms(void);





#endif