/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:10:39 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/29 18:12:35 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	print_updated_pos(t_player_data *player)
{
	printf("/* ----------------------------    print_updated_pos    -------------------------*/\n");
	printf ("player->posX = %.4f\n", player->posX);
	printf ("player->posY = %.4f\n", player->posY);
	printf ("player->planeX = %.4f\n", player->planeX);
	printf ("player->planeY = %.4f\n", player->planeY);
	printf ("player->dirX = %.4f\n", player->dirX);
	printf ("player->dirY = %.4f\n", player->dirY);
	printf("player->old_time = %.2f		player->time = %.2f		player->frameTime = %.2f	FPS = %.2f\n", player->old_time, player->time, player->frameTime, 1.0 / player->frameTime);
	printf ("player->moveSpeed = %.4f\n", player->moveSpeed);
	printf ("player->rotSpeed = %.4f\n", player->rotSpeed);
	printf("/* ------------------------------------------------------------------------------*/\n\n");



}

void	handle_move(t_player_data *player)
{
	if (player->kbrd.key_w)
	{
		// printf ("W pressed \n" );


		if (player->posX + player->dirX * player->moveSpeed >= 1 && player->posX + player->dirX * player->moveSpeed < player->mlx_data_pointer->map.cols
			&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + player->dirX * player->moveSpeed)] != '1')
			player->posX += player->dirX * player->moveSpeed;
		if (player->posY + player->dirY * player->moveSpeed >= 1 && player->posY + player->dirX * player->moveSpeed < player->mlx_data_pointer->map.rows
			&& player->mlx_data_pointer->map.grid[(int)(player->posY + player->dirY * player->moveSpeed)][(int)player->posX] != '1')
			player->posY += player->dirY * player->moveSpeed;
		// print_updated_pos(player);

	}

	if (player->kbrd.key_s)
	{
		// printf ("S pressed \n" );

		if (player->posX - player->dirX * player->moveSpeed >= 1 && player->posX - player->dirX * player->moveSpeed < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX - player->dirX * player->moveSpeed)] != '1')
			player->posX -= player->dirX * player->moveSpeed;
		if (player->posY - player->dirY * player->moveSpeed >= 1 && player->posY - player->dirX * player->moveSpeed < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY - player->dirY * player->moveSpeed)][(int)player->posX] != '1')
			player->posY -= player->dirY * player->moveSpeed;
		// print_updated_pos(player);

	}
	if (player->kbrd.key_a)
	{
		// printf ("A pressed \n" );

		// Move perpendicular to the right: use (dirY, -dirX)
		double strafeX = -player->dirY * player->moveSpeed;
		double strafeY = player->dirX * player->moveSpeed;

		if (player->posX + strafeX >= 1 && player->posX + strafeX < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + strafeX)] != '1')
			player->posX += strafeX;
		if (player->posY + strafeY >= 1 && player->posY + strafeY < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY + strafeY)][(int)player->posX] != '1')
			player->posY += strafeY;
		// print_updated_pos(player);
	}

	if (player->kbrd.key_d)
	{
		// Move perpendicular to the left: use (-dirY, dirX)
		// printf ("D pressed \n" );

		double strafeX = player->dirY * player->moveSpeed;
		double strafeY = -player->dirX * player->moveSpeed;

		if (player->posX + strafeX >= 1 && player->posX + strafeX < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + strafeX)] != '1')
			player->posX += strafeX;
		if (player->posY + strafeY >= 1 && player->posY + strafeY < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY + strafeY)][(int)player->posX] != '1')
			player->posY += strafeY;
		// print_updated_pos(player);
	}
	if (player->kbrd.key_right)
	{
		// printf ("right arrow pressed \n" );
		double	oldDirX = player->dirX;
		player->dirX = player->dirX * cos(- player->rotSpeed) - player->dirY * sin(- player->rotSpeed);
		player->dirY = oldDirX * sin(- player->rotSpeed) + player->dirY * cos(-player->rotSpeed);
		double	oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos( - player->rotSpeed) - player->planeY * sin( - player->rotSpeed);
		player->planeY = oldPlaneX * sin(- player->rotSpeed) + player->planeY * cos(- player->rotSpeed);
		// print_updated_pos(player);
	}

	if (player->kbrd.key_left)
	{
		// printf ("left arrow pressed \n" );
		double	oldDirX = player->dirX;
		player->dirX = player->dirX * cos(player->rotSpeed) - player->dirY * sin(player->rotSpeed);
		player->dirY = oldDirX * sin(player->rotSpeed) + player->dirY * cos(-player->rotSpeed);
		double	oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(player->rotSpeed) - player->planeY * sin(player->rotSpeed);
		player->planeY = oldPlaneX * sin(player->rotSpeed) + player->planeY * cos(player->rotSpeed);
		// print_updated_pos(player);
	}

}
