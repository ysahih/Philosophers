NAME = philo

HDR = philo.h


SRCS = main.c\
parsing.c lst_utils.c\

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