SRCS	= main.c philo_utils.c error.c new_philo.c start.c routine.c philo_utils_2.c 

OBJS	= ${SRCS:.c=.o}

NAME	= philo

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=thread

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
				${RM} ${OBJBS} ${OBJS}

fclean: 	clean
				${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re
