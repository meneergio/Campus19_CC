/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:01:54 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/03 14:36:55 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx/mlx.h"

/* Game constants */
# define TILE_SIZE 64
# define BUFFER_SIZE 1024

/* Screen resolution and limits */
# define SCREEN_WIDTH 3840
# define SCREEN_HEIGHT 2160
# define MAX_MAP_WIDTH 60
# define MAX_MAP_HEIGHT 33

/* Leave some space for window decorations and taskbar */
# define SAFE_MAX_WIDTH 58
# define SAFE_MAX_HEIGHT 29

/* Key codes (Linux) */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Map characters */
# define WALL '1'
# define FLOOR '0'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'

/* Error messages */
# define ERR_ARGS "Error\nUsage: ./so_long <map.ber>\n"
# define ERR_MAP_FILE "Error\nCannot read map file\n"
# define ERR_MAP_INVALID "Error\nInvalid map configuration\n"
# define ERR_MAP_NOT_RECTANGULAR "Error\nMap is not rectangular\n"
# define ERR_MAP_NO_WALLS "Error\nMap must be surrounded by walls\n"
# define ERR_MAP_MISSING_ELEMENTS "Error\nMap missing required elements\n"
# define ERR_MAP_TOO_MANY_PLAYERS "Error\nMap has duplicate players or exits\n"
# define ERR_MAP_NO_PATH "Error\nNo valid path to all collectibles and exit\n"
# define ERR_MAP_INVALID_CHAR "Error\nMap contains invalid characters\n"
# define ERR_MAP_TOO_LARGE "Error\nMap too large for screen\n"
# define ERR_MLX_INIT "Error\nMiniLibX initialization failed\n"
# define ERR_MLX_WIN "Error\nWindow creation failed\n"
# define ERR_MLX_IMG "Error\nImage loading failed\n"

/* Point structure for coordinates */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/* Validation structure for pathfinding */
typedef struct s_validation
{
	t_point	player_pos;
	int		total_collectibles;
	int		collectibles_reachable;
	int		exit_reachable;
}	t_validation;

/* Game structure */
typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		collectibles_total;
	int		collectibles_collected;
	int		moves;
	int		game_won;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
}	t_game;

/* Main functions */
int		main(int argc, char **argv);
void	error_exit(char *message);
void	init_game(t_game *game);
void	cleanup_game(t_game *game);
int		close_window(t_game *game);

/* Map parsing functions */
int		check_map_size(t_game *game);
int		parse_map(char *filename, t_game *game);
int		count_lines(char *filename);
char	**allocate_map(int height);
int		read_line_from_buffer(char *buffer, char *current_line,
			int *buffer_pos, int *line_pos);
int		process_line(t_game *game, char *current_line, int *i);

/* Map reading functions (from map_reader.c) */
int		read_map_content(int fd, t_game *game);

/* Map validation functions */
int		check_map_walls(t_game *game);
int		check_map_elements(t_game *game);
int		validate_map(t_game *game);
int		check_valid_path(t_game *game);

/* Map utility functions (from map_validation_utils.c) */
char	**copy_map(t_game *game);
void	count_reachable_items(t_game *game, char **map_copy, t_validation *val);

/* Game logic functions */
int		can_move_to(t_game *game, int x, int y);
void	collect_item(t_game *game, int x, int y);
void	check_win_condition(t_game *game);
void	move_player(t_game *game, int new_x, int new_y);
int		handle_keypress(int keycode, t_game *game);

/* Rendering functions */
int		load_textures(t_game *game);
void	render_tile(t_game *game, int x, int y);
void	render_game(t_game *game);
void	render_player_on_tile(t_game *game, int x, int y);

/* Utility functions */
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
void	free_map(char **map);
void	print_moves(t_game *game);
void	count_map_elements(t_game *game);
void	find_player_position(t_game *game);

#endif
