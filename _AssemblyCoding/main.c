#include "stdio.h"
#include "string.h"

int erdem_strlen(char* c);
void erdem_strcpy(char* dst, char* src);
int erdem_strcmp(char* c1, char* c2);

int main()
{
    // strlen function implementation - counting number of chars in a string
    printf("string.h function len: %d\n", strlen("erdem test string"));
    printf("assembly function len: %d\n", erdem_strlen("erdem test string"));

    // strcpy implementation
    char source1 [] = "erdem_sukr";
    char dest1 [11];
    strcpy(dest1, source1);
    
    char source2 [] = "erdem_sukr";
    char dest2 [11];
    erdem_strcpy(dest2, source2);

    printf("string.h function copy: src: %s dst: %s\n", source1, dest1);
    printf("assembly function copy: src: %s dst: %s\n", source2, dest2);

    char cmp1 [] = "1";
    char cmp2 [] = "1";

    printf("string.h cmp: %d\n", strcmp(cmp1, cmp2));
    printf("assembly cmp: %d\n", erdem_strcmp(cmp1, cmp2));

    return 0;
}
