An�lise Din�mica efetuada com a ferrameta gcov.
1) Crie uma pasta e coloque apenas os fontes.
2) Acesse a pasta pelo terminal como usu�rio root.
3) Execute o comando gcc -fprofile-arcs -ftest-coverage *.c
4) Se o seu programa n�o tiver nenhum erro e nenhum warning
ele executar� o comando acima como se estivesse compilando.
E ser� gerado dois arquivos com extens�o .gcno e gcda para 
cada fonte do seu programa.
5) Execute o comando gcov -b *.c 
Feito isso ser� informado a porcentagem de execu��o e
ser� criado um arquivo com extens�o .c.gcov para cada fonte
A an�lise estar� contida nestes arquivos junto com o seu 
programa.   