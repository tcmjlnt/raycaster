/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_mlx_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:10:50 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/25 20:33:56 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

int	close_window(t_mlx_data *data)
{
	for (int i = 0; i < 7; i++)
		mlx_destroy_image(data->mlx_pointer, data->textures[i]);
	mlx_destroy_image(data->mlx_pointer, data->ray_image);
	mlx_destroy_window(data->mlx_pointer, data->mlx_window);
	mlx_destroy_display(data->mlx_pointer);
	free(data->mlx_pointer);
	exit(1);
}

void	clear_ray_image(t_mlx_data *data)
{
	for (int y = 0; y < data->window_height; y++)
	{
		for (int x = 0; x < data->window_width; x++)
		{
			int offset = (y * data->ray_line_length) + (x * (data->ray_bits_per_pixel / 8));
			*(unsigned int*)(data->ray_data + offset) = 0x000000;
		}
	}
}

