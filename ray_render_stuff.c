/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_stuff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:13:25 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/03 15:40:46 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

// static void	render_player(t_mlx_data *data, t_tile tile_type, int tile_x, int tile_y)
// {
// 	int center_offset_x = PLAYER_SIZE / 2 + (TILE_SIZE - PLAYER_SIZE) / 2;
// 	int center_offset_y = (TILE_SIZE - PLAYER_SIZE) / 2;
// 	int pixel_x = tile_x * TILE_SIZE + center_offset_x;
// 	int pixel_y = tile_y * TILE_SIZE + center_offset_y;

// 	mlx_put_image_to_window(data->mlx_pointer, data->mlx_window,
// 		data->textures[tile_type], pixel_x, pixel_y);
// }

// static void	render_tile(t_mlx_data *data, t_tile tile_type, int x, int y)
// {
// 	if (tile_type >= 2 && tile_type <= 5)
// 	{
// 		mlx_put_image_to_window(data->mlx_pointer, data->mlx_window,
// 			data->textures[E_FLOOR], x * TILE_SIZE, y * TILE_SIZE);
// 		render_player(data, tile_type, x, y);
// 		// mlx_put_image_to_window(data->mlx_pointer, data->mlx_window,
// 		// 	data->textures[tile_type], x * TILE_SIZE, y * TILE_SIZE);
// 	}
// 	else
// 		mlx_put_image_to_window(data->mlx_pointer, data->mlx_window,
// 			data->textures[tile_type], x * TILE_SIZE, y * TILE_SIZE);
// }

// void convert_to_screen_coords(double math_x, double math_y, int *screen_x, int *screen_y)
// {
// 	*screen_x = (int)(math_x * TILE_SIZE);
// 	// Flip Y coordinate for screen display (mathematical Y=0 is at bottom, screen Y=0 is at top)
// 	*screen_y = (int)((math_y) * TILE_SIZE); // Assuming 8x8 map
// }


void draw_ray_line(t_mlx_data *data, int x0, int y0, int x1, int y1) // a expliciter
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	int x = x0, y = y0;

	while (1)
	{
		if (x >= 0 && x <= data->window_width && y>= 0 && y<= data->window_height)
			img_pix_put(&data->map_img, x, y, 0xFFFF00);
		// if (x >= 0 && x <= WNDW_W && y>= 0 && y<= WNDW_H)
		// 	img_pix_put(&data->game_img, x, y, 0xFFFF00);


		if (x == x1 && y == y1) break;

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

void	render_2Dray(t_mlx_data *data, t_player_data *player, int x, FILE *fp) // a expliciter
{
	(void) fp;
	(void) x;
	// Calculate the exact wall hit position
	double wallHitX, wallHitY;
	// Store the starting position for ray drawing
	double startX = player->posX;
	double startY = player->posY;

	if (player->side == 0) // Hit a vertical wall (x-side)
	{
		wallHitX = player->mapX;
		if (player->stepX == -1)
			wallHitX += 1.0; // Hit the right side of the previous cell
		wallHitY = player->posY + (wallHitX - player->posX) * player->rayDirY / player->rayDirX;
	}
	else // Hit a horizontal wall (y-side)
	{
		wallHitY = player->mapY;
		if (player->stepY == -1)
			wallHitY += 1.0; // Hit the bottom side of the previous cell
		wallHitX = player->posX + (wallHitY - player->posY) * player->rayDirX / player->rayDirY;
	}

	// if (player->print_debug)
	// {
	// 	print_ray_info(player, x, fp);
	// 	fprintf(fp, "		Ray[%d]->startX =		%.4f		startY =		%.4f\n", x, startX, startY);
	// 	fprintf(fp, "		Ray[%d]->wallHitX =		%.4f		wallHitY =		%.4f\n\n", x, wallHitX, wallHitY);
	// }
	// int start_screen_x, start_screen_y, end_screen_x, end_screen_y;
	// convert_to_screen_coords(startX, startY, &start_screen_x, &start_screen_y);
	// convert_to_screen_coords(wallHitX, wallHitY, &end_screen_x, &end_screen_y);

	// Draw the ray to the exact wall hit position
	draw_ray_line(data,
		startX * TILE_SIZE, startY * TILE_SIZE,
		wallHitX * TILE_SIZE, wallHitY * TILE_SIZE);
	// draw_ray_line(data, start_screen_x, start_screen_y, end_screen_x, end_screen_y);

}


void	verLine(t_mlx_data *data, int x, int drawStart, int drawEnd, int color)
{
	int	y = 0;

	while (y < drawStart)
	{
		img_pix_put(&data->game_img, x, y, RGB_SKY);
		y++;
	}
	y = drawEnd;
	while (y < WNDW_H)
	{
		img_pix_put(&data->game_img, x, y, RGB_FLR);
		y++;
	}
	while (drawStart < drawEnd)
	{
		img_pix_put(&data->game_img, x, drawStart, color);
		drawStart++;
	}

}


void	render_cubes(t_mlx_data *data, t_player_data *player, int x)
{

	int color = RGB_RED;
	int	lineHeight = (int)(WNDW_H / player->perpWallDist);

	int	drawStart = -lineHeight / 2 + WNDW_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WNDW_H / 2;
	if (drawEnd >= WNDW_H)
		drawEnd = WNDW_H - 1;

	if (player->side) // le mur est un cote (est-ouest)
	{
		if (player->stepY == 1) // WEST facing wall -- on regarde a l'est
			color = RGB_BLUE;
		else
			color = RGB_RED; // EAST facing wall -- on regarde a l'ouest
	}
	else // le mur n'est pas un cote (est-ouest)
	{
		if (player->stepX == 1) // NORTH facing wall -- on regarde au sud
			color = RGB_GRN;
		else
			color = RGB_YLW; // SOUTH facing wall -- on regarde au nord
	}
	verLine(data, x, drawStart, drawEnd, color);







}


void	render_map(t_mlx_data *data, t_player_data *player)
{
	(void) player;
	int x, y;

	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{
			int screen_x = x * TILE_SIZE;
			int screen_y = y * TILE_SIZE;
			if (char_to_tile(data->map.grid[y][x]) == E_WALL)
				render_sqr(&data->map_img, (t_sqr){screen_x, screen_y,  TILE_SIZE, RGB_RED});

			else
				render_sqr(&data->map_img, (t_sqr){screen_x, screen_y,  TILE_SIZE, 0x000000});			// render_tile(data, char_to_tile(data->map.grid[y][x]), x, y);
		}
	}

	// raycasting_loop(data, player);
}


