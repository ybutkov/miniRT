# =========================
# Project
# =========================
NAME = miniRT

SRC_DIR = src
BUILD_DIR = build

UNAME_SYSTEM = $(shell uname -s)

# =========================
# MinilibX
# =========================
MINILIBX_DIR = MinilibX

# Linux
MINILIB_GIT = https://github.com/42paris/minilibx-linux.git

# macOS
MINILIB_MAC_OS_URL = https://cdn.intra.42.fr/document/document/39773/minilibx_macos_metal.tgz
MINILIB_ZIP_FILE = $(notdir $(MINILIB_MAC_OS_URL))

ifeq ($(UNAME_SYSTEM), Linux)
	MINILIBX = $(MINILIBX_DIR)/libmlx.a
	LFLAGS_OS = -L$(MINILIBX_DIR) -lXext -lX11 -lm
else ifeq ($(UNAME_SYSTEM), Darwin)
	MINILIBX = $(MINILIBX_DIR)/libmlx.dylib
	LFLAGS_OS = -framework OpenGL -framework AppKit -Wl,-rpath,@executable_path/MinilibX
endif

# =========================
# Libft
# =========================
LIBFT_DIR = libft
LIBFT_NAME = ft
LIBFT = $(LIBFT_DIR)/libft.a

# =========================
# Includes
# =========================
INCLUDES = -Iincludes -I$(MINILIBX_DIR) -I$(LIBFT_DIR)/includes

# =========================
# Compiler flags
# =========================
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 $(INCLUDES)
LFLAGS = -L$(LIBFT_DIR) -l$(LIBFT_NAME) -L$(MINILIBX_DIR) -lmlx $(LFLAGS_OS)

SAN_ASAN = -fsanitize=address,undefined -fno-omit-frame-pointer

# =========================
# Source files
# =========================
C_SHELL_FILES = \
	app_op/app_core.c \
	app_op/app_core_2.c \
	app_op/app_basic.c \
	events/hooks.c \
	events/mouse_hooks.c \
	events/key_actions.c \
	events/actions_wrapper_1.c \
	events/actions_wrapper_2.c \
	events/actions_wrapper_3.c \
	events/actions_wrapper_4.c \
	main.c \
	parsing/parser.c \
	parsing/parser_elements.c \
	parsing/parser_utils.c \
	parsing/scene.c \
	parsing/utils.c

C_FILES = $(addprefix $(SRC_DIR)/, $(C_SHELL_FILES))
C_OBJ_FILES = $(C_FILES:%.c=$(BUILD_DIR)/%.o)

BUILD_DIRS := $(sort $(dir $(C_OBJ_FILES)))

# =========================
# Targets
# =========================
all: $(NAME)
bonus: all

$(NAME): $(MINILIBX) $(LIBFT) $(BUILD_DIRS) $(C_OBJ_FILES)
	$(CC) $(CFLAGS) $(C_OBJ_FILES) $(LFLAGS) -o $(NAME)
ifeq ($(UNAME_SYSTEM), Darwin)
	install_name_tool -change libmlx.dylib @executable_path/MinilibX/libmlx.dylib $(NAME)
endif
	@echo "Build OK"

# =========================
# Build object directories
# =========================
$(BUILD_DIRS):
	@mkdir -p $@

# =========================
# Build object files
# =========================
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Libft
# =========================
$(LIBFT):
	@make -C $(LIBFT_DIR) all

# =========================
# MinilibX
# =========================
$(MINILIBX):
	if [ ! -d $(MINILIBX_DIR) ]; then \
		if [ "$(UNAME_SYSTEM)" = "Linux" ]; then \
			git clone $(MINILIB_GIT) $(MINILIBX_DIR); \
		elif [ "$(UNAME_SYSTEM)" = "Darwin" ]; then \
			mkdir -p $(MINILIBX_DIR); \
			curl -LO $(MINILIB_MAC_OS_URL); \
			tar -xzf $(MINILIB_ZIP_FILE) --strip-components=1 -C $(MINILIBX_DIR); \
		else \
			echo "Unsupported OS"; \
			exit 1; \
		fi; \
	fi
	if [ ! -f $(MINILIBX) ]; then \
		make -C $(MINILIBX_DIR) all; \
	fi

# =========================
# Clean
# =========================
clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "clean OK"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(MINILIB_ZIP_FILE)
	[ -d $(MINILIBX_DIR) ] && rm -rf $(MINILIBX_DIR)
	@echo "fclean OK"

re: fclean all
s: all

# =========================
# AddressSanitizer
# =========================
asan: CFLAGS += $(SAN_ASAN)
asan: re

# =========================
# Valgrind
# =========================
v: re
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--suppressions=tools/sub.sub ./$(NAME)

.PHONY: all bonus clean fclean re s asan v


# NAME = miniRT
# NAME_C = miniRT.c

# SRC = src
# BUILD_DIR =	build

# UNAME_SYSTEM = $(shell uname -s)

# MINILIBX_DIR = MinilibX

# # Linux
# MINILIB_GIT = https://github.com/42paris/minilibx-linux.git

# # MacOS
# MINILIB_MAC_OS_URL = https://cdn.intra.42.fr/document/document/39773/minilibx_macos_metal.tgz
# MINILIB_ZIP_FILE = $(notdir $(MINILIB_MAC_OS_URL))

