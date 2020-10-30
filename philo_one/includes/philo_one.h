/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:46:28 by nforay            #+#    #+#             */
/*   Updated: 2020/10/30 21:59:54 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "philosopher.h"

# define ERROR_1 "Error: arguments expected\n"
# define ERROR_2 "Error: invalid number_of_philosopher\n"
# define ERROR_3 "Error: invalid time_to_die\n"
# define ERROR_4 "Error: invalid time_to_eat\n"
# define ERROR_5 "Error: invalid time_to_sleep\n"
# define ERROR_6 "Error: invalid number_of_time_each_philosophers_must_eat\n"

#endif
