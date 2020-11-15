/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:46:28 by nforay            #+#    #+#             */
/*   Updated: 2020/11/15 18:57:38 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define ERROR_1 "Error: arguments expected\n"
# define ERROR_2 "Error: invalid number_of_philosopher\n"
# define ERROR_3 "Error: invalid time_to_die\n"
# define ERROR_4 "Error: invalid time_to_eat\n"
# define ERROR_5 "Error: invalid time_to_sleep\n"
# define ERROR_6 "Error: invalid number_of_time_each_philosophers_must_eat\n"
# define ERROR_7 "Error: sem_open failed\n"
# define ERROR_8 "Error: malloc failed\n"

enum	e_state
{
	THINKING,
	TAKING,
	EATING,
	SLEEPING
};

typedef struct				s_params
{
	size_t					philosopher_count;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t					nbr_of_meals;
	size_t					time;
}							t_params;

#endif
