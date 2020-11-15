/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:35:48 by nforay            #+#    #+#             */
/*   Updated: 2020/11/15 18:49:02 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	init_philosopher(t_philosopher *phi, t_params *params, size_t nbr)
{
	memset(phi, 0, sizeof(t_philosopher));
	phi->nbr = nbr;
	phi->alive = 1;
	phi->state = THINKING;
	phi->params = params;
	phi->starvation = params->time + phi->params->time_to_die * 1000;
}

void	*philosopher_watchdog(void *arg)
{
	t_philosopher	*phi;

	phi = (t_philosopher*)arg;
	while (1)
	{
		if (gettime_us() > phi->starvation)
		{
			phi->alive = 0;
			force_print_status(phi, phi->nbr, " died\n", 9);
			sem_wait(phi->params->print);
			sem_post(phi->params->forks);
			usleep(100);
			break ;
		}
	}
	return (NULL);
}

void	start_philosophers(size_t nbr, t_params *params, pid_t *pids)
{
	t_philosopher	phi;
	pid_t			pid;

	while (nbr++ < params->philosopher_count)
	{
		if ((pid = fork()) == -1)
		{
			free(pids);
			exit(print_error(ERROR_8, 22));
		}
		if (pid == 0)
		{
			free(pids);
			pthread_create(&phi.thread, NULL, &philosopher_watchdog, &phi);
			pthread_detach(phi.thread);
			init_philosopher(&phi, params, nbr);
			state_machine(&phi);
			sem_close(params->forks);
			sem_close(params->print);
			sem_close(params->quit);
			exit(phi.alive);
		}
		else
			pids[nbr - 1] = pid;
	}
}

void	wait_philosophers_end(t_params *params, pid_t *pids)
{
	int	state;

	(void)pids;
	while (params->philo_fed < params->philosopher_count)
	{
		waitpid(-1, &state, 0);
		if (WEXITSTATUS(state) == 1)
		{
			if (++params->philo_fed == params->philosopher_count)
				break ;
		}
		else
		{
			while (params->philosopher_count--)
			{
				kill(pids[params->philosopher_count], SIGKILL);
				usleep(500);
			}
			break ;
		}
	}
}

int		main(int argc, char **argv)
{
	t_params		params;
	pid_t			*pids;

	memset(&params, 0, sizeof(t_params));
	if (argc < 5 || argc > 6)
		return (print_error(ERROR_1, 27));
	if (parse_args(argc, argv, &params))
		return (1);
	if (!(pids = malloc(sizeof(pid_t) * params.philosopher_count)))
		return (-1);
	params.time = gettime_us();
	start_philosophers(0, &params, pids);
	wait_philosophers_end(&params, pids);
	sem_close(params.forks);
	sem_close(params.print);
	sem_close(params.quit);
	free(pids);
	return (1);
}
