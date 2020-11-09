/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:26:09 by nforay            #+#    #+#             */
/*   Updated: 2020/11/09 19:17:40 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				destroy_table(t_philosopher *phi)
{
	t_philosopher	*tmp;

	tmp = phi;
	while (phi)
	{
		tmp = phi->next;
		free(phi);
		phi = tmp;
	}
	sem_unlink("/forks");
	return (-1);
}

int				destroy_philisophers(t_philosopher *phi, t_philosopher *tmp)
{
	while (tmp)
	{
		if (tmp->params->time)
			pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	sem_unlink("/forks");
	while (phi)
	{
		if (phi->nbr == 1)
			sem_close(phi->forks);
		tmp = phi->next;
		free(phi);
		phi = tmp;
	}
	return (1);
}

static int		str_conv_uint(char *str, unsigned long long *nbr)
{
	if (!str || *str == 0)
		return (1);
	while (*str && *str >= '0' && *str <= '9')
	{
		*nbr = *nbr * 10 + *str - '0';
		str++;
	}
	if (*str == 0)
		return (0);
	return (1);
}

static int		check_number(char *str, size_t *nbr)
{
	unsigned long long	llnbr;

	llnbr = 0;
	if (str_conv_uint(str, &llnbr))
		return (1);
	if (llnbr >= 4294967296)
		return (1);
	*nbr = (size_t)llnbr;
	return (0);
}

int				parse_args(int argc, char **argv, t_params *params)
{
	if (check_number(argv[1], &params->philosopher_count))
		return (print_error(ERROR_2, 38));
	if (check_number(argv[2], &params->time_to_die))
		return (print_error(ERROR_3, 28));
	if (check_number(argv[3], &params->time_to_eat))
		return (print_error(ERROR_4, 28));
	if (check_number(argv[4], &params->time_to_sleep))
		return (print_error(ERROR_5, 30));
	if (argc == 6 && check_number(argv[5], &params->nbr_of_meals))
		return (print_error(ERROR_6, 58));
	return (0);
}
