#include "./includes/philo.h"

void	clean_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
		pthread_mutex_destroy(&table->init_forks[i++]);
	free (table->init_forks);
	free (table->philos);
}

bool	help_to_die(t_table *table)
{
	pthread_mutex_lock(&table->meal);
	if (table->print_msg == false || \
		table->happy_philos == table->num_philos)
	{
		pthread_mutex_unlock(&table->meal);
		return (true);
	}
	pthread_mutex_unlock(&table->meal);
	return (false);
}

long long	time_set(void)
{
	struct timeval	tv;
	long long		ms_time;

	gettimeofday(&tv, NULL);
	ms_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms_time);
}

long	ft_atoi(char *str)
{
	long	nbr;

	nbr = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			printf("Error, negative number.");
			exit(1);
		}
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return ((long)nbr);
}

void	review_data(t_table *table, char **av)
{
	table->print_msg = true;
	table->happy_philos = 0;
	table->num_philos = ft_atoi(av[1]);
	table->dying_time = ft_atoi(av[2]);
	table->eating_time = ft_atoi(av[3]);
	table->sleeping_time = ft_atoi(av[4]);
	table->meal_limit = -1;
	if (table->dying_time < 60 || table->eating_time < 60
		|| table->sleeping_time < 60)
	{
		printf("Use bigger timestamps than 60ms.\n");
		exit(1);
	}
	if (av[5])
		table->meal_limit = ft_atoi(av[5]);
}

