/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:47:58 by tjacquel          #+#    #+#             */
/*   Updated: 2025/09/27 17:49:43 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
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

int render_empty_sqr(t_img *img, t_sqr sqr)
{
	int	i;
	int j;

	i = sqr.y;
	while (i < sqr.y + sqr.side)
	{
		j = sqr.x;
		while (j < sqr.x + sqr.side)
		{
			// Only draw pixels on the border (edges)
			if (i == sqr.y || i == sqr.y + sqr.side - 1 ||
				j == sqr.x || j == sqr.x + sqr.side - 1)
				img_pix_put(img, j, i, sqr.color);
			j++;
		}
		i++;
	}
	return (0);
}

int render_sqr(t_img *img, t_sqr sqr)
{
	int	i;
	int j;

	i = sqr.y;
	while (i < sqr.y + sqr.side)
	{
		j = sqr.x;
		while (j < sqr.x + sqr.side)
				img_pix_put(img, j++, i, sqr.color);
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