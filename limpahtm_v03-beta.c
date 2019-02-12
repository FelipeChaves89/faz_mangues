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

void pause(){
    __fpurge(stdin);
    getchar();
}
void concatenach(char *__strtag,char __ch){
    char catch[2]={__ch,'\0'};
    strcat(__strtag,catch);
}
int analisech(char __ch){
    if(__ch>='A'&&__ch<='Z') return 1;
    if(__ch>='a'&&__ch<='z') return 1;
    if(__ch=='<') return 1;
    return 0;
}

int main(){
    char nomearq1[]="lotfac.txt"; // arquivo que será lido
    //char nomearq2[]="tags.txt"; // arquivo que será salvo as tags
    char nomearq3[]="novohtm.htm"; // arquivo que será salvo htm correto
    FILE *arq,*new; // ,*tag
    arq=fopen(nomearq1,"r"); // abre arquivo para leitura
        if(arq==NULL){ // finaliza o programa se não abrir o arquivo
            printf("Erro ao abrir arquivo\n\n\n");
            return 0;}
    //tag=fopen(nomearq2,"w+"); // cria arquivo tag para leitura e gravação
    new=fopen(nomearq3,"w+"); // cria arquivo new para leitura e gravação

    char ch;

    // INICIO DO BOM
    char strtag[100]="";
    int onoff,travaonoff=1,proximo=0;

    while((ch=fgetc(arq))!=EOF){
        if(travaonoff==1){
            if(ch=='<'){ // fputc off
                onoff=0;
                continue;
            }
            if(ch=='>'){ // fputc on
                onoff=1;
                strtag[0]='\0'; // esvazia a string de teste
                continue;
            }
        }
        if(onoff==1) fputc(ch,new); // vai escrevendo o arquivo
        if(onoff==0){ // até achar o <
            concatenach(strtag,ch);
            if(!strcmp(strtag,"html")) fprintf(new,"<html>");
            if(!strcmp(strtag,"/html")) fprintf(new,"</html>");
            if(!strcmp(strtag,"table")) fprintf(new,"<table>");
            if(!strcmp(strtag,"/table")) fprintf(new,"</table>");
            if(!strcmp(strtag,"tr")) fprintf(new,"<tr>");
            if(!strcmp(strtag,"/tr")) fprintf(new,"</tr>");
            if(!strcmp(strtag,"td")){
                travaonoff=0; // desliga controle onoff [sempre onoff=0]
                continue;
            }
            if(travaonoff==0){
                if(ch=='>'){
                    proximo=1; // indica pra verificar o proximo caractere
                    continue;
                }
                if(proximo==1){ // verifica o proximo caractere
                    if(analisech(ch)){ // se for letra ou <
                        travaonoff=1;
                        proximo=0; // finaliza a escrita da tag
                        continue;
                    }
                    fprintf(new,"<td>"); // se não for grava a primeira tag
                    fputc(ch,new); // grava o primeiro caractere
                    proximo=2; // e passa pro proximo
                    continue;
                }
                if(proximo==2){
                    if(ch=='<'){ // se achar o fechamento da tag
                        fprintf(new,"</td>"); // fecha a tag e reinicia padrão do programa
                        travaonoff=1; // liga o controle onoff
                        proximo=0; // reinicia o procedimento
                    }
                    else fputc(ch,new); // se não vai escrevendo o conteudo da tag
                }
            }
            /*printf("%s\n%i %i %i\n",strtag,onoff,travaonoff,proximo);
            pause(); // DEPURAÇÃO*/
        }
    }
    // FIM DO BOM

    /*
    char tag_str[3]=""; // vetor para identificar a tag
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
        }
    }
    */
    fclose(arq);
    //fclose(tag);
    fclose(new);
    return 0;

}
