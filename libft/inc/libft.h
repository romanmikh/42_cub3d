/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rocky <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:48 by rmikhayl          #+#    #+#             */
/*   Updated: 2024/09/26 18:31:00 by rocky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// Includes
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>
# include <signal.h>
# include <stdbool.h>
# include <math.h>

// Macros
# define TRUE 1
# define FALSE 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 32

# define RESET "\033[0m"
# define BLK "\033[0;30m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYA "\033[0;36m"
# define WHI "\033[0;37m"
# define B_BLK "\033[1;30m"
# define B_RED "\033[1;31m"
# define B_GRN "\033[1;32m"
# define B_YEL "\033[1;33m"
# define B_BLU "\033[1;34m"
# define B_MAG "\033[1;35m"
# define B_CYA "\033[1;36m"
# define B_WHI "\033[1;37m"

// Enumations
enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

// Function Prototypes
int			ft_abs(int n);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_is_alpha(int c);
int			ft_is_digit(int c);
int			ft_is_alnum(int c);
int			ft_is_ascii(int c);
int			ft_is_print(int c);
int			ft_print_int(int n);
int			ft_print_char(int c);
int			ft_print_percent(void);
int			ft_print_str(char *str);
int			ft_is_whitespace(char c);
int			ft_atoi(const char *str);
int			ft_is_num(const char *n);
int			ft_is_valid_rgb(int rgb);
int			ft_ptr_len(uintptr_t num);
int			ft_list_len_char(char a[]);
int			ft_list_len_str(char *a[]);
int			ft_len_2d_arr(char **array);
int			ft_is_double(const char *n);
int			ft_is_num_str(const char *str);
int			ft_printf(const char *format, ...);
int			ft_print_ptr(unsigned long long ptr);
int			ft_print_unsigned_dec(unsigned int n);
int			ft_find_max_in_list(int a[], int size);
int			ft_count_bits(unsigned char current_char);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_list_repeat_check_int(int a[], int size);
int			ft_list_repeat_check_str(char *a[], int size);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_print_unsigned_hex(unsigned int num, const char format);

char		*ft_itoa(int n);
char		*f_strdup(char *s1);
char		*get_next_line(int fd);
char		*ft_strdup(const char *s);
char		*ft_get_next_line(int fd);
char		*f_strchr(char *s, int c);
char		*f_strjoin(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strcat(char *dest, char *src);
char		*ft_strrchr(const char *s, int c);
char		**ft_split(char const *s, char c);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_remove_quotes(char *str, char quote_type);
char		*ft_strstr(const char *big, const char *little);
char		*ft_strcat_const(const char *dest, const char *src);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_realloc_array(char **array, int old_size, int new_size);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

void		ft_put_ptr(uintptr_t num);
void		ft_free_2d_arr(void **arr);
void		ft_bzero(void *s, size_t n);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_print_2d_arr(char **arr, char *name);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);

double		ft_atof(const char *str);

long		ft_atol(const char *nptr);

bool		ft_is_digit_in_str(char *str);

const char	*ft_exclude_delimiters(const char *str, char *delims);

unsigned long	ft_rgb_to_hex(int *rgb_int_arr);

#endif /* LIBFT_H */
