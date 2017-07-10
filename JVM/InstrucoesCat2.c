#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#include "InstrucoesCat2.h"

extern struct frame *frame_corrente;

void jvm_lconst_0() {
	push(0); push(0);
	frame_corrente->pc++;
}

void jvm_lconst_1() {
	push(0); push(1);
	frame_corrente->pc++;
}

void jvm_dconst_0() {
	u4 temp4;
	u8 *temp8;
	double auxD = 0.0;
	
	temp8 = (u8*) malloc(sizeof(u8));
	memcpy(temp8, &auxD, 2*sizeof(u4));
	
	temp4 = *temp8 >> 32;
	push(temp4);
	
	temp4 = *temp8;
	push(temp4);
	frame_corrente->pc++;
}

void jvm_dconst_1() {
	u4 temp4;
	u8 *temp8;
	double auxD = 1.0;
	
	temp8 = (u8*) malloc(sizeof(u8));
	memcpy(temp8, &auxD, 2*sizeof(u4));
	
	temp4 = *temp8 >> 32;
	push(temp4);
	
	temp4 = *temp8;
	push(temp4);
	frame_corrente->pc++;
}

void jvm_ldc() {
	u1 indice, tag;
	u2 stringIndex;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];
	tag = frame_corrente->constantPool[indice-1].tag;
	
	switch(tag) {
		case(CPOOL_INTEGER):
			push(frame_corrente->constantPool[indice-1].type.Integer.bytes);
			break;
		case(CPOOL_FLOAT):
			push(frame_corrente->constantPool[indice-1].type.Float.bytes);
			break;
		case(CPOOL_STRING):
			stringIndex = frame_corrente->constantPool[indice-1].type.String.stringIndex;
			push((u4)getNome(frame_corrente->class, stringIndex));
			break;
	}
	
	frame_corrente->pc++;
}

void jvm_ldc_w() {
	u1 tag;
	u4 indice;
	u4 last, first;
	u2 stringIndex;

	frame_corrente->pc++;
	last = frame_corrente->code[frame_corrente->pc];
	
	frame_corrente->pc++;
	first = frame_corrente->code[frame_corrente->pc];
	
	indice = shift8To32(first, last);
	tag = frame_corrente->constantPool[indice-1].tag;

	switch(tag) {
		case(CPOOL_INTEGER):
			push(frame_corrente->constantPool[indice-1].type.Integer.bytes);
			break;
		case(CPOOL_FLOAT):
			push(frame_corrente->constantPool[indice-1].type.Float.bytes);
			break;
		case(CPOOL_STRING):
			stringIndex = frame_corrente->constantPool[indice-1].type.String.stringIndex;
			push((u4)getNome(frame_corrente->class, stringIndex));
			break;
	}
	
	frame_corrente->pc++;
}

void jvm_ldc2_w() {
	u1 tag;
	u4 indice;
	u4 last, first;

	frame_corrente->pc++;
	last = frame_corrente->code[frame_corrente->pc];
	
	frame_corrente->pc++;
	first = frame_corrente->code[frame_corrente->pc];
	
	indice = shift8To32(first, last);
	tag = (frame_corrente->constantPool[indice-1]).tag;

	switch(tag) {
		case(CPOOL_LONG):
			push(frame_corrente->constantPool[indice-1].type.Long.highBytes);
			push(frame_corrente->constantPool[indice-1].type.Long.lowBytes);
			break;
		case(CPOOL_DOUBLE):
			push(frame_corrente->constantPool[indice-1].type.Double.highBytes);
			push(frame_corrente->constantPool[indice-1].type.Double.lowBytes);
			break;
	}
	
	frame_corrente->pc++;
}

void jvm_lload_0() {
	push(frame_corrente->fields[0]);
	push(frame_corrente->fields[1]);
	frame_corrente->pc++;
}

void jvm_lload_1() {
	push(frame_corrente->fields[1]);
	push(frame_corrente->fields[2]);
	frame_corrente->pc++;
}

void jvm_lload_2() {
	push(frame_corrente->fields[2]);
	push(frame_corrente->fields[3]);
	frame_corrente->pc++;
}

void jvm_lload_3() {
	push(frame_corrente->fields[3]);
	push(frame_corrente->fields[4]);
	frame_corrente->pc++;
}

void jvm_dload_0() {
	push(frame_corrente->fields[0]);
	push(frame_corrente->fields[1]);
	frame_corrente->pc++;
}

