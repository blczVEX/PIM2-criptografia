#include <stdio.h>
#include <string.h>

void menuCriptografia(void);
void submenuCesar(void);
void submenuAtbash(void);
void submenuTransposicao(void);
void menuCuriosidades(void);
void menuDesafio(void);

void criptografarCesar(char mensagem[], int deslocamento, char textoCifrado[]);
void descriptografarCesar(char textoCifrado[], int deslocamento, char mensagemOriginal[]);

void criptografarAtbash(char mensagem[], char textoCifrado[]);
void descriptografarAtbash(char mensagem[], char textoCifrado[]);

char paraMinusculo(char c);
void limparQuebraLinha(char str[]);
void limparBuffer(void);
void obterOrdemChave(const char chave[], int ordem[], int colunas);
void criptografarTransposicao(char mensagem[], char chave[], char textoCifrado[], int exibirMatrizes);
void descriptografarTransposicao(char textoCifrado[], char chave[], char mensagemOriginal[]);

int main() {
    int opcaoPrincipal = -1;

    do {
        printf("\n============================================\n");
        printf("          SISTEMA DE CRIPTOGRAFIA           \n");
        printf("============================================\n");
        printf("1 - Criptografar e Descriptografar (Cesar / Transposicao)\n");
        printf("2 - Curiosidades sobre Criptografia\n");
        printf("3 - Desafio: Descubra o Texto Original\n");
        printf("0 - Sair do Programa\n");
        printf("--------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcaoPrincipal) != 1) {
            opcaoPrincipal = -1;
        }
        limparBuffer();

        switch (opcaoPrincipal) {
            case 1:
                menuCriptografia();
                break;
            case 2:
                menuCuriosidades();
                break;
            case 3:
                menuDesafio();
                break;
            case 0:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
            default:
                printf("\n[!] Opcao invalida! Escolha entre 0 e 3.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}

// SUBMENU 1: ESCOLHA DO MÉTODO DE CRIPTOGRAFIA / DESCRIPTOGRAFIA
void menuCriptografia(void) {
    int opcao = -1;

    do {
        printf("\n--- [ MENU: MODALIDADES DE CRIPTOGRAFIA ] ---\n");
        printf("1 - Cifra de Cesar (Substituicao por deslocamento)\n");
        printf("2 - Cifra de Atbash (Substituicao por inversao)\n");
        printf("3 - Cifra de Transposicao Colunar (Matriz com chave)\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha o metodo: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                submenuCesar();
                break;
            case 2:
                submenuAtbash();
                break;
            case 3:
                submenuTransposicao();
                break;
            case 0:
                printf("\nRetornando ao Menu Principal...\n");
                break;
            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void submenuCesar(void) {
    char palavra[100] = "";
    char textoCifrado[100] = "";
    char textoDecifrado[100] = "";
    int deslocamento = 0;
    int opcao = -1;

    do {
        printf("\n--- [ CIFRA DE CESAR ] ---\n");
        printf("1 - Criptografar mensagem\n");
        printf("2 - Descriptografar texto cifrado\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("\nDigite a mensagem (plaintext): ");
                fgets(palavra, sizeof(palavra), stdin);
                limparQuebraLinha(palavra);

                printf("Digite o deslocamento (chave numerica, ex: 3): ");
                scanf("%d", &deslocamento);
                limparBuffer();

                criptografarCesar(palavra, deslocamento, textoCifrado);
                printf("\n>>> Texto Cifrado (Cesar): \"%s\"\n", textoCifrado);
                break;

            case 2:
                printf("\nDigite o texto cifrado (ou Enter para usar o ultimo gerado): ");
                char entrada[100];
                fgets(entrada, sizeof(entrada), stdin);
                limparQuebraLinha(entrada);

                if (strlen(entrada) > 0) {
                    strcpy(textoCifrado, entrada);
                }

                printf("Digite o deslocamento usado na criptografia: ");
                scanf("%d", &deslocamento);
                limparBuffer();

                if (strlen(textoCifrado) == 0) {
                    printf("\n[!] Nenhum texto cifrado informado!\n");
                } else {
                    descriptografarCesar(textoCifrado, deslocamento, textoDecifrado);
                    printf("\n>>> Texto Original Restaurado (Cesar): \"%s\"\n", textoDecifrado);
                }
                break;

            case 0:
                break;

            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void submenuAtbash(void) {
    char mensagem[100] = "";
    char textoCifrado[100] = "";
    int opcao = -1;

    do {
        printf("\n--- [ SUBMENU: CIFRA DE ATBASH ] ---\n");
        printf("1 - Criptografar mensagem\n");
        printf("2 - Descriptografar mensagem\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("\nDigite a mensagem para criptografar: ");
                fgets(mensagem, sizeof(mensagem), stdin);
                limparQuebraLinha(mensagem);

                criptografarAtbash(mensagem, textoCifrado);
                printf("\n[>] Texto Cifrado: %s\n", textoCifrado);
                break;

            case 2:
                printf("\nDigite o texto cifrado para descriptografar: ");
                fgets(textoCifrado, sizeof(textoCifrado), stdin);
                limparQuebraLinha(textoCifrado);

                descriptografarAtbash(mensagem, textoCifrado);
                printf("\n[>] Mensagem Original: %s\n", mensagem);
                break;

            case 0:
                printf("\nVoltando ao menu de criptografia...\n");
                break;

            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void submenuTransposicao(void) {
    char palavra[100] = "";
    char chave[30] = "";
    char textoCifrado[150] = "";
    char textoDecifrado[150] = "";
    int opcao = -1;

    do {
        printf("\n--- [ CIFRA DE TRANSPOSICAO COLUNAR ] ---\n");
        printf("1 - Criptografar mensagem\n");
        printf("2 - Descriptografar texto cifrado\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("\nDigite a mensagem (plaintext): ");
                fgets(palavra, sizeof(palavra), stdin);
                limparQuebraLinha(palavra);

                printf("Digite a palavra-chave (sem espacos): ");
                fgets(chave, sizeof(chave), stdin);
                limparQuebraLinha(chave);

                if (strlen(palavra) == 0 || strlen(chave) == 0) {
                    printf("\n[!] A mensagem e a chave nao podem estar vazias!\n");
                } else {
                    criptografarTransposicao(palavra, chave, textoCifrado, 1);
                    printf("\n>>> Texto Cifrado (Transposicao): \"%s\"\n", textoCifrado);
                }
                break;

            case 2:
                printf("\nDigite o texto cifrado (ou Enter para usar o ultimo gerado): ");
                char entradaCifrada[150];
                fgets(entradaCifrada, sizeof(entradaCifrada), stdin);
                limparQuebraLinha(entradaCifrada);

                if (strlen(entradaCifrada) > 0) {
                    strcpy(textoCifrado, entradaCifrada);
                }

                printf("Digite a palavra-chave (ou Enter para usar a ultima chave): ");
                char entradaChave[30];
                fgets(entradaChave, sizeof(entradaChave), stdin);
                limparQuebraLinha(entradaChave);

                if (strlen(entradaChave) > 0) {
                    strcpy(chave, entradaChave);
                }

                if (strlen(textoCifrado) == 0 || strlen(chave) == 0) {
                    printf("\n[!] Texto cifrado ou palavra-chave ausentes!\n");
                } else {
                    descriptografarTransposicao(textoCifrado, chave, textoDecifrado);
                    printf("\n>>> Texto Restaurado (Transposicao): \"%s\"\n", textoDecifrado);
                }
                break;

            case 0:
                break;

            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// SUBMENU 2: CURIOSIDADES
void menuCuriosidades(void) {
    int opcao = -1;

    do {
        printf("\n--- [ MENU: CURIOSIDADES DA CRIPTOGRAFIA ] ---\n");
        printf("1 - A historia da Cifra de Cesar\n");
        printf("2 - Como funciona a Cifra de Transposicao Colunar?\n");
        printf("3 - Por que preencher celulas vazias com letras aleatorias?\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha um topico: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("\n[Curiosidade 1 - Cifra de Cesar]\n");
                printf("Diferente do que muitos pensam, não foi criada pelo imperador \n");
                printf("romano Julio Cesar para se comunicar com seus generais. Seu\n");
                printf("primeiro uso registrado apenas foi atribuido a ele. \n");
                printf("Ela substitui cada letra do texto por outra deslocada um\n");
                printf("numero fixo de posicoes no alfabeto (relatos dizem que Cesar)\n");
                printf("utilizava deslocamento 3)\n");
                break;

            case 2:
                printf("\n[Curiosidade 2 - Cifra de Transposicao]\n");
                printf("Enquanto a Cifra de Cesar troca uma letra por outra,\n");
                printf("a cifra de transposicao mantem as letras originais da mensagem,\n");
                printf("mas embaralha suas posicoes usando uma matriz e uma palavra-chave\n");
                printf("para reordenar as colunas em ordem alfabetica.\n");
                break;

            case 3:
                printf("\n[Curiosidade 3 - Caracteres Aleatorios (Padding)]\n");
                printf("Se a mensagem nao preencher toda a ultima linha da matriz, o tamanho\n");
                printf("das colunas revelaria pistas sobre a chave. Preencher os espacos\n");
                printf("restantes com letras aleatorias mantem a matriz completa e dificulta\n");
                printf("a quebra da criptografia.\n");
                break;

            case 0:
                printf("\nRetornando ao Menu Principal...\n");
                break;

            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// SUBMENU 3: DESAFIO DE ACERTAR O TEXTO ORIGINAL
void menuDesafio(void) {
    char segredoCesar[] = "criptografia";
    int chaveCesar = 4;
    char cifradoCesar[100] = "";

    char segredoTransp[] = "seguranca"; // 9 letras
    char chaveTransp[] = "SOL";         // 3 colunas (sem sobras)
    char cifradoTransp[100] = "";

    char palpite[100] = "";
    int opcao = -1;

    criptografarCesar(segredoCesar, chaveCesar, cifradoCesar);
    criptografarTransposicao(segredoTransp, chaveTransp, cifradoTransp, 0);

    do {
        printf("\n--- [ DESAFIO: DESCUBRA O TEXTO ORIGINAL ] ---\n");
        printf("1 - Desafio Nivel 1: Cifra de Cesar\n");
        printf("2 - Desafio Nivel 2: Cifra de Transposicao\n");
        printf("0 - Voltar ao Menu Principal\n");
        printf("Escolha o desafio: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("\n[Desafio 1 - Cifra de Cesar]\n");
                printf("Texto Cifrado : \"%s\"\n", cifradoCesar);
                printf("Dica          : Deslocamento de %d posicoes para frente.\n", chaveCesar);
                printf("Qual e o texto original? ");
                fgets(palpite, sizeof(palpite), stdin);
                limparQuebraLinha(palpite);

                if (strcmp(palpite, segredoCesar) == 0) {
                    printf("\n[PARABENS!] Voce acertou o Desafio de Cesar!\n");
                } else {
                    printf("\n[X] Incorreto! Tente voltar %d letras no alfabeto para cada caractere.\n", chaveCesar);
                }
                break;

            case 2:
                printf("\n[Desafio 2 - Cifra de Transposicao]\n");
                printf("Texto Cifrado : \"%s\"\n", cifradoTransp);
                printf("Palavra-Chave : \"%s\" (Ordem alfabetica das colunas: L - O - S)\n", chaveTransp);
                printf("Qual e o texto original? ");
                fgets(palpite, sizeof(palpite), stdin);
                limparQuebraLinha(palpite);

                if (strcmp(palpite, segredoTransp) == 0) {
                    printf("\n[PARABENS!] Voce acertou o Desafio de Transposicao!\n");
                } else {
                    printf("\n[X] Incorreto! Dica: monte uma matriz de 3 colunas (S-O-L) e desordene de L-O-S para S-O-L.\n");
                }
                break;

            case 0:
                printf("\nRetornando ao Menu Principal...\n");
                break;

            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// FUNÇÕES DA CIFRA DE CÉSAR
void criptografarCesar(char mensagem[], int deslocamento, char textoCifrado[]) {
    int i = 0;
    int shift = (deslocamento % 26 + 26) % 26;

    while (mensagem[i] != '\0') {
        char c = mensagem[i];
        if (c >= 'a' && c <= 'z') {
            textoCifrado[i] = 'a' + (c - 'a' + shift) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            textoCifrado[i] = 'A' + (c - 'A' + shift) % 26;
        } else {
            textoCifrado[i] = c;
        }
        i++;
    }
    textoCifrado[i] = '\0';
}

void descriptografarCesar(char textoCifrado[], int deslocamento, char mensagemOriginal[]) {
    // Descriptografar em César equivale a deslocar no sentido inverso (26 - deslocamento)
    int shiftInverso = (26 - (deslocamento % 26)) % 26;
    criptografarCesar(textoCifrado, shiftInverso, mensagemOriginal);
}

// FUNÇÕES DA CIFRA DE SUBSTITUIÇÃO ATBASH

void criptografarAtbash(char mensagem[], char textoCifrado[]){
    int i = 0;

    while (mensagem[i] != '\0') {
        char c = mensagem[i];
        if (c >= 'a' && c <= 'z') {
            textoCifrado[i] = 'z' - (c - 'a');
        } else if (c >= 'A' && c <= 'Z') {
            textoCifrado[i] = 'Z' - (c - 'A');
        } else {
            textoCifrado[i] = c;
        }
        i++;
    }
    textoCifrado[i] = '\0';
}

void descriptografarAtbash(char mensagem[], char textoCifrado[]){
    int i = 0;

    while (textoCifrado[i] != '\0') {
        char c = textoCifrado[i];
        if (c >= 'a' && c <= 'z') {
            mensagem[i] = 'z' - (c - 'a');
        } else if (c >= 'A' && c <= 'Z') {
            mensagem[i] = 'Z' - (c - 'A');
        } else {
            mensagem[i] = c;
        }
        i++;
    }
    mensagem[i] = '\0';
}

// FUNÇÕES DA CIFRA DE TRANSPOSIÇÃO E UTILITÁRIOS

void limparQuebraLinha(char str[]) {
    str[strcspn(str, "\n")] = '\0';
}

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char paraMinusculo(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

void obterOrdemChave(const char chave[], int ordem[], int colunas) {
    for (int i = 0; i < colunas; i++) {
        ordem[i] = i;
    }
    
    for (int i = 0; i < colunas - 1; i++) {
        for (int j = 0; j < colunas - i - 1; j++) {
            if (paraMinusculo(chave[ordem[j]]) > paraMinusculo(chave[ordem[j + 1]])) {
                int temp = ordem[j];
                ordem[j] = ordem[j + 1];
                ordem[j + 1] = temp;
            }
        }
    }
}

void criptografarTransposicao(char mensagem[], char chave[], char textoCifrado[], int exibirMatrizes) {
    int colunas = strlen(chave);
    int tamMsg = strlen(mensagem);
    
    if (colunas == 0) return;

    int linhasMsg = (tamMsg + colunas - 1) / colunas;
    int totalLinhas = linhasMsg + 1;

    char matriz[totalLinhas][colunas];
    char matrizOrdenada[totalLinhas][colunas];

    // 1. Primeira linha recebe a palavra-chave
    for (int c = 0; c < colunas; c++) {
        matriz[0][c] = chave[c];
    }

    // 2. Semente pseudoaleatória baseada na mensagem e chave
    unsigned int semente = tamMsg + colunas;
    for (int i = 0; i < tamMsg; i++) {
        semente = semente * 31 + mensagem[i];
    }

    // Preenche a mensagem e completa células restantes com letras aleatórias
    int idx = 0;
    for (int r = 1; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            if (idx < tamMsg) {
                matriz[r][c] = mensagem[idx++];
            } else {
                semente = (semente * 1103515245 + 12345) & 0x7fffffff;
                matriz[r][c] = 'a' + (semente % 26);
            }
        }
    }

    if (exibirMatrizes) {
        printf("\n1. Matriz Inicial (Chave + Mensagem + Letras Aleatorias):\n");
        for (int r = 0; r < totalLinhas; r++) {
            for (int c = 0; c < colunas; c++) {
                printf("[%c] ", matriz[r][c]);
            }
            printf("\n");
        }
    }

    // 3. Reorganiza as colunas em ordem alfabética da chave
    int ordem[colunas];
    obterOrdemChave(chave, ordem, colunas);

    for (int novaCol = 0; novaCol < colunas; novaCol++) {
        int colOriginal = ordem[novaCol];
        for (int r = 0; r < totalLinhas; r++) {
            matrizOrdenada[r][novaCol] = matriz[r][colOriginal];
        }
    }

    if (exibirMatrizes) {
        printf("\n2. Matriz com Colunas Reorganizadas (Ordem Alfabetica da Chave):\n");
        for (int r = 0; r < totalLinhas; r++) {
            for (int c = 0; c < colunas; c++) {
                printf("[%c] ", matrizOrdenada[r][c]);
            }
            printf("\n");
        }
    }

    // 4. Extrai o texto cifrado
    idx = 0;
    for (int r = 1; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            textoCifrado[idx++] = matrizOrdenada[r][c];
        }
    }
    textoCifrado[idx] = '\0';
}

void descriptografarTransposicao(char textoCifrado[], char chave[], char mensagemOriginal[]) {
    int colunas = strlen(chave);
    int tamCifrado = strlen(textoCifrado);
    
    if (colunas == 0) return;

    int linhasMsg = (tamCifrado + colunas - 1) / colunas;
    int totalLinhas = linhasMsg + 1;

    char matrizOrdenada[totalLinhas][colunas];
    char matrizOriginal[totalLinhas][colunas];

    int ordem[colunas];
    obterOrdemChave(chave, ordem, colunas);

    // 1. Monta a matriz com a chave ordenada e o texto cifrado
    for (int c = 0; c < colunas; c++) {
        matrizOrdenada[0][c] = chave[ordem[c]];
    }

    int idx = 0;
    for (int r = 1; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            matrizOrdenada[r][c] = (idx < tamCifrado) ? textoCifrado[idx++] : ' ';
        }
    }

    // 2. Desfaz a permutação voltando cada coluna para seu índice original
    for (int colOrdenada = 0; colOrdenada < colunas; colOrdenada++) {
        int colOriginal = ordem[colOrdenada];
        for (int r = 0; r < totalLinhas; r++) {
            matrizOriginal[r][colOriginal] = matrizOrdenada[r][colOrdenada];
        }
    }

    // Exibe a matriz restaurada
    printf("\nMatriz Restaurada (Estado Original):\n");
    for (int r = 0; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            printf("[%c] ", matrizOriginal[r][c]);
        }
        printf("\n");
    }

    // 3. Reconstrói a mensagem original
    idx = 0;
    for (int r = 1; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            mensagemOriginal[idx++] = matrizOriginal[r][c];
        }
    }
    mensagemOriginal[idx] = '\0';
}