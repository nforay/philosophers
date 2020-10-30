/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:46:28 by nforay            #+#    #+#             */
/*   Updated: 2020/10/31 00:37:44 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

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

typedef struct				s_philosopher
{
	size_t					nbr;
	size_t					alive;
	size_t					meals_eaten;
	pthread_t				*thread;
	enum e_state			state;
	t_params				*params;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	size_t					starvation;
	struct s_philosopher	*next;
}							t_philosopher;

typedef int					(*t_function)(t_philosopher *);
void						*state_machine(void *arg);
int							parse_args(int argc, char **argv, t_params *params);
int							destroy_table(t_philosopher *phi);
void						destroy_philisophers(t_philosopher *phi,
								t_philosopher *tmp);
int							print_error(char *str, int len);
void						print_status(t_philosopher *phi, size_t nbr,
								char *str, size_t size);
size_t						gettime_us(void);

#endif