void jvm_dload_1() {
	push(frame_corrente->fields[1]);
	push(frame_corrente->fields[2]);
	frame_corrente->pc++;
}

void jvm_dload_2() {
	push(frame_corrente->fields[2]);
	push(frame_corrente->fields[3]);
	frame_corrente->pc++;
}

void jvm_dload_3() {
	push(frame_corrente->fields[3]);
	push(frame_corrente->fields[4]);
	frame_corrente->pc++;
}

void jvm_laload() {
	u4 indice;
	void *ref;
	
	indice = pop();
	ref = (void*) pop();
	pushU8(((u8*)ref)[indice]);
	frame_corrente->pc++;
}

void jvm_daload() {
	u4 indice;
	void *ref;
	
	indice = pop();
	ref = (void*) pop();
	pushU8(((u8*)ref)[indice]);
	frame_corrente->pc++;
}

void jvm_lstore() {
	u2 indice;
	u4 last, first;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];
	
	first = pop(); last = pop();
	
	frame_corrente->fields[indice] = last;
	frame_corrente->fields[indice + 1] = first;
	frame_corrente->pc++;
}

void jvm_dstore() {
	u2 indice;
	u4 last, first;
	
	frame_corrente->pc++;
	indice = frame_corrente->code[frame_corrente->pc];
	
	first = pop(); last = pop();
	
	frame_corrente->fields[indice] = first;
	frame_corrente->fields[indice + 1] = last;
	frame_corrente->pc++;
}

void jvm_lstore_0() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[0] = last;
	frame_corrente->fields[1] = first;
	frame_corrente->pc++;
}

void jvm_lstore_1() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[1] = last;
	frame_corrente->fields[2] = first;
	frame_corrente->pc++;
}

void jvm_lstore_2() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[2] = last;
	frame_corrente->fields[3] = first;
	frame_corrente->pc++;
}

void jvm_lstore_3() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[3] = last;
	frame_corrente->fields[4] = first;
	frame_corrente->pc++;
}

void jvm_dstore_0() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[0] = first;
	frame_corrente->fields[1] = last;
	frame_corrente->pc++;
}

void jvm_dstore_1() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[1] = first;
	frame_corrente->fields[2] = last;
	frame_corrente->pc++;
}

void jvm_dstore_2() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[2] = first;
	frame_corrente->fields[3] = last;
	frame_corrente->pc++;
}

void jvm_dstore_3() {
	u4 last, first;
	
	first = pop(); last = pop();
	
	frame_corrente->fields[3] = first;
	frame_corrente->fields[4] = last;
	frame_corrente->pc++;
}

void jvm_lastore() {
	u4 indice, first, last;
	u8 num;
	void *ref;
	
	first = pop(); last = pop();
	num = shift32To64(first, last);
	
	indice = pop();
	ref = (void *)pop();
	((u8 *)ref)[indice] = num;
	frame_corrente->pc++;
}

void jvm_dastore() {
	u4 indice, first, last;
	u8 num;
	void *ref;
	
	first = pop(); last = pop();
	num = shift32To64(first, last);
	
	indice = pop();
	ref = (void *)pop();
	((u8 *)ref)[indice] = num;
	frame_corrente->pc++;
}

void jvm_ladd() {
	int64_t temp1, temp2;
	u4 first, last;
	
	first = pop(); last = pop();
	temp1 = shift32To64(first, last);
	
	first = pop(); last = pop();
	temp2 = shift32To64(first, last);
	
	pushU8(temp1 + temp2);
	frame_corrente->pc++;
}

void jvm_dadd() {
	double temp1, temp2;
	u4 last, first;
	u8 temp;
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&temp1, &temp, sizeof(u8));
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&temp2, &temp, sizeof(u8));
	
	temp1 += temp2;
	memcpy(&temp, &temp1, sizeof(u8));
	shift64To32(temp, &first, &last);
	
	push(last); push(first);
	frame_corrente->pc++;
}

void jvm_lsub() {
	int64_t temp1, temp2;
	u4 first, last;
	
	first = pop(); last = pop();
	temp1 = (signed) shift32To64(first, last);
	
	first = pop(); last = pop();
	temp2 = (signed) shift32To64(first, last);
	
	pushU8(temp2 - temp1);
	frame_corrente->pc++;
}

void jvm_dsub() {
	u4 last1, first1, last2, first2;
	double num1, num2;
	u8 resulto;
	
	first2 = pop(); last2 = pop();
	first1 = pop(); last1 = pop();
	
	num1 = shiftCast32ToDouble(first1, last1);
	num2 = shiftCast32ToDouble(first2, last2);
	num1 -= num2;
	memcpy(&resulto, &num1, sizeof(u8));
	
	pushU8(resulto);
	frame_corrente->pc++;
}

