/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:46:28 by nforay            #+#    #+#             */
/*   Updated: 2020/11/15 17:43:10 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "philosopher.h"

typedef struct				s_philosopher
{
	size_t					nbr;
	size_t					alive;
	size_t					meals_eaten;
	enum e_state			state;
	pthread_t				thread;
	t_params				*params;
	size_t					starvation;
}							t_philosopher;

typedef int					(*t_function)(t_philosopher *);
void						*state_machine(void *arg);
int							parse_args(int argc, char **argv, t_params *params);
int							print_error(char *str, int len);
void						*philosopher_watchdog(void *arg);
void						print_status(t_philosopher *phi, size_t nbr,
								char *str, size_t size);
void						force_print_status(t_philosopher *phi, size_t nbr,
								char *str, size_t size);
size_t						gettime_us(void);

#endif
