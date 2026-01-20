/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:46:51 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:34:05 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	pre_eat_check(t_philo *philo)
{
	long	now;
	long	ts;

	pthread_mutex_lock(&philo->data->state_mutex);
	now = current_ms();
	ts = now - philo->data->start_time;
	if (check_death_locked(philo, ts))
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (0);
}

int	post_forks_check(t_philo *philo)
{
	long	now;
	long	ts;

	pthread_mutex_lock(&philo->data->state_mutex);
	now = current_ms();
	ts = now - philo->data->start_time;
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		unlock_forks(philo);
		return (1);
	}
	if (check_death_locked(philo, ts))
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		unlock_forks(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is eating\n", ts, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->last_meal = now;
	update_meals(philo);
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (0);
}