void	raycasting_loop(t_mlx_data *data, t_player_data *player)
{

	// int	w = data->map.cols;
	int	w = WNDW_W;
	// int w = 16;
	FILE	*fp;
	// int dda = 0;
	// if (player->print_debug)
	// {
	// 	print_ray_info(player, x, fp);
	// 	fprintf(fp, "		Ray[%d]->startX =		%.4f		startY =		%.4f\n", x, startX, startY);
	// 	fprintf(fp, "		Ray[%d]->wallHitX =		%.4f		wallHitY =		%.4f\n\n", x, wallHitX, wallHitY);
	// }
	if (player->print_debug)
	{
		fp = fopen("output.txt", "w");
		if (fp == NULL)
		{
			perror("fopen");
			close_window(player->mlx_data_pointer);
		}
	}


	for (int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		player->cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		player->rayDirX = player->dirX + player->planeX * player->cameraX;
		player->rayDirY = player->dirY + player->planeY * player->cameraX;

		//which box of the map we're in
		player->mapX = (int)player->posX;
		player->mapY = (int)player->posY;

		// printf("player->rayDirX = %f\n", player->rayDirX);
		// printf("player->rayDirY = %f\n", player->rayDirY);


		//length of ray from one x or y-side to next x or y-side --> deltaDistX || deltaDistY
		if (player->rayDirX == 0)
			player->deltaDistX = 1e30;
		else
			player->deltaDistX = fabs(1 / player->rayDirX);

		if (player->rayDirY == 0)
			player->deltaDistY = 1e30;
		else
			player->deltaDistY = fabs(1 / player->rayDirY);
		// if (player->print_debug)
		// {	printf("player->deltaDistX = %f\n", player->deltaDistX);
		// 	printf("player->deltaDistY = %f\n", player->deltaDistY);}

		player->hit = 0;

		//length of ray from current position to next x or y-side --> sideDistX || sideDistY
		if (player->rayDirX < 0)
		{
			player->stepX = -1;
			player->sideDistX = (player->posX - player->mapX) * player->deltaDistX;
		}
		else
		{
			player->stepX = 1;
			player->sideDistX = (player->mapX + 1.0 - player->posX) * player->deltaDistX;
		}
		if (player->rayDirY < 0)
		{
			player->stepY = -1;
			player->sideDistY = (player->posY - player->mapY) * player->deltaDistY;
		}
		else
		{
			player->stepY = 1;
			player->sideDistY = (player->mapY + 1.0 - player->posY) * player->deltaDistY;
		}
		// if (player->print_debug)
		// {
		// 	printf("player->sideDistX = %f\n", player->sideDistX);
		// 	printf("player->sideDistY = %f\n", player->sideDistY);
		// }


		// DDA - Digital Differential Analyzer
		// dda = 0;	// pour les prints de debug
		while (player->hit == 0)
		{
			//jump to next map sqr, either in x-direction, or in y-direction
			if (player->sideDistX < player->sideDistY)
			{
				player->sideDistX += player->deltaDistX;
				player->mapX += player->stepX;
				player->side = 0;
			}
			else
			{
				player->sideDistY += player->deltaDistY;
				player->mapY += player->stepY;
				player->side = 1;
			}
			// if (player->print_debug)
			// {
			// 	fprintf(fp, "			Ray[%d] DDA[%d]		sideDistX = %.4f		sideDistY = %.4f\n", x, dda, player->sideDistX, player->sideDistY);
			// 	dda++;
			// }
			if (data->map.grid[player->mapY][player->mapX] == '1')
				player->hit = 1;
		}
		if (player->side == 0)
			player->perpWallDist = player->sideDistX - player->deltaDistX;
		else
			player->perpWallDist = player->sideDistY - player->deltaDistY;


		if (player->kbrd.key_m == true)
		{
			// if (player->print_debug)
			// 	print_ray_info(player, x, fp);
			// render_minimap_background(data);

			// render_map(player->mlx_data_pointer, player);
			render_2Dray(player->mlx_data_pointer, player, x, fp);
		}

		render_cubes(player->mlx_data_pointer, player, x);


		// if (player->kbrd.key_m == true)
		// {
		// 	// if (player->print_debug)
		// 	// 	print_ray_info(player, x, fp);
		// 	// render_minimap_background(data);

		// 	// render_map(player->mlx_data_pointer, player);
		// 	render_2Dray(player->mlx_data_pointer, player);
		// }

	}
	if (player->print_debug)
		fclose(fp);
	player->print_debug = false;

}


