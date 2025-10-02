/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:01:42 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/02 14:14:41 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	init_images(t_mlx_data *data)
{
	// init minimap image
	data->map_img.mlx_img = mlx_new_image(data->mlx_pointer, data->window_width, data->window_height);
	data->map_img.addr = mlx_get_data_addr(data->map_img.mlx_img, &data->map_img.bpp, &data->map_img.line_len, &data->map_img.endian);

	// // init background image
	// data->background_img.mlx_img = mlx_new_image(data->mlx_pointer, WNDW_W, WNDW_H);
	// data->background_img.addr = mlx_get_data_addr(data->background_img.mlx_img, &data->background_img.bpp, &data->background_img.line_len, &data->background_img.endian);

	// init game images
	data->game_img.mlx_img = mlx_new_image(data->mlx_pointer, WNDW_W, WNDW_H);
	data->game_img.addr = mlx_get_data_addr(data->game_img.mlx_img, &data->game_img.bpp, &data->game_img.line_len, &data->game_img.endian);


}



void	init_textures(t_mlx_data *data)
{

	size_t		i;
	const char	*textures_path[] = {P_FLOOR, P_WALL, P_EP, P_SP, P_WP, P_NP, P_EXTRA};
	const char	*floor_ceiling_txtre_path[] = {P_GRASS, P_SKY};

	i = 0;
	while (i < 2)
	{
		data->bckgr_txtr[i] = mlx_xpm_file_to_image(data->mlx_pointer,
			(char *)floor_ceiling_txtre_path[i], &data->img_width, &data->img_height);
		if (!data->bckgr_txtr[i])
		{
			printf("Error initializing the textures\n");
			close_window(data);
		}
		i++;
	}

	i = 0;
	while (i < 7)
	{
		data->textures[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 7)
	{
		data->textures[i] = mlx_xpm_file_to_image(data->mlx_pointer,
				(char *)textures_path[i], &data->img_width, &data->img_height);
		if (!data->textures[i])
		{
			printf("Error initializing the textures\n");
			close_window(data);
		}
		i++;
	}
}

static void	init_map(t_map *map)
{
	char temp_map[8][8] = {
		{'1','1','1','1','1','0','0','0'},
		{'1','0','1','0','1','0','0','0'},
		{'1','0','1','0','0','1','1','1'},
		{'1','0','1','0','W','0','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','1','0','C','0','0','1','1'},
		{'1','0','0','0','0','1','0','1'},
		{'1','1','1','1','1','1','1','1'}
	};

	// Copy the array
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			map->grid[i][j] = temp_map[i][j];
		}
	}
	map->cols = 8;
	map->rows = 8;
}

void	init_data(t_mlx_data *data)
{
	init_map(&(data->map));
	data->img_width = 0;
	data->img_height = 0;
	data->moves = 0;
	data->window_width = (data->map).cols * TILE_SIZE;
	data->window_height = (data->map).rows * TILE_SIZE;
	data->display_map = true;
}

void	which_starting_direction(t_player_data *player, char facing)
{
	if (facing == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = -0.66;
	}
	if (facing == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		player->planeX = 0;
		player->planeY = 0.66;
	}

	if (facing == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
		player->planeX = 0.66;
		player->planeY = 0;
	}

	if (facing == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
		player->planeX = -0.66;
		player->planeY = 0;
	}
}

int	init_player(t_player_data *player, t_mlx_data *data)
{
	int	init_pos = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			if (data->map.grid[i][j] == 'E' || data->map.grid[i][j] == 'W'
				|| data->map.grid[i][j] == 'S' || data->map.grid[i][j] == 'N')
			{
				if (init_pos != 0)
					return (printf("Multiple starting position\n"), 0);
				player->posX = j + 0.5;
				player->posY = i + 0.5;
				which_starting_direction(player, data->map.grid[i][j]);
				init_pos++;

			}
		}
	}
	// player->dirX = -1;
	// player->dirY = 0;
	// player->planeX = 0;
	// player->planeY = 0.66;
	player->start_time = date_in_ms();
	player->time = 0;
	player->old_time = 0;
	player->frameTime = 0;
	player->mlx_data_pointer = data;

	player->rotSpeed = 0;
	player->moveSpeed = 0;

	player->perpWallDist = 0;

	player->kbrd.key_w = false;
	player->kbrd.key_s = false;
	player->kbrd.key_a = false;
	player->kbrd.key_d = false;
	player->kbrd.key_left = false;
	player->kbrd.key_right = false;
	player->kbrd.key_m = true;

	player->w_side.east = false;
	player->w_side.west = false;
	player->w_side.north = false;
	player->w_side.south = false;

	player->side = 0;

	player->print_debug = true;
	player->game_init = true;

	return (1);



}



