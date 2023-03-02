/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:31:28 by hyyoo             #+#    #+#             */
/*   Updated: 2023/03/02 16:44:47 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define FIRST 1
# define SECOND 0
# define WRITE 1
# define READ 0

struct	s_info;

typedef struct s_philo
{
	int					left;
	int					right;
	int					philo_id;
	int					eat_cnt;
	pthread_t			thread;
	long long			last_eat;
	pthread_mutex_t		eat_cnt_mutex;
	struct s_info		*info;
}	t_philo;

typedef struct s_info
{
	int					must_eat;
	int					num_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					eat_flag;
	int					die_flag;
	long long			t_start;
	t_philo				*philo;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	pthread_mutex_t		checker;
	pthread_mutex_t		die_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		flag_eat_mutex;
}				t_info;

long long	ft_get_time(void);
void		ft_mutex_lock_fork(t_philo *philo, t_info *info, int check);
void		ft_mutex_unlock_fork(t_info *info, t_philo *philo, int philo_id);
void		ft_thread(t_info *all);
void		ft_eat(t_philo *philo);
void		ft_sleep_think(t_philo *philo);
void		*ft_philo(void	*philo_ptr);
void		ft_check_finish(t_info *info);
void		ft_print(int id, char *str, t_info *all);
void		ft_pass_time(long long time, int num_philo);
void		ft_eat_mutex(t_philo *philo);
void		ft_eat(t_philo *philo);
void		*ft_philo(void *philo_ptr);
void		ft_all_eat_checker(t_info *info, int *num_eat);
void		ft_check_finish(t_info *info);
void		ft_destroy_mutex(t_info *info);
void		ft_free_thread(t_info *info);
void		ft_thread(t_info *info);
int			ft_init(int argc, char **argv, t_info *all);
int			ft_check_is_int(char **argv);
int			ft_four(char **av, t_info *info);
int			ft_five(char **av, t_info *info);
int			ft_error_msg(char *str);
int			ft_atoi(char *nbr);
int			ft_check_die_flag(t_info *info, int flag);
int			ft_check_eat_flag(t_info *info, int flag);
int			ft_eat_cnt_check(t_philo *philo, int flag);
int			ft_create_thread(t_info *info);
#endif
