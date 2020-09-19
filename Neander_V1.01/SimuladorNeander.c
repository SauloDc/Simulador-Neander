#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NeanderFunctions.h"

void limpaChar(char chr[]){ // completo
	chr[0] = '\0';
	chr[1] = '\0';
	chr[2] = '\0';
	chr[3] = '\0';
	chr[4] = '\0';
}

int carregarMemoria(char nome[], int mem[]){  // completo
    int instrucao = 0, cont = 0, n_instr, n_endereco, n;
    char chr_atual, instr[5], endereco[5], asc = ' ';

    FILE *arq;

    arq = fopen(nome, "r");
    limpaChar(instr);
    limpaChar(endereco);

    if (arq == NULL) {
		printf("Erro ao abrir o arquivo ");
		exit(1);
	}

	while((chr_atual = getc(arq)) != -1){
        n = chr_atual;
        if(n == 32){
            instrucao = 1;
            cont = 0;
        }
        else if(n == 10){
            n_endereco = atoi(endereco);
            n_instr = atoi(instr);

            mem[n_endereco] = n_instr;
            instrucao = 0;
            cont = 0;

            limpaChar(instr);
            limpaChar(endereco);
        }
        if(instrucao == 1){
            instr[cont] = chr_atual;
           //printf("%s",instr);
        }
        else{
            endereco[cont] = chr_atual;
            //printf("%s",endereco);
        }
        cont++;
        //printf("%d ",cont);
	}

    fclose(arq);
}

void gerarModelo(){  // completo

    char nome[50];
    int cont, sel;

    FILE *arq;
    printf("\n--------------------Gerar Modelo-------------------- \n");
    printf("Caso voce va codificar de forma manual, note que voce deve \n");
    printf("atender a todos os padroes estabelecidos no manual. \n");
    printf("do contrario o programa pode apresentar mau funcionamento\n");
    printf("Digite um nome para o Arquivo de modelo. \n");
    printf(">> ");
    scanf("%s", nome);
    strcat(nome, ".neander");

    arq = fopen(nome, "w");

    for (cont = 000; cont < 256; cont++){
        fprintf(arq, "%d \n", cont);
    }
    fclose(arq);

    //system("cls");

    printf("\nModelo criado como: %s \n \n", nome);
}

void ecreverCodigo(){  // completo
    char instr[4], nome[50];
    int endereco, inst;
    FILE *arq;

    printf("\n--------------------Escrever Codigo:-------------------- \n");
    printf("As linhas de codigo nao precisao ser escritas em ordem. \n");
    printf("por exemplo: \n");
    printf("End: 128. Dados: 10  \n");
    printf("End:   0. Dados: LDA \n");
    printf("\n");
    printf("note que os dados devem ser escritos em Decimais\n");
    printf("e ja as intrucoes com letras maiusculas\n");
    printf("esse modo se encerra quando o programador insere o HLT \n");
    printf("\n");

    printf("Digite um nome para o Arquivo. \n");
    printf(">> ");
    scanf("%s", nome);
    strcat(nome, ".neander");

    arq = fopen(nome, "w");

    for(;;){
        printf("\nEndereco:\n");
        printf(">> ");
        scanf("%d", &endereco);

        printf("\nDados:\n");
        printf(">> ");
        scanf("%s", instr);

        inst = instrConverter(instr);

        fprintf(arq,"%d %d\n", endereco, inst);

        if(inst == HLT){
            break;
        }
        printf("\n");
    }

    fclose(arq);
    printf("\nArquivo criado como: %s \n \n", nome);
}

void zerarMemoria(int vet[]){  // completo
    int cont;
    for(cont = 0; cont < 256; cont++){
        vet[cont] = 0;
    }

}

