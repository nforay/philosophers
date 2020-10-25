/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:26:09 by nforay            #+#    #+#             */
/*   Updated: 2020/10/25 22:54:07 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	str_conv_uint(char *str, unsigned int *nbr)
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

int	parse_args(int argc, char **argv, t_params *params)
{
	if (str_conv_uint(argv[1], &params->philosopher_count))
		return (1);
	if (str_conv_uint(argv[2], &params->time_to_die))
		return (1);
	if (str_conv_uint(argv[3], &params->time_to_eat))
		return (1);
	if (str_conv_uint(argv[4], &params->time_to_sleep))
		return (1);
	if (argc == 6 && str_conv_uint(argv[5], &params->nbr_of_meals))
		return (1);
	printf("philosopher_count: %d\t", params->philosopher_count);
	printf("time_to_die: %d\t", params->time_to_die);
	printf("time_to_eat: %d\t", params->time_to_eat);
	printf("time_to_sleep: %d\t", params->time_to_sleep);
	printf("nbr_of_meals: %d\n", params->nbr_of_meals);
	return (0);
}
