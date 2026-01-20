# ---- Project ---------------------------------------------------------------
NAME	:= philo
# ---- Paths -----------------------------------------------------------------
INC_DIR		:= inc
SRC_DIR		:= src
OBJ_DIR		:= obj


# ---- Tools & Flags ---------------------------------------------------------
CC			:= cc -g
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -I$(INC_DIR)
RM			:= rm -f

# ---- Sources ---------------------------------------------------------------
SRC	:= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/routine.c \
	$(SRC_DIR)/routine2.c \
	$(SRC_DIR)/monitor.c \
	$(SRC_DIR)/check.c \
	$(SRC_DIR)/forks.c \
	$(SRC_DIR)/init_threads.c \
	$(SRC_DIR)/single_philo.c \

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ---- Rules -----------------------------------------------------------------
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
