#include <stdio.h>
#include <stdlib.h>


// 0xff 0xd8 0xff 0xe

typedef unsigned char BYTE;

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

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);   // calculating the size of the file
    fseek(file, 0, SEEK_SET);

    find_jpeg(file, file_size);

}


void find_jpeg(FILE *file, int file_size)
{
    BYTE buffer[512];
    fread(buffer, 512, 1, file);
    if (buffer[0] ==  0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            read_file(file, filesize);
            return 0;
        }
    else
    {
        find_jpeg(file);
    }
}

int read_file(FILE *file, int file_size)
{
    BYTE buffer[512];
    int jpg_count = 0;

    char *filename;
    sprintf(filename, "%03i.jpg", jpg_count);
    FILE *img = fopen(filename, "w");

    unsigned int position = ftell(file);

    for (int i = ftell(file), a = 0; i < file_size ; a++)
    {
        fwrite(buffer, 512, 1, img);
        fread(buffer, 512, 1, file);
        if (buffer[0] ==  0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            jpg_count++;
            read_file(file, file_size);
        }
        else
        {
            fwrite(buffer, 512, 1, img);
        }
    }


}


