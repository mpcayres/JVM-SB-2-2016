/**  @file: GerenciaMetodos.h
 * @brief Arquivo de Metodos
 * 
 * @details Aqui sao declaradas todas funcoes usadas para a gerencia de metodos
 */

#ifndef MET_H
#define MET_H

#include "FuncoesAuxiliares.h"
#include "SalvaInfo.h"
#include "InstrucoesGerais.h"
#include "GerenciaFrames.h"
#include "GerenciaPilha.h"

/** Variavel usada para saber qual o tipo de retorno da funcao */
u1 returnType;
/** Variavel usada para saber qual o retorno da funcao*/
u8 returnValue;

/**@brief Recupera a metodo main
*
*@return metodo recuperado
*/
methodInfo* recuperaMetodoMain();

/**@brief recupera um metodo estatioco 
*
*@param main_class: classe de onde o metodo deve ser recuperado
*@return as informacoes do metodo recuperado ou null caso nao seja encontrado metodo 
*/
methodInfo* recuperaMetodoEstaticoInit();

/**@brief recupera um metodo pelo seu nome
*
*@param main_class: a classe main
*@param name_type_class: a classe de onde o nome do metodo deve ser recuperado
*@param name_type_index: o indice dentro do constant pool da name_type_class
*@return as informacoes do metodo recuperado ou null caso o metodo pedido nao seja encontrado
*/
methodInfo* recuperaMetodoPorNome_IndiceDesc(classStructure *main_class, classStructure *name_type_class, u2 name_type_index);

/**@brief recupera o numero de parametros de um metodo
*
*@param class: classe corrente
*@param method: metodo 
*@return o numero de parametros recuperado
*/
int32_t recuperaNumeroParametros(methodInfo *method, classStructure *class);

/**@brief executa um metodo. Todas as instrucoes do frame corrente. 
*@return null
*/
void executarMetodo();

/**@brief prepara um metodo construindo um novo frame
*
*@param class: classe do metodo 
*@param method: metodo
*/
void prepararMetodo(methodInfo *method, classStructure *class);

#endif
