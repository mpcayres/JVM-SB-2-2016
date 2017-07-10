#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#include "InstrucoesCat1.h"

extern struct frame *frame_corrente;

void jvm_aconst_null() {
	push(NULL_CONST);
	frame_corrente->pc++;
}

void jvm_iconst_m1() {
	push(-1);
	frame_corrente->pc++;
}

void jvm_iconst_0() {
	push(0);
	frame_corrente->pc++;
}

void jvm_iconst_1() {
	push(1);
	frame_corrente->pc++;
}

void jvm_iconst_2() {
	push(2);
	frame_corrente->pc++;
}

void jvm_iconst_3() {
	push(3);
	frame_corrente->pc++;
}

void jvm_iconst_4() {
	push(4);
	frame_corrente->pc++;
}

void jvm_iconst_5() {
	push(5);
	frame_corrente->pc++;
}

void jvm_fconst_0() {
	u4 *temp;
	float auxF = 0.0;
	temp = (u4*) malloc(sizeof(u4));
	memcpy(temp, &auxF, sizeof(u4));
	push(*temp);
	frame_corrente->pc++;
}

void jvm_fconst_1() {
	u4 *temp;
	float f = 1.0;
	
	temp = (u4*) malloc(sizeof(u4));
	memcpy(temp, &f, sizeof(u4));
	
	push(*temp);
	frame_corrente->pc++;
}

void jvm_fconst_2() {
	u4 *temp;
	float f = 2.0;
	
	temp = (u4*) malloc(sizeof(u4));
	memcpy(temp, &f, sizeof(u4));
	
	push(*temp);
	frame_corrente->pc++;
}

void jvm_bipush() {
	int8_t temp = (int8_t) frame_corrente->code[(++frame_corrente->pc)];
	push((u4) temp);
	frame_corrente->pc++;
}

void jvm_sipush() {
	u1 first, last;
	int16_t temp;
	
	frame_corrente->pc++;
	last = frame_corrente->code[frame_corrente->pc];
	
	frame_corrente->pc++;
	first = frame_corrente->code[frame_corrente->pc];
	
	temp = (int16_t) shift8To32(first, last);
	push((u4) temp);
	frame_corrente->pc++;
}

void jvm_iload_0() {
	push(frame_corrente->fields[0]);
	frame_corrente->pc++;
}

void jvm_iload_1() {
	push(frame_corrente->fields[1]);
	frame_corrente->pc++;
}

void jvm_iload_2() {
	push(frame_corrente->fields[2]);
	frame_corrente->pc++;
}

void jvm_iload_3() {
	push(frame_corrente->fields[3]);
	frame_corrente->pc++;
}

void jvm_fload_0() {
	push(frame_corrente->fields[0]);
	frame_corrente->pc++;
}

void jvm_fload_1() {
	push(frame_corrente->fields[1]);
	frame_corrente->pc++;
}

void jvm_fload_2() {
	push(frame_corrente->fields[2]);
	frame_corrente->pc++;
}

void jvm_fload_3() {
	push(frame_corrente->fields[3]);
	frame_corrente->pc++;
}

void jvm_aload_0() {
	push(frame_corrente->fields[0]);
	frame_corrente->pc++;
}

void jvm_aload_1() {
	push(frame_corrente->fields[1]);
	frame_corrente->pc++;
}

void jvm_aload_2() {
	push(frame_corrente->fields[2]);
	frame_corrente->pc++;
}

void jvm_aload_3() {
	push(frame_corrente->fields[3]);
	frame_corrente->pc++;
}

void jvm_iaload() {
	u4 indice;
	void *ref;
	
	indice = pop();
	ref = (void*) pop();
	push(((u4*)ref)[indice]);
	frame_corrente->pc++;
}

void jvm_faload() {
	u4 indice, res;
	void *ref;
	
	indice = pop();
	ref = (void*) pop();
	memcpy(&res, &((float*)ref)[indice], sizeof(u4));
	push(res);
	frame_corrente->pc++;
}

void jvm_aaload() {
	u4 indice;
	void *ref;
	
	indice = pop();
	ref = (void*) pop();
	push(((u4*)ref)[indice]);
	frame_corrente->pc++;
}

