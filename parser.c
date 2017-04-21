#include "ft_db.h"
#include <stdio.h>

typedef struct		s_entry
{
	char		type[16];
	char		*entry;
}			t_entry;

//(()(object))
//((person)((name)(age)))
//(((Erik Williamson)(string))(object))
//(((Erik Williamson)(name))((29)(age))(person))
//(((Marco Kok)(name))((23)(age))(person))

void		get_token(char *str, char *match)
{
	int	i = 0;

	while (str[i])
	{

	}
}

t_list		*database_read(FILE *file)
{
	t_data		data;
	t_list		*node = NULL;
	
	if (fscanf(file, "%s %d", data.name, &data.age) == EOF)
		return (NULL);
	node = ft_lstnew(&data, sizeof(data));
	node->next = database_read(file);
	return (node);
}

int		main(void)
{
	t_list	*head;
	if (!(head = database_read(fopen("file.db", "r"))))
		return (1);
}
