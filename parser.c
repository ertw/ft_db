#include "ft_db.h"
#include <stdio.h>

enum e_types {t_paren, t_string};

typedef struct		s_entry
{
	char		type[16];
	char		*entry;
}			t_entry;

/* s-expression */
//((person)(((name)(Erik Williamson))((age)(29))))

t_list		*tokenize(char *str)
{
	int	i = 0;
	t_list	*node = NULL;
	char	*close_paren;
	char	*tmp;

	if (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			node = ft_lstnew(&str[i], sizeof(str[i]));
			return (node->next = tokenize(++str));
		}
		else
		{
			if (!(close_paren = strchr(str, ')')))
				printf("Error: ')' not found");
			tmp = strndup(str, close_paren - str);
			node = ft_lstnew(&tmp, sizeof(tmp));
			return (node->next = tokenize(++str));
		}
	}
	return (NULL);
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
//	if (!(head = database_read(fopen("file.db", "r"))))
//		return (1);
	head = tokenize("((person)(((name)(Erik Williamson))((age)(29))))");
}
