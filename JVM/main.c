/**  @file: main.c
 * @brief Aquivo principal do programa
 * 
 * @details Aqui sao comeca a execucao da JVM chamando todos as funcoes de execucao e exibicao
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FuncoesAuxiliares.h"
#include "InicializaClasses.h"
#include "InstrucoesGerais.h"
#include "GerenciaMetodos.h"

struct array *tamArray;
u4 numArrays;

/**
* @brief Função principal do programa
*
* @param int32_t argc - número de parâmetros passados por linha de comando
* @param char **argv - nome do arquivo.class e/ou flag passado por linha de comando
* 
* @return Sucesso ou falha de acordo com o .class passado
*/
int32_t main(int32_t argc, char **argv) {
	char strIn[100], strOut[100], strPath[200];
	methodInfo *metodoMain;
	int32_t flagImpr = 0, flagExec = 1;
	numArrays = 0;
	tamArray = NULL;
	
	iniciarInstrucoes();
	carregaOpcodeInfo();

	if (argc < 2) {
		printf("Informe o nome do .class: ");
		scanf("%s", strIn);
		getchar();
	} else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-p") == 0){
		
		flagImpr = 1;
		if(strcmp(argv[1], "-p") == 0) flagExec = 0;
		
		if (argc >= 3) {
			strcpy(strIn, argv[2]);
		} else{
			printf("Informe o nome do .class: ");
			scanf("%s", strIn);
			getchar();
		}
		
		if (argc >= 4) {
			strcpy(strOut, argv[3]);
		} else{
			strcpy(strOut, "");
		}
		
		if (argc >= 5) {
			strcpy(strPath, argv[4]);
		} else{
			strcpy(strPath, "");
		}
		
		if (argc > 5) {
			printf("Aviso: necessario, no maximo, tres parametros, caso a flag esteja ativada.\n");
		}
		
	} else {
		
		strcpy (strIn, argv[1]);
		strcpy(strOut, "");
		
		if (argc >= 3) {
			strcpy(strPath, argv[2]);
		} else{
			strcpy(strPath, "");
		}
		
		if (argc > 3) {
			printf("Aviso: necessario, no maximo, dois parametros, caso a flag nao esteja ativada.\n");
		}
		
	}
	
	configuraSaida(strOut, strPath, flagImpr, flagExec);
	carregaClass(strIn);
	
	if(flagExec == 1){
		metodoMain = recuperaMetodoMain();
		if(metodoMain) {
			prepararMetodo(metodoMain, capturaClassPorIndice(0));
			executarMetodo();
		} else {
			printf("\nErro: o metodo main nao foi encontrado.\n");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;

}
