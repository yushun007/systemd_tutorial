#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char**argv){
    int count = 0;
    char *model = malloc(25);
    if(argc ==2){
        model = argv[1];
        while (1)
        {
            sleep(1);
            count++;
            printf("count = %d\n",count);
            printf("model:%s\n",model);
        }
    }
    return 0;
}