/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:35:48 by nforay            #+#    #+#             */
/*   Updated: 2020/10/25 02:30:32 by nforay           ###   ########.fr       */
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
	printf("philosopher_count: %d\n", params->philosopher_count);
	printf("time_to_die: %d\n", params->time_to_die);
	printf("time_to_eat: %d\n", params->time_to_eat);
	printf("time_to_sleep: %d\n", params->time_to_sleep);
	if (params->nbr_of_meals)
		printf("nbr_of_meals: %d\n", params->nbr_of_meals);
	return (0);
}

int	main(int argc, char **argv)
{
	t_params	params;

	memset(&params, 0, sizeof(params));
	if (argc < 5 || argc > 6 || parse_args(argc, argv, &params))
		return (-1);
	return (1);
}
