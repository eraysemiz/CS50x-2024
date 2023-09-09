#include <cs50.h>
#include <stdio.h>
#include <string.h>
// 4003600000000014
int main(void)
{
    long card_number;
    printf("Card number: ");
    scanf("%li", &card_number);

    char card_string[20];
    sprintf(card_string, "%li", card_number);

    int length = strlen(card_string);

    int check = 0;
    int sum = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        int digit = card_string[i] - '0';

        if (check % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = digit % 10 + 1;
            }

            sum += digit;
        }
        check++;
    }
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if ((card_string[0] == '3') && (strlen(card_string) == 15) && (card_string[1] == '4' || card_string[1] == '7'))
        {
            printf("AMEX\n");
        }

        else if ((card_string[0] == '5') && (strlen(card_string) == 16) &&
                 (card_string[1] == '1' || card_string[1] == '2' || card_string[1] == '3' || card_string[1] == '4' ||
                  card_string[1] == '5'))
        {
            printf("MASTERCARD\n");
        }

        else if ((card_string[0] == '4') && (strlen(card_string) == 13 || strlen(card_string) == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}