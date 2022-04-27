CC			= gcc
FLAGS		= -Wall -Wextra -Werror -o3 -g3
LIBFT		= -L./libft -lft
MLXLIB		= -I ./minilibx -L minilibx -lmlx 
FRAMEWORK	= -framework OpenGL -framework AppKit
INCLUDES	= -I libft/includes/ -I includes/ -I minilibx/

NAME 		= fdf

SRCS 	=	$(wildcard srcs/*.c)

OBJS	=	$(SRCS:.c=.o)

_BLUE	=	\e[34m
_PURPLE	=	\e[35m
_CYAN	=	\e[36m
_END	=	\e[0m

%.o: %.c
			@printf "FDF object : $(_BLUE)%-33.33s\r$(_END)" $@
			@${CC} ${CFLAGS} $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			@printf "\nfdf objects	[$(_BLUE)✓$(_END)]\n"
			@$(MAKE) -C ./libft
			@gcc $(FLAGS) $(OBJS) $(MLXLIB) $(INCLUDES) $(LIBFT)  -o $(NAME) $(FRAMEWORK)
			@printf "fdf		[$(_BLUE)✓$(_END)]\n"

all : 		$(NAME)

re:			clean
			$(MAKE) $(NAME)

clean :
			@rm -rf $(OBJS) $(NAME)
			@printf "$(_PURPLE)FDF object	deleted$(_END)\n"

fclean :	clean
			@$(MAKE) fclean -C ./libft
			@rm -rf $(NAME)
			@printf "$(_PURPLE)fdf		deleted$(_END)\n"

PHONY : re all clean fclean
