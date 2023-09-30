#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

const int POSICION_INICIO = 0;

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t cantidad_elementos;
};

struct lista_iterador {
	lista_t *lista; 
    nodo_t *nodo_actual; 
};

lista_t *lista_crear()
{
	lista_t *lista = calloc(1,sizeof(lista_t));

	if(lista == NULL){
		return NULL;
	}

	return lista;
}

//TODO: pruebas caso borde lista no valida

lista_t *lista_insertar(lista_t *lista, void *elemento)
{	
	if(!lista){
		return NULL;
	}

	nodo_t *nuevo = malloc(sizeof(nodo_t));
	if(nuevo == NULL){
		return NULL;
	}
	nuevo->elemento = elemento;
	nuevo->siguiente = NULL;

	if(lista_vacia(lista)){
		lista->nodo_inicio = nuevo;
		lista->nodo_final = nuevo;
		lista->cantidad_elementos++;
		return lista;
	}

	lista->nodo_final->siguiente = nuevo;
	lista->nodo_final = nuevo;
	lista->cantidad_elementos++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)				
{
	if(!lista){
		return NULL;
	}
	if(lista_vacia(lista) || posicion >= lista->cantidad_elementos){
		return lista_insertar(lista, elemento);
	}
	if(posicion == 0){
		nodo_t *nuevo = malloc(sizeof(nodo_t));
		if(nuevo == NULL){
			return NULL;
		}
		nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo;
		nuevo->elemento = elemento;
		lista->cantidad_elementos++;
		return lista;
	}
	
	
	nodo_t *aux = lista->nodo_inicio;
	nodo_t *anterior = lista->nodo_inicio;
	nodo_t *nuevo = malloc(sizeof(nodo_t));
	if(nuevo == NULL){
		return NULL;
	}
	for(int i = 0; i < lista->cantidad_elementos;i++){
		if(i == posicion){
			anterior->siguiente = nuevo;
			nuevo->siguiente = aux;
			nuevo->elemento = elemento;
			lista->cantidad_elementos++;
			return lista;
		}
		
		anterior = aux;
		aux = aux->siguiente;
	}
	
	return NULL;
}


void *lista_quitar(lista_t *lista)
{
	if(!lista || lista_vacia(lista)){
		return NULL;
	}
	if(lista->cantidad_elementos == 1 && lista->nodo_final == lista->nodo_inicio){
		void* elemento = lista->nodo_inicio->elemento;
		lista->cantidad_elementos--;
		free(lista->nodo_inicio);
		return elemento;
	}

	nodo_t* anterior = NULL;
	nodo_t* actual = lista->nodo_inicio;

	for(int i = 0; i < lista->cantidad_elementos - 1; i++){
		anterior = actual;
		actual = actual->siguiente;
	}

	if(lista->nodo_final == actual){
		void* elemento = actual->elemento;
		anterior->siguiente = NULL;
		lista->nodo_final = anterior;
		lista->cantidad_elementos--;
		free(actual);
		return elemento;
	}

	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(!lista || lista_vacia(lista)){
		return NULL;
	}
	if(posicion == 0){
		nodo_t *aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		lista->cantidad_elementos--;
		void *elemento = aux->elemento; 
		free(aux);
		return elemento;
	}
	if(posicion >= lista->cantidad_elementos){
		return lista_quitar(lista);
	}

	nodo_t* auxiliar = lista->nodo_inicio;
	nodo_t *anterior = lista->nodo_inicio;
	
	for(int i = 0; i < lista->cantidad_elementos;i++){
		if(i == posicion){
			anterior->siguiente = auxiliar->siguiente;
			void *elemento = auxiliar->elemento;
			lista->cantidad_elementos--;
			free(auxiliar);
			return elemento;
		}

		anterior = auxiliar;
		auxiliar = auxiliar->siguiente;
	}

	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista)){
		return NULL;
	}
	nodo_t *aux = lista->nodo_inicio;
	for(int i = 0; i < lista->cantidad_elementos;i++){
		if(i == posicion){
			return aux->elemento;
		}
		aux = aux->siguiente;
	}
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	 if (lista == NULL || comparador == NULL) {
        return NULL; 
    }

    nodo_t *nodo_actual = lista->nodo_inicio;

    while (nodo_actual != NULL) {
        if (comparador(nodo_actual->elemento, contexto) == 0) {
            return nodo_actual->elemento; 
        }
        nodo_actual = nodo_actual->siguiente;
    }

    return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (!lista || lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista || lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_final->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if (lista == NULL || lista->cantidad_elementos == 0 || lista->nodo_inicio == NULL){
		return true;
	}
	return false; 
}

size_t lista_tamanio(lista_t *lista)
{
	if(lista_vacia(lista)){
		return 0;
	}
	return lista->cantidad_elementos;
}

void lista_destruir(lista_t *lista)
{
	if (lista != NULL){
		lista_destruir_todo(lista,NULL);
	}

}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(!lista){
		return;
	}
	nodo_t *aux = lista->nodo_inicio;
	for(int i = 0 ; i < lista->cantidad_elementos; i++){
		if(funcion!=NULL){
			funcion(aux->elemento);
		}
		nodo_t *liberar = aux;
		aux = aux->siguiente;
		free(liberar);
	}
	
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if(!lista){
		return NULL;
	}

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if(iterador==NULL){
		return NULL;
	}

	iterador->lista = lista;
	iterador->nodo_actual = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->nodo_actual == NULL){
		return false;
	}
	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(iterador == NULL){
		return false;
	}
	
	if(iterador->nodo_actual == iterador->lista->nodo_final){
		iterador->nodo_actual = NULL;
	}

	if(lista_iterador_tiene_siguiente(iterador)){
		iterador->nodo_actual = iterador->nodo_actual->siguiente;
		return true;
	}
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(iterador == NULL || iterador->nodo_actual == NULL){
		return NULL;
	}
	return iterador->nodo_actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if(lista == NULL || funcion == NULL){
		return 0;
	}
	size_t elementos_iterados = 0;
    nodo_t *nodo_actual = lista->nodo_inicio;

	for(int i = 0; i < lista->cantidad_elementos;i++){
		if (!funcion(nodo_actual->elemento, contexto)) {
            return elementos_iterados+1;
        }
		elementos_iterados++;
		nodo_actual = nodo_actual->siguiente;
	}

    return elementos_iterados;
}