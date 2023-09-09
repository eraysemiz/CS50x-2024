#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height > 8 || height < 1);

    for (int i = 0; i < height; i++)
    {
        for (int j = height - (i + 1); j > 0; j -= 1)
        {
            printf(" ");
        }

        for (int hash = 0; hash < i + 1; hash++)
        {
            printf("#");
        }

        printf("  ");

        for (int hash = 0; hash < i + 1; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
}