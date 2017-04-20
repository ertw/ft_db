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
			printf("ptr: %s | buff + start: %s\n", ptr, buff + start + 1);
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

int	handle_login(char **argv)
{
	int		fd;
	int		r;
	char	*ptr;
	char	buff[4000];

	fd = open("login.txt", O_RDONLY);
	r = read(fd, &buff, 3999);
	buff[r] = '\0';
	ptr = ft_strjoin(argv[1], ">");
	ptr = ft_strxjoin(ptr, argv[2], 1);
	ptr = ft_strxjoin(ptr, "\n", 1);
	if ((cred_check(ptr, buff)))
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc < 3)
		ft_putstr("usage: EZ-DB [login] [pw]\n");
	else
	{
		if (handle_login(argv))
			printf("Welcome to our database, %s.\n", argv[1]);
		else
			ft_putstr("Invalid username/Pass\n");
	}
	return (0);
}
