#Customization:
MAKEFLAGS += --no-print-directory
.RECIPEPREFIX = ~
PINK_BOLD = \033[1;38;5;206m
END = \033[0m
GREEN = \033[38;5;71m
RED = \033[38;5;204m

#Essentials:
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
PFLAGS = -lpthread
SRC_DIR = src
SRC = main.c utils.c start_simulation.c routine.c print_msgs.c time.c clean_all.c init_structs.c sim_utils.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

#Rules:

all: $(NAME)

$(NAME): $(OBJ) 
~@echo "$(GREEN)Compiling $(NAME)...$(END)"
~@echo "$(PINK_BOLD)DONE !$(END)"
~@$(CC) $(CFLAGS) -o $@ $^ $(PFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
~@echo "$(GREEN)Creating object files...$(END)"
~@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
~@mkdir -p $(OBJ_DIR)

clean:
~@echo "$(RED)Deleting object files..."
~@rm -rf $(OBJ_DIR)

fclean: clean
~@echo "$(RED)Deleting $(NAME)..."
~@rm -f $(NAME)

re: fclean all

PHONY: all clean fclean re