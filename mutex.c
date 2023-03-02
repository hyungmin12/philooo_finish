/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:35:35 by hyyoo             #+#    #+#             */
/*   Updated: 2023/03/02 15:41:35 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	ft_check_die_flag(t_info *info, int flag)
{
	int	check;

	check = 0;
	if (flag == WRITE)
	{
		pthread_mutex_lock(&(info->die_mutex));
		{
			info->die_flag = 1;
		}
		pthread_mutex_unlock(&(info->die_mutex));
	}
	else
	{
		pthread_mutex_lock(&(info->die_mutex));
		if (info->die_flag == 1)
		{
			check = 1;
		}
		pthread_mutex_unlock(&(info->die_mutex));
	}
	return (check);
}

int	ft_check_eat_flag(t_info *info, int flag)
{
	int	check;

	check = 0;
	if (flag == WRITE)
	{
		pthread_mutex_lock(&(info->flag_eat_mutex));
		{
			info->eat_flag = 1;
		}
		pthread_mutex_unlock(&(info->flag_eat_mutex));
	}
	else
	{
		pthread_mutex_lock(&(info->flag_eat_mutex));
		if (info->eat_flag == 1)
		{
			check = 1;
		}
		pthread_mutex_unlock(&(info->flag_eat_mutex));
	}
	return (check);
}

int	ft_eat_cnt_check(t_philo *philo, int flag)
{
	int	check;

	check = 0;
	if (flag == WRITE)
	{
		pthread_mutex_lock(&(philo->eat_cnt_mutex));
		{
			philo->eat_cnt += 1;
		}
		pthread_mutex_unlock(&(philo->eat_cnt_mutex));
	}
	else
	{
		pthread_mutex_lock(&(philo->eat_cnt_mutex));
		{
			check = philo->eat_cnt;
		}
		pthread_mutex_unlock(&(philo->eat_cnt_mutex));
	}
	return (check);
}

void	ft_eat_mutex(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->eat_mutex));
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&(philo->info->eat_mutex));
}
