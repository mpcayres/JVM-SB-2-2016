#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#include "InstrucoesGerais.h"

extern struct frame *frame_corrente;
extern struct array *tamArray;
extern u1 returnType;
extern u8 returnValue;
int32_t wide = 0;

void jvm_nop() {
	frame_corrente->pc++;
}

void jvm_pop() {
	pop();
	frame_corrente->pc++;
}

void jvm_pop2() {
	pop();
	pop();
	frame_corrente->pc++;
}

void jvm_dup() {
	u4 temp;
	
	temp = pop();
	
	push(temp);
	push(temp);
	
	frame_corrente->pc++;
}

void jvm_dup_x1() {
	u4 temp1, temp2;
	
	temp1 = pop();
	temp2 = pop();
	
	push(temp1);
	push(temp2);
	push(temp1);
	
	frame_corrente->pc++;
}

void jvm_dup_x2() {
	u4 atributo1, atributo2, atributo3;
	
	atributo1 = pop();
	atributo2 = pop();
	atributo3 = pop();
	
	push(atributo1);
	push(atributo3);
	push(atributo2);
	push(atributo1);
	
	frame_corrente->pc++;
}

void jvm_dup2() {
	u4 atributo1, atributo2;
	
	atributo1 = pop();
	atributo2 = pop();
	
	push(atributo2);
	push(atributo1);
	push(atributo2);
	push(atributo1);
	
	frame_corrente->pc++;
}

void jvm_dup2_x1() {
	u4 atributo1, atributo2, atributo3;
	
	atributo1 = pop();
	atributo2 = pop();
	atributo3 = pop();
	
	push(atributo2);
	push(atributo1);
	push(atributo3);
	push(atributo2);
	push(atributo1);
	
	frame_corrente->pc++;
}

void jvm_dup2_x2() {
	u4 atributo1, atributo2, atributo3, atributo4;
	
	atributo1 = pop();
	atributo2 = pop();
	atributo3 = pop();
	atributo4 = pop();
	
	push(atributo2);
	push(atributo1);
	push(atributo4);
	push(atributo3);
	push(atributo2);
	push(atributo1);
	
	frame_corrente->pc++;
}

void jvm_swap() {
	u4 temp1, temp2;
	
	temp1 = pop();
	temp2 = pop();
	
	push(temp1);
	push(temp2);
	
	frame_corrente->pc++;
}

void jvm_iload() {
	u2 indice;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];

	if(wide == 1) {
		indice = indice << 8;
		frame_corrente->pc++;
		indice = indice | frame_corrente->code[frame_corrente->pc];
		wide = 0;
	}
	
	push(frame_corrente->fields[indice]);
	frame_corrente->pc++;
}

void jvm_fload() {
	u2 indice;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];

	if(wide == 1) {
		indice = indice << 8;
		frame_corrente->pc++;
		indice = indice | frame_corrente->code[frame_corrente->pc];
		wide = 0;
	}
	
	push(frame_corrente->fields[indice]);
	frame_corrente->pc++;
}

void jvm_lload() {
	u2 indice = 0;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];

	if(wide == 1) {
		indice = indice << 8;
		frame_corrente->pc++;
		indice = indice | frame_corrente->code[frame_corrente->pc];
		wide = 0;
	}
	
	push(frame_corrente->fields[indice]);
	push(frame_corrente->fields[indice+1]);
	frame_corrente->pc++;
}

void jvm_dload() {
	u2 indice;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];

	if(wide == 1) {
		indice = indice << 8;
		frame_corrente->pc++;
		indice = indice | frame_corrente->code[frame_corrente->pc];
		wide = 0;
	}
	
	push(frame_corrente->fields[indice]);
	push(frame_corrente->fields[indice+1]);
	frame_corrente->pc++;
}

void jvm_aload() {
	u2 indice;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];

	if(wide == 1) {
		indice = indice << 8;
		frame_corrente->pc++;
		indice = indice | frame_corrente->code[frame_corrente->pc];
		wide = 0;
	}
	
	push(frame_corrente->fields[indice]);
	frame_corrente->pc++;
}

void jvm_ireturn() {
	u4 atributo;
	
	atributo = pop();
	returnType = RETURN_32;
	returnValue = (u8) atributo;
	
	frame_corrente->pc++;
}

void jvm_freturn() {
	u4 atributo;
	
	atributo = pop();
	returnType = RETURN_32;
	returnValue = (u8) atributo;
	
	frame_corrente->pc++;
}

void jvm_lreturn() {
	u4 first, last;
	
	first = pop(); last = pop();
	returnType = RETURN_64;
	returnValue = shift32To64(first, last);
	
	frame_corrente->pc++;
}

void jvm_dreturn() {
	u4 first, last;
	
	first = pop(); last = pop();
	returnType = RETURN_64;
	returnValue = shift32To64(first, last);
	
	frame_corrente->pc++;
}

void jvm_areturn() {
	u4 atributo;
	
	atributo = pop();
	returnType = RETURN_32;
	returnValue = (u8) atributo;
	
	frame_corrente->pc++;
}

void jvm_return() {
	returnType = RETURN_NONE;
	returnValue = 0;
	frame_corrente->pc++;
}

