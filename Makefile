NAME = philo
CC = cc
RM = rm -f

SRCS = main.c \
		utils.c \
		errors.c \
		init.c \
		actions.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) -c $< -o $@

clean:
		$(RM) $(OBJS)

fclean : clean
			$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
