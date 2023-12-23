// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

void replace(string word);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    string word = argv[1];
    replace(word);
    return 0;
}

void replace(string word)
{
    char new_word[100];
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == 'a')
        {
            new_word[i] = '6';
        }
        else if (word[i] == 'e')
        {
            new_word[i] = '3';
        }
        else if (word[i] == 'i')
        {
            new_word[i] = '1';
        }
        else if (word[i] == 'o')
        {
            new_word[i] = '0';
        }
        else
        {
            new_word[i] = word[i];
        }
    }
    new_word[strlen(word)] = '\0';

    printf("%s\n", new_word);

}

