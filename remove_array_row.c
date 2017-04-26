/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_array_row.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

char	***remove_row(t_parse *meta, char ***db, char *new_row)
{
	char	***new;
	int		x;
	int		y;
	int		z;
	int		row;

	x = 0;
	y = 0;
	z = 0;
	row = ft_atoi(new_row);
	new = (char ***)ft_memalloc(sizeof(char **) * (meta->columns + 1));
	new[meta->columns] = 0;
	while (y < meta->columns)
	{
		new[y] = (char**)ft_memalloc(sizeof(char*) * (meta->rows));
		new[y][meta->rows - 1] = 0;
		while (x < meta->rows)
		{
			if (x != row)
			{
				new[y][z] = ft_strdup(db[y][x]);
				z++;
			}
			x++;
		}
		z = 0;
		x = 0;
		y++;
	}
	return (new);
}

int		validate_rows(t_parse *meta, char *row_number)
{
	int x;

	x = ft_atoi(row_number);
	if (x < 0 || x >= meta->rows)
		return (0);
	else if (meta->rows == 1)
	{
		ft_putstr("Need at least 1 row to be valid database.\n");
		return (0);
	}
	return (1);
}

void	remove_array_row(t_parse *meta, char **argv)
{
	char	***db;
	char	***new;

	if ((access(argv[2], F_OK)) != -1)
	{
		ft_printf("[.red.Remove Row.] - ");
		meta->rows = count_rows(argv[2]);
		if (validate_rows(meta, argv[3]))
		{
			ft_printf("[.red.%s.]\n", argv[3]);
			db = get_db(meta, argv[2]);
			new = remove_row(meta, db, argv[3]);
			meta->rows--;
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