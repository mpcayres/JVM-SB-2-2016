/**  @file: GerenciaFrames.h
 * @brief Arquivo de Frames
 * 
 * @details Aqui sao declaradas todas estruturas de gerencia de frames
 */
#ifndef FRAME_H
#define FRAME_H

#include "GerenciaPilha.h"
#include "FuncoesAuxiliares.h"

/** Estrutura de um frame */
struct frame {
	/** Campos */
	u4 *fields;
	/** Pool de constantes */
	cpInfo *constantPool;
	/** Classe corrente */
	classStructure 	*class;
	/** Tamanho maximo da pilha de operandos*/
	u2 maxStack;
	/** Quantidade maxima de variaveis locais*/
	u2 maxLocals;
	/**Tamanho do codigo*/
	u4 codeLength;
	/** Codigo */
	u1 *code;
	/** Valor de PC*/
	u4 pc;
};

/** Pilha de Frames*/
struct pilhaFrames {
	/** Frame corrente */
	struct frame *valor;
	/** Frame anterior*/
	struct pilhaFrames *prox;
};


struct frame *frame_corrente;

/**
 * @brief Carrega as informacoes para um novo frame
 * 
 * @param class: classe corrente
 * @param constantPool: pool de constantes
 * @param attribute: atributo que invocou o novo frame
 */
void popularFrame(classStructure *class, cpInfo *constantPool, attributeInfo *attribute);

/**
 * @brief Cria um novo frame
 * 
 * @param class: classe corrente
 * @param constantPool: pool de constantes
 * @param attribute: atributo que invocou o novo frame
 */
void novoFrame(classStructure *class, cpInfo *constantPool, attributeInfo *attribute);

/**
 * @brief Destroi o frame atual e retorna a pilha para o frame anterior
 */
void liberaFrame();

#endif
