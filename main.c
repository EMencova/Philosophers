#include "./includes/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		check(ac, av);
		review_data(&table, av);
		init_data(&table);
		clean_all(&table);
	}
	else
		error_args();
	return (0);
}
