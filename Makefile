NAME		=	philo

HEADER		=	./include/

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra #-g -I $(HEADER) -fsanitize=thread -g

SRCS = ./main.c \
	   ./ft_init.c \
	   ./ft_init2.c \
	   ./mutex.c \
	   ./philo_th.c \
	   ./philo_th2.c \
	   ./utils.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all