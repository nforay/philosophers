/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 20:09:41 by nforay            #+#    #+#             */
/*   Updated: 2020/10/25 23:15:44 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	taking(t_philosopher *phi)
{
	struct timeval	now;
	long long		timestamp;
	pthread_mutex_t	*fork;
	int				taken;

	taken = 0;
	while (taken < 2)
	{
		fork = ((phi->nbr + taken) % 2) ? phi->l_fork : phi->r_fork;
		if (pthread_mutex_lock(fork))
			return (-1);
		gettimeofday(&now, NULL);
		timestamp = (now.tv_sec - phi->params->time->tv_sec) * 1000 +
			(now.tv_usec - phi->params->time->tv_usec) * 0.001;
		printf("%lldms %ld has taken a fork\n", timestamp, phi->nbr);
		taken++;
	}
	phi->state = EATING;
	return (1);
}

static int	eating(t_philosopher *phi)
{
	struct timeval	now;
	long long		timestamp;

	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec - phi->params->time->tv_sec) * 1000 +
		(now.tv_usec - phi->params->time->tv_usec) * 0.001;
	printf("%lldms %ld is eating\n", timestamp, phi->nbr);
	usleep(1000 * phi->params->time_to_eat);
	if (pthread_mutex_unlock(phi->l_fork))
		return (-1);
	if (pthread_mutex_unlock(phi->r_fork))
		return (-1);
	phi->state = SLEEPING;
	return (1);
}

static int	sleeping(t_philosopher *phi)
{
	struct timeval	now;
	long long		timestamp;

	gettimeofday(&now, NULL);
	//phi->starvation = now + time_to_die
	timestamp = (now.tv_sec - phi->params->time->tv_sec) * 1000 +
		(now.tv_usec - phi->params->time->tv_usec) * 0.001;
	printf("%lldms %ld is sleeping\n", timestamp, phi->nbr);
	usleep(1000 * phi->params->time_to_sleep);
	phi->state = THINKING;
	return (1);
}

static int	thinking(t_philosopher *phi)
{
	struct timeval	now;
	long long		timestamp;

	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec - phi->params->time->tv_sec) * 1000 +
		(now.tv_usec - phi->params->time->tv_usec) * 0.001;
	printf("%lldms %ld is thinking\n", timestamp, phi->nbr);
	usleep(1000 * phi->params->time_to_eat);
	phi->state = TAKING;
	return (1);
}

void		*state_machine(void *arg)
{
	t_philosopher		*phi;
	static t_function	process[4] = {taking, eating, sleeping, thinking};

	phi = (t_philosopher*)arg;
	while (phi->state != DIED)
		process[phi->state](phi);
	printf("%ld died\n", phi->nbr);
	return (NULL);
}
