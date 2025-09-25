/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:12:04 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/25 15:54:16 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

double	date_in_s(void)
{
	double		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("gettimeofday() returned -1\n");
		return (-1);
	}
	time = current_time.tv_sec + current_time.tv_usec / 1000000.0;
	return (time);
}

double	date_in_ms(void)
{
	double		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("gettimeofday() returned -1\n");
		return (-1);
	}
	time = (current_time.tv_sec * 1000.0) + (current_time.tv_usec / 1000.0);
	return (time);
}

t_tile	char_to_tile(char c)
{
	if (c == '0') return E_FLOOR;
	if (c == '1') return E_WALL;
	if (c == 'E') return E_EP;
	if (c == 'S') return E_SP;
	if (c == 'W') return E_WP;
	if (c == 'N') return E_NP;
	if (c == 'C') return E_EXTRA;

	return E_FLOOR; // Default fallback
}

void	print_map(t_map *map)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%c ", map->grid[i][j]);
		}
		printf("\n");
	}
}
