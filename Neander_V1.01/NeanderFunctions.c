#include <string.h>
#include <stdlib.h>

//Versao atual

#define VERSAO 1.01     //resolvido problema de combatibilidade com o linux
//#define VERSAO 1.00

// Conjuto de instrucoes

#define NOP		0
#define STA		1
#define LDA		2
#define ADD		3
#define OR		4
#define AND		5
#define NOT		6
#define JMP		8
#define JN		9
#define JZ		10
#define HLT		15

int instrConverter(char *instr){                                  //completo
    int ins = 0;

    if(strcmp(instr, "NOP") == 0){
        return NOP;
    }
    if(strcmp(instr, "STA") == 0){
        return STA;
    }
    if(strcmp(instr, "LDA") == 0){
        return LDA;
    }
    if(strcmp(instr, "ADD") == 0){
        return ADD;
    }
    if(strcmp(instr, "OR" ) == 0){
        return OR;
    }
    if(strcmp(instr, "AND") == 0){
        return AND;
    }
    if(strcmp(instr, "NOT") == 0){
        return NOT;
    }
    if(strcmp(instr, "JMP") == 0){
        return JMP;
    }
    if(strcmp(instr, "JN" ) == 0){
        return JN;
    }
    if(strcmp(instr, "JZ" ) == 0){
        return JZ;
    }
    if(strcmp(instr, "HLT") == 0){
        return HLT;
    }

    ins = atoi(instr);

    if((ins > -1) && (ins < 256) ){
        return ins;
    }

    return HLT;
}

int decBin(int n){                                                //completo
    int bin[9], i = 0;
    
    for(i = 9; i >= 0; i--){
        if(n > 0){
            bin[i] = n%2;
            n /= 2;
        }
        else
            bin[i] = 0;
    }
    for(i = 0; i <= 9; i++){
        n *= 10;
        n += bin[i];
    }
    printf("essa eh a string: %d\n", n);
    return n;
}

int binpDec(int n){                                               //completo
    int deci = 0, pot = 1;

    while(n > 0) {
        deci += n % 10 * pot;
        n = n / 10;
        pot = pot * 2;
    }
    return deci;
}

void fNeanderStatus(int *ac, int *n, int *z){                     //completo
    if(*ac < 0){
        *n = 1;
    }
    else if(*ac == 0){
        *z = 1;
    }
}

void fNop(){                                                      //completo
 //faz nada.......
}

void fSta(int mem[], int *ac, int *pc){                           //completo
    mem[mem[*pc + 1]] = *ac;
    *pc++;
}

void fLda(int mem[], int *ac, int *pc, int *n, int *z){           //completo
    *ac = mem[mem[*pc + 1]];
    *pc++;
    fNeanderStatus( ac, n, z);
}

void fAdd(int mem[], int *ac, int *pc, int *n, int *z){           //completo
    *ac = *ac + mem[mem[*pc + 1]];
    *pc++;
    fNeanderStatus(ac, n, z);
}

void fOr(int mem[], int *ac, int *pc, int *n, int *z){            //completo
    char bin[9];

    //itoa(*ac | mem[mem[*pc + 1]] , bin, 2);


    *ac = binpDec(decBin(*ac | mem[mem[*pc + 1]]));
    *pc++;
    fNeanderStatus(ac, n, z);
}

void fAnd(int mem[], int *ac, int *pc, int *n, int *z){           //completo
    char bin[9];
    //itoa((*ac & mem[mem[*pc + 1]] ), bin, 2);

    //*ac = binpDec(atoi(bin));
    *ac = binpDec(decBin(*ac | mem[mem[*pc + 1]]));
    *pc++;

   fNeanderStatus(ac, n, z);
}

void fNot(int *ac, int *n, int *z){                               //completo
    *ac = ~(*ac);
    fNeanderStatus(ac, n, z);
}

void fJmp(int mem[], int *pc){                                    //completo
    *pc = (mem[*pc + 1]) - 1;
    *pc++;
}

void fJn(int mem[], int *ac, int *pc, int *n){                     //completo
    if(*n == 1){
        *pc = (mem[*pc + 1]) - 1;
    }
    else{
        *pc++;
    }
}

void fJz(int mem[], int *ac, int *pc, int *z){                     //completo
    if(*z == 1){
        *pc = (mem[*pc + 1]) - 1;
    }
    else{
        *pc++;
    }
}

void fHlt(int *pc){                                               //completo
    *pc = 255;
}

