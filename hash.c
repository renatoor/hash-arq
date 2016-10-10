#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)

#define TAMANHO 900001

typedef struct {
	char endereco[73];
	char bairro[73];
	char cidade[73];
	char estado[73];
	char sigla[3];
	char cep[9];
} endereco;

typedef struct {
	long cep;
	long posicao;
	long prox;
} Indice;

typedef struct Lista Lista;

struct Lista {
	endereco *end;
	Lista *prox;
};

long hash(char* cep) {
	return atol(cep) % TAMANHO;
}

void zeraIndice() {

	FILE *indice = fopen("indice.dat", "wb");

	Indice novo;

	novo.cep = -1;
	novo.posicao = -1;
	novo.prox = -1;

	for(int i = 0; i < TAMANHO; i++) {
		fwrite(&novo.cep, sizeof(long), 1, indice);
		fwrite(&novo.posicao, sizeof(long), 1, indice);
		fwrite(&novo.prox, sizeof(long), 1, indice);
	}

	fclose(indice);

}

void preencheIndice() {

	zeraIndice();

	FILE *indice = fopen("indice.dat", "r+");
	FILE *entrada = fopen("cep.dat", "r");

	long tam;

	fseek(entrada, 0, SEEK_END);
	tam = ftell(entrada);
	rewind(entrada);

	do {
		long registro, hashn;
		Indice i;
		endereco e;

		registro = ftell(entrada);

		memset(&e, 0, sizeof(endereco));
		fread(&e.endereco, sizeof(char), 72, entrada);
		fread(&e.bairro, sizeof(char), 72, entrada);
		fread(&e.cidade, sizeof(char), 72, entrada);
		fread(&e.estado, sizeof(char), 72, entrada);
		fread(&e.sigla, sizeof(char), 2, entrada);
		fread(&e.cep, sizeof(char), 8, entrada);
		fseek(entrada, 2, SEEK_CUR);

		hashn = hash(e.cep);

		fseek(indice, hashn * sizeof(Indice), SEEK_SET);
		fread(&i.cep, sizeof(long), 1, indice);
		fread(&i.posicao, sizeof(long), 1, indice);
		fread(&i.prox, sizeof(long), 1, indice);

		if(i.cep == -1) {
			i.cep = atol(e.cep);
			i.posicao = registro;
			i.prox = -1;

			fseek(indice, hashn * sizeof(Indice), SEEK_SET);
			fwrite(&i.cep, sizeof(long), 1, indice);
			fwrite(&i.posicao, sizeof(long), 1, indice);
			fwrite(&i.prox, sizeof(long), 1, indice);
		}
		else {
			long proximo;

			fseek(indice, 0, SEEK_END);

			proximo = ftell(indice);
			i.cep = atol(e.cep);
			i.posicao = registro;

			fwrite(&i.cep, sizeof(long), 1, indice);
			fwrite(&i.posicao, sizeof(long), 1, indice);
			fwrite(&i.prox, sizeof(long), 1, indice);

			fseek(indice, hashn * sizeof(Indice), SEEK_SET);
			fseek(indice, 2 * sizeof(long), SEEK_CUR);

			fwrite(&proximo, sizeof(long), 1, indice);
		}
	} while(tam > ftell(entrada));

	fclose(indice);
	fclose(entrada);

}

void procuraCep(char *cep) {

	FILE *indice = fopen("indice.dat", "r");
	FILE *entrada = fopen("cep.dat", "r");

	Indice i;
	endereco e;

	int passos = 0;
	long hashn = hash(cep);

	fseek(indice, hashn * sizeof(Indice), SEEK_SET);

	do {

		passos++;

		memset(&i, 0, sizeof(Indice));
		fread(&i.cep, sizeof(long), 1, indice);
		fread(&i.posicao, sizeof(long), 1, indice);
		fread(&i.prox, sizeof(long), 1, indice);

		if(i.prox != -1)
			fseek(indice, i.prox, SEEK_SET);

		if(i.cep == atol(cep)) {

			fseek(entrada, i.posicao, SEEK_SET);

			memset(&e, 0, sizeof(endereco));
			fread(&e.endereco, sizeof(char), 72, entrada);
			fread(&e.bairro, sizeof(char), 72, entrada);
			fread(&e.cidade, sizeof(char), 72, entrada);
			fread(&e.estado, sizeof(char), 72, entrada);
			fread(&e.sigla, sizeof(char), 2, entrada);
			fread(&e.cep, sizeof(char), 8, entrada);

			printf("Índice -> CEP: %ld, Posição: %ld, Próxima posição: %ld.\n", i.cep, i.posicao, i.prox);
			printf("Número de passos para encontrar: %d\n", passos);
			printf("Endereco: %s\n", e.endereco);
			printf("Bairro: %s\n", e.bairro);
			printf("Cidade: %s\n", e.cidade);
			printf("Estado: %s\n", e.estado);
			printf("Sigla: %s\n", e.sigla);
			printf("CEP: %s\n", e.cep);

			break;

		}

	} while(i.prox != -1); 

	if(i.prox == -1 && strcmp(e.cep, cep) != 0)
		printf("CEP não encontrado.\n");

	fclose(indice);
	fclose(entrada);

}

