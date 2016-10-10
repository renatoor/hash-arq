# hash-arq
Trabalho para a disciplina Organização e estrutura de arquivos.  
Professor: Renato Mauro  
CEFET/RJ - Campus Maracanã

##Sobre
O trabalho consiste na criação de um índice utilizando uma função de hash aplicada sobre os CEPs contidos em um arquivo de amostra fornecido pelo professor.  

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
