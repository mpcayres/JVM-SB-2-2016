/**@file: InicializaClasses.h
 * @brief Arquivo de inicializacao de classes
 * 
 * @details Aqui sao declaradas as funcoes de inicializacao e carregamento do .class
 */

#ifndef INIC_H
#define INIC_H

#include "FuncoesAuxiliares.h"
#include "SalvaInfo.h"
#include "GerenciaMetodos.h"

/**
 * @brief Configura a flag de impressao, atribui o nome do arquivo de saida e do caminho do arquivo de entrada
 * 
 * @param *out: O nome do arquivo de saida
 * @param *path: O caminho para o arquivo de entrada
 * @param flag: Flag de impressao
 * @param flag2: Flag de execucao
 */
void configuraSaida(char *out, char *path, int32_t flag, int32_t flag2);

/**
 * @brief Carrega os parâmetros do .class nos obtejos globais
 * 
 * @param *nomeClass: O nome da classe
 * 
 * @return O Indice da classe
 */
int32_t carregaClass(char *nomeClass);

/**
 * @brief Captura o nome da classe e atribui aos objetos globais
 * 
 * @param *class: Estrutura da classe que contem os parametros
 * 
 * @return O nome da classe de acordo com o seu Indice
 */
char *capturaNomeClass(classStructure *class);

/**
 * @brief Captura o nome da super classe e atribui aos objetos globais
 * 
 * @param *class: Estrutura da classe que contem os parametros
 * 
 * @return O nome da classe de acordo com o seu Indice
 */
char *capturaParentNome(classStructure *class);

/**
 * @brief Captura a classe pelo seu nome
 * 
 * @param *nomeClass: O nome da classe a ser buscada
 * 
 * @return Estrutura da classe com o nome buscado
 */
classStructure* capturaClassPorNome(char *nomeClass);

/**
 * @brief Captura a classe pelo seu Indice
 * 
 * @param Indice: O Indice da classe a ser buscada
 * 
 * @return Estrutura da classe com o Indice buscado
 */
classStructure* capturaClassPorIndice(int32_t Indice);

/**
 * @brief Captura o Indice do descritor
 * 
 * @param *nomeClass: O nome da classe
 * @param *nome: O nome
 * @param nome_tam: O tamanho do nome
 * @param *desc: O descritor
 * @param desc_tam: O tamanho do descritor
 * 
 * @return O indice do descritor buscado
 */
int32_t capturaIndicedoDescritor(char *nomeClass, char *nome, u2 nome_tam, char *desc, u2 desc_tam);

/**
 * @brief Captura o campo estatico pelo indice da classe 
 * 
 * @param classIndice: Indice da classe
 * @param field_Indice: Indice do campo
 * 
 * @return O valor do indice do campo no vetor de classes estatico
 */
u8 capturaCampoEstatico(int32_t classIndice, int32_t field_Indice);

/**
 * @brief Atribui o campo estatico pelo indice da classe 
 * 
 * @param classIndice: Indice da classe
 * @param field_Indice: Indice do campo
 * @param value: O valor a ser atribuido
 */
void atribuiCampoEstatico(int32_t classIndice, int32_t field_Indice, u8 value);

#endif
