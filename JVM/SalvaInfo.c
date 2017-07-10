#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SalvaInfo.h"

classStructure* salvaInfos(char *fileSrc, char *fileTrg, char *filePath, int32_t flag_impressao) {
	static int32_t contSaidas = 0, contEntr = 0;
	char outFileName[110], tipo_perm[70], fileName[306], auxIn[100];
	FILE *fpClass, *fpSaida;

	strcpy(fileName, filePath);
	strcat(fileName, fileSrc);
	if(fileName != NULL) trocaCaracter(fileName, "/", "\\");
	if(strstr(fileName,".class") == NULL) {
		sprintf(fileName, "%s.class", fileName);
	}
	fpClass = fopen(fileName, "rb");
	if(!fpClass && contEntr > 0){
		printf("\nErro: Super Class %s nao se encontra no diretorio.\n", fileName);
		exit(1);
	}
	while(!fpClass) {
		printf("\nErro: arquivo inexistente %s\nInforme o nome de um .class valido: ", fileName);
		scanf("%s", auxIn);
		getchar();
		
		strcpy(fileName, filePath);
		strcat(fileName, auxIn);
		if(strstr(fileName,".class") == NULL) {
			sprintf(fileName, "%s.class", fileName);
		}
		fpClass = fopen(fileName, "rb");
	}
	contEntr++;
	printf("Arquivo aberto: [%s]\n\n", fileName);

	cs = calloc(sizeof(classStructure), 1);

	if(!verificaNumMagic(fpClass)) {
		printf("\nErro: O arquivo nao e do tipo .class\n");
		fclose(fpClass);
		exit(1);
    } else {
        armazenaVersoes(fpClass);
        
        if(!verificaVersao()) {
        	printf("\nErro: o arquivo .class nao e compativel com java 1.2\n");
    		fclose(fpClass);
    		exit(1);
        } else {
            armazenaConstantPool(fpClass);
            armazenaAccessFlags(fpClass);
            armazenaClasses(fpClass);
            armazenaInterfaces(fpClass);
            armazenaCampos(fpClass);
            armazenaMetodos(fpClass);
            armazenaAtributos(fpClass);
        }
    }

	if(flag_impressao == 1) {
        if(strcmp(fileTrg, "") == 0){
        	strcpy(outFileName, "Resultado.txt");
        } else{
        	strcpy(outFileName, fileTrg);
        	if(strstr(outFileName,".txt") == NULL) {
				sprintf(outFileName, "%s.txt", outFileName);
			}
        }
        
        if(contSaidas > 0){
        	outFileName[strlen(outFileName) - 4] = '\0';
        	sprintf(outFileName, "%s%d.txt", outFileName, contSaidas%10);
		}
		
		if(outFileName != NULL) trocaCaracter(outFileName, "/", "\\");
		fpSaida = fopen(outFileName, "w");
		if(!fpSaida) {
			printf("\nErro: nao foi possivel criar um arquivo de saida.\n");
			fclose(fpClass);
			return cs;
		}
		contSaidas++;
		printf("Arquivo de saida gerado: %s\n\n", outFileName);
		fprintf(fpSaida, "\n%s\n\n", fileName);
		
        salvaGeral(fpSaida, tipo_perm);
        salvaConstantPool(fpSaida);
        salvaInterfaces(fpSaida);
        salvaCampos(fpSaida);
        salvaMetodos(fpSaida);
        salvaAtributos(fpSaida);
        
		fclose(fpSaida);
    }

	fclose(fpClass);
	fpClass = NULL;

	return cs;
}

