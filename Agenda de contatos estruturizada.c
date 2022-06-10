#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_STR 80

typedef char texto_t[TAM_STR];

typedef struct Contato_T
{
    texto_t nome;
    texto_t endereco;
    texto_t telefone_res;
    texto_t telefone_cel;
    texto_t data_nascimento;
} Contato;

Contato *criarContato()
{
    Contato *contato = (Contato *)malloc(sizeof(Contato));

    printf("Nome: ");
    fgets(contato->nome, TAM_STR - 1, stdin);
    contato->nome[strlen(contato->nome) - 1] = '\0';

    printf("Endereco: ");
    fgets(contato->endereco, TAM_STR - 1, stdin);
    contato->endereco[strlen(contato->endereco) - 1] = '\0';

    printf("Telefone residencial: ");
    fgets(contato->telefone_res, TAM_STR - 1, stdin);
    contato->telefone_res[strlen(contato->telefone_res) - 1] = '\0';

    printf("Telefone celular: ");
    fgets(contato->telefone_cel, TAM_STR - 1, stdin);
    contato->telefone_cel[strlen(contato->telefone_cel) - 1] = '\0';

    printf("Data de nascimento: ");
    fgets(contato->data_nascimento, TAM_STR - 1, stdin);
    contato->data_nascimento[strlen(contato->data_nascimento) - 1] = '\0';

    return contato;
}

void mostrarContato(Contato *contato)
{
    printf("Nome: %s\n", contato->nome);
    printf("Endereco: %s\n", contato->endereco);
    printf("Telefone residencial: %s\n", contato->telefone_res);
    printf("Telefone celular: %s\n", contato->telefone_cel);
    printf("Data de nascimento: %s\n", contato->data_nascimento);
}

void mostrarcontatoFile(const char *nome_arq, Contato *contato)
{
    FILE *arq = fopen(nome_arq, "a");
    fprintf(arq, "%s;", contato->nome);
    fprintf(arq, "%s;", contato->endereco);
    fprintf(arq, "%s;", contato->telefone_res);
    fprintf(arq, "%s;", contato->telefone_cel);
    fprintf(arq, "%s", contato->data_nascimento);
    fclose(arq);
}

typedef Contato ItemLista;

typedef struct Celula_T
{
    ItemLista *item;
    struct Celula_T *prox;
} Celula;

Celula *criarCelula(ItemLista *item, Celula *prox)
{
    Celula *celula = (Celula *)malloc(sizeof(Celula));

    if (celula != NULL) // se há memória
    {
        celula->item = item;
        celula->prox = prox;
    }

    return celula;
}

typedef struct ListaEncadeada_T
{
    Celula *inicio;
    Celula *fim;
    int quantos;
} ListaEncadeada;

ListaEncadeada *criarListaEncadeada()
{
    ListaEncadeada *lista = (ListaEncadeada *)malloc(sizeof(ListaEncadeada));

    if (lista != NULL) // se há memória
    {
        lista->inicio = lista->fim = NULL;
        lista->quantos = 0;
    }
    return lista;
}

int inserirNoFim(ListaEncadeada *lista, ItemLista *item)
{
    if (lista == NULL)
        return 0;
    else
    {
        Celula *novo = criarCelula(item, NULL);

        if (novo == NULL)
            return 0;

        if (estah_vazia(lista) == 1)
            lista->inicio = lista->fim = novo;
        else
        {
            lista->fim->prox = novo;
            lista->fim = novo;
        }
        lista->quantos++;
        return 1;
    }
}

int estah_vazia(ListaEncadeada *lista)
{
    if ((lista == NULL) || (lista->quantos == 0))
        return 1;

    return 0;
}

int item_ehIgual(ItemLista *item1, ItemLista *item2)
{
    if ((item1 != NULL) && (item2 != NULL) && strcmp(item1->nome, item2->nome) == 0)
        return 1;

    return 0;
}

