/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_array_column.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	delete_db(char ***db)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (db[y])
	{
		while (db[y][x])
		{
			if (db[y][x])
				ft_strdel(&db[y][x]);
			x++;
		}
		if (db[y][x])
			ft_strdel(&db[y][x]);
		if (db[y])
			ft_memdel((void*)&db[y]);
		x = 0;
		y++;
	}
	if (db[y])
		ft_memdel((void*)&db[y]);
	if (db)
		ft_memdel((void*)&db);
}

char	***get_db(t_parse *meta, char *source)
{
	char	***db;

	meta->rows = count_rows(source);
	meta->columns = count_columns(source);
	db = fill_db(meta, source);
	return (db);
}

char	***add_column(t_parse *meta, char ***db, char *new_field)
{
	char		***new;
	t_triplet	*triplet;

	triplet = init_triplet(0, 0, 0);
	new = (char ***)ft_memalloc(sizeof(char **) * (meta->columns + 2));
	new[meta->columns + 1] = 0;
	while (Y < meta->columns + 1)
	{
		new[Y] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 1));
		new[Y][meta->rows] = 0;
		if (Y == meta->columns)
		{
			while (X < meta->rows)
				new[Y][X++] = ft_strdup(new_field);
		}
		while (X < meta->rows)
		{
			new[Y][X] = ft_strdup(db[Y][X]);
			X++;
		}
		new[Y++][X] = 0;
		X = 0;
	}
	return (new);
}

void	add_column_gui(t_parse *meta, char *source)
{
	char	buff[100];

	printf("Please type in content for new column\n");
	scanf("%s", buff);
	add_array_column(meta, source, buff);
	db_manipulator(meta, source);
}

void	add_array_column(t_parse *meta, char *source, char *content)
{
	char	***db;
	char	***new;

	if ((access(source, F_OK)) != -1)
	{
		ft_printf("[.green.Add Column.] - ");
		if (content)
		{
			ft_printf("[.green.%s.]\n", content);
			db = get_db(meta, source);
			new = add_column(meta, db, content);
			meta->columns++;
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
