/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:40:49 by nforay            #+#    #+#             */
/*   Updated: 2020/11/09 17:58:25 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

	if (!phi->alive)
		return ;
	ptr = buff;
	timestamp = (gettime_us() - phi->params->time) / 1000;
	putnbr_buff(timestamp, &ptr);
	putstr_buff(" ", &ptr);
	while (timestamp /= 10)
		size++;
	putnbr_buff(nbr, &ptr);
	while (nbr /= 10)
		size++;
	putstr_buff(str, &ptr);
	if (write(STDOUT_FILENO, buff, size))
		return ;
}

int				print_error(char *str, int len)
{
	if (write(STDERR_FILENO, str, len))
		return (1);
	return (1);
}
