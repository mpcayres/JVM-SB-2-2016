#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "FuncoesAuxiliares.h"

u8 shift32To64(u4 low, u4 high) {
	u8 aux;
	
	aux = high;
	aux <<= 32;
	aux += low;
	
	return aux;
}

u4 shift8To32(u4 low, u4 high) {
	u4 aux;
	
	aux = high;
	aux <<= 8;
	aux |= low;
	
	return aux;
}

void shift64To32(u8 aux, u4 *low, u4 *high) {
	*high = aux >> 32;
	*low = aux & 0xffffffff;
}

double shiftCast32ToDouble(u4 low, u4 high) {
	double m, pot;
	int64_t bits, s, e, aux_high;
	int32_t i, j;
	
	aux_high = high;
	bits = (aux_high << 32) + low;
	
	s = ((bits >> 63) == 0) ? 1 : -1;
	e = ((bits >> 52) & 0x7ffL);
	for(m = 0, i = 1; i <= 52; i++) {
		if((bits >> (52 - i)) & 1)	{
			pot = 1;
			for(j = 1; j <= i; j++) pot = pot*2;
			m = m + (1.0 / pot);
		}
	}
	
	m = m + 1; pot = 1;
	if((e-1023) > 0) for(j = 1; j <= (e - 1023); j++) pot = pot*2;
	else for(j = 1; j <= -(e - 1023); j++) pot = pot/2;
	
	return s*m*pot;
}

void trocaCaracter(char *stringOriginal, char *subString, char *stringSubstituta) {
	char buffer[4096], *ch;
	
	if(!(ch = strstr(stringOriginal, subString))) return;
	
	strncpy(buffer, stringOriginal, ch-stringOriginal);
	buffer[ch-stringOriginal] = 0;
	
	sprintf(buffer+(ch - stringOriginal), "%s%s", stringSubstituta, ch + strlen(subString));
	stringOriginal[0] = 0;
	
	strcpy(stringOriginal, buffer);
	return trocaCaracter(stringOriginal, subString, stringSubstituta);
}