void jvm_baload() {
	u4 indice;
	void *ref;
	
	indice = pop();
	ref = (void*) pop();
	push((u4) (((u1*)ref)[indice]));
	frame_corrente->pc++;
}

void jvm_caload() {
	u4 indice;
	void *ref;
	
	indice = pop();
	ref = (void*) pop();
	push((u4) (((u2*)ref)[indice]));
	frame_corrente->pc++;
}

void jvm_saload() {
	u4 indice;
	void *ref;
	
	indice = pop();
	ref = (void *)pop();
	push((u4) (((u2*)ref)[indice]));
	frame_corrente->pc++;
}

void jvm_istore() {
	u2 indice;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];
	
	frame_corrente->fields[indice] = pop();
	frame_corrente->pc++;
}

void jvm_fstore() {
	u2 indice;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];

	frame_corrente->fields[indice] = pop();
	frame_corrente->pc++;
}

void jvm_astore() {
	u2 indice;

	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];

	frame_corrente->fields[indice] = pop();
	frame_corrente->pc++;
}

void jvm_istore_0() {
	frame_corrente->fields[0] = pop();
	frame_corrente->pc++;
}

void jvm_istore_1() {
	frame_corrente->fields[1] = pop();
	frame_corrente->pc++;
}

void jvm_istore_2() {
	frame_corrente->fields[2] = pop();
	frame_corrente->pc++;
}

void jvm_istore_3() {
	frame_corrente->fields[3] = pop();
	frame_corrente->pc++;
}

void jvm_fstore_0() {
	frame_corrente->fields[0] = pop();
	frame_corrente->pc++;
}

void jvm_fstore_1() {
	frame_corrente->fields[1] = pop();
	frame_corrente->pc++;
}

void jvm_fstore_2() {
	frame_corrente->fields[2] = pop();
	frame_corrente->pc++;
}

void jvm_fstore_3() {
	frame_corrente->fields[3] = pop();
	frame_corrente->pc++;
}

void jvm_astore_0() {
	frame_corrente->fields[0] = pop();
	frame_corrente->pc++;
}

void jvm_astore_1() {
	frame_corrente->fields[1] = pop();
	frame_corrente->pc++;
}

void jvm_astore_2() {
	frame_corrente->fields[2] = pop();
	frame_corrente->pc++;
}

void jvm_astore_3() {
	frame_corrente->fields[3] = pop();
	frame_corrente->pc++;
}

void jvm_iastore() {
	u4 indice, num;
	void *ref;
	
	num = pop();
	indice = pop();
	ref = (void*) pop();
	
	((u4*)ref)[indice] = num;
	frame_corrente->pc++;
}

void jvm_fastore() {
	u4 indice, num;
	void *ref;
	
	num = pop();
	indice = pop();
	ref = (void*) pop();
	
	((u4*)ref)[indice] = num;
	frame_corrente->pc++;
}

void jvm_aastore() {
	u4 indice, num;
	void *ref;
	
	num = pop();
	indice = pop();
	ref = (void*) pop();
	
	((u4*)ref)[indice] = num;
	frame_corrente->pc++;
}

void jvm_bastore() {
	u4 indice, num;
	void *ref;
	
	num = pop();
	indice = pop();
	ref = (void *)pop();
	
	((u1*)ref)[indice] = (u1) num;
	frame_corrente->pc++;
}

void jvm_castore() {
	u4 indice, num;
	void *ref;
	
	num = pop();
	indice = pop();
	ref = (void*) pop();
	
	((u2*)ref)[indice] = (u2) num;
	frame_corrente->pc++;
}

void jvm_sastore() {
	u4 indice, num;
	void *ref;
	
	num = pop();
	indice = pop();
	ref = (void*) pop();
	
	((u2*)ref)[indice] = (u2) num;
	frame_corrente->pc++;
}

void jvm_iadd() {
	u4 temp1, temp2;
	
	temp1 = pop();
	temp2 = pop();
	
	push(temp1 + temp2);
	frame_corrente->pc++;
}

void jvm_fadd() {
	float f1, f2;
	u4 temp1, temp2;
	
	temp1 = pop();
	memcpy(&f1, &temp1, sizeof(u4));
	
	temp2 = pop();
	memcpy(&f2, &temp2, sizeof(u4));
	
	f1 += f2;
	memcpy(&temp1, &f1, sizeof(u4));
	
	push(temp1);
	frame_corrente->pc++;
}

