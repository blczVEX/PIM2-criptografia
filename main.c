#include <stdio.h>
#include <string.h>

// Funcoes de menus e navegacao
void menuCriptografia(void);
void submenuCesar(void);
void submenuAtbash(void);
void submenuTransposicao(void);
void menuCuriosidades(void);
void menuDesafio(void);

// funcoes da Cifra de Cesar
void criptografarCesar(char mensagem[], int deslocamento, char textoCifrado[]);
void descriptografarCesar(char textoCifrado[], int deslocamento, char mensagemOriginal[]);

// funcoes da Cifra de Atbash
void criptografarAtbash(char mensagem[], char textoCifrado[]);
void descriptografarAtbash(char mensagem[], char textoCifrado[]);

// funcoes da Cifra de Transposicao e utilitarios
char paraMinusculo(char c);
void limparQuebraLinha(char str[]);
void limparBuffer(void);
int contemApenasNumeros(char str[]);
void obterOrdemChave(const char chave[], int ordem[], int colunas);
void criptografarTransposicao(char mensagem[], char chave[], char textoCifrado[], int exibirMatrizes);
void descriptografarTransposicao(char textoCifrado[], char chave[], char mensagemOriginal[], int tamOriginal);

int main() {
    int opcaoPrincipal = -1;

    // Laco principal que mantem o programa rodando ate o usuario escolher 0
    do {
        printf("\n============================================\n");
        printf("          SISTEMA DE CRIPTOGRAFIA           \n");
        printf("============================================\n");
        printf("1 - Criptografar e Descriptografar (Cesar / Atbash / Transposicao)\n");
        printf("2 - Curiosidades sobre Criptografia\n");
        printf("3 - Desafio: Descubra o Texto Original\n");
        printf("0 - Sair do Programa\n");
        printf("--------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        // Verifica se a leitura do numero inteiro foi bem-sucedida
        if (scanf("%d", &opcaoPrincipal) != 1) {
            opcaoPrincipal = -1; // Define valor invalido caso o usuario digite letras
        }
        limparBuffer(); // Limpa o buffer do teclado para evitar loop infinito

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

// SUBMENU 1: ESCOLHA DO METODO DE CRIPTOGRAFIA / DESCRIPTOGRAFIA
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

// Submenu dedicado para operar a Cifra de Cesar
void submenuCesar(void) {
    // Vetores inicializados vazios para evitar lixo de memoria
    char palavra[100] = "";
    char textoCifrado[100] = "";
    char textoDecifrado[100] = "";
    char entrada[100] = "";
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

                // Impede que o usuario envie texto vazio ou apenas numeros
                if (strlen(palavra) == 0 || contemApenasNumeros(palavra)) {
                    printf("\n[!] Digite uma mensagem valida com letras (numeros nao sofrem deslocamento)!\n");
                    break;
                }

                printf("Digite o deslocamento (chave numerica, ex: 3): ");
                // Insiste na leitura enquanto o usuario digitar letras em vez de numeros
                while (scanf("%d", &deslocamento) != 1) {
                    printf("[!] Entrada invalida! Digite apenas numeros para o deslocamento: ");
                    limparBuffer();
                }
                limparBuffer();

                criptografarCesar(palavra, deslocamento, textoCifrado);
                printf("\n>>> Texto Cifrado (Cesar): \"%s\"\n", textoCifrado);
                break;

            case 2:
                printf("\nDigite o texto cifrado (ou Enter para usar o ultimo gerado): ");
                fgets(entrada, sizeof(entrada), stdin);
                limparQuebraLinha(entrada);

                // Se o usuario digitou algo novo, valida e atualiza o textoCifrado
                if (strlen(entrada) > 0) {
                    if (contemApenasNumeros(entrada)) {
                        printf("\n[!] Texto invalido! Digite um texto cifrado com letras ou aperte apenas Enter.\n");
                        break;
                    }
                    strcpy(textoCifrado, entrada);
                }

                // Verifica se realmente existe algum texto cifrado salvo antes de continuar
                if (strlen(textoCifrado) == 0) {
                    printf("\n[!] Nenhum texto cifrado informado ou salvo anteriormente!\n");
                    break;
                }

                printf("Digite o deslocamento usado na criptografia: ");
                // Protecao contra letras na leitura do deslocamento
                while (scanf("%d", &deslocamento) != 1) {
                    printf("[!] Entrada invalida! Digite apenas numeros para o deslocamento: ");
                    limparBuffer();
                }
                limparBuffer();

                descriptografarCesar(textoCifrado, deslocamento, textoDecifrado);
                printf("\n>>> Texto Original Restaurado (Cesar): \"%s\"\n", textoDecifrado);
                break;

            case 0:
                break;

            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// Submenu dedicado para operar a Cifra de Atbash
void submenuAtbash(void) {
    char mensagem[100] = "";
    char textoCifrado[100] = "";
    char textoDecifrado[100] = "";
    char entrada[100] = "";
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

                if (strlen(mensagem) == 0 || contemApenasNumeros(mensagem)) {
                    printf("\n[!] Digite uma mensagem valida com letras!\n");
                    break;
                }

                criptografarAtbash(mensagem, textoCifrado);
                printf("\n>>> Texto Cifrado (Atbash): \"%s\"\n", textoCifrado);
                break;

            case 2:
                // Permite apertar Enter para reaproveitar o ultimo texto cifrado, igual ao menu de Cesar
                printf("\nDigite o texto cifrado (ou Enter para usar o ultimo gerado): ");
                fgets(entrada, sizeof(entrada), stdin);
                limparQuebraLinha(entrada);

                if (strlen(entrada) > 0) {
                    if (contemApenasNumeros(entrada)) {
                        printf("\n[!] Texto invalido! Digite um texto cifrado com letras ou aperte apenas Enter.\n");
                        break;
                    }
                    strcpy(textoCifrado, entrada);
                }

                if (strlen(textoCifrado) == 0) {
                    printf("\n[!] Nenhum texto cifrado informado ou salvo anteriormente!\n");
                } else {
                    descriptografarAtbash(textoDecifrado, textoCifrado);
                    printf("\n>>> Texto Original Restaurado (Atbash): \"%s\"\n", textoDecifrado);
                }
                break;

            case 0:
                printf("\nVoltando ao menu de criptografia...\n");
                break;

            default:
                printf("\n[!] Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// Submenu dedicado para operar a Cifra de Transposicao Colunar
void submenuTransposicao(void) {
    char palavra[100] = "";
    char chave[30] = "";
    char textoCifrado[150] = "";
    char textoDecifrado[150] = "";
    int ultimoTamOriginal = 0; // Guarda o tamanho exato da palavra sem as letras aleatorias
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
                } else if (contemApenasNumeros(palavra) || contemApenasNumeros(chave)) {
                    printf("\n[!] Digite palavras com letras para a mensagem e para a chave!\n");
                } else {
                    // Salva quantas letras a mensagem original tinha antes de preencher a matriz
                    ultimoTamOriginal = strlen(palavra);
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
                    if (contemApenasNumeros(entradaCifrada)) {
                        printf("\n[!] Texto invalido! Digite o texto cifrado com letras ou aperte apenas Enter.\n");
                        break;
                    }
                    strcpy(textoCifrado, entradaCifrada);
                    // Se o usuario digitou um texto cifrado manualmente, usa o tamanho total dele
                    ultimoTamOriginal = strlen(textoCifrado);
                }

                printf("Digite a palavra-chave (ou Enter para usar a ultima chave): ");
                char entradaChave[30];
                fgets(entradaChave, sizeof(entradaChave), stdin);
                limparQuebraLinha(entradaChave);

                if (strlen(entradaChave) > 0) {
                    if (contemApenasNumeros(entradaChave)) {
                        printf("\n[!] Chave invalida! Digite uma palavra-chave com letras.\n");
                        break;
                    }
                    strcpy(chave, entradaChave);
                }

                if (strlen(textoCifrado) == 0 || strlen(chave) == 0) {
                    printf("\n[!] Texto cifrado ou palavra-chave ausentes!\n");
                } else {
                    descriptografarTransposicao(textoCifrado, chave, textoDecifrado, ultimoTamOriginal);
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

// SUBMENU 2: CURIOSIDADES (Parte didatica do projeto)
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
                printf("Diferente do que muitos pensam, nao foi criada pelo imperador \n");
                printf("romano Julio Cesar para se comunicar com seus generais. Seu\n");
                printf("primeiro uso registrado apenas foi atribuido a ele. \n");
                printf("Ela substitui cada letra do texto por outra deslocada um\n");
                printf("numero fixo de posicoes no alfabeto (relatos dizem que Cesar\n");
                printf("utilizava deslocamento 3).\n");
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

// SUBMENU 3: DESAFIO DE ACERTAR O TEXTO ORIGINAL (Gamificacao)
void menuDesafio(void) {
    char segredoCesar[] = "criptografia";
    int chaveCesar = 4;
    char cifradoCesar[100] = "";

    char segredoTransp[] = "seguranca"; // 9 letras
    char chaveTransp[] = "SOL";         // 3 colunas (divisao exata, sem sobras)
    char cifradoTransp[100] = "";

    char palpite[100] = "";
    int opcao = -1;

    // Prepara os textos cifrados dos desafios sem exibir as matrizes na tela (parametro 0)
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

// FUNCOES DA CIFRA DE CESAR
void criptografarCesar(char mensagem[], int deslocamento, char textoCifrado[]) {
    int i = 0;
    // Garante que o deslocamento fique entre 0 e 25, mesmo se for negativo ou maior que 26
    int shift = (deslocamento % 26 + 26) % 26;

    while (mensagem[i] != '\0') {
        char c = mensagem[i];
        // Desloca letras minusculas usando a tabela ASCII
        if (c >= 'a' && c <= 'z') {
            textoCifrado[i] = 'a' + (c - 'a' + shift) % 26;
        // Desloca letras maiusculas usando a tabela ASCII
        } else if (c >= 'A' && c <= 'Z') {
            textoCifrado[i] = 'A' + (c - 'A' + shift) % 26;
        // Mantem espacos e pontuacoes sem alteracao
        } else {
            textoCifrado[i] = c;
        }
        i++;
    }
    textoCifrado[i] = '\0'; // Finaliza a string
}

void descriptografarCesar(char textoCifrado[], int deslocamento, char mensagemOriginal[]) {
    // Descriptografar equivale a andar para tras no alfabeto (26 menos o deslocamento)
    int shiftInverso = (26 - (deslocamento % 26)) % 26;
    criptografarCesar(textoCifrado, shiftInverso, mensagemOriginal);
}

// FUNCOES DA CIFRA DE SUBSTITUICAO ATBASH
void criptografarAtbash(char mensagem[], char textoCifrado[]) {
    int i = 0;

    // Inverte o alfabeto: 'a' vira 'z', 'b' vira 'y', e assim por diante
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

void descriptografarAtbash(char mensagem[], char textoCifrado[]) {
    int i = 0;

    // A Atbash e simetrica: aplicar a mesma regra de inversao recupera o texto original
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

// FUNCOES DA CIFRA DE TRANSPOSICAO E UTILITARIOS

// Remove o '\n' (Enter) que o fgets captura no final do texto
void limparQuebraLinha(char str[]) {
    str[strcspn(str, "\n")] = '\0';
}

// Consome caracteres restantes no buffer do teclado ate encontrar o Enter
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Verifica se a string digitada possui apenas digitos numericos (0 a 9)
int contemApenasNumeros(char str[]) {
    int i = 0;
    if (str[0] == '\0') return 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return 0; // Encontrou uma letra ou simbolo, entao nao sao apenas numeros
        }
        i++;
    }
    return 1; // Todos os caracteres sao numeros
}

// Converte uma letra maiuscula para minuscula pela tabela ASCII para comparar a chave
char paraMinusculo(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

// Descobre a ordem alfabetica das letras da palavra-chave (usando Bubble Sort simples)
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

    // Calcula quantas linhas serao necessarias na matriz (arredondando para cima)
    int linhasMsg = (tamMsg + colunas - 1) / colunas;
    int totalLinhas = linhasMsg + 1; // +1 linha no topo para colocar a chave

    char matriz[totalLinhas][colunas];
    char matrizOrdenada[totalLinhas][colunas];

    // 1. Primeira linha da matriz recebe as letras da palavra-chave
    for (int c = 0; c < colunas; c++) {
        matriz[0][c] = chave[c];
    }

    // 2. Gera letras para preencher os espacos vazios da ultima linha
    unsigned int semente = tamMsg + colunas;
    for (int i = 0; i < tamMsg; i++) {
        semente = semente * 31 + mensagem[i];
    }

    // Preenche a matriz com a mensagem e completa buracos vazios com letras aleatorias
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

    // 3. Reorganiza as colunas seguindo a ordem alfabetica da chave
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

    // 4. Extrai o texto cifrado lendo a matriz ja embaralhada
    idx = 0;
    for (int r = 1; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            textoCifrado[idx++] = matrizOrdenada[r][c];
        }
    }
    textoCifrado[idx] = '\0';
}

void descriptografarTransposicao(char textoCifrado[], char chave[], char mensagemOriginal[], int tamOriginal) {
    int colunas = strlen(chave);
    int tamCifrado = strlen(textoCifrado);
    
    if (colunas == 0) return;

    int linhasMsg = (tamCifrado + colunas - 1) / colunas;
    int totalLinhas = linhasMsg + 1;

    char matrizOrdenada[totalLinhas][colunas];
    char matrizOriginal[totalLinhas][colunas];

    int ordem[colunas];
    obterOrdemChave(chave, ordem, colunas);

    // 1. Monta a matriz com a chave em ordem alfabetica e preenche com o texto cifrado
    for (int c = 0; c < colunas; c++) {
        matrizOrdenada[0][c] = chave[ordem[c]];
    }

    int idx = 0;
    for (int r = 1; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            matrizOrdenada[r][c] = (idx < tamCifrado) ? textoCifrado[idx++] : ' ';
        }
    }

    // 2. Desfaz a troca das colunas, devolvendo cada coluna para sua posicao original
    for (int colOrdenada = 0; colOrdenada < colunas; colOrdenada++) {
        int colOriginal = ordem[colOrdenada];
        for (int r = 0; r < totalLinhas; r++) {
            matrizOriginal[r][colOriginal] = matrizOrdenada[r][colOrdenada];
        }
    }

    // Exibe a matriz restaurada na tela
    printf("\nMatriz Restaurada (Estado Original):\n");
    for (int r = 0; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            printf("[%c] ", matrizOriginal[r][c]);
        }
        printf("\n");
    }

    // 3. Copia os caracteres da matriz de volta para o vetor da mensagem
    idx = 0;
    for (int r = 1; r < totalLinhas; r++) {
        for (int c = 0; c < colunas; c++) {
            mensagemOriginal[idx++] = matrizOriginal[r][c];
        }
    }
    
    // Corta a string exatamente no tamanho da palavra original para descartar as letras aleatorias de sobra
    if (tamOriginal > 0 && tamOriginal <= idx) {
        mensagemOriginal[tamOriginal] = '\0';
    } else {
        mensagemOriginal[idx] = '\0';
    }
}