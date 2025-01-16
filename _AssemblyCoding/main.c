#include "stdio.h"
#include "string.h"

int erdem_strlen(char* c);

int main()
{
    //if (maxofthree(1,2,3) == 3)
    printf("string.h function : %d\n", strlen("erdem test string"));
    printf("assembly function : %d\n", erdem_strlen("erdem test string"));
    return 0;
}
