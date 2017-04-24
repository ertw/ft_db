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

	while ((c = getopt(argc, argv, "-alr")) != -1)
	{
		if (c == 'l')
			meta->opt_l = 1;
		else if (c == 'a')
			meta->opt_a = 1;
		else if (c == 'r')
			meta->opt_r = 1;
		else
		{
			ft_printf("[.blue.EZ-DB.]: %c : [.red.invalid option.].\n", c);
			ft_printf("usage: [.blue.EZ-DB.] [-al] [...]\n");
			break ;
		}
	}
	cert_check(meta);
}

void	dispatch_manager(t_parse *meta, char **argv)
{
	if (meta->opt_a == 1 && meta->opt_r == 1)
	{
		ft_printf("[.blue.EZ-DB.]: Invalid Simultaneous Options: -lr.\n");
		return ;
	}
	if (meta->opt_a == 1)
	{
		ft_printf("Option ->[.green.a.]<-\n");
		add_array_field(meta, argv);
	}
	else if (meta->opt_r == 1)
	{
		ft_printf("Option ->[.red.r.]<-\n");
		remove_array_field(meta, argv);
	}
	else if (meta->opt_l == 1)
		display_array_db(meta, argv);
}

int		main(int argc, char **argv)
{
	t_parse meta;

	if (argc == 1)
		ft_putstr("usage: [.blue.EZ-DB.] [-alr] [...]\n");
	else
		parse_args(argc, argv, &meta);
	if (meta.cert_present == 0 && argc > 1)
		user_login(&meta);
	if (meta.cert_present == 1 && argc > 1)
		dispatch_manager(&meta, argv);
	return (0);
}