void jvm_ifeq() {
	u1 divinfo1, divinfo2;
	int16_t desloc;
	int32_t temp;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp = (signed) pop();
	if(temp == 0) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_ifne() {
	u1 divinfo1, divinfo2;
	int16_t desloc;
	int32_t temp;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp = (signed) pop();
	if(temp != 0) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_iflt() {
	u1 divinfo1, divinfo2;
	int32_t temp;
	int16_t desloc;
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	temp = (signed) pop();
	if(temp < 0) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else {
		frame_corrente->pc += 3;
	}
}

void jvm_ifge() {
	u1 divinfo1, divinfo2;
	int32_t temp;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp = (signed) pop();
 	if(temp >= 0) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_ifgt() {
	u1 divinfo1, divinfo2;
	int32_t temp;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp = (signed) pop();
	if(temp > 0) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_ifle() {
	u1 divinfo1, divinfo2;
	int32_t temp;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp = (signed) pop();
	if(temp <= 0) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_icmpeq() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp1 = (signed) pop(); temp2 = (signed) pop();
	if(temp1 == temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_icmpne() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp1 = (signed) pop(); temp2 = (signed) pop();
	if(temp1 != temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_icmplt() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp2 = (signed) pop(); temp1 = (signed) pop();
 	if(temp1 < temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_icmpge() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp2 = (signed) pop(); temp1 = (signed) pop();
	if(temp1 >= temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_icmpgt() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp2 = (signed) pop(); temp1 = (signed) pop();
	if(temp1 > temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_icmple() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp2 = (signed) pop(); temp1 = (signed) pop();
	if(temp1 <= temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_acmpeq() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp2 = (signed) pop(); temp1 = (signed) pop();
	if(temp1 == temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_if_acmpne() {
	u1 divinfo1, divinfo2;
	int32_t temp1, temp2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	temp2 = (signed) pop(); temp1 = (signed) pop();
	if(temp1 != temp2) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_goto() {
	u1 divinfo1, divinfo2;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	desloc = (int16_t)shift8To32(divinfo2, divinfo1);
	frame_corrente->pc += desloc;
}

void jvm_jsr() {
	u1 divinfo1, divinfo2;
	int16_t desloc;
	
	push((frame_corrente->pc) + 3);
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	
	desloc = (int16_t)shift8To32(divinfo2, divinfo1);
	frame_corrente->pc += desloc;
}

void jvm_ret() {
	u2 indice;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];
	
	if(wide == 1){
		indice = indice << 8;
		frame_corrente->pc++;
		indice = indice | frame_corrente->code[frame_corrente->pc];
		wide = 0;
	}
	
	frame_corrente->pc = frame_corrente->fields[indice];
}

void jvm_tableswitch() {
	int32_t defaulT, last, first, indice, *tableswitch;
	u4 i, info1, info2, info3, info4, tableswitch_address, target, tableSize, desloc;

	indice = (int32_t) pop();
	for(tableswitch_address = frame_corrente->pc; (frame_corrente->pc + 1) % 4 != 0; frame_corrente->pc++) 
	frame_corrente->pc++;

	info1 = frame_corrente->code[frame_corrente->pc++];
	info2 = frame_corrente->code[frame_corrente->pc++];
	info3 = frame_corrente->code[frame_corrente->pc++];
	info4 = frame_corrente->code[frame_corrente->pc++];
	defaulT = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);

	info1 = frame_corrente->code[frame_corrente->pc++];
	info2 = frame_corrente->code[frame_corrente->pc++];
	info3 = frame_corrente->code[frame_corrente->pc++];
	info4 = frame_corrente->code[frame_corrente->pc++];
	first = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);

	info1 = frame_corrente->code[frame_corrente->pc++];
	info2 = frame_corrente->code[frame_corrente->pc++];
	info3 = frame_corrente->code[frame_corrente->pc++];
	info4 = frame_corrente->code[frame_corrente->pc++];
	last = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);

	tableSize = last - first + 1;
	tableswitch = calloc(sizeof(u4), tableSize);

	for(i = 0; i < tableSize; i++) 	{
		info1 = frame_corrente->code[frame_corrente->pc++];
		info2 = frame_corrente->code[frame_corrente->pc++];
		info3 = frame_corrente->code[frame_corrente->pc++];
		info4 = frame_corrente->code[frame_corrente->pc++];
		tableswitch[i] = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);
	}

	if(indice < first || indice > last) target = tableswitch_address + defaulT;
	else {
		desloc = tableswitch[indice - first];
		target = tableswitch_address + desloc;
	}
	
	frame_corrente->pc = target;
}

void jvm_lookupswitch() {
	int32_t defaulT, npairs, key, *match, *desloc;
	u4 i, info1, info2, info3, info4, target, lookupswitch_address;
	u1 encontrado;

	key = (int32_t)pop();
	for(lookupswitch_address = frame_corrente->pc; (frame_corrente->pc + 1) % 4 != 0; frame_corrente->pc++);
	frame_corrente->pc++;

	info1 = frame_corrente->code[frame_corrente->pc++];
	info2 = frame_corrente->code[frame_corrente->pc++];
	info3 = frame_corrente->code[frame_corrente->pc++];
	info4 = frame_corrente->code[frame_corrente->pc++];
	defaulT = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);

	info1 = frame_corrente->code[frame_corrente->pc++];
	info2 = frame_corrente->code[frame_corrente->pc++];
	info3 = frame_corrente->code[frame_corrente->pc++];
	info4 = frame_corrente->code[frame_corrente->pc++];
	npairs = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);

	match = calloc(sizeof(int32_t), npairs);
	desloc = calloc(sizeof(int32_t), npairs);
	for(i = 0; i < npairs; i++) {
		info1 = frame_corrente->code[frame_corrente->pc++];
		info2 = frame_corrente->code[frame_corrente->pc++];
		info3 = frame_corrente->code[frame_corrente->pc++];
		info4 = frame_corrente->code[frame_corrente->pc++];
		match[i] = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);
		
		info1 = frame_corrente->code[frame_corrente->pc++];
		info2 = frame_corrente->code[frame_corrente->pc++];
		info3 = frame_corrente->code[frame_corrente->pc++];
		info4 = frame_corrente->code[frame_corrente->pc++];
		desloc[i] = ((info1 & 0xFF) << 24) | ((info2 & 0xFF) << 16) | ((info3 & 0xFF) << 8) | (info4 & 0xFF);
	}

	for(i = 0, encontrado = 0; (i < npairs) && (!encontrado); i++)
		if(match[i] == key) encontrado = 1;
	i--;

	if(encontrado) target = desloc[i] + lookupswitch_address;
	else target = defaulT + lookupswitch_address;

	frame_corrente->pc = target;
}

void jvm_getstatic() {
	u1 indice1, indice2;
	u2 indice, nameTypeIndex;
	u4 classIndexTemp;
	u8 atributo;
	int32_t classIndex, field_index;
	char *className, *name, *type;

	indice1 = (u1) frame_corrente->code[++(frame_corrente->pc)];
	indice2 = (u1) frame_corrente->code[++(frame_corrente->pc)];
	indice = ((u2) indice1 << 8) | (u2) indice2;
	
	classIndexTemp = frame_corrente->constantPool[indice-1].type.FieldRef.classIndex;
	className = getNome(frame_corrente->class, frame_corrente->constantPool[classIndexTemp-1].type.Class.nameIndex);
	nameTypeIndex = frame_corrente->constantPool[indice-1].type.FieldRef.nameTypeIndex;
	name = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);

	while((field_index = capturaIndicedoDescritor(className, name, strlen(name), type, strlen(type))) == -1)
		className = capturaParentNome(capturaClassPorNome(className));

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') pushU8(0);
		else push(0);
	} else {
		classIndex = carregaClass(className);
		atributo = capturaCampoEstatico(classIndex, field_index);
		if(type[0] == 'J' || type[0] == 'D') pushU8(atributo);
		else push((u4)atributo);
	}
	
	frame_corrente->pc++;
}

void jvm_putstatic() {
	u1 indice1, indice2;
	u2 indice, nameTypeIndex;
	u4 classIndexTemp, atributo1, atributo2;
	u8 atributo;
	int32_t classIndex, field_index;
	char *className, *name, *type;

	indice1 = (u1) frame_corrente->code[++(frame_corrente->pc)];
	indice2 = (u1) frame_corrente->code[++(frame_corrente->pc)];
	indice = ((u2)indice1 << 8) | (u2)indice2;
	
	classIndexTemp = frame_corrente->constantPool[indice-1].type.FieldRef.classIndex;
	className = getNome(frame_corrente->class, frame_corrente->constantPool[classIndexTemp-1].type.Class.nameIndex);
	nameTypeIndex = frame_corrente->constantPool[indice-1].type.FieldRef.nameTypeIndex;
	name = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);
	
	while((field_index = capturaIndicedoDescritor(className, name, strlen(name), type, strlen(type))) == -1)
		className = capturaParentNome(capturaClassPorNome(className));

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') {
			pop(); pop();
		} else pop();
	} else{
		if(type[0] == 'J' || type[0] == 'D') {
			atributo1 = pop();
			atributo2 = pop();
			atributo = shift32To64(atributo1, atributo2);
		} else atributo = (u8) pop();
		classIndex = carregaClass(className);
		atribuiCampoEstatico(classIndex, field_index, atributo);
	}

	frame_corrente->pc++;
}

