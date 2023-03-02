/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:36:23 by hyyoo             #+#    #+#             */
/*   Updated: 2023/03/02 20:34:39 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	ft_print(int philo_id, char *msg, t_info *info)
{
	pthread_mutex_lock(&(info->print));
	if (!(ft_check_die_flag(info, READ)))
	{
		printf("%lld %d %s\n", ft_get_time() - info->t_start, philo_id + 1, msg);
	}
	pthread_mutex_unlock(&(info->print));
}

int	ft_error_msg(char *str)
{
	printf("%s\n", str);
	return (0);
}

long long	ft_get_time(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (ft_error_msg("get_time_error"));
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000)); //시간 계산하는 방법 챗 지피티한테 물어보기, 그냥 시간을 계산하는 방식.
}

void	ft_pass_time(long long time, int num_philo)
{
	long long	get_time;

	get_time = ft_get_time();
	if (!get_time)
		return ;
	while ((ft_get_time() - get_time) < time) //그냥 유슬립을 걸어버리면, 스톱 레디 런 있어서 시간이 100이면 100될때까지 잘게 쪼개서 확인
	{
		if (num_philo < 50)
			usleep(time / 10); //필로가 조금있으면 시간을 더 잘게쪼갠다.
		else
			usleep(1000);
	}
}