int excluir(ListaEncadeada *lista, ItemLista *item)
{

    if (lista == NULL)
        return 0;
    else if (estah_vazia(lista))
        return 0;
    else
    {
        Celula *ctt_auxiliar = lista->inicio;
        if (item_ehIgual(ctt_auxiliar->item, item))
        {
            lista->inicio = ctt_auxiliar->prox;
            ctt_auxiliar->prox = NULL;
            free(ctt_auxiliar->item);
            free(ctt_auxiliar);
            lista->quantos--;
            return 1;
        }
        else
        {
            while (ctt_auxiliar->prox != NULL)
            {
                if (item_ehIgual(ctt_auxiliar->prox->item, item))
                {
                    Celula *temp = ctt_auxiliar->prox;
                    if (ctt_auxiliar->prox == lista->fim)
                        lista->fim = ctt_auxiliar;

                    ctt_auxiliar->prox = temp->prox;
                    temp->prox = NULL;
                    free(temp->item);
                    free(temp);
                    lista->quantos--;
                    return 1;
                }
                ctt_auxiliar = ctt_auxiliar->prox;
            }
        }
    }

    return 0;
}

int tamanho(ListaEncadeada *lista)
{

    if (lista == NULL)
        return 0;

    return lista->quantos;
}

ItemLista *pesquisarItem(ListaEncadeada *lista, texto_t nome)
{
    if (estah_vazia(lista) == 1)
        return NULL;

    Celula *ctt_auxiliar = lista->inicio;
    do
    {
        if (strcmp(ctt_auxiliar->item->nome, nome) == 0)
            return ctt_auxiliar->item;

        ctt_auxiliar = ctt_auxiliar->prox;
    } while (ctt_auxiliar != NULL);

    return NULL;
}

void alterarContato(ItemLista *contato)
{
    printf("Novo nome: ");
    fgets(contato->nome, TAM_STR - 1, stdin);
    contato->nome[strlen(contato->nome) - 1] = '\0';

    printf("Novo endereco: ");
    fgets(contato->endereco, TAM_STR - 1, stdin);
    contato->endereco[strlen(contato->endereco) - 1] = '\0';

    printf("Novo telefone residencial: ");
    fgets(contato->telefone_res, TAM_STR - 1, stdin);
    contato->telefone_res[strlen(contato->telefone_res) - 1] = '\0';

    printf("Novo telefone celular: ");
    fgets(contato->telefone_cel, TAM_STR - 1, stdin);
    contato->telefone_cel[strlen(contato->telefone_cel) - 1] = '\0';

    printf("Nova data de nascimento: ");
    fgets(contato->data_nascimento, TAM_STR - 1, stdin);
    contato->data_nascimento[strlen(contato->data_nascimento) - 1] = '\0';
}

ItemLista **obterArray(ListaEncadeada *lista)
{
    ItemLista **array = (ItemLista **)malloc(tamanho(lista) * sizeof(ItemLista *));

    Celula *ctt_auxiliar = lista->inicio;
    for (int i = 0; i < tamanho(lista); i++)
    {
        array[i] = ctt_auxiliar->item;
        ctt_auxiliar = ctt_auxiliar->prox;
    }

    return array;
}

int menu()
{
    int opcao;

    printf("\n1. Adicionar\n");
    printf("2. Remover\n");
    printf("3. Pesquisar\n");
    printf("4. Alterar\n");
    printf("5. Listar todos\n");
    printf("6. Sair\n");
    printf("Opcao: ");

    scanf("%d", &opcao);
    fflush(stdin);

    return opcao;
}

void ArquivoParaLista(ListaEncadeada *lista)
{
    FILE *file = fopen("contatos.txt", "r");

    char linha_aux[500];
    for (int i = 0; i < lista->quantos; i++)
    {
        Contato *contato = (Contato *)malloc(sizeof(Contato));
        Celula *celulaFile = criarCelula(contato, NULL);
        if (celulaFile == NULL)
            return 0;
        if (i == 0)
        {
            lista->fim = lista->inicio = celulaFile;
        }
        else
        {
            lista->fim->prox = celulaFile;
            lista->fim = celulaFile;
        }
    }

    Celula *auxiliar = lista->inicio;
    for (int x = 0; fgets(linha_aux, 499, file) != NULL; x++)
    {
        char *elemento_atual = strtok(linha_aux, ";");
        strcpy(auxiliar->item->nome, elemento_atual);

        elemento_atual = strtok(NULL, ";");
        strcpy(auxiliar->item->endereco, elemento_atual);
        free(elemento_atual);

        elemento_atual = strtok(NULL, ";");
        strcpy(auxiliar->item->telefone_res, elemento_atual);
        free(elemento_atual);

        elemento_atual = strtok(NULL, ";");
        strcpy(auxiliar->item->telefone_cel, elemento_atual);
        free(elemento_atual);

        elemento_atual = strtok(NULL, ";");
        strcpy(auxiliar->item->data_nascimento, elemento_atual);
        free(elemento_atual);

        auxiliar = auxiliar->prox;
    }
    fclose(file);
}

