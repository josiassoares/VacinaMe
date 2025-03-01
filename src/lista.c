#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/lista.h"

TipoLista *criaLista()
{
    TipoLista *novaLista = (TipoLista *)malloc(sizeof(TipoLista));

    if (novaLista != NULL)
    {
        novaLista->primeiro = NULL;
        novaLista->ultimo = NULL;
        novaLista->quantidade = 0;
    }

    return novaLista;
}

void liberaLista(TipoLista *lista)
{
    if (lista != NULL)
    {

        while (lista->primeiro != NULL)
        {
            TipoMembroLista *membroAuxiliar;
            membroAuxiliar = lista->primeiro;
            lista->primeiro = lista->primeiro->proximo;
            free(membroAuxiliar);
        }

        free(lista);
    }
}

void resetarLista(TipoLista *lista)
{
    liberaLista(lista);
    lista = criaLista();
}

int listaVazia(TipoLista *lista)
{
    if (lista == NULL)
        return 1;
    if (lista->primeiro == NULL)
        return 1;
    return 0;
}

int insereListaInicio(TipoLista *lista, Cidadao dadosCidadao)
{
    if (lista == NULL)
        return 0;

    TipoMembroLista *novoMembro = (TipoMembroLista *)malloc(sizeof(TipoMembroLista));
    if (novoMembro == NULL)
        return 0;

    novoMembro->cidadao = dadosCidadao;

    if (listaVazia(lista))
    {
        lista->primeiro = novoMembro;
        lista->primeiro->anterior = NULL;
        lista->ultimo = novoMembro;
    }
    else
    {
        novoMembro->proximo = lista->primeiro;
        lista->primeiro->anterior = novoMembro;
        lista->primeiro = novoMembro;
    }
    lista->ultimo->proximo = NULL;
    lista->quantidade++;
    return 1;
}

int insereListaFinal(TipoLista *lista, Cidadao dadosCidadao)
{
    if (lista == NULL)
        return 0;

    TipoMembroLista *novoMembro = (TipoMembroLista *)malloc(sizeof(TipoMembroLista));
    if (novoMembro == NULL)
        return 0;

    novoMembro->cidadao = dadosCidadao;

    if (listaVazia(lista))
    {
        free(novoMembro);
        return insereListaInicio(lista, dadosCidadao);
    }
    else
    {
        lista->ultimo->proximo = novoMembro;
        novoMembro->anterior = lista->ultimo;
        lista->ultimo = novoMembro;
        lista->ultimo->proximo = NULL;
        lista->quantidade++;
        return 1;
    }
}

int removeListaInicio(TipoLista *lista)
{
    if (lista == NULL)
        return 0;
    if ((lista->primeiro) == NULL)
        return 0;

    TipoMembroLista *membroAuxiliar = lista->primeiro;
    lista->primeiro = membroAuxiliar->proximo;

    if (membroAuxiliar->proximo != NULL)
    {
        membroAuxiliar->proximo->anterior = NULL;
    }

    lista->quantidade--;
    free(membroAuxiliar);
    return 1;
}

int removeListaFinal(TipoLista *lista)
{
    if (lista == NULL)
        return 0;
    if ((lista->primeiro) == NULL)
        return 0;

    TipoMembroLista *membroAuxiliar = lista->ultimo;

    if (membroAuxiliar == lista->primeiro)
    {
        free(membroAuxiliar);
        return removeListaInicio(lista);
    }
    else
    {
        lista->ultimo->anterior->proximo = NULL;
        lista->ultimo = lista->ultimo->anterior;
        lista->quantidade--;
        free(membroAuxiliar);
        return 1;
    }
}

void exibeLista(TipoLista *lista)
{
    if (lista->quantidade == 0)
    {
        printf("\n\t!!! Não há nenhum cidadão com os critérios informados !!!\n");
        return;
    }

    TipoMembroLista *membroAuxiliar = lista->primeiro;
    char nomeVacina[14];

    printf(" IDADE\t  NOME\t\t\t\t\t\t CPF\t       EMAIL\t\t\t      VACINA\n");
    while (membroAuxiliar != NULL)
    {
        switch (membroAuxiliar->cidadao.codigoVacina)
        {
        case 1:
            strcpy(nomeVacina, "Coronavac");
            break;
        case 2:
            strcpy(nomeVacina, "Covishield");
            break;
        case 3:
            strcpy(nomeVacina, "Pfizer");
            break;
        case 4:
            strcpy(nomeVacina, "Janssen");
            break;
        default:
            strcpy(nomeVacina, "Não Vacinado");
            break;
        }

        printf("\n %-4d     %-45s  %-12s  %-30s %-14s", membroAuxiliar->cidadao.idade, membroAuxiliar->cidadao.nome, membroAuxiliar->cidadao.cpf, membroAuxiliar->cidadao.email, nomeVacina);

        membroAuxiliar = membroAuxiliar->proximo;
    }
}

void criarListaPrioridade(TipoLista *lista, TipoLista *listaAux)
{
    resetarLista(listaAux);
    TipoMembroLista *membroAuxiliar = lista->primeiro;

    while (membroAuxiliar != NULL)
    {
        if (membroAuxiliar->cidadao.grupoPrioritario == 1)
        {
            insereListaInicio(listaAux, membroAuxiliar->cidadao);
        }
        membroAuxiliar = membroAuxiliar->proximo;
    }
}
