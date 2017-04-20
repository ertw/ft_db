#include "./libft/includes/libft.h"
#include <fcntl.h>
#include <termios.h>

typedef struct 		s_parse
{
	int				opt_l;
	int				cert_present;
}					t_parse;

typedef struct		s_data
{
	char			name[128];
	int				age;
}					t_data;

int					ft_strdelic(char *s1, char *s2, char delim);
