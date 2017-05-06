/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		error_control(t_parse *meta)
{
	if (meta->opt_c == 1 && meta->opt_r == 1)
	{
		ft_printf("[.blue.EZ-DB.]: Invalid Simultaneous Options: -cr.\n");
		return (0);
	}
	else if (meta->opt_a == 1 && meta->opt_x == 1)
	{
		ft_printf("[.blue.EZ-DB.]: Invalid Simultaneous Options: -ax.\n");
		return (0);
	}
	return (1);
}

void	dispatch_add(t_parse *meta, char **argv)
{
	ft_printf("Option: [.green.Add.]\n");
	if (meta->opt_c == 1)
		add_array_column(meta, argv[2], argv[3]);
	else if (meta->opt_r == 1)
		add_array_row(meta, argv[2], argv[3]);
}

void	dispatch_remove(t_parse *meta, char **argv)
{
	ft_printf("Option: [.red.Remove.]\n");
	if (meta->opt_c == 1)
		remove_array_column(meta, argv[2], argv[3]);
	else if (meta->opt_r == 1)
		remove_array_row(meta, argv[2], argv[3]);
}

void	dispatch_modify(t_parse *meta, char **argv)
{
	ft_printf("Option: [.yellow.Modify.]\n");
	modify_array_cell(meta, argv);
}

void	dispatch_manager(t_parse *meta, char **argv)
{
	if (!(error_control(meta)))
		return ;
	if (meta->opt_a == 1)
		dispatch_add(meta, argv);
	else if (meta->opt_x == 1)
		dispatch_remove(meta, argv);
	else if (meta->opt_m == 1)
		dispatch_modify(meta, argv);
	else if (meta->opt_d == 1)
		db_manager(meta);
	else if (meta->opt_l == 1)
		display_array_db(meta, argv);
	else if (meta->opt_h == 1)
		help();
}
