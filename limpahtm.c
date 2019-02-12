#include <stdio.h>
#include <stdio_ext.h> // __fpurge()
#include <string.h> // strcmp() strcat()

void pause(){
    __fpurge(stdin);
    getchar();
}
void dbug(char __char,char *__str,int __int1,int __int2, int __int3){
    if(__char==1) printf("%i\t%i\t%i\n",__int1,__int2,__int3);
    else printf("%c\t%s\n%i\t%i\t%i\n",__char,__str,__int1,__int2,__int3);
    pause();
}
void concatenach(char *__strtag,char __ch){
    if(__ch!='<'&&__ch!='>'){
        char catch[2]={__ch,'\0'};
        strcat(__strtag,catch);
    }
}
int analisech(char __ch){
    if(__ch>='A'&&__ch<='Z') return 1;
    if(__ch>='a'&&__ch<='z') return 1;
    //if(__ch=='<') return 1;
    //if(__ch=='\n') return 1;
    return 0;
}

int main(){
    FILE *arq,*new,*sli;
    sli=fopen("teste.txt","r"); // abre arquivo para leitura
    if(arq==NULL){ // finaliza o programa se não abrir o arquivo
        printf("Erro ao abrir arquivo\n\n\n");
        return 0;
    }
    arq=fopen("semlinha.htm","w+");
    char _ch;
    while((_ch=fgetc(sli))!=EOF){
        if(_ch!='\n') fputc(_ch,arq);
    }
    fclose(sli);
    rewind(arq);
    new=fopen("novohtm.htm","w+"); // cria arquivo new para leitura e gravação

    char ch,strtag[100]="";
    int onoff=0,travaonoff=1,proximo=0;

    while((ch=fgetc(arq))!=EOF){
        //dbug(ch,strtag,onoff,travaonoff,proximo); // [DEPURAÇÃO]
        if(travaonoff==1){
            if(ch=='<'){ // fputc off
                onoff=0;
                strcpy(strtag,""); // esvazia a string de teste
                continue;
            }
            if(ch=='>'){ // fputc on
                onoff=1;
                strcpy(strtag,""); // esvazia a string de teste
                continue;
            }
        }
        if(onoff==1) fputc(ch,new); // vai escrevendo o arquivo
        if(onoff==0){ // até achar o <
            concatenach(strtag,ch); // cria a string pra comparar
            dbug(ch,strtag,onoff,travaonoff,proximo); // [DEPURAÇÃO]
            if(travaonoff==0){
                if(ch=='>'){ // espera passar a primeira tag
                    proximo=1; // indica pra verificar o proximo caractere
                    continue;
                }
                if(proximo==1){ // verifica o proximo caractere
                    if(analisech(ch)){ // se for letra
                        travaonoff=1;
                        proximo=0;         // finaliza a escrita da tag
                        continue;
                    }
                    if(ch=='<') continue;
                    if(ch!='/'){
                        if(strtag[1]=='d') fprintf(new,"<td>"); // se não for grava a primeira tag td
                        if(strtag[1]=='r') fprintf(new,"<tr>\n"); // ou primeira tag tr
                        fputc(ch,new); // grava o primeiro caractere
                        proximo=2; // e passa pro proximo
                        char _str[2]={ch,'\0'};
                        strcpy(strtag,_str); // coloca string só com letra
                        printf("%s\t%s",_str,strtag);
                        continue;
                    }
                }
                if(proximo==2){
                    if(ch=='<'){ // se achar o fechamento da tag
                        if(strtag[1]=='d') fprintf(new,"</td>\n"); // fecha a tag td
                        if(strtag[1]=='r') fprintf(new,"</tr>\n"); // ou tag tr
                        travaonoff=1;
                        proximo=0;         // finaliza a escrita da tag
                    }
                    else fputc(ch,new); // se não vai escrevendo o conteudo da tag
                }
            }
            if(!strcmp(strtag,"html")) fprintf(new,"<html>\n");
            if(!strcmp(strtag,"/html")) fprintf(new,"</html>\n");
            if(!strcmp(strtag,"table")) fprintf(new,"<table>\n");
            if(!strcmp(strtag,"/table")) fprintf(new,"</table>\n");
            if(!strcmp(strtag,"td")||!strcmp(strtag,"tr")) travaonoff=0; // desliga controle onoff [sempre onoff=0]
        }
    }
    fclose(arq);
    fclose(new);
    return 0;
}
