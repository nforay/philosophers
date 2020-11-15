/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 20:09:41 by nforay            #+#    #+#             */
/*   Updated: 2020/11/15 18:14:45 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	taking(t_philosopher *phi)
{
	sem_wait(phi->params->forks);
	print_status(phi, phi->nbr, " has taken a fork\n", 21);
	sem_wait(phi->params->forks);
	print_status(phi, phi->nbr, " has taken a fork\n", 21);
	phi->state = EATING;
	return (phi->alive);
}

static int	eating(t_philosopher *phi)
{
	print_status(phi, phi->nbr, " is eating\n", 14);
	phi->starvation = gettime_us() + phi->params->time_to_die * 1000;
	phi->meals_eaten++;
	usleep(1000 * phi->params->time_to_eat);
	sem_post(phi->params->forks);
	sem_post(phi->params->forks);
	if (phi->meals_eaten == phi->params->nbr_of_meals)
		return (0);
	phi->state = SLEEPING;
	return (phi->alive);
}

static int	sleeping(t_philosopher *phi)
{
	print_status(phi, phi->nbr, " is sleeping\n", 16);
	usleep(1000 * phi->params->time_to_sleep);
	phi->state = THINKING;
	return (phi->alive);
}

static int	thinking(t_philosopher *phi)
{
	print_status(phi, phi->nbr, " is thinking\n", 16);
	if (phi->params->philosopher_count % 2 && phi->meals_eaten)
		usleep(999 * phi->params->time_to_eat);
	else if (phi->params->philosopher_count % 2 && (!(phi->nbr % 2) ||
			phi->nbr == phi->params->philosopher_count))
		usleep(999 * phi->params->time_to_eat);
	phi->state = TAKING;
	return (phi->alive);
}

void		*state_machine(void *arg)
{
	t_philosopher		*phi;
	static t_function	process[4] = {thinking, taking, eating, sleeping};

	phi = (t_philosopher*)arg;
	while (process[phi->state](phi))
		;
	return (NULL);
}
