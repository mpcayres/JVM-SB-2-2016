#include <stdio.h>
#include <stdlib.h>

#include "GerenciaPilha.h"

static u4 pilha[tamanho_maximo_pilha];
static u4 topo;
static u4 frame_base;


void novaPilha() {
	topo = -1;
	frame_base = 0;
}

void pushU8(u8 valoru8) {
	u4 low, high;
	shift64To32(valoru8, &low, &high);
	push(high);	push(low);
}

void push(u4 valoru4) {
	if (topo == tamanho_maximo_pilha) {
		printf("\nErro: pilha sem espaco disponivel.\n");
		exit(1);
	} else pilha[++topo] = valoru4;
}

u4 pop() {
	if (topo < frame_base) {
		printf("\nErro: acesso em posicao invalida da pilha.\n");
		return 0;
	} return pilha[topo--];
}

void novoFramePilha() {
	push(frame_base);
	frame_base = topo;
}

void liberaFramePilha() {
	u4 frame_anterior;
	topo = frame_base;
	frame_anterior = pop();
	
	if (frame_anterior > frame_base) {
		printf("\nErro: acesso em posicao invalida da pilha, frame nao existe.\n");
	} else frame_base = frame_anterior;
}
