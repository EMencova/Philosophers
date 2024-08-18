#include "./includes/philo.h"

void	printer(long long time, t_philo *philo, char letter)
{
	pthread_mutex_lock(&philo->table->print);
    time = time_set() - philo->table->start;
	if (letter == 'F' && philo->table->print_msg == true)
    {
        printf("%lld %d has taken a fork\n", time, philo->id);
        time = time_set() - philo->table->start;
    }
	if (letter == 'E' && philo->table->print_msg == true)
    {
        printf("%lld %d is eating\n", time, philo->id);
        time = time_set() - philo->table->start;
    }
	if (letter == 'S' && philo->table->print_msg == true)
	{
		pthread_mutex_unlock(&philo->table->print);
		printf("%lld %d is sleeping\n", time, philo->id);
		usleep(philo->table->sleeping_time * 1000);
        time = time_set() - philo->table->start;
		pthread_mutex_lock(&philo->table->print);
		if (philo->table->print_msg == true)
		{
			pthread_mutex_unlock(&philo->table->print);
            time = time_set() - philo->table->start;
			printf("%lld %d is thinking\n", time, philo->id);
			return ;
		}
		pthread_mutex_unlock(&philo->table->print);
		return ;
	}
	pthread_mutex_unlock(&philo->table->print);
}

void	time_death(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i != table->num_philos)
		{
			pthread_mutex_lock(&table->meal);
			if ((time_set() - table->philos[i].last_meal_time) \
				>= table->dying_time && table->philos[i].is_hungry == true)
			{
				pthread_mutex_unlock(&table->meal);
				pthread_mutex_lock(&table->print);
				table->print_msg = false;
				pthread_mutex_unlock(&table->print);
				printf("%lld %d died\n", \
				(time_set() - table->start), table->philos[i].id);
				break ;
			}
			pthread_mutex_unlock(&table->meal);
            i++;
		}
		if (help_to_die(table))
			break ;
	}
}

void	dinner_time(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_one);
	printer((time_set() - philo->table->start), philo, 'F');
	if (philo->table->num_philos == 1)
	{
		usleep(philo->table->dying_time * 1000);
		pthread_mutex_unlock(philo->fork_one);
		return ;
	}
	pthread_mutex_lock(philo->fork_two);
    printer((time_set() - philo->table->start), philo, 'F');
	printer((time_set() - philo->table->start), philo, 'E');
	philo->meals_count++;
	pthread_mutex_lock(&philo->table->meal);
	philo->last_meal_time = time_set();
	pthread_mutex_unlock(&philo->table->meal);
	usleep(philo->table->eating_time * 1000);
	pthread_mutex_unlock(philo->fork_one);
	pthread_mutex_unlock(philo->fork_two);
}

void	*philo_life(void *args)
{
	t_philo	*philo;

	philo = args;
	pthread_mutex_lock(&philo->table->meal);
	philo->last_meal_time = time_set();
	pthread_mutex_unlock(&philo->table->meal);
	while (philo->meals_count != philo->table->meal_limit)
	{
		pthread_mutex_lock(&philo->table->print);
		if (philo->table->print_msg == false)
		{
			pthread_mutex_unlock(&philo->table->print);
			break ;
		}
		pthread_mutex_unlock(&philo->table->print);
		dinner_time(philo);
		if (philo->meals_count != philo->table->meal_limit \
				&& philo->table->num_philos != 1)
			printer((time_set() - philo->table->start), philo, 'S');
	}
	philo->is_hungry = false;
	pthread_mutex_lock(&philo->table->meal);
	philo->table->happy_philos++;
	pthread_mutex_unlock(&philo->table->meal);
	return (NULL);
}

