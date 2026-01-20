/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:31:00 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:32:19 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_philo *philo)
{
	if (philo->data->must_eat > 0
		&& philo->meals_eaten >= philo->data->must_eat)
		return (1);
	return (0);
}

int	check_death_locked(t_philo *philo, long ts)
{
	if (philo->data->someone_died)
		return (1);
	if (current_ms() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died\n", ts, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		philo->data->someone_died = 1;
		return (1);
	}
	return (0);
}

int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
