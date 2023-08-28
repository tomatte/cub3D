/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:32:17 by felcaue-          #+#    #+#             */
/*   Updated: 2023/08/28 20:48:09 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "../libs/libft/includes/libftprintf.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define VALID_ID "NSEWCF\n"
# define PLAYER_VALID "NSEW"
# define MAP_CHARS_VALID "01 NSEW\n"
# define MAP_SPACES_VALID "01"
# define OUTLINE 57
# define OUTER_EDGE 33
# define INNER_EDGE 64
# define SPACE_FILLER 35

typedef enum e_tf
{
	FALSE,
	TRUE
}	t_tf;

typedef enum e_textures
{
	TEXTURE_NB
}	t_textures;

typedef struct s_image
{
	int			bpp;
	int			size_l;
	int			endian;
	int			width;
	int			height;
	int			color;
	void		*img_ptr;
	int			*dump;
}	t_image;

typedef struct s_parameters
{
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	int		top_color;
	int		bottom_color;
}	t_parameters;

typedef struct s_game_data
{
	int				game_state;
	t_tf			game_running;
	char			**map_data;
	char			**map_dev;
	int				map_lines;
	int				line_length;
	t_image			image[TEXTURE_NB];
	t_parameters	parameters;
}	t_game_data;

typedef struct s_map
{
	int		**matrix;
	char	**charmatrix;
	int		width;
	int		height;
}	t_map;

typedef struct s_cords
{
	int	x;
	int	y;
}	t_cords;

///////////////////// validation_start.c

t_tf	validation(t_game_data *data, int argc, char **argv);
t_tf	print_error(char *error);
void	init_parameters(t_parameters *parameters);
t_tf	validate_args(t_game_data *data, int argc, char **argv);
t_tf	validate_map_name(t_game_data *game_data, char *name_map);

///////////////////// validation_utils_01.c

t_tf	fail_validation(t_parameters *parameters, char **map);
void	free_ptr_matrix(char **ptr_matrix);
void	free_pointer(void **pointer);
int		commas_quantity(char *string);
void	gnl_free(char *temporary, int fd);

///////////////////// validation_utils_02.c

int		string_size(char *string, char *cha_group);
int		char_trim(char cha, char const *cha_group);
void	fill_map_sizes(t_game_data *game);
void	clear_map_arr(char **map);
void	clear_game_data(t_game_data *game_data);

///////////////////// validation_map_file_01.c

char	**get_array_map(int fd);
t_tf	in_group(char cha, char *group);
char	*string_merge(char *string1, char *string2);
char	**padding_map(char **map_mtx, int size_max);
int		max_string_size(char **matrix);

///////////////////// validation_files_01.c

t_tf	validate_files(t_parameters *parameters, char *file);
t_tf	first_char_inval(int fd, char **temporary);
t_tf	check_text(t_parameters *params, char **text, char *file, char *temp);
char	*arrange_colours(char **text);
t_tf	colours_validation(char *colour_text, int *holder);

///////////////////// validation_files_02.c

int		colour_get(int red, int green, int blue);
char	*text_string_erase(char *string, char *group);
t_tf	texture_validation(char *file_holder, char **holder_res);
t_tf	validate_all_parameters(t_parameters *parameters);

///////////////////// validation_map_01.c

t_tf	validate_map(char **map_array);
t_tf	player_locator(char **map_array);
void	cleanup_map_first(char **map_array);
t_tf	adjacent_to_char(char **map_ar, int x_cord, int y_cord, char c);
t_tf	map_chars_validation(char **map_array);

///////////////////// validation_map_02.c

void	map_outline(char **map_array);
t_tf	cha_border(char **map_array, int xcord, int ycord, char cha);
void	map_nu_walls(char **map_array);
t_tf	stuck_player(char **map_ar);
t_cords	cordinates_obtain(char **map_array, int x_cord, int y_cord);

///////////////////// validation_map_03.c

t_tf	geom_crawl(char **map_array, int x_cor, int y_cor, char cha_put);
int		break_check(char **map_array, int x_cord, int y_cord, char cha);
t_tf	geom_fork(char **map_array, int x_cord, int y_cord);
t_tf	geom_recur(char **map_array, int x_cord, int y_cord);
t_tf	player_in(char **map_ar, int line, int collum);

///////////////////// validation_map_04.c

void	change_cha_array(char **map_array, char *identify, char *substitute);
void	change_cha_line(char *map_line, char *identify, char *substitute);
int		in_identify(char cha_in_line, char *identify);
char	substitute_find(char *substitute, int index);
void	outer_edge_removal(char **map_array);

///////////////////// validation_map_05.c

t_tf	geom_inner_sealed(char **map_array);

///////////////////// validation_print_map.c

void	map_print(char **data_map);
void	map_print_with_colour(char **data_map);

#endif