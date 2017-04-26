#include "ft_db.h"
#include <stdio.h>
#define C_TOKEN(node739) ((t_token*)node739->content)

enum e_type {t_open, t_close, t_string, t_name, t_age};

typedef struct		s_token
{
	enum e_type	type;
	char		*token;
}			t_token;

typedef struct		s_tree
{
	void		*content;
	struct s_tree	*left;
	struct s_tree	*right;
}			t_tree;

/* s-expression */
//((person)(((name)(Erik Williamson))((age)(29))))
//(person (name "Erik Williamson") (age 29))

/* tokenize s-expression string */
t_list		*tokenize(const char *str)
{
	t_list	*node = NULL;
	char	*close_paren = NULL;
	t_token	symbol;

	if (*str)
	{
		if (*str == '(' || *str == ')')
		{
			symbol.type = *str == '('
				? t_open
				: t_close;
			symbol.token = strndup(str, 1);
			node = ft_lstnew(&symbol, sizeof(symbol));
			node->next = tokenize(++str);
		}
		else
		{
			if (!(close_paren = strchr(str, ')')))
				printf("Error: ')' not found");
			symbol.type = t_string;
			symbol.token = strndup(str, close_paren - str);
			node = ft_lstnew(&symbol, sizeof(symbol));
			node->next = tokenize(close_paren);
		}
	}
	return (node);
}

/* create a new tree root */
t_tree		*tree_new(void const *content, size_t content_size)
{
	t_tree		*root;
	
	if (!(root = ft_memalloc(sizeof(root))))
		return (NULL);
	if (!(root->content = ft_memalloc(sizeof(content_size))))
		return (NULL);
	if (content)
		memcpy(root->content, content, content_size);
	else
		root->content = NULL;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

t_tree		*treeify_recursive(t_list *alst)
{
	t_tree		*root;

	if (!alst)
		return (NULL);
	if (C_TOKEN(alst)->type == t_open)
		;
	if (C_TOKEN(alst)->type == t_close)
		;
	root = ft_memalloc(sizeof(root));
	root->left = treeify_recursive(alst->next);
	root->right = treeify_recursive(alst->next);
	return (root);
}

t_tree		*treeify(t_list *head)
{
	t_tree		*root;
	t_list		*cursor;
	int		level = 0;

	cursor = head;
	while (cursor)
	{
		if (C_TOKEN(cursor)->type == t_open)
			level++;
		if (C_TOKEN(cursor)->type == t_open)
			level--;
	}
	return(root);
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
	ft_strdel(&((t_token*)content)->token);
	ft_memdel((void**)(t_token*)&content);
}

/* print out each node's word */
void			lst_node_print(t_list *node)
{
	if (C_TOKEN(node)->type == t_open || C_TOKEN(node)->type == t_close)
		printf(C_TOKEN(node)->type == t_open
				? "OPEN   : %s\n"
				: "CLOSE  : %s\n", C_TOKEN(node)->token);
	else
		printf("STRING : %s\n", C_TOKEN(node)->token);
}

int		main(void)
{
	t_list	*head;
	t_list	*cursor;
//	if (!(head = database_read(fopen("file.db", "r"))))
//		return (1);
	head = tokenize("((person)(((name)(Erik Williamson))((age)(29))))");
//	head = tokenize("((+)((1)(2)))");
//	while (cursor)
//	{
//		printf("%< c >\n", cursor->content);
//		cursor = cursor->next;
//	}
	ft_lstiter(head, lst_node_print);
	ft_lstdel(&head, lst_del_data);
}
