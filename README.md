# HASH
Trabalho para a disciplina ORGANIZAÇÃO DE ESTRUTURAS DE ARQUIVOS.  
Professor: Renato Mauro  
CEFET/RJ - Campus Maracanã

##Sobre
O trabalho consiste na criação de um índice utilizando uma função de hash aplicada sobre os CEPs contidos em um arquivo de amostra fornecido pelo professor, além da análise das estatísticas obtidas na concepção do índice para estudo.

(Download do arquivo de amostra)[https://www.dropbox.com/sh/ow81qsfo4prvquu/AACNyR9TD9kE_0Om90rmtjwqa/Aula4?dl=0&preview=cep.dat#]

##Compilação
```{r, engine='bash'}
gcc -o hash hash.c
```

##Uso
```{r, engine='bash'}
./hash -g
```
Gera arquivo de índice.  
```{r, engine='bash'}
./hash -s
```
Mosta estatísticas do índice.  
```{r, engine='bash'}
./hash <CEP>
```
Procura CEP passado como argumento por linha de comando.  
OBS: deve-se gerar o arquivo de índice antes.