void estatistica() {

	Lista *tab[900001];
	FILE *entrada = fopen("cep.dat", "r");
	int linha = 0;
	int colisao = 0;
	int maiorLinha = 1;
	int elementos = 0;
	long tam;

	fseek(entrada, 0, SEEK_END);
	tam = ftell(entrada);
	rewind(entrada);

	for(int i = 0; i < 900001; i++) {
		tab[i] = malloc(sizeof(Lista));
		tab[i]->end = NULL;
		tab[i]->prox = NULL;
	}

	do {
		elementos++;
		endereco *e = malloc(sizeof(endereco));
		fread(e->endereco, sizeof(char), 72, entrada);
		fread(e->bairro, sizeof(char), 72, entrada);
		fread(e->cidade, sizeof(char), 72, entrada);
		fread(e->estado, sizeof(char), 72, entrada);
		fread(e->sigla, sizeof(char), 2, entrada);
		fread(e->cep, sizeof(char), 8, entrada);
		fseek(entrada, 2, SEEK_CUR);

		int hashNum = hash(e->cep);
		Lista *aux = tab[hashNum];

		if(aux->end == NULL) {
			linha++;
			aux->end = e;
		}
		else {
			Lista *novo = malloc(sizeof(Lista));
			int cont = 1;
			novo->end = e;
			novo->prox = NULL;
			while(aux->prox != NULL) {
				aux = aux->prox;
				cont++;
			}
			cont++;
			if(cont > maiorLinha)
				maiorLinha = cont;
			colisao++;
			aux->prox = novo;
		}
	} while(ftell(entrada) < tam);

	int freq[maiorLinha];

	for(int i = 0; i < maiorLinha; i++) {
		freq[i] = 0;
	}

	for(int i = 0; i < TAMANHO; i++) {
		Lista *aux = tab[i];

		if(aux->end == NULL) {
			continue;
		}
		else {
			int cont = 1;
			while(aux->prox != NULL) {
				aux = aux->prox;
				cont++;
			}
			freq[cont - 1]++;
		}
	}

	printf("Número de elementos: %d\n", elementos);
	printf("Número de colisões: %d\n", colisao);
	printf("Maior número de colisões em uma mesma linha: %d\n", maiorLinha);
	printf("Número de linhas preenchidas: %d\n", linha);
	printf("Número de linhas não preenchidas: %d\n", TAMANHO - linha);

	int passos = 0;

	for(int i = 0; i < maiorLinha; i++) {
		printf("Probabilidade de achar um elemento em %d passo(s): %f\n", i + 1, (float) linha / (float) elementos);
		passos += linha * (i + 1);
		linha -= freq[i];

	}

	printf("Media de passos para encontrar um elemento: %f\n", (float) passos / (float) elementos);

	for(int i = 0; i < TAMANHO; i++) {
		if(tab[i]->prox == NULL && tab[i]->end != NULL) {
			free(tab[i]->end);
		}
		else {
			Lista *prox;
			Lista *aux = tab[i]->prox;
			while(aux != NULL) {
				prox = aux->prox;
				free(aux->end);
				free(aux);
				aux = prox;
			}
		}
		free(tab[i]);
	}

	fclose(entrada);

}

int main(int argc, char** argv) {

	if(argc == 2) {

		int op = 0;

		if(strcmp(argv[1], "-g") == 0)
			op = 1;
		else if(strcmp(argv[1], "-s") == 0)
			op = 2;

		switch(op) {
			case 1:
				preencheIndice();
				break;
			case 2:
				estatistica();
				break;
			default:
				procuraCep(argv[1]);
		}
	}
	else {
		printf("Uso: \t./hash -g -> Gera índice.\n");
		printf("\t./hash -s -> Mostra estatísticas do índice.\n");
		printf("\t./hash <CEP> -> Procura CEP. Obs: Deve-se gerar o índice antes.\n");
	}

	return 0;
}
