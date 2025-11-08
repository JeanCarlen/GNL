# --- Noms des exécutables ---
NAME_MANDATORY = mandatory_tester
NAME_BONUS = bonus_tester

# --- Fichiers sources ---
SRCS_MANDATORY_LIB = get_next_line.c get_next_line_utils.c
SRCS_BONUS_LIB = get_next_line_bonus.c get_next_line_utils_bonus.c
SRCS_MAIN = main.c

# --- Fichiers objets ---
OBJS_MANDATORY_LIB = $(SRCS_MANDATORY_LIB:.c=.o)
OBJS_BONUS_LIB = $(SRCS_BONUS_LIB:.c=.o)


# Un .o pour le main du mandatory
OBJS_MAIN_M = main_m.o
# Un .o pour le main du bonus
OBJS_MAIN_B = main_b.o

# --- Compilation ---
CC = cc
# Flags de base
CFLAGS = -Wall -Wextra -Werror
# Buffer size par défaut
BS = 1
# On combine les flags de base + le buffer size
CFLAGS_BASE = $(CFLAGS) -D BUFFER_SIZE=$(BS)

# --- Règles ---
all: bonus

# Règle pour compiler le testeur de la partie MANDATORY
mandatory: $(NAME_MANDATORY)

# Le testeur mandatory dépend des libs mandatory ET du main_m.o
$(NAME_MANDATORY): $(OBJS_MANDATORY_LIB) $(OBJS_MAIN_M)
	$(CC) $(CFLAGS_BASE) -D BONUS=0 -o $(NAME_MANDATORY) $(OBJS_MANDATORY_LIB) $(OBJS_MAIN_M)
	@echo "\n--- Testeur MANDATOIRE (./mandatory_tester) créé avec BUFFER_SIZE=$(BS) ---"

# Règle pour compiler le main_m.o avec le bon flag
$(OBJS_MAIN_M): $(SRCS_MAIN)
	$(CC) $(CFLAGS_BASE) -D BONUS=0 -c $(SRCS_MAIN) -o $(OBJS_MAIN_M)

# Règle pour compiler le testeur de la partie BONUS
bonus: $(NAME_BONUS)

# Le testeur bonus dépend des libs bonus ET du main_b.o
$(NAME_BONUS): $(OBJS_BONUS_LIB) $(OBJS_MAIN_B)
	$(CC) $(CFLAGS_BASE) -D BONUS=1 -o $(NAME_BONUS) $(OBJS_BONUS_LIB) $(OBJS_MAIN_B)
	@echo "\n--- Testeur BONUS (./bonus_tester) créé avec BUFFER_SIZE=$(BS) ---"

# Règle pour compiler le main_b.o avec le bon flag
$(OBJS_MAIN_B): $(SRCS_MAIN)
	$(CC) $(CFLAGS_BASE) -D BONUS=1 -c $(SRCS_MAIN) -o $(OBJS_MAIN_B)

# --- Nettoyage ---
clean:
	rm -f $(OBJS_MANDATORY_LIB) $(OBJS_BONUS_LIB) $(OBJS_MAIN_M) $(OBJS_MAIN_B)

fclean: clean
	rm -f $(NAME_MANDATORY) $(NAME_BONUS) $(OBJS_MAIN_M) $(OBJS_MAIN_B)

re: fclean all

.PHONY: all clean fclean re mandatory bonus