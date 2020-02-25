# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/12 18:13:02 by lubenard          #+#    #+#              #
#    Updated: 2020/02/25 12:58:41 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g3

NAME		= fdf
LIBFT		= libft
LIBX_UNIX	= minilibx/unix
LIBX_SIERRA	= minilibx/sierra
LIBX_MOJAVE	= minilibx/mojave
SRCSDIR		= srcs
INCDIR		= includes
OBJSDIR		= objs

FILES		= main.c \
			  get_map.c \
			  init_structs.c \
			  init_mlx.c \
			  draw.c \
			  move.c \
			  utils.c

SRCS		= $(addprefix $(SRCSDIR)/, $(FILES))
OBJS		= $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)
OBJSD		= $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.d)

##### Cross compil #####

UNIX 		= false
MAC			= false

##### Colors #####
_END		= \x1b[0m
_BOLD		= \x1b[1m
_UNDER		= \x1b[4m
_REV		= \x1b[7m
_GREY		= \x1b[30m
_RED		= \x1b[31m
_GREEN		= \x1b[32m
_YELLOW		= \x1b[33m
_BLUE		= \x1b[34m
_PURPLE		= \x1b[35m
_CYAN		= \x1b[36m
_WHITE		= \x1b[37m

##### Debug #####

FSANITIZE	= false

all: $(NAME)

ifeq ($(FSANITIZE), true)
CFLAGS += -fsanitize=address
endif

ifeq ($(UNIX), true)
all: $(OBJS) unix_compil
endif

ifeq ($(SIERRA), true)
all: $(OBJS) sierra_compil
endif

ifeq ($(MOJAVE), true)
all: $(OBJS) mojave_compil
endif

$(NAME): $(OBJS)
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -j4 -C $(LIBFT)
	@echo -e -n "\n${_BLUE}${_BOLD}[Create Executable] $(NAME)${_END}"
	@make -j4 -C $(LIBX_SIERRA) &> /dev/null
	#@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft 
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft -L ./$(LIBX_SIERRA) -lmlx -framework OpenGL -framework AppKit
	@echo -e "\n${_GREEN}${_BOLD}$(NAME) done.${_END}"

unix_compil:
	@echo "${_RED}Compiling UNIX minilibx${_END}"
	@make -j4 -C $(LIBX_UNIX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBFT) -lft -L ./$(LIBX_UNIX) -lmlx -lXext -lX11

mojave_compil:
	@echo "${_RED}Compiling MOJAVE minilibx${_END}"
	@make -j4 -C $(LIBX_MOJAVE)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBFT) -lft -L ./$(LIBX_MOJAVE) -lmlx -framework OpenGL -framework AppKit

sierra_compil:
	@echo "${_RED}Compiling SIERRA minilibx${_END}"
	@make -j4 -C $(LIBX_SIERRA) &> /dev/null
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT) -lft -L ./$(LIBX_SIERRA) -lmlx -framework OpenGL -framework AppKit

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c Makefile
	@mkdir -p $(@D)
	@echo -n -e "\r\033[K${_PURPLE}${BOLD}[${NAME}] Compiling $<${_END}"
	@$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT)/$(INCDIR) -MMD -o $@ -c $<

libft:
	@$(MAKE) -q -C $(LIBFT) || $(MAKE) -j4 -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./$(LIBFT)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo "${_RED}${_BOLD}Cleaning obj files...${_END}"
	@rm -f $(OBJS)
	@rm -f $(OBJSD)
	@rm -Rf $(OBJDIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBX_UNIX) clean
	@$(MAKE) -C $(LIBX_SIERRA) clean
	@$(MAKE) -C $(LIBX_MOJAVE) clean
	@echo "${_RED}${_BOLD}Cleaning project...${_END}"
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME).dSYM

re: fclean
	@$(MAKE)

norm:
	@norminette $(INCDIR) $(SRCSDIR) | grep "Warning\|Error" || true
	@echo "Norm done!"

check_error:
	@grep -rn "printf" srcs | grep -v "ft_"
	@grep -rn "stdio.h" srcs

unix: all
	@make -q -C $(LIBX_UNIX) || $(MAKE) -C $(LIBX_UNIX)

.PHONY: all clean fclean re norm tests $(LIBFT)

.SILENT:

-include $(OBJSD)
