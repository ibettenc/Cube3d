
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **load_map(const char *filename, int *out_width, int *out_height) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return NULL;
    }

    char **map = NULL;
    char buffer[1024];
    int width = 0;
    int height = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        int len = strlen(buffer);

        // Remove newline if present
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        // Track max width
        if (len > width) {
            width = len;
        }

        // Allocate space for a new row
        map = realloc(map, sizeof(char*) * (height + 1));
        map[height] = malloc(len + 1);
        strcpy(map[height], buffer);

        height++;
    }

    fclose(fp);

    *out_width = width;
    *out_height = height;
    return map;
}

void	flood_fill(char **map, int x, int y, int hit)
{
	if (y < 0 || y >= hit)
		return ;
	if (x < 0 || x >= (int) ft_strlen(map[y]))
		return ;
	if (map[y][x] != ' ')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int main(void)
{

}