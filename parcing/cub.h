/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:22:38 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/05 16:25:46 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# define BUFFER_SIZE 3
# define TRUE 1
# define FALSE 0
# define F 0
# define C 1

typedef struct		s_color
{
	int	r;
	int	g;
	int	b;
	int	color;
}					t_color;

typedef struct		s_map
{
	char	*str;
	char	**map;
	int		nbr_cols;
	int		nbr_rows;
}					t_map;

typedef struct		s_parcing
{
	int		p_w;
	int		p_h;
	char	* south;
	char	* north;
	char	* east;
	char	* west;
	char	* s_path;
	int		file_args;
	t_color c[2];
	t_map	map;
}					t_parcing;

void				initial_color(t_parcing *p);
void				initial(t_parcing *p);
void				ft_parse(t_parcing *p, int ac, char **av);
void				ft_putchar(char *str);
size_t				ft_strlen(const char *str);
char				*ft_chr(const char *s, int c);
char				*str_get(char *rest, int i, char **line);
int					get_next_line(int fd, char **line);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);
char				*ft_strjoin_2(char *s, char *s1, char *s2);
int					ft_error(char *str);
void				ft_get_resol(t_parcing *p, char *line);
void				ft_check_r(char *line);
unsigned long long	ft_atoi2(const char *str);
unsigned long long	ft_atoi(const char *str);
int					ft_check_textures(char *line);
void				ft_check_texture(t_parcing *p, char *line);
char				*ft_get_texture(char *line);
int					check_space(char *line);
void				ft_get_color(t_parcing *p, char *line);
void				check_comma(char *line, int count);
void				ft_color(t_parcing *p, char *line, int c_f);
int					ft_check_color(t_parcing *p);

void				map_out_line(t_parcing *p);
void				map_out_up_down(t_parcing *p, int pos);
void				maperr(t_parcing *p);
void				mapcheck(t_parcing *p, char **tab);

int					mapsearsh(char *line);
int					map_is_last(t_parcing *p);
void				ft_stock_map(t_parcing *p, char *line);
int					countrow(char **tab);
void				ft_check_map(t_parcing *p);

void				map_out_line(t_parcing *p);
void				map_out_up_down(t_parcing *p, int pos);
void				maperr(t_parcing *p);
void				mapcheck(t_parcing *p, char **tab);

void				table_free(char **tab);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
int					check(char c, char *set);
void				ft_check_atoi(char *line, int i);

#endif