void jvm_isub() {
	u4 temp1, temp2;
	
	temp1 = pop();
	temp2 = pop();
	
	push(temp2 - temp1);
	frame_corrente->pc++;
}

void jvm_fsub() {
	u4 temp1, temp2, resulto;
	float num1, num2;
	
	temp2 = pop();
	temp1 = pop();
	
	memcpy(&num1, &temp1, sizeof(u4));
	memcpy(&num2, &temp2, sizeof(u4));
	
	num1 -= num2;
	memcpy(&resulto, &num1, sizeof(u4));
	
	push(resulto);
	frame_corrente->pc++;
}

void jvm_imul() {
	int32_t num1, num2;
	
	num1 = (int32_t) pop();
	num2 = (int32_t) pop();
	
	push((u4)(num1 * num2));
	frame_corrente->pc++;
}

void jvm_fmul() {
	u4 temp1, temp2, resulto;
	float num1, num2;
	
	temp1 = pop();
	temp2 = pop();
	
	memcpy(&num1, &temp1, sizeof(u4));
	memcpy(&num2, &temp2, sizeof(u4));
	
	num1 *= num2;
	memcpy(&resulto, &num1, sizeof(u4));
	
	push(resulto);
	frame_corrente->pc++;
}

void jvm_idiv() {
	int32_t num1, num2;
	
	num2 = (int32_t) pop();
	num1 = (int32_t) pop();
	
	push(num1/num2);
	frame_corrente->pc++;
}

void jvm_fdiv() {
	u4 temp1, temp2, resulto;
	float num1, num2;
	
	temp2 = pop();
	temp1 = pop();
	
	memcpy(&num1, &temp1, sizeof(u4));
	memcpy(&num2, &temp2, sizeof(u4));
	
	num1 /= num2;
	memcpy(&resulto, &num1, sizeof(u4));
	
	push(resulto);
	frame_corrente->pc++;
}

void jvm_irem() {
	u4 num1, num2;
	
	num2 = pop();
	num1 = pop();
	
	push(num1%num2);
	frame_corrente->pc++;
}

void jvm_frem() {
	float f1, f2;
	u4 temp1, temp2;
	
	temp1 = pop();
	memcpy(&f2, &temp1, sizeof(u4));
	
	temp2 = pop();
	memcpy(&f1, &temp2, sizeof(u4));
	
	f1 = fmodf(f1, f2);
	memcpy(&temp1, &f1, sizeof(u4));
	
	push(temp1);
	frame_corrente->pc++;
}

void jvm_ineg() {
	int32_t temp;
	
	temp = (int32_t) pop();
	
	temp = -temp;	
	push((u4) temp);
	frame_corrente->pc++;
}

void jvm_fneg() {
	u4 temp;
	float f;
	
	temp = pop();
	memcpy(&f, &temp, sizeof(u4));
	
	f = -f;
	memcpy(&temp, &f, sizeof(u4));
	
	push(temp);
	frame_corrente->pc++;
}

void jvm_ishl() {
	u4 mascara = 0x1f;
	u4 temp1, temp2;
	
	temp2 = pop();
	temp2 &= mascara;
	
	temp1 = pop();
	temp1 <<= temp2;
	
	push(temp1);
	frame_corrente->pc++;
}

void jvm_ishr() {
	u4 mascara = 0x1f;
	u4 temp1, i;
	int32_t temp2;
	
	temp1 = pop();
	temp1 &= mascara;
	
	temp2 = (int32_t) pop();
	for(i = 0; i < temp1; i++) temp2 /= 2;

	push((u4)temp2);
	frame_corrente->pc++;
}

void jvm_iushr() {
	u4 mascara = 0x1f;
	u4 temp1, temp2;
	
	temp2 = pop();
	temp2 &= mascara;
	
	temp1 = pop();
	temp1 >>= temp2;
	
	push(temp1);
	frame_corrente->pc++;
}

void jvm_iand() {
	u4 temp1, temp2;
	
	temp1 = pop();
	temp2 = pop();
	temp1 &= temp2;
	
	push(temp1);
	frame_corrente->pc++;
}

void jvm_ior() {
	u4 temp1, temp2;
	
	temp1 = pop();
	temp2 = pop();
	temp1 |= temp2;
	
	push(temp1);
	frame_corrente->pc++;
}

