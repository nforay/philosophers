/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:26:09 by nforay            #+#    #+#             */
/*   Updated: 2020/11/15 18:47:30 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int				print_error(char *str, int len)
{
	if (write(STDERR_FILENO, str, len))
		return (1);
	return (1);
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
	sem_unlink("/forks");
	if (!(params->forks = sem_open("/forks", O_CREAT, 0660,
			params->philosopher_count)))
		return (print_error(ERROR_7, 24));
	sem_unlink("/print");
	if (!(params->print = sem_open("/print", O_CREAT, 0660, 1)))
		return (print_error(ERROR_7, 24));
	sem_unlink("/quit");
	if (!(params->quit = sem_open("/quit", O_CREAT, 0660, 1)))
		return (print_error(ERROR_7, 24));
	return (0);
}
