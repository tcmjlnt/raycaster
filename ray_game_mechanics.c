/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_game_mechanics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:10:39 by tjacquel          #+#    #+#             */
/*   Updated: 2025/10/01 19:59:21 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	print_ray_info(t_player_data *player, int x, FILE *fp)
{
		fprintf(fp, "		Ray[%d]->mapX =			%d			mapY =			%d\n", x, player->mapX, player->mapY);
		fprintf(fp, "		Ray[%d]->rayDirX =		%.4f		rayDirY =		%.4f\n", x, player->rayDirX, player->rayDirY);
		fprintf(fp, "		Ray[%d]->deltaDistX =	%.4f		deltaDistY =	%.4f\n", x, player->deltaDistX, player->deltaDistY);
		fprintf(fp, "		Ray[%d]->sideDistX =		%.4f		sideDistY =		%.4f\n", x, player->sideDistX, player->sideDistY);
		fprintf(fp, "		Ray[%d]->stepX =			%d			stepY =			%d		 hit = %d, side = %d, perpWallDist = %.4f\n",
							x, player->stepX, player->stepY, player->hit, player->side, player->perpWallDist);




}

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

	if (player->game_init)
		player->game_init = false;

}

void	handle_move(t_player_data *player)
{
	if (player->kbrd.key_w)
	{
		printf ("W pressed \n" );


		if (player->posX + player->dirX * player->moveSpeed >= 1 && player->posX + player->dirX * player->moveSpeed < player->mlx_data_pointer->map.cols
			&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + player->dirX * player->moveSpeed)] != '1')
			player->posX += player->dirX * player->moveSpeed;
		if (player->posY + player->dirY * player->moveSpeed >= 1 && player->posY + player->dirX * player->moveSpeed < player->mlx_data_pointer->map.rows
			&& player->mlx_data_pointer->map.grid[(int)(player->posY + player->dirY * player->moveSpeed)][(int)player->posX] != '1')
			player->posY += player->dirY * player->moveSpeed;
		print_updated_pos(player);
		player->print_debug = true;

	}

	if (player->kbrd.key_s)
	{
		printf ("S pressed \n" );

		if (player->posX - player->dirX * player->moveSpeed >= 1 && player->posX - player->dirX * player->moveSpeed < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX - player->dirX * player->moveSpeed)] != '1')
			player->posX -= player->dirX * player->moveSpeed;
		if (player->posY - player->dirY * player->moveSpeed >= 1 && player->posY - player->dirX * player->moveSpeed < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY - player->dirY * player->moveSpeed)][(int)player->posX] != '1')
			player->posY -= player->dirY * player->moveSpeed;
		print_updated_pos(player);
		player->print_debug = true;


	}
	if (player->kbrd.key_d)
	{
		printf ("A pressed \n" );

		// Move perpendicular to the right: use (dirY, -dirX)
		double strafeX = -player->dirY * player->moveSpeed;
		double strafeY = player->dirX * player->moveSpeed;

		if (player->posX + strafeX >= 1 && player->posX + strafeX < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + strafeX)] != '1')
			player->posX += strafeX;
		if (player->posY + strafeY >= 1 && player->posY + strafeY < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY + strafeY)][(int)player->posX] != '1')
			player->posY += strafeY;
		print_updated_pos(player);
		player->print_debug = true;

	}

	if (player->kbrd.key_a)
	{
		// Move perpendicular to the left: use (-dirY, dirX)
		printf ("S pressed \n" );

		double strafeX = player->dirY * player->moveSpeed;
		double strafeY = -player->dirX * player->moveSpeed;

		if (player->posX + strafeX >= 1 && player->posX + strafeX < player->mlx_data_pointer->map.cols
				&& player->mlx_data_pointer->map.grid[(int)player->posY][(int)(player->posX + strafeX)] != '1')
			player->posX += strafeX;
		if (player->posY + strafeY >= 1 && player->posY + strafeY < player->mlx_data_pointer->map.rows
				&& player->mlx_data_pointer->map.grid[(int)(player->posY + strafeY)][(int)player->posX] != '1')
			player->posY += strafeY;
		print_updated_pos(player);
		player->print_debug = true;

	}
	if (player->kbrd.key_left)
	{
		printf ("left arrow pressed \n" );
		//	Matrice de rotation 2D
		double	oldDirX = player->dirX;
		player->dirX = player->dirX * cos(- player->rotSpeed) - player->dirY * sin(- player->rotSpeed);
		player->dirY = oldDirX * sin(- player->rotSpeed) + player->dirY * cos(-player->rotSpeed);

		//	Matrice de rotation 2D
		double	oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos( - player->rotSpeed) - player->planeY * sin( - player->rotSpeed);
		player->planeY = oldPlaneX * sin(- player->rotSpeed) + player->planeY * cos(- player->rotSpeed);
		print_updated_pos(player);
		player->print_debug = true;

	}

	if (player->kbrd.key_right)
	{
		printf ("right arrow pressed \n" );
		//	Matrice de rotation 2D
		double	oldDirX = player->dirX;
		player->dirX = player->dirX * cos(player->rotSpeed) - player->dirY * sin(player->rotSpeed);
		player->dirY = oldDirX * sin(player->rotSpeed) + player->dirY * cos(player->rotSpeed);

		//	Matrice de rotation 2D
		double	oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(player->rotSpeed) - player->planeY * sin(player->rotSpeed);
		player->planeY = oldPlaneX * sin(player->rotSpeed) + player->planeY * cos(player->rotSpeed);
		print_updated_pos(player);
		player->print_debug = true;

	}

}
