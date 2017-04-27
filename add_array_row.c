/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_array_row.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

char	***add_row(t_parse *meta, char ***db, char *content)
{
	char	***new;
	int		x;
	int		y;

	x = 0;
	y = 0;
	new = (char ***)ft_memalloc(sizeof(char **) * (meta->columns + 1));
	new[meta->columns] = 0;
	while (y < meta->columns)
	{
		new[y] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 2));
		new[y][meta->rows + 1] = 0;
		while (x < meta->rows)
		{
			new[y][x] = ft_strdup(db[y][x]);
			x++;
		}
		new[y][x] = ft_strdup(content);
		x = 0;
		y++;
	}
	return (new);
}

void	add_array_row(t_parse *meta, char *source, char *content)
{
	char	***db;
	char	***new;

	if ((access(source, F_OK)) != -1)
	{
		ft_printf("[.green.Add Row.] - ");
		if (content)
		{
			ft_printf("[.green.%s.]\n", content);
			db = get_db(meta, source);
			new = add_row(meta, db, content);
			meta->rows++;
			if (meta->opt_l == 1)
				display_db(meta, new, source);
			update_db(meta, new, source);
			delete_db(db);
			delete_db(new);
		}
		else
			ft_printf("[.red.Need argument.]\n");
	}
	else
		ft_printf("[.red.File error.]\n");
}