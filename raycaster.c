/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:11:46 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/30 22:01:29 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

// void	toggle_minimap(t_mlx_data *data, t_player_data *player)
// {
// 	if (data->display_map == true)	// Hide minimap - clear window
// 	{
// 		printf("Hide minimap\n");
// 		mlx_clear_window(data->mlx_pointer, data->mlx_window);
// 		data->display_map = false;
// 	}
// 	else 								// Show minimap - render it
// 	{
// 		printf("Show minimap\n");
// 		if (!data->textures[0])			// Ensure textures are loaded
// 			init_textures(data);
// 		render_map(data, player);
// 		data->display_map = true;
// 	}
// }

/* int	key_hook(int keycode, t_player_data *player)
{
	if (keycode == 65307)
		close_window(player->mlx_data_pointer);
	if (keycode == 109) {
		printf("Keycode = %d pressed\n", keycode);

		toggle_minimap(player->mlx_data_pointer, player); }
	if (keycode == 119)
	{
		printf("Keycode = %d pressed\n", keycode);
		printf("------------------- VALUES IN KEY_HOOK() ------------------\n");
		printf("player->posX = %.4f		player->dirX = %.4f\n", player->posX, player->dirX);
		printf("player->posY = %.4f		player->dirY = %.4f\n", player->posY, player->dirY);
		printf("player->moveSpeed = %.4f\n", player->moveSpeed);

		printf("------------------- -------------------- ------------------\n");

		if (player->posX + player->dirX * player->moveSpeed >= 1 && player->posX + player->dirX * player->moveSpeed < player->mlx_data_pointer->map.cols
			&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + player->dirX * player->moveSpeed)] != '1')
			player->posX += player->dirX * player->moveSpeed;
		// if (player->mlx_data_pointer->map.grid[(int)(player->posX + player->dirX * player->moveSpeed)][(int)player->posY] == '0')
		// 	player->posX += player->dirX * player->moveSpeed;
		if (player->posY + player->dirY * player->moveSpeed >= 1 && player->posY + player->dirX * player->moveSpeed < player->mlx_data_pointer->map.rows
			&& player->mlx_data_pointer->map.grid[(int)(player->posY + player->dirY * player->moveSpeed)][(int)player->posX] != '1')
			player->posY += player->dirY * player->moveSpeed;
		// if (player->mlx_data_pointer->map.grid[(int)player->posX][(int)(player->posY + player->dirY * player->moveSpeed)] == '0')
		// 	player->posY += player->dirY * player->moveSpeed;
		// render_map(player->mlx_data_pointer, player);



	}

	if (keycode == 115) // press S
	{
		if (player->posX - player->dirX * player->moveSpeed >= 1 && player->posX - player->dirX * player->moveSpeed < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX - player->dirX * player->moveSpeed)] != '1')
			player->posX -= player->dirX * player->moveSpeed;
		if (player->posY - player->dirY * player->moveSpeed >= 1 && player->posY - player->dirX * player->moveSpeed < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY - player->dirY * player->moveSpeed)][(int)player->posX] != '1')
			player->posY -= player->dirY * player->moveSpeed;
	}
	if (keycode == 100) // press D move right (strafe)
	{
		// Move perpendicular to the right: use (dirY, -dirX)
		double strafeX = -player->dirY * player->moveSpeed;
		double strafeY = player->dirX * player->moveSpeed;

		if (player->posX + strafeX >= 1 && player->posX + strafeX < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + strafeX)] != '1')
			player->posX += strafeX;
		if (player->posY + strafeY >= 1 && player->posY + strafeY < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY + strafeY)][(int)player->posX] != '1')
			player->posY += strafeY;
	}

	if (keycode == 97) // press A move left (strafe)
	{
		// Move perpendicular to the left: use (-dirY, dirX)
		double strafeX = player->dirY * player->moveSpeed;
		double strafeY = -player->dirX * player->moveSpeed;

		if (player->posX + strafeX >= 1 && player->posX + strafeX < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + strafeX)] != '1')
			player->posX += strafeX;
		if (player->posY + strafeY >= 1 && player->posY + strafeY < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY + strafeY)][(int)player->posX] != '1')
			player->posY += strafeY;
	}

	if (keycode == 65361)
	{
		printf ("left arrow pressed \n" );
		double	oldDirX = player->dirX;
		player->dirX = player->dirX * cos(- player->rotSpeed) - player->dirY * sin(- player->rotSpeed);
		player->dirY = oldDirX * sin(- player->rotSpeed) + player->dirY * cos(-player->rotSpeed);
		double	oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos( - player->rotSpeed) - player->planeY * sin( - player->rotSpeed);
		player->planeY = oldPlaneX * sin(- player->rotSpeed) + player->planeY * cos(- player->rotSpeed);
		// render_map(player->mlx_data_pointer, player);

	}

	if (keycode == 65363)
	{
		printf ("right arrow pressed \n" );
		double	oldDirX = player->dirX;
		player->dirX = player->dirX * cos(player->rotSpeed) - player->dirY * sin(player->rotSpeed);
		player->dirY = oldDirX * sin(player->rotSpeed) + player->dirY * cos(-player->rotSpeed);
		double	oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(player->rotSpeed) - player->planeY * sin(player->rotSpeed);
		player->planeY = oldPlaneX * sin(player->rotSpeed) + player->planeY * cos(player->rotSpeed);
		// render_map(player->mlx_data_pointer, player);

	}

	return (0);
} */

