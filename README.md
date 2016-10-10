# HASH
Trabalho para a disciplina ORGANIZAÇÃO DE ESTRUTURAS DE ARQUIVOS.  
Professor: Renato Mauro  
CEFET/RJ - Campus Maracanã

##Sobre
O trabalho consiste na criação de um índice utilizando uma função de hash aplicada sobre os CEPs contidos em um arquivo de amostra fornecido pelo professor, além da análise das estatísticas obtidas na concepção do índice para estudo.

[Download do arquivo de amostra](https://www.dropbox.com/sh/ow81qsfo4prvquu/AACNyR9TD9kE_0Om90rmtjwqa/Aula4?dl=0&preview=cep.dat)

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
./hash CEP
```
Procura CEP passado como argumento por linha de comando.  
OBS: deve-se gerar o arquivo de índice antes.

##Estatísticas
>Número de elementos: 699307  
>Número de colisões: 301770  
>Maior número de colisões em uma mesma linha: 15  
>Número de linhas preenchidas: 397537  
>Número de linhas não preenchidas: 502464  
>Probabilidade de achar um elemento em 1 passo(s): 0.568473  
>Probabilidade de achar um elemento em 2 passo(s): 0.247539  
>Probabilidade de achar um elemento em 3 passo(s): 0.101997  
>Probabilidade de achar um elemento em 4 passo(s): 0.045122  
>Probabilidade de achar um elemento em 5 passo(s): 0.019634  
>Probabilidade de achar um elemento em 6 passo(s): 0.009193  
>Probabilidade de achar um elemento em 7 passo(s): 0.004240  
>Probabilidade de achar um elemento em 8 passo(s): 0.002042  
>Probabilidade de achar um elemento em 9 passo(s): 0.000962  
>Probabilidade de achar um elemento em 10 passo(s): 0.000462  
>Probabilidade de achar um elemento em 11 passo(s): 0.000214  
>Probabilidade de achar um elemento em 12 passo(s): 0.000079  
>Probabilidade de achar um elemento em 13 passo(s): 0.000030  
>Probabilidade de achar um elemento em 14 passo(s): 0.000010  
>Probabilidade de achar um elemento em 15 passo(s): 0.000003  
>Media de passos para encontrar um elemento: 1.766530  
