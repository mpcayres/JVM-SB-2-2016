/**@file: FuncoesAuxiliares.h
 * @brief Arquivo de Funcoes Auxiliares
 * 
 * @details Aqui sao declaradas as estruturas principais (Tipos de dados, flags de acesso, constantes de atributo, etc) a serem utilizadas na JVM
 */
#ifndef ESTR_H
#define ESTR_H

#include <stdint.h>

/** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_CONSTANT_VALUE			0
 /** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_CODE						1
 /** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_DEPRECATED				2
 /** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_EXCEPTIONS				3
 /** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_INNER_CLASSES				4
 /** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_LINE_NUMBER_TABLE			5
 /** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_LOCAL_VARIABLE_TABLE		6
 /** @brief CONSTANTE DE ATRIBUTO*/
#define ATTRIBUTE_SOURCE_FILE				7

/** @brief FLAG DE ACESSO*/
#define FLAG_PUBLIC    0x0001
 /** @brief FLAG DE ACESSO*/
#define FLAG_PRIVATE   0x0002
 /** @brief FLAG DE ACESSO*/
#define FLAG_PROTECTED 0x0004
 /** @brief FLAG DE ACESSO*/
#define FLAG_STATIC    0x0008
 /** @brief FLAG DE ACESSO*/
#define FLAG_FINAL     0x0010
 /** @brief FLAG DE ACESSO*/
#define FLAG_SUPER     0x0020
 /** @brief FLAG DE ACESSO*/
#define FLAG_VOLATILE  0x0040
 /** @brief FLAG DE ACESSO*/
#define FLAG_TRANSIENT 0x0080
 /** @brief FLAG DE ACESSO*/
#define FLAG_NATIVE    0x0100
 /** @brief FLAG DE ACESSO*/
#define FLAG_INTERFACE 0x0200
 /** @brief FLAG DE ACESSO*/
#define FLAG_ABSTRACT  0x0400
 /** @brief FLAG DE ACESSO*/
#define FLAG_STRICT    0x0800

 /** @brief TIPO DE RETORNO*/
#define RETURN_NONE 	0
 /** @brief TIPO DE RETORNO*/
#define RETURN_32 		1
 /** @brief TIPO DE RETORNO*/
#define RETURN_64 		2

 /** @brief TIPO REFERENCE*/
#define TYPE_REFERENCE 	0
 /** @brief TIPO BOOLEAN*/
#define	TYPE_BOOLEAN 	4
 /** @brief TIPO CHAR*/
#define	TYPE_CHAR 		5
 /** @brief TIPO FLOAT*/
#define	TYPE_FLOAT 		6
 /** @brief TIPO DOUBLE*/
#define	TYPE_DOUBLE 	7
 /** @brief TIPO BYTE*/
#define	TYPE_BYTE 		8
 /** @brief TIPO SHORT*/
#define	TYPE_SHORT 		9
 /** @brief TIPO INT*/
#define	TYPE_INT 		10
 /** @brief TIPO LONG*/
#define	TYPE_LONG 		11

 /** @brief TAMANHO DO TIPO BOOLEAN*/
#define	TYPE_BOOLEAN_SIZE	1
 /** @brief TAMANHO DO TIPO BYTE*/
#define	TYPE_BYTE_SIZE		1
 /** @brief TAMANHO DO TIPO CHAR*/
#define	TYPE_CHAR_SIZE		2
 /** @brief TAMANHO DO TIPO SHORT*/
#define	TYPE_SHORT_SIZE		2
 /** @brief TAMANHO DO TIPO REFERENCE*/
#define TYPE_REFERENCE_SIZE	4
 /** @brief TAMANHO DO TIPO INT*/
#define	TYPE_INT_SIZE 		4
 /** @brief TAMANHO DO TIPO FLOAT*/
#define	TYPE_FLOAT_SIZE		4
 /** @brief TAMANHO DO TIPO DOUBLE*/
