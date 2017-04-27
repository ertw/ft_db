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
	char		***new;
	t_triplet	*triplet;
	int			row;

	triplet = init_triplet(0, 0, 0);
	row = ft_atoi(new_row);
	new = (char ***)ft_memalloc(sizeof(char **) * (meta->columns + 1));
	new[meta->columns] = 0;
	while (Y < meta->columns)
	{
		new[Y] = (char**)ft_memalloc(sizeof(char*) * (meta->rows));
		new[Y][meta->rows - 1] = 0;
		while (X < meta->rows)
		{
			if (X != row)
				new[Y][Z++] = ft_strdup(db[Y][X]);
			X++;
		}
		Z = 0;
		X = 0;
		Y++;
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

void	remove_array_row(t_parse *meta, char *source, char *content)
{
	char	***db;
	char	***new;

	if ((access(source, F_OK)) != -1)
	{
		ft_printf("[.red.Remove Row.] - ");
		meta->rows = count_rows(source);
		if (validate_rows(meta, content))
		{
			ft_printf("[.red.%s.]\n", content);
			db = get_db(meta, source);
			new = remove_row(meta, db, content);
			meta->rows--;
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
