# hash-arq
Trabalho para a disciplina Organização e estrutura de arquivos.  
Professor: Renato Mauro  
CEFET/RJ - Campus Maracanã

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
./hash < CEP >
```
Procura CEP passado por argumento de linhas de comando.
