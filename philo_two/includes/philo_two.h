/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:46:28 by nforay            #+#    #+#             */
/*   Updated: 2020/11/09 19:06:15 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include "philosopher.h"

typedef struct				s_philosopher
{
	size_t					nbr;
	size_t					alive;
	size_t					meals_eaten;
	pthread_t				thread;
	enum e_state			state;
	t_params				*params;
	sem_t					*forks;
	size_t					starvation;
	struct s_philosopher	*next;
}							t_philosopher;

typedef int					(*t_function)(t_philosopher *);
void						*state_machine(void *arg);
int							parse_args(int argc, char **argv, t_params *params);
int							destroy_table(t_philosopher *phi);
int							destroy_philisophers(t_philosopher *phi,
								t_philosopher *tmp);
int							print_error(char *str, int len);
void						print_status(t_philosopher *phi, size_t nbr,
								char *str, size_t size);
size_t						gettime_us(void);

#endif
