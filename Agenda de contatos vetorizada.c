#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char texto_t[80];

int opcao_desejada = 0;
int qts_ctts;
texto_t *nome;
texto_t *endereco;
long long int *telefone_res;
long long int *telefone_cel;
int *data_nascimento;

void inicializar(int tam)
{
    nome = (texto_t *)malloc(tam * sizeof(texto_t));
    endereco = (texto_t *)malloc(tam * sizeof(texto_t));
    telefone_res = (long long int *)malloc(tam * sizeof(long long int));
    telefone_cel = (long long int *)malloc(tam * sizeof(long long int));
    data_nascimento = (int *)malloc(tam * sizeof(int));
}

void adicionar(const char *nome_arq)
{

    FILE *arq = fopen(nome_arq, "a");

    inicializar(qts_ctts);
    printf("Escreva o nome do contato:\n");
    fflush(stdin);
    fgets(nome, 499, stdin);
    strtok(nome, "\n");
    printf("Escreva o endereco do contato:\n");
    fflush(stdin);
    fgets(endereco, 499, stdin);
    strtok(endereco, "\n");
    printf("Escreva o telefone residencial do contato:\n");
    scanf("%ld", &telefone_res);
    printf("Escreva o telefone celular do contato:\n");
    scanf("%ld", &telefone_cel);
    printf("Escreva a data de nascimento do contato:\n");
    scanf("%d", &data_nascimento);

    printf("Seu contato sera salvo como: %s;%s;%ld;%ld;%ld", nome, endereco, telefone_res, telefone_cel, data_nascimento);
    fclose(arq);

    arq = fopen(nome_arq, "r");
    FILE *arq2 = fopen("temp_a.dat", "w");

    fprintf(arq2, "%d\n", qts_ctts + 1);

    fclose(arq2);
    arq2 = fopen("temp_a.dat", "a");

    char linha[500];
    int linha_a = 1;

    while (fgets(linha, 499, arq) != NULL)
    {
        if (linha_a != 1)
            fputs(linha, arq2);
        linha_a++;
    }
    fprintf(arq2, "\n%s;%s;%ld;%ld;%ld", nome[0], endereco[0], telefone_res, telefone_cel, data_nascimento);

    fclose(arq);
    fclose(arq2);

    arq = fopen(nome_arq, "w");
    arq2 = fopen("temp_a.dat", "r");

    while (fgets(linha, 499, arq2) != NULL)
        fputs(linha, arq);

    fclose(arq);
    fclose(arq2);
}

void remover(const char *nome_arq)
{
    FILE *arq = fopen(nome_arq, "r");
    char linha_aux[500];
    char linha[500];
    char contato_excluir[60];
    int aux = 0;

    scanf("%s", contato_excluir);
    fscanf(arq, "%d\n", &qts_ctts);
    inicializar(qts_ctts);

    for (int i = 0; i < qts_ctts; i++)
    {
        fgets(linha_aux, 499, arq);
        sscanf(linha_aux, "%[^;]s", nome[i]);
        if (strcmp(nome[i], contato_excluir) == 0)
            aux = i + 2;
    }

    if (aux == 0)
    {
        printf("O contato que voce digitou nao existe.\n");
        return;
    }
    fclose(arq);

    arq = fopen(nome_arq, "r");
    FILE *arq2 = fopen("temp_r.dat", "w");
    int linha_a = 1;

    fprintf(arq2, "%d\n", qts_ctts - 1);

    fclose(arq2);

    arq2 = fopen("temp_r.dat", "a");
    while (fgets(linha, 499, arq) != NULL)
    {
        if (linha_a != 1)
        {
            if (linha_a == aux)
            {
            }
            else
            {
                fputs(linha, arq2);
            }
        }
        linha_a++;
    }

    fclose(arq);
    fclose(arq2);

    arq = fopen(nome_arq, "w");
    arq2 = fopen("temp_r.dat", "r");

    while (fgets(linha, 499, arq2) != NULL)
        fputs(linha, arq);

    fclose(arq);
    fclose(arq2);

    printf("O contato %s foi excluido com sucesso!\n", contato_excluir);
}

void listar(const char *nome_arq)
{
    FILE *arq = fopen(nome_arq, "r");
    char linha[500];

    fscanf(arq, "%d\n", &qts_ctts);
    inicializar(15);
    for (int i = 0; i < qts_ctts; i++)
    {
        fgets(linha, 499, arq);
        sscanf(linha, "%[^;]s", nome[i]);
        printf("%s\n", nome[i]);
    }
}

void buscar(const char *nome_arq)
{
    FILE *arq = fopen(nome_arq, "r");
    char linha[500];
    char nome_buscar[60];
    int aux = 0;

    scanf("%s", &nome_buscar);

    fscanf(arq, "%d\n", &qts_ctts);
    inicializar(15);
    for (int i = 0; i < qts_ctts; i++)
    {
        fgets(linha, 499, arq);
        sscanf(linha, "%[^;]s", nome[i]);
        if (strcmp(nome[i], nome_buscar) == 0)
        {
            printf("As informacoes sobre %s sao:\n", nome[i]);
            printf("%s", linha);
            aux = 1;
            break;
        }
    }
    if (aux == 0)
        printf("O contato que voce digitou nao existe.\n");
}

void alterar(const char *nome_arq) //Nao consegui fazer essa funcao funcionar nem dessa maneira nem de outras, desculpa
{
    printf("Para alterar um contato vamos removelo e adicionalo denovo logo em seguida.\n");
    printf("Digite o nome do contato que voce deseja alterar para ele ser excluido\n");
    remover(nome_arq);
    printf("Agora, adicione este contato com as informacoes alteradas.\n");
    adicionar(nome_arq);
    printf("\nContato alterado com sucesso!");
}

int menu(const char *nome_arq)
{
    printf("O que voce deseja fazer?(digite o numero da opcao desejada)\n1-Adicionar um contato\n2-Remover um contato\n3-Listar os contatos\n4-Pesquisar pelo nome de um contato\n5-Alterar um contato\n6-Sair\n");
    scanf("%d", &opcao_desejada);

    switch (opcao_desejada)
    {
    case 1:
        printf("Para adicionar um contato siga as seguintes instrucoes:\n");
        adicionar(nome_arq);
        break;
    case 2:
        printf("Digite o nome do contato que voce deseja remover:\n");
        remover(nome_arq);
        break;
    case 3:
        printf("Os nomes em sua lista de contatos sao:\n");
        listar(nome_arq);
        break;
    case 4:
        printf("Digite o nome do contato que voce deseja buscar:\n");
        buscar(nome_arq);
        break;
    case 5:
        alterar(nome_arq);
        break;
    default:
        printf("opcao invalida, tente novamente.\n");
        opcao_desejada = 0;
    }

    return opcao_desejada;
}

int main()
{
    const char *nome_arq = "dados.txt";
    FILE *file = fopen(nome_arq, "r");
    if (file == NULL)
    {
        printf("Nao foi possivel carregar o arquivo");
        return 0;
    }
    fscanf(file, "%d", &qts_ctts);
    fclose(file);

    for (int i = 0; i < 1;)
    {
        opcao_desejada = menu(nome_arq);
        if (opcao_desejada == 0)
        {
        }
        else
            break;
    }

    return 0;
}