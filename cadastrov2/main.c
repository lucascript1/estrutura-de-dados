#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    char descricao[50];
    float preco;
} tProd;

int mostra_menu()
{
    int opcao;
    system("cls");
    printf("+------------------------------------------------+ \n");
    printf("|                 MEU PRINCIPAL                  | \n");
    printf("+------------------------------------------------+ \n");
    printf("1 - Incluir.:.. \n");
    printf("2 - Listar.:... \n");
    printf("3 - Pesquisar.:... \n");
    printf("4 - Gravar.:... \n");
    printf("5 - Ler arquivo:... \n");
    printf("6 - Ordenar produtos:...\n");
    printf("0 - Sair.:..... \n");
    printf("Tecle a opcao:  \n");
    scanf("%d", &opcao);
    return opcao;
}

void ordenar_produtos(tProd* vProd, int qtd) {
    int i, j;
    tProd temp;
    for (i = 0; i < qtd - 1; i++) {
        for (j = i + 1; j < qtd; j++) {
            if (strcmp(vProd[i].descricao, vProd[j].descricao) > 0) {
                temp = vProd[i];
                vProd[i] = vProd[j];
                vProd[j] = temp;
            }
        }
    }
    listar(vProd, qtd);
}

int inclusao(tProd* vProd, int qtd)
{
    system("cls");
    printf("Inclusao\n");

    // codigo automatico
    vProd[qtd].codigo = qtd + 1;

    printf("descricao.: ");
    getchar(); // para consumir o '\n' deixado pelo scanf anterior
    fgets(vProd[qtd].descricao, sizeof(vProd[qtd].descricao), stdin);
    vProd[qtd].descricao[strcspn(vProd[qtd].descricao, "\n")] = '\0'; // Remove o '\n'

    printf("preco.....: ");
    scanf("%f", &vProd[qtd].preco);

    printf("Registro Incluido!\n");
    system("pause");
    return qtd + 1;
}

int listar(tProd* vProd, int qtd)
{
    int i;
    system("cls");
    printf("+-------------------------------------------------+\n");
    printf("|              Listagem de Produtos               |\n");
    printf("+-------------------------------------------------+\n");
    for (i = 0; i < qtd; i++)
    {
        printf("| %5d | %-30s | %6.2f |\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
    }
    printf("+-------------------------------------------------+\n");
    printf("| Total de Registros: %3d                         |\n", qtd);
    printf("+-------------------------------------------------+\n");
    system("pause");
    return qtd;
}

void print_spaces(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf(" ");
    }
}

int pesquisar(tProd* vProd, int qtd)
{
    int i, cont = 0;
    char buscar[50];
    system("cls");
    printf("Informe a Expressao de Busca: ");
    getchar(); // para consumir o '\n' deixado pelo scanf anterior
    fgets(buscar, sizeof(buscar), stdin);
    buscar[strcspn(buscar, "\n")] = '\0'; // Remove o '\n'

    printf("+-------------------------------------------------+\n");
    printf("| Pesquisando Produto '%s'", buscar);
    print_spaces(26 - strlen(buscar));
    printf("|\n");
    printf("+-------------------------------------------------+\n");
    for (i = 0; i < qtd; i++)
    {
        if (strstr(vProd[i].descricao, buscar) != NULL)
        {
            printf("| %5d | %-30s | %6.2f |\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
            cont++;
        }
    }
    printf("+-------------------------------------------------+\n");
    printf("| %3d Registros Encontrados                       |\n", cont);
    printf("+-------------------------------------------------+\n");
    system("pause");
    return cont;
}

int gravar(tProd* vProd, int qtd)
{
    int i;
    char nomearquivo[] = "produtos.csv";
    FILE* file = fopen(nomearquivo, "w");
    if (file == NULL)
    {
        printf("Erro ao tentar gravar o arquivo\n");
    }
    else
    {
        for (i = 0; i < qtd; i++)
        {
            fprintf(file, "%d;%s;%f\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
        }
        printf("Arquivo gravado com sucesso!\n");
        system("pause");
    }
    fclose(file);
    return qtd;
}

int ler_arquivo(tProd* vProd)
{
    int cont = 0;
    char linha[256];
    char* token;
    char nomearquivo[] = "produtos.csv";
    FILE* file = fopen(nomearquivo, "r");
    if (file == NULL)
    {
        printf("Erro ao ler o arquivo\n");
    }
    else
    {
        while (fgets(linha, sizeof(linha), file))
        {
            token = strtok(linha, ";\n");
            if (token != NULL) {
                vProd[cont].codigo = atoi(token);
                token = strtok(NULL, ";\n");
                if (token != NULL) {
                    strcpy(vProd[cont].descricao, token);
                    token = strtok(NULL, ";\n");
                    if (token != NULL) {
                        vProd[cont].preco = atof(token);
                        cont++;
                    }
                }
            }
        }
        printf("%d registros lidos!\n", cont);
        fclose(file);
        system("pause");
    }
    return cont;
}

int main()
{
    tProd vProd[100];
    int qtd = 0;
    int opcao;

    do
    {
        opcao = mostra_menu();

        switch (opcao)
        {
        case 1:
            qtd = inclusao(vProd, qtd);
            break;
        case 2:
            listar(vProd, qtd);
            break;
        case 3:
            pesquisar(vProd, qtd);
            break;
        case 4:
            gravar(vProd, qtd);
            break;
        case 5:
            qtd = ler_arquivo(vProd);
            break;
        case 6:
            ordenar_produtos(vProd, qtd);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
        }

    } while (opcao != 0);

    return 0;
}
