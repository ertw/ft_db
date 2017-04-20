#include "ft_db.h"

int	cred_check(char *ptr, char *buff)
{
	int x;
	int start;

	x = 0;
	while (buff[x])
	{
		if (buff[x] == '$')
		{
			start = x + 1;
			if (ft_strdelic(ptr, buff + start, '\n'))
			{
				ft_strdel(&ptr);
				return (1);
			}
		}
		x++;
	}
	return (0);
}

int	handle_login(char *user, char *pass)
{
	int		fd;
	int		r;
	char	*ptr;
	char	buff[4000];

	fd = open("login.txt", O_RDONLY);
	r = read(fd, &buff, 3999);
	buff[r] = '\0';
	ptr = ft_strjoin(user, ">");
	ptr = ft_strxjoin(ptr, pass, 1);
	ptr = ft_strxjoin(ptr, "\n", 1);
	if ((cred_check(ptr, buff)))
		return (1);
	return (0);
}

int		login_certification(char *user, char *pass)
{
	int		x;
	FILE	*fd;
	time_t	current;

	x = 0;
	if ((handle_login(user, pass)) && (x = 1))
	{
		printf("Welcome to our database, %s.\n", user);
		fd = fopen("cert.ers", "w+");
		current = time(NULL);
		fprintf(fd, "$%s>%s\n%s", user, pass, asctime(gmtime(&current)));
	}
	else
		ft_putstr("Invalid username/Pass\n");
	return (x);
}

void	cert_check(t_parse *user)
{
	if ((access("cert.ers", F_OK)) != -1)
	{
		user->cert_present = 1;
		ft_putstr("Certificate Status: good\n");
	}
	else
	{
		user->cert_present = 0;
		ft_putstr("Certificate Status: meh\n");
	}
}

void	parse_args(int argc, char **argv, t_parse *meta)
{
	int	c;

	while ((c = getopt(argc, argv, "-l")) != -1)
	{
		if (c == 'l')
			meta->opt_l = 1;
		else
		{
			printf("EZ-DB: %c : invalid option\n", c);
			ft_putstr("usage: EZ-DB [-l] [...]\n");
			break ;
		}
	}
	cert_check(meta);
}

char	*get_pass()
{
	int 	x;
	char 	c;
	char	pass[100];

	x = 0;
	printf("Enter password: ");
	while ((scanf(" %c", &c) && c != '\n'))
	{
		pass[x] = c;
		x++;
	}
	pass[x] = '\0';
	return (ft_strdup(pass));
}

void	user_login(t_parse *meta)
{
	char	user[100];
	char 	*pass;

	printf("Enter username: ");
	scanf(" %s", user);
	pass = getpass("Enter pass: ");
	if ((login_certification(user, pass)))
		meta->cert_present = 1;
	ft_strdel(&pass);
}

int		main(int argc, char **argv)
{
	t_parse meta;

	if (argc == 1)
		ft_putstr("usage: EZ-DB [-l] [...]\n");
	else
		parse_args(argc, argv, &meta);
	if (meta.cert_present == 0)
		user_login(&meta);
	else
		direct_to_main_prog(&meta);
	return (0);
}