# CriptoLab — Ferramenta Didática de Criptografia em C

> **Projeto Integrador Multidisciplinar II (PIM II)**  
> Curso Superior de Tecnologia em Análise e Desenvolvimento de Sistemas — **UNIP**

---

## 📌 Sobre o Projeto
O **CriptoLab** é uma aplicação desenvolvida em linguagem C para terminal (linha de comando) com foco em **educação e conscientização digital**. O objetivo do software é demonstrar de forma didática o funcionamento de cifras clássicas da história da computação e a relevância da proteção de dados na internet.

O sistema integra a manipulação prática de mensagens, módulos educativos com curiosidades históricas e desafios de decodificação.

---

## 🔐 Algoritmos Implementados
1. **Cifra de César:** Substituição monoalfabética baseada no deslocamento fixo de caracteres na tabela ASCII.
2. **Cifra de Substituição:** Permutação e mapeamento de caracteres conforme chave pré-definida.
3. **Cifra de Transposição:** Reorganização posicional dos caracteres mantendo sua composição original.

---

## 🚀 Funcionalidades
- **Menu Interativo e Modular:** Navegação estruturada em submenus no console via laços de repetição (`do-while`) e controle de fluxo (`switch-case`).
- **Validação de Entradas:** Tratamento de entradas do usuário para impedir mensagens vazias e entradas inválidas.
- **Módulo Didático & Desafios:** Área interativa com desafios práticos de decodificação e curiosidades históricas.
- **Processamento Bidirecional:** Rotinas dedicadas para criptografar e descriptografar textos informados pelo usuário.

---

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C (Padrão C99 / C11)
- **Interface:** Terminal / Linha de Comando (CLI)
- **Controle de Versão:** Git e GitHub

---

## 💻 Estrutura e Execução

O projeto consolida as rotinas de interface e os motores matemáticos de criptografia em um arquivo central:

* `main.c` — Contém a função principal `main()`, fluxo de menus interativos, validações de entrada, módulos didáticos e as rotinas dos algoritmos de cifragem.

### Execução
Após a compilação no ambiente de desenvolvimento:
- **Windows:**
  ```cmd
  .\criptolab.exe
