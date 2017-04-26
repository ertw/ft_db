/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_array_cell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		validate_row_column(t_parse *meta, char **argv)
{
	meta->x = atoi(argv[3]);
	meta->y = atoi(argv[4]);
	meta->columns = count_columns(argv[2]);
	meta->rows = count_rows(argv[2]);
	if (meta->x > meta->rows - 1 || meta->x < 0)
	{
		printf("Invalid user input: %d: Row must be between 0 and %d\n", meta->x, meta->rows - 1);
		return (0);
	}
	else if (meta->y > meta->columns - 1 || meta->y < 0)
	{
		printf("Invalid user input: %d: Column must be between 0 and %d\n", meta->y, meta->columns - 1);
		return (0);
	}
	return (1);
}

char	***modify_cell(t_parse *meta, char ***db, char **argv)
{
	char	***new;
	int 	x;
	int 	y;

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
			if (meta->x == x && meta->y == y)
				new[y][x] = ft_strdup(argv[5]);
			else
				new[y][x] = ft_strdup(db[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
	return (new);
}

void	modify_array_cell(t_parse *meta, char **argv)
{
	char	***db;
	char	***new;

	if ((access(argv[2], F_OK)) != -1)
	{
		ft_printf("[.yellow.Modify Field.] - ");
		if (argv[3] && argv[4] && argv[5] && 
			validate_row_column(meta, argv))
		{
			ft_printf("[.yellow.%s.]\n", argv[5]);
			db = get_db(meta, argv[2]);
			new = modify_cell(meta, db, argv);
			if (meta->opt_l == 1)
				display_db(meta, new, argv[2]);
			update_db(meta, new, argv[2]);
			delete_db(db);
			delete_db(new);
		}
		else
			ft_printf("Need argument (column number)\n");
	}
	else
		ft_printf("File error.]\n");
}