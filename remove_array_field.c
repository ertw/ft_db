/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_array_field.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/20 10:51:27 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

char	***remove_field(t_parse *meta, char ***db, char *old_field)
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
		if (y != atoi(old_field) - 1)
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

void	remove_array_field(t_parse *meta, char **argv)
{
	char	***db;
	char	***new;

	if ((access(argv[2], F_OK)) != -1)
	{
		ft_printf("[red.Remove Field.] - ");
		if (argv[3])
		{
			ft_printf("[.red.%s.]\n", argv[3]);
			db = get_db(meta, argv);
			new = remove_field(meta, db, argv[3]);
			meta->columns--;
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