#include "./includes/philo.h"

void	action(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->print, NULL);
	table->start = time_set();
	while (i < table->num_philos)
	{
		pthread_create(&table->philos[i].thread, NULL,
			&philo_life, &table->philos[i]);
        i++;
	}
	usleep((table->dying_time) * 1000);
	time_death(table);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	if (table->print_msg == true)
		printf("\n All Philos are satisfied \n");
}

t_philo	*init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc (sizeof(t_philo) * table->num_philos);
	while (i < table->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_count = 0;
		philo[i].is_hungry = true;
		philo[i].fork_one = &(table->init_forks[i]);
		philo[i].fork_two = &(table->init_forks[(i + 1) % table->num_philos]);
		if (i == 0)
		{
			philo[i].fork_one = &(table->init_forks[(i + 1) \
				% table->num_philos]);
			philo[i].fork_two = &(table->init_forks[i]);
		}
		philo[i].table = table;
        i++;
	}
	return (philo);
}

pthread_mutex_t	*init_forks(int num_philos)
{
	pthread_mutex_t	*init_forks;
	int				i;

	i = -1;
	init_forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	while (++i < num_philos)
		pthread_mutex_init(&init_forks[i], NULL);
	return (init_forks);
}

void	init_data(t_table *table)
{
	pthread_mutex_init(&table->happy, NULL);
	pthread_mutex_init(&table->meal, NULL);
	table->init_forks = init_forks(table->num_philos);
	table->philos = init_philos(table);
	action(table);
}

