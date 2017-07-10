#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "GerenciaHeap.h"

static u4 heap_indice;
static u4 heap_maximo;

void novaHeap() {
	heap = calloc(sizeof(struct Object*), HEAP_INIT);
	heap_indice = 0;
	heap_maximo = HEAP_INIT;
}

struct Object* novoObject(classStructure *cs_this) {
	struct Object *object;
	u4 i, j, cont;
	u2 indice;
	char descriptor[200];
	cpInfo *descriptor_struct;

	if(!cs_this) return NULL;

	if(heap == NULL) novaHeap();
	if(heap_indice == heap_maximo) {
		if(heap == NULL) {
			printf("\nErro: sem memoria Heap.\n");
			exit(1);
		}
		heap = realloc(heap, heap_maximo + HEAP_INIT);
		heap_maximo += HEAP_INIT;
	}

	object = calloc(sizeof(struct Object), 1);
	object->this = cs_this;
	object->super = novoObject(capturaClassPorNome(capturaParentNome(cs_this)));

	for (i = 0, cont = 0; i < cs_this->fieldCount; i++) {
		cont++;
		indice = cs_this->fields[i].descriptorIndex;
		descriptor_struct = &(cs_this->constantPool[indice - 1]);
		memcpy(descriptor, descriptor_struct->type.Utf8.bytes, descriptor_struct->type.Utf8.length);

		if (descriptor[0] == 'D' || descriptor[0] == 'J') cont++;
	}

	object->fields = calloc(sizeof(u4), cont);
	object->fields_index = calloc(sizeof(u4), cont);

	for (i = 0, j = 0; i < cs_this->fieldCount; i++, j++) {
		object->fields_index[j] = cs_this->fields[i].nameIndex;

		indice = cs_this->fields[i].descriptorIndex;
		descriptor_struct = &(cs_this->constantPool[indice - 1]);
		memcpy(descriptor, descriptor_struct->type.Utf8.bytes, descriptor_struct->type.Utf8.length);

		if (descriptor[0] == 'D' || descriptor[0] == 'J')
			object->fields_index[++j] = -1;
			
	}

	heap[heap_indice] = object;
	heap_indice++;
	return object;
}

u4 capturaCampoObjeto(struct Object* object, u4 nameIndex) {
	int32_t i;
	
	for(i = 0; object->fields_index[i] != nameIndex; i++);
	
	return object->fields[i];
}

u8 capturaCampoObjetoLargo(struct Object* object, u4 nameIndex) {
	int32_t i = 0;
	
	for(i = 0; object->fields_index[i] != nameIndex; i++);

	return shift32To64(object->fields[i],object->fields[i+1]);
}

void atribuiCampoObjeto(struct Object* object, u4 nameIndex, u4 valor) {
	int32_t i;
	
	for(i = 0; object->fields_index[i] != nameIndex; i++);
	
	object->fields[i] = valor;
}

void atribuiCampoObjetoLargo(struct Object* object, u4 nameIndex, u8 valor) {
	int32_t i;
	u4 low, high;

	for(i = 0; object->fields_index[i] != nameIndex; i++);

	shift64To32(valor, &low, &high);
	object->fields[i] = low;
	object->fields[i+1] = high;
}

void* novoArray(u4 cont, u1 type) {
	u4 size;
	void *array;

	switch (type) {
		case TYPE_BOOLEAN:
			size = 1;
			break;
		case TYPE_BYTE:
			size = 1;
			break;
		case TYPE_SHORT:
			size = 2;
			break;
		case TYPE_CHAR:
			size = 2;
			break;
		case TYPE_INT:
			size = 4;
			break;
		case TYPE_FLOAT:
			size= 4;
			break;
		case TYPE_REFERENCE:
			size = 4;
			break;
		case TYPE_DOUBLE:
			size = 8;
			break;
		case TYPE_LONG:
			size = 8;
			break;
	}

	numArrays++;
	
	array = calloc(cont, size);
	tamArray = realloc(tamArray, sizeof(struct array)*numArrays);
	
	tamArray[numArrays-1].size = size;
	tamArray[numArrays-1].ref = (u4) array;

	return array;
}

