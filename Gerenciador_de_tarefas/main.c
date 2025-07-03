#include <stdio.h>
#include <stdbool.h>
#include <conio.h>     // _getch()
#include <windows.h>   // Sleep(), system("cls")
#include "utils.h"     // Declarações de funções e tipos de tarefa

/**
 * @brief Função principal do programa de gerenciamento de tarefas.
 * 
 * Carrega as tarefas salvas em arquivo, exibe o menu principal em loop
 * e executa a ação escolhida pelo usuário até que ele decida sair.
 * 
 * @param argc Número de argumentos da linha de comando (não utilizado).
 * @param argv Vetor de argumentos da linha de comando (não utilizado).
 * @return int Código de saída (0 = sucesso).
 */
int main(int argc, char **argv) {
    // Carrega tarefas previamente salvas em disco
    carregar_tarefas();

    // Loop principal: continua até o usuário escolher sair (opção 9)
    while (true) {
        system("cls");          // Limpa a tela do console
        exibir_menu();          // Mostra as opções de menu
        int opcao = ler_inteiro();  // Lê a escolha do usuário
        
        switch (opcao) {
            case 1:
                // Cadastrar nova tarefa
                system("cls");
                cadastrar_tarefa();
                Sleep(5000);    // Pausa para ver a mensagem de confirmação
                break;

            case 2:
                // Listar todas as tarefas cadastradas
                system("cls");
                listar_tarefas();
                printf("Pressione qualquer tecla para voltar ao menu... ");
                _getch();       // Aguarda tecla para retornar
                break;

            case 3:
                // Listar tarefas filtradas por status (PENDENTE, EM_ANDAMENTO, CONCLUIDA)
                system("cls");
                listar_por_status();
                printf("Pressione qualquer tecla para voltar ao menu... ");
                _getch();
                break;

            case 4:
                // Marcar uma tarefa como concluída
                system("cls");
                listar_tarefas();
                marcar_concluida();
                Sleep(3000);
                break;

            case 5:
                // Editar descrição de uma tarefa existente
                system("cls");
                listar_tarefas();
                editar_tarefa();
                Sleep(5000);
                break;

            case 6:
                // Remover uma tarefa da lista
                system("cls");
                listar_tarefas();
                remover_tarefa();
                Sleep(2000);
                break;

            case 7:
                // Ordenar tarefas (por ID, status ou outra lógica definida)
                ordenar_tarefas();
                Sleep(2000);
                break;

            case 8:
                // Buscar tarefas que contenham uma palavra-chave
                system("cls");
                buscar_tarefas();
                printf("Pressione qualquer tecla para voltar ao menu... ");
                _getch();
                break;

            case 9:
                // Sair do programa: salva tarefas e encerra
                printf("Saindo....\n");
                salvar_tarefas();
                Sleep(2000);
                return 0;

            default:
                // Opção inválida: avisa o usuário
                printf("Opção inválida.\n");
                Sleep(2000);
        }
    }

    return 0;
}

