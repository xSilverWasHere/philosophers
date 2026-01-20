/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:31:00 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:32:19 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	order_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	long	ts;

	ts = current_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->state_mutex);
	if (check_death_locked(philo, ts))
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	return (0);
}

static int	take_first_fork(t_philo *philo, pthread_mutex_t *first)
{
	pthread_mutex_lock(first);
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d has taken a fork\n", current_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

static int	take_second_fork(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(second);
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d has taken a fork\n", current_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = NULL;
	second = NULL;
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	if (order_forks(philo, &first, &second))
		return (1);
	if (take_first_fork(philo, first))
		return (1);
	if (take_second_fork(philo, first, second))
		return (1);
	return (0);
}
