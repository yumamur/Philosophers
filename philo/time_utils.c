/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:52:16 by yumamur           #+#    #+#             */
/*   Updated: 2023/10/31 19:52:16 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philo_types.h"

t_time	nanotime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	p_sleep(t_flag *death, t_time length)
{
	_Atomic t_time	cur;

	cur = nanotime();
	while (!*death)
	{
		if (nanotime() - cur >= length)
			return ;
		usleep(1000);
	}
}
