# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dly <dly@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 14:22:17 by dly               #+#    #+#              #
#    Updated: 2023/02/03 15:56:31y dly              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                                                              #
#                              VARIABLES                                       #
#                                                                              #
################################################################################

SRCS_FILES		= main.c  init.c  utils.c  philo.c  actions.c 

SRCS_DIR		= srcs/
M_SRCS			= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
M_OBJS			= $(M_SRCS:.c=.o)

INCLUDE			= -Iinclude
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -pthread -fsanitize=thread 

RM				= rm -f
AR				= ar rcs

NAME			= philo 
HEADER			= include/philo.h

################################################################################
#                                                                              #
#                                  RULES                                       #
#                                                                              #
################################################################################

all:			$(NAME)

%.o:			%.c
				@echo "Compiling: $<"
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME):		$(M_OBJS) $(HEADER) 
				@$(CC) $(CFLAGS) $(INCLUDE) $(M_OBJS) -o $(NAME) 
				@echo "philo executable ready!"

clean:
				@$(RM) $(M_OBJS) 
				@echo "every object files cleaned!"

fclean:			clean
				@$(RM) $(NAME)
				@echo "executable files cleaned!"

re:				fclean $(NAME)

norm:
				@norminette $(M_SRCS) $(HEADER) 

.PHONY:			all clean fclean re 
