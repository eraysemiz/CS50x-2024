#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 0xff 0xd8 0xff 0xe

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int create_jpeg(FILE *file);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("Usage: ./recover filename\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        perror("Cannot open the given file\n");
        return 1;
    }
    create_jpeg(file);
    fclose(file);
}

// ilk .jpg dosyasını bul

int create_jpeg(FILE *file)
{
    int jpg_count = 0;
    int counter = 0;
    BYTE buffer[512];
    char filename[8];
    FILE *img = fopen("test.jpg", "w");

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpg_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                counter = 1;
                jpg_count++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpg_count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                jpg_count++;
            }
        }
        else
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }
    fclose(img);
    return 0;
}
