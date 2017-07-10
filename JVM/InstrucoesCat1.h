/**@file: InstrucoesCat1.h
 * @brief Arquivo de instrucoes cat 1
 * 
 * @details Aqui sao declaradas as funcoes que dizem respeito as instrucoes de categoria 1 (float e int)
 */

#ifndef INSTRCAT1_H
#define INSTRCAT1_H

#include "FuncoesAuxiliares.h"
#include "InstrucoesGerais.h"
#include "GerenciaPilha.h"

#define NULL_CONST 0


/**@brief empilha um null
*@return null
*/
void jvm_aconst_null();

/**@brief push de um inteiro igual a -1 
*@return null 
*/
void jvm_iconst_m1();

/**@brief push de um inteiro igual a 0
*@return null 
*/
void jvm_iconst_0();

/**@brief push de um inteiro igual a 1
*@return null 
*/
void jvm_iconst_1();

/**@brief push de um inteiro igual a 2 
*@return null 
*/
void jvm_iconst_2();

/**@brief push de um inteiro igual a 3 
*@return null 
*/
void jvm_iconst_3();

/**@brief push de um inteiro igual a 4 
*@return null 
*/
void jvm_iconst_4();

/**@brief push de um inteiro igual a 5
*@return null 
*/
void jvm_iconst_5();

/**@brief push de um float igual a 0.0
*@return null 
*/
void jvm_fconst_0();

/**@brief push de um float igual a 1.0
*@return null 
*/
void jvm_fconst_1();

/**@brief push de um float igual a 2.0
*@return null 
*/
void jvm_fconst_2();

/** @brief Pega um parametro (frame->code) inteiro de 8-bits e empilha na pilha de operandos
*@return void
*/
void jvm_bipush();

/** @brief Pega um parametro (frame->code) inteiro de 16-bits e empilha na pilha de operandos
*@return void
*/
void jvm_sipush();


/** @brief Recupera um inteiro da posicao 0 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_iload_0();

/** @brief Recupera um inteiro da posicao 1 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_iload_1();

/** @brief Recupera um inteiro da posicao 2 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_iload_2();

/** @brief Recupera um inteiro da posicao 3 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_iload_3();


/** @brief Recupera um float da posicao 0 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_fload_0();

/** @brief Recupera um float da posicao 1 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_fload_1();

/** @brief Recupera um float da posicao 2 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_fload_2();

/** @brief Recupera um float da posicao 3 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_fload_3();


/** @brief Recupera uma referencia a objeto da posicao 0 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_aload_0();

/** @brief Recupera uma referencia a objeto da posicao 1 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_aload_1();

/** @brief Recupera uma referencia a objeto da posicao 2 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_aload_2();

/** @brief Recupera uma referencia a objeto da posicao 3 das variaveis locais (frame->fields) e empilha
*@return void
*/
void jvm_aload_3();


/** @brief Recupera um componete de uma array de inteiros removendo da pilha a referencia para um array de inteiros
* e o index do componete. Empilha o resultado
*@return void
*/
void jvm_iaload();

/** @brief Recupera um componete de uma array de float removendo da pilha a referencia para um array de float
* e o index do componete. Empilha o resultado
*@return void
*/
void jvm_faload();

/** @brief Recupera um componete de uma array de objetos removendo da pilha a referencia para um array de objetos
* e o index do componete. Empilha o resultado
*@return void
*/
void jvm_aaload();

/** @brief Recupera um componete de uma array de bytes ou booleanos removendo da pilha a referencia para a array
* e o index do componete. Empilha o resultado
*@return void
*/
void jvm_baload();

/** @brief Recupera um caracter de uma array de chars removendo da pilha a referencia para um array de chars
* e o index do componete. Empilha o resultado
*@return void
*/
void jvm_caload();

/** @brief Recupera um componete de uma array de shorts removendo da pilha a referencia para um array de shorts
* e o index do componete. Empilha o resultado
*@return void
*/
void jvm_saload();


/** @brief Recupera um int32_t da pilha e salva em uma variavel local (frame->fields) com indice no code
*@return void
*/
void jvm_istore();

