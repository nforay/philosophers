/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:35:48 by nforay            #+#    #+#             */
/*   Updated: 2020/11/09 18:44:36 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		start_philosophers(t_philosopher *phi, t_params *params)
{
	if (!phi)
		return (0);
	phi->starvation = gettime_us() + params->time_to_die * 1000;
	if (pthread_create(&phi->thread, NULL, &state_machine, phi) < 0)
		return (start_philosophers(phi, params));
	return (start_philosophers(phi->next, params));
}

int		setup_table(t_philosopher *phi, t_params *params, size_t nbr,
			size_t total)
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
	memset(phi->next, 0, sizeof(t_philosopher));
	return (setup_table(phi->next, params, nbr + 1, total));
}

int		init_philosopher(t_philosopher *phi, t_philosopher *first)
{
	if (!phi)
		return (0);
	phi->meals_eaten = 0;
	phi->alive = 1;
	phi->state = THINKING;
	if (!(phi->r_fork = malloc(sizeof(pthread_mutex_t))))
		return (destroy_philisophers(first, first));
	pthread_mutex_init(phi->r_fork, NULL);
	if (phi->next)
		phi->next->l_fork = phi->r_fork;
	else
		first->l_fork = phi->r_fork;
	if (phi->params->philosopher_count == 1)
	{
		if (!(phi->l_fork = malloc(sizeof(pthread_mutex_t))))
			return (destroy_philisophers(first, first));
		pthread_mutex_init(phi->l_fork, NULL);
	}
	return (init_philosopher(phi->next, first));
}

void	wait_philosophers_end(t_philosopher *phi)
{
	t_philosopher	*tmp;
	int				meals;
	size_t			nbr_of_meals;

	tmp = phi;
	meals = 1;
	nbr_of_meals = phi->params->nbr_of_meals;
	while (1)
	{
		meals = (meals && nbr_of_meals && tmp->meals_eaten >= nbr_of_meals);
		if (gettime_us() > tmp->starvation)
		{
			print_status(tmp, tmp->nbr, " died\n", 9);
			break ;
		}
		if (!(tmp = tmp->next))
			if ((tmp = phi) && meals++)
				break ;
	}
	tmp = phi;
	while (tmp)
	{
		tmp->alive = 0;
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv)
{
	t_params		params;
	t_philosopher	*phi;

	memset(&params, 0, sizeof(t_params));
	if (argc < 5 || argc > 6)
		return (print_error(ERROR_1, 27));
	if (parse_args(argc, argv, &params))
		return (1);
	if (!(phi = malloc(sizeof(t_philosopher))))
		return (-1);
	memset(phi, 0, sizeof(t_philosopher));
	if (setup_table(phi, &params, 1, params.philosopher_count))
		return (destroy_table(phi));
	if (init_philosopher(phi, phi))
		return (-1);
	params.time = gettime_us();
	start_philosophers(phi, &params);
	wait_philosophers_end(phi);
	destroy_philisophers(phi, phi);
	return (1);
}
