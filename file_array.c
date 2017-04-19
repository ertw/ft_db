#include "ft_db.h"
#include <stdio.h>
#define NUM_ROWS 10
#define ERR_NO_SPACE 10

/* database format:
 * line1 col1\n
 * line2 col2\n
 * ...etc
 */

/* takes a database FILE and a function that will do something with it */
int		database_read(FILE *file, int (*action)(char *, int))
{
	size_t		bufsize = 0;
	char		*line;
	char		**splitstring;
	int		ret;

	while (getline(&line, &bufsize, file))
	{
		splitstring = ft_strsplit(line, ' ');
	}
	while (getdelim(&line, &bufsize, (int)' ', file) > 0)
	{
	}
}

/* takes a person, returns an age */
int		get_age(char *person, int age)
{

}

/* takes a person and age, returns a success / failure */
int		add_person(char *person, int age)
{

}

