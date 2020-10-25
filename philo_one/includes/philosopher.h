/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:46:28 by nforay            #+#    #+#             */
/*   Updated: 2020/10/25 02:27:51 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

typedef struct				s_params
{
	unsigned int			philosopher_count;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	unsigned int			nbr_of_meals;
	struct timeval			*time;
}							t_params;

typedef struct				s_philosopher
{
	unsigned int			nbr;
	pthread_t				id;
	t_params				*params;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	struct s_philosopher	*next;
}							t_philosopher;

#endif
