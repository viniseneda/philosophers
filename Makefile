SRCS	= main.c thread_data.c
OBJS	= ${SRCS:.c=.o}

CC	= cc

CFLAGS = -Wall -Werror -Wextra

NAME	= philosophers

.c.o:
	${CC} ${CFLAGS} -c ${SRCS}

RM	= rm -f

$(NAME):	${OBJS}
	cc -o $(NAME) ${OBJS} 

all:	$(NAME)

clean:
	${RM} ${OBJS}
	make -C ./libft clean

fclean:	clean
	${RM} ${NAME}
	make -C ./libft fclean

re:	fclean all

.PHONY: 	all clean fclean