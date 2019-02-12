/*
    ./limpahtm2

    Programa final para organizar as TAGs do arquivo
    htm baixado do site da Caixa com os resultados
    da lotofácil.

    Escrito por Felipe Chaves
*/

#include <stdio.h>
#include <stdio_ext.h> // __fpurge()
#include <string.h> // strcmp() strcat()
#define tam_linha 100 // tamanho maximo da linha da segunda etapa

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
    if(__ch==' ') return 1;
    if(__ch=='&') return 1;
    return 0;
}

int main(){
    // INICIO DO PRIMEIRO PROCESSAMENTO
    // CARACTERE POR CARACTERE
    char nomearq1[20];
    char nomearq2[30]="novo_";
    char nomearq3[30]="final_";
    FILE *arq,*new,*final;
    do{
        printf("Nome do arquivo: ");
        gets(nomearq1);
        //scanf("%s",nomearq1);
        arq=fopen(nomearq1,"r"); // abre arquivo para leitura
        if(arq==NULL){ // informa erro e volta
            printf("Erro ao abrir arquivo\n\n");
        }
    }while(arq==NULL);
    strcat(nomearq2,nomearq1);
    strcat(nomearq3,nomearq1);
    new=fopen(nomearq2,"w+"); // cria arquivo new para leitura e gravação
    final=fopen(nomearq3,"w"); // cria o arquivo final para gravação

    char ch,strtag[100]="";
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
        }
    }
    fclose(arq);
    // FIM DO PRIMEIRO PROCESSAMENTO
    // AGORA É LINHA POR LINHA
    rewind(new); // volta pro inicio do arquivo
    char strglinha[tam_linha]; // vetor pra armazenar a linha
    int prova=0;

    while(fgets(strglinha,tam_linha,new)!=NULL){
        printf("%i\t%s",prova,strglinha); // [DEPURAÇÃO]
        pause(); // [DEPURAÇÃO]
        if(strglinha[0]!='\n') { // se a linha não for vazia
            // depois
            if(prova==1){
                if(!strcmp(strglinha,"</tr>\n")){
                    prova=0;
                    continue;
                }else{ // ou escreve no arquivo final
                fprintf(final,"<tr>\n%s",strglinha);
                prova=0;
                continue;
                }
            }
            // primeiro
            if(!strcmp(strglinha,"<tr>\n")){ // verifica
                prova=1;
                continue;
            }else{ // se não for <tr> escreve a linha
                fprintf(final,"%s",strglinha);
                continue;
            }
        }
    }
    fclose(final);
    return 0;
}