void jvm_getfield() {
	u1 first, last;
	u2 nameTypeIndex;
	u4 indice, valor_temp;
	u8 atributo;
	int32_t classIndex, field_index, nameIndex;
	char *className, *name, *type;
	struct Object *objeto;

	last = frame_corrente->code[++(frame_corrente->pc)];
	first = frame_corrente->code[++(frame_corrente->pc)];
	indice = shift8To32(first, last);
	
	classIndex = frame_corrente->constantPool[indice-1].type.FieldRef.classIndex;
	className = getNome(frame_corrente->class, frame_corrente->constantPool[classIndex-1].type.Class.nameIndex);
	nameTypeIndex = frame_corrente->constantPool[indice-1].type.FieldRef.nameTypeIndex;
	name = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);
	objeto = (struct Object *) pop();

	while((field_index = capturaIndicedoDescritor(className, name, strlen(name), type, strlen(type))) == -1)
		className = capturaParentNome(capturaClassPorNome(className));

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') pushU8(0);
		else push(0);
	} else{	
		nameIndex = frame_corrente->class->fields[field_index].nameIndex;
		if(type[0] == 'J' || type[0] == 'D') {
			atributo = capturaCampoObjetoLargo(objeto, nameIndex);
			pushU8(atributo);
		} else {
			valor_temp = capturaCampoObjeto(objeto, nameIndex);
			push(valor_temp);
		}
	}
	frame_corrente->pc++;
}

void jvm_putfield() {
	u1 first, last;
	u4 indice;
	int32_t classIndex, field_index, nameIndex;
	u2 nameTypeIndex;
	char *className, *name, *type;

	struct Object *objeto;
	u4 atributo1, atributo2;
	u8 atributo;

	last = frame_corrente->code[++(frame_corrente->pc)];
	first = frame_corrente->code[++(frame_corrente->pc)];
	indice = shift8To32(first, last);
	classIndex = frame_corrente->constantPool[indice-1].type.FieldRef.classIndex;
	className = getNome(frame_corrente->class, frame_corrente->constantPool[classIndex-1].type.Class.nameIndex);
	nameTypeIndex = frame_corrente->constantPool[indice-1].type.FieldRef.nameTypeIndex;
	name = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.nameIndex);
	type = getNome(frame_corrente->class, frame_corrente->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex);

	while((field_index = capturaIndicedoDescritor(className, name, strlen(name), type, strlen(type))) == -1) {
		className = capturaParentNome(capturaClassPorNome(className));
	}

	if(field_index == -2) {
		if(type[0] == 'J' || type[0] == 'D') {
			pop();
			pop();
		} else {
			pop();
		}
		frame_corrente->pc++;
		return;
	}

	nameIndex = frame_corrente->class->fields[field_index].nameIndex;
	if(type[0] == 'J' || type[0] == 'D') {
		atributo1 = pop();
		atributo2 = pop();
		objeto = (struct Object *) pop();
		atributo = shift32To64(atributo1, atributo2);
		atribuiCampoObjetoLargo(objeto, nameIndex, atributo);
	} else {
		atributo1 = pop();
		objeto = (struct Object *) pop();
		atribuiCampoObjeto(objeto, nameIndex, atributo1);
	}
	frame_corrente->pc++;
}

