NAME = miniRT
NAME_C = miniRT.c

SRC = src
BUILD_DIR =	build

UNAME_SYSTEM = $(shell uname -s)

MINILIBX_DIR = MinilibX

# Linux
MINILIB_GIT = https://github.com/42paris/minilibx-linux.git

# MacOS
MINILIB_MAC_OS_URL = https://cdn.intra.42.fr/document/document/39773/minilibx_macos_metal.tgz
MINILIB_ZIP_FILE = $(notdir $(MINILIB_MAC_OS_URL))

# Set MINILIBX based on OS
ifeq ($(UNAME_SYSTEM), Linux)
	MINILIBX = $(MINILIBX_DIR)/libmlx.a
	LFLAGS_OS = -L$(MINILIBX_DIR) -lXext -lX11 -lm
else ifeq ($(UNAME_SYSTEM), Darwin)
	MINILIBX = $(MINILIBX_DIR)/libmlx.dylib
	LFLAGS_OS = -framework OpenGL -framework AppKit -Wl,-rpath,@executable_path/MinilibX
endif

LIBFT_DIR = libft
LIBFT_NAME = ft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -Iincludes
INCLUDES += -I$(MINILIBX_DIR)
INCLUDES += -I$(LIBFT_DIR)/includes

PRINT_FLAG = -s --no-print-directory

DEFAULT_SILENT ?= 1
ifneq ($(filter s,$(MAKECMDGOALS)),)
SILENT := 0
else
SILENT ?= $(DEFAULT_SILENT)
endif
ifeq ($(SILENT),1)
MAKEFLAGS += -s --no-print-directory
endif

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined
CFLAGS = -Wall -Wextra -Werror -g -O0 $(INCLUDES)
LFLAGS = -L$(LIBFT_DIR) -l$(LIBFT_NAME) 
LFLAGS += -L$(MINILIBX_DIR) -lmlx
LFLAGS += $(LFLAGS_OS)

#two last flags are for compiling an external library for readline
SAN_ASAN = -fsanitize=address,undefined -fno-omit-frame-pointer

C_SHELL_FILES += \
		app_op/app_core.c \
		app_op/app_core_2.c \
		app_op/app_basic.c \
		map_op/map_core.c \
		map_op/map_core_2.c \
		map_op/map_basic.c \
		draw_func/put_pixel.c \
		draw_func/draw_axes_line.c \
		draw_func/draw_axes.c \
		draw_func/draw_axes_labels.c \
		draw_func/draw_axes_info.c \
		events/hooks.c \
		events/mouse_hooks.c \
		events/key_actions.c \
		events/object_selection.c \
		events/actions_wrapper_1.c \
		events/actions_wrapper_2.c \
		events/actions_wrapper_3.c \
		events/actions_wrapper_4.c

C_SHELL_FILES += \
		objects/obj_core.c \
		objects/camera_core.c \
		objects/sphere_core.c \
		objects/sphere_vtables.c \
		objects/cylinder_core.c \
		objects/cylinder_vtables.c \
		objects/plane_core.c \
		objects/plane_vtables.c \
		objects/triangle_core.c \
		objects/triangle_vtables.c \
		objects/box_core.c \
		objects/box_vtables.c \
		objects/light_core.c \
		objects/ambient_core.c \
		objects/cone_core.c \
		objects/cone_vtables.c \
		objects/texture.c \
		objects/sky_core.c

C_SHELL_FILES += \
		bvh/bvh_core.c \
		bvh/bvh_generate_1.c \
		bvh/bvh_generate_2.c \
		bvh/bvh_generate_3.c \
		bvh/bvh_generate_4.c \
		bvh/bvh_node_core.c

C_SHELL_FILES += \
		math/color/color_core.c \
		math/color/color_func.c \
		math/ray/ray_core.c \
		math/ray/ray_func_1.c \
		math/ray/ray_func_2.c \
		math/vector/vector_core.c \
		math/vector/vector_func_1.c \
		math/vector/vector_func_2.c \
		math/math_utils.c

C_SHELL_FILES += \
        parsing/parser.c \
        parsing/parser_utils.c \
        parsing/utils.c \
		parsing/utils_2.c \
		parsing/data_rules.c

C_FIlES = $(addprefix $(SRC)/, $(C_SHELL_FILES))
C_OBJ_FIlES =	$(C_FIlES:%.c=$(BUILD_DIR)/%.o)

BUILD_DIRS := $(sort $(dir $(C_OBJ_FIlES)))

all : $(NAME)
bonus : all

${NAME} : $(MINILIBX) $(LIBFT) $(BUILD_DIRS) $(C_OBJ_FIlES)
	$(CC) $(CFLAGS) $(C_OBJ_FIlES) $(NAME_C) $(LFLAGS) -o $(NAME)
ifeq ($(UNAME_SYSTEM), Darwin)
	install_name_tool -change libmlx.dylib @executable_path/MinilibX/libmlx.dylib $(NAME)
endif
	@echo "Build OK"

clean :
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean $(PRINT_FLAG)
	@echo "clean OK"

fclean f: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean $(PRINT_FLAG)
	@rm -f $(MINILIB_ZIP_FILE)
	@[ -d $(MINILIBX_DIR) ] && rm -rf $(MINILIBX_DIR) || true
	@echo "fclean OK"

re	: fclean all
s : all


# adds AddressSanitizer and UndefinedBehaviorSanitizer flags
asan: CFLAGS += $(SAN_ASAN)
asan: re

$(BUILD_DIRS):
	@mkdir -p $@

$(BUILD_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make -C $(LIBFT_DIR) all $(PRINT_FLAG)

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

.PHONY : all clean fclean re bonus s v

v: re
	valgrind --leak-check=full  --show-leak-kinds=all --track-fds=yes \
		./miniRT scenes/earth2.rt
#		--suppressions=tools/sub.sub   
# 		--track-origins=yes --trace-children=yes --suppressions=tools/sub.sub  ./minishell

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  --error-exitcode=1 ./program

#valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -s ./minishell

