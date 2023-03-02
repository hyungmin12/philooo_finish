/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:40:46 by hyyoo             #+#    #+#             */
/*   Updated: 2023/03/02 16:05:19 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	ft_destroy_mutex(t_info *info)
{
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->die_mutex));
	pthread_mutex_destroy(&(info->eat_mutex));
	pthread_mutex_destroy(&(info->flag_eat_mutex));
	pthread_mutex_destroy(&(info->checker));
}

void	ft_free_thread(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		pthread_mutex_destroy(&(info->philo[i].eat_cnt_mutex));
	}
	ft_destroy_mutex(info);
}

void	ft_free(t_info *info)
{
	if (info->fork)
		free(info->fork);
	if (info->philo)
		free(info->philo);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		check;

	check = ft_init(argc, argv, &info);
	if (!check)
		return (0);
	ft_thread(&info);
	ft_free(&info);
	return (0);
}
