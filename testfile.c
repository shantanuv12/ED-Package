#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE *file= fopen("testfile.txt","w");
    int a=0,b=1;
    fprintf(file, "%d %d\n",a,b);
    fclose(file);
    return 0;
}
