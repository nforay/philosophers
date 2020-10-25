/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:35:48 by nforay            #+#    #+#             */
/*   Updated: 2020/10/25 23:16:50 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	start_philosophers(t_philosopher *phi, t_params *params)
{
	if (!phi)
		return (0);
	phi->state = (phi->nbr % 2 && phi->next) ? TAKING : THINKING;
	phi->starvation->tv_sec = phi->params->time->tv_sec;
	phi->starvation->tv_usec = phi->params->time->tv_usec;
	pthread_create(phi->thread, NULL, &state_machine, phi);
	return (start_philosophers(phi->next, params));
}

int	setup_table(t_philosopher *phi, t_params *params, size_t nbr, size_t total)
{
	phi->nbr = nbr;
	phi->params = params;
	if (nbr == total)
	{
		phi->next = NULL;
		return (0);
	}
	else if (!(phi->next = malloc(sizeof(t_philosopher))))
		return (1);
	return (setup_table(phi->next, params, nbr + 1, total));
}

int	init_philosopher(t_philosopher *phi, t_philosopher *first)
{
	if (!phi)
		return (0);
	if (!(phi->r_fork = malloc(sizeof(pthread_mutex_t))))
		return (-1);
	if (!(phi->thread = malloc(sizeof(pthread_t))))
		return (-1);
	if (!(phi->starvation = malloc(sizeof(struct timeval))))
		return (-1);
	pthread_mutex_init(phi->r_fork, NULL);
	if (phi->next)
		phi->next->l_fork = phi->r_fork;
	else
		first->l_fork = phi->r_fork;
	return (init_philosopher(phi->next, first));
}

int	main(int argc, char **argv)
{
	t_params		params;
	t_philosopher	*phi;
	t_philosopher	*tmp;

	memset(&params, 0, sizeof(t_params));
	if (argc < 5 || argc > 6 || parse_args(argc, argv, &params))
		return (-1);
	if (!(phi = malloc(sizeof(t_philosopher))))
		return (-1);
	if (!(params.time = malloc(sizeof(struct timeval))))
		return (-1);
	if (setup_table(phi, &params, 1, params.philosopher_count))
		return (-1);
	if (init_philosopher(phi, phi))
		return (-1);
	if (gettimeofday(params.time, NULL))
		return (-1);
	if (start_philosophers(phi, &params))
		return (-1);
	tmp = phi;
	while (tmp && tmp->state != DIED) //if now > tmp->starvation !DIED!
		if (!(tmp = tmp->next))
			tmp = phi;
	return (1);
}