void jvm_invokevirtual() {
	classStructure *class;
	methodInfo *method;
	u1 first, last, *bytes;
	u2 length, nameTypeIndex, methodNameIndex, methodDescriptorIndex;
	u4 indice, valorlast, valorfirst, vu4, array_ref, *fieldsTemp;
	u8 atributo;
	int32_t i, j, numParams, classIndex, classIndexTemp;
	char *className, *methodName, *methodDesc;
	float vfloat;

	last = frame_corrente->code[++(frame_corrente->pc)];
	first = frame_corrente->code[++(frame_corrente->pc)];
	indice = shift8To32(first, last);
	
	classIndexTemp = frame_corrente->constantPool[indice-1].type.MethodRef.classIndex;
	className = getNome(frame_corrente->class, frame_corrente->constantPool[classIndexTemp-1].type.Class.nameIndex);
	nameTypeIndex = frame_corrente->constantPool[indice-1].type.MethodRef.nameTypeIndex;
	methodNameIndex = frame_corrente->constantPool[nameTypeIndex-1].type.NameType.nameIndex;
	methodDescriptorIndex = frame_corrente->constantPool[nameTypeIndex-1].type.NameType.descriptorIndex;
	methodDesc = getNome(frame_corrente->class, methodDescriptorIndex);
	methodName = getNome(frame_corrente->class, methodNameIndex);

	if((strcmp(className, "java/io/PrintStream") == 0) && ((strcmp(methodName,"print") == 0) || (strcmp(methodName,"println") == 0))) {

		if(strstr(methodDesc, "J") != NULL){
			valorfirst = pop();
			valorlast = pop();
			atributo = shift32To64(valorfirst, valorlast);
			printf("%"PRIi64, (int64_t)atributo);
		} else if(strstr(methodDesc, "D") != NULL) {
			valorfirst = pop();
			valorlast = pop();
			atributo = shift32To64(valorfirst, valorlast);
			printf("%.15f", atributo);
		} else if(strstr(methodDesc, "Z") != NULL) {
			if(pop()) printf("true");
			else printf("false");
		} else if(strstr(methodDesc, "C") != NULL) {

			if(strstr(methodDesc, "[C") != NULL){
				array_ref = pop();
				for(i = 0; i < numArrays; i++)
					if(tamArray[i].ref == array_ref) break;
				for(j = 0; j < tamArray[i].size; j++)
					printf("%c", (int16_t) array_ref +i);
			} else printf("%c", (int16_t) pop());

		} else if(strstr(methodDesc, "I") != NULL) {
			printf("%"PRIi32, (int32_t)pop());
		} else if(strstr(methodDesc, "F") != NULL) {
			vu4 = pop();
			memcpy(&vfloat, &vu4, sizeof(u4));
			printf("%f", vfloat);
		} else if(strstr(methodDesc, "Ljava/lang/String") != NULL) {
			vu4 = pop();
			printf("%s", (char *)vu4);
		} else if(strstr(methodDesc, "Ljava/lang/Object") != NULL) {
			printf("%p", (void *)pop());
		}

		if(strcmp(methodName,"println") == 0) printf("\n");
		
	} else {
		
		classIndex = carregaClass(className);
		class = capturaClassPorIndice(classIndex);

		while(class != NULL && (method = recuperaMetodoPorNome_IndiceDesc(class, frame_corrente->class, nameTypeIndex)) == NULL) {
			className = capturaParentNome(class);
			classIndex = carregaClass(className);
			class = capturaClassPorIndice(classIndex);
		}

		if(class == NULL) {
			printf("\nErro: metodo nao localizado.\n");
			exit(1);
		}

		numParams = recuperaNumeroParametros(method, class);
		fieldsTemp = calloc(sizeof(u4),numParams+1);
		for(i = numParams; i >= 0; i--) fieldsTemp[i] = pop();

		if(((method->accessFlags) & FLAG_NATIVE) || strcmp("println", getNome(class, method->nameIndex)) == 0) {
			bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
			length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;
			if(bytes[length-1] == 'D' || bytes[length-1] == 'J') pushU8(0);
			else if(bytes[length-1] != 'V') push(0);
		} else {
			prepararMetodo(method, class);
			for(i = numParams; i >= 0; i--) frame_corrente->fields[i] = fieldsTemp[i];
			executarMetodo();
		}
		
	}

	frame_corrente->pc++;
}

void jvm_invokespecial() {
	classStructure *class;
	methodInfo *method;
	u1 first, last, *bytes;
	u2 nameTypeIndex, length;
	u4 indice, *fieldsTemp;
	int32_t i, numParams, classIndex, classIndexTemp;
	char *className;

	last = frame_corrente->code[++(frame_corrente->pc)];
	first = frame_corrente->code[++(frame_corrente->pc)];
	indice = shift8To32(first, last);
	
	classIndexTemp = (frame_corrente->constantPool[indice-1]).type.MethodRef.classIndex;
	className = getNome(frame_corrente->class, (frame_corrente->constantPool[classIndexTemp-1]).type.Class.nameIndex);
	classIndex = carregaClass(className);
	class = capturaClassPorIndice(classIndex);
	nameTypeIndex = ((frame_corrente->constantPool[indice-1])).type.MethodRef.nameTypeIndex;

	while(class != NULL && (method = recuperaMetodoPorNome_IndiceDesc(class, frame_corrente->class, nameTypeIndex)) == NULL) {
		className = capturaParentNome(class);
		classIndex = carregaClass(className);
		class = capturaClassPorIndice(classIndex);
	}

	if(class == NULL) {
		printf("\nErro: metodo nao localizado.\n");
		exit(1);
	}

	numParams = recuperaNumeroParametros(method, class);
	fieldsTemp = calloc(sizeof(u4),numParams+1);
	for(i = numParams; i >= 0; i--) fieldsTemp[i] = pop();

	if(method->accessFlags & FLAG_NATIVE) {
		bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
		length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;
		if(bytes[length-1] == 'D' || bytes[length-1] == 'J') pushU8(0);
		else if(bytes[length-1] != 'V') push(0);
	} else {
		prepararMetodo(method, class);
		for(i = numParams; i >= 0; i--) frame_corrente->fields[i] = fieldsTemp[i];
		executarMetodo();
	}
	
	frame_corrente->pc++;
}

