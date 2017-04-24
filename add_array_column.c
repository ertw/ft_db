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

char	***get_db(t_parse *meta, char **argv)
{
	char	***db;

	meta->rows = count_rows(argv[2]);
	meta->columns = count_columns(meta, argv[2]);
	db = fill_db(meta, argv[2]);
	return (db);
}

char	***add_field(t_parse *meta, char ***db, char *new_field)
{
	char	***new;
	int		x;
	int		y;

	new = (char ***)ft_memalloc(sizeof(char **) * (meta->columns + 2));
	new[meta->columns + 1] = 0;
	x = 0;
	y = 0;
	while (y < meta->columns + 1)
	{
		new[y] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 1));
		new[y][meta->rows] = 0;
		if (y == meta->columns)
		{
			while(x < meta->rows)
			{
				new[y][x] = ft_strdup(new_field);
				x++;
			}
		}
		while (x < meta->rows)
		{
			new[y][x] = ft_strdup(db[y][x]);
			x++;
		}
		new[y][x] = 0;
		x = 0;
		y++;
	}
	return (new);
}

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

}

void	add_array_column(t_parse *meta, char **argv)
{
	char	***db;
	char	***new;

	if ((access(argv[2], F_OK)) != -1)
	{
		ft_printf("[.green.Add Field.] - ");
		if (argv[3])
		{
			ft_printf("[.green.%s.]\n", argv[3]);
			db = get_db(meta, argv);
			new = add_field(meta, db, argv[3]);
			meta->columns++;
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