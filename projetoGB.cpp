#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

typedef struct {
    int seg;
    int ter;
    int qua;
    int qui;
    int sex;
    int sab;
    int dom;
} precipitacao;

char cidade[100];

void menu();
precipitacao leiturachuvas();
void chance_alagamento(precipitacao chuvas);
void le_nome_cidade();
float media_precipitacao(precipitacao chuvas);
void gerar_relatorio(precipitacao chuvas);

void menu() {
    puts("=======================================");
    puts("= Sistema de Monitoramento de Chuvas =");
    puts("=======================================");
    puts("1- Leitura dos dados de precipitacao da semana em mm(militmetros)");
    puts("2- Chance de alagamento/enchente na regiao");
    puts("3- Media de precipitacao na semana");
    puts("4- Inserir nome da cidade");
    puts("5- Gerar relatorio");
    puts("6- Sair");
    printf("Digite sua opcao: ");
}

precipitacao leiturachuvas() {
    precipitacao chuvas;
    system("cls");
    printf("Digite o valor de precipitacao para segunda: ");
    scanf("%d", &chuvas.seg);
    printf("Digite o valor de precipitacao para terca: ");
    scanf("%d", &chuvas.ter);
    printf("Digite o valor de precipitacao para quarta: ");
    scanf("%d", &chuvas.qua);
    printf("Digite o valor de precipitacao para quinta: ");
    scanf("%d", &chuvas.qui);
    printf("Digite o valor de precipitacao para sexta: ");
    scanf("%d", &chuvas.sex);
    printf("Digite o valor de precipitacao para sabado: ");
    scanf("%d", &chuvas.sab);
    printf("Digite o valor de precipitacao para domingo: ");
    scanf("%d", &chuvas.dom);
    return chuvas;
}

void chance_alagamento(precipitacao chuvas) {
    system("cls");
    float cheia;
    int dia;
    char o;
    printf("Tem rio na encosta da sua cidade: (use S para sim e N para nao) ");
    fflush(stdin);  
    o = getchar();
    o = toupper(o);
    switch (o) {
        case 'S':
            printf("Qual a cota de cheia do seu rio (em metros): ");
            scanf("%f", &cheia);
            printf("Qual dia chove mais (use 1-seg, 2-ter, 3-qua, 4-qui, 5-sex, 6-sab, 7-dom): ");
            scanf("%d", &dia);
            break;
        case 'N':
            printf("Qual dia chove mais (use 1-seg, 2-ter, 3-qua, 4-qui, 5-sex, 6-sab, 7-dom): ");
            scanf("%d", &dia);
            break;
        default:
            printf("Opcao invalida. ");
            return;
    }

    int chuva_dia;
    switch (dia) {
        case 1: chuva_dia = chuvas.seg; break;
        case 2: chuva_dia = chuvas.ter; break;
        case 3: chuva_dia = chuvas.qua; break;
        case 4: chuva_dia = chuvas.qui; break;
        case 5: chuva_dia = chuvas.sex; break;
        case 6: chuva_dia = chuvas.sab; break;
        case 7: chuva_dia = chuvas.dom; break;
        default:
            printf("Dia invalido.\n");
            return;
    }

    if (o == 'S') {
        if (chuva_dia >= 100) {
            puts("Chuva severa, chance altissima de alagamentos");
            if (cheia < 12) {
                puts("Perigo grande de subida do rio, preferencial ficar em locais mais altos");
            }
        } else if (chuva_dia >= 80) {
            puts("Chuva forte, chance alta de alagamentos");
            if (cheia < 8) {
                puts("Chance alta de subida do rio principalmente nas encostas");
            }
        } else if (chuva_dia >= 50) {
            puts("Chuva forte, chance alta de alagamentos");
            if (cheia < 3) {
                puts("Chance baixa de subida do rio");
            }
        } else if (chuva_dia >= 20) {
            puts("Chuva moderada, chance moderada/baixa de alagamentos e sem chance de subida do rio acima da cota de cheia");
        } else {
            puts("Pouca chuva, nao apresenta perigo de alagamentos e sem subida de rios");
        }
    } else {
        if (chuva_dia >= 100) {
            puts("Chuva severa, chance altissima de alagamentos");
        } else if (chuva_dia >= 80) {
            puts("Chuva forte, chance alta de alagamentos");
        } else if (chuva_dia >= 50) {
            puts("Chuva forte, chance moderada de alagamentos");
        } else if (chuva_dia >= 20) {
            puts("Chuva moderada, chance baixa de alagamentos");
        } else {
            puts("Pouca chuva, nao apresenta perigo de alagamentos");
        }
    }
    system("pause");
    system("cls");
}

float media_precipitacao(precipitacao chuvas) {
    float media = 0;
    int total_precipitacao = chuvas.seg + chuvas.ter + chuvas.qua + chuvas.qui + chuvas.sex + chuvas.sab + chuvas.dom;
    media = (float) total_precipitacao / 7;
    return media;
}

void le_nome_cidade() {
    system("cls");
    printf("Digite o nome da cidade: ");
    fflush(stdin);
    fgets(cidade, 100, stdin);
    cidade[strcspn(cidade, "\n")] = 0;  // Remove a newline character from the end if present
    printf("Cidade inserida: %s\n", cidade);
    system("pause");
    system("cls");
}

void gerar_relatorio(precipitacao chuvas) {
    FILE *arquivo = fopen("relatorio.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }
    fprintf(arquivo, "Relatorio de Precipitacao\n");
    fprintf(arquivo, "=========================\n");
    fprintf(arquivo, "Cidade: %s\n\n", cidade);
    fprintf(arquivo, "Precipitacao da Semana:\n");
    fprintf(arquivo, "Segunda: %d mm\n", chuvas.seg);
    fprintf(arquivo, "Terca: %d mm\n", chuvas.ter);
    fprintf(arquivo, "Quarta: %d mm\n", chuvas.qua);
    fprintf(arquivo, "Quinta: %d mm\n", chuvas.qui);
    fprintf(arquivo, "Sexta: %d mm\n", chuvas.sex);
    fprintf(arquivo, "Sabado: %d mm\n", chuvas.sab);
    fprintf(arquivo, "Domingo: %d mm\n", chuvas.dom);
    float media = media_precipitacao(chuvas);
    fprintf(arquivo, "\nMedia de precipitacao na semana: %.2f mm\n", media);
    fclose(arquivo);
    printf("Relatorio gerado com sucesso.\n");
    system("pause");
    system("cls");
}

int main(void) {
    precipitacao chuvas;
    int op, flag = 0;
    float media = 0;

    do {
        menu();
        scanf("%d", &op);
        switch (op) {
            case 1:
                chuvas = leiturachuvas();
                flag = 1;
                break;
            case 2:
                if (flag == 0) {
                    system("cls");
                    puts("Selecionar a opcao 1 primeiro");
                } else {
                    chance_alagamento(chuvas);
                }
                break;
            case 3:
                if (flag == 0) {
                    system("cls");
                    puts("Selecionar a opcao 1 primeiro");
                } else {
                    media = media_precipitacao(chuvas);
                    system("cls");
                    printf("A media de precipitacao e: %.2f mm\n", media);
                    system("pause");
                }
                break;
            case 4:
                le_nome_cidade();
                break;
            case 5:
                if (flag == 0) {
                    system("cls");
                    puts("Selecionar a opcao 1 primeiro");
                } else {
                    gerar_relatorio(chuvas);
                }
                break;
            case 6:
                return 0;
            default:
                system("cls");
                puts("Opcao invalida, redigite");
                break;
        }
    } while (op != 6);
}