void jvm_invokestatic() {
	classStructure *class;
	methodInfo *method;
	u1 first, last, *bytes;
	u2 nameTypeIndex, length;
	u4 indice, *fieldsTemp;	
	int32_t i, numParams, classIndex, classIndexTemp;	
	char *className;

	last = frame_corrente->code[++(frame_corrente->pc)];
	first = frame_corrente->code[++(frame_corrente->pc)];
	indice = shift8To32(first, last);
	
	classIndexTemp = frame_corrente->constantPool[indice-1].type.MethodRef.classIndex;
	className = getNome(frame_corrente->class, frame_corrente->constantPool[classIndexTemp-1].type.Class.nameIndex);
	nameTypeIndex = frame_corrente->constantPool[indice-1].type.MethodRef.nameTypeIndex;
	classIndex = carregaClass(className);
	
	class = capturaClassPorIndice(classIndex);
	method = recuperaMetodoPorNome_IndiceDesc(class, frame_corrente->class, nameTypeIndex);
	numParams = recuperaNumeroParametros(method, class);
	fieldsTemp = calloc(sizeof(u4),numParams+1);
	
	for(i = numParams-1; i >= 0; i--) {
		indice = pop();
		fieldsTemp[i] = indice;
	}

	if(method->accessFlags & FLAG_NATIVE) {
		bytes = class->constantPool[(method->descriptorIndex-1)].type.Utf8.bytes;
		length = class->constantPool[(method->descriptorIndex-1)].type.Utf8.length;
		if(bytes[length-1] == 'D' || bytes[length-1] == 'J') pushU8(0);
		else if(bytes[length-1] != 'V') push(0);
	} else {
		prepararMetodo(method, class);
		for(i = numParams-1; i >= 0; i--) frame_corrente->fields[i] = fieldsTemp[i];
		executarMetodo();
	}
	
	frame_corrente->pc++;
}

void jvm_invokeinterface() {
	classStructure *class;
	methodInfo *method;
	u1 first, last, args_count, zero;
	u4 indice, *fieldsTemp;
	u2 nameTypeIndex;
	int32_t i, classIndex, classIndexTemp;
	char *className;

	last = frame_corrente->code[++(frame_corrente->pc)];
	first = frame_corrente->code[++(frame_corrente->pc)];
	indice = shift8To32(first, last);
	
	args_count = frame_corrente->code[++(frame_corrente->pc)];
	zero = frame_corrente->code[++(frame_corrente->pc)];
	fieldsTemp = calloc(sizeof(u4),args_count+1);
	
	for(i = args_count; i >= 0; i--) fieldsTemp[i] = pop();

	classIndexTemp = frame_corrente->constantPool[indice-1].type.MethodRef.classIndex;
	className = getNome(frame_corrente->class, frame_corrente->constantPool[classIndexTemp-1].type.Class.nameIndex);
	classIndex = carregaClass(className);
	
	class = capturaClassPorIndice(classIndex);
	nameTypeIndex = (frame_corrente->constantPool[indice-1].type.MethodRef.nameTypeIndex);
	
	while(class != NULL && (method = recuperaMetodoPorNome_IndiceDesc(class, frame_corrente->class, nameTypeIndex)) == NULL) {
		className = capturaParentNome(class);
		classIndex = carregaClass(className);
		class = capturaClassPorIndice(classIndex);
	}

	if(class == NULL) {
		printf("\nErro: metodo nao localizado.\n");
		exit(1);
	}
	
	prepararMetodo(method, class);
	for(i = args_count; i >= 0; i--) frame_corrente->fields[i] = fieldsTemp[i];
	executarMetodo();
	
	frame_corrente->pc++;
}

void jvm_invokedynamic() {
	printf("\nErro: nao e capaz de realizar invokedynamic.\n");
	exit(1);
}

void jvm_new() {
	u1 first, last;
	u4 indice;
	int32_t classIndex;
	char *className;
	classStructure *class;
	struct Object *objeto;

	last = frame_corrente->code[++(frame_corrente->pc)];
	first = frame_corrente->code[++(frame_corrente->pc)];

	indice = shift8To32(first, last);
	className = getNome(frame_corrente->class, frame_corrente->constantPool[indice-1].type.Class.nameIndex);
	classIndex = carregaClass(className);
	class = capturaClassPorIndice(classIndex);
	objeto = novoObject(class);
	
	push((u4) objeto);
	frame_corrente->pc++;
}

void jvm_newarray() {
	u1 type;
	u4 count;
	
	count = pop();
	frame_corrente->pc++;
	type = frame_corrente->code[frame_corrente->pc];
	
	if(count < 0){
		printf("\nErro: array de tamanho incompativel.\n");
		exit(1);
	}
	
	push((u4) novoArray(count, type));
	frame_corrente->pc++;
}

void jvm_anewarray() {
	u4 count;
	count = pop();
	frame_corrente->pc++;
	frame_corrente->pc++;
	if(count < 0) {
		printf("\nErro: array de tamanho incompativel.\n");
		exit(1);
	}
	
	push((u4) novoArray(count, 0));
	frame_corrente->pc++;
}

void jvm_arraylength() {
	u4 aref;
	int32_t i;
	
	aref = pop();
	for(i = 0; i < numArrays; i++, frame_corrente->pc++) {
		if(tamArray[i].ref == aref) {
			push(tamArray[i].ref);
			frame_corrente->pc++;
			return;
		}
	}
	
	push(0);
	frame_corrente->pc++;
}

void jvm_athrow() {
	frame_corrente->pc++;
}

void jvm_checkcast() {
	u2 indice;
	struct Object *ref;

	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];
	indice = indice << 8;
	
	frame_corrente->pc++;
	indice = indice | frame_corrente->code[frame_corrente->pc];
	ref = (struct Object *) pop();
	
	if(ref == NULL) {
		printf("\nErro: referencia incorreta.\n");
		exit(1);
	}
	
	if(strcmp(getNome(frame_corrente->class, indice), capturaNomeClass(ref->this)) == 0) {
		printf("\nErro: objeto de tipo errado.\n");
		exit(1);
	}
	
	push((u4) ref);
	frame_corrente->pc++;
}