void jvm_lmul() {
	int64_t num1, num2, resulto;
	u4 last1, first1, last2, first2;
	
	first1 = pop(); last1 = pop();
	first2 = pop(); last2 = pop();
	
	num1 = (int64_t)shift32To64(first1, last1);
	num2 = (int64_t)shift32To64(first2, last2);
	resulto = num1 * num2;
	
	pushU8(((u8)resulto));
	frame_corrente->pc++;
}

void jvm_dmul() {
	u4 last1, first1, last2, first2;
	u8 num;
	double num1, num2;
	
	first1 = pop(); last1 = pop();
	first2 = pop(); last2 = pop();
	
	num1 = shiftCast32ToDouble(first1, last1);
	num2 = shiftCast32ToDouble(first2, last2);
	num1 *= num2;
	memcpy(&num, &num1, sizeof(u8));
	
	pushU8(num);
	frame_corrente->pc++;
}

void jvm_ldiv() {
	int64_t num1, num2;
	u4 last1, first1, last2, first2;
	
	first2 = pop(); last2 = pop();
	first1 = pop(); last1 = pop();
	
	num1 = (int64_t) shift32To64(first1, last1);
	num2 = (int64_t) shift32To64(first2, last2);
	
	pushU8(num1/num2);
	frame_corrente->pc++;
}

void jvm_ddiv() {
	u4 last1, first1, last2, first2;
	u8 temp;
	double num1, num2;
	
	first2 = pop(); last2 = pop();
	first1 = pop(); last1 = pop();
	
	num1 = shiftCast32ToDouble(first1, last1);
	num2 = shiftCast32ToDouble(first2, last2);
	num1 /= num2;
	memcpy(&temp, &num1, sizeof(u8));
	
	pushU8(temp);
	frame_corrente->pc++;
}

void jvm_lrem() {
	int64_t temp1, temp2;
	u4 first, last;
	
	first = pop(); last = pop();
	temp2 = (signed) shift32To64(first, last);
	
	first = pop(); last = pop();
	temp1 = (signed) shift32To64(first, last);
	temp1 %= temp2;
	
	push((u8) temp1);
	frame_corrente->pc++;
}

void jvm_drem() {
	double d1, d2;
	u8 temp;
	u4 first, last;

	first = pop(); last = pop();
	temp = shift32To64(first, last);	
	memcpy(&d2, &temp, sizeof(u8));
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&d1, &temp, sizeof(u8));
	
	d1 = fmod(d1, d2);
	memcpy(&temp, &d1, sizeof(u8));
	
	pushU8(temp);
	frame_corrente->pc++;
}

void jvm_lneg() {
	int64_t temp;
	u4 first, last;
	
	first = pop(); last = pop();
	temp = (int64_t) shift32To64(first, last);
	temp = -temp;
	
	pushU8((u8)temp);
	frame_corrente->pc++;
}

void jvm_dneg() {
	double d;
	u8 temp;
	u4 first, last;
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&d, &temp, sizeof(u8));
	
	d = -d;
	memcpy(&temp, &d, sizeof(u8));
	
	pushU8(temp);
	frame_corrente->pc++;
}

void jvm_lshl() {
	int64_t temp1;
	u4 mask = 0x3f, first, last, temp2;
	
	temp2 = pop();
	temp2 &= mask;
	
	first = pop(); last = pop();
	temp1 = (signed) shift32To64(first, last);
	temp1 <<= temp2;
	
	push((u8) temp1);
	frame_corrente->pc++;
}

void jvm_lshr() {
	u4 mask = 0x3f, temp2, first, last;
	u8 temp1 = 0xffffffffffffffff, temp4 = 0x8000000000000000;
	int64_t temp3;
	
	temp2 = pop();
	temp2 &= mask;

	temp1 <<= (64-temp2);
	first = pop(); last = pop();
	temp3 = (signed) shift32To64(first, last);

	temp4 = temp3 & temp4;
	temp3 >>= temp2;
	if(temp4) temp3 |= temp1;
	
	push((u8)temp3);
	frame_corrente->pc++;
}

void jvm_lushr() {
	int64_t temp1;
	u4 mask = 0x3f;
	u4 temp2;
	u4 first, last;
	
	temp2 = pop();
	temp2 &= mask;
	
	first = pop();last = pop();
	temp1 = (signed) shift32To64(first, last);
	temp1 >>= temp2;
	
	pushU8((u8) temp1);
	frame_corrente->pc++;
}

