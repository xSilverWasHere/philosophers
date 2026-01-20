/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:26:21 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 12:13:00 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	precise_sleep(long ms)
{
	long	sleep_time;

	sleep_time = ms * 1000;
	usleep(sleep_time);
}

static int	parse_args(t_data *data, int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf("invalid args! Usage: ./philo nbr_philo time_to_die "
				"time_to_eat time_to_sleep (& optionally) nbr_times_must_eat"));
	while (i < ac)
	{
		if (!is_numeric(av[i]))
			return (printf("Error: must be a positive number\n"));
		i++;
	}
	data->nbr_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->must_eat = atoi(av[5]);
	else
		data->must_eat = -1;
	if (data->nbr_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->must_eat <= 0))
		return (printf("please insert values higher than 0"));
	return (0);
}

int	alloc_arrays(t_data *data, t_philo **philos, pthread_t **threads)
{
	*philos = malloc(sizeof(t_philo) * data->nbr_philo);
	*threads = malloc(sizeof(pthread_t) * data->nbr_philo);
	if (!*philos || !*threads)
		return (printf("error allocating memory for philos or threads"));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_args(&data, ac, av) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (1);
	return (0);
}
