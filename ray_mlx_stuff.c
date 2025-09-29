/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_mlx_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:50 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/29 18:03:00 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static void	destroy_images(t_mlx_data *data)
{
		mlx_destroy_image(data->mlx_pointer, data->map_img.mlx_img);
		// mlx_destroy_image(data->mlx_pointer, data->background_img.mlx_img);
		mlx_destroy_image(data->mlx_pointer, data->game_img.mlx_img);

}

int	close_window(t_mlx_data *data)
{
	for (int i = 0; i < 7; i++)
		mlx_destroy_image(data->mlx_pointer, data->textures[i]);
	mlx_destroy_image(data->mlx_pointer, data->bckgr_txtr[0]);
	mlx_destroy_image(data->mlx_pointer, data->bckgr_txtr[1]);

	// mlx_destroy_image(data->mlx_pointer, data->ray_image);
	destroy_images(data);
	mlx_destroy_window(data->mlx_pointer, data->mlx_window);
	mlx_destroy_display(data->mlx_pointer);
	free(data->mlx_pointer);
	exit(1);
}

// void	clear_ray_image(t_mlx_data *data)
// {
// 	for (int y = 0; y < data->window_height; y++)
// 	{
// 		for (int x = 0; x < data->window_width; x++)
// 		{
// 			int offset = (y * data->ray_line_length) + (x * (data->ray_bits_per_pixel / 8));
// 			*(unsigned int*)(data->ray_data + offset) = 0x000000;
// 		}
// 	}
// }

void	clear_img(t_img *img, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			img_pix_put(img, j, i, 0x000000); // Black
			j++;
		}
		i++;
	}
}

void	clear_img_fast(t_img *img, int width, int height)
{
	(void) width;
	int total_bytes = height * img->line_len;
	memset(img->addr, 0, total_bytes);
}

void	clear_all_img_buffers(t_player_data *player)
{
	// clear_img_fast(&player->mlx_data_pointer->background_img, WNDW_W, WNDW_H);
	clear_img_fast(&player->mlx_data_pointer->game_img, WNDW_W, WNDW_H);
	clear_img_fast(&player->mlx_data_pointer->map_img,
		player->mlx_data_pointer->window_width,
		player->mlx_data_pointer->window_height);
}
