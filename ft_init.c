/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:41:09 by hyyoo             #+#    #+#             */
/*   Updated: 2023/03/02 15:40:26 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	ft_atoi(char *str)
{
	long long	ret;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	ret = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	ret = ret * sign;
	if (ret < -2147483648 || ret > 2147483647)
		return (-1);
	return (ret * sign);
}

int	ft_init_philo(t_info *info)
{
	int	i;

	i = -1;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * (info->num_philo));
	if (!(info->philo))
		return (0);
	while (++i < info->num_philo)
	{
		info->philo[i].philo_id = i;
		info->philo[i].eat_cnt = 0;
		info->philo[i].left = i;
		info->philo[i].right = (i + 1) % info->num_philo;
		info->philo[i].last_eat = 0;
		info->philo[i].info = info;
		if (pthread_mutex_init(&(info->philo[i].eat_cnt_mutex), NULL))
		{
			return (0);
		}
	}
	return (1);
}

int	ft_init_mutex(t_info *info)
{
	int	i;

	i = -1;
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->num_philo);
	if (!(info->fork))
		return (0);
	if (pthread_mutex_init(&(info->die_mutex), NULL))
		return (0);
	if (pthread_mutex_init(&(info->eat_mutex), NULL))
		return (0);
	if (pthread_mutex_init(&(info->flag_eat_mutex), NULL))
		return (0);
	if (pthread_mutex_init(&(info->print), NULL))
		return (0);
	if (pthread_mutex_init(&(info->checker), NULL))
		return (0);
	while (++i < info->num_philo)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			return (0);
	}
	return (1);
}

int	ft_init_info(t_info *info)
{
	info->philo = NULL;
	info->fork = NULL;
	info->eat_flag = 0;
	info->die_flag = 0;
	info->t_start = 0;
	if (!(ft_init_philo(info)))
		return (0);
	if (!(ft_init_mutex(info)))
		return (0);
	return (1);
}

int	ft_init(int argc, char **argv, t_info *info)
{
	if (!(ft_check_is_int(argv)))
		return (0);
	if (argc == 5)
	{
		if (ft_four(argv, info) == 0)
			return (0);
	}
	if (argc == 6)
	{
		if (ft_five(argv, info) == 0)
			return (0);
	}
	if (!(ft_init_info(info)))
		return (0);
	return (1);
}
