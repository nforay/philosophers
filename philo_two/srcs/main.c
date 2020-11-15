/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:35:48 by nforay            #+#    #+#             */
/*   Updated: 2020/11/15 18:59:35 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		start_philosophers(t_philosopher *phi, t_params *params)
{
	if (!phi)
		return (0);
	phi->starvation = gettime_us() + params->time_to_die * 1000;
	pthread_create(&phi->thread, NULL, &state_machine, phi);
	return (start_philosophers(phi->next, params));
}

int		setup_table(t_philosopher *phi, t_params *params, size_t nbr,
			size_t total)
{
	phi->nbr = nbr;
	if (phi->nbr == 1)
	{
		sem_unlink("/forks");
		phi->forks = sem_open("/forks", O_CREAT, 0660,
			params->philosopher_count);
		if (phi->forks == SEM_FAILED)
			return (print_error(ERROR_7, 24));
	}
	if (nbr == total)
	{
		phi->next = NULL;
		return (0);
	}
	else if (!(phi->next = malloc(sizeof(t_philosopher))))
		return (print_error(ERROR_8, 22));
	memset(phi->next, 0, sizeof(t_philosopher));
	phi->next->forks = phi->forks;
	return (setup_table(phi->next, params, nbr + 1, total));
}

int		init_philosopher(t_philosopher *phi, t_philosopher *first)
{
	if (!phi)
		return (0);
	phi->meals_eaten = 0;
	phi->alive = 1;
	phi->state = THINKING;
	phi->params = first->params;
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
		return (print_error(ERROR_8, 22) * -1);
	memset(phi, 0, sizeof(t_philosopher));
	if (setup_table(phi, &params, 1, params.philosopher_count))
		return (destroy_table(phi));
	phi->params = &params;
	init_philosopher(phi, phi);
	params.time = gettime_us();
	start_philosophers(phi, &params);
	wait_philosophers_end(phi);
	destroy_philisophers(phi, phi);
	return (1);
}
