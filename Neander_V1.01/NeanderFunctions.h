#ifndef NEANDERFUNCTIONS_H_INCLUDED
#define NEANDERFUNCTIONS_H_INCLUDED

#include "NeanderFunctions.c"

int instrConverter(char *instr);

int decpBinario(int n);
int binpDec(int n);

void fNeanderStatus(int *ac, int *n, int *z);

void fNop();
void fSta(int mem[], int *ac, int *pc);
void fLda(int mem[], int *ac, int *pc, int *n, int *z);
void fAdd(int mem[], int *ac, int *pc, int *n, int *z);
void fOr(int mem[], int *ac, int *pc, int *n, int *z);
void fAnd(int mem[], int *ac, int *pc, int *n, int *z);
void fNot(int *ac, int *n, int *z);
void fJmp(int mem[], int *pc);
void fJn(int mem[], int *ac, int *pc, int *n);
void fJz(int mem[], int *ac, int *pc, int *z);
void fHlt(int *pc);

#endif // NEANDERFUNCTIONS_H_INCLUDED
