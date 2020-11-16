/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:40:49 by nforay            #+#    #+#             */
/*   Updated: 2020/11/16 16:52:28 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

size_t			gettime_us(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) == -1)
		return (gettime_us());
	return ((tp.tv_sec * 1000000) + tp.tv_usec);
}

static void		putnbr_buff(size_t nbr, char **buff)
{
	if (nbr / 10)
		putnbr_buff(nbr / 10, buff);
	*(*buff)++ = (char)(nbr % 10 + '0');
}

static void		putstr_buff(char *str, char **buff)
{
	while (*str)
		*(*buff)++ = *str++;
}

void			print_status(t_philosopher *phi, size_t nbr, char *str,
				size_t size)
{
	size_t			timestamp;
	char			buff[64];
	char			*ptr;

	timestamp = (gettime_us() - phi->params->time) / 1000;
	if (!phi->alive)
		return ;
	ptr = buff;
	putnbr_buff(timestamp, &ptr);
	putstr_buff(" ", &ptr);
	while (timestamp /= 10)
		size++;
	putnbr_buff(nbr, &ptr);
	while (nbr /= 10)
		size++;
	putstr_buff(str, &ptr);
	sem_wait(phi->params->print);
	write(STDOUT_FILENO, buff, size);
	sem_post(phi->params->print);
}

void			force_print_status(t_philosopher *phi, size_t nbr, char *str,
				size_t size)
{
	size_t			timestamp;
	char			buff[64];
	char			*ptr;

	timestamp = (gettime_us() - phi->params->time) / 1000;
	sem_wait(phi->params->quit);
	ptr = buff;
	putnbr_buff(timestamp, &ptr);
	putstr_buff(" ", &ptr);
	while (timestamp /= 10)
		size++;
	putnbr_buff(nbr, &ptr);
	while (nbr /= 10)
		size++;
	putstr_buff(str, &ptr);
	write(STDOUT_FILENO, buff, size);
}
