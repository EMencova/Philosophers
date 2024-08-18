#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>

typedef struct s_philo
{
	int				id;
	int				meals_count;
	long long		last_meal_time;
	bool			is_hungry;
	struct s_table	*table;
	pthread_t		thread;
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;
}	t_philo;

typedef struct s_table
{
	bool			print_msg;
	int				happy_philos;
	int				num_philos;
	int				meal_limit;
	long long		dying_time;
	long long		eating_time;
	long long		sleeping_time;
	long long		start;
	t_philo			*philos;
	pthread_mutex_t	*init_forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	happy;
	pthread_mutex_t	print;
}	t_table;

int			main(int ac, char **av);
long		ft_atoi(char *str);
long long	time_set(void);
void		check(int ac, char **av);
void		error_args(void);
void		review_data(t_table *table, char **av);
void		init_data(t_table *table);
void		*philo_life(void *args);
void		clean_all(t_table *table);
void		dinner_time(t_philo *philo);
void		time_death(t_table *table);
void		printer(long long t, t_philo *philo, char letter);
bool		help_to_die(t_table *table);

#endif

