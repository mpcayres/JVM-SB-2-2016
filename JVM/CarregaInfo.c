#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "CarregaInfo.h"

u1 u1Leitura(FILE *fpClass) {
	u1 byte;
	
    if(fread(&byte, sizeof(u1), 1, fpClass) < 0) {
		printf("\nErro: leitura do byte com incompatibilidade.\n");
		return EXIT_FAILURE;
	}

    return byte;
}

u2 u2Leitura(FILE *fpClass) {
	u1 byte1, byte2;

	if((fread(&byte1, sizeof(u1), 1, fpClass)) < 0 || 
		(fread(&byte2, sizeof(u1), 1, fpClass)) < 0) {
		printf("\nErro: leitura do byte com incompatibilidade.\n");
		return EXIT_FAILURE;
	}

    return ((byte1 << 8) | byte2);
}

u4 u4Leitura(FILE *fpClass) {
	u1 byte1, byte2, byte3, byte4;

    if((fread(&byte1, sizeof(u1), 1, fpClass)) < 0 || 
		(fread(&byte2, sizeof(u1), 1, fpClass)) < 0 || 
		(fread(&byte3, sizeof(u1), 1, fpClass)) < 0 || 
		(fread(&byte4, sizeof(u1), 1, fpClass)) < 0) {
		printf("\nErro: leitura do byte com incompatibilidade.\n");
		return EXIT_FAILURE;
	}

    return ((byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4);
}

int32_t verificaNumMagic(FILE *fpClass) {
    cs->magicNumber = u4Leitura(fpClass);
    
    if(cs->magicNumber == 0xCAFEBABE) return TRUE;
    return FALSE;
}

int32_t verificaVersao() {
    if(cs->majorVersion <= 0x2E) return TRUE;
    return FALSE;
}

void armazenaVersoes(FILE *fpClass) {
    cs->minorVersion = u2Leitura(fpClass);
    cs->majorVersion = u2Leitura(fpClass);
}

void armazenaConstantPool(FILE *fpClass) {
    int32_t i, j;

    cs->constantPoolCount = u2Leitura(fpClass);
    cs->constantPool = malloc(sizeof(cpInfo)*(cs->constantPoolCount - 1));

    for(i = 0; i < (cs->constantPoolCount - 1); i++) {
    	
        cpInfo cpi, cpi2;
        cpi.tag = u1Leitura(fpClass);
        
        switch(cpi.tag) {
            case CPOOL_UTF8:
                cpi.type.Utf8.length = u2Leitura(fpClass);
                cpi.type.Utf8.bytes = malloc(sizeof(u1)*(cpi.type.Utf8.length + 1));
                for(j = 0; j < cpi.type.Utf8.length; j++)
                    cpi.type.Utf8.bytes[j] = u1Leitura(fpClass);
                cpi.type.Utf8.bytes[j] = '\0';
                break;
            case CPOOL_INTEGER:
                cpi.type.Integer.bytes = u4Leitura(fpClass);
                break;
            case CPOOL_FLOAT:
                cpi.type.Float.bytes = u4Leitura(fpClass);
                break;
            case CPOOL_LONG:
                cpi.type.Long.highBytes = u4Leitura(fpClass);
                cpi.type.Long.lowBytes = u4Leitura(fpClass);
                break;
            case CPOOL_DOUBLE:
                cpi.type.Double.highBytes = u4Leitura(fpClass);
                cpi.type.Double.lowBytes = u4Leitura(fpClass);
                break;
            case CPOOL_CLASS:
                cpi.type.Class.nameIndex = u2Leitura(fpClass);
                break;
            case CPOOL_STRING:
                cpi.type.String.stringIndex = u2Leitura(fpClass);
                break;
            case CPOOL_FIELD:
                cpi.type.FieldRef.classIndex = u2Leitura(fpClass);
                cpi.type.FieldRef.nameTypeIndex = u2Leitura(fpClass);
                break;
            case CPOOL_METHOD:
                cpi.type.MethodRef.classIndex = u2Leitura(fpClass);
                cpi.type.MethodRef.nameTypeIndex = u2Leitura(fpClass);
                break;
            case CPOOL_INTERFACE:
                cpi.type.InterfaceMethodRef.classIndex = u2Leitura(fpClass);
                cpi.type.InterfaceMethodRef.nameTypeIndex = u2Leitura(fpClass);
                break;
            case CPOOL_NAMETYPE:
                cpi.type.NameType.nameIndex = u2Leitura(fpClass);
                cpi.type.NameType.descriptorIndex = u2Leitura(fpClass);
                break;
            default:
                break;
        }
        
        cs->constantPool[i] = cpi;
        if(cpi.tag == CPOOL_LONG || cpi.tag == CPOOL_DOUBLE) {
            cpi2.tag = 0;
            sprintf(cpi2.type.Continued.bytes, "(large numeric continued)");
            cs->constantPool[++i] = cpi2;
        }
        
    }
    
}

void armazenaAccessFlags(FILE *fpClass) {
    cs->accessFlags = u2Leitura(fpClass);
}

void armazenaClasses(FILE *fpClass) {
    cs->thisClass = u2Leitura(fpClass);
    cs->superClass = u2Leitura(fpClass);
}

void armazenaInterfaces(FILE *fpClass) {
    int32_t i;

    cs->interfaceCount = u2Leitura(fpClass);
    cs->interfaces = malloc(sizeof(u2)*(cs->interfaceCount));

    for(i = 0; i < cs->interfaceCount; i++)
        cs->interfaces[i] = u2Leitura(fpClass);
        
}

void armazenaCampos(FILE *fpClass) {
    int32_t i, j;

    cs->fieldCount = u2Leitura(fpClass);
    cs->fields = malloc(sizeof(fieldInfo)*(cs->fieldCount));

    for(i = 0; i < cs->fieldCount; i++) {
        fieldInfo field;
        
        field.accessFlags = u2Leitura(fpClass);
        field.nameIndex = u2Leitura(fpClass);
        field.descriptorIndex = u2Leitura(fpClass);
        field.attributeCount = u2Leitura(fpClass);
        
        field.attributes = malloc(sizeof(attributeInfo)*(field.attributeCount));
        for(j = 0; j < field.attributeCount; j++)
            armazenaAtributoUnico(fpClass, &(field.attributes[j]));
        cs->fields[i] = field;
    }
    
}

void armazenaMetodos(FILE *fpClass) {
    int32_t i, j;

    cs->methodCount = u2Leitura(fpClass);
    cs->methods = malloc(sizeof(methodInfo)*(cs->methodCount));

    for(i = 0; i < cs->methodCount; i++) {
        methodInfo met;
        
        met.accessFlags = u2Leitura(fpClass);
        met.nameIndex = u2Leitura(fpClass);
        met.descriptorIndex = u2Leitura(fpClass);
        met.attributeCount = u2Leitura(fpClass);
        
        met.attributes = malloc(sizeof(attributeInfo)*(met.attributeCount));
        for(j = 0; j < met.attributeCount; j++)
            armazenaAtributoUnico(fpClass, &(met.attributes[j]));
        cs->methods[i] = met;
    }
    
}

void armazenaAtributos(FILE *fpClass) {
    int32_t i;

    cs->attributeCount = u2Leitura(fpClass);
    
    cs->attributes = malloc(sizeof(attributeInfo)*(cs->attributeCount));
    for(i = 0; i < cs->attributeCount; i++)
        armazenaAtributoUnico(fpClass, &(cs->attributes[i]));
        
}

void armazenaAtributoUnico(FILE *fpClass, attributeInfo *atrib) {
    char *attType;

    atrib->attributeNameIndex = u2Leitura(fpClass);
    atrib->attributeLength = u4Leitura(fpClass);

    attType = malloc(sizeof(char)*(cs->constantPool[atrib->attributeNameIndex - 1].type.Utf8.length));
    strcpy(attType, (char*) cs->constantPool[atrib->attributeNameIndex - 1].type.Utf8.bytes);
    
    if(strcmp(attType, "ConstantValue") == 0) armazenaAtrConst(fpClass, atrib);
    else if(strcmp(attType, "Code") == 0) armazenaAtrCode(fpClass, atrib);
    else if(strcmp(attType, "Exceptions") == 0) armazenaAtrExc(fpClass, atrib);
    else if(strcmp(attType, "InnerClasses") == 0) armazenaAtrInnerClass(fpClass, atrib);
    else if(strcmp(attType, "Synthetic") == 0) armazenaAtrSynthetic(fpClass, atrib);
	else if(strcmp(attType, "Deprecated") == 0) armazenaAtrDeprec(fpClass, atrib);
	else if(strcmp(attType, "LineNumberTable") == 0) armazenaAtrLineNumTable(fpClass, atrib);
	else if(strcmp(attType, "LocalVariableTable") == 0) armazenaAtrLocalVarTable(fpClass, atrib);
	else if(strcmp(attType, "SourceFile") == 0) armazenaAtrSourceFile(fpClass, atrib);
    else armazenaAtrDefault(fpClass, atrib);
}

void armazenaAtrConst(FILE *fpClass, attributeInfo *atrib) {
	atrib->tag = ATTRIBUTE_CONSTANT_VALUE;
    atrib->type.ConstantValue.constantValueIndex = u2Leitura(fpClass);
}

void armazenaAtrCode(FILE *fpClass, attributeInfo *atrib) {
    int32_t i;

	atrib->tag = ATTRIBUTE_CODE;
    atrib->type.Code.maxStack = u2Leitura(fpClass);
    atrib->type.Code.maxLocals = u2Leitura(fpClass);
    atrib->type.Code.codeLength = u4Leitura(fpClass);
    
    atrib->type.Code.code = malloc(sizeof(u1)*(atrib->type.Code.codeLength));
    for(i = 0; i < atrib->type.Code.codeLength; i++)
        atrib->type.Code.code[i] = u1Leitura(fpClass);
        
    atrib->type.Code.exceptionTableLength = u2Leitura(fpClass);
    
    atrib->type.Code.exceptionTable = 
		malloc(sizeof(exceptionTableType)*(atrib->type.Code.exceptionTableLength));
    for(i = 0; i < atrib->type.Code.exceptionTableLength; i++) {
        atrib->type.Code.exceptionTable[i].startPc = u2Leitura(fpClass);
        atrib->type.Code.exceptionTable[i].endPc = u2Leitura(fpClass);
        atrib->type.Code.exceptionTable[i].handlerPc = u2Leitura(fpClass);
        atrib->type.Code.exceptionTable[i].catchType = u2Leitura(fpClass);
    }
    
    atrib->type.Code.attributeCount = u2Leitura(fpClass);
    
    atrib->type.Code.attributes = 
		malloc(sizeof(attributeInfo)*(atrib->type.Code.attributeCount));
    for(i = 0; i < atrib->type.Code.attributeCount; i++)
        armazenaAtributoUnico(fpClass, &(atrib->type.Code.attributes[i]));
    
}

void armazenaAtrExc(FILE *fpClass, attributeInfo *atrib) {
    int32_t i;

	atrib->tag = ATTRIBUTE_EXCEPTIONS;
    atrib->type.Exceptions.numberOfExceptions = u2Leitura(fpClass);
    
    atrib->type.Exceptions.exceptionIndexTable = 
		malloc(sizeof(u2)*(atrib->type.Exceptions.numberOfExceptions));
    for(i = 0; i < atrib->type.Exceptions.numberOfExceptions; i++)
        atrib->type.Exceptions.exceptionIndexTable[i] = u2Leitura(fpClass);
        
}

void armazenaAtrInnerClass(FILE *fpClass, attributeInfo *atrib) {
    int32_t i;

	atrib->tag = ATTRIBUTE_INNER_CLASSES;
    atrib->type.InnerClasses.numberOfClasses = u2Leitura(fpClass);
    
    atrib->type.InnerClasses.classes = 
		malloc(sizeof(classType)*(atrib->type.InnerClasses.numberOfClasses));
    for(i = 0; i < atrib->type.InnerClasses.numberOfClasses; i++) {
        atrib->type.InnerClasses.classes[i].innerClassInfoIndex = u2Leitura(fpClass);
        atrib->type.InnerClasses.classes[i].outerClassInfoIndex = u2Leitura(fpClass);
        atrib->type.InnerClasses.classes[i].innerNameIndex = u2Leitura(fpClass);
        atrib->type.InnerClasses.classes[i].innerClassAccessFlags = u2Leitura(fpClass);
    }
    
}

void armazenaAtrSynthetic(FILE *fpClass, attributeInfo *atrib) {
	printf("\nErro: o programa não trabalha com atributos sinteticos.\n");
}

void armazenaAtrDefault(FILE *fpClass, attributeInfo *atrib) {
    int32_t i;

    atrib->type.Default.info = malloc(sizeof(u1)*(atrib->attributeLength));
    for(i = 0; i < atrib->attributeLength; i++)
        atrib->type.Default.info[i] = u1Leitura(fpClass);
        
}

void armazenaAtrDeprec(FILE *fpClass, attributeInfo *atrib) {
	atrib->tag = ATTRIBUTE_DEPRECATED;
}

void armazenaAtrLineNumTable(FILE *fpClass, attributeInfo *atrib) {
	int32_t i;

	atrib->tag = ATTRIBUTE_LINE_NUMBER_TABLE;
	atrib->type.LineNumberTable.lineNumberTableLength = u2Leitura(fpClass);
	
	atrib->type.LineNumberTable.lineNumberTable = 
		malloc(sizeof(LineNumberTableType)*(atrib->type.LineNumberTable.lineNumberTableLength));
	for(i = 0; i < atrib->type.LineNumberTable.lineNumberTableLength; i++) {
		atrib->type.LineNumberTable.lineNumberTable[i].startPc = u2Leitura(fpClass);
		atrib->type.LineNumberTable.lineNumberTable[i].lineNumber = u2Leitura(fpClass);
	}
	
}

void armazenaAtrLocalVarTable(FILE *fpClass, attributeInfo *atrib) {
	int32_t i;

	atrib->tag = ATTRIBUTE_LOCAL_VARIABLE_TABLE;
	atrib->type.LocalVariableTable.localVariableTableLength = u2Leitura(fpClass);
	
	atrib->type.LocalVariableTable.localVariableTable = 
		malloc(sizeof(LocalVariableTableType)*(atrib->type.LocalVariableTable.localVariableTableLength));
	for(i = 0; i < atrib->type.LocalVariableTable.localVariableTableLength; i++) {
		atrib->type.LocalVariableTable.localVariableTable[i].startPc = u2Leitura(fpClass);
		atrib->type.LocalVariableTable.localVariableTable[i].length = u2Leitura(fpClass);
		atrib->type.LocalVariableTable.localVariableTable[i].nameIndex = u2Leitura(fpClass);
		atrib->type.LocalVariableTable.localVariableTable[i].descriptorIndex = u2Leitura(fpClass);
		atrib->type.LocalVariableTable.localVariableTable[i].index = u2Leitura(fpClass);
	}
	
}

void armazenaAtrSourceFile(FILE *fpClass, attributeInfo *atrib) {
	atrib->tag = ATTRIBUTE_SOURCE_FILE;
	atrib->type.SourceFile.sourceFileIndex = u2Leitura(fpClass);
}
