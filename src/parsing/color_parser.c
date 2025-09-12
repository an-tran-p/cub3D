#include "cub3d.h"

uint32_t get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int validate_rgb_format(char *line)
{
    int i;
    int comma_count;
    int digit_num;

    i = 0;
    comma_count = 0;
    digit_num = 0;
    while (line[i] && line[i] != '\n')
    {
        if (ft_isdigit(line[i]))
        {
            while (line[i] && ft_isdigit(line[i]))
                i++;
            digit_num++;
        }
        else if (line[i] == ',')
        {
            comma_count++;
            i++;
        }
        else if (line[i] == ' ')
            i++;
        else
        {
            print_error("Invalid RGB: invalid character\n");
            return (1);
        }    
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

int save_color(uint32_t	*color, char *line)
{
    int i;
    int r;
    int g;
    int b;

    if (*color != (uint32_t)-1)
    {
        print_error("Duplicate color identifier\n");
        return (1);
    }
    if (validate_rgb_format(line) != 0)
        return (1);
    i = 0;
    while(line[i] == ' ' && line[i])
        i++;
    r = ft_atoi(line + i);
    if (r < 0 || r > 255)
    {
        print_error("Invalid RGB: R is outside the range 0-255\n");
        return (1);
    }
    while(ft_isdigit(line[i]) && line[i])
        i++;
    while(line[i] != ',' && line[i])
        i++;
    if (line[i] == ',')
        i++;
    while(line[i] == ' ' && line[i])
        i++;
    g = ft_atoi(line + i);
    if (g < 0 || g > 255)
    {
        print_error("Invalid RGB: G is outside range 0-255\n");
        return (1);
    }
    while(ft_isdigit(line[i]) && line[i])
        i++;
    while(line[i] != ',' && line[i])
        i++;
    if (line[i] == ',')
        i++;
    while(line[i] == ' ' && line[i])
        i++;
    b = ft_atoi(line + i);
    if (b < 0 || b > 255)
    {
        print_error("Invalid RGB: B is outside range 0-255\n");
        return (1);
    }
    *color = get_rgba(r, g, b, 255);
    printf("%d, %d, %d\n", r, g, b);
    return (0);
}
