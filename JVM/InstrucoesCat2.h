/**@file: InstrucoesCat2.h
 * @brief Arquivo de instrucoes cat 2
 * 
 * @details Aqui sao declaradas as funcoes que dizem respeito as instrucoes de categoria 2 (long e double)
 */

#ifndef INSTRCAT2_H
#define INSTRCAT2_H

#include "FuncoesAuxiliares.h"
#include "InstrucoesGerais.h"
#include "GerenciaPilha.h"

/** @brief Empilha a constante 0 por meio da funcao push e incrementa o valor do membro pc apontado 
 * pelo ponteiro de struct frame_corrente. A constante e tratada como uma long.
 *@return void
 */
void jvm_lconst_0();

/** @brief Empilha a constante 1 por meio da funcao push e incrementa o valor do membro pc apontado 
 * pelo ponteiro de struct frame_corrente. No entanto ele empilha tambem o zero.
 *@return void
 */
void jvm_lconst_1();

/** @brief Realiza o push da constante zero como double. Para isto utiliza-se de uma variavel temporaria  
 * para alocar memoria com um malloc. Em seguida shifta em 32 bits para completar o double. Obtendo o 
 * tamanho adequado da memoria a ser alocada por meio de um sizeof do tipo u4 e u8. 
 *@return void
 */
void jvm_dconst_0();

/** @brief Realiza o push da constante 1 como double. Para isto utiliza-se de uma variavel temporaria  
 * para alocar memoria com um malloc. Em seguida shifta em 32 bits para completar o double. Obtendo o 
 * tamanho adequado da memoria a ser alocada por meio de um sizeof do tipo u4 e u8. 
 *@return void
 */
void jvm_dconst_1();

/** @brief Efetua-se um switch para decidir entre os casos inteiro, float e string pois em cada   
 *  caso sera colocado em um membro diferente da struct. Atualiza-se assim os campos da constant_pool.
 *@return void
 */
void jvm_ldc();

/** @brief Utiliza-se da funcao shift para converter 8 bits em 32 bits para completar uma word.  
 *  E empilha o valor adequado dentre string, float e inteiro. O indice da constant_pool e
 *  dado pela aplicacomposicaoao da funcao shift8To32.
 *@return void
 */
void jvm_ldc_w();

/** @brief Empilha valores long ou double. O indice e obtido por meio da conversao de um valor de valor 
 *  de 8 bits para 32 bits. Assim o switch tem apenas duas opcomposicaooes para armazenar o valor no local correto
 *  da constant_pool.
 *@return void
 */
void jvm_ldc2_w();

/** @brief Realiza o push de do field 0 e field 1 no ponteiro frame_corrente e incrementa. 
 *@return void
 */
void jvm_lload_0();

/** @brief  Empilha o field 1 e o field 2 na stack e incrementa o frame_corrente->pc.
 *@return void
 */
void jvm_lload_1();

/** @brief Efetua o push do ponteiro frame_corrente->field[2] e do field[3].  
 * E ao final incrementa o pc do frame_corrente.
 *@return void
 */
void jvm_lload_2();

/** @brief Empilha os fields 3 e 4 depois incrementa pc. 
 * O codigo hexadecimal das instrucoes lload sao 42(0), 43(1), 44(2) e 45(3).
 *@return void
 */
void jvm_lload_3();

/** @brief A Implementacao das Instrucoes load seguem um padrao em sua composicao e estruturacao logica.
 * O que as diferencia e o  valor incial da constante a ser empilhado.
 * @return void
 */
void jvm_dload_0();

/** @brief Empilha-se os fields 1 e 2 do frame_corrente e incrementa pc. 
 * O prefixo neste caso e double.     
 *@return void
 */
void jvm_dload_1();

/** @brief Empilha-se os membros 2 e 3 do ponteiro para struct frame_corrente.  
 *@return void
 */
void jvm_dload_2();

/** @brief Esta funcao empilha os indices 3 e 4 do fields que compoem o frame_corrente.   
 *@return void
 */
void jvm_dload_3();

/** @brief Implementacao das Instrucoes store.
 * Cria-se duas variaveis do tipo u2 e u4.
 * Incrementa-se o campo pc, desempilha-se dois valores e guarda-os nos fields.
 * @return void
 */
void jvm_lstore();

/** @brief Esta funcao e construida da seguinte forma: declara-se variaveis last e first para
 * receber os valores desempilhados. Apos a declaracomposicaoao incrementa-se frame_corrente->pc e desempilha.
 * Por fim os dos fields recebem first e last.
 *@return void
 */