void imprimir(int vet[]){  // completo
    int cont;

    printf("\n| End|  Dad|  End|  Dad|  End|  Dad|  End|  Dad|  End|  Dad|  End|  Dad|  End|  Dad|  End|  Dad|");

    for(cont = 0; cont < 256; cont++){
        if(cont % 8 == 0){
            printf("\n  ");
        }

        if(cont < 10){
            if(vet[cont] == 0)
                printf("00%d   ---   ",cont);
            else
                printf("00%d   %3d   ",cont, vet[cont]);
        }
        else if(cont > 9 && cont < 100){
            if(vet[cont] == 0)
                printf("0%d   ---   ",cont);
            else
                printf("0%d   %3d   ",cont, vet[cont]);
        }
        else {
            if(vet[cont] == 0)
                printf("%d   ---   ",cont);
            else
                printf("%d   %3d   ",cont, vet[cont]);
        }

    }
    printf("\n \n");
}

void sobre(){
    printf("\n---------------------------------------------------------\n");
    printf("|                                                       |\n");
    printf("| Simulador Neander  v%.2f                              |\n", VERSAO);
    printf("| Criado por Saulo de Castro                            |\n");
    printf("|                                                       |\n");
    printf("| Disciplina: Arquitetura de Computadores               |\n");
    printf("| Prof: Walisson F. Pereira                             |\n");
    printf("|                                                       |\n");
    printf("| Em caso de duvidas leia a documentacao em PDF         |\n");
    printf("---------------------------------------------------------\n");
}

void executarCodigo(int mem[]){
    int pc, ac = 0, n = 0, z = 0, ri;
    char nome[50];

    printf("\n----------------------Executar Codigo:---------------------- \n");
    printf("Durante a execucao do codigo, o Simulador Neander le todas as\n");
    printf("informacoes na memoria e executa conforme o programa carregado. \n");
    printf("Sendo assim, Digite o nome do Programa.\n");
    printf(">> ");
    scanf("%s", nome);

    strcat(nome, ".neander");

    carregarMemoria(nome, mem);

    for(pc = 0; pc < 256; pc++){

        ri = mem[pc];

        printf("------Simulador Neander------\n");
        printf("Cp: %d; Ac: %d;Ri: %d Z: %d; N: %d; \n \n", pc, ac, ri, z, n);

        switch(ri){
            case NOP:{
                fNop();
                break;
            }
            case STA:{
                fSta(mem, &ac, &pc);
                break;
            }
            case LDA:{
                fLda(mem, &ac, &pc, &n, &z);
                break;
            }
            case ADD:{
                fAdd(mem, &ac, &pc, &n, &z);
                break;
            }
            case OR:{
                fOr(mem, &ac, &pc, &n, &z);
                break;
            }
            case AND:{
                fAnd(mem, &ac, &pc, &n, &z);
                break;
            }
            case NOT:{
                fNot(&ac, &n, &z);
                break;
            }
            case JMP:{
                fJmp(mem, &pc);
                break;
            }
            case JN:{
                fJn(mem, &ac, &pc, &n);
                break;
            }
            case JZ:{
                fJz(mem, &ac, &pc, &z);
                break;
            }
            case HLT:{
                fHlt(&pc);
                break;
            }
        }
    }
    imprimir(mem);
}

int main() {
    int select = 1;
    int memoria[256];

    zerarMemoria(memoria);

    do{
        printf("\nSimulardor Neander %.2f\n\n", VERSAO);
        printf("--------------- Menu --------------- \n\n");
        printf("Escolha uma das opcoes: \n \n");
        printf("1 - Gerar Modelo para codificacao manual. \n");
        printf("2 - Escrever Codigo e Salvar em arquivo. \n");
        printf("3 - Executar Codigo existente. \n");
        printf("4 - Imprimir estado atual da memoria. \n");
        printf("5 - Sobre o Simulador. \n");
        printf("0 - Sair \n \n");
        printf("=>  ");
        scanf("%d",&select);

        //system("cls");

        switch(select){

            case 1:{
                gerarModelo();
                break;
            }
            case 2:{
                ecreverCodigo();
                break;
            }
            case 3:{
                executarCodigo(memoria);
                break;
            }
            case 4:{
                imprimir(memoria);
                break;
            }
            case 5:{
                sobre();
                break;
            }
            case 0:{
                exit(0);
                break;
            }
        }

    }while(select);

    return 0;
}







