# PIM II — Criptografia em C

Projeto Integrador Multidisciplinar (PIM II) — UNIP  
Curso: Análise e Desenvolvimento de Sistemas

## Sobre
Aplicação didática em linguagem C (modo console/terminal) focada em algoritmos clássicos de criptografia e conceitos de segurança digital. O sistema permite criptografar e descriptografar mensagens na prática, além de contar com uma seção educativa de curiosidades e desafios interativos.

## Funcionalidades e Algoritmos
- **Cifra de César:** Substituição por deslocamento numérico no alfabeto.
- **Cifra de Atbash:** Substituição por inversão direta do alfabeto.
- **Cifra de Transposição Colunar:** Reorganização de caracteres utilizando matrizes e palavra-chave (com visualização passo a passo da matriz no terminal).
- **Módulo Didático:** Textos explicativos sobre a história das cifras e conceitos de segurança (como preenchimento de matriz/padding).
- **Modo Desafio:** Jogos rápidos no terminal para o usuário tentar descobrir o texto original a partir de dicas.

## Como Compilar e Executar
Para compilar o projeto via terminal (utilizando o GCC):

```bash
gcc main.c -o criptografia
