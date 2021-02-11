SRCS = ft_printf.c dvs_write_chars.c dvs_preparation_to_write_others.c dvs_write_others.c


OBJC = ${SRCS:.c=.o}
CC = gcc
GFS = -Wall -Wextra -Werror
NAME = libftprintf.a

.c.o:
		${CC} ${GFS} -c $<

all: $(NAME)

$(NAME): ${OBJC}
		ar rc ${NAME} ${OBJC}
		ranlib ${NAME}

clean:
		-rm -f ${OBJC}

fclean: clean
		-rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re
