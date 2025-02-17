# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 18:15:56 by rmikhayl          #+#    #+#              #
#    Updated: 2024/06/05 18:16:01 by rmikhayl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a
CC = 	clang
AR =	ar rcs
RM = 	rm -rf

CFLAGS =	-Wall -Werror -Wextra
MAKEFLAGS += --silent
SHELL := bash

# *************************************************************************** #

B =		$(shell tput bold)
BLA =	$(shell tput setaf 0)
RED =	$(shell tput setaf 1)
GRE =	$(shell tput setaf 2)
YEL =	$(shell tput setaf 3)
BLU =	$(shell tput setaf 4)
MAG =	$(shell tput setaf 5)
CYA =	$(shell tput setaf 6)
WHI =	$(shell tput setaf 7)
D =		$(shell tput sgr0)
BEL =	$(shell tput bel)
CLR =	$(shell tput el 1)


# *************************************************************************** #

SRCSPATH =	./src/
OBJSPATH =	./obj/
INC 		 =	./inc/

SRCS =		$(wildcard $(SRCSPATH)*.c) $(wildcard $(SRCSPATH)**/*.c)
SRCSNAME =	$(subst $(SRCSPATH), , $(SRCS))

OBJSNAME =	$(SRCSNAME:.c=.o)
OBJS =		$(addprefix $(OBJSPATH), $(OBJSNAME))

# *************************************************************************** #

define	progress_bar
	i=0
	while [[ $$i -le $(words $(SRCS)) ]] ; do \
		printf " " ; \
		((i = i + 1)) ; \
	done
	printf "$(B)]\r[$(GRE)"
endef

# *************************************************************************** #

all:		launch $(NAME)
	@printf "\n$(B)$(CYA)$(NAME) binaries compiled$(D)\n"

launch:
	$(call progress_bar)

$(NAME):	$(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJSPATH)%.o: $(SRCSPATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@
	@printf "█"
	
clean:
	@$(RM) $(OBJSPATH)

fclean:		clean
	@$(RM) $(OBJSPATH)
	@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re

# *************************************************************************** #
