SRCS	= main.c thread_data.c
OBJS	= ${SRCS:.c=.o}

CC	= cc

CFLAGS = -Wall -Werror -Wextra

NAME	= philosophers

.c.o:
	${CC} ${CFLAGS} -c ${SRCS}

RM	= rm -f

$(NAME):	${OBJS}
	cc -o $(NAME) ${OBJS} -lpthread

all:	$(NAME)

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: 	all clean fclean