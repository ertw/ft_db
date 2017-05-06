/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/05/05 22:36:25 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void	cert_check(t_parse *meta)
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

static int	first_half(t_parse *meta, int c)
{
	int x;

	x = 0;
	if (c == 'l' && (x = 1))
		meta->opt_l = 1;
	else if (c == 'a' && (x = 1))
		meta->opt_a = 1;
	else if (c == 'r' && (x = 1))
		meta->opt_r = 1;
	else if (c == 'x' && (x = 1))
		meta->opt_x = 1;
	return (x);
}

static int	second_half(t_parse *meta, int c)
{
	int x;

	x = 0;
	if (c == 'c' && (x = 1))
		meta->opt_c = 1;
	else if (c == 'm' && (x = 1))
		meta->opt_m = 1;
	else if (c == 'd' && (x = 1))
		meta->opt_d = 1;
	else if (c == 'h' && (x = 1))
		meta->opt_h = 1;
	return (x);
}

static void	parse_args(int argc, char **argv, t_parse *meta)
{
	int	c;

	while ((c = getopt(argc, argv, "-acdhlrmx")) != -1)
	{
		if (c == 'l' || c == 'a' || c == 'r' || c == 'x')
			first_half(meta, c);
		else if (c == 'c' || c == 'm' || c == 'd' || c == 'h')
			second_half(meta, c);
		else
		{
			print_bad_opts(c);
			break ;
		}
	}
	cert_check(meta);
}

int			main(int argc, char **argv)
{
	t_parse meta;

	if (argc == 1)
		print_usage();
	else
		parse_args(argc, argv, &meta);
	if (meta.cert_present == 0 && argc > 1)
		user_login(&meta);
	if (meta.cert_present == 1 && argc > 1)
		dispatch_manager(&meta, argv);
	return (0);
}
