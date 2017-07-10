Análise Dinâmica efetuada com a ferrameta gcov.
1) Crie uma pasta e coloque apenas os fontes.
2) Acesse a pasta pelo terminal como usuário root.
3) Execute o comando gcc -fprofile-arcs -ftest-coverage *.c
4) Se o seu programa não tiver nenhum erro e nenhum warning
ele executará o comando acima como se estivesse compilando.
E será gerado dois arquivos com extensão .gcno e gcda para 
cada fonte do seu programa.
5) Execute o comando gcov -b *.c 
Feito isso será informado a porcentagem de execução e
será criado um arquivo com extensão .c.gcov para cada fonte
A análise estará contida nestes arquivos junto com o seu 
programa.   