#define	TYPE_DOUBLE_SIZE	8
 /** @brief TAMANHO DO TIPO LONG*/
#define	TYPE_LONG_SIZE		8

 /** @brief inteiro de tamanho 8*/
typedef uint8_t  u1;
/** @brief inteiro de tamanho 16*/
typedef uint16_t u2;
/** @brief inteiro de tamanho 32*/
typedef uint32_t u4;
/** @brief inteiro de tamanho 64*/
typedef uint64_t u8;

/** informacao do opcode*/
typedef struct OPCODE_info {
    /** Descricao do opcode*/
	char info[30];
    /** Contador de operandos*/
	uint32_t cont_op;
    /** Indice do operando*/
	uint32_t *operandos_index;
} opcode_informacao;

 /** Conversao de Float*/
union fltConv {
    /** Variavel float*/
    float f;
    /** Inteiro 32 bits*/
    uint32_t i;
} u;

/** Conversao de Double*/
union dblConv {
    /** Variavel float*/
    double d;
    /** Variavel long*/
    long l;
} du;

 /** Tabela de Excecoes*/
typedef struct {
    /** PC inicial*/
	u2 startPc;
    /** PC final*/
	u2 endPc;
    /** PC auxiliar*/
	u2 handlerPc;
    /** Tipo de captura*/
	u2 catchType;
} exceptionTableType;

/** Tabela de Classes*/
typedef struct {
    /** Indice de informacao da classe interna*/
	u2 innerClassInfoIndex;
    /** Indice de informacao da classe externa*/
	u2 outerClassInfoIndex;
    /** Indice de nome interno*/
	u2 innerNameIndex;
    /** Flag de acesso da classe interna*/
	u2 innerClassAccessFlags;
} classType;

/** Tabela do tipo de numero da linha*/
typedef struct {
    /** PC inicial*/
	u2 startPc;
    /** Numero da linha*/
	u2 lineNumber;
} LineNumberTableType;

/** Tabela do tipo de variaveis locais*/
typedef struct {
    /** PC inicial*/
    u2 startPc;
    /** Tamanho*/
    u2 length;
    /** Indice de nome*/
    u2 nameIndex;
    /** Indice descritor*/
    u2 descriptorIndex;
    /** indice*/
    u2 index;
} LocalVariableTableType;

 /** Estrutura estatica*/
typedef struct {
    /** Nome da classe*/
	u1 *className;
    /** Contador de campos*/
	u2 fieldCount;
    /** Valor*/
	u8 *value;
} staticStruct;

 /** Informacoes de atributo*/
typedef struct attrInfo {
    u2 attributeNameIndex;
    u4 attributeLength;
    u2 tag;
    union {
        struct {
            u2 constantValueIndex;
        } ConstantValue;
        struct {
            u2 maxStack;
            u2 maxLocals;
            u4 codeLength;
            u1 *code;
            u2 exceptionTableLength;
            exceptionTableType *exceptionTable;
            u2 attributeCount;
            struct attrInfo *attributes;
        } Code;
        struct {
            u2 numberOfExceptions;
            u2 *exceptionIndexTable;
        } Exceptions;
        struct {
            u2 numberOfClasses;
            classType *classes;
        } InnerClasses;
        struct {
            u2 sourceFileIndex;
        } SourceFile;
        struct {
            
        } Synthetic, Deprecated;
        struct {
            u2 	lineNumberTableLength;
            LineNumberTableType * lineNumberTable;
        } LineNumberTable;
        struct {
            u2 	localVariableTableLength;
            LocalVariableTableType 	* localVariableTable;
        } LocalVariableTable;
        struct {
            u1 * info;
        } Default;
    } type;
} attributeInfo;

 /** Informacoes de metodo e campo*/
