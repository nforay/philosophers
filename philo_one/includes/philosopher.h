/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:46:28 by nforay            #+#    #+#             */
/*   Updated: 2020/10/25 22:57:13 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

enum	e_state
{
	TAKING,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

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
	size_t					nbr;
	pthread_t				*thread;
	enum e_state			state;
	t_params				*params;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	struct timeval			*starvation;
	struct s_philosopher	*next;
}							t_philosopher;

typedef int					(*t_function)(t_philosopher *);
void						*state_machine(void *arg);
int							parse_args(int argc, char **argv, t_params *params);

#endif
