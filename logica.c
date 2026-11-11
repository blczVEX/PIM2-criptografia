#include <stdio.h>
#include <string.h>
void criptografarCesar(char palavra[], int passo);
void descriptografarCesar(char palavra[], int passo);
void saibaMais();

int main() {
	char palavra[50];
	int opcao = 0;
	printf("\n = Bem vindo(a) =\n");
	printf("\nOla! Este programa tem o objetivo de ensinar, de maneira "
	       "ludica, um pouco sobre criptografia.\nPara comecar, voce deve"
	       "informar a palavra/frase a ser criptografada.\nNos usamos a cifra "
	       "de Cesar, que consiste em apenas fazer que cada letra seja "
	       "representada pela que esta a uma certa distancia dela.\nIsso e "
	       "definido pelo que aqui chamaremos de passo. Um passo 4, por exemplo, "
	       "transforma um 'a' em 'd', 'batata' em 'edxdxd', e assim por diante. "
	       "essa cifra trata o alfabeto como um circulo, tal que, estando no 'z' "
	       "e tendo passo 2, a letra cifrada é 'b'.\n");
	do {
		printf("1 - Definir o plaintext (texto nao cifrado)\n");
		printf("2 - Criptografar\n");
		printf("3 - Descriptografar\n");
		printf("4 - Saiba mais\n");
		printf("0 - Sair\n");
		printf("Escolha: ");
		scanf("%d", &opcao);
		switch (opcao) {

		case 1:
			printf("Texto: ");
			scanf("%s", &palavra);
			break;
		case 2:
			printf("Escolha o passo: ");
			scanf("%d", &opcao);
			criptografarCesar(palavra, -3);
			printf(" > %s\n", palavra);
			break;
		case 3:
			descriptografarCesar(palavra, -3);
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
		}
	} while (opcao != 0);
	return 0;
}

void criptografarCesar(char palavra[], int passo) {
	if (passo > 26) passo %= 26;
	if (passo < 0) passo += 26;
	for (int i = 0; i < strlen(palavra); i++) {
		if (palavra[i] >= 'a' && palavra[i] <= 'z')
			palavra[i] = ((palavra[i] - 'a' + passo) % 26) + 'a';

		else if (palavra[i] >= 'A' && palavra[i] <= 'Z')
			palavra[i] = ((palavra[i] - 'A' + passo) % 26) + 'A';

		else {
			printf("Caracter invalido: %c", palavra[i]);
			break;
		}
	}
}

void descriptografarCesar(char palavra[], int passo) {
	if (passo > 26) passo %= 26;
	if (passo < 0) passo += 26;

	for (int i = 0; i < strlen(palavra); i++) {
		if (palavra[i] >= 'a' && palavra[i] <= 'z')
			palavra[i] = ((palavra[i] - 'a' - passo + 26) % 26) + 'a';

		else if (palavra[i] >= 'A' && palavra[i] <= 'Z')
			palavra[i] = ((palavra[i] - 'A' - passo + 26) % 26) + 'A';

		else {
			printf("Caracter invalido: %c", palavra[i]);
			break;
		}
	}
}

void saibaMais() {
	char plaintxt[50];
	char chute[50];
	char resposta[50];
	int opcao = 0;
	int passo = 0;
	do {
		printf("\n = Descubra o texto real para saber mais sobre criptografia! =\n"
		       "Dica: todas as cifras são baseadas na cifra de César");
		printf("1 - Por que e como fazer senhas seguras?\n");
		printf("2 - Criptografar\n");
		printf("3 - Descriptografar\n");
		printf("4 - Saiba mais\n");
		printf("0 - Sair\n");
		printf("Escolha: ");
		scanf("%d", &opcao);
		switch (opcao) {

		case 1:
			char escolha = ' ';
			do {
				char plaintxt[] = "admin";
				char resposta[] = "admin";
				printf("O texto cifrado é: ehqmr\n");
				printf("Digite o texto que voce acha que foi cifrado:\n");
				scanf("%s", &chute);
				printf("Agora digite o passo usado para gerar este texto:\n");
				scanf("%d", &passo);

				criptografarCesar(chute, passo);
				criptografarCesar(resposta, passo);

				if (strcmp(resposta, chute) != 0 || chute[1] != resposta[1]) {
					printf("Você errou!\nDigite 'n' para voltar ao menu de desafios.\n"
					       "Digite outra letra para tentar de novo.\n");
					scanf(" %c", &escolha);
				}
				else {
					printf("O texto original era '%s'\n", chute);
					printf("Essa foi fácil!\n"
					       "Você sabia que essa é uma das senhas mais utilizadas atualmente?\n"
					       "A verdade é que senhas como essa, '123456', 'password', '112233', "
					       "são extremamente comuns, mas não são nada seguras.\n"
					       "Hoje em dia, aqueles que armazenam dados trabalham com a ideia "
					       "de que eles serão vazados. O que é guardado em um banco não"
					       " é a sua senha, mas uma versão dela que foi criptografada através de diversos protocolos.");
					printf("Digite Enter para voltar ao menu de desafios.\n");
					scanf(" %c", &escolha);
					escolha = 'n';
				}
			} while (escolha != 'n');
			break;
		case 2:
			printf(" > %s\n", plaintxt);
			break;
		case 3:
			printf("Palavra: ");
			scanf("%s", &plaintxt);
			break;
		case 0:
			printf("Saindo...\n");
			break;
		default:
			printf("Opcao invalida!\n");
		}
	} while (opcao != 0);


}
