#include "cub3d.h"

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	check_rgb_chars(char *line, int *comma_count, int *digit_num)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (ft_isdigit(line[i]))
		{
			while (line[i] && ft_isdigit(line[i]))
				i++;
			(*digit_num)++;
		}
		else if (line[i] == ',')
		{
			(*comma_count)++;
			i++;
		}
		else if (line[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int	validate_rgb_format(char *line)
{
	int	comma_count;
	int	digit_num;

	comma_count = 0;
	digit_num = 0;
	if (check_rgb_chars(line, &comma_count, &digit_num) != 0)
	{
		print_error("Invalid RGB: invalid character\n");
		return (1);
	}
	if (digit_num != 3)
	{
		print_error("Invalid RGB: expected 3 numbers\n");
		return (1);
	}
	if (comma_count != 2)
	{
		print_error("Invalid RGB: expected two commas\n");
		return (1);
	}
	return (0);
}

int	parse_check_rgb_range(char *line, int *i, int *color)
{
	while (!ft_isdigit(line[*i]))
		(*i)++;
	*color = ft_atoi(line + *i);
	if (*color < 0 || *color > 255)
		return (-1);
	while (ft_isdigit(line[*i]))
		(*i)++;
	return (0);
}

int	save_color(uint32_t *color, char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (*color != (uint32_t)-1)
		return (print_error("Duplicate color identifier\n"), 1);
	if (validate_rgb_format(line) != 0)
		return (1);
	i = 0;
	if (parse_check_rgb_range(line, &i, &r) == -1)
		return (print_error(MSG_INVALID_RGB_R), 1);
	if (parse_check_rgb_range(line, &i, &g) == -1)
		return (print_error(MSG_INVALID_RGB_G), 1);
	if (parse_check_rgb_range(line, &i, &b) == -1)
		return (print_error(MSG_INVALID_RGB_B), 1);
	*color = get_rgba(r, g, b, 255);
	return (0);
}
