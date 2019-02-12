#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>

char *fgets_unlocked (char *__restrict __s, int __n,FILE *__restrict __stream);
void pause(){
    __fpurge(stdin);
    getchar();
}

void main(){
    FILE *arq1,*arq2;
    arq1=fopen("fac.htm","r");
    arq2=fopen("fac2.htm","r");
    long int pp1,pp2;

    // fgets()
    char str1[100],str2[100];
    
    /*do{
        fgets(str1,100,arq1);
        fgets(str2,100,arq2);
        printf("%s\t%s",str1,str2);
        pause();
    }while(ftell(arq1)!=EOF);*/

    while(fgets(str1,100,arq1)!=NULL){
        fgets_unlocked(str2,100,arq2);
        //fgets(str2,100,arq2);
            pp1=ftell(arq1);
            pp2=ftell(arq2);
            printf("%i\t%i",pp1,pp2);
            pause();
        printf("%s%s",str1,str2);
        pause();
    }

    // fgetc() [TUDO CONFERIDO]
    //char ch1,ch2;

    /*do{
        ch1=fgetc(arq1);
        ch2=fgetc(arq2);
        printf("%c\t%c",ch1,ch2);
        pause();
    }while(ch1!=EOF);*/

    /*while((ch1=fgetc(arq1))!=EOF){
        ch2=fgetc(arq2);
        printf("%c\t%c",ch1,ch2);
        pause();
    }*/

    fclose(arq1);
    fclose(arq2);
}

/*
*/