void jvm_instanceof() {
	u2 indice;
	struct Object *ref;

	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];
	indice = indice << 8;
	
	frame_corrente->pc++;
	indice = indice | frame_corrente->code[frame_corrente->pc];
	ref = (struct Object *) pop();
	
	if(ref == NULL) {
		printf("\nErro: referencia nula.\n");
		exit(1);
	}
	
	if(strcmp(getNome(frame_corrente->class, indice), capturaNomeClass(ref->this)) == 0) {
		push(1);
		frame_corrente->pc++;
		return;
	}
	
	push(0);
	frame_corrente->pc++;
}

void jvm_monitorenter() {
	printf("\nErro: nao e capaz de realizar monitorenter.\n");
	exit(1);
}

void jvm_monitorexit() {
	printf("\nErro: nao e capaz de realizar monitorexit.\n");
	exit(1);
}

void jvm_wide() {
	wide = 1;	
	frame_corrente->pc++;
}

void jvm_multianewarray() {
	u1 dimensions;
	u2 indexinfo1, indexinfo2, indice, type, atype;
	u4 i, dimension, size;
	void *arrayref;
	char *array_type;

	frame_corrente->pc++; indexinfo1 = frame_corrente->code[frame_corrente->pc];
	frame_corrente->pc++; indexinfo2 = frame_corrente->code[frame_corrente->pc];
	frame_corrente->pc++; frame_corrente->code[frame_corrente->pc];
	frame_corrente->pc++; frame_corrente->code[frame_corrente->pc];
	
	indice = ((indexinfo1 & 0xFF) << 8) | (indexinfo2 & 0xFF);
	dimension = pop();
	arrayref = novoArray(dimension, TYPE_REFERENCE);
	array_type = getNome(frame_corrente->class, frame_corrente->constantPool[indice -1].type.Class.nameIndex);
	
	for(i = 0; array_type[i] == '['; i++);
	
	switch(array_type[i]) {
		case 'L':
			type = TYPE_REFERENCE;
			atype = TYPE_REFERENCE;
			break;
		case 'Z':
			type = TYPE_BOOLEAN;
			atype = TYPE_BOOLEAN_SIZE;
			break;
		case 'C':
			type = TYPE_CHAR;
			atype = TYPE_CHAR_SIZE;
			break;
		case 'F':
			type = TYPE_FLOAT;
			atype = TYPE_FLOAT_SIZE;
			break;
		case 'D':
			type = TYPE_DOUBLE;
			atype = TYPE_DOUBLE_SIZE;
			break;
		case 'B':
			type = TYPE_BYTE;
			atype = TYPE_BYTE_SIZE;
			break;
		case 'S':
			type = TYPE_SHORT;
			atype = TYPE_SHORT_SIZE;
			break;
		case 'I':
			type = TYPE_INT;
			atype = TYPE_INT_SIZE;
			break;
		case 'J':
			type = TYPE_LONG;
			atype = TYPE_LONG_SIZE;
			break;
		default:
			type = TYPE_REFERENCE;
			atype = TYPE_REFERENCE_SIZE;
	}
	for(i = 0; i < dimensions; i++)	{
		
		size = pop();
		
		if(size == 0) break;
		if(atype == 1) ((u1**)arrayref)[i] = (u1*)novoArray(type, size);
		else if(atype == 2) ((u2**)arrayref)[i] = (u2*)novoArray(type, size);
		else if(atype == 4) ((u4**)arrayref)[i] = (u4*)novoArray(type, size);
		else ((u8**)arrayref)[i] = (u8*)novoArray(type, size);
		
	}
	
	push((u4) arrayref);
	frame_corrente->pc++;
}

