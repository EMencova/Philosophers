#include "./includes/philo.h"

long	ft_atoi_check(char *str)
{
	long	nbr;

	nbr = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			printf("Error, negative number.\n");
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

void	error_args(void)
{
	printf("Error, wrong amount of arguments.\n");
	exit (1);
}

int	only_digits(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < ac)
	{
		if (av[j][i] == '-' || av[j][i] == '+')
			i++;
		while (av[j][i] != '\0')
		{
			if (av[j][i] < '0' || av[j][i] > '9')
			{
				printf("Error, only digits please.\n");
				exit (1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

void	is_negative(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		ft_atoi_check(av[i]);
		i++;
	}
}

void	check(int ac, char **av)
{
	only_digits(ac, av);
	is_negative(av);
}

