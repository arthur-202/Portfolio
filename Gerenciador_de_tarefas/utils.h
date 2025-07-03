#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>    

typedef enum { PENDENTE, EM_ANDAMENTO, CONCLUIDA } Status;

typedef struct Tarefa {
    int id;
    char Descricao[256];
    int dia, mes, ano;
    Status status;
    int prioridade;
    struct Tarefa *proxima;
} Tarefa;

// variáveis globais
extern Tarefa *inicio;
extern int ultimo_id;
extern const char *nome_arquivo;

// Protótipos de função
bool carregar_tarefas(void);
void salvar_tarefas(void);
void exibir_menu(void);
int ler_inteiro(void);
void cadastrar_tarefa(void);
const char* status_texto(Status s);
void listar_tarefas(void);
void listar_por_status(void);
void marcar_concluida(void);
void editar_tarefa(void);
void remover_tarefa(void);
void ordenar_tarefas(void);
void buscar_tarefas(void);

#endif

