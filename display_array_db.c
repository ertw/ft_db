/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_array_db.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	print_format_line(t_parse *meta, int pad)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < meta->columns)
	{
		while (y < pad + 3)
		{
			ft_putchar('-');
			y++;
		}
		y = 0;
		x++;
	}
	ft_putchar('-');
	ft_putchar('\n');
}

int		get_pad(char ***db)
{
	int x;
	int	y;
	int	test;
	int pad;

	x = 0;
	y = 0;
	pad = 0;
	while (db[y])
	{
		while (db[y][x])
		{
			if ((test = ft_strlen(db[y][x])) > pad)
				pad = test;
			x++;
		}
		x = 0;
		y++;
	}
	return (pad);
}

void	display_db(t_parse *meta, char ***db, char *name)
{
	int	x;
	int	y;
	int	pad;

	x = 0;
	y = 0;
	pad = get_pad(db);
	ft_printf("[.cyan.Display DB.] - [.cyan.%s.]\n", name);
	print_format_line(meta, pad);
	while (x < meta->rows)
	{
		while (y < meta->columns)
		{
			ft_printf("| %*s ", pad, db[y][x]);
			y++;
		}
		ft_putstr("|\n");
		print_format_line(meta, pad);
		y = 0;
		x++;
	}
}

void	display_array_db(t_parse *meta, char **argv)
{
	char	***db;

	if ((access(argv[2], F_OK)) != -1)
	{
		if (meta->opt_l == 1)
		{
			ft_printf("Option: [.cyan.l.]\n");
			meta->rows = count_rows(argv[2]);
			meta->columns = count_columns(argv[2]);
			db = fill_db(meta, argv[2]);
			display_db(meta, db, argv[2]);
			delete_db(db);
		}
	}
	else
		ft_putstr("File error\n");
}
