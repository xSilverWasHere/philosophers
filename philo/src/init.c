/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:53:33 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:34:05 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->forks)
		return (printf("error allocating memory for forks"));
	if (pthread_mutex_init(&data->print_mutex, NULL)
		|| pthread_mutex_init(&data->state_mutex, NULL))
		return (printf("error initializing mutex"));
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("error initializing fork mutex"));
		i++;
	}
	return (0);
}

static void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->nbr_philo];
		philos[i].meals_eaten = 0;
		philos[i].last_meal = data->start_time;
		i++;
	}
}

static int	run_simulation(t_data *data, t_philo *philos, pthread_t *threads,
		pthread_t monitor_thread)
{
	long	death_check_interval;

	death_check_interval = 1;
	if (pthread_create(&monitor_thread, NULL, monitor_deaths, data) != 0)
		return (cleanup(data, philos, threads, monitor_thread), 1);
	if (start_threads(data, philos, threads) != 0)
		return (cleanup(data, philos, threads, monitor_thread), 1);
	while (1)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (data->someone_died
			|| (data->must_eat > 0
				&& data->finished_eating == data->nbr_philo))
		{
			pthread_mutex_unlock(&data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->state_mutex);
		precise_sleep(death_check_interval);
	}
	cleanup(data, philos, threads, monitor_thread);
	return (0);
}

int	init_data(t_data *data)
{
	t_philo		*philos;
	pthread_t	*threads;
	pthread_t	monitor_thread;

	monitor_thread = 0;
	data->start_time = current_ms();
	data->finished_eating = 0;
	data->someone_died = 0;
	if (alloc_arrays(data, &philos, &threads) != 0)
		return (1);
	if (init_mutexes(data) != 0)
		return (cleanup(data, philos, threads, monitor_thread), 1);
	data->philos = philos;
	init_philos(data, philos);
	return (run_simulation(data, philos, threads, monitor_thread));
}