void jvm_ixor() {
	u4 temp1, temp2;
	
	temp1 = pop();
	temp2 = pop();
	temp1 ^= temp2;
	
	push(temp1);
	frame_corrente->pc++;
}

void jvm_iinc() {
	u1 field_index = frame_corrente->code[++(frame_corrente->pc)];
	u4 temp = frame_corrente->fields[field_index];
	u1 temp2 = frame_corrente->code[++(frame_corrente->pc)];
	int8_t indice = (int8_t) temp;
	int8_t constant = (int8_t) temp2;
	
	indice += constant;
	frame_corrente->fields[field_index] = (u4) indice;
	frame_corrente->pc++;
}

void jvm_i2l() {
	u4 mascara = 0x80000000;
	u8 extend = 0xffffffff00000000;
	u4 temp1, temp3;
	int64_t temp2;
	
	temp1 = pop();
	temp3 = temp1 & mascara;
	temp2 = (int64_t) temp1;
	
	if(temp3) temp2 |= extend;
	pushU8(temp2);
	frame_corrente->pc++;
}

void jvm_i2f() {
	u4 temp2;
	int32_t temp;
	float f;
	
	temp = (int32_t)pop();
	f = (float)temp;
	memcpy(&temp2, &f, sizeof(u4));
	
	push(temp2);
	frame_corrente->pc++;
}

void jvm_i2d() {
	double doubleNum;
	int32_t temp1;
	u8 temp2;
	
	temp1 = (int32_t)pop();
	doubleNum = (double)temp1;
	memcpy(&temp2, &doubleNum, sizeof(u8));
	
	pushU8(temp2);
	frame_corrente->pc++;
}

void jvm_f2i() {
	u4 temp;
	float f;
	
	temp = pop();
	memcpy(&f, &temp, sizeof(u4));
	
	temp = (u4) f;
	push(temp);
	frame_corrente->pc++;
}

void jvm_f2l() {
	u4 temp4;
	u8 temp8;
	float f;
	
	temp4 = pop();
	memcpy(&f, &temp4, sizeof(u4));
	temp8 = (u8) f;
	
	pushU8(temp8);
	frame_corrente->pc++;
}

void jvm_f2d() {
	u4 temp4;
	u8 temp8;
	float auxF;
	double doubleNum;
	
	temp4 = pop();
	memcpy(&auxF, &temp4, sizeof(u4));
	
	doubleNum = (double) auxF;
	memcpy(&temp8, &doubleNum, 2*sizeof(u4));
	
	pushU8(temp8);
	frame_corrente->pc++;
}

void jvm_i2b() {
	int8_t temp;
	int32_t temp2;
	
	temp = (int8_t) pop();
	temp2 = (int32_t)temp;
	
	push((u4)temp2);
	frame_corrente->pc++;
}

void jvm_i2c() {
	int16_t temp;
	int32_t temp2;
	
	temp = (int16_t) pop();
	temp2 = (int32_t)temp;
	
	push((u4) temp2);
	frame_corrente->pc++;
}

void jvm_i2s() {
	int16_t temp;
	int32_t temp2;
	
	temp = (int16_t) pop();
	temp2 = (int32_t)temp;
	
	push((u4) temp2);
	frame_corrente->pc++;
}

void jvm_fcmpl() {
	u4 temp;
	int32_t resultado;
	float auxF1, auxF2;
	
	temp = pop();
	memcpy(&auxF2, &temp, sizeof(u4));
	
	temp = pop();
	memcpy(&auxF1, &temp, sizeof(u4));
	
	if(auxF1 == auxF2) resultado = 0;
	else if(auxF1 > auxF2) resultado = 1;
	else resultado = -1;

	push((u4) resultado);
	frame_corrente->pc++;
}

void jvm_fcmpg() {
	float auxF1, auxF2;
	u4 temp;
	int32_t resultado;
	
	temp = pop();
	memcpy(&auxF2, &temp, sizeof(u4));
	
	temp = pop();
	memcpy(&auxF1, &temp, sizeof(u4));
	
	if(auxF1 == auxF2) resultado = 0;
	else if(auxF1 > auxF2) resultado = 1;
	else resultado = -1;
	
	push((u4) resultado);
	frame_corrente->pc++;
}
