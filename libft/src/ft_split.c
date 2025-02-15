/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <rmikhayl@student.42london.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:25:26 by rmikhayl          #+#    #+#             */
/*   Updated: 2023/12/17 17:25:26 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* *************************** ft_split ************************************* */
/*   Splits the input string 's' into an array of substrings using the        */
/*   delimiter character 'c'. Returns the array, with a NULL-terminated       */
/*   element marking the end.                                                 */
/*                                                                            */
/*   Edge Cases:                                                              */
/*   - If 's' is NULL, returns NULL.                                          */
/*   - If 'c' is '\0', returns an array with 's' as the only element.         */
/*   - If 's' does not contain 'c', returns an array with 's' as the only     */
/*     element.                                                               */
/*                                                                            */
/*   Behavior:                                                                */
/*   - The function splits 's' into substrings wherever 'c' is encountered.   */
/*   - Consecutive 'c' characters result in empty strings in the array.       */
/*   - Leading and trailing 'c' characters are ignored.                       */
/* ************************************************************************** */

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		else
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*strndup(const char *s, size_t n)
{
	char	*dup;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

static void	split_into_words(char **result, const char *s, char c)
{
	int			i;
	int			in_word;
	const char	*start;

	i = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			start = s;
			in_word = 1;
		}
		else if (*s == c && in_word)
		{
			result[i++] = strndup(start, s - start);
			in_word = 0;
		}
		s++;
	}
	if (in_word)
		result[i++] = strndup(start, s - start);
	result[i] = NULL;
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	split_into_words(result, s, c);
	return (result);
}