// void	render_background(t_mlx_data *data, t_player_data *player)
// {
// 	(void) player;
// 	render_rect(&data->background_img, (t_rect){0, 0, WNDW_W, (WNDW_H / 2), RGB_SKY});
// 	render_rect(&data->background_img, (t_rect){0, WNDW_H / 2, WNDW_W, (WNDW_H / 2), RGB_FLR});




// }

// void	render_background(t_img *background_img, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < WNDW_H)
// 	{
// 		j = 0;
// 		while (j < WNDW_W)
// 		{
// 			img_pix_put(background_img, j++, i, color);
// 		}
// 		++i;
// 	}
// }


int	render_loop(t_player_data *player)
{

	// (void) player;
	// int x, y;
	// int	w = data->map.cols;
	// int	w = data->window_width;

	// printf ("player->posX = %.4f\n", player->posX);
	// printf ("player->posY = %.4f\n", player->posY);
	player->old_time = player->time;
	player->time = date_in_ms() - player->start_time;
	player->frameTime = (player->time - player->old_time) / 1000.0;
	// printf("player->old_time = %.2f		player->time = %.2f		player->frameTime = %.2f	FPS = %.2f\n", player->old_time, player->time, player->frameTime, 1.0 / player->frameTime);

	player->moveSpeed = player->frameTime * 5.0;
	player->rotSpeed  = player->frameTime * 3.0;

	if (player->game_init)
		print_updated_pos(player);
	handle_move(player);
	// clear_image(player->mlx_data_pointer);

	// clear_all_img_buffers(player);


	// for (y = 0; y < 8; y++)
	// {
	// 	for (x = 0; x < 8; x++)
	// 	`{
	// 		render_tile(player->mlx_data_pointer, char_to_tile(player->mlx_data_pointer->map.grid[y][x]), x, y);
	// 	}
	// }

	// render_background(player->mlx_data_pointer, player);

	// mlx_put_image_to_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window,
	// 	player->mlx_data_pointer->bckgr_txtr[1], 0, 0);
	// mlx_put_image_to_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window,
	// 	player->mlx_data_pointer->bckgr_txtr[0], 0, WNDW_H / 2);

	if (player->kbrd.key_m == true)
		render_map(player->mlx_data_pointer, player);


	raycasting_loop(player->mlx_data_pointer, player);

	// if (player->kbrd.key_m == true)
	// 	render_map(player->mlx_data_pointer, player);



	// mlx_clear_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window);


	// mlx_put_image_to_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window,
	// 	player->mlx_data_pointer->background_img.mlx_img, 0, 0);
	mlx_put_image_to_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window,
			player->mlx_data_pointer->game_img.mlx_img, 0, 0);
	if (player->kbrd.key_m == true)
		{mlx_put_image_to_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window,
			player->mlx_data_pointer->map_img.mlx_img, 0, 0);}


	// mlx_put_image_to_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window,
	// 							player->mlx_data_pointer->ray_image, 0, 0);

	return (0);
}


bool	render(t_mlx_data *data, t_player_data *player)
{
	data->mlx_pointer = mlx_init();
	if (!data->mlx_pointer)
		return (printf("MLX initialization failed\n"), false);

	data->mlx_window = mlx_new_window(data->mlx_pointer, WNDW_W,
			WNDW_H, "raycaster");
	// data->mlx_window = mlx_new_window(data->mlx_pointer, WNDW_W,
	// 		WNDW_H, "raycaster");
	if (!data->mlx_window)
	{
		mlx_destroy_display(data->mlx_pointer);
		free(data->mlx_pointer);
		return (printf("Window creation failed\n"), false);
	}
	init_textures(data);

	init_images(data);
	// render_background(player->mlx_data_pointer, player);


	mlx_loop_hook(data->mlx_pointer, render_loop, player);
	mlx_hook(data->mlx_window, KeyPress, KeyPressMask, key_press_hook, player);
	mlx_hook(data->mlx_window, KeyRelease, KeyReleaseMask, key_release_hook, player);
	mlx_hook(data->mlx_window, DestroyNotify, NoEventMask, close_window, data);
	// mlx_key_hook(data->mlx_window, key_hook, player);
	mlx_loop(data->mlx_pointer);

	cleanup_mlx(data);


	return (true);
}