ListaEncadeada *ordemAlfabetica(ListaEncadeada *lista)
{
    Celula *auxiliar = lista->inicio;
    Contato *ctt_auxiliar;
    int aux = 0;

    for (int i = 0; i < lista->quantos - 1; i++)
    {
        for (int qtd_letras = 0; qtd_letras < strlen(auxiliar->item->nome); qtd_letras++)                
            auxiliar->item->nome[qtd_letras] = tolower(auxiliar->item->nome[qtd_letras]);             
        for (int qtd_letras = 0; qtd_letras < strlen(auxiliar->prox->item->nome); qtd_letras++)            
            auxiliar->prox->item->nome[qtd_letras] = tolower(auxiliar->prox->item->nome[qtd_letras]);
    }

    for (int i = 0; i < lista->quantos - 1; i++)
    {
        if (strcmp(auxiliar->item->nome, auxiliar->prox->item->nome) > 0)
        {
            ctt_auxiliar = auxiliar->item;
            auxiliar->item = auxiliar->prox->item;
            auxiliar->prox->item = ctt_auxiliar;
            aux = 1;
        }
        auxiliar = auxiliar->prox;
    }
    ListaEncadeada *listaOrdenada = lista;
    if (aux == 1)
        ordemAlfabetica(lista);
    return listaOrdenada;
}

int main()
{
    int numero = 0;
    int opcao = 6;
    ListaEncadeada *lista = criarListaEncadeada();
    Contato *contato;
    texto_t nome;
    const char *nome_arq = "contatos.txt";
    FILE *file = fopen(nome_arq, "r");
    if (file == NULL)
    {
        printf("Sua lista de contatos esta vazia por enquanto.\n");
        fclose(file);
    }
    else
    {
        char linha[500];
        do
        {
            numero++;
        } while (fgets(linha, 499, file) != NULL);
        lista->quantos = numero - 1;
        ArquivoParaLista(lista);
    }

    do
    {
        opcao = menu();

        switch (opcao)
        {
        case 1:
            printf("### ADICIONAR ####\n");
            contato = criarContato();
            inserirNoFim(lista, contato);
            break;

        case 2:
            printf("### REMOVER ####\n");
            printf("Informe o nome: ");
            fgets(nome, TAM_STR - 1, stdin);
            nome[strlen(nome) - 1] = '\0';
            contato = pesquisarItem(lista, nome);
            if (contato != NULL)
            {
                excluir(lista, contato);
                printf("*** Contato Excluido ***\n");
                mostrarContato(contato);
            }
            else
                printf("Excluir::Nenhum contato com o nome '%s'\n\n", nome);
            break;

        case 3:
            printf("### PESQUISAR ####\n");
            printf("Informe o nome: ");
            fgets(nome, TAM_STR - 1, stdin);
            nome[strlen(nome) - 1] = '\0';
            contato = pesquisarItem(lista, nome);
            if (contato != NULL)
                mostrarContato(contato);
            else
                printf("Pesquisar::Nenhum contato com o nome '%s'\n\n", nome);
            break;

        case 4:
            printf("### ALTERAR ####\n");
            printf("Informe o nome do contato a ser alterado: ");
            fgets(nome, TAM_STR - 1, stdin);
            nome[strlen(nome) - 1] = '\0';
            contato = pesquisarItem(lista, nome);
            if (contato != NULL)
            {
                alterarContato(contato);
            }
            else
                printf("Nenhum contato com o nome '%s'\n\n", nome);

            break;

        case 5:
            printf("### LISTAR ####\n");
            Contato **contatos = obterArray(lista);
            for (int i = 0; i < tamanho(lista); i++)
            {
                printf("**************************\n");
                mostrarContato(contatos[i]);
            }
            break;

        case 6:
            printf("### SAIR ####\n");
            fopen(nome_arq, "w");
            lista = ordemAlfabetica(lista);
            Contato **contatosFile = obterArray(lista);
            for (int i = 0; i < tamanho(lista); i++)
            {
                mostrarcontatoFile(nome_arq, contatosFile[i]);
            }
            fclose(nome_arq);
            exit(1);
            break;
        }
        system("pause");
        system("cls");
    } while (opcao != 6);

    return 0;
}