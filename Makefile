CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=thread
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
PRINTF_DIR = ft_printf/
PRINTF = $(PRINTF_DIR)libftprintf.a

NAME = philosophers
SRC_DIR = philo/src/
OBJ_DIR = philo/obj/
HEADER = $(SRC_DIR)philosophers.h
FILES = main.c create.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

BONUS = philosophers_bonus
BONUS_SRC_DIR = philo_bonus/src/
BONUS_OBJ_DIR = philo_bonus/obj/
BONUS_HEADER = $(BONUS_SRC_DIR)philosophers_bonus.h
BONUS_FILES = main_bonus.c create_bonus.c
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(BONUS_FILES))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))

RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m

.PHONY: all $(LIBFT) $(PRINTF) $(OBJ_DIR) bonus clean fclean re

all: $(LIBFT) $(PRINTF) $(OBJ_DIR) $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $<

$(PRINTF): $(PRINTF_DIR)
	@make -C $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "$(BLUE)$(BOLD)Creating $(NAME) executable...$(RESET)"
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) created$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
	$(CC) $(FLAGS) -c $< -o $@

bonus: $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS)

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

$(BONUS): $(BONUS_OBJ)
	@echo "$(BLUE)$(BOLD)Creating $(BONUS) executable...$(RESET)"
	$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) $(GNL) -o $(BONUS)
	@echo "$(GREEN)$(BOLD)$(BONUS) created$(RESET)"

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_HEADER) $(GNL_HEADER)
	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	@echo "$(RED)$(BOLD)Object files removed$(RESET)"

fclean: clean
	rm -f $(NAME) $(BONUS)
	@echo "$(RED)$(BOLD)$(NAME) and $(BONUS) removed$(RESET)"

re: fclean all