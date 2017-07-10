/**@file: InstrucoesGerais.h
 * @brief Arquivo de instrucoes gerais
 * 
 * @details Aqui sao implementadas as instrucoes gerais da JVM 
 */

#ifndef INSTRGER_H
#define INSTRGER_H

#include "FuncoesAuxiliares.h"
#include "InicializaClasses.h"
#include "InstrucoesCat1.h"
#include "InstrucoesCat2.h"
#include "GerenciaHeap.h"
#include "GerenciaMetodos.h"
#include "GerenciaPilha.h"

/** No operation*/
void jvm_nop();

/**@brief Categoria 2 \n
 * Pop + incremento do pc*/
void jvm_pop();

/**@brief Categoria 2 \n
 * Pop 2 vezes + incremento do pc*/
void jvm_pop2();

/**@brief Categoria 2 \n
 * Faz uma copia do topo da pilha + incremento do pc*/
void jvm_dup();

/**@brief Categoria 2 \n
 * Faz uma copia do topo da pilha intercalando 1 valor de pop + incremento do pc*/
void jvm_dup_x1();

/**@brief Categoria 2 \n
 * Faz uma copia do topo da pilha intercalando 2 valores de pop + incremento do pc*/
void jvm_dup_x2();

/**@brief Categoria 2 \n
 * Faz uma copia do topo da pilha de 2 words + incremento do pc*/
void jvm_dup2();

/**@brief Categoria 2 \n
 * Faz uma copia do topo da pilha de 2 words intercalando 1 valor + incremento do pc*/
void jvm_dup2_x1();

/**@brief Categoria 2 \n
 * Faz uma copia do topo da pilha de 2 words intercalando 2 valores + incremento do pc*/
void jvm_dup2_x2();

 /**@brief Categoria 2 \n
 * Troca os dois ultimos valores da pilha + incremento do pc*/
void jvm_swap();

/** @brief Recupera o valor de um inteiro das variaveis locais e o empilha. O indice eh recuperado da pilha
*/
void jvm_iload();

/** @brief Recupera o valor de um float das variaveis locais e o empilha. O indice eh recuperado da pilha
*/
void jvm_fload();

/** @brief Recupera o valor de um inteiro long de um array de longs e o empilha. O indice e a referencia para o array
*sao recuperados da pilha
*/
void jvm_laload();

/** @brief Recupera o valor de um double de um array de doubles e o empilha. O indice e a referencia para o array
*sao recuperados da pilha
*/
void jvm_daload();

/** @brief Recupera o valor de uma referencia a objeto das variaveis locais e empilha. O indice eh recuperado da pilha
*/
void jvm_aload();


/** @brief Funcao que faz o return com tipo inteiro de um metodo */
void jvm_ireturn();

/** @brief Funcao que faz o return com tipo float de um metodo */
void jvm_freturn();

/** @brief Funcao que faz o return com tipo long de um metodo */
void jvm_lreturn();

/** @brief Funcao que faz o return com tipo double de um metodo */
void jvm_dreturn();

/** @brief Funcao que faz o return com uma referencia para objeto de um metodo */
void jvm_areturn();

/** @brief Funcao que faz o return de um metodo. Para metodos com retorno do tipo void */
void jvm_return();

/** @brief Jump se zero. Se o topo da pilha for zero, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_ifeq();

/** @brief Jump se não zero. Se o topo da pilha não for zero, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_ifne();

/** @brief Jump se menor que zero. Se o topo da pilha for negativo, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_iflt();

/** @brief Jump se maior ou igual zero. Se o topo da pilha for maior ou igual a zero, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_ifge();

/** @brief Jump se maior zero. Se o topo da pilha for inteiro diferente de zero, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_ifgt();

/** @brief Jump se menor ou igual zero. Se o topo da pilha for negativo ou igaul a zero, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_ifle();

/** @brief Jump dois inteiro forem iguais. Compara os dois numeros no topo da pilha  e se os dois forem iguais, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_icmpeq();

/** @brief Jump dois inteiro não forem iguais. Compara os dois numeros no topo da pilha  e se os dois não forem iguais, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_icmpne();

/** @brief Jump se menor que. Compara os dois numeros no topo da pilha  e se o segundo valor for menor que o primeiro, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_icmplt();

/** @brief Jump se maior ou igual. Compara os dois numeros no topo da pilha  e se o segundo valor for maior ou igual ao primeiro, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_icmpge();

/** @brief Jump se maior que. Compara os dois numeros no topo da pilha  e se o segundo valor for maior que o primeiro, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_icmpgt();

/** @brief Jump se menor ou igual. Compara os dois numeros no topo da pilha  e se o segundo valor for menor ou igual ao primeiro, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_icmple();

/** @brief Jump se objetos iguais. Compara duas referencias a objeto do topo da pilha  e se os valores forem iguais, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_acmpeq();

/** @brief Jump se objetos não iguais. Compara duas referencias a objeto do topo da pilha  e não forem iguais, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_if_acmpne();

/** @brief Jump para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_goto();

/** @brief Jump para subrotina. Usando o endereco (pc + offset). Offset eh recuperado do codigo (frame->code). Empilha o pc + 3. 
 */
