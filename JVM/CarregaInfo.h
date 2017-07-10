/**  @file: CarregaInfo.h
 * @brief Arquivo do Leitor
 * 
 * @details Aqui sao declaradas todas funcoes usadas para a carregar as informacoes do .class
 */
#ifndef CARREGA_H
#define CARREGA_H

#include <stdio.h>

#include "FuncoesAuxiliares.h"

#define TRUE 1
#define FALSE 0

/** @brief CONSTANT POOL*/
#define CPOOL_CONTINUED          0
/** @brief CONSTANT POOL*/
#define CPOOL_UTF8               1
/** @brief CONSTANT POOL*/
#define CPOOL_INTEGER            3
/** @brief CONSTANT POOL*/
#define CPOOL_FLOAT              4
/** @brief CONSTANT POOL*/
#define CPOOL_LONG               5
/** @brief CONSTANT POOL*/
#define CPOOL_DOUBLE             6
/** @brief CONSTANT POOL*/
#define CPOOL_CLASS              7
/** @brief CONSTANT POOL*/
#define CPOOL_STRING             8
/** @brief CONSTANT POOL*/
#define CPOOL_FIELD				 9
/** @brief CONSTANT POOL*/
#define CPOOL_METHOD          	 10
/** @brief CONSTANT POOL*/
#define CPOOL_INTERFACE 		 11
/** @brief CONSTANT POOL*/
#define CPOOL_NAMETYPE           12

classStructure *cs;

/**
 * @brief le um byte do arquivo. Utilizada para captura os opcodes
 * 
 * @param fpClassClass: arquivo de entrada
 * 
 * @return byte lido do arquivo de entrada
 */
u1 u1Leitura(FILE *fpClassClass);

/**
 * @brief le dois bytes do arquivo
 * 
 * @param fpClassClass: arquivo de entrada
 * 
 * @return os valores lidos
 */
u2 u2Leitura(FILE *fpClassClass);

/**
 * @brief le 4 bytes do arquivo
 * 
 * @param fpClassClass: arquivo de entrada
 * 
 * @return os valores lidos
 */
u4 u4Leitura(FILE *fpClassClass);

/**
 * @brief Verifica o numero magic do arquivo
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 * @return 1 se CAFEBABE e 0 se nao
 */
int32_t verificaNumMagic(FILE *fpClass);

/**
 * @brief Verifica o versao da classe
 * 
 * @param cs: estrutura dos dados da classe java
 * 
 * @return 1 se CAFEBABE e 0 se nao
 */
int32_t verificaVersao();

/**
 * @brief armazena os valores das versoes (ninor e major)
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 */
void armazenaVersoes(FILE *fpClassClass);

/**
 * @brief armazena os valores do pool de constantes 
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 */
void armazenaConstantPool(FILE *fpClassClass);

/**
 * @brief armazena o valor das flags de acesso
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 */
void armazenaAccessFlags(FILE *fpClassClass);

/**
 * @brief armazena os valores de This class e Super class
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 */
void armazenaClasses(FILE *fpClassClass);

/**
 * @brief armazena as interfaces
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 */
void armazenaInterfaces(FILE *fpClassClass);

/**
 * @brief armazena os campos
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 */
void armazenaCampos(FILE *fpClassClass);

/**
 * @brief armazena os metodos
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 */
void armazenaMetodos(FILE *fpClassClass);

/**
 * @brief armazena os atributos
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * 
 */
void armazenaAtributos(FILE *fpClassClass);

/**
 * @brief armazena um unico atributo
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * @param att: ponteiro para armazenar o atributo
 * 
 */
void armazenaAtributoUnico(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo do tipo constante
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrConst(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo do tipo Code
 * 
 * @param fpClass: arquivo de entrada
 * @param cs: estrutura dos dados da classe java
 * @param att: ponteiro para armazenar o atributo
 * 
 */
void armazenaAtrCode(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo do tipo Exceptions
 * 
 * @param fpClass: arquivo de entrada
 * @param att: ponteiro para armazenar o atributo
 * 
 */
void armazenaAtrExc(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo InnerClasses
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrInnerClass(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo Synthetic
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrSynthetic(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo padrao
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrDefault(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo depreciado
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrDeprec(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo numero de linha
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrLineNumTable(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo de variavel local
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrLocalVarTable(FILE *fpClass, attributeInfo * );

/**
 * @brief armazena um atributo de arquivo de origem
 * 
 * @param fpClass: arquivo de entrada
 * @param att: estrutura dos dados da classe java
 * 
 */
void armazenaAtrSourceFile(FILE *fpClass, attributeInfo * );

#endif