void jvm_dstore();

/** @brief First e last recebem os valores desempilhados e frame_corrente->fields[0] e [1]
 * recebem last e first respectivamente.   
 *@return void
 */
void jvm_lstore_0();

/** @brief De maneira analoga segue os passos descritos para as funcomposicaooes store com a diferencomposicaoas que
 * os fields[1] recebe last e fields[2] recebe first.   
 *@return void
 */
void jvm_lstore_1();

/** @brief Ocorre o desempilhamento. Fields 2 e 3 recebem last e first respectivamente. Incrementa-se pc.   
 *@return void
 */
void jvm_lstore_2();

/** @brief first recebe pop(), last recebe pop() e frame_corrente->fields[3] = last e frame_corrente->fields[4]    
 * recebe first. 
 *@return void
 */
void jvm_lstore_3();

/** @brief Declara-se variaveis last e first do tipo u4. De maneira analoga as Instrucoes store, ocorre uma     
 *  atribuicomposicaoao dos valores desempilhados e carrega-se o frame_corrente com esses valores.
 *@return void
 */
void jvm_dstore_0();

/** @brief As constantes a direita indicam um valor e seu sucessor que indexaram os membros fields do    
 *  ponteiro frame_corrente. Segue-se os passos declara, desempilha, carrega last e first no frame e incrementa-se.
 *@return void
 */
void jvm_dstore_1();

/** @brief Armazena um double em uma variavel local de maneira geral este e o efeito de funcomposicaooes do tipo dstore. 
 *@return void
 */
void jvm_dstore_2();

/** @brief Declara-se last e first com tipo u4 para 4 bytes. Desempilha um valor e atribui a first.    
 * Desempilha-se outro valor e atribui a last. O ponteiro de field[3] recebe first e o ponteiro
 * de field[4] recebe last. Incrementa pc. 
 *@return void
 */
void jvm_dstore_3();

/** @brief Declara-se o indice alem do first e do last. E tambem e criada uma nova variavel do tipo u8. E
 * tambem declara-se um ponteiro void de referancia. Desempilha e atribui a first, depois desempilha
 * e atribui a last. A diferencomposicaoa neste caso e a conversao de um valor de 32 bits para um de 64 bits. Realizada
 * pela funcao shift32to64.      
 *@return void
 */
void jvm_lastore();

/** @brief Fisrt recebe o valor do topo da pilha depois last tambem recebe da pilha. Realiza-se a conversao
 * por meio da funcao shift32to64 e incrementa-se pc++ ao final.
 *@return void
 */
void jvm_dastore();

/** @brief As Instrucoes aritmeticas sempre recorrem a uma pilha. Desta forma para somar empilha-se os 
 * operandos efetua-se  a operacomposicaoao e desempilha o resultado. 
 *@return void
 */
void jvm_ladd();

/** @brief Para adicionar 2 doubles devemos recorrer a este instrucomposicaoao. Declara-se as temporarias, declara-se 
 * last e first. Converte de 32 bits para 64 bits. Copia na memoria com a funcao memcpy. Reduz de 64 buts para
 * 32 bits.
 *@return void
 */
void jvm_dadd();

/** @brief Utilizada para subtrair duas longs. Declara-se as variaveis temporarias do tipo int64_t.
 * Declara-se first e last. Desempilha-se dois valores. Converte de 32 buts para 64. E efetua-se a operacomposicaoao
 * por intermedio de uma stack. 
 *@return void
 */
void jvm_lsub();

/** @brief Subtrai dois valores double. Declara-se as variaveis necessarias. Desempilha-se 4 valores e nao mais
 * 2 como estava sendo feito anteriormente. Converte-se de 32 para 64. Copia com a funcao memcpy. 
 * Por fim empilha resultado. 
 *@return void
 */
void jvm_dsub();

/** @brief Declara variaveis do tipo int64_t e u4. Desempilha 4 entradas da pilha. Pois as palavras da pilha sao
 * de 32 bits entao para guardar numeros de 64 bits temos 2 registros. Junta os dois numeros em um so por meio da
 * funcao shift32To64. Por fim multiplica dois valores long e empilha. 
 *@return void
 */
void jvm_lmul();

/** @brief Esta funcao tambem realiza a multiplicacomposicaoao de dois numeros so que neste caso do tipo double.
 *  Para isto deve declarar as variaveis first e last. Em seguida desempilha os quatros valores. Depois converte
 * com shiftCast32ToDouble, empilhando e incrementarndo o ponteiro.
 *@return void
 */
