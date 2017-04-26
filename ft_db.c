/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	cert_check(t_parse *meta)
{
	if ((access("cert.ers", F_OK)) != -1)
	{
		meta->cert_present = 1;
		ft_printf("Certificate Status: [.green.good.].\n");
	}
	else
	{
		meta->cert_present = 0;
		ft_printf("Certificate Status: [.red.meh.]. :[\n");
	}
}

void	parse_args(int argc, char **argv, t_parse *meta)
{
	int	c;

	while ((c = getopt(argc, argv, "-acdlrmx")) != -1)
	{
		if (c == 'l')
			meta->opt_l = 1;
		else if (c == 'a')
			meta->opt_a = 1;
		else if (c == 'r')
			meta->opt_r = 1;
		else if (c == 'x')
			meta->opt_x = 1;
		else if (c == 'c')
			meta->opt_c = 1;
		else if (c == 'm')
			meta->opt_m = 1;
		else if (c == 'd')
			meta->opt_d = 1;
		else
		{
			ft_printf("[.blue.EZ-DB.]: %c : [.red.invalid option.].\n", c);
			ft_printf("usage: [.blue.EZ-DB.] [-acdlrmx] [...]\n");
			break ;
		}
	}
	cert_check(meta);
}

int		main(int argc, char **argv)
{
	t_parse meta;

	if (argc == 1)
		ft_putstr("usage: [.blue.EZ-DB.] [-acdlrmx] [...]\n");
	else
		parse_args(argc, argv, &meta);
	if (meta.cert_present == 0 && argc > 1)
		user_login(&meta);
	if (meta.cert_present == 1 && argc > 1)
		dispatch_manager(&meta, argv);
	return (0);
}
