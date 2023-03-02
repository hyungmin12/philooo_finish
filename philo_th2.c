/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:36:07 by hyyoo             #+#    #+#             */
/*   Updated: 2023/03/02 20:19:13 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	ft_mutex_unlock_fork(t_info *info, t_philo *philo, int philo_id)
{
	if (philo_id % 2 == 1)
	{
		pthread_mutex_unlock(&(info->fork[philo->left]));
		pthread_mutex_unlock(&(info->fork[philo->right]));
	}
	else
	{
		pthread_mutex_unlock(&(info->fork[philo->right]));
		pthread_mutex_unlock(&(info->fork[philo->left]));
	}
}

void	ft_mutex_lock_fork(t_philo *philo, t_info *info, int check)
{	
	if ((philo->philo_id) % 2 == check)
		pthread_mutex_lock(&(info->fork[philo->left]));
	else
		pthread_mutex_lock(&(info->fork[philo->right]));
	ft_print(philo->philo_id, "has taken a fork", info);
}

void	ft_eat(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	ft_mutex_lock_fork(philo, info, FIRST);
	if (philo->left == philo->right) // 한명
	{
		pthread_mutex_unlock(&(info->fork[philo->left]));
		ft_pass_time(info->t_die * 2, info->num_philo);
		return ;
	}
	ft_mutex_lock_fork(philo, info, SECOND);
	pthread_mutex_lock(&(info->checker));
	ft_print(philo->philo_id, "is eating", info);
	pthread_mutex_lock(&(philo->info->eat_mutex));
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&(philo->info->eat_mutex));
	pthread_mutex_unlock(&(info->checker));
	ft_eat_cnt_check(philo, WRITE);
	ft_pass_time(info->t_eat, info->num_philo);
	ft_mutex_unlock_fork(info, philo, philo->philo_id);
}

void	*ft_philo(void *philo_ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)philo_ptr;
	info = philo->info;
	if (philo->philo_id % 2)
		usleep(1000);
	else
		usleep(500);
	while (ft_check_die_flag(info, READ) == 0)
	{
		ft_eat(philo);
		if (ft_check_eat_flag(info, READ) == 1)
		{
			break ;
		}
		ft_print(philo->philo_id, "is sleeping", info);
		ft_pass_time(info->t_sleep, info->num_philo);
		ft_print(philo->philo_id, "is thinking", info);
	}
	return (NULL);
}