int	key_press_hook(int keysym, t_player_data *player)
{
	if (keysym == XK_Escape)
		close_window(player->mlx_data_pointer);
	// if (keysym == XK_m)
	// {
	// 	if (player->kbrd.key_m == false)
	// 	{
	// 		player->kbrd.key_m = true;
	// 		printf("player->kbrd.key_m = %d \n", player->kbrd.key_m);
	// 	}
	// 	else
	// 	{
	// 		player->kbrd.key_m = false;
	// 		printf("player->kbrd.key_m = %d \n", player->kbrd.key_m);
	// 		mlx_clear_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window);
	// 	}
	// 	// toggle_minimap(player->mlx_data_pointer, player);
	// }
	if (keysym == XK_w) // keycode ==
		player->kbrd.key_w = true;
	if (keysym == XK_s)
		player->kbrd.key_s = true;
	if (keysym == XK_a)
		player->kbrd.key_a = true;
	if (keysym == XK_d)
		player->kbrd.key_d = true;
	if (keysym == XK_Left)
		player->kbrd.key_left = true;
	if (keysym == XK_Right)
		player->kbrd.key_right = true;
	return (0);
}

int	key_release_hook(int keysym, t_player_data *player)
{

	if (keysym == XK_m)
	{
		if (player->kbrd.key_m == false)
		{
			player->kbrd.key_m = true;
			printf("player->kbrd.key_m = %d \n", player->kbrd.key_m);
		}
		else
		{
			player->kbrd.key_m = false;
			printf("player->kbrd.key_m = %d \n", player->kbrd.key_m);
			// mlx_clear_window(player->mlx_data_pointer->mlx_pointer, player->mlx_data_pointer->mlx_window);
		}
		// toggle_minimap(player->mlx_data_pointer, player);
	}
	if (keysym == XK_w)
		player->kbrd.key_w = false;
	if (keysym == XK_s)
		player->kbrd.key_s = false;
	if (keysym == XK_a)
		player->kbrd.key_a = false;
	if (keysym == XK_d)
		player->kbrd.key_d = false;
	if (keysym == XK_Left)
		player->kbrd.key_left = false;
	if (keysym == XK_Right)
		player->kbrd.key_right = false;
	return (0);
}



int	main(void)
{
	t_mlx_data		data;
	t_player_data	player;

	init_data(&data);
	if (!init_player(&player, &data))
		return (1);
	print_map(&(data.map));
	if (!render(&data, &player))
		return (1);
	return (0);
}