/**  @file: SalvaInfo.h
 * @brief Arquivo do Exibidor
 * 
 * @details Aqui sao declaradas todas funcoes usadas para a salvar as informacoes lidas do .class
 */
#ifndef SALVA_H
#define SALVA_H

#include "FuncoesAuxiliares.h"
#include "CarregaInfo.h"

/**@brief Salva as informacoes do .class. E se necessario monta o arquivo de saida com o nome especificado ou como "Resultado.txt".
*
*@param fileSrc: nome do arquivo .class
*@param fileTrg: nome do arquivo de saida
*@param filePath: caminho do arquivo de entrada
*@param flag_impressao: indica se o arquivo txt de saida deve ser montado
*@return estrutura do .class
*/
classStructure* salvaInfos(char *fileSrc, char *fileTrg, char *filePath, int32_t flag_impressao);

/**@brief salva no arquivo de saida as informacoes gerais o arquivo .class informado
*
*@param fpSaida: ponteiro para o arquivo de saida
*@param accessType: endereco de armazenamento da string correspondente ao tipo de permissao identificada por accessFlags
*/
void salvaGeral(FILE *fpSaida, char *accessType);

/**@brief Funcao que salva no arquivo de saida os valores do pool de constantes
*
*@param fpSaida: arquivo de saida
*/
void salvaConstantPool(FILE *fpSaida);

/**@brief Funcao que salva no arquivo de saida as interfaces
*
* @param fpSaida: arquivo de saida
*/
void salvaInterfaces(FILE *fpSaida);

/**@brief Funcao que salva no arquivo de saida os campos
*
*@param fpSaida: arquivo de saida
*/
void salvaCampos(FILE *fpSaida);

/**@brief Funcao que salva no arquivo de saida os metodos
*
*@param fpSaida: arquivo de saida
*/
void salvaMetodos(FILE *fpSaida);

/**@brief Funcao que salva no arquivo de saida os atributos
*
*@param fpSaida: arquivo de saida
*/
void salvaAtributos(FILE *fpSaida);

/**@brief Funcao que salva no arquivo de saida um unico atributo
* 
*@param fpSaida: arquivo de saida
*@param att: ponteiro para endereco do atributo a armazenar
*@param a: posicao do atributo
*/
void salvaAtributoUnico(FILE * fpSaida, attributeInfo * att, int32_t a);

/**@brief Funcao que salva no arquivo de saida os mnemonicos
*
*@param bytecode: endereco da operacao
*@param tam: tamanho da operacao
*@param fpSaida: arquivo de saida
*/
void imprimirMnemonics(u1 *bytecode, u2 tam, FILE *fpSaida);

/**@brief Funcao que determina o tipo de permissao identificada por accessFlags
*@param intValue: valor inteiro de accessFlags
*@param target: string onde sao amazenados os tipos de acesso correspondentes
*/
void getPermissaoDeAcesso(int32_t intValue, char * target);

/**@brief Funcao que pega um nome no constantPoll
*
*@param class_file: a estrutura da classe (classStructure)
*@param nameIndex: o endereco no constantPool
*@return string com o nome resgatado
*/
char* getNome(classStructure *class_file, u2 nameIndex);

#endif

