#include "stdio.h"
#include "string.h"

int erdem_strlen(char* c);
void erdem_strcpy(char* dst, char* src);

int main()
{
    // strlen function implementation - counting number of chars in a string
    printf("string.h function : %d\n", strlen("erdem test string"));
    printf("assembly function : %d\n", erdem_strlen("erdem test string"));

    // strcpy implementation
    char char1 [] = "erdem sukr";
    char char2 [5];
    strcpy(char2, char1);

    for (int i=0; i<10; i++) {
        //printf("char1[%d] = %02X\n", i, (unsigned char)char1[i]);
    }

    for (int i=0; i<10; i++) {
        //printf("char2[%d] = %02X\n", i, (unsigned char)char2[i]);
    }
    printf("char1 length sys:%d erdem:%d\n", strlen(char1), erdem_strlen(char1));
    for (int i=0; i<erdem_strlen(char1); i++)
        printf("char1 %d %c\n", (unsigned char)char1[i], char1[i]);

    printf("char2 length sys:%d erdem:%d\n", strlen(char2), erdem_strlen(char2));
    for (int i=0; i<erdem_strlen(char2); i++)
        printf("char2 %d %c\n", (unsigned char)char2[i], char2[i]);

    //printf("write %d\n", '\0');
    //printf("wiite %s\n", char1[12]);
    //printf("wiite %s\n", char2[10]);
    //printf("assembly function : %s\n", char2);
    while (1)
    {

    }

    return 0;
}