void carregaOpcodeInfo() {
	int32_t i;
	op_info = malloc(sizeof(opcode_informacao)*256);

	strcpy(op_info[0x00].info, "nop");
	strcpy(op_info[0x01].info, "aconst_null");
	strcpy(op_info[0x02].info, "iconst_m1");
	strcpy(op_info[0x03].info, "iconst_0");
	strcpy(op_info[0x04].info, "iconst_1");
	strcpy(op_info[0x05].info, "iconst_2");
	strcpy(op_info[0x06].info, "iconst_3");
	strcpy(op_info[0x07].info, "iconst_4");
	strcpy(op_info[0x08].info, "iconst_5");
	strcpy(op_info[0x09].info, "lconst_0");
	strcpy(op_info[0x0a].info, "lconst_1");
	strcpy(op_info[0x0b].info, "fconst_0");
	strcpy(op_info[0x0c].info, "fconst_1");
	strcpy(op_info[0x0d].info, "fconst_2");
	strcpy(op_info[0x0e].info, "dconst_0");
	strcpy(op_info[0x0f].info, "dconst_1");
	strcpy(op_info[0x10].info, "bipush");
	strcpy(op_info[0x11].info, "sipush");
	strcpy(op_info[0x12].info, "ldc");
	strcpy(op_info[0x13].info, "ldc_w");
	strcpy(op_info[0x14].info, "ldc2_w");
	strcpy(op_info[0x15].info, "iload");
	strcpy(op_info[0x16].info, "lload");
	strcpy(op_info[0x17].info, "fload");
	strcpy(op_info[0x18].info, "dload");
	strcpy(op_info[0x19].info, "aload");
	strcpy(op_info[0x1a].info, "iload_0");
	strcpy(op_info[0x1b].info, "iload_1");
	strcpy(op_info[0x1c].info, "iload_2");
	strcpy(op_info[0x1d].info, "iload_3");
	strcpy(op_info[0x1e].info, "lload_0");
	strcpy(op_info[0x1f].info, "lload_1");
	strcpy(op_info[0x20].info, "lload_2");
	strcpy(op_info[0x21].info, "lload_3");
	strcpy(op_info[0x22].info, "fload_0");
	strcpy(op_info[0x23].info, "fload_1");
	strcpy(op_info[0x24].info, "fload_2");
	strcpy(op_info[0x25].info, "fload_3");
	strcpy(op_info[0x26].info, "dload_0");
	strcpy(op_info[0x27].info, "dload_1");
	strcpy(op_info[0x28].info, "dload_2");
	strcpy(op_info[0x29].info, "dload_3");
	strcpy(op_info[0x2a].info, "aload_0");
	strcpy(op_info[0x2b].info, "aload_1");
	strcpy(op_info[0x2c].info, "aload_2");
	strcpy(op_info[0x2d].info, "aload_3");
	strcpy(op_info[0x2e].info, "iaload");
	strcpy(op_info[0x2f].info, "laload");
	strcpy(op_info[0x31].info, "daload");
	strcpy(op_info[0x32].info, "aaload");
	strcpy(op_info[0x33].info, "baload");
	strcpy(op_info[0x34].info, "caload");
	strcpy(op_info[0x35].info, "saload");
	strcpy(op_info[0x36].info, "istore");
	strcpy(op_info[0x37].info, "lstore");
	strcpy(op_info[0x38].info, "fstore");
	strcpy(op_info[0x39].info, "dstore");
	strcpy(op_info[0x3a].info, "astore");
	strcpy(op_info[0x3b].info, "istore_0");
	strcpy(op_info[0x3c].info, "istore_1");
	strcpy(op_info[0x3d].info, "istore_2");
	strcpy(op_info[0x3e].info, "istore_3");
	strcpy(op_info[0x3f].info, "lstore_0");
	strcpy(op_info[0x40].info, "lstore_1");
	strcpy(op_info[0x41].info, "lstore_2");
	strcpy(op_info[0x42].info, "lstore_3");
	strcpy(op_info[0x43].info, "fstore_0");
	strcpy(op_info[0x44].info, "fstore_1");
	strcpy(op_info[0x45].info, "fstore_2");
	strcpy(op_info[0x46].info, "fstore_3");
	strcpy(op_info[0x47].info, "dstore_0");
	strcpy(op_info[0x48].info, "dstore_1");
	strcpy(op_info[0x49].info, "dstore_2");
	strcpy(op_info[0x4a].info, "dstore_3");
	strcpy(op_info[0x4b].info, "astore_0");
	strcpy(op_info[0x4c].info, "astore_1");
	strcpy(op_info[0x4d].info, "astore_2");
	strcpy(op_info[0x4e].info, "astore_3");
	strcpy(op_info[0x4f].info, "iastore");
	strcpy(op_info[0x50].info, "lastore");
	strcpy(op_info[0x51].info, "fastore");
	strcpy(op_info[0x52].info, "dastore");
	strcpy(op_info[0x53].info, "aastore");
	strcpy(op_info[0x54].info, "bastore");
	strcpy(op_info[0x55].info, "castore");
	strcpy(op_info[0x56].info, "sastore");
	strcpy(op_info[0x57].info, "pop");
	strcpy(op_info[0x58].info, "pop2");
	strcpy(op_info[0x59].info, "dup");
	strcpy(op_info[0x5a].info, "dup_x1");
	strcpy(op_info[0x5b].info, "dup_x2");
	strcpy(op_info[0x5c].info, "dup2");
	strcpy(op_info[0x5d].info, "dup2_x1");
	strcpy(op_info[0x5e].info, "dup2_x2");
	strcpy(op_info[0x5f].info, "swap");
	strcpy(op_info[0x60].info, "iadd");
	strcpy(op_info[0x61].info, "ladd");
	strcpy(op_info[0x62].info, "fadd");
	strcpy(op_info[0x63].info, "dadd");
	strcpy(op_info[0x64].info, "isub");
	strcpy(op_info[0x65].info, "lsub");
	strcpy(op_info[0x66].info, "fsub");
	strcpy(op_info[0x67].info, "dsub");
	strcpy(op_info[0x68].info, "imul");
	strcpy(op_info[0x69].info, "lmul");
	strcpy(op_info[0x6a].info, "fmul");
	strcpy(op_info[0x6b].info, "dmul");
	strcpy(op_info[0x6c].info, "idiv");
	strcpy(op_info[0x6d].info, "ldiv");
	strcpy(op_info[0x6e].info, "fdiv");
	strcpy(op_info[0x6f].info, "ddiv");
	strcpy(op_info[0x70].info, "irem");
	strcpy(op_info[0x71].info, "lrem");
	strcpy(op_info[0x72].info, "frem");
	strcpy(op_info[0x73].info, "drem");
	strcpy(op_info[0x74].info, "ineg");
	strcpy(op_info[0x75].info, "lneg");
	strcpy(op_info[0x76].info, "fneg");
	strcpy(op_info[0x77].info, "dneg");
	strcpy(op_info[0x78].info, "ishl");
	strcpy(op_info[0x79].info, "lshl");
	strcpy(op_info[0x7a].info, "ishr");
	strcpy(op_info[0x7b].info, "lshr");
	strcpy(op_info[0x7c].info, "iushr");
	strcpy(op_info[0x7d].info, "lushr");
	strcpy(op_info[0x7e].info, "iand");
	strcpy(op_info[0x7f].info, "land");
	strcpy(op_info[0x80].info, "ior");
	strcpy(op_info[0x81].info, "lor");
	strcpy(op_info[0x82].info, "ixor");
	strcpy(op_info[0x83].info, "lxor");
	strcpy(op_info[0x84].info, "iinc");
	strcpy(op_info[0x85].info, "i2l");
	strcpy(op_info[0x86].info, "i2f");
	strcpy(op_info[0x87].info, "i2d");
	strcpy(op_info[0x88].info, "l2i");
	strcpy(op_info[0x89].info, "l2f");
	strcpy(op_info[0x8a].info, "l2d");
	strcpy(op_info[0x8b].info, "f2i");
	strcpy(op_info[0x8c].info, "f2l");
	strcpy(op_info[0x8d].info, "f2d");
	strcpy(op_info[0x8e].info, "d2i");
	strcpy(op_info[0x8f].info, "d2l");
	strcpy(op_info[0x90].info, "d2f");
	strcpy(op_info[0x91].info, "i2b");
	strcpy(op_info[0x92].info, "i2c");
	strcpy(op_info[0x93].info, "i2s");
	strcpy(op_info[0x94].info, "lcmp");
	strcpy(op_info[0x95].info, "fcmpl");
	strcpy(op_info[0x96].info, "fcmpg");
	strcpy(op_info[0x97].info, "dcmpl");
	strcpy(op_info[0x98].info, "dcmpg");
	strcpy(op_info[0x99].info, "ifeq");
	strcpy(op_info[0x9a].info, "ifne");
	strcpy(op_info[0x9b].info, "iflt");
	strcpy(op_info[0x9c].info, "ifge");
	strcpy(op_info[0x9d].info, "ifgt");
	strcpy(op_info[0x9e].info, "ifle");
	strcpy(op_info[0x9f].info, "if_icmpeq");
	strcpy(op_info[0xa0].info, "if_icmpne");
	strcpy(op_info[0xa1].info, "if_icmplt");
	strcpy(op_info[0xa2].info, "if_icmpge");
	strcpy(op_info[0xa3].info, "if_icmpgt");
	strcpy(op_info[0xa4].info, "if_icmple");
	strcpy(op_info[0xa5].info, "if_acmpeq");
	strcpy(op_info[0xa6].info, "if_acmpne");
	strcpy(op_info[0xa7].info, "goto");
	strcpy(op_info[0xa8].info, "jsr");
	strcpy(op_info[0xa9].info, "ret");
	strcpy(op_info[0xaa].info, "tableswitch");
	strcpy(op_info[0xab].info, "lookupswitch");
	strcpy(op_info[0xac].info, "ireturn");
	strcpy(op_info[0xad].info, "lreturn");
	strcpy(op_info[0xae].info, "freturn");
	strcpy(op_info[0xaf].info, "dreturn");
	strcpy(op_info[0xb0].info, "areturn");
	strcpy(op_info[0xb1].info, "return");
	strcpy(op_info[0xb2].info, "getstatic");
	strcpy(op_info[0xb3].info, "putstatic");
	strcpy(op_info[0xb4].info, "getfield");
	strcpy(op_info[0xb5].info, "putfield");
	strcpy(op_info[0xb6].info, "invokevirtual");
	strcpy(op_info[0xb7].info, "invokespecial");
	strcpy(op_info[0xb8].info, "invokestatic");
	strcpy(op_info[0xb9].info, "invokeinterface");
	strcpy(op_info[0xba].info, "invokedynamic");
	strcpy(op_info[0xbb].info, "new");
	strcpy(op_info[0xbc].info, "newarray");
	strcpy(op_info[0xbd].info, "anewarray");
	strcpy(op_info[0xbe].info, "arraylength");
	strcpy(op_info[0xbf].info, "athrow");
	strcpy(op_info[0xc0].info, "checkcast");
	strcpy(op_info[0xc1].info, "instanceof");
	strcpy(op_info[0xc2].info, "monitorenter");
	strcpy(op_info[0xc3].info, "monitorexit");
	strcpy(op_info[0xc4].info, "wide");
	strcpy(op_info[0xc5].info, "multianewarray");
	strcpy(op_info[0xc6].info, "ifnull");
	strcpy(op_info[0xc7].info, "ifnonnull");
	strcpy(op_info[0xc8].info, "goto_w");
	strcpy(op_info[0xc9].info, "jsr_w");

	for(i = 0x00; i <= 0xc9; i++) op_info[i].cont_op = 0;
	
	op_info[0x10].cont_op = 1;
	op_info[0x11].cont_op = 2;
	op_info[0x12].cont_op = 1;
	op_info[0x13].cont_op = 2;
	op_info[0x14].cont_op = 2;
	op_info[0x15].cont_op = 1;
	op_info[0x16].cont_op = 1;
	op_info[0x17].cont_op = 1;
	op_info[0x18].cont_op = 1;
	op_info[0x19].cont_op = 1;
	op_info[0x36].cont_op = 1;
	op_info[0x37].cont_op = 1;
	op_info[0x38].cont_op = 1;
	op_info[0x39].cont_op = 1;
	op_info[0x3a].cont_op = 1;
	op_info[0x84].cont_op = 2;
	op_info[0x99].cont_op = 2;
	op_info[0x9a].cont_op = 2;
	op_info[0x9b].cont_op = 2;
	op_info[0x9c].cont_op = 2;
	op_info[0x9d].cont_op = 2;
	op_info[0x9e].cont_op = 2;
	op_info[0x9f].cont_op = 2;
	op_info[0xa0].cont_op = 2;
	op_info[0xa1].cont_op = 2;
	op_info[0xa2].cont_op = 2;
	op_info[0xa3].cont_op = 2;
	op_info[0xa4].cont_op = 2;
	op_info[0xa5].cont_op = 2;
	op_info[0xa6].cont_op = 2;
	op_info[0xa7].cont_op = 2;
	op_info[0xa8].cont_op = 2;
	op_info[0xa9].cont_op = 1;
	op_info[0xaa].cont_op = 14;
	op_info[0xab].cont_op = 10;
	op_info[0xb2].cont_op = 2;
	op_info[0xb3].cont_op = 2;
	op_info[0xb4].cont_op = 2;
	op_info[0xb5].cont_op = 2;
	op_info[0xb6].cont_op = 2;
	op_info[0xb7].cont_op = 2;
	op_info[0xb8].cont_op = 2;
	op_info[0xb9].cont_op = 4;
	op_info[0xba].cont_op = 4;
	op_info[0xbb].cont_op = 2;
	op_info[0xbc].cont_op = 1;
	op_info[0xbd].cont_op = 2;
	op_info[0xc0].cont_op = 2;
	op_info[0xc1].cont_op = 2;
	op_info[0xc4].cont_op = 5;
	op_info[0xc5].cont_op = 3;
	op_info[0xc6].cont_op = 2;
	op_info[0xc7].cont_op = 2;
	op_info[0xc8].cont_op = 4;
	op_info[0xc9].cont_op = 4;

}
