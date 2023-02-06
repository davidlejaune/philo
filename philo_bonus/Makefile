# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dly <dly@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 14:22:17 by dly               #+#    #+#              #
#    Updated: 2023/02/06 16:26:25 by dly              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                                                              #
#                              VARIABLES                                       #
#                                                                              #
################################################################################

BONUS_FILES		= main_bonus.c  init_bonus.c  utils_bonus.c \
				  philo_bonus.c  actions_bonus.c

B_SRCS_DIR		= srcs/

B_SRCS			= $(addprefix $(B_SRCS_DIR), $(BONUS_FILES))
B_OBJS			= $(B_SRCS:.c=.o)


INCLUDE			= -Iinclude
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -pthread  -fsanitize=thread

RM				= rm -f
AR				= ar rcs

NAME			= philo_bonus
HEADER_B		= include/philo_bonus.h

################################################################################
#                                                                              #
#                                  RULES                                       #
#                                                                              #
################################################################################

all:			$(NAME)

%.o:			%.c
				@echo "Compiling: $<"
				@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

bonus:			$(NAME) 

$(NAME):		$(B_OBJS) $(HEADER_B) 
				@$(CC) $(CFLAGS) $(INCLUDE) $(B_OBJS) -o $(NAME)
				@echo "philo_bonus executable ready!"
				
clean:
				@$(RM) $(B_OBJS)
				@echo "every object files cleaned!"

fclean:			clean
				@$(RM) $(NAME)
				@echo "executable files cleaned!"

re:				fclean $(NAME) 

norm:
				@norminette $(B_SRCS) $(HEADER_B) 

.PHONY:			all clean fclean re bonus
