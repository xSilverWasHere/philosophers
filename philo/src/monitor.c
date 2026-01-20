/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:30:00 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:34:05 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_deaths(t_data *data)
{
	int		i;
	long	ts;

	i = 0;
	while (i < data->nbr_philo)
	{
		ts = current_ms() - data->start_time;
		if (current_ms() - data->philos[i].last_meal
			> data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", ts, data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			data->someone_died = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_deaths(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
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
		if (check_philo_deaths(data))
		{
			pthread_mutex_unlock(&data->state_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->state_mutex);
		precise_sleep(1);
	}
	return (NULL);
}
