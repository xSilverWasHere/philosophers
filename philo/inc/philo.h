/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-g <jpedro-g@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:12:06 by jpedro-g          #+#    #+#             */
/*   Updated: 2026/01/13 14:35:26 by jpedro-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nbr_philo;
	long			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				someone_died;
	int				must_eat;
	int				finished_eating;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	t_data			*data;
	long long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int		init_data(t_data *data);
long	current_ms(void);
void	precise_sleep(long ms);
void	*thread_function(void *arg);
int		alloc_arrays(t_data *data, t_philo **philos, pthread_t **threads);
int		check_stop(t_philo *philo);
int		check_death_locked(t_philo *philo, long ts);
void	update_meals(t_philo *philo);
int		is_numeric(const char *str);
int		pre_eat_check(t_philo *philo);
int		post_forks_check(t_philo *philo);
int		think_phase(t_philo *philo);
int		take_forks(t_philo *philo);
int		eat_phase(t_philo *philo);
int		sleep_phase(t_philo *philo);
void	*monitor_deaths(void *arg);
void	cleanup(t_data *data, t_philo *philos, pthread_t *threads,
			pthread_t monitor_thread);
int		start_threads(t_data *data, t_philo *philos, pthread_t *threads);

#endif
