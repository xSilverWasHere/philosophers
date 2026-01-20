/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:32:00 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:35:11 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_threads(t_data *data, pthread_t *threads,
		pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

static void	cleanup_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->state_mutex);
}

void	cleanup(t_data *data, t_philo *philos, pthread_t *threads,
		pthread_t monitor_thread)
{
	cleanup_threads(data, threads, monitor_thread);
	cleanup_mutexes(data);
	free(threads);
	free(philos);
	free(data->forks);
}

int	start_threads(t_data *data, t_philo *philos, pthread_t *threads)
{
	int	i;
	int	result;

	i = 0;
	while (i < data->nbr_philo)
	{
		result = pthread_create(&threads[i], NULL, thread_function, &philos[i]);
		if (result != 0)
			return (printf("error creating thread"));
		i++;
	}
	return (0);
}
