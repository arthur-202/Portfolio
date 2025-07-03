/**
 * @file utils.c
 * @brief Implementacao de funcoes de gerenciamento de tarefas.
 * 
 * Este arquivo contem a implementacao de um sistema de gerenciamento de tarefas
 * utilizando uma lista encadeada e persistencia em arquivo binario.
 */

#include "utils.h"
#include <windows.h> // apenas para 1 sleep

// Variaveis globais
Tarefa *inicio = NULL;   ///< Ponteiro para o primeiro elemento da lista de tarefas
int ultimo_id = 0;       ///< Contador para geracao de IDs unicos
const char *nome_arquivo = "tarefas.bin";   ///< Nome do arquivo de armazenamento
 
/**
 * @brief Carrega tarefas do arquivo binario para a memoria
 * 
 * Le o arquivo binario especificado e reconstrói a lista encadeada de tarefas.
 * Atualiza o contador de IDs com o maior ID encontrado.
 * 
 * @return true se o carregamento foi bem-sucedido, false caso contrario
 */
bool carregar_tarefas(void) {
    FILE *arq = fopen(nome_arquivo, "rb");
    if (!arq) {
        printf("O arquivo %s nao existe!\n como sou bonzinho, vou criá-lo para você!\n", nome_arquivo);
	Sleep(3000);
        return false;
    }
    Tarefa temp;
    while (fread(&temp, sizeof(Tarefa), 1, arq)) {
        Tarefa *nova = malloc(sizeof(Tarefa));
        if (!nova) {
            printf("Erro de alocacao de memoria!\n");
            fclose(arq);
            return false;
        }
        *nova = temp;
        nova->proxima = inicio;
        inicio = nova;
        if (temp.id > ultimo_id) ultimo_id = temp.id;
    }
    fclose(arq);
    return true;
}

/**
 * @brief Salva todas as tarefas da memoria em arquivo binario
 * 
 * Escreve toda a lista encadeada de tarefas no arquivo binario especificado.
 */
void salvar_tarefas(void) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }
    Tarefa *atual = inicio;
    while (atual) {
        fwrite(atual, sizeof(Tarefa), 1, arquivo);
        atual = atual->proxima;
    }
    fclose(arquivo);
}

/**
 * @brief Exibe o menu principal de opcoes
 * 
 * Mostra as operacoes disponiveis para o usuario.
 */
void exibir_menu(void) {
    printf("1. Nova tarefa\n");
    printf("2. Listar todas\n");
    printf("3. Listar por status\n");
    printf("4. Marcar concluida\n");
    printf("5. Editar tarefa\n");
    printf("6. Remover tarefa\n");
    printf("7. Ordenar tarefas\n");
    printf("8. Buscar tarefas\n");
    printf("9. Salvar e sair\n");
    printf("Escolha uma opcao: ");
}

/**
 * @brief Le um valor inteiro da entrada padrao
 * 
 * @return O inteiro lido do teclado
 */
int ler_inteiro(void) {
    int x;
    scanf("%d", &x);
    return x;
}

/**
 * @brief Converte um valor de enumeracao Status para string
 * 
 * @param s Valor de status a ser convertido
 * @return String correspondente ao status
 */
const char* status_texto(Status s) {
    switch (s) {
        case PENDENTE: return "Pendente";
        case EM_ANDAMENTO: return "Em Andamento";
        case CONCLUIDA: return "Concluida";
        default: return "Desconhecido";
    }
}

/**
 * @brief Adiciona uma nova tarefa a lista
 * 
 * Solicita os dados da tarefa ao usuario, gera um ID unico,
 * e insere a nova tarefa no final da lista.
 */
void cadastrar_tarefa(void) {
    Tarefa *t = malloc(sizeof(Tarefa));
    if (!t) {
        printf("Erro ao alocar memoria para nova tarefa.\n");
        return;
    }
    t->id = ++ultimo_id;
    printf("Descricao: ");
    scanf(" %[^\n]", t->Descricao);
    printf("Data limite (DD MM AAAA): ");
    scanf("%d %d %d", &t->dia, &t->mes, &t->ano);
    printf("Prioridade (1 a 5): ");
    scanf("%d", &t->prioridade);
    t->status = PENDENTE;
    t->proxima = NULL;
    if (!inicio) {
        inicio = t;
    } else {
        Tarefa *aux = inicio;
        while (aux->proxima) {
            aux = aux->proxima;
        }
        aux->proxima = t;
    }
    printf("Tarefa cadastrada! ID: %d\n", t->id);
}

/**
 * @brief Lista todas as tarefas cadastradas
 * 
 * Exibe no console todas as tarefas da lista em ordem inversa
 * a de cadastro (do mais recente para o mais antigo).
 */
void listar_tarefas(void) {
    if (!inicio) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }
    Tarefa *t = inicio;
    while (t) {
        printf("[ID:%d] %s  \nDATA_ENTREGA: %02d/%02d/%04d \nPrioridade:%d \nStatus:%s\n\n",
               t->id, t->Descricao, t->dia, t->mes, t->ano,
               t->prioridade, status_texto(t->status));
        t = t->proxima;
    }
}

/**
 * @brief Lista tarefas por status
 * 
 * Solicita um status ao usuario e exibe todas as tarefas
 * que possuem o status correspondente.
 */
