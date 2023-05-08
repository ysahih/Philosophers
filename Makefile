NAME = philo

HDR = philo.h


SRCS = main.c\
srcs/parsing.c srcs/lst_utils.c\
srcs/init.c srcs/utils.c\
srcs/philo_life.c srcs/feeding.c\

RM = rm -rf
CC = cc
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror -pthread

all : $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^


%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS) $(B_OBJS)

fclean : clean
	@$(RM) $(NAME) $(B_NAME)

re : fclean all