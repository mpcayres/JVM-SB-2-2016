#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "InicializaClasses.h"

classStructure **vetorClasses = NULL;
staticStruct *vetorClassesEstatico = NULL;
int32_t numero_classes = 0;

int32_t flag_impressao = 0;
int32_t flag_execucao = 0;
char strOut[100];
char strPath[200];

void configuraSaida(char *out, char *path, int32_t flag, int32_t flag2){
	flag_impressao = flag;
	flag_execucao = flag2;
	strcpy(strOut, out);
	strcpy(strPath, path);	
}

int32_t carregaClass(char *nomeClass) {
	int32_t i, classIndice;
	methodInfo *metodoEstatico;

	if (nomeClass == NULL) return -1;
	for (i = 0; i < numero_classes; i++)
		if (strcmp(nomeClass, capturaNomeClass(vetorClasses[i])) == 0) return i;
	numero_classes++;
	classIndice = numero_classes;
	
	vetorClasses = realloc(vetorClasses, sizeof(classStructure*)*classIndice);
	vetorClassesEstatico = realloc(vetorClassesEstatico, sizeof(staticStruct)*classIndice);

	vetorClasses[classIndice-1] = salvaInfos(nomeClass, strOut, strPath, flag_impressao);
	if (vetorClasses[classIndice-1] == NULL) {
		printf("\nErro: nao foi possivel abrir o arquivo.\n");
		exit(1);
	}
	//Caso queira imprimir apenas os dados do primeiro arquivo aberto
	//if(flag_impressao == 1) flag_impressao = 0;
	
	if(flag_execucao == 1) {
		vetorClassesEstatico[classIndice-1].className = malloc(strlen(nomeClass)+1);
		memcpy(vetorClassesEstatico[classIndice-1].className, nomeClass, strlen(nomeClass));
		vetorClassesEstatico[classIndice-1].fieldCount = vetorClasses[classIndice-1]->fieldCount;
		vetorClassesEstatico[classIndice-1].value = malloc(sizeof(u8)*(vetorClasses[classIndice-1]->fieldCount));
	
		metodoEstatico = recuperaMetodoEstaticoInit(vetorClasses[classIndice-1]);
		if (metodoEstatico != NULL) {
			prepararMetodo(metodoEstatico, vetorClasses[classIndice-1]);
			executarMetodo();
		}
	}

	//Caso deseje carregar sempre a super classe, porém pode ser que não esteja disponível para ser aberta na pasta
	//char* parent = capturaParentNome(vetorClasses[classIndice-1]);
	//carregaClass(parent);
	return classIndice-1;
}

char* capturaNomeClass(classStructure *class) {
	u2 thisClass = class->thisClass;
	u2 nameIndex = (class->constantPool[thisClass-1]).type.Class.nameIndex;
	
	return getNome(class, nameIndex);
}

char* capturaParentNome(classStructure *class) {
	u1 *name;
	u2 superClass, nameIndex, length;
	char *nomeClass;

	superClass = class->superClass;
	if (superClass == 0) return NULL;

	nameIndex = class->constantPool[superClass-1].type.Class.nameIndex;
	length = class->constantPool[nameIndex-1].type.Utf8.length;
	name = class->constantPool[nameIndex-1].type.Utf8.bytes;
	
	nomeClass = malloc(sizeof(u2) * length+1);
	strncpy(nomeClass, (char *) name, length);
	nomeClass[length] = '\0';
	
	return nomeClass;
}

classStructure* capturaClassPorNome(char *nomeClass) {
	int32_t i;
	if (!nomeClass) return NULL;
	
	for (i = 0; i < numero_classes; i++)
		if (strcmp(nomeClass, capturaNomeClass(vetorClasses[i])) == 0)	return vetorClasses[i];
		
	return NULL;
}

classStructure* capturaClassPorIndice(int32_t indice) {
	if (indice >= numero_classes) return NULL;
	
	return vetorClasses[indice];
}

int32_t capturaIndicedoDescritor(char *nomeClass, char *name, u2 nameLen, char *desc, u2 descLen) {
	u1 *m_nome, *m_descriptor;
	u2 m_nome_tam, m_descriptor_tam;
	classStructure *main_class;
	int32_t i;

	main_class = capturaClassPorNome(nomeClass);
	if (!main_class) return -2;
	
	for (i = 0; main_class && i < main_class->fieldCount; i++) {
		m_nome = main_class->constantPool[(main_class->fields[i].nameIndex-1)].type.Utf8.bytes;
		m_nome_tam = main_class->constantPool[(main_class->fields[i].nameIndex-1)].type.Utf8.length;
		m_descriptor = main_class->constantPool[(main_class->fields[i].descriptorIndex-1)].type.Utf8.bytes;
		m_descriptor_tam = main_class->constantPool[(main_class->fields[i].descriptorIndex-1)].type.Utf8.length;
		
		if(m_descriptor[0] != 'C' && m_descriptor[0] != 'I' && m_descriptor[0] != 'F' && m_descriptor[0] != 'J' &&
			m_descriptor[0] != 'D' && m_descriptor[0] != 'L' && m_descriptor[0] != '[') {
			printf("\nErro: descritor desconhecido.\n");
			exit(1);
		}
		if (nameLen != m_nome_tam && descLen != m_descriptor_tam) continue;

		if ((strncmp((char *)name, (char *)m_nome, m_nome_tam) == 0) && 
			(strncmp((char *)desc, (char *)m_descriptor, m_descriptor_tam) == 0)) 
			return i;
	}

	return -1;
}

u8 capturaCampoEstatico(int32_t classIndice, int32_t campo_indice) {
	return vetorClassesEstatico[classIndice].value[campo_indice];
}

void atribuiCampoEstatico(int32_t classIndice, int32_t campo_indice, u8 value) {
	vetorClassesEstatico[classIndice].value[campo_indice] = value;
}