void listar_por_status(void) {
    printf("Status (0=Pendente,1=EmAndamento,2=Concluida): ");
    int s = ler_inteiro();
    bool achou = false;
    Tarefa *t = inicio;
    while (t) {
        if ((int)t->status == s) {
            printf("[ID:%d] %s  \nDATA_ENTREGA: %02d/%02d/%04d \nPrioridade:%d \nStatus:%s\n\n",
                   t->id, t->Descricao, t->dia, t->mes, t->ano,
                   t->prioridade, status_texto(t->status));
            achou = true;
        }
        t = t->proxima;
    }
    if (!achou) {
        printf("Nenhuma tarefa com esse status.\n");
    }
}

/**
 * @brief Altera o status de uma tarefa para "Concluida"
 * 
 * Solicita o ID da tarefa e atualiza seu status para CONCLUIDA.
 */
void marcar_concluida(void) {
    printf("ID da tarefa a marcar como concluida: ");
    int id = ler_inteiro();
    Tarefa *t = inicio;
    while (t) {
        if (t->id == id) {
            t->status = CONCLUIDA;
            printf("Tarefa marcada como concluida.\n");
            return;
        }
        t = t->proxima;
    }
    printf("ID nao encontrado.\n");
}

/**
 * @brief Edita os dados de uma tarefa existente
 * 
 * Solicita o ID da tarefa e permite editar sua descricao,
 * data limite, prioridade e status.
 */
void editar_tarefa(void) {
    printf("ID da tarefa a editar: ");
    int id = ler_inteiro();
    Tarefa *t = inicio;
    while (t) {
        if (t->id == id) {
            printf("Nova descricao: ");
            scanf(" %[^\n]", t->Descricao);
            printf("Nova data (DD MM AAAA): ");
            scanf("%d %d %d", &t->dia, &t->mes, &t->ano);
            printf("Nova prioridade (1-5): ");
            scanf("%d", &t->prioridade);
            printf("Novo status (0=Pendente,1=EmAndamento,2=Concluida): ");
            int s = ler_inteiro();
            if (s >= 0 && s <= 2) {
                t->status = (Status)s;
            }
            printf("Tarefa atualizada.\n");
            return;
        }
        t = t->proxima;
    }
    printf("ID nao encontrado.\n");
}

/**
 * @brief Remove uma tarefa da lista
 * 
 * Lista todas as tarefas, solicita um ID e remove a tarefa correspondente.
 */
void remover_tarefa(void) {
    system("cls");
    listar_tarefas();
    printf("ID da tarefa a remover: ");
    int id = ler_inteiro();
    Tarefa *t = inicio;
    Tarefa *ant = NULL;
    while (t) {
        if (t->id == id) {
            if (!ant) {
                inicio = t->proxima;
            } else {
                ant->proxima = t->proxima;
            }
            free(t);
            printf("Tarefa removida.\n");
            return;
        }
        ant = t;
        t = t->proxima;
    }
    printf("ID nao encontrado.\n");
}

/**
 * @brief Ordena as tarefas da lista
 * 
 * Ordena as tarefas por data de entrega (cronologica) ou
 * prioridade (decrescente) usando algoritmo bubble sort.
 */
void ordenar_tarefas(void) {
    if (!inicio) {
        printf("Nenhuma tarefa para ordenar.\n");
        return;
    }
    printf("Ordenar por (1=Data, 2=Prioridade): ");
    int op = ler_inteiro();
    bool trocou;
    do {
        trocou = false;
        Tarefa *atual = inicio;
        while (atual && atual->proxima) {
            int cond = 0;
            if (op == 1) {
                Tarefa *a = atual;
                Tarefa *b = atual->proxima;
                if (a->ano > b->ano) cond = 1;
                else if (a->ano == b->ano && a->mes > b->mes) cond = 1;
                else if (a->ano == b->ano && a->mes == b->mes && a->dia > b->dia) cond = 1;
            } else if (op == 2) {
                if (atual->prioridade > atual->proxima->prioridade) cond = 1;
            }
            if (cond) {
                Tarefa temp = *atual;
                *atual = *(atual->proxima);
                *(atual->proxima) = temp;
                Tarefa *aux = atual->proxima;
                atual->proxima = aux->proxima;
                aux->proxima = atual;
                trocou = true;
            } else {
                atual = atual->proxima;
            }
        }
    } while (trocou);
    printf("Tarefas ordenadas.\n");
}

/**
 * @brief Busca tarefas por palavra-chave na descricao
 * 
 * Solicita uma palavra-chave e exibe todas as tarefas cuja
 * descricao contem o termo pesquisado (case-sensitive).
 */
void buscar_tarefas(void) {
    char key[256];
    printf("Palavra-chave: ");
    scanf(" %[^\n]", key);
    Tarefa *t = inicio;
    int achou = 0;
    while (t) {
        if (strstr(t->Descricao, key) != NULL) {
            printf("[ID:%d] %s  \nDATA_ENTREGA: %02d/%02d/%04d \nPrioridade:%d \nStatus:%s\n\n",
                t->id, t->Descricao, t->dia, t->mes, t->ano,
                t->prioridade, status_texto(t->status));
            achou = 1;
        }
        t = t->proxima;
    }
    if (!achou) {
        printf("Nenhuma tarefa encontrada com essa palavra-chave.\n");
    }
}
