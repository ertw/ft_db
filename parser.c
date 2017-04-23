#include "ft_db.h"
#include <stdio.h>
#define C_ATOM(node739) ((t_atom*)node739->content)

enum e_type {t_paren, t_string, t_name, t_age};

typedef struct		s_atom
{
	enum e_type	type;
	char		*atom;
}			t_atom;

/* s-expression */
//((person)(((name)(Erik Williamson))((age)(29))))

t_list		*tokenize(char *str)
{
	t_list	*node = NULL;
	char	*close_paren = NULL;
	t_atom	symbol;

	if (*str)
	{
		if (*str == '(' || *str == ')')
		{
			symbol.type = t_paren;
			symbol.atom = strndup(str, 1);
			node = ft_lstnew(&symbol, sizeof(symbol));
			node->next = tokenize(++str);
		}
		else
		{
			if (!(close_paren = strchr(str, ')')))
				printf("Error: ')' not found");
			symbol.type = t_string;
			symbol.atom = strndup(str, close_paren - str);
			node = ft_lstnew(&symbol, sizeof(symbol));
			node->next = tokenize(close_paren);
		}
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

/* delete each list node */
void			lst_del_data(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_strdel(&((t_atom*)content)->atom);
	ft_memdel((void**)(t_atom*)&content);
}

/* print out each node's word */
void			lst_node_print(t_list *node)
{
	if (C_ATOM(node)->type == t_paren)
		printf("PAREN : %s\n", C_ATOM(node)->atom);
	else
		printf("STRING : %s\n", C_ATOM(node)->atom);
}

int		main(void)
{
	t_list	*head;
	t_list	*cursor;
//	if (!(head = database_read(fopen("file.db", "r"))))
//		return (1);
	head = tokenize("((person)(((name)(Erik Williamson))((age)(29))))");
//	while (cursor)
//	{
//		printf("%< c >\n", cursor->content);
//		cursor = cursor->next;
//	}
	ft_lstiter(head, lst_node_print);
	ft_lstdel(&head, lst_del_data);
}