void jvm_dmul();

/** @brief Realiza a divisao de dois longs. Declara 3 variaveis do tipo int64_t e 4 variaveis last e first do tipo u4.
 * Desempilha as usuais 4 registros do topo da pilha. Transforma eles para 64bits com o shift. Opera a divisao com /
 * operador da biblioteca math.h   
 *@return void
 */
void jvm_ldiv();

/** @brief Realiza a divisao de dois valores do tipo double. 
 *@return void
 */
void jvm_ddiv();

/** @brief Calcula  o resto da divisao de duas variaveis do tipo long. Declara variaveis. Desempilha dois valores
 * e converte com shift32to64. Desempilha outros dois valores e converte novamente. Calcula o resto com o operador
 * (%) da biblioteca math.h e empilha o resultado.  
 *@return void
 */
void jvm_lrem();

/** @brief Determina o resto da divisao de duas variaveis do tipo double. 
 *@return void
 */
void jvm_drem();

/** @brief Inverte o sinal de duas longs. Declara variaveis do tipo int64_t e u4. Desempilha dois valores.
 * Converte com shift32To64. Nega a variavel temporaria alterando o sinal: temp = -temp; 
 *@return void
 */
void jvm_lneg();

/** @brief Altera o sinal de duas variaveis do tipo double. 
 *@return void
 */
void jvm_dneg();

/** @brief Declara uma variavel temporaria do tipo int64_t e 3 do tipo u4. Define a mascara 0x3f. Desempilha um
 * valor e faz um and logico com a mascara. Converte de 32 para 64 bits. Realiza o deslocamento temp1 <<= temp2;
 * Empilha o resultado e incrementa pc. 
 *@return void
 */
void jvm_lshl();

/** @brief Efetua o deslocamento de dois valores do tipo long para a direita partindo das referancias 0xffffffffffffffff e
 * 0x80000000000000000.
 *@return void
 */
void jvm_lshr();

/** @brief Efetua o deslocamento de dois valores do tipo long para a direita e desconsidera o sinal.
 *@return void
 */
void jvm_lushr();

/** @brief Declara variaveis do tipo u4 e u8. Desempilha dois valores first e last. Utiliza-se de uma variavel temporaria
 * para converter esses valores de 32 para 64bits. Realliza um and logico com operador &. Por fim empilha o resultado e
 * incrementa o frame_corrente->pc.
 *@return void
 */
void jvm_land();

/** @brief Realiza a operacomposicaoao or bit a bit de duas longs. Desempilha duas entradas da pilha e converte de 32 para 64 bits.
 * Efetua a operacomposicaoao or(|). Empilha resultado. 
 *@return void
 */
void jvm_lor();

/** @brief Efetua a operacomposicaoao ou exclusivo com duas variaveis do tipo long. 
 *@return void
 */
void jvm_lxor();

/** @brief Converte variaveis do tipo long para inteiro. Desempilha dois valores da pilha e empilha apenas um. 
 *@return void
 */
void jvm_l2i();

/** @brief Converte variaveis do tipo long para float. 
 *@return void
 */
void jvm_l2f();

/** @brief Converte de long para double. 
 *@return void
 */
void jvm_l2d();

/** @brief Converte valores do tipo double para inteiro. 
 *@return void
 */
void jvm_d2i();

/** @brief Efetua a conversao de double para long.  
 *@return void
 */
void jvm_d2l();

/** @brief Realiza a conversao de valores do tipo double para float utilizando as funcomposicaooes shift32To64 e
 * memcpy.  
 *@return void
 */
void jvm_d2f();

/** @brief As Instrucoes cmp fazem a comparacomposicaoao entre valor1 e valor2. lcmp: sao para tipos long. 
 * As comparacomposicaoaes devem ser indicadas pelos tipos.
 * @return void
 */
void jvm_lcmp();

/** @brief Compara bit a bit um variavel do tipo double com uma do tipo long.   
 *@return void
 */
void jvm_dcmpl();

/** @brief Declara duas variaveis do tipo double, duas do tipo u4 e uma do tipo u8. Desempilha dois valores e converte
 * de 32 para 64 bits. Copia o valor na variavel com a funcao memcpy. Testa por meio de uma condicional se os valores 
 * sao iguais se sim retorna 0. Se a primeira for maior que a segunda retorna 1 caso contrario retorna -1.  
 *@return void
 */
void jvm_dcmpg();

#endif
