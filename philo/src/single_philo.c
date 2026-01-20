/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:32:00 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:34:05 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	single_philo_dies(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("0 %d has taken a fork\n", philo->id);
	philo->data->someone_died = 1;
	precise_sleep(philo->data->time_to_die);
	printf("%ld %d died\n", current_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(philo->left_fork);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philo == 1)
	{
		single_philo_dies(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_sleep(1);
	while (1)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		if (philo->data->someone_died
			|| (philo->data->must_eat > 0
				&& philo->data->finished_eating == philo->data->nbr_philo))
		{
			pthread_mutex_unlock(&philo->data->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->state_mutex);
		if (eat_phase(philo) || think_phase(philo) || sleep_phase(philo))
			break ;
	}
	return (NULL);
}
