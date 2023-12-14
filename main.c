#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
    int dia;
    int mes;
    int ano;
};
typedef struct data Data;

struct fardo {
    char cultivar[20];
    char tipoDeFeno;
    int diametro;
};
typedef struct fardo Fardo;

struct producao {
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;
    int qtDeFardos;
    float duracao;
};
typedef struct producao Producao;

struct tnode {
    Producao info;
    struct tnode *left, *right;
};
typedef struct tnode Node;

struct ttree {
    Node *root;
};
typedef struct ttree Tree;

void initTree(Tree *t) {
    t->root = NULL;
}

int buscaCodigo(Node *t, Node *key) {
    if (t == NULL) {
        return 0;
    }
    if (t->info.codigo == key->info.codigo){
        return 1;
    }
    
    if (key->info.codigo < t->info.codigo){
        return buscaCodigo(t->left, key);
    } 
    else {
        return buscaCodigo(t->right, key);
    }
}

int comparaData(Data data1, Data data2) {
    if (data1.ano != data2.ano) {
        return data1.ano - data2.ano;
    }
    if (data1.mes != data2.mes) {
        return data1.mes - data2.mes;
    }
    return data1.dia - data2.dia;
}

Node *insertNode(Node *t, Node *n) {
    if (t == NULL) {
        return n;
    }
    int comp = comparaData(n->info.dataProducao, t->info.dataProducao);
    if (comp < 0) {
        t->left = insertNode(t->left, n);
    } 
    else if (comp > 0) {
        t->right = insertNode(t->right, n);
    } 
    else {
        t->left = insertNode(t->left, n);
    }
    return t;
}

Node *newNode() {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o novo no.\n");
        exit(EXIT_FAILURE);
    }

    printf("Digite o codigo da producao: ");
    scanf("%d", &n->info.codigo);

    printf("Digite a data da producao (separado por espaco): ");
    scanf("%d %d %d", &n->info.dataProducao.dia, &n->info.dataProducao.mes, &n->info.dataProducao.ano);
    while (1){
        if (n->info.dataProducao.dia > 31){
            printf("Data invalida, tente novamente: ");
            scanf("%d %d %d", &n->info.dataProducao.dia, &n->info.dataProducao.mes, &n->info.dataProducao.ano);
        }
        if (n->info.dataProducao.dia < 0){
            printf("Data invalida, tente novamente: ");
            scanf("%d %d %d", &n->info.dataProducao.dia, &n->info.dataProducao.mes, &n->info.dataProducao.ano);
        }
        if (n->info.dataProducao.mes > 12){
            printf("Data invalida, tente novamente: ");
            scanf("%d %d %d", &n->info.dataProducao.dia, &n->info.dataProducao.mes, &n->info.dataProducao.ano);
        }
        if (n->info.dataProducao.dia < 0){
            printf("Data invalida, tente novamente: ");
            scanf("%d %d %d", &n->info.dataProducao.dia, &n->info.dataProducao.mes, &n->info.dataProducao.ano);
        }
        if (n->info.dataProducao.ano < 1951){
            printf("Data invalida, tente novamente: ");
            scanf("%d %d %d", &n->info.dataProducao.dia, &n->info.dataProducao.mes, &n->info.dataProducao.ano);
        }
        if (n->info.dataProducao.ano > 2023){
            printf("Data invalida, tente novamente: ");
            scanf("%d %d %d", &n->info.dataProducao.dia, &n->info.dataProducao.mes, &n->info.dataProducao.ano);
        }
        else{
            break;
        }
    }

    int selecao;
    printf("Selecione o tipo de cultivar do feno:\n 1 - Tifton 85, 2 - Florakirk, 3 - Jiggs, 4 - Coastcross: ");
    scanf("%d", &selecao);
    switch (selecao){
        case 1:
        strcpy(n->info.tipoDeFardo.cultivar, "Tifton 85");
        break;

        case 2:
        strcpy(n->info.tipoDeFardo.cultivar, "Florakirk");
        break;

        case 3:
        strcpy(n->info.tipoDeFardo.cultivar, "Jiggs");
        break;

        case 4:
        strcpy(n->info.tipoDeFardo.cultivar, "Coastcross");
        break;
        
        default:
        printf("Opçao invalida. Tente novamente.\n");
        break;
    }

    int selecao2;
    printf("Selecione o tipo do feno:\n 1 - A, 2 - B, 3 - C: ");
    scanf(" %d", &selecao2);

    switch (selecao2){
        case 1:
        n->info.tipoDeFardo.tipoDeFeno = 'A';
        break;

        case 2:
        n->info.tipoDeFardo.tipoDeFeno = 'B';
        break;

        case 3:
        n->info.tipoDeFardo.tipoDeFeno = 'C';
        break;

        default:
        printf("Opçao invalida. Tente novamente.\n");
        break;
    }
    
    printf("Digite o diametro do feno: ");
    scanf("%d", &n->info.tipoDeFardo.diametro);

    printf("Digite a quantidade de fardos: ");
    scanf("%d", &n->info.qtDeFardos);

    printf("Digite a duracao do fardo: ");
    scanf("%f", &n->info.duracao);

    n->left = NULL;
    n->right = NULL;

    return n;
}

