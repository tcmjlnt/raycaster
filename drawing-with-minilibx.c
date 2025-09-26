/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing-with-minilibx.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 16:20:37 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/26 19:05:03 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "./minilibx-linux/mlx.h"
// #include "./minilibx-linux/mlx_int.h"


#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_square
{
	int	x;
	int	y;
	int side;
	int color;
}	t_square;

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}


int render_square(t_img *img, t_square square)
{
	int	i;
	int j;

	i = square.y;
	while (i < square.y + square.side)
	{
		j = square.x;
		while (j < square.x + square.side)
				img_pix_put(img, j++, i, square.color);
		++i;
	}
	return (0);
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
				img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int render_empty_rect(t_img *img, t_rect rect)
{
	int j;

	// Draw top and bottom horizontal lines
	for (j = rect.x; j < rect.x + rect.width; j++)
	{
		img_pix_put(img, j, rect.y, rect.color);                    // top line
		img_pix_put(img, j, rect.y + rect.height - 1, rect.color); // bottom line
	}

	// Draw left and right vertical lines
	for (int i = rect.y; i < rect.y + rect.height; i++)
	{
		img_pix_put(img, rect.x, i, rect.color);                    // left line
		img_pix_put(img, rect.x + rect.width - 1, i, rect.color);  // right line
	}

	return (0);
}

int render_empty_square(t_img *img, t_square square)
{
	int	i;
	int j;

	i = square.y;
	while (i < square.y + square.side)
	{
		j = square.x;
		while (j < square.x + square.side)
		{
			// Only draw pixels on the border (edges)
			if (i == square.y || i == square.y + square.side - 1 ||
				j == square.x || j == square.x + square.side - 1)
				img_pix_put(img, j, i, square.color);
			j++;
		}
		i++;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (keysym == XK_Left || keysym == XK_M)
	{
		printf("Key Symbol = %d pressed\n", keysym);
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
	render_empty_square(&data->img, (t_square){WINDOW_WIDTH - 150, WINDOW_HEIGHT - 150, 50, GREEN_PIXEL});
	render_empty_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}