#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

void criptografarCesar(char palavra[], int passo);
void descriptografarCesar(char palavra[], int passo);
void saibaMais(void);
void limparEntrada(void);
int lerInteiro(int *numero);
void lerTexto(char texto[], int tamanho);

int main(void) {
    char palavra[50] = "";
    int opcao = 0;
    int passo = 0;

    printf("\n = Bem vindo(a) =\n");
    printf("\nOla! Este programa tem o objetivo de ensinar, de maneira "
           "ludica, um pouco sobre criptografia.\n"
           "Para comecar, voce deve informar a palavra/frase a ser criptografada.\n"
           "Nos usamos a cifra de Cesar, que consiste em fazer cada letra ser "
           "representada por outra a uma certa distancia dela.\n"
           "Isso e definido pelo que aqui chamaremos de passo.\n"
           "Um passo 4, por exemplo, transforma 'a' em 'e' e "
           "'batata' em 'fexexe'.\n"
           "Essa cifra trata o alfabeto como um circulo, tal que, "
           "estando no 'z' e tendo passo 2, a letra cifrada e 'b'.\n");

    do {
        printf("\n1 - Definir o plaintext (texto nao cifrado)\n");
        printf("2 - Criptografar\n");
        printf("3 - Descriptografar\n");
        printf("4 - Saiba mais\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (!lerInteiro(&opcao)) {
            printf("Opcao invalida!\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {

        case 1:
            printf("Texto: ");
            lerTexto(palavra, sizeof(palavra));
            break;

        case 2:
            if (palavra[0] == '\0') {
                printf("Primeiro defina um texto na opcao 1.\n");
                break;
            }

            printf("Escolha o passo: ");
            if (!lerInteiro(&passo)) {
                printf("Passo invalido!\n");
                break;
            }

            criptografarCesar(palavra, passo);
            printf(" > %s\n", palavra);
            break;

        case 3:
            if (palavra[0] == '\0') {
                printf("Primeiro defina um texto na opcao 1.\n");
                break;
            }

            printf("Escolha o passo: ");
            if (!lerInteiro(&passo)) {
                printf("Passo invalido!\n");
                break;
            }

            descriptografarCesar(palavra, passo);
            printf(" > %s\n", palavra);
            break;

        case 4:
            saibaMais();
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}

void criptografarCesar(char palavra[], int passo) {
    passo = ((passo % 26) + 26) % 26;

    for (int i = 0; palavra[i] != '\0'; i++) {

        if (palavra[i] >= 'a' && palavra[i] <= 'z') {
            palavra[i] = ((palavra[i] - 'a' + passo) % 26) + 'a';
        }

        else if (palavra[i] >= 'A' && palavra[i] <= 'Z') {
            palavra[i] = ((palavra[i] - 'A' + passo) % 26) + 'A';
        }
    }
}

void descriptografarCesar(char palavra[], int passo) {
    passo = ((passo % 26) + 26) % 26;

    for (int i = 0; palavra[i] != '\0'; i++) {

        if (palavra[i] >= 'a' && palavra[i] <= 'z') {
            palavra[i] = ((palavra[i] - 'a' - passo + 26) % 26) + 'a';
        }

        else if (palavra[i] >= 'A' && palavra[i] <= 'Z') {
            palavra[i] = ((palavra[i] - 'A' - passo + 26) % 26) + 'A';
        }
    }
}

void saibaMais(void) {
    char plaintxt[50] = "";
    char chute[50] = "";
    char resposta[50] = "admin";
    char escolha = 's';

    int opcao = 0;
    int passo = 0;

    do {
        printf("\n = Descubra o texto real para saber mais "
               "sobre criptografia! =\n");
        printf("Dica: todas as cifras dos desafios usam a cifra de Cesar.\n\n");

        printf("1 - Por que e como fazer senhas seguras?\n");
        printf("2 - Criptografar\n");
        printf("3 - Descriptografar\n");
        printf("4 - Saiba mais\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (!lerInteiro(&opcao)) {
            printf("Opcao invalida!\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {

        case 1:
            escolha = 's';

            do {
                printf("\nO texto cifrado e: ehqmr\n");
                printf("Digite o texto que voce acha que foi cifrado: ");
                lerTexto(chute, sizeof(chute));

                printf("Agora digite o passo usado para gerar este texto: ");

                if (!lerInteiro(&passo)) {
                    printf("Passo invalido!\n");
                    continue;
                }

                criptografarCesar(chute, passo);

                if (strcmp(chute, "ehqmr") != 0 || passo != 4) {
                    printf("\nVoce errou!\n");
                    printf("Digite 'n' para voltar ao menu de desafios.\n");
                    printf("Digite outra letra para tentar de novo: ");

                    char entrada[10];
                    lerTexto(entrada, sizeof(entrada));
                    escolha = entrada[0];
                }

                else {
                    printf("\nO texto original era '%s'\n", resposta);

                    printf("\nEssa foi facil!\n"
                           "Voce sabia que essa e uma das senhas mais utilizadas?\n"
                           "A verdade e que senhas como 'admin', '123456', "
                           "'password' e '112233' sao extremamente comuns, "
                           "mas nao sao nada seguras.\n\n"
                           "Hoje em dia, quem armazena dados precisa considerar "
                           "a possibilidade de vazamentos.\n"
                           "Por isso, o ideal e armazenar um hash seguro "
                           "da senha, com salt, em vez da senha original.\n"
                           "Funcoes como Argon2id sao utilizadas para "
                           "proteger senhas.\n"
                           "Tambem e importante criar senhas longas, "
                           "unicas e ativar a autenticacao em dois fatores.\n");

                    printf("\nPressione Enter para voltar ao menu de desafios.");
                    char entrada[10];
                    lerTexto(entrada, sizeof(entrada));

                    escolha = 'n';
                }

            } while (escolha != 'n' && escolha != 'N');

            break;

        case 2:
            printf("Texto: ");
            lerTexto(plaintxt, sizeof(plaintxt));

            printf("Escolha o passo: ");
            if (!lerInteiro(&passo)) {
                printf("Passo invalido!\n");
                break;
            }

            criptografarCesar(plaintxt, passo);
            printf(" > %s\n", plaintxt);
            break;

        case 3:
            printf("Texto: ");
            lerTexto(plaintxt, sizeof(plaintxt));

            printf("Escolha o passo: ");
            if (!lerInteiro(&passo)) {
                printf("Passo invalido!\n");
                break;
            }

            descriptografarCesar(plaintxt, passo);
            printf(" > %s\n", plaintxt);
            break;

        case 4:
            printf("\n = Saiba mais sobre criptografia =\n");

            printf("A criptografia e uma tecnica utilizada para "
                   "proteger informacoes.\n"
                   "A cifra de Cesar e um metodo simples que desloca "
                   "as letras do alfabeto por um numero de posicoes.\n"
                   "Por exemplo, com passo 3, a letra 'a' vira 'd'.\n"
                   "Embora seja interessante para aprender, a cifra "
                   "de Cesar nao e segura para proteger dados reais.\n"
                   "Atualmente existem algoritmos mais avancados, "
                   "como o AES, que utiliza chaves criptograficas "
                   "para proteger informacoes.\n\n");
            break;

        case 0:
            printf("Voltando ao menu principal...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (opcao != 0);
}

void limparEntrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void lerTexto(char texto[], int tamanho) {
    if (fgets(texto, tamanho, stdin) != NULL) {
        size_t tamanhoTexto = strlen(texto);

        if (tamanhoTexto > 0 && texto[tamanhoTexto - 1] == '\n') {
            texto[tamanhoTexto - 1] = '\0';
        } else {
            limparEntrada();
        }
    } else {
        texto[0] = '\0';
    }
}

int lerInteiro(int *numero) {
    char entrada[50];
    char *fim;
    long valor;

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    if (strchr(entrada, '\n') == NULL) {
        limparEntrada();
        return 0;
    }

    valor = strtol(entrada, &fim, 10);

    if (entrada == fim || valor < INT_MIN || valor > INT_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*fim)) {
        fim++;
    }

    if (*fim != '\0') {
        return 0;
    }

    *numero = (int)valor;
    return 1;
}