void jvm_land() {
	u8 temp1, temp2;
	u4 first, last;
	
	first = pop(); last = pop();
	temp1 = shift32To64(first, last);
	
	first = pop(); last = pop();
	temp2 = shift32To64(first, last);
	temp1 &= temp2;
	
	pushU8(temp1);
	frame_corrente->pc++;
}

void jvm_lor() {
	u8 temp1, temp2;
	u4 first, last;
	
	first = pop(); last = pop();
	temp1 = shift32To64(first, last);
	
	first = pop(); last = pop();
	temp2 = shift32To64(first, last);
	temp1 |= temp2;
	
	pushU8(temp1);
	frame_corrente->pc++;
}

void jvm_lxor() {
	u8 temp1, temp2;
	u4 first, last;
	
	first = pop(); last = pop();
	temp1 = shift32To64(first, last);
	
	first = pop(); last = pop();
	temp2 = shift32To64(first, last);
	temp1 ^= temp2;
	
	pushU8(temp1);
	frame_corrente->pc++;
}

void jvm_l2i() {
	u4 first, last;
	
	first = pop(); last = pop();
	
	push(first);
	frame_corrente->pc++;
}

void jvm_l2f() {
	u4 first, last, *temp;
	float auxF;
	
	first = pop(); last = pop();
	auxF = (float) shiftCast32ToDouble(first, last);
	
	temp = (u4*) malloc(sizeof(u4));
	memcpy(temp, &auxF, sizeof(u4));
	
	push(*temp);
	frame_corrente->pc++;
}

void jvm_l2d() {
	u8 *temp8;
	u4 first, last, temp4;
	double auxD;
	
	first = pop(); last = pop();
	auxD =  shiftCast32ToDouble(first, last);
	
	temp8 = (u8*) malloc(sizeof(u8));
	memcpy(temp8, &auxD, 2*sizeof(u4));
	temp4 = *temp8 >> 32;
	
	push(temp4);
	temp4 = *temp8;
	
	push(temp4);
	frame_corrente->pc++;
}

void jvm_d2i() {
	u8 temp;
	u4 first, last;
	int32_t resp;
	double auxD;
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	
	memcpy(&auxD, &temp, 2*sizeof(u4));
	resp = (int32_t) auxD;
	
	push((u4)resp);
	frame_corrente->pc++;
}

void jvm_d2l() {
	u8 temp;
	u4 first, last;
	double auxD;
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	
	memcpy(&auxD, &temp, 2*sizeof(u4));
	temp = (u8) auxD;
	
	push(temp);
	frame_corrente->pc++;
}

void jvm_d2f() {
	u8 temp;
	u4 first, last, resp;
	double d;
	float f;
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&d, &temp, 2*sizeof(u4));
	
	f = (float) d;
	memcpy(&resp, &f, sizeof(u4));
	
	push(resp);
	frame_corrente->pc++;
}

void jvm_lcmp() {
	int32_t resp;
	u4 first, last;
	u8 temp1, temp2;
	
	first = pop(); last = pop();
	temp2 = shift32To64(first, last);
	
	first = pop(); last = pop();
	temp1 = shift32To64(first, last);
	
	if(temp1 == temp2) resp = 0;
	else if(temp1 > temp2) resp = 1;
	else resp = -1;
	
	push((u4) resp);
	frame_corrente->pc++;
}

void jvm_dcmpl() {
	u8 temp;
	u4 first, last;
	double auxD1, auxD2;
	int32_t resultado;
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&auxD2, &temp, 2*sizeof(u4));
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&auxD1, &temp, 2*sizeof(u4));
	
	if(auxD1 == auxD2) resultado = 0;
	else if(auxD1 > auxD2) resultado = 1;
	else resultado = -1;
	
	push((u4) resultado);
	frame_corrente->pc++;
}

void jvm_dcmpg() {
	u8 temp;
	u4 first, last;
	double auxD1, auxD2;
	int32_t resultado;
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&auxD2, &temp, 2*sizeof(u4));
	
	first = pop(); last = pop();
	temp = shift32To64(first, last);
	memcpy(&auxD1, &temp, 2*sizeof(u4));
	
	if(auxD1 == auxD2) resultado = 0;
	else if(auxD1 > auxD2) resultado = 1;
	else resultado = -1;
	
	push((u4) resultado);
	frame_corrente->pc++;
}
