#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo
{

    char Proprietario[100];
    char combustivel[20];
    char modelo[40];
    char cor[50];
    char numChassi[500];
    int ano;
    char placa[50];
    struct Veiculo *prox;
} Veiculo;

Veiculo *criarlistaInicial()
{
    return NULL;
}

Veiculo *adicionarVeiculo()
{
    Veiculo novoVeiculo = (Veiculo)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL)
    {
        printf("Erro de aloacao");
        exit(EXIT_FAILURE);
    }
    novoVeiculo->prox = NULL;
    return novoVeiculo;
}

Veiculo *cadastrar(Veiculo *lista)
{
    Veiculo *novoVeiculo = adicionarVeiculo();

    printf("\nDigite o Proprietario: ");
    scanf("%s", &novoVeiculo->Proprietario);

    printf("\nDigite o Combustivel: ");
    scanf("%s", &novoVeiculo->combustivel);

    printf("\nDigite o Modelo: ");
    scanf("%s", &novoVeiculo->modelo);

    printf("\nDigite a Cor: ");
    scanf("%s", &novoVeiculo->cor);

    printf("\nDigite o Numero do Chassi: ");
    scanf("%s", &novoVeiculo->numChassi);

    printf("\nDigite o ano: ");
    scanf("%d", &novoVeiculo->ano);

    printf("\nDigite a Placa: ");
    scanf("%s", &novoVeiculo->placa);

    if (lista == NULL)
    {
        return novoVeiculo;
    }
    else
    {
        Veiculo *atual = lista;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novoVeiculo;
        return lista;
    }
}

void Diesel(struct Veiculo *lista)
{
    struct Veiculo *atual = lista;
    while (lista != NULL)
    {
        if (atual->ano >= 2010 && strcmp(atual->combustivel, "diesel") == 0)
        {
            printf("Proprietario: %s\n", atual->Proprietario);
        }
        atual = atual->prox;
    }
}

void PlacasJ(Veiculo *lista)
{
    printf("\nProprietarios: ");
    while (lista != NULL)
    {
        if (lista->placa[0] == 'J' && (lista->placa[7] == '0' || lista->placa[7] == '2' || lista->placa[7] == '4' || lista->placa[7] == '7'))
        {

            printf("\nPlaca: %s, Proprietario: %s\n", lista->placa, lista->Proprietario);
        }
        lista = lista->prox;
    }
}

void listarVogal(Veiculo *veiculo)
{
    while (veiculo != NULL)
    {
        char segundaLetraPlaca = tolower(veiculo->placa[1]);
        int somaDigitos = 0;
        for (int i = 3; i < 7; i++)
        {
            somaDigitos += veiculo->placa[i] - '0';
        }
        if (strchr("AEIOU", segundaLetraPlaca) != NULL && somaDigitos % 2 == 0)
        {
            printf("Modelo: %s, Cor: %s\n", veiculo->modelo, veiculo->cor);
        }
        veiculo = veiculo->prox;
    }
}

void trocarProprietario(Veiculo *lista)
{

    char chassiTrocado[50];
    printf("\nDigite o chassi para troca de proprietario: ");
    scanf("%s", chassiTrocado);

    char novoProprietario[50];
    printf("Digite o novo proprietario: ");
    scanf("%s", novoProprietario);

    Veiculo *atual = lista;

    while (atual != NULL)
    {
        if (strcmp(atual->numChassi, chassiTrocado) == 0 && strpbrk(atual->placa, "0") == NULL)
        {
            strncpy(atual->Proprietario, novoProprietario, sizeof(atual->Proprietario));
            printf("Proprietario alterado com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Nenhum carro encontrado com o chassi fornecido ou a placa possui digito zero.\n");
}

void VeiculosLiberado(Veiculo *lista)
{
    Veiculo *atual = lista;
    Veiculo *proximoVeiculo;
    while (atual != NULL)
    {
        proximoVeiculo = atual->prox;
        free(atual);
        atual = proximoVeiculo;
    }
}

main()
{
    int opcao;
    Veiculo *lista = criarlistaInicial();

    do
    {
        printf("    REGISTTO DOS VEICULOS   \n");
        printf("\n|1| - Cadastrar Veiculos: ");
        printf("\n|2| - Listar Diesel e carros 2010 ou posterior");
        printf("\n|3| - Listar placas com a leta 'J' e terminda com '0','2','4' ou '7'");
        printf("\n|4| - Listar Vogais e Numero Par");
        printf("\n|5| - Trocar de Proprietario");
        printf("\n|0| - sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            lista = cadastrar(lista);
            break;
        case 2:
            Diesel(lista);
            break;
        case 3:
            PlacasJ(lista);
            break;
        case 4:
            listarVogal(lista);
            break;
        case 5:
            trocarProprietario(lista);
            break;
        }

    } while (opcao != 0);
    VeiculosLiberado(lista);
}