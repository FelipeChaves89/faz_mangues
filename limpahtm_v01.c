    /*
    #define tam_linha 200
    char strglinha[tam_linha]; // vetor pra armazenar a linha
    while(fgets(strglinha,tam_linha,arq)!=NULL){
        if(strglinha[0]!='\n') { // se a linha não for vazia
            printf("Linha %i - %s",linhas,strglinha);
        }
        linhas++;
    }
    */

#include <stdio.h>
#include <stdio_ext.h> // __fpurge()
#include <string.h> // strcmp()

void pause(){
    __fpurge(stdin);
    getchar();
}

int main(){

    char nomearq1[]="lotfac.txt"; // arquivo que será lido
    char nomearq2[]="tags.txt"; // arquivo que será salvo as tags
    //char nomearq3[]=""; // arquivo que será salvo htm correto
    char ch;
    int onoff,linhas=1;

    FILE *arq,*tag;
    arq=fopen(nomearq1,"r"); // abre arquivo para leitura
        if(arq==NULL){ // finaliza o programa se não abrir o arquivo
            printf("Erro ao abrir arquivo\n\n\n");
            return 0;}
    tag=fopen(nomearq2,"w+"); // cria arquivo tag para leitura e gravação

    int trcont=0,tdcont=0; // variaveis da contagem de tr's e td's
    char tag_str[3]=""; // vetor para identificar a tag
    int chtag=0; // contador de limite da strcat()
    //int teste;

    while((ch=fgetc(arq))!=EOF){
        if(ch=='\n') linhas++; // conta quantas linhas tem o documento
        if(ch=='<'){ // putchar off
            fprintf(tag,"<");
            onoff=0;
            chtag=0;
            tag_str[0]='\0';
            continue;
        }
        if(ch=='>'){ // putchar on
            fprintf(tag,">\n");
            onoff=1;
            continue;
        }
        if(onoff==1) putchar(ch); // se putchar on, imprime a letra
        if(onoff==0){ // se putchar off
            fputc(ch,tag); // salva a letra no arquivo tag
            if(chtag<2){
                char catch[2]={ch,'\0'}; // cria string para concatenar
                strcat(tag_str,catch); // salva a letra na string
                chtag++;
                //teste=strcmp(tag_str,"td");
                //printf("ch=%c tag_str=%s [teste=%i]",ch,tag_str,teste);
                //pause();
                if(!strcmp(tag_str,"td")) {
                    tdcont++;
                    chtag=0;
                    tag_str[0]='\0';
                    //printf("ch=%c tag_str=%s [tdcont=%i]",ch,tag_str,tdcont);
                    //pause();
                }
                if(!strcmp(tag_str,"tr")) {
                    trcont++;
                    chtag=0;
                    tag_str[0]='\0';
                    //printf("ch=%c tag_str=%s [trcont=%i]",ch,tag_str,trcont);
                    //pause();
                }
            }
        }
    }

    fclose(arq);
    fclose(tag);
    printf("td=%i tr=%i linhas=%i \n\n",tdcont,trcont,linhas);
    return 0;

}
