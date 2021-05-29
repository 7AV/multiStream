# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/26 10:16:29 by sbudding          #+#    #+#              #
#    Updated: 2021/03/30 16:59:14 by sbudding         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

HEADER = philo_three.h

SRC = utils.c init.c

FLAGS = -Wall -Wextra -Werror 

OBJ = $(SRC:.c=.o)

%.o:%.c
	gcc  $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) main.c
	gcc $(FLAGS) main.c $(OBJ) -o $(NAME)

run: all
	./philo_three 5 800 200 200

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all