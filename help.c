/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/05/05 22:36:49 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	print_usage(void)
{
	ft_printf("usage: [.blue.EZ-DB.] [-acdlrmx] [ ... ]\n");
}

void	print_bad_opts(char c)
{
	print_usage();
	ft_printf("[.blue.EZ-DB.]: %c : [.red.invalid option.].\n", c);
}

void	help(void)
{
	ft_putstr("\n");
	ft_printf("Welcome to [.blue.EZ-DB.] manager.\n");
	ft_printf("-----------------------------------------------------------\n");
	ft_printf("* usage options: -acdlrmx\n\n");
	ft_printf("* [.magenta.d.]: [.magenta.display mode.] - the front end.\n");
	ft_printf("* [.cyan.l.]: [.cyan.list mode.] - displays a db\n");
	ft_printf("* [.green.a.]: [.green.add mode.] - add a row or column\n");
	ft_printf("     example: ./ft_db -ar family.db ten_brothers\n");
	ft_printf("* [.red.x.]: [.red.subtract mode.] - subtract row or column\n");
	ft_printf("     example: ./ft_db -xc family.db 4\n");
	ft_printf("* c: column mode - use in conjunction with a and x modes.\n");
	ft_printf("* r: row mode - same as columns\n");
	ft_printf("* note: viable database must have one row and one column.\n");
	ft_printf("-----------------------------------------------------------\n");
}