void salvaGeral(FILE * fpSaida, char * tipo_perm) {
    fprintf(fpSaida, "General Information:\n\n");
    fprintf(fpSaida, "Magic Number:   \t0x%08X\n", cs->magicNumber);
    fprintf(fpSaida, "Minor Version: %14d\n", cs->minorVersion);
    fprintf(fpSaida, "Major Version: %14d\n", cs->majorVersion);
    fprintf(fpSaida, "Constant Pool Count: %8d\n", cs->constantPoolCount - 1);
    getPermissaoDeAcesso(cs->accessFlags, tipo_perm);
    fprintf(fpSaida, "Access Flags:  \t0x%x [ %s]\n", cs->accessFlags, tipo_perm);
    fprintf(fpSaida, "This Class:    \t#%d <%s>\n", cs->thisClass, 
						cs->constantPool[cs->constantPool[cs->thisClass - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
    if(cs->superClass == (int32_t) NULL) fprintf(fpSaida, "Super Class: \n");
	else fprintf(fpSaida, "Super Class:   \t#%d <%s>\n", cs->superClass, 
						cs->constantPool[cs->constantPool[cs->superClass - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
    fprintf(fpSaida, "Interface Count: %12d\n", cs->interfaceCount);
    fprintf(fpSaida, "Field Count: %16d\n", cs->fieldCount);
    fprintf(fpSaida, "Method Count: %15d\n", cs->methodCount);
    fprintf(fpSaida, "Attribute Count: %12d\n\n", cs->attributeCount);
}

void salvaConstantPool(FILE * fpSaida) {
    int32_t j;
    long long whole;

    fprintf(fpSaida, "-----------------------------------------------\n\n");
    fprintf(fpSaida, "Constant Pool Count: %d\n\n", cs->constantPoolCount - 1);

    for(j = 0; j < cs->constantPoolCount - 1; j++) {
        fprintf(fpSaida, "Constant Pool [%d]\n", j + 1);
        
        switch(cs->constantPool[j].tag) {
            case CPOOL_CONTINUED:
                fprintf(fpSaida, "%s\n\n", cs->constantPool[j].type.Continued.bytes);
                break;
            case CPOOL_UTF8:
                fprintf(fpSaida, "Type: Utf8\nLength: %d\nString: %s\n\n",
						cs->constantPool[j].type.Utf8.length, cs->constantPool[j].type.Utf8.bytes);
                break;
            case CPOOL_INTEGER:
                fprintf(fpSaida, "Type: Integer\nBytes: 0x%x\nValue: %d\n\n",
                        cs->constantPool[j].type.Integer.bytes, cs->constantPool[j].type.Integer.bytes);
                break;
            case CPOOL_FLOAT:
                u.i = cs->constantPool[j].type.Float.bytes;
                fprintf(fpSaida, "Type: Float\nBytes: 0x%x\nValue: %f\n\n", cs->constantPool[j].type.Float.bytes, u.f);
                break;
            case CPOOL_LONG:
                whole = (long long) cs->constantPool[j].type.Long.highBytes << 32;
                whole = whole | cs->constantPool[j].type.Long.lowBytes;
                fprintf(fpSaida, "Type: Long\nHigh Bytes: 0x%x\nLow Bytes: 0x%x\nValue: %lu\n\n",
                        cs->constantPool[j].type.Long.highBytes, cs->constantPool[j].type.Long.lowBytes, whole);
                break;
            case CPOOL_DOUBLE:
                whole = (long long) cs->constantPool[j].type.Double.highBytes << 32;
                du.l = whole | cs->constantPool[j].type.Double.lowBytes;
                fprintf(fpSaida, "Type: Double\nHigh Bytes: 0x%x\nLow Bytes: 0x%x\nValue: %f\n\n",
                        cs->constantPool[j].type.Double.highBytes, cs->constantPool[j].type.Double.lowBytes, du.d);
                break;
            case CPOOL_CLASS:
                fprintf(fpSaida, "Type: Class\nName: #%d <%s>\n\n", cs->constantPool[j].type.Class.nameIndex,
                        cs->constantPool[cs->constantPool[j].type.Class.nameIndex - 1].type.Utf8.bytes);
                break;
            case CPOOL_STRING:
                fprintf(fpSaida, "Type: String\nString: #%d <%s>\n\n",
                        cs->constantPool[j].type.Class.nameIndex,
                        cs->constantPool[cs->constantPool[j].type.Class.nameIndex - 1].type.Utf8.bytes);
                break;
            case CPOOL_FIELD:
                fprintf(fpSaida, "Type: Field Reference\nClass: #%d <%s>\nName and Type: #%d <%s%s>\n\n",
                        cs->constantPool[j].type.FieldRef.classIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.FieldRef.classIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[j].type.FieldRef.nameTypeIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.FieldRef.nameTypeIndex - 1].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.FieldRef.nameTypeIndex - 1].type.NameType.descriptorIndex - 1].type.Utf8.bytes);
                break;
            case CPOOL_METHOD:
                fprintf(fpSaida, "Type: Method Reference\nClass: #%d <%s>\nName and Type: #%d <%s%s>\n\n",
                        cs->constantPool[j].type.MethodRef.classIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.MethodRef.classIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[j].type.MethodRef.nameTypeIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.MethodRef.nameTypeIndex - 1].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.MethodRef.nameTypeIndex - 1].type.NameType.descriptorIndex - 1].type.Utf8.bytes);
                break;
            case CPOOL_INTERFACE:
                fprintf(fpSaida, "Type: Interface Method Reference\nClass: #%d <%s>\nName and Type: #%d <%s%s>\n\n",
                        cs->constantPool[j].type.InterfaceMethodRef.classIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.InterfaceMethodRef.classIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[j].type.InterfaceMethodRef.nameTypeIndex,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.InterfaceMethodRef.nameTypeIndex - 1].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[cs->constantPool[cs->constantPool[j].type.InterfaceMethodRef.nameTypeIndex - 1].type.NameType.descriptorIndex - 1].type.Utf8.bytes);
                break;
            case CPOOL_NAMETYPE:
                fprintf(fpSaida, "Type: Name and Type\nName: #%d <%s>\nDescriptor: #%d <%s>\n\n",
                        cs->constantPool[j].type.NameType.nameIndex,
                        cs->constantPool[cs->constantPool[j].type.NameType.nameIndex - 1].type.Utf8.bytes,
                        cs->constantPool[j].type.NameType.descriptorIndex,
                        cs->constantPool[cs->constantPool[j].type.NameType.descriptorIndex - 1].type.Utf8.bytes);
                break;
            default:
                break;
        }
        
    }
    
}

