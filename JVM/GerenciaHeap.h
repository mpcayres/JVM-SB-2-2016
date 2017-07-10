/**  @file: GerenciaHeap.h
 * @brief Arquivo da Heap
 * 
 * @details Aqui sao declaradas todas estruturas que gerenciam a heap
 */

#ifndef HEAP_H
#define HEAP_H

#include "InicializaClasses.h"
#include "FuncoesAuxiliares.h"

/** Tamanho padrao da heap*/
#define HEAP_INIT 32

/** Estrutura da classe de objeto*/
struct Object {
	/** Estrutura autorreferenciativa*/
	classStructure *this;
	/** Estrutura da classe mae*/
	struct Object *super;
	/** Campos*/
	u4 *fields;
	/** Indices de campos*/
	u4 *fields_index;
};

/** Estrutura do array*/
struct array{
	/** Referencia*/
	u4 ref;
	/** Tamanho*/
	u4 size;
};

/** Referencia para um objeto*/
struct Object **heap;

/** Vetor com o tamanho dos arrays*/
struct array *tamArray;

/** Numero de arrays alocados*/
u4 numArrays;

/**
 * @brief Aloca memoria para uma nova heap
 */
void novaHeap();

/**
 * @brief Instancia um novo objeto
 * 
 * @param *cs_this: autorreferencia da classe
 * 
 * @return Um novo objeto com os campos alocados
 */
struct Object* novoObject(classStructure *cs_this);

/**
 * @brief Busca qual objeto de tamanho 32 que tem o campo igual ao Indice nome
 * 
 * @param *object: Ponteiro do objeto
 * @param nameIndex: Indice nome
 * 
 * @return O campo do objeto equivalente ao Indice nome
 */
u4 capturaCampoObjeto(struct Object* object, u4 nameIndex);

/**
 * @brief Busca qual objeto de tamanho 64 que tem o campo igual ao Indice nome
 * 
 * @param *object: Ponteiro do objeto
 * @param nameIndex: Indice nome
 * 
 * @return O campo do objeto equivalente ao Indice nome
 */
u8 capturaCampoObjetoLargo(struct Object* object, u4 nameIndex);

/**
 * @brief Atribui os campos ao objeto de tamanho 32 com indice igual ao do Indice nome
 * 
 * @param *object: Ponteiro do objeto
 * @param nameIndex: Indice nome
 * @param value: Valor a ser atribuido
 */
void atribuiCampoObjeto(struct Object* object, u4 nameIndex, u4 value);

/**
 * @brief Atribui os campos ao objeto de tamanho 64 com indice igual ao do Indice nome
 * 
 * @param *object: Ponteiro do objeto
 * @param nameIndex: Indice nome
 * @param value: Valor a ser atribuido
 */
void atribuiCampoObjetoLargo(struct Object* object, u4 nameIndex, u8 value);

/**
 * @brief Instancia um novo array de acordo com o tamanho do tipo de dado
 * 
 * @param cont: Tamanho do array
 * @param type: Tipo de dado do array

 * @return Um ponteiro da estrutura array inicializado
 */
void* novoArray(u4 cont, u1 type);

#endif
