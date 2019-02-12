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
#include <string.h> // strcmp() strcat()

void pause(){ // função para pausar a tela quando precisar verificar algo
    __fpurge(stdin);
    getchar();
}

int main(){

    char nomearq1[]="lotfac.txt"; // arquivo que será lido
    char nomearq2[]="tags.txt"; // arquivo que será salvo as tags
    char nomearq3[]="novohtm.txt"; // arquivo que será salvo htm correto
    

    FILE *arq,*tag,*new;
    arq=fopen(nomearq1,"r"); // abre arquivo para leitura
        if(arq==NULL){ // finaliza o programa se não abrir o arquivo
            printf("Erro ao abrir arquivo\n\n\n");
            return 0;}
    tag=fopen(nomearq2,"w+"); // cria arquivo tag para leitura e gravação
    new=fopen(nomearq3,"w+"); // cria arquivo new para leitura e gravação

    char ch;
    char tag_str[3]=""; // vetor para identificar a tag
    char fulltag[100]="<";
    int onoff,linhas=1;
    int trcont=0,tdcont=0; // variaveis da contagem de tr's e td's
    int chtag=0; // contador de limite da strcat()
    

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
            strcat(fulltag,">\n");
            fprintf(new,fulltag); // salva fulltag no arquivo new
            fulltag[0]='<'; // re-inicia a string
            fulltag[1]='\0'; // finaliza a linha
            continue;
        }
        char catch[2]={ch,'\0'}; // cria string para concatenar
        if(onoff==1) putchar(ch); // se putchar on, imprime a letra na tela
        if(onoff==0){ // se putchar off
            fputc(ch,tag); // [etapa 1] salva a letra no arquivo tag
            if(chtag<2){ // [etapa 2] limita o tamanho de catch[] pra 2 letras
                //char catch[2]={ch,'\0'}; // cria string para concatenar
                strcat(tag_str,catch); // salva a letra na string
                chtag++;
                if(!strcmp(tag_str,"td")) { // se for igual a 'td'
                    tdcont++;
                    chtag=0;
                    tag_str[0]='\0'; // limpa a string
                }
                if(!strcmp(tag_str,"tr")) { // se for igual a 'tr'
                    trcont++;
                    chtag=0;
                    tag_str[0]='\0'; // limpa a string
                }
            }
            strcat(fulltag,catch); // [etapa 3] concatena a tag completa
        }
    }

    fclose(arq);
    fclose(tag);
    printf("td=%i tr=%i linhas=%i \n\n",tdcont,trcont,linhas);
    return 0;

}