void incluirRegistro(Tree *t) {
    Node *n = newNode();
    if(buscaCodigo(t->root, n) == 1){
        printf("Nao foi possivel inserir pois o codigo de producao ja existe.\n");
    } 
    else{
       t->root = insertNode(t->root, n); 
    }
}

void listarTodos(Node *t) {
    if (t == NULL) {
        return;
    }

    listarTodos(t->left);
    printf("\nCodigo: %d\n", t->info.codigo);
    printf("Data: %d/%d/%d\n", t->info.dataProducao.dia, t->info.dataProducao.mes, t->info.dataProducao.ano);
    printf("Cultivar: %s\n", t->info.tipoDeFardo.cultivar);
    printf("Tipo de feno: %c\n", t->info.tipoDeFardo.tipoDeFeno);
    printf("Diametro dos fardos: %d\n", t->info.tipoDeFardo.diametro);
    printf("Quantidade de fardos: %d\n", t->info.qtDeFardos);
    printf("Duracao: %.2f\n", t->info.duracao);
    listarTodos(t->right);
}

void consultarPorData(Node *t, Data data) {
    if (t == NULL) {
        printf("Nenhum registro encontrado para a data %d/%d/%d.\n", data.dia, data.mes, data.ano);
        return;
    }

    int comp = comparaData(data, t->info.dataProducao);

    if (comp < 0) {
        consultarPorData(t->left, data);
    } 
    else if (comp > 0) {
        consultarPorData(t->right, data);
    } 
    else {
        printf("<%d/%d/%d>: <%s> - <%c> - <%d>\n", data.dia, data.mes, data.ano, t->info.tipoDeFardo.cultivar, t->info.tipoDeFardo.tipoDeFeno, t->info.qtDeFardos);
    }

        if (t->left != NULL){
        consultarPorData(t->left, data);
        }
        if (t->right != NULL){
        consultarPorData(t->right, data);
        }
}

int somaFardosA(Node *t, char cultivar[20]) {
    if (t == NULL) {
        return 0;
    }

    int soma = 0;
    soma += somaFardosA(t->left, cultivar);
    if ((strcmp(cultivar, t->info.tipoDeFardo.cultivar) == 0) && (t->info.tipoDeFardo.tipoDeFeno == 'A')){
        soma += t->info.qtDeFardos;
    }
    soma += somaFardosA(t->right, cultivar);
    return soma;
}

int somaFardosB(Node *t, char cultivar[20]) {
    if (t == NULL) {
        return 0;
    }

    int soma = 0;
    soma += somaFardosB(t->left, cultivar);
    if ((strcmp(cultivar, t->info.tipoDeFardo.cultivar) == 0) && (t->info.tipoDeFardo.tipoDeFeno == 'B')){
        soma += t->info.qtDeFardos;
    }
    soma += somaFardosB(t->right, cultivar);
    return soma;
}

int somaFardosC(Node *t, char cultivar[20]) {
    if (t == NULL) {
        return 0;
    }

    int soma = 0;
    soma += somaFardosC(t->left, cultivar);
    if ((strcmp(cultivar, t->info.tipoDeFardo.cultivar) == 0) && (t->info.tipoDeFardo.tipoDeFeno == 'C')){
        soma += t->info.qtDeFardos;
    }
    soma += somaFardosC(t->right, cultivar);
    return soma;
}

void consultarPorCultivar(Node *t, int selop) {
    if (t == NULL) {
        printf("Nenhum registro encontrado para o cultivar.\n");
        return;
    }

    char opcaocultivar[20];
    switch (selop){
        case 1:
            strcpy(opcaocultivar, "Tifton 85");
            break;

        case 2:
            strcpy(opcaocultivar, "Florakirk");
            break;

        case 3:
            strcpy(opcaocultivar, "Jiggs");
            break;

        case 4:
            strcpy(opcaocultivar, "Coastcross");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
            return;
    }

    int somarFardosA = somaFardosA(t, opcaocultivar);
    int somarFardosB = somaFardosB(t, opcaocultivar);
    int somarFardosC = somaFardosC(t, opcaocultivar);

    if (somarFardosA != 0) {
        printf("<%s>: - <A> - <%d>\n", opcaocultivar, somarFardosA);
    }
    if (somarFardosB != 0) {
        printf("<%s>: - <B> - <%d>\n", opcaocultivar, somarFardosB);
    }
    if (somarFardosC != 0) {
        printf("<%s>: - <C> - <%d>\n", opcaocultivar, somarFardosC);
    }
}

