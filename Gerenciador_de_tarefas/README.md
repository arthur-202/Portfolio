

#Visão Geral
------------
Este programa de linha de comando em C permite gerenciar uma lista de tarefas com as seguintes operações:
------------

	- Carregar e salvar tarefas em arquivo binário
	- Cadastrar nova tarefa
	- Listar todas as tarefas ou por status
	- Marcar tarefa como concluída
	- Editar dados da tarefa (descrição, data, prioridade, status)
	- Remover tarefa
	- Ordenar tarefas por data ou prioridade
	- Buscar tarefas por palavra-chave
	- Menu interativo e feedback imediato ao usuário

Estrutura do Projeto
--------------------
	src/
		main.c       - Função principal (menu e controle de fluxo)
		utils.h      - Declarações de tipos (Tarefa, Status), variáveis globais e protótipos
		utils.c      - Implementação das funções de manipulação de tarefas

Descrição dos Arquivos
----------------------
			main.c
			- Inclui headers necessários (<stdio.h>, <conio.h>, <windows.h>, "utils.h")
			- Função main(): carrega tarefas, exibe menu em loop e chama funções conforme opção
			- Uso de system("cls") para limpar tela, Sleep() para pausa e _getch() para aguardar tecla

			utils.h
			- Enum Status: PENDENTE, EM_ANDAMENTO, CONCLUIDA
			- Struct Tarefa: id, Descricao[256], data (dia, mes, ano), status, prioridade, ponteiro next
			- Variáveis globais: inicio (lista ligada), ultimo_id, nome_arquivo
			- Protótipos das funções de manipulação

			utils.c
			- carregar_tarefas(): lê de tarefas.bin, reconstrói lista e atualiza ultimo_id
			- salvar_tarefas(): grava lista atual em tarefas.bin
			- exibir_menu(), ler_inteiro(): interface básica de interação
			- status_texto(): converte enum para string
			- cadastrar_tarefa(): entrada de dados e inserção no final da lista
			- listar_tarefas(), listar_por_status(): exibição formatada das tarefas
			- marcar_concluida(), editar_tarefa(), remover_tarefa(): operações CRUD básicas
			- ordenar_tarefas(): bubble sort por data ou prioridade
			- buscar_tarefas(): pesquisa simples por substring na descrição

Como Compilar
-------------
	No Windows (MinGW ou Visual Studio):
		gcc src/main.c src/utils.c -o gerenciador.exe

Uso
---
1. Abra o prompt de comando e execute:
     gerenciador.exe
2. Escolha uma opção (1-9) no menu.
3. Siga as instruções exibidas.
4. Ao sair (opção 9), as tarefas são salvas em `tarefas.bin`.

Formato de Dados
----------------
Cada tarefa possui:
- ID: inteiro autoincremental
- Descrição: texto (até 255 caracteres)
- Data limite: dia, mês, ano
- Prioridade: 1 (baixa) a 5 (alta)
- Status: Pendente, Em Andamento, Concluída

Dependências
------------
- Windows OS
- Bibliotecas padrão (stdio.h, stdlib.h, string.h, conio.h, windows.h)
- Compilador C compatível (GCC, Clang ou MSVC)

Considerações
--------------
	- Arquivo de dados: `tarefas.bin` (binário)
	- Se `tarefas.bin` não existir ao iniciar, o programa exibe mensagem e encerra.
	- Uso de pausas (Sleep) para melhor experiência de usuário.
	- Lista ligada simples para armazenar dinamicamente tarefas.

Licença e Copyright
-------------------
© 2025 Arthur Pereira Tavares. Todos os direitos reservados.
Utilização permitida para estudos e projetos pessoais.
