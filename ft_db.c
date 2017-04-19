#include "ft_db.h"

int	handle_login(char **argv)
{
	int		login;
	char	*stream;

	stream = NULL;
	login = open("login.txt", O_RDONLY);
	while (get_next_line(login, &stream))
	{
		if ((ft_strncmp(stream, argv[1], ft_strlen(argv[1]))) == 0)
		{
			ft_strdel(&stream);
			get_next_line(login, &stream);
			if ((ft_strcmp(stream, argv[2])) == 0)
			{
				ft_strdel(&stream);
				return (1);
			}
			else
				break ;
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc < 3)
		ft_putstr("usage: EZ-DB [login] [pw]\n");
	else
	{
		if (handle_login(argv))
			ft_putstr("Welcome to our database, friend. :D~\n");
		else
			ft_putstr("Invalid username/Pass\n");
	}
	return (0);
}
