#include "stdio.h"
#include "string.h"
#include "fcntl.h"
#include <unistd.h>

int erdem_strlen(char* c);
void erdem_strcpy(char* dst, char* src);
int erdem_strcmp(char* c1, char* c2);
int erdem_open(char* fileName, int flags);
ssize_t erdem_read(int fd, void* buf, size_t count);
ssize_t erdem_write(int fd, const void* buf, size_t count);
char* erdem_strdup(const char* source);

int main()
{
    printf("testing \n");
    // strlen function implementation - counting number of chars in a string
    printf("string.h function len: %d\n", (int)strlen("erdem test string"));
    printf("assembly function len: %d\n", erdem_strlen("erdem test string"));

    // strcpy implementation
    char source1 [] = "erdem_sukr";
    char dest1 [11];
    char source2 [] = "erdem_sukr";
    char dest2 [11];
    
    strcpy(dest1, source1);
    erdem_strcpy(dest2, source2);

    printf("string.h function copy: src: %s dst: %s\n", source1, dest1);
    printf("assembly function copy: src: %s dst: %s\n", source2, dest2);

    char cmp1 [] = "1aağt";
    char cmp2 [] = "1aağt";

    printf("string.h cmp: %d\n", strcmp(cmp1, cmp2));
    printf("assembly cmp: %d\n", erdem_strcmp(cmp1, cmp2));

//    int fileFD = open("erdem.txt", O_WRONLY | O_APPEND | O_RDONLY);
    int fileFD = open("erdem.txt", O_WRONLY);

    printf("filed1 %d\n", fileFD);
    char buf[100] = "deneme test 123";
    int readCount = erdem_write(fileFD, (void *)buf, 15);

    printf("file1 ridden %d\n", readCount);
    printf("file1 ridden %s\n", buf);

    char copyChars[] = "Very long test string but it is a char array since such thing as string does not exist here in c world.";
    char* res = erdem_strdup(&copyChars);

    printf("copied: %s\n", res);

    return 0;
}