typedef struct {
    /** Flag de acesso*/
	u2 	accessFlags;
    /** Indice de nome*/
	u2 	nameIndex;
    /** Indice de descricao*/
	u2 	descriptorIndex;
    /** Contador de atributos*/
	u2 	attributeCount;
    /** Atributos*/
	attributeInfo * attributes;
} fieldInfo, methodInfo;

 /** Informacoes da Constant Pool
 *  @details Estrutura para lidar com as informacoes da constant pool
 */
typedef struct {
    /** Tag principal*/
    u1 tag;
    union {
        struct {
            char bytes[26];
        } Continued;
        struct {
            u2 length;
            u1 * bytes;
        } Utf8;
        struct {
            u4 bytes;
        } Integer, Float;
        struct {
            u4 lowBytes;
            u4 highBytes;
        } Long, Double;
        struct {
            u2 nameIndex;
        } Class;
        struct {
            u2 stringIndex;
        } String;
        struct {
            u2 classIndex;
            u2 nameTypeIndex;
        } FieldRef, MethodRef, InterfaceMethodRef;
        struct {
            u2 nameIndex;
            u2 descriptorIndex;
        } NameType;
    } type;
} cpInfo;

 /** Estruturas da classe
 *  @details Estrutura para lidar com as estruturas da classe
 */
typedef struct {
    /** Magic number CAFEBABE*/
    u4 magicNumber;

    /** Minor version*/
    u2 minorVersion;
    
    /** Major Version*/
    u2 majorVersion;

    /** Contador da constant pool*/
    u2 constantPoolCount;
    cpInfo * constantPool;

    /** Flags de acesso*/
    u2 accessFlags;

    /** Classe atual*/
    u2 thisClass;
    /** Classe superior*/
    u2 superClass;

    /** Contador de interfaces*/
    u2 interfaceCount;
    u2 * interfaces;

    /** Contador de campos*/
    u2 fieldCount;
    fieldInfo * fields;

    /** Contador de metodos*/
    u2 methodCount;
    methodInfo * methods;

    /** Contador de atributos*/
    u2 attributeCount;
    attributeInfo * attributes;
} classStructure;

opcode_informacao *op_info;

/** @brief Funcao para converter 2 inteiros de 32 bits em 1 de 64
*
* @param u4 low: parte menos significativa da palavra final
* @param u4 high: parte mais significativa da palavra final
* 
* @return O inteiro de 64 bits concatenando os 2 passados
*/
u8 shift32To64(u4 low, u4 high);

/** @brief Funcao para converter 2 inteiros de 8 bits em 1 de 32
*
* @param u4 low: parte menos significativa da palavra final
* @param u4 high: parte mais significativa da palavra final
* 
* @return O inteiro de 32 bits concatenando os 2 passados
*/
u4 shift8To32(u4 low, u4 high);

/** @brief Funcao para dividir 1 inteiro de 64 bits em 2 de 32
*
* @param aux: valor a ser dividido
* @param u4 low: ponteiro da parte menos significativa da palavra final
* @param u4 high: ponteiro da parte mais significativa da palavra final
* 
* @return void
*/
void shift64To32(u8 aux, u4 *low, u4 *high);

/** @brief Funcao para fazer o cast de inteiro de 32 bits para double
*
* @param u4 low: ponteiro da parte menos significativa da palavra final
* @param u4 high: ponteiro da parte mais significativa da palavra final
* 
* @return double equivalente ao inteiro passado
*/
double shiftCast32ToDouble(u4 low, u4 high);

/* @brief Funcao para montar a string de traducao dos opcodes para os mnemônicos
 * 
 */
void carregaOpcodeInfo();

/** @brief Substitui os caracteres em uma string
*
* @param char *stringOriginal: string de origem
* @param char *subString: string que será substituida na string de origem
* @param char *stringSubstituta: string a substituir na string de origem
* 
*/
void trocaCaracter(char *stringOriginal, char *subString, char *stringSubstituta);

#endif