void jvm_ifnull() {
	u4 desloc;
	u1 divinfo1, divinfo2;
	int32_t temp;

	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	temp = (signed) pop();
	
	if(temp == NULL_CONST) {
		desloc = shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_ifnonnull() {
	u1 divinfo1, divinfo2;
	int32_t temp;
	int16_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	temp = (signed) pop();
	
	if(temp != NULL_CONST) {
		desloc = (int16_t)shift8To32(divinfo2, divinfo1);
		frame_corrente->pc += desloc;
	} else frame_corrente->pc += 3;
	
}

void jvm_goto_w() {
	u4 divinfo1, divinfo2, divinfo3, divinfo4;
	int32_t desloc;
	
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	divinfo3 = frame_corrente->code[(frame_corrente->pc)+3];
	divinfo4 = frame_corrente->code[(frame_corrente->pc)+4];
	
	desloc = (int32_t) ( ((divinfo1 & 0xFF)<<24) | ((divinfo2 & 0xFF)<<16) | 
						  ((divinfo3 & 0xFF)<<8) | (divinfo1 & 0xFF) );
	frame_corrente->pc += desloc;
}

void jvm_jsr_w() {
	u4 divinfo1, divinfo2, divinfo3, divinfo4;
	int32_t desloc;
	
	push((frame_corrente->pc) + 5);
	divinfo1 = frame_corrente->code[(frame_corrente->pc)+1];
	divinfo2 = frame_corrente->code[(frame_corrente->pc)+2];
	divinfo3 = frame_corrente->code[(frame_corrente->pc)+3];
	divinfo4 = frame_corrente->code[(frame_corrente->pc)+4];
	
	desloc = (int32_t) ( ((divinfo1 & 0xFF)<<24) | ((divinfo2 & 0xFF)<<16) | 
						  ((divinfo3 & 0xFF)<<8) | (divinfo1 & 0xFF) );
	frame_corrente->pc += desloc;
}

void executarInstrucoes(u1 opcode) {
	vetorInstruc[opcode]();
}

void iniciarInstrucoes() {
	vetorInstruc[0x00] = jvm_nop;
	vetorInstruc[0x01] = jvm_aconst_null;
	vetorInstruc[0x02] = jvm_iconst_m1;
	vetorInstruc[0x03] = jvm_iconst_0;
	vetorInstruc[0x04] = jvm_iconst_1;
	vetorInstruc[0x05] = jvm_iconst_2;
	vetorInstruc[0x06] = jvm_iconst_3;
	vetorInstruc[0x07] = jvm_iconst_4;
	vetorInstruc[0x08] = jvm_iconst_5;
	vetorInstruc[0x09] = jvm_lconst_0;
	vetorInstruc[0x0a] = jvm_lconst_1;
	vetorInstruc[0x0b] = jvm_fconst_0;
	vetorInstruc[0x0c] = jvm_fconst_1;
	vetorInstruc[0x0d] = jvm_fconst_2;
	vetorInstruc[0x0e] = jvm_dconst_0;
	vetorInstruc[0x0f] = jvm_dconst_1;
	vetorInstruc[0x10] = jvm_bipush;
	vetorInstruc[0x11] = jvm_sipush;
	vetorInstruc[0x12] = jvm_ldc;
	vetorInstruc[0x13] = jvm_ldc_w;
	vetorInstruc[0x14] = jvm_ldc2_w;
	vetorInstruc[0x15] = jvm_iload;
	vetorInstruc[0x16] = jvm_lload;
	vetorInstruc[0x17] = jvm_fload;
	vetorInstruc[0x18] = jvm_dload;
	vetorInstruc[0x19] = jvm_aload;
	vetorInstruc[0x1a] = jvm_iload_0;
	vetorInstruc[0x1b] = jvm_iload_1;
	vetorInstruc[0x1c] = jvm_iload_2;
	vetorInstruc[0x1d] = jvm_iload_3;
	vetorInstruc[0x1e] = jvm_lload_0;
	vetorInstruc[0x1f] = jvm_lload_1;
	vetorInstruc[0x20] = jvm_lload_2;
	vetorInstruc[0x21] = jvm_lload_3;
	vetorInstruc[0x22] = jvm_fload_0;
	vetorInstruc[0x23] = jvm_fload_1;
	vetorInstruc[0x24] = jvm_fload_2;
	vetorInstruc[0x25] = jvm_fload_3;
	vetorInstruc[0x26] = jvm_dload_0;
	vetorInstruc[0x27] = jvm_dload_1;
	vetorInstruc[0x28] = jvm_dload_2;
	vetorInstruc[0x29] = jvm_dload_3;
	vetorInstruc[0x2a] = jvm_aload_0;
	vetorInstruc[0x2b] = jvm_aload_1;
	vetorInstruc[0x2c] = jvm_aload_2;
	vetorInstruc[0x2d] = jvm_aload_3;
	vetorInstruc[0x2e] = jvm_iaload;
	vetorInstruc[0x2f] = jvm_laload;
	vetorInstruc[0x30] = jvm_faload;
	vetorInstruc[0x31] = jvm_daload;
	vetorInstruc[0x32] = jvm_aaload;
	vetorInstruc[0x33] = jvm_baload;
	vetorInstruc[0x34] = jvm_caload;
	vetorInstruc[0x35] = jvm_saload;
	vetorInstruc[0x36] = jvm_istore;
	vetorInstruc[0x37] = jvm_lstore;
	vetorInstruc[0x38] = jvm_fstore;
	vetorInstruc[0x39] = jvm_dstore;
	vetorInstruc[0x3a] = jvm_astore;
	vetorInstruc[0x3b] = jvm_istore_0;
	vetorInstruc[0x3c] = jvm_istore_1;
	vetorInstruc[0x3d] = jvm_istore_2;
	vetorInstruc[0x3e] = jvm_istore_3;
	vetorInstruc[0x3f] = jvm_lstore_0;
	vetorInstruc[0x40] = jvm_lstore_1;
	vetorInstruc[0x41] = jvm_lstore_2;
	vetorInstruc[0x42] = jvm_lstore_3;
	vetorInstruc[0x43] = jvm_fstore_0;
	vetorInstruc[0x44] = jvm_fstore_1;
	vetorInstruc[0x45] = jvm_fstore_2;
	vetorInstruc[0x46] = jvm_fstore_3;
	vetorInstruc[0x47] = jvm_dstore_0;
	vetorInstruc[0x48] = jvm_dstore_1;
	vetorInstruc[0x49] = jvm_dstore_2;
	vetorInstruc[0x4a] = jvm_dstore_3;
	vetorInstruc[0x4b] = jvm_astore_0;
	vetorInstruc[0x4c] = jvm_astore_1;
	vetorInstruc[0x4d] = jvm_astore_2;
	vetorInstruc[0x4e] = jvm_astore_3;
	vetorInstruc[0x4f] = jvm_iastore;
	vetorInstruc[0x50] = jvm_lastore;
	vetorInstruc[0x51] = jvm_fastore;
	vetorInstruc[0x52] = jvm_dastore;
	vetorInstruc[0x53] = jvm_aastore;
	vetorInstruc[0x54] = jvm_bastore;
	vetorInstruc[0x55] = jvm_castore;
	vetorInstruc[0x56] = jvm_sastore;
	vetorInstruc[0x57] = jvm_pop;
	vetorInstruc[0x58] = jvm_pop2;
	vetorInstruc[0x59] = jvm_dup;
	vetorInstruc[0x5a] = jvm_dup_x1;
	vetorInstruc[0x5b] = jvm_dup_x2;
	vetorInstruc[0x5c] = jvm_dup2;
	vetorInstruc[0x5d] = jvm_dup2_x1;
	vetorInstruc[0x5e] = jvm_dup2_x2;
	vetorInstruc[0x5f] = jvm_swap;
	vetorInstruc[0x60] = jvm_iadd;
	vetorInstruc[0x61] = jvm_ladd;
	vetorInstruc[0x62] = jvm_fadd;
	vetorInstruc[0x63] = jvm_dadd;
	vetorInstruc[0x64] = jvm_isub;
	vetorInstruc[0x65] = jvm_lsub;
	vetorInstruc[0x66] = jvm_fsub;
	vetorInstruc[0x67] = jvm_dsub;
	vetorInstruc[0x68] = jvm_imul;
	vetorInstruc[0x69] = jvm_lmul;
	vetorInstruc[0x6a] = jvm_fmul;
	vetorInstruc[0x6b] = jvm_dmul;
	vetorInstruc[0x6c] = jvm_idiv;
	vetorInstruc[0x6d] = jvm_ldiv;
	vetorInstruc[0x6e] = jvm_fdiv;
	vetorInstruc[0x6f] = jvm_ddiv;
	vetorInstruc[0x70] = jvm_irem;
	vetorInstruc[0x71] = jvm_lrem;
	vetorInstruc[0x72] = jvm_frem;
	vetorInstruc[0x73] = jvm_drem;
	vetorInstruc[0x74] = jvm_ineg;
	vetorInstruc[0x75] = jvm_lneg;
	vetorInstruc[0x76] = jvm_fneg;
	vetorInstruc[0x77] = jvm_dneg;
	vetorInstruc[0x78] = jvm_ishl;
	vetorInstruc[0x79] = jvm_lshl;
	vetorInstruc[0x7a] = jvm_ishr;
	vetorInstruc[0x7b] = jvm_lshr;
	vetorInstruc[0x7c] = jvm_iushr;
	vetorInstruc[0x7d] = jvm_lushr;
	vetorInstruc[0x7e] = jvm_iand;
	vetorInstruc[0x7f] = jvm_land;
	vetorInstruc[0x80] = jvm_ior;
	vetorInstruc[0x81] = jvm_lor;
	vetorInstruc[0x82] = jvm_ixor;
	vetorInstruc[0x83] = jvm_lxor;
	vetorInstruc[0x84] = jvm_iinc;
	vetorInstruc[0x85] = jvm_i2l;
	vetorInstruc[0x86] = jvm_i2f;
	vetorInstruc[0x87] = jvm_i2d;
	vetorInstruc[0x88] = jvm_l2i;
	vetorInstruc[0x89] = jvm_l2f;
	vetorInstruc[0x8a] = jvm_l2d;
	vetorInstruc[0x8b] = jvm_f2i;
	vetorInstruc[0x8c] = jvm_f2l;
	vetorInstruc[0x8d] = jvm_f2d;
	vetorInstruc[0x8e] = jvm_d2i;
	vetorInstruc[0x8f] = jvm_d2l;
	vetorInstruc[0x90] = jvm_d2f;
	vetorInstruc[0x91] = jvm_i2b;
	vetorInstruc[0x92] = jvm_i2c;
	vetorInstruc[0x93] = jvm_i2s;
	vetorInstruc[0x94] = jvm_lcmp;
	vetorInstruc[0x95] = jvm_fcmpl;
	vetorInstruc[0x96] = jvm_fcmpg;
	vetorInstruc[0x97] = jvm_dcmpl;
	vetorInstruc[0x98] = jvm_dcmpg;
	vetorInstruc[0x99] = jvm_ifeq;
	vetorInstruc[0x9a] = jvm_ifne;
	vetorInstruc[0x9b] = jvm_iflt;
	vetorInstruc[0x9c] = jvm_ifge;
	vetorInstruc[0x9d] = jvm_ifgt;
	vetorInstruc[0x9e] = jvm_ifle;
	vetorInstruc[0x9f] = jvm_if_icmpeq;
	vetorInstruc[0xa0] = jvm_if_icmpne;
	vetorInstruc[0xa1] = jvm_if_icmplt;
	vetorInstruc[0xa2] = jvm_if_icmpge;
	vetorInstruc[0xa3] = jvm_if_icmpgt;
	vetorInstruc[0xa4] = jvm_if_icmple;
	vetorInstruc[0xa5] = jvm_if_acmpeq;
	vetorInstruc[0xa6] = jvm_if_acmpne;
	vetorInstruc[0xa7] = jvm_goto;
	vetorInstruc[0xa8] = jvm_jsr;
	vetorInstruc[0xa9] = jvm_ret;
	vetorInstruc[0xaa] = jvm_tableswitch;
	vetorInstruc[0xab] = jvm_lookupswitch;
	vetorInstruc[0xac] = jvm_ireturn;
	vetorInstruc[0xad] = jvm_lreturn;
	vetorInstruc[0xae] = jvm_freturn;
	vetorInstruc[0xaf] = jvm_dreturn;
	vetorInstruc[0xb0] = jvm_areturn;
	vetorInstruc[0xb1] = jvm_return;
	vetorInstruc[0xb2] = jvm_getstatic;
	vetorInstruc[0xb3] = jvm_putstatic;
	vetorInstruc[0xb4] = jvm_getfield;
	vetorInstruc[0xb5] = jvm_putfield;
	vetorInstruc[0xb6] = jvm_invokevirtual;
	vetorInstruc[0xb7] = jvm_invokespecial;
	vetorInstruc[0xb8] = jvm_invokestatic;
	vetorInstruc[0xb9] = jvm_invokeinterface;
	vetorInstruc[0xba] = jvm_invokedynamic;
	vetorInstruc[0xbb] = jvm_new;
	vetorInstruc[0xbc] = jvm_newarray;
	vetorInstruc[0xbd] = jvm_anewarray;
	vetorInstruc[0xbe] = jvm_arraylength;
	vetorInstruc[0xbf] = jvm_athrow;
	vetorInstruc[0xc0] = jvm_checkcast;
	vetorInstruc[0xc1] = jvm_instanceof;
	vetorInstruc[0xc2] = jvm_monitorenter;
	vetorInstruc[0xc3] = jvm_monitorexit;
	vetorInstruc[0xc4] = jvm_wide;
	vetorInstruc[0xc5] = jvm_multianewarray;
	vetorInstruc[0xc6] = jvm_ifnull;
	vetorInstruc[0xc7] = jvm_ifnonnull;
	vetorInstruc[0xc8] = jvm_goto_w;
	vetorInstruc[0xc9] = jvm_jsr_w;
}
