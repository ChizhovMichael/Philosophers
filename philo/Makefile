NAME	= 	philo

HEADER	= 	./includes/

SRCS	=	./philo_one.c \
			./utils1.c \
			./validation.c \
			./error.c \
			./utils2.c
		
OBJS	= 	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I

LINUX	=	-pthread

MACOS	= 	-lpthread

.c.o:
		gcc $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
		gcc $(LINUX) $(OBJS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re