void salvaInterfaces(FILE * fpSaida) {
    int32_t i;

    fprintf(fpSaida, "-----------------------------------------------\n\n");
    fprintf(fpSaida, "Interface Count: %d\n\n", cs->interfaceCount);

    for(i = 0; i < cs->interfaceCount; i++) {
        fprintf(fpSaida, "Interface [%d]\nName: #%d <%s>\n\n", i + 1, cs->interfaces[i],
                cs->constantPool[cs->constantPool[cs->interfaces[i] - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
    }
    
}

void salvaCampos(FILE * fpSaida) {
    int32_t j, i;
    char tipo_perm[70];

    fprintf(fpSaida, "-----------------------------------------------\n\n");
    fprintf(fpSaida, "Field Count: %d\n\n", cs->fieldCount);

    for(j = 0; j < cs->fieldCount; j++) {
        fprintf(fpSaida, "Field [%d]\n", j + 1);
        
        getPermissaoDeAcesso(cs->fields[j].accessFlags, tipo_perm);
        fprintf(fpSaida, "Access Flags: 0x%x [ %s]\nName: #%d <%s>\nDescriptor: #%d <%s>\n\nAttribute Count: %d\n\n",
                cs->fields[j].accessFlags, tipo_perm, cs->fields[j].nameIndex,
                cs->constantPool[cs->fields[j].nameIndex - 1].type.Utf8.bytes,
                cs->fields[j].descriptorIndex,
                cs->constantPool[cs->fields[j].descriptorIndex - 1].type.Utf8.bytes,
                cs->fields[j].attributeCount);
                
        for(i = 0; i < cs->fields[j].attributeCount; i++)
            salvaAtributoUnico(fpSaida, &(cs->fields[j].attributes[i]), i + 1);
            
    }
    
}

void salvaMetodos(FILE * fpSaida) {
    int32_t i, j;
    char tipo_perm[70];

    fprintf(fpSaida, "-----------------------------------------------\n\n");
    fprintf(fpSaida, "Method Count: %d\n\n", cs->methodCount);

    for(j = 0; j < cs->methodCount; j++) {
        fprintf(fpSaida, "Method [%d]\n", j + 1);
        
        getPermissaoDeAcesso(cs->methods[j].accessFlags, tipo_perm);
        fprintf(fpSaida, "Access Flags: 0x%x [ %s]\nName: #%d <%s>\nDescriptor: #%d <%s>\n\nAttribute Count: %d\n\n",
                cs->methods[j].accessFlags, tipo_perm, cs->methods[j].nameIndex,
                cs->constantPool[cs->methods[j].nameIndex - 1].type.Utf8.bytes,
                cs->methods[j].descriptorIndex,
                cs->constantPool[cs->methods[j].descriptorIndex - 1].type.Utf8.bytes,
                cs->methods[j].attributeCount);
                
        for(i = 0; i < cs->methods[j].attributeCount; i++)
            salvaAtributoUnico(fpSaida, &(cs->methods[j].attributes[i]), i + 1);
            
    }
    
}

void salvaAtributos(FILE * fpSaida) {
    int32_t i;

    fprintf(fpSaida, "-----------------------------------------------\n\n");
    fprintf(fpSaida, "Attribute Count: %d\n\n", cs->attributeCount);

    for(i = 0; i < cs->attributeCount; i++)
        salvaAtributoUnico(fpSaida, &(cs->attributes[i]), i + 1);

}

void salvaAtributoUnico(FILE * fpSaida, attributeInfo * att, int32_t j) {
    int32_t i;
    char tipo_atrib[30] = "", tipo_perm[70];
    long long whole;

    fprintf(fpSaida, "\tAttribute [%d]\n", j);
    strcpy(tipo_atrib, (char*) cs->constantPool[att->attributeNameIndex - 1].type.Utf8.bytes);
    fprintf(fpSaida, "\t[Generic Info]\n\tAttribute Name: #%d <%s>\n\tAttribute Length: %d\n\n",
            att->attributeNameIndex, tipo_atrib, att->attributeLength);
            
    if(strcmp(tipo_atrib, "ConstantValue") == 0) {
        fprintf(fpSaida, "\t[Specific Info]\n");
        fprintf(fpSaida, "\tConstant Value: #%d", att->type.ConstantValue.constantValueIndex);
                
        switch(cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].tag) {
            case CPOOL_INTEGER:
                fprintf(fpSaida, " <%d>\n", cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Integer.bytes);
                break;
            case CPOOL_FLOAT:
                u.i = cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Float.bytes;
                fprintf(fpSaida, " <%f>\n", u.f);
                break;
            case CPOOL_LONG:
                whole = (long long) cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Long.highBytes << 32;
                whole = whole | cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Long.lowBytes;
                fprintf(fpSaida, " <%lu>\n", whole);
                break;
            case CPOOL_DOUBLE:
                whole = (long long) cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Double.highBytes << 32;
                du.l = whole | cs->constantPool[att->type.ConstantValue.constantValueIndex - 1].type.Double.lowBytes;
                fprintf(fpSaida, " <%f>\n", du.d);
                break;
            default:
                fprintf(fpSaida, "\n");
                break;
        }
    } else if(strcmp(tipo_atrib, "Code") == 0) {
        fprintf(fpSaida, "\t[Specific Info]\n");
        fprintf(fpSaida, "\tMaximum stack depth: %d\n\tMaximum local variables: %d\n\tCode Length: %d\n",
                att->type.Code.maxStack, att->type.Code.maxLocals, att->type.Code.codeLength);
                
        if(att->type.Code.exceptionTableLength >= 0)
			fprintf(fpSaida, "\n\tException Table Length: %d\n\n", att->type.Code.exceptionTableLength);
			
        for(i = 0; i < att->type.Code.exceptionTableLength; i++) {
            fprintf(fpSaida, "\tCode [%d]\n\tStart PC: %d\n\tEnd PC: %d\n\tHandler PC: %d\n\tCatch Type: %d\n",
                    i + 1, att->type.Code.exceptionTable[i].startPc, att->type.Code.exceptionTable[i].endPc,
                    att->type.Code.exceptionTable[i].handlerPc, att->type.Code.exceptionTable[i].catchType);
        }
        
        if(att->type.Code.attributeCount > 0) {
        	fprintf(fpSaida, "\n\tSub-attribute Count: %d\n\n", att->type.Code.attributeCount);
        	
        	for(i = 0; i < att->type.Code.attributeCount; i++)
	            salvaAtributoUnico(fpSaida, &(att->type.Code.attributes[i]), i + 1);
	            
    		imprimirMnemonics(att->type.Code.code, att->type.Code.codeLength, fpSaida);
			fprintf(fpSaida, "\n");
		}
		
    } else if(strcmp(tipo_atrib, "Exceptions") == 0) {
        fprintf(fpSaida, "\t[Specific Info]\n");
        fprintf(fpSaida, "\tNumber of Exceptions: %d\n\n", att->type.Exceptions.numberOfExceptions);
        
        for(i = 0; i < att->type.Exceptions.numberOfExceptions; i++) {
            fprintf(fpSaida, "\tException [%d]\n\tClass: #%d\n\tClass Name: #%d <%s>\n\n",
                    i + 1, att->type.Exceptions.exceptionIndexTable[i],
                    cs->constantPool[att->type.Exceptions.exceptionIndexTable[i] - 1].type.Class.nameIndex,
                    cs->constantPool[cs->constantPool[att->type.Exceptions.exceptionIndexTable[i] - 1].type.Class.nameIndex - 1].type.Utf8.bytes);
        }
        
    } else if(strcmp(tipo_atrib, "InnerClasses") == 0) {
        fprintf(fpSaida, "\t[Specific Info]\n");
        fprintf(fpSaida, "\tNumber of Classes: %d\n\n", att->type.InnerClasses.numberOfClasses);

        for(i = 0; i < att->type.InnerClasses.numberOfClasses; i++) {
            getPermissaoDeAcesso(att->type.InnerClasses.classes[i].innerClassAccessFlags, tipo_perm);
            fprintf(fpSaida, "\tInner Class [%d]\n\tInner Class: #%d <%s>\n\tOuter Class: #%d <%s>\n"
                             "\tInner Name: #%d <%s>\n\tInner Class Access Flags: 0x%x [ %s]\n",
                    i + 1, att->type.InnerClasses.classes[i].innerClassInfoIndex,
                    cs->constantPool[cs->constantPool[att->type.InnerClasses.classes[i].innerClassInfoIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                    att->type.InnerClasses.classes[i].outerClassInfoIndex,
                    cs->constantPool[cs->constantPool[att->type.InnerClasses.classes[i].outerClassInfoIndex - 1].type.Class.nameIndex - 1].type.Utf8.bytes,
                    att->type.InnerClasses.classes[i].innerNameIndex,
                    cs->constantPool[att->type.InnerClasses.classes[i].innerNameIndex - 1].type.Utf8.bytes,
                    att->type.InnerClasses.classes[i].innerClassAccessFlags, tipo_perm);
        }
        
    } else if(strcmp(tipo_atrib, "SourceFile") == 0) {
    	fprintf(fpSaida, "\t[Specific Info]\n");
        fprintf(fpSaida, "\tSource File Name Index: #%d\n", att->type.SourceFile.sourceFileIndex);
    }
}

void imprimirMnemonics(u1 *bytecode, u2 tam, FILE *fpSaida) {
	int32_t i, j;
	opcode_informacao op_aux;

	fprintf(fpSaida, "\tBytecode:\n");
	for(i = 0; i < tam; i++) {
		op_aux = op_info[bytecode[i]];
		fprintf(fpSaida, "\t%d  %s", i, op_aux.info);
		
		op_aux.operandos_index = calloc(sizeof(u4), op_aux.cont_op);
		for(j = 0; j < op_aux.cont_op; j++) {
			op_aux.operandos_index[j] = bytecode[++i];
			if(j == 0) {
				if(op_aux.operandos_index[j] == 0) fprintf(fpSaida, " #");
				else fprintf(fpSaida, " #%hu", op_aux.operandos_index[j]);
			}
			else fprintf(fpSaida, "%hu", op_aux.operandos_index[j]);
		}
		fprintf(fpSaida, "\n");
	}

}

void getPermissaoDeAcesso(int32_t intValue, char *target) {
    strcpy(target, "");

    if( (intValue) & (1 << 0) ) strcat(target, "public ");
    else if( (intValue) & (1 << 1) ) strcat(target, "private ");
    else if( (intValue) & (1 << 2) ) strcat(target, "protected ");

    if( (intValue) & (1 << 3) ) strcat(target, "static ");
    if( (intValue) & (1 << 4) ) strcat(target, "final ");
    if( (intValue) & (1 << 5) ) strcat(target, "super ");
    if( (intValue) & (1 << 6) ) strcat(target, "volatile ");
    if( (intValue) & (1 << 7) ) strcat(target, "transient ");
    if( (intValue) & (1 << 8) ) strcat(target, "native ");
    if( (intValue) & (1 << 9) ) strcat(target, "interface ");
    if( (intValue) & (1 << 10) ) strcat(target, "abstract ");
}

char* getNome(classStructure *class_file, u2 nameIndex) {
	int32_t i;
	char *dest = malloc((class_file->constantPool[nameIndex - 1]).type.Utf8.length + 1);

	for(i = 0; i < (class_file->constantPool[nameIndex - 1]).type.Utf8.length; i++)
		dest[i] = (char) (class_file->constantPool[nameIndex - 1]).type.Utf8.bytes[i];
	dest[i] = '\0';

	return dest;
}
