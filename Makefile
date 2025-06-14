CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

MAN_DIR = philo/
NAME = $(MAN_DIR)philo
SRC_DIR = $(MAN_DIR)src/
OBJ_DIR = $(MAN_DIR)obj/
HEADER = $(SRC_DIR)philosophers.h
FILES = actions.c create.c functions.c main.c utils.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

BONUS_DIR = philo_bonus/
BONUS = $(BONUS_DIR)philo_bonus
BONUS_SRC_DIR = $(BONUS_DIR)src/
BONUS_OBJ_DIR = $(BONUS_DIR)obj/
BONUS_HEADER = $(BONUS_SRC_DIR)philosophers_bonus.h
BONUS_FILES = actions_bonus.c create_bonus.c functions_bonus.c main_bonus.c utils_bonus.c
BONUS_SRC = $(addprefix $(BONUS_SRC_DIR), $(BONUS_FILES))
BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))

RED = \033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
BLUE = \033[0;34m
BOLD = \033[1m
RESET = \033[0m

.PHONY: all $(LIBFT) $(OBJ_DIR) bonus clean fclean re

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@echo "$(BLUE)$(BOLD)Creating $(NAME) executable...$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) created$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

bonus: $(LIBFT) $(BONUS_OBJ_DIR) $(BONUS)

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)

$(BONUS): $(BONUS_OBJ)
	@echo "$(BLUE)$(BOLD)Creating $(BONUS) executable...$(RESET)"
	@$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) $(GNL) -o $(BONUS)
	@echo "$(GREEN)$(BOLD)$(BONUS) created$(RESET)"

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(BONUS_HEADER) $(GNL_HEADER)
	@echo "$(CYAN)$(BOLD)Compiling $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)$(BOLD)Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME) $(BONUS)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)$(BOLD)$(NAME) and $(BONUS) removed$(RESET)"

re: fclean all