void jvm_jsr();

/** @brief Retorno de uma subrotina. O endereco de retorno eh recuperado das variaveis locais com o indice sendo recuperado do codigo (fram->code) 
 */
void jvm_ret();

/** @brief Jump computado com base numa jump table. 
 */
void jvm_tableswitch();

/** @brief Jump com comparacao. Usando uma lookupswitch table. Se o int recuperado da pilha for igual a alguma dos campos <key> das entradas, pula para endereco na <label> correspondente.
* Se não achar correspondente pula para <labelDefault>
 */
void jvm_lookupswitch();

/** @brief Pega o valor de um static field. Recupera uma referencia para objeto da pilha e recupera o valor do campo
* classe (<field-spec>). O resultado eh empilhado
 */
void jvm_getstatic();

/** @brief Salva um valor em um static field. O valor eh recuperado da pilha
 */
void jvm_putstatic();

/** @brief Pega o valor de um object field. Pega a referencia para o objeto da pilha. O resultado eh empilhado
 */
void jvm_getfield();

/** @brief Salva o valor de um object field. O valor eh recuperado da pilha.
 */
void jvm_putfield();


/**@brief Invoca um metodo Java. Usado para quase todos tipos de metodos menos interfaces, metodos estaticos e alguns casos especiais.
*/
void jvm_invokevirtual();

/**@brief Invoca metodos especiais como o metodo <init>, um metodo privado e um metodo da superclasse
*/
void jvm_invokespecial();
/**@brief Invoca um metodo estatico (um metodo classe)
*/
void jvm_invokestatic();
/**@brief Invoca um metodo de interface.
*/
void jvm_invokeinterface();

/**@brief Invoca um metodo dinamico.
*/
void jvm_invokedynamic();

/**@brief Cria um objeto. Tem como parametro (no codigo) a classe do novo objeto. Os campos sao inicalizados com 0 ou com null.
*Uma referencia para o objeto eh acrescentada ao topo da pilha 
*/
void jvm_new();

/**@brief Aloca uma array (booleanos,chars,floats,doubles,bytes,shorts,ints e longs). O numero de elementos do array eh recuperado da pilha.
*Uma referencia para a array eh acrescentada a pilha.
*/
void jvm_newarray();

/**@brief Aloca uma array de objetos. O numero de elementos do array eh recuperado da pilha .
*Uma referencia para a array eh acrescentada a pilha.
*/
void jvm_anewarray();

/**@brief Retorna o tamanho de uma array para o topo da pilha. Se for uma array multidimencional so a primeira dimensao eh retornada.
*Remove a referencia a array do topo da pilha.
*/
void jvm_arraylength();

/** @brief Indica excecao ou erro
 */
void jvm_athrow();

/**@brief Testa o tipo. Se houver diferenca indica uma excecao ou erro de tipo
*/
void jvm_checkcast();

/**@brief Testa classe. Se houver diferenca indica uma excecao ou erro de classe
*/
void jvm_instanceof();

/**@brief Usado para controlar acesso a um objeto dentro de varias threads.
*/
void jvm_monitorenter();

/**@brief Usado para liberar o acesso a um objeto.
*/
void jvm_monitorexit();

/**@brief Usado para indicar que a proxima instrucao que acessa uma variavel local
*/
void jvm_wide();

/**@brief Aloca uma array multidimensional. O numero de elementos das dimensoes do array sao recuperados da pilha.
*Uma referencia para a array eh acrescentada a pilha.
*/
void jvm_multianewarray();

/** @brief Jump se null. Se o topo da pilha for null, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
void jvm_ifnull();

/** @brief Jump se não null. Se o topo da pilha não for null, pula para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code)
 */
 void jvm_ifnonnull();

/** @brief Jump para o endereco (pc + offset). Offset eh recuperado do codigo (frame->code) e tem tamanho 32-bits
 */
void jvm_goto_w();

/** @brief Jump para subrotina. Usando o endereco (pc + offset). Offset eh recuperado do codigo (frame->code) e tem tamnho 32-bits. Empilha o pc + 5. 
 */
void jvm_jsr_w();

/** Usado para identificar as instrucoes */
void (*vetorInstruc[256]) ();

/** @brief Executa uma instrucao
*
*@param opcode: opcode da instrucao a ser executada
*@return void
 */
void executarInstrucoes(u1 opcode);

/**@brief Inicializa o vetorInstruc com as instrucoes
*/
void iniciarInstrucoes();

#endif
