#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size;
    int end_size;
    do
    {
        printf("Start size: ");
        scanf("%i", &start_size);
    }
    while (start_size < 9);

    do
    {
        printf("End size: ");
        scanf("%i", &end_size);
    }
    while (end_size < start_size);

    int size = start_size;
    int years = 0;
    while (size < end_size)
    {
        years++;
        int dead = size / 4;
        int born = size / 3;
        size += born;
        size -= dead;
    }
    printf("Years: %i\n", years);
}
