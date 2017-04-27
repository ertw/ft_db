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

char	***remove_column(t_parse *meta, char ***db, char *old_field)
{
	char	***new;
	int		x;
	int		y;
	int		z;

	new = (char ***)ft_memalloc(sizeof(char **) * (meta->columns));
	new[meta->columns - 1] = 0;
	x = 0;
	y = 0;
	z = 0;
	while (y < meta->columns)
	{
		if (y != atoi(old_field))
		{
			new[z] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 1));
			new[z][meta->rows] = 0;
			x = 0;
			while (x < meta->rows)
			{
				new[z][x] = ft_strdup(db[y][x]);
				x++;
			}
			z++;
		}
		y++;
	}
	return (new);
}

int 	validate_column(t_parse *meta, char	*input)
{
	int 	x;

	x = ft_atoi(input);
	if (x < 0 || x > meta->columns - 1)
		return (0);
	else if (meta->columns == 1)
		ft_putstr("Must have at least 1 column\n");
	return (1);
}

void	remove_array_column(t_parse *meta, char *source, char *content)
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