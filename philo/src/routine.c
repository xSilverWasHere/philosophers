/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:45:20 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:32:19 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think_phase(t_philo *philo)
{
	long	now;
	long	ts;

	now = current_ms();
	ts = now - philo->data->start_time;
	pthread_mutex_lock(&philo->data->state_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death_locked(philo, ts))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	printf("%ld %d is thinking\n", ts, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->state_mutex);
	precise_sleep(1);
	return (0);
}

int	eat_phase(t_philo *philo)
{
	if (pre_eat_check(philo))
		return (1);
	if (take_forks(philo))
		return (1);
	if (post_forks_check(philo))
		return (1);
	precise_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	sleep_phase(t_philo *philo)
{
	long	now;
	long	ts;

	now = current_ms();
	ts = now - philo->data->start_time;
	pthread_mutex_lock(&philo->data->state_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_death_locked(philo, ts))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	printf("%ld %d is sleeping\n", ts, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->state_mutex);
	precise_sleep(philo->data->time_to_sleep);
	return (0);
}

void	update_meals(t_philo *philo)
{
	philo->meals_eaten++;
	if (philo->data->must_eat > 0
		&& philo->meals_eaten == philo->data->must_eat)
		philo->data->finished_eating++;
	if (philo->data->finished_eating == philo->data->nbr_philo)
		philo->data->someone_died = 1;
}
