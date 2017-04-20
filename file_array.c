#include "ft_db.h"
#include <stdio.h>
#define NUM_ROWS 10
#define ERR_NO_SPACE 10
#define C_DATA(node289) ((t_data*)node289->content)

/* database format:
 * line1 col1\n
 * line2 col2\n
 * ...etc
 */

/* takes a database FILE and a function that will do something with it */
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

t_list			*find_name(t_list *alst, char *name)
{
	t_list		*node = NULL;
	t_data		data;

	if (!alst)
		return (NULL);
	if (!(strcmp(C_DATA(alst)->name, name)))
	{
		memcpy(&data, C_DATA(alst), sizeof(data));
		node = ft_lstnew(&data, sizeof(data));
		node->next = find_name(alst->next, name);
	}
}

/* print each node */
void			lst_node_print(t_list *node)
{
	printf("%s %d\n", C_DATA(node)->name, C_DATA(node)->age);
}

/* delete each list node */
void			lst_del_data(void *content, size_t sizeofcontent)
{
	if (!sizeofcontent)
	{
		;
	}
	ft_memdel((void**)(t_data*)&content);
}

int		main(void)
{
	t_list	*head;
	t_list	*sorted;
	t_list	*cursor;

	if (!(head = database_read(fopen("file.db", "r"))))
		return (1);
	sorted = find_name(head, "mkok");
	cursor = sorted;
	while (cursor)
	{
		lst_node_print(cursor);
		cursor = cursor->next;
	}
//	ft_lstiter(sorted, lst_node_print);
	ft_lstdel(&head, lst_del_data);
	ft_lstdel(&sorted, lst_del_data);
}

///* takes a person, returns an age */
//int		get_age(char *person, int age)
//{
//	if (!(strcmp()))
//}

///* takes a person and age, returns a success / failure */
//int		add_person(char *person, int age)
//{
//
//}