# # Set MINILIBX based on OS
# ifeq ($(UNAME_SYSTEM), Linux)
# 	MINILIBX = $(MINILIBX_DIR)/libmlx.a
# 	LFLAGS_OS = -L$(MINILIBX_DIR) -lXext -lX11 -lm
# else ifeq ($(UNAME_SYSTEM), Darwin)
# 	MINILIBX = $(MINILIBX_DIR)/libmlx.dylib
# 	LFLAGS_OS = -framework OpenGL -framework AppKit -Wl,-rpath,@executable_path/MinilibX
# endif

# LIBFT_DIR = libft
# LIBFT_NAME = ft
# LIBFT = $(LIBFT_DIR)/libft.a

# INCLUDES = -Iincludes
# INCLUDES += -I$(MINILIBX_DIR)
# INCLUDES += -I$(LIBFT_DIR)/includes

# PRINT_FLAG = -s --no-print-directory

# DEFAULT_SILENT ?= 1
# ifneq ($(filter s,$(MAKECMDGOALS)),)
# SILENT := 0
# else
# SILENT ?= $(DEFAULT_SILENT)
# endif
# ifeq ($(SILENT),1)
# MAKEFLAGS += -s --no-print-directory
# endif

# CC = cc
# # CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined
# CFLAGS = -Wall -Wextra -Werror -g -O0 $(INCLUDES)
# LFLAGS = -L$(LIBFT_DIR) -l$(LIBFT_NAME) 
# LFLAGS += -L$(MINILIBX_DIR) -lmlx
# LFLAGS += $(LFLAGS_OS)

# #two last flags are for compiling an external library for readline
# SAN_ASAN = -fsanitize=address,undefined -fno-omit-frame-pointer

# C_SHELL_FILES += \
# 		app_op/app_core.c \
# 		app_op/app_core_2.c \
# 		app_op/app_basic.c \
# 		events/hooks.c \
# 		events/mouse_hooks.c \
# 		events/key_actions.c \
# 		events/actions_wrapper_1.c \
# 		events/actions_wrapper_2.c \
# 		events/actions_wrapper_3.c \
# 		events/actions_wrapper_4.c 
		
# C_SHELL_FILES += \
# 		main.c \
#         parser.c \
#         parser_elements.c \
# 		parser_utils.c \
# 		scene.c \
# 		utils.c


# C_FIlES = $(addprefix $(SRC)/, $(C_SHELL_FILES))
# C_OBJ_FIlES =	$(C_FIlES:%.c=$(BUILD_DIR)/%.o)

# BUILD_DIRS := $(sort $(dir $(C_OBJ_FIlES)))

# all : $(NAME)
# bonus : all

# ${NAME} : $(MINILIBX) $(LIBFT) $(BUILD_DIRS) $(C_OBJ_FIlES)
# 	$(CC) $(CFLAGS) $(C_OBJ_FIlES) $(NAME_C) $(LFLAGS) -o $(NAME)
# ifeq ($(UNAME_SYSTEM), Darwin)
# 	install_name_tool -change libmlx.dylib @executable_path/MinilibX/libmlx.dylib $(NAME)
# endif
# 	@echo "Build OK"

# clean :
# 	@rm -rf $(BUILD_DIR)
# 	@make -C $(LIBFT_DIR) clean $(PRINT_FLAG)
# 	@echo "clean OK"

# fclean f: clean
# 	@rm -f $(NAME)
# 	@make -C $(LIBFT_DIR) fclean $(PRINT_FLAG)
# 	@rm -f $(MINILIB_ZIP_FILE)
# 	[ -d $(MINILIBX_DIR) ] && rm -rf $(MINILIBX_DIR)
# 	@echo "fclean OK"

# re	: fclean all
# s : all

# # adds AddressSanitizer and UndefinedBehaviorSanitizer flags
# asan: CFLAGS += $(SAN_ASAN)
# asan: re

# $(BUILD_DIRS):
# 	@mkdir -p $@

# $(BUILD_DIR)/%.o : %.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(LIBFT) :
# 	@make -C $(LIBFT_DIR) all $(PRINT_FLAG)

# $(MINILIBX):
# 	if [ ! -d $(MINILIBX_DIR) ]; then \
# 		if [ "$(UNAME_SYSTEM)" = "Linux" ]; then \
# 			git clone $(MINILIB_GIT) $(MINILIBX_DIR); \
# 		elif [ "$(UNAME_SYSTEM)" = "Darwin" ]; then \
# 			mkdir -p $(MINILIBX_DIR); \
# 			curl -LO $(MINILIB_MAC_OS_URL); \
# 			tar -xzf $(MINILIB_ZIP_FILE) --strip-components=1 -C $(MINILIBX_DIR); \
# 		else \
# 			echo "Unsupported OS"; \
# 			exit 1; \
# 		fi; \
# 	fi
# 	if [ ! -f $(MINILIBX) ]; then \
# 		make -C $(MINILIBX_DIR) all; \
# 	fi

# .PHONY : all clean fclean re bonus s v

# v: re
# 	valgrind --leak-check=full  --show-leak-kinds=all --track-fds=yes \
# 		--suppressions=tools/sub.sub  ./miniRT
# # 		--track-origins=yes --trace-children=yes --suppressions=tools/sub.sub  ./minishell

# #valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -s ./minishell

