/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:35:49 by hyyoo             #+#    #+#             */
/*   Updated: 2023/03/02 20:30:15 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	ft_all_eat_checker(t_info *info, int *num_eat)
{
	int	i;

	i = -1;
	while (info->must_eat != -1 && ++i < info->num_philo)
	{
		if (ft_eat_cnt_check(&(info->philo[i]), READ) >= info->must_eat)
			(*num_eat) += 1;
	}
	if (*num_eat == info->num_philo)
		ft_check_eat_flag(info, WRITE);
}

void	ft_check_finish(t_info *info)
{
	int	i;
	int	num_eat;

	i = -1;
	while (!(info->eat_flag))
	{
		num_eat = 0;
		i = -1;
		while (++i < info->num_philo && !(ft_check_die_flag(info, READ)))
		{
			pthread_mutex_lock(&(info->checker));
			if (ft_get_time() - info->philo[i].last_eat > info->t_die)
			{
				ft_print(info->philo[i].philo_id, "died", info);
				ft_check_die_flag(info, WRITE);
			}
			pthread_mutex_unlock(&(info->checker));
		}
		if (ft_check_die_flag(info, READ))
			break ;
		ft_all_eat_checker(info, &num_eat);
	}
}

int	ft_create_thread(t_info *info)
{
	int			i;

	i = -1;
	info->t_start = ft_get_time();
	while (++i < info->num_philo)
		ft_eat_mutex(&((info->philo)[i]));
	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_create(&(info->philo[i].thread), NULL,
				&ft_philo, (void *)&(info->philo[i])) != 0)
		{
			printf("Error == create thread\n");
			return (0);
		}
	}
	return (1);
}

void	ft_thread(t_info *info)
{
	int	check;

	check = ft_create_thread(info);
	if (!check)
		return ;
	ft_check_finish(info);
	ft_free_thread(info);
	if (info->die_flag == 0)
		return ;
}