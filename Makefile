NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

HEADER_SRCS	=	pipex.h pipex_bonus.h
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

MPATH_SRCS	=	pipex.c child_routine.c ft_split.c ft_strdup.c ft_strjoin.c ft_free.c ft_putstr_fd.c ft_split_2.c ft_split_2_utils.c
MPATH_DIR	=	mandatory/
MPATH		=	$(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M		=	$(MPATH:.c=.o)

BPATH_SRCS	=	pipex_bonus.c child_routine_bonus.c ft_split_bonus.c ft_strdup_bonus.c ft_strjoin_bonus.c ft_free_bonus.c ft_putstr_fd_bonus.c\
				ft_split_2_bonus.c ft_split_2_utils_bonus.c
BPATH_DIR	=	bonus/
BPATH		=	$(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B		=	$(BPATH:.c=.o)

%.o: %.c $(HEADER) Makefile
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_F) $(OBJ_M)
				@$(CC) $(OBJ_F) $(OBJ_M) -o $(NAME)
				@echo -e "$(NAME) created!"

all:			$(NAME)

bonus:			$(OBJ_F) $(OBJ_B)
				@$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME)
				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
				@$(RM) $(OBJ_M)
				@$(RM) $(OBJ_F)
				@$(RM) $(OBJ_B)
				@echo -e "object files deleted!"

fclean:			clean
				@$(RM) $(NAME)
				@echo -e "all deleted!"

re:				fclean all

.PHONY:		all clean fclean bonus re
