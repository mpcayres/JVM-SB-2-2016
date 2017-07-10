#include <stdlib.h>

#include "GerenciaFrames.h"

static struct pilhaFrames *pilha = NULL;

void popularFrame(classStructure *class, cpInfo *constantPool, attributeInfo *attribute){
	pilha->valor->class = class;
	pilha->valor->constantPool = constantPool;
	pilha->valor->maxStack = attribute->type.Code.maxStack;
	pilha->valor->maxLocals = attribute->type.Code.maxLocals;
	pilha->valor->codeLength = attribute->type.Code.codeLength;
	pilha->valor->code = attribute->type.Code.code;
	pilha->valor->fields = calloc(sizeof(u4), pilha->valor->maxLocals);
	pilha->valor->pc = 0;
}

void novoFrame(classStructure *class, cpInfo *constantPool, attributeInfo *attribute) {
	struct pilhaFrames *novo;
	novo = calloc(sizeof(struct pilhaFrames), 1);
	novo->valor = calloc(sizeof(struct frame), 1);
	novo->prox = pilha;

	pilha = novo;
	popularFrame(class, constantPool, attribute);
	
	frame_corrente = pilha->valor;
	novoFramePilha();
}

void liberaFrame() {
	struct pilhaFrames *proximo;
	
	if(pilha != NULL) {
		proximo = pilha->prox;
		free(pilha->valor->fields); free(pilha->valor); free(pilha);
		pilha = proximo;
		
		liberaFramePilha();
	}
}
