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
    printf("0 - Sair.:..... \n");
    printf("Tecle a opcao:  \n");
    scanf("%d", &opcao);
    return opcao;
}

int inclusao(tProd* vProd, int qtd)
{
    system("cls");
    printf("Inclusao\n");

    // codigo manual
    //printf("codigo....: ");
    //scanf("%d", &vProd[qtd].codigo);
    // codigo automatico
    vProd[qtd].codigo = qtd + 1;

    printf("descricao.: ");
    fflush(stdin);
    gets(vProd[qtd].descricao);
    printf("preco.....: ");
    scanf("%f", &vProd[qtd].preco);
    printf("Registro Incluido!\n");
    system("pause");
    return qtd+1;
}

int listar(tProd* vProd, int qtd)
{
    int i;
    system("cls");
    printf("+-------------------------------------------------+\n");
    printf("|              Listagem de Produtos               |\n");
    printf("+-------------------------------------------------+\n");
    for (i=0; i<qtd; i++)
    {
        printf("| %5d | %-30s | %6.2f |\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
    }
    printf("+-------------------------------------------------+\n");
    printf("| Total de Registros: %3d                         |\n", qtd);
    printf("+-------------------------------------------------+\n");
    system("pause");
}

void print_spaces(int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        printf(" ");
    }
}

int pesquisar(tProd* vProd, int qtd)
{
    int i, cont=0;;
    char buscar[50];
    system("cls");
    printf("Informe a Expressao de Busca: ");
    fflush(stdin);
    gets(buscar);

    printf("+-------------------------------------------------+\n");
    printf("| Pesquisando Produto '%s'",buscar);
    print_spaces(26-strlen(buscar));
    printf("|\n");
    printf("+-------------------------------------------------+\n");
    for (i=0; i<qtd; i++)
    {
        if (strstr(strlwr(vProd[i].descricao), strlwr(buscar))!=NULL)
        {
            printf("| %5d | %-30s | %6.2f |\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
            cont++;
        },
    }
    printf("+-------------------------------------------------+\n");
    printf("| %3d Registros Encontrados                       |\n", cont);
    printf("+-------------------------------------------------+\n");
    system("pause");
}
int gravar(tProd* vProd, int qtd)
{
    int i;
    char nomearquivo[] = "produtos.csv";
    FILE* file = fopen(nomearquivo, "w");
    if(file == NULL)
    {
        printf("Erro ao tentar gravar o arquivo\n");
    }
    else
    {
        for (i=0; i<qtd; i++)
        {
            fprintf(file, "%d;%s;%f\n", vProd[i].codigo, vProd[i].descricao, vProd[i]. preco);
        }
        printf("Arquivo gravado com sucesso!\n");
        system("pause");
    }
    fclose(file);
}
int ler_arquivo(tProd* vProd)
{
    int contador =0;

    char linha[256] = "";
    char* token;
    char nomearquivo[] = "produtos.csv";
    FILE* file = fopen(nomearquivo, "r");
    if(file == NULL)
    {
        printf("Erro ao ler o arquivo\n");
    }
    else
    {
        //ler linhas
        while (fgets(linha,256, file))
        {
            printf("%s", linha);
            //processar os campos da linha
            //codigo
            token = strtok(linha, ";\n");
            vProd[contador].codigo = atoi(token);
            //descricao
            token = strtok(NULL, ";\n");
            strcpy(vProd[contador].descricao, token);
            //preco
            token = strtok(linha, ";\n");
            vProd[contador].preco = atof(token);
            contador ++;
            }

           printf("%d registros lidos!\n", contador);

        }
        fclose(file);
        system("pause");
    return contador;
    }



int main()
{
    tProd vProd[3];
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
            ler_arquivo(vProd);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
        }

    }
    while (opcao != 0);
}
