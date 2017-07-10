/**  @file: GerenciaPilha.h
 * @brief Arquivo da Pilha
 * 
 * @details Aqui sao declaradas todas estruturas que gerenciam a pilha
 */
#ifndef GPILHA_H
#define GPILHA_H

#include "FuncoesAuxiliares.h"
#define tamanho_maximo_pilha 200

/**
 * @brief Cria uma nova pilha
 */
void novaPilha();

/**
 * @brief Acrecenta um inteiros de tamanho 64 a pilha
 * 
 * @param valoru8: inteiro
 */
void push(u4 value);

/**
 * @brief Acrecenta um inteiro de tamanho 32 a pilha
 * 
 * @param valoru4: inteiro
 */
void pushU8(u8 value);

/**
 * @brief Remove o elemento que esta no topo da pilha
 * 
 * @return topo da pilha
 */
u4 pop();

/**
 * @brief Acrecenta um novo frame ao topo da pilha
 */
void novoFramePilha();

/**
 * @brief Descarta o frame do topo da pilha
 */
void liberaFramePilha();

#endif
