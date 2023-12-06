#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct data{
int dia;
int mes;
int ano;
};
typedef struct data Data;

struct fardo{
char cultivar[20];
char tipoDeFeno;
int diametro;
};
typedef struct fardo Fardo;

struct producao{
int codigo;
Data dataProducao;
Fardo tipoDeFardo;
int qtDeFardos;
float duracao;
struct producao *next;
struct producao *prev;
};
typedef struct producao Producao;

void menu(){
    int opcao;
    while(opcao != 6){
    printf("\nMenu Principal:\n");
    printf("1 - Incluir Producao\n");
    printf("2 - Consultar\n");
    printf("3 - Alterar\n");
    printf("4 - Excluir\n");
    printf("5 - Listar todos\n");
    printf("6 - Sair\n");
    printf("Digite o numero da opcao desejada: ");
    scanf("%d", &opcao);

    switch (opcao){
            case 1:
                printf("caso 1.\n");
                break;
            case 2:
                printf("caso 2.\n");
                break;
            case 3:
                printf("caso 3.\n");
                break;
            case 4:
                printf("caso 4.\n");
                break;
            case 5:
                printf("caso 5.\n");
                break;
            case 6:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opçao invalida. Tente novamente.\n");
        }
    }
}

int main(){

    menu();

    return 0;
}