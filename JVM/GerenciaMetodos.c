#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GerenciaMetodos.h"

extern struct frame *frame_corrente;

methodInfo* recuperaMetodoMain() {
	u1 *name, *descriptor;
	u2 name_length, descriptor_length;
	classStructure *main_class;
	int32_t i;

	main_class = capturaClassPorIndice(0);
	for(i = 0; i < main_class->methodCount; i++) {
		
		name = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.bytes;
		name_length = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.length;
		descriptor = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.bytes;
		descriptor_length = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.length;
		
		if((strncmp("main", (char *)name, name_length) == 0) && 
			(strncmp("([Ljava/lang/String;)V", (char *) descriptor, descriptor_length) == 0)) return &(main_class->methods[i]);
			
	}
	
	return NULL;
}

methodInfo* recuperaMetodoEstaticoInit(classStructure *main_class) {
	u1 *name, *descriptor;
	u2 name_length, descriptor_length;
	int32_t i;

	for(i = 0; i < main_class->methodCount; i++) {
		
		name = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.bytes;
		name_length = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.length;
		descriptor = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.bytes;
		descriptor_length = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.length;
		
		if((strncmp("<clinit>", (char *)name, name_length) == 0) && 
			(strncmp("()V", (char *)descriptor, descriptor_length) == 0)) return &(main_class->methods[i]);
	
	}
	
	return NULL;
}

methodInfo* recuperaMetodoPorNome_IndiceDesc(classStructure *main_class, classStructure *name_type_class, u2 name_type_index) {
	u1 *metodo_name, *metodo_descriptor;
	u2 metodo_name_len, metodo_descriptor_len, name_len, descriptor_len;
	char *name, *descriptor;
	int32_t i;
	
	name = getNome(name_type_class, name_type_class->constantPool[name_type_index-1].type.NameType.nameIndex);
	name_len = strlen(name);
	descriptor = getNome(name_type_class, name_type_class->constantPool[name_type_index-1].type.NameType.descriptorIndex);
	descriptor_len = strlen(descriptor);
	
	for(i = 0; i < main_class->methodCount; i++) {
		
		metodo_name = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.bytes;
		metodo_name_len = main_class->constantPool[(main_class->methods[i].nameIndex-1)].type.Utf8.length;
		metodo_descriptor = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.bytes;
		metodo_descriptor_len = main_class->constantPool[(main_class->methods[i].descriptorIndex-1)].type.Utf8.length;
		
		if(name_len != metodo_name_len && descriptor_len != metodo_descriptor_len) continue;
	
		if((strncmp((char *) name, (char *) metodo_name, metodo_name_len) == 0) && 
			(strncmp((char *) descriptor, (char *) metodo_descriptor, metodo_descriptor_len) == 0))
			return (main_class->methods + i);
		
	}
	return NULL;
}

int32_t recuperaNumeroParametros(methodInfo *method, classStructure *class) {
	int32_t i, numero_parametros = 0;
	u1 *bytes;
	u2 length;

	bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
	length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;
	
	for(i = 0; i < length && bytes[i] != ')'; i++) {
		
		if(bytes[i] == 'L') {
			for( ; bytes[i] != ';'; i++);
	     	numero_parametros++;	
		} else if((bytes[i] == 'B') ||
				 (bytes[i] == 'C') ||
				 (bytes[i] == 'F') || 
				 (bytes[i] == 'I') ||
				 (bytes[i] == 'S') ||
				 (bytes[i] == 'Z') ) {
			numero_parametros++;
		} else if((bytes[i] == 'D') ||
				 (bytes[i] == 'J')) {
			numero_parametros += 2;
		}
		
	}
	
	return numero_parametros;
}

void executarMetodo() {
	
	while(frame_corrente != NULL && (frame_corrente->pc) < frame_corrente->codeLength)
		executarInstrucoes(frame_corrente->code[frame_corrente->pc]);
	liberaFrame();
	
	if(returnType == RETURN_32) push((u4) returnValue);
	else if(returnType == RETURN_64) pushU8( returnValue );
	
	returnType = RETURN_NONE;
	returnValue = 0;
	
}

void prepararMetodo(methodInfo *method, classStructure *class) {
	int32_t i;
	
	for(i = 0; i < method->attributeCount; i++)
		if(method->attributes[i].tag == ATTRIBUTE_CODE)	break;
	
	if(method->attributeCount != 0) {
		if(method->attributes[i].tag != ATTRIBUTE_CODE) {
			printf("\nErro: nao foi encontrado atributo code no metodo.");
			exit(1);
		}
		novoFrame(class, class->constantPool, &(method->attributes[i]));
	} else {
		(method->attributeCount)++;
		method->attributes = malloc(1 * sizeof(attributeInfo));
		
		method->attributes[0].type.Code.codeLength = 0;
		novoFrame(class, class->constantPool, &(method->attributes[0]));
	}
	
}
