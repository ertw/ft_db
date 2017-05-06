/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	update_db(t_parse *meta, char ***db, char *file_name)
{
	int x;
	int y;

	x = 0;
	y = 0;
	meta->fd = fopen(file_name, "w+");
	while (x < meta->rows)
	{
		while (y < meta->columns)
		{
			fprintf(meta->fd, "%s", db[y][x]);
			if (y + 1 < meta->columns)
				fprintf(meta->fd, " ");
			y++;
		}
		fprintf(meta->fd, "\n");
		y = 0;
		x++;
	}
	fclose(meta->fd);
}
