JVM - Software Básico 2/2016

0) Integrantes:

- Amanda Lopes Dantas (13/0100391)
- Edgar Fabiano de Souza Filho (14/0019201)
- Guilherme Gomes Brandi (15/0128274)
- Marcos Paulo Cayres Rosa (14/0027131)
- Rennê Ruan Alves Oliveira (14/0030930)

1) Compilação:

gcc -I../ -std=c99 -o jvm.exe *.c
ou DEV

2) Execução:

2.1) Para rodar a JVM, execute dentro da pasta JVM:

jvm exemplo.class [C:\Users\seucaminho\JVM\]
-- jvm exemplo.class
-- jvm exemplo.class C:\Users\seucaminho\JVM\

2.2) Para rodar a JVM e o leitor/exibidor, execute dentro da pasta JVM:

jvm -c exemplo.class [output.txt C:\Users\seucaminho\JVM\]
-- jvm -c exemplo.class
-- jvm -c exemplo.class output.txt
-- jvm -c exemplo.class output.txt C:\Users\seucaminho\JVM\

2.3) Para rodar somente o leitor/exibidor, execute dentro da pasta JVM:

jvm -p exemplo.class [output.txt C:\Users\seucaminho\JVM\]
-- jvm -p exemplo.class
-- jvm -p exemplo.class output.txt
-- jvm -p exemplo.class output.txt C:\Users\seucaminho\JVM\

3) Observações:

- Parâmetros entre colchetes são opcionais
--- Nome de arquivo de saída padrão: Resultado.txt
--- Caminho padrão: o da pasta em que está sendo executado
- jvm é o nome do executável que a compilação gera (só que sem o exe)
- C:\Users\seucaminho\JVM\ é o caminho da pasta no seu pc
- output.txt é o arquivo que conterá os mnemônicos equivalente ao javap -c
- Se o .class não for informado ou não for possível abri-lo, será solicitada sua inserção por linha de comando
