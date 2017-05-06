/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_array_column.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/20 10:51:27 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

t_triplet	*init_triplet(int x, int y, int z)
{
	t_triplet	*triplet;

	triplet = ft_memalloc(sizeof(triplet));
	triplet->x = x;
	triplet->y = y;
	triplet->z = z;
	return (triplet);
}

char		***remove_column(t_parse *meta, char ***db, char *old_field)
{
	char		***new;
	t_triplet	*triplet;

	triplet = init_triplet(0, 0, 0);
	new = (char ***)ft_memalloc(sizeof(char **) * (meta->columns));
	new[meta->columns - 1] = 0;
	while (Y < meta->columns)
	{
		if (Y != atoi(old_field))
		{
			new[Z] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 1));
			new[Z][meta->rows] = 0;
			X = 0;
			while (X < meta->rows)
			{
				new[Z][X] = ft_strdup(db[Y][X]);
				X++;
			}
			Z++;
		}
		Y++;
	}
	ft_memdel((void*)&triplet);
	return (new);
}

void		remove_column_gui(t_parse *meta, char *source)
{
	char	buff[100];

	printf("Please type in column number to remove [0 - %d]\n",
			meta->columns - 1);
	scanf("%s", buff);
	remove_array_column(meta, source, buff);
	db_manipulator(meta, source);
}

int			validate_column(t_parse *meta, char *input)
{
	int		x;

	x = ft_atoi(input);
	if (x < 0 || x > meta->columns - 1)
		return (0);
	else if (meta->columns == 1)
		ft_putstr("Must have at least 1 column\n");
	return (1);
}

void		remove_array_column(t_parse *meta, char *source, char *content)
{
	char	***db;
	char	***new;

	if ((access(source, F_OK)) != -1)
	{
		ft_printf("[.red.Remove Field.] - ");
		meta->columns = count_columns(source);
		if (validate_column(meta, content))
		{
			ft_printf("[.red.%s.]\n", content);
			db = get_db(meta, source);
			new = remove_column(meta, db, content);
			meta->columns--;
			if (meta->opt_l == 1)
				display_db(meta, new, source);
			update_db(meta, new, source);
			delete_db(db);
			delete_db(new);
		}
		else
			ft_printf("Need argument (column number)\n");
	}
	else
		ft_printf("File error.]\n");
}
