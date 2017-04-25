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

char	***add_row(t_parse *meta, char ***db, char *new_row)
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
		new[y] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 1));
		new[y][meta->rows] = 0;
		while (x < meta->rows)
		{
			new[y][x] = ft_strdup(db[y][x]);
			x++;
		}
		new[y][x] = ft_strdup(new_row);
		x++;
		new[y][x] = 0;
		x = 0;
		y++;
	}
	return (new);
}

void	add_array_row(t_parse *meta, char **argv)
{
	char	***db;
	char	***new;

	if ((access(argv[2], F_OK)) != -1)
	{
		ft_printf("[.green.Add Row.] - ");
		if (argv[3])
		{
			ft_printf("[.green.%s.]\n", argv[3]);
			db = get_db(meta, argv);
			new = add_row(meta, db, argv[3]);
			meta->rows++;
			if (meta->opt_l == 1)
				display_db(meta, new, argv[2]);
			update_db(meta, new, argv[2]);
			delete_db(db);
			delete_db(new);
		}
		else
			ft_printf("[.red.Need argument.]\n");
	}
	else
		ft_printf("[.red.File error.]\n");
}