void consultar(Tree *t) {
    int opcaoConsulta;
    printf("Escolha o tipo de consulta:\n");
    printf("1 - Por data\n");
    printf("2 - Por cultivar\n");
    scanf("%d", &opcaoConsulta);

    switch (opcaoConsulta) {
        case 1: {
            Data dataConsulta;
            printf("Digite a data para consulta (separado por espaco): ");
            scanf("%d %d %d", &dataConsulta.dia, &dataConsulta.mes, &dataConsulta.ano);
            consultarPorData(t->root, dataConsulta);
            break;
        }
        case 2: {
            int selop;
            printf("Selecione o tipo de cultivar do feno:\n 1 - Tifton 85, 2 - Florakirk, 3 - Jiggs, 4 - Coastcross: ");
            scanf("%d", &selop);
            consultarPorCultivar(t->root, selop);
            break;
        }
        default:
            printf("Opção inválida.\n");
    }
}

void alterarRegistro(Node *t, int codigo) {
    if (t == NULL) {
        return;
    }

    alterarRegistro(t->left, codigo);
    alterarRegistro(t->right, codigo);
    if (t != NULL && codigo == t->info.codigo){
        int opcaoAlteracao;
        do {
            printf("Escolha o campo para alteracao:\n");
            printf("1 - Codigo\n");
            printf("2 - Data\n");
            printf("3 - Cultivar\n");
            printf("4 - Tipo de feno\n");
            printf("5 - Diametro dos fardos\n");
            printf("6 - Quantidade de fardos\n");
            printf("7 - Duracao\n");
            printf("8 - Sair\n");
            printf("Digite o numero da opcao desejada: ");
            scanf("%d", &opcaoAlteracao);

            switch (opcaoAlteracao) {
                case 1:
                    printf("Digite o novo codigo: ");
                    scanf("%d", &t->info.codigo);
                    break;
                case 2:
                    printf("Digite a nova data (separado por espaco): ");
                    scanf("%d %d %d", &t->info.dataProducao.dia, &t->info.dataProducao.mes, &t->info.dataProducao.ano);
                    break;
                case 3:
                    printf("Digite o novo cultivar: ");
                    scanf("%s", t->info.tipoDeFardo.cultivar);
                    break;
                case 4:
                    printf("Digite o novo tipo de feno: ");
                    scanf(" %c", &t->info.tipoDeFardo.tipoDeFeno);
                    break;
                case 5:
                    printf("Digite o novo diametro dos fardos: ");
                    scanf("%d", &t->info.tipoDeFardo.diametro);
                    break;
                case 6:
                    printf("Digite a nova quantidade de fardos: ");
                    scanf("%d", &t->info.qtDeFardos);
                    break;
                case 7:
                    printf("Digite a nova duracao dos fardos: ");
                    scanf("%f", &t->info.duracao);
                    break;
                case 8:
                    printf("Saindo do menu de alteracao.\n");
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
            }
        } while (opcaoAlteracao != 8);
    }
}

void chamarAlteracao(Tree *t) {
    int codigoAlteracao;
    printf("Digite o codigo do registro que deseja alterar: ");
    scanf("%d", &codigoAlteracao);
    alterarRegistro(t->root, codigoAlteracao);
}

Node *removerNode(Node *t, int codigo) {
    if (t == NULL) {
        printf("A arvore esta vazia. Nenhum registro para excluir.\n");
        return t;
    }

    if (codigo < t->info.codigo) {
        t->left = removerNode(t->left, codigo);
    } 
    else if (codigo > t->info.codigo) {
        t->right = removerNode(t->right, codigo);
    } 
    else {
        if(t->left == NULL && t->right == NULL){
            free(t);
            printf("Registro com codigo %d excluido com sucesso.\n", codigo);
            return NULL;
        }
        if(t->left != NULL && t->right == NULL){
            Node *aux = t->left;
            free(t);
            printf("Registro com codigo %d excluido com sucesso.\n", codigo);
            return aux;
        }
        else if(t->left == NULL && t->right != NULL){
            Node *aux = t->right;
            free(t);
            printf("Registro com codigo %d excluido com sucesso.\n", codigo);
            return aux;
        }
        else{ 
            Node *successorParent = t;
            Node *succ = t->right;
            while (succ->left != NULL){
                successorParent = succ;
                succ = succ->left;
            }
            if(successorParent != t){
                successorParent->left = succ->right;
            }
            else{
                successorParent->right = succ->right;
            }
            t->info = succ->info;
            free(succ);
            printf("Registro com codigo %d excluido com sucesso.\n", codigo);
            return t;
        }
    }
    return t;
}

void chamarExclusao(Tree *t) {
    int codigoExclusao;
    printf("Digite o codigo do registro que deseja excluir: ");
    scanf("%d", &codigoExclusao);
    t->root = removerNode(t->root, codigoExclusao);
}

void menu(Tree *t) {
    int opcao;
    do {
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
                incluirRegistro(t);
                break;
            case 2:
                consultar(t);
                break;
            case 3:
                chamarAlteracao(t);
                break;
            case 4:
                chamarExclusao(t);
                break;
            case 5:
                listarTodos(t->root);
                break;
            case 6:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opçao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);
}

int main() {
    Tree t;
    initTree(&t);

    menu(&t);

    return 0;
}
