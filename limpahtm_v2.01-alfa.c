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
#define tam_linha 100

void pause(){
    __fpurge(stdin);
    getchar();
}
void dbug(char __char,char *__str,int __int1,int __int2, int __int3){
    if(__char==1) printf("%i\t%i\t%i\n",__int1,__int2,__int3);
    else if(__char==2) printf("%i\t%s",__int1,__str);
    else printf("%c\t%s\n%i\t%i\t%i\n",__char,__str,__int1,__int2,__int3);
    pause();
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
    char nomearq1[]="lotfac.txt"; // arquivo que será lido
    char nomearq2[]="novo.htm"; // arquivo que será salvo htm correto
    FILE *arq,*new; // ,*tag
    arq=fopen(nomearq1,"r"); // abre arquivo para leitura
        if(arq==NULL){ // finaliza o programa se não abrir o arquivo
            printf("Erro ao abrir arquivo\n\n\n");
            return 0;}
    new=fopen(nomearq2,"w+"); // cria arquivo new para leitura e gravação

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
    //fclose(new);
    // FIM DO PRIMEIRO PROCESSAMENTO
    // AGORA É LINHA POR LINHA
    rewind(new); // volta pro inicio do arquivo
    FILE *final;
    final=fopen("final.htm","w+"); // cria o arquivo final para gravação

    char strglinha[tam_linha]; // vetor pra armazenar a linha
    int prova=0;

    while(fgets(strglinha,tam_linha,new)!=NULL){
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
