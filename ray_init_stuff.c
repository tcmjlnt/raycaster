/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:01:42 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/25 19:53:46 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	init_ray_image(t_mlx_data *data)
{
	data->ray_image = mlx_new_image(data->mlx_pointer, data->window_width, data->window_height);
	data->ray_data = mlx_get_data_addr(data->ray_image, &data->ray_bits_per_pixel,
										&data->ray_line_length, &data->ray_endian);
}

void	init_textures(t_mlx_data *data)
{

		size_t		i;
	const char	*textures_path[] = {P_FLOOR, P_WALL, P_EP, P_SP, P_WP, P_NP, P_EXTRA};

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
		{'1','1','1','1','1','1','1','1'},
		{'1','0','1','0','0','0','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','1','0','W','0','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','1','0','C','0','1','0','1'},
		{'1','0','0','0','0','0','0','1'},
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

// void	player_dir(t_player_data *player)
// {
// 	if (player->facing == 'E')
// 	{
// 		player->dirX = 1;
// 		player->dirY = 0;
// 		player->planeX = 0;
// 		player->planeY = 0.66;
// 	}
// 		if (player->facing == 'W')
// 	{
// 		player->dirX = -1;
// 		player->dirY = 0;
// 		player->planeX = 0;
// 		player->planeY = 0.66;
// 	}
// 		if (player->facing == 'N')
// 	{
// 		player->dirX = 0;
// 		player->dirY = -1;
// 		player->planeX = 0.66;
// 		player->planeY = 0;
// 	}
// 		if (player->facing == 'S')
// 	{
// 		player->dirX = 0;
// 		player->dirY = 1;
// 		player->planeX = 0.66;
// 		player->planeY = 0;
// 	}
// }

void	init_player(t_player_data *player, t_mlx_data *data)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			if (data->map.grid[i][j] == 'E' || data->map.grid[i][j] == 'W'
				|| data->map.grid[i][j] == 'S' || data->map.grid[i][j] == 'N')
			{
				player->posX = j + 0.5;
				player->posY = i + 0.5;
			}
		}
	}
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
	player->start_time = date_in_ms();
	player->time = 0;
	player->old_time = 0;
	player->frameTime = 0;
	player->mlx_data_pointer = data;

	player->rotSpeed = 0;
	player->moveSpeed = 0;
}