/** @brief Recupera um float da pilha e salva em uma variavel local (frame->fields) com indice no code
*@return void
*/
void jvm_fstore();

/** @brief Recupera uma referencia para um objeto ou array e salva em uma variavel local (frame->fields) com indice no code
*@return void
*/
void jvm_astore();


/** @brief Recupera um int32_t da pilha e salva na posicao 0 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_istore_0();

/** @brief Recupera um int32_t da pilha e salva na posicao 1 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_istore_1();

/** @brief Recupera um int32_t da pilha e salva na posicao 2 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_istore_2();

/** @brief Recupera um int32_t da pilha e salva na posicao 3 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_istore_3();


/** @brief Recupera um float da pilha e salva na posicao 0 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_fstore_0();

/** @brief Recupera um float da pilha e salva na posicao 1 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_fstore_1();

/** @brief Recupera um float da pilha e salva na posicao 2 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_fstore_2();

/** @brief Recupera um float da pilha e salva na posicao 3 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_fstore_3();

/** @brief Recupera uma referencia para objeto ou array da pilha e salva na posicao 0 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_astore_0();

/** @brief Recupera uma referencia para objeto ou array da pilha e salva na posicao 1 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_astore_1();

/** @brief Recupera uma referencia para objeto ou array da pilha e salva na posicao 2 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_astore_2();

/** @brief Recupera uma referencia para objeto ou array da pilha e salva na posicao 3 das variaveis locais (frame->fields) 
*@return void
*/
void jvm_astore_3();

/** @brief Recupera um int32_t da pilha e salva em um array de inteiros. A referencia para o array e o indice tambem sao retirados
* da pilha.  
*@return void
*/
void jvm_iastore();

/** @brief Recupera um float da pilha e salva em um array de floats. A referencia para o array e o indice tambem sao retirados
* da pilha.  
*@return void
*/
void jvm_fastore();

/** @brief Recupera uma referencia para objeto e salva em um array de objetos. A referencia para o array e o indice tambem sao retirados
* da pilha.  
*@return void
*/
void jvm_aastore();

/** @brief Recupera um byte ou booleano da pilha e salva em um array de bytes ou booleanos. A referencia para o array e o indice tambem sao retirados
* da pilha.  
*@return void
*/
void jvm_bastore();

/** @brief Recupera um caractere da pilha e salva em um array de chars. A referencia para o array e o indice tambem sao retirados
* da pilha.  
*@return void
*/
void jvm_castore();

/** @brief Recupera um int32_t da pilha e salva em um array de shorts. A referencia para o array e o indice tambem sao retirados
* da pilha.  
*@return void
*/
void jvm_sastore();


/* São as instruções aritméticas que operam a partir da Stack e podem apresentar overflow. */

/** @brief Recupera dos inteiros da pilha e os soma. O resultado e devolvido a pilha
*@return void
*/
void jvm_iadd();

/** @brief Recupera dos floats da pilha e os soma. O resultado e devolvido a pilha
*@return void
*/
void jvm_fadd();

/** @brief Recupera dos inteiros da pilha e subtrai o do topo do segundo. O resultado e devolvido a pilha
*@return void
*/
void jvm_isub();

/** @brief Recupera dos floats da pilha e subtrai o do topo do segundo. O resultado e devolvido a pilha
*@return void
*/
void jvm_fsub();

/** @brief Recupera dos inteiros da pilha e os multiplica. O resultado e devolvido a pilha
*@return void
*/
void jvm_imul();

/** @brief Recupera dos floats da pilha e os multiplica. O resultado e devolvido a pilha
*@return void
*/
void jvm_fmul();

/** @brief Recupera dos inteiros da pilha e divide o valor do topo pelo segundo valor. O resultado e devolvido a pilha
*@return void
*/
void jvm_idiv();

/** @brief Recupera dos floats da pilha e divide o valor do topo pelo segundo valor. O resultado e devolvido a pilha
*@return void
*/
void jvm_fdiv();


/** @brief Recupera dois inteiros da pilha e divide o valor do topo pelo segundo valor. O resto da divisão eh devolvido a pilha
*@return void
*/
void jvm_irem();

