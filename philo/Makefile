
NAME = philo

SRCS =	src/philo.c \
		src/utils1.c \
		src/utils2.c \
			
CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDES = -I./include

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS) -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(OBJS)
	rm -rf $(NAME)

re : fclean all

.PHONY:	all clean fclean re