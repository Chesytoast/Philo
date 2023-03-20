# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 11:18:13 by mcourtin          #+#    #+#              #
#    Updated: 2023/03/13 16:24:26 by mcourtin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
DIR		= srcs/
CC		= gcc -pthread
FLAGS	= -Wall -Wextra -Werror

SRCS =	src/main.c src/parsing.c src/error.c src/utils.c \
		src/routine.c src/free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re