/** @brief Recupera dois floats da pilha e divide o valor do topo pelo segundo valor. O resto da divisão eh devolvido a pilha
*@return void
*/
void jvm_frem();


/** @brief Recupera um inteiro da pilha e devolve seu negativo
*@return void
*/
void jvm_ineg();

/** @brief Recupera um float da pilha e devolve seu negativo
*@return void
*/
void jvm_fneg();

/** @brief Recupera dois inteiro da pilha e shifta o segundo valor para direita o numero de vezes ditado pelo outro valor. O resultado eh devovido para pilha
*@return void
*/
void jvm_ishl();

/** @brief Recupera dois inteiro da pilha e shifta o segundo valor para esquerda o numero de vezes ditado pelo outro valor. O resultado eh devovido para pilha
*@return void
*/
void jvm_ishr();

/** @brief Recupera dois inteiro da pilha e shifta o segundo valor para direita (shift logico) o numero de vezes ditado pelo outro valor. O resultado eh devovido para pilha
*@return void
*/
void jvm_iushr();

/** @brief Recupera dois inteiro da pilha e faz um and bit a bit do primeiro valor com o segundo. O resultado eh devovido para pilha
*@return void
*/
void jvm_iand();

/** @brief Recupera dois inteiro da pilha e faz um or bit a bit do primeiro valor com o segundo. O resultado eh devovido para pilha
*@return void
*/
void jvm_ior();

/** @brief Recupera dois inteiro da pilha e faz um xor bit a bit do primeiro valor com o segundo. O resultado eh devovido para pilha
*@return void
*/
void jvm_ixor();

/** @brief Incrementa um componente inteiro das variaveis locais. O indice e o valor que indica quanto o componente deve ser incrementado ou decrementado sao retirados da pilha.
* O resultado tambem eh gradado na pilha.
*@return void
*/
void jvm_iinc();

/** @brief Recupera um inteiro da pilha e o converte em long. O resultado eh devovido a pilha
*@return void
*/
void jvm_i2l();

/** @brief Recupera um inteiro da pilha e o converte em float. O resultado eh devovido a pilha
*@return void
*/
void jvm_i2f();

/** @brief Recupera um inteiro da pilha e o converte em double. O resultado eh devovido a pilha
*@return void
*/
void jvm_i2d();

/** @brief Recupera um float da pilha e o converte em int32_t. O resultado eh devovido a pilha
*@return void
*/
void jvm_f2i();

/** @brief Recupera um float da pilha e o converte em long. O resultado eh devovido a pilha
*@return void
*/
void jvm_f2l();

/** @brief Recupera um float da pilha e o converte em double. O resultado eh devovido a pilha
*@return void
*/
void jvm_f2d();

/** @brief Recupera um inteiro da pilha e o converte em byte. O resultado eh devovido a pilha
*@return void
*/
void jvm_i2b();

/** @brief Recupera um inteiro da pilha e o converte em unsigned char. O resultado eh devovido a pilha
*@return void
*/
void jvm_i2c();

/** @brief Recupera um inteiro da pilha e o converte em int32_t. O resultado eh devovido a pilha
*@return void
*/
void jvm_i2s();

/** @brief Compara dois floats retirados da pilha. Se os dois numeros forem iguais o int32_t 0 eh acrescetado a pilha.
*Se o primeiro valor for maior que o segundo o int32_t 1 eh acrecentado a pilha. Se o segundo valor for maior que o primeiro
*o int32_t -1 eh acrestado na pilha. Se alguns dos numeros for NaN o int32_t -1 eh acrescentado a pilha.
*@return void
*/
void jvm_fcmpl();

/** @brief Compara dois floats retirados da pilha. Se os dois numeros forem iguais o int32_t 0 eh acrescetado a pilha.
*Se o primeiro valor for maior que o segundo o int32_t 1 eh acrecentado a pilha. Se o segundo valor for maior que o primeiro
*o int32_t -1 eh acrestado na pilha
*@return void
*/
void jvm_fcmpg();

#endif
