#include "pa2m.h"
#include <stdio.h>
#include <string.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include <stdio.h>

typedef struct nodo nodo_t;

void prueba_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_vacia(lista), "La lista está vacía");
	lista_insertar(lista, NULL);
	pa2m_afirmar(!lista_vacia(lista), "La lista no está vacía");
	lista_destruir(lista);
	lista_t *lista_NULL = NULL;
	pa2m_afirmar(lista_vacia(lista_NULL) == true,
		     "Lista NULL devuelve vacia");
}

void prueba_crear_lista()
{
	lista_t *lista = lista_crear();
	if (lista) {
		pa2m_afirmar(lista != NULL, "la lista se creo correctamente");
		lista_destruir(lista);
	}
}

void prueba_insertar_lista_nula()
{
	lista_t *lista = NULL;
	pa2m_afirmar(lista_insertar(lista, (void *)3) == NULL,
		     "la funcion devuelve NULL si la lista es NULL");
}

void prueba_insertar_lista_vacia()
{
	lista_t *lista = lista_crear();
	void *numero = malloc(sizeof(int));
	if (numero) {
		*(int *)numero = 3;
		lista_insertar(lista, numero);
		bool encontrado = false;
		if (lista_primero(lista) == numero) {
			encontrado = true;
		}
		pa2m_afirmar(encontrado, "Añade elemento a una lista vacia");
		free(numero);
		lista_destruir(lista);
	}
}

void prueba_insertar_al_final()
{
	lista_t *lista = lista_crear();

	void *letra = malloc(sizeof(char));
	if (letra) {
		lista_insertar(lista, NULL);
		*(char *)letra = 'a';
		lista_insertar(lista, letra);
		bool encontrado = false;
		if (lista_ultimo(lista) == letra) {
			encontrado = true;
		}
		pa2m_afirmar(encontrado, "Añade elemento al final");

		free(letra);
		lista_destruir(lista);
	}
}

void prueba_lista_insertar_en_posicion()
{
	lista_t *lista = lista_crear();
	void *numero = (void *)3;
	if (lista) {
		for (int i = 0; i < 5; i++) {
			lista_insertar(lista, (void *)7);
		}
		lista_insertar_en_posicion(lista, numero, 2);
		pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == numero &&
				     lista_tamanio(lista) == 6,
			     "Se inserto en posicion");
		lista_insertar_en_posicion(lista, numero, 10);
		pa2m_afirmar(lista_tamanio(lista) == 7,
			     "Se añade al final si la posicion es invalida");
		lista_t *nul = NULL;
		pa2m_afirmar(lista_insertar_en_posicion(nul, (void *)1, 6) ==
				     NULL,
			     "Devuelve NULL si la lista es NULL");
	}
	lista_destruir(lista);
}

void prueba_lista_quitar()
{
	lista_t *lista = lista_crear();
	if (lista) {
		lista_insertar(lista, (void *)1);

		pa2m_afirmar(
			lista_quitar(lista) == (void *)1,
			"se eliminó cuando hay un solo nodo correctamente");
		for (int i = 0; i < 3; i++) {
			lista_insertar(lista, (void *)1);
		}
		lista_quitar(lista);
		pa2m_afirmar(lista_tamanio(lista) == 2,
			     "se eliminó un nodo del final correctamente");
	}
	lista_destruir(lista);
	lista_t *lista_2 = NULL;
	pa2m_afirmar(lista_quitar(lista_2) == NULL,
		     "Si se envia lista NULL devuelve NULL");
}

void prueba_lista_quitar_de_posicion()
{
	lista_t *lista = lista_crear();
	if (lista) {
		for (int i = 0; i < 3; i++) {
			lista_insertar(lista, (void *)1);
		}
		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		//(1,1,1,5,3)

		pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == (void *)1,
			     "Se eliminola primera posicion correctamente");
		//(1,1,5,3)
		pa2m_afirmar(
			lista_quitar_de_posicion(lista, 50) == (void *)3,
			"Se elimino la ultima posicion al poner una invalida");
		//(1,1,5)
		pa2m_afirmar(
			lista_quitar_de_posicion(lista, 2) == (void *)5,
			"Se elimino la posicion elegida valida correctamente");

		lista_destruir(lista);
	}
}

void prueba_lista_elemento_en_posicion()
{
	lista_t *lista = lista_crear();
	if (lista) {
		for (int i = 0; i < 3; i++) {
			lista_insertar(lista, (void *)1);
		}
		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		pa2m_afirmar(
			lista_elemento_en_posicion(lista, 3) == (void *)5,
			"El elemento en la posicion valida elegida es el correcto");
		pa2m_afirmar(
			lista_elemento_en_posicion(lista, 4) == (void *)3,
			"El elemento en la posicion valida elegida es el correcto");
		pa2m_afirmar(
			lista_elemento_en_posicion(lista, 2) == (void *)1,
			"El elemento en la posicion valida elegida es el correcto");

		pa2m_afirmar(lista_elemento_en_posicion(lista, 50) == NULL,
			     "Posicion invalida devuelve NULL");
		lista_t *lista_NULL = NULL;
		pa2m_afirmar(lista_elemento_en_posicion(lista_NULL, 3) == NULL,
			     "Lista invalida devuelve NULL");
		lista_destruir(lista);
	}
}

int comparador(void *comp1, void *comp2)
{
	if (comp1 == comp2) {
		return 0;
	} else {
		return 1;
	}
}

void prueba_lista_buscar_elemento(int (*comparador)(void *, void *))
{
	lista_t *lista = lista_crear();
	if (lista) {
		for (int i = 0; i < 3; i++) {
			lista_insertar(lista, (void *)1);
		}

		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		pa2m_afirmar(lista_buscar_elemento(lista, comparador,
						   (void *)5) == (void *)5,
			     "Elemento valido encontrado");
		pa2m_afirmar(
			lista_buscar_elemento(lista, comparador, (void *)9) ==
				NULL,
			"Busqueda de elemento que no se encuentra en lista devuelve NULL");
		lista_t *lista_NULL = NULL;
		pa2m_afirmar(lista_buscar_elemento(lista_NULL, comparador,
						   (void *)1) == NULL,
			     "Lista NULL funcion devuelve NULL");
		lista_destruir(lista);
	}
}

void prueba_lista_primero()
{
	lista_t *lista = lista_crear();
	if (lista) {
		lista_insertar(lista, (void *)1);
		pa2m_afirmar(lista_primero(lista) == (void *)1,
			     "Un solo elemento lo devuelve correctamente");

		for (int i = 0; i < 3; i++) {
			lista_insertar(lista, (void *)1);
		}
		pa2m_afirmar(lista_primero(lista) == (void *)1,
			     "4 elementos, devuelve el primero correctamente");

		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		pa2m_afirmar(lista_primero(lista) == (void *)1,
			     "6 elementos, devuelve el primero correctamente");
		lista_t *lista_NULL = NULL;
		pa2m_afirmar(lista_primero(lista_NULL) == NULL,
			     "Lista NULL funcion devuelve NULL");
		lista_destruir(lista);
		lista_t *lista_2 = lista_crear();
		if (lista_2) {
			pa2m_afirmar(lista_primero(lista_2) == NULL,
				     "Lista vacia la funcion devuelve NULL");
			lista_destruir(lista_2);
		}
	}
}

void prueba_lista_ultimo()
{
	lista_t *lista = lista_crear();
	if (lista) {
		lista_insertar(lista, (void *)1);
		pa2m_afirmar(lista_ultimo(lista) == (void *)1,
			     "Un solo elemento lo devuelve correctamente");

		for (int i = 0; i < 3; i++) {
			lista_insertar(lista, (void *)1);
		}
		pa2m_afirmar(lista_ultimo(lista) == (void *)1,
			     "4 elementos, devuelve el ultimo correctamente");

		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		//(1,1,1,5,3)
		pa2m_afirmar(lista_ultimo(lista) == (void *)3,
			     "6 elementos, devuelve el ultimo correctamente");
		lista_t *lista_NULL = NULL;
		pa2m_afirmar(lista_ultimo(lista_NULL) == NULL,
			     "Lista NULL funcion devuelve NULL");
		lista_destruir(lista);
		lista_t *lista_2 = lista_crear();
		if (lista_2) {
			pa2m_afirmar(lista_ultimo(lista_2) == NULL,
				     "Lista vacia la funcion devuelve NULL");
			lista_destruir(lista_2);
		}
	}
}

void pruebas_lista_tamanio()
{
	lista_t *lista = lista_crear();
	if (lista) {
		for (int i = 0; i < 3; i++) {
			lista_insertar(lista, (void *)1);
		}
		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		pa2m_afirmar(lista_tamanio(lista) == 5,
			     "5 elementos en la lista");
		lista_insertar(lista, (void *)3);
		pa2m_afirmar(lista_tamanio(lista) == 6,
			     "6 elementos en la lista");
		lista_insertar(lista, (void *)3);
		pa2m_afirmar(lista_tamanio(lista) == 7,
			     "7 elementos en la lista");

		lista_t *lista_NULL = NULL;
		pa2m_afirmar(lista_tamanio(lista_NULL) == 0,
			     "Lista NULL no tiene elementos");
		lista_destruir(lista);
		lista_t *lista_2 = lista_crear();
		if (lista_2) {
			pa2m_afirmar(lista_tamanio(lista_2) == 0,
				     "Lista vacia la no tiene elementos");
			lista_destruir(lista_2);
		}
	}
}

void prueba_lista_iterador_crear()
{
	lista_t *lista = lista_crear();
	if (lista) {
		lista_iterador_t *itera = lista_iterador_crear(lista);
		pa2m_afirmar(itera != NULL, "Crea iterador de lista vacia");
		lista_iterador_destruir(itera);
		lista_insertar(lista, (void *)1);
		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		//(1,5,3)
		lista_iterador_t *iterador = lista_iterador_crear(lista);
		pa2m_afirmar(lista_iterador_elemento_actual(iterador) ==
				     (void *)1,
			     "El iterador se creo correctamente");
		lista_destruir(lista);
		lista_iterador_destruir(iterador);
		lista_t *lista_NULL = NULL;
		pa2m_afirmar(lista_iterador_crear(lista_NULL) == NULL,
			     "Devuelve NULL si la lista es NULL");
	}
}

void prueba_lista_iterador_tiene_siguiente()
{
	lista_t *lista = lista_crear();
	if (lista) {
		lista_iterador_t *iterador = lista_iterador_crear(lista);
		lista_insertar(lista, (void *)1);
		pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador),
			     "Devuelve False si no tiene siguiente");
		lista_iterador_destruir(iterador);
		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		//(1,5,3)
		lista_iterador_t *iterador_2 = lista_iterador_crear(lista);
		pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_2),
			     "Devuelve True si tiene siguiente");
		lista_destruir(lista);
		lista_iterador_destruir(iterador_2);
	}
}

void prueba_lista_iterador_avanzar()
{
	lista_t *lista = lista_crear();
	if (lista) {
		lista_insertar(lista, (void *)1);
		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)3);
		lista_iterador_t *iterador = lista_iterador_crear(lista);
		pa2m_afirmar(
			lista_iterador_avanzar(iterador) &&
				lista_iterador_elemento_actual(iterador) ==
					(void *)5,
			"Avanza y devuelve true correctamente con el primer nodo");
		pa2m_afirmar(
			lista_iterador_avanzar(iterador) &&
				lista_iterador_elemento_actual(iterador) ==
					(void *)3,
			"Avanza y devuelve true correctamente con el segundo nodo");
		pa2m_afirmar(
			!lista_iterador_avanzar(iterador),
			"Devuelve False y no avanza si no se puede avanzar mas");
		lista_destruir(lista);
		lista_iterador_destruir(iterador);
	}
}

void prueba_lista_iterador_elemento_actual()
{
	lista_t *lista = lista_crear();
	if (lista) {
		lista_insertar(lista, (void *)1);
		lista_insertar(lista, (void *)5);
		lista_insertar(lista, (void *)6);
		lista_insertar(lista, (void *)2);
		lista_insertar(lista, (void *)3);
		lista_iterador_t *iterador = lista_iterador_crear(lista);
		pa2m_afirmar(lista_iterador_elemento_actual(iterador) ==
				     (void *)1,
			     "Devuelve correctamente el primer elemento");
		lista_iterador_avanzar(iterador);
		pa2m_afirmar(lista_iterador_elemento_actual(iterador) ==
				     (void *)5,
			     "Devuelve correctamente el segundo elemento");
		lista_iterador_avanzar(iterador);
		pa2m_afirmar(lista_iterador_elemento_actual(iterador) ==
				     (void *)6,
			     "Devuelve correctamente el tercer elemento");
		lista_iterador_avanzar(iterador);
		pa2m_afirmar(lista_iterador_elemento_actual(iterador) ==
				     (void *)2,
			     "Devuelve correctamente el cuarto elemento");
		lista_iterador_avanzar(iterador);
		pa2m_afirmar(lista_iterador_elemento_actual(iterador) ==
				     (void *)3,
			     "Devuelve correctamente el ultimo elemento");
		lista_iterador_avanzar(iterador);
		pa2m_afirmar(lista_iterador_elemento_actual(iterador) == NULL,
			     "Si se llama al final, devolvera NULL");
		lista_destruir(lista);
		lista_iterador_destruir(iterador);
	}
}

bool funcion(void *comp1, void *comp2)
{
	if (comp1 == comp2) {
		return false;
	}
	return true;
}

void prueba_lista_con_cada_elemento(bool (*funcion)(void *, void *))
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion, (void *)6) == 0,
		     "No recorre nada si la lista esta vacia");
	lista_insertar(lista, (void *)6);
	lista_insertar(lista, (void *)7);
	lista_insertar(lista, (void *)5);
	lista_insertar(lista, (void *)2);
	lista_insertar(lista, (void *)1);
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion, (void *)6) == 1,
		     "Itera correctamente 1 elemento");
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion, (void *)7) == 2,
		     "Itera correctamente 2 elementos");
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion, (void *)5) == 3,
		     "Itera correctamente 3 elementos");
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion, (void *)2) == 4,
		     "Itera correctamente 4 elementos");
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion, (void *)1) == 5,
		     "Itera correctamente 5 elementos");
	pa2m_afirmar(lista_con_cada_elemento(lista, funcion, (void *)8) == 5,
		     "Recorre todo si no encuentra el elemento ");

	lista_destruir(lista);
}

void prueba_cola_crear()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "La cola se creo correctamente");
	cola_destruir(cola);
}

void prueba_cola_encolar()
{
	cola_t *cola = cola_crear();
	if (cola) {
		pa2m_afirmar(
			cola_encolar(cola, (void *)1) == cola &&
				cola_tamanio(cola) == 1 &&
				cola_frente(cola) == (void *)1,
			"Se añadio el primer elemento a la cola correctamente");
		pa2m_afirmar(
			cola_encolar(cola, (void *)3) == cola &&
				cola_tamanio(cola) == 2 &&
				cola_frente(cola) == (void *)1,
			"Se añadio el segundo elemento a la cola correctamente");
		pa2m_afirmar(
			cola_encolar(cola, (void *)3) == cola &&
				cola_tamanio(cola) == 3 &&
				cola_frente(cola) == (void *)1,
			"Se añadio el tercer elemento a la cola correctamente");
		pa2m_afirmar(
			cola_encolar(cola, (void *)3) == cola &&
				cola_tamanio(cola) == 4 &&
				cola_frente(cola) == (void *)1,
			"Se añadio el cuarto elemento a la cola correctamente");
		pa2m_afirmar(
			cola_encolar(cola, (void *)3) == cola &&
				cola_tamanio(cola) == 5 &&
				cola_frente(cola) == (void *)1,
			"Se añadio el ultimo elemento a la cola correctamente");
		cola_t *cola2 = NULL;
		pa2m_afirmar(cola_encolar(cola2, (void *)3) == NULL,
			     "La funcion devuelve NULL si la cola era NULL");
	}
	cola_destruir(cola);
}

void prueba_cola_desencolar()
{
	cola_t *cola = cola_crear();
	if (cola) {
		for (int i = 0; i < 4; i++) {
			cola_encolar(cola, (void *)1);
		}
		cola_encolar(cola, (void *)3);

		pa2m_afirmar(cola_desencolar(cola) == (void *)1 &&
				     cola_tamanio(cola) == 4,
			     "Se desencolo correctamente el primer elemento");
		pa2m_afirmar(cola_desencolar(cola) == (void *)1 &&
				     cola_tamanio(cola) == 3,
			     "Se desencolo correctamente otro elemento");
		pa2m_afirmar(cola_desencolar(cola) == (void *)1 &&
				     cola_tamanio(cola) == 2,
			     "Se desencolo correctamente otro elemento");
		pa2m_afirmar(cola_desencolar(cola) == (void *)1 &&
				     cola_tamanio(cola) == 1,
			     "Se desencolo correctamente otro elemento");
		pa2m_afirmar(cola_desencolar(cola) == (void *)3 &&
				     cola_tamanio(cola) == 0,
			     "Se desencolo correctamente el ultimo elemento");

		pa2m_afirmar(
			cola_desencolar(cola) == NULL &&
				cola_tamanio(cola) == 0,
			"Devuelve NULL si no hay nada mas para desencolar");

		cola_destruir(cola);
	}
}

void prueba_cola_frente()
{
	cola_t *cola = cola_crear();
	if (cola) {
		cola_encolar(cola, (void *)3);
		pa2m_afirmar(cola_frente(cola) == (void *)3,
			     "El primer elemento es correcto");
		cola_desencolar(cola);
		pa2m_afirmar(cola_frente(cola) == NULL,
			     "Si no hay elementos devuelve NULL");

		cola_destruir(cola);
	}
}

void prueba_cola_tamanio()
{
	cola_t *cola = cola_crear();
	if (cola) {
		pa2m_afirmar(cola_tamanio(cola) == 0,
			     "Si no hay elementos la lista esta vacia");
		cola_encolar(cola, (void *)3);
		pa2m_afirmar(cola_tamanio(cola) == 1,
			     "Un solo elemento verificado");
		cola_encolar(cola, (void *)3);
		pa2m_afirmar(cola_tamanio(cola) == 2,
			     "Dos elementos verificados");
		cola_encolar(cola, (void *)3);
		pa2m_afirmar(cola_tamanio(cola) == 3,
			     "Tres elementos verificados");
		cola_encolar(cola, (void *)3);
		pa2m_afirmar(cola_tamanio(cola) == 4,
			     "cuatro elementos verificados");

		cola_destruir(cola);
	}
}

void prueba_cola_vacia()
{
	cola_t *cola = cola_crear();
	if (cola) {
		pa2m_afirmar(cola_vacia(cola), "La cola esta vacia");
		cola_encolar(cola, (void *)1);
		pa2m_afirmar(!cola_vacia(cola), "La cola no esta vacia");
	}
	cola_destruir(cola);
}

void prueba_pila_crear()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "la pila se creo correctamente");
	pila_destruir(pila);
}

void prueba_pila_apilar()
{
	pila_t *pila = pila_crear();
	if (pila) {
		pa2m_afirmar(pila_apilar(pila, (void *)1) == pila &&
				     pila_tamanio(pila) == 1 &&
				     pila_tope(pila) == (void *)1,
			     "Un elemento apilado correctamente");
		pa2m_afirmar(pila_apilar(pila, (void *)2) == pila &&
				     pila_tamanio(pila) == 2 &&
				     pila_tope(pila) == (void *)2,
			     "Dos elementos apilado correctamente");
		pa2m_afirmar(pila_apilar(pila, (void *)3) == pila &&
				     pila_tamanio(pila) == 3 &&
				     pila_tope(pila) == (void *)3,
			     "Tres elementos apilado correctamente");
		pa2m_afirmar(pila_apilar(pila, (void *)4) == pila &&
				     pila_tamanio(pila) == 4 &&
				     pila_tope(pila) == (void *)4,
			     "Catro elementos apilado correctamente");
		pa2m_afirmar(pila_apilar(pila, (void *)5) == pila &&
				     pila_tamanio(pila) == 5 &&
				     pila_tope(pila) == (void *)5,
			     "Cinco elementos apilado correctamente");
		pila_destruir(pila);
	}
}

void prueba_pila_desapilar()
{
	pila_t *pila = pila_crear();
	if (pila) {
		pila_apilar(pila, (void *)1);
		pila_apilar(pila, (void *)2);
		pila_apilar(pila, (void *)3);
		pila_apilar(pila, (void *)4);
		pila_apilar(pila, (void *)5);
		pa2m_afirmar(pila_desapilar(pila) == (void *)5 &&
				     pila_tamanio(pila) == 4,
			     "Se desapilo correctamente un elemento");
		pa2m_afirmar(pila_desapilar(pila) == (void *)4 &&
				     pila_tamanio(pila) == 3,
			     "Se desapilo correctamente otro elemento");
		pa2m_afirmar(pila_desapilar(pila) == (void *)3 &&
				     pila_tamanio(pila) == 2,
			     "Se desapilo correctamente otro elemento");
		pa2m_afirmar(pila_desapilar(pila) == (void *)2 &&
				     pila_tamanio(pila) == 1,
			     "Se desapilo correctamente otro elemento");
		pa2m_afirmar(pila_desapilar(pila) == (void *)1 &&
				     pila_tamanio(pila) == 0,
			     "Se desapilo correctamente otro elemento");
		pa2m_afirmar(pila_desapilar(pila) == NULL &&
				     pila_tamanio(pila) == 0,
			     "Devuelve NULL si la pila esta vacia");

		pila_destruir(pila);
	}
}

void prueba_pila_tope()
{
	pila_t *pila = pila_crear();
	if (pila) {
		pa2m_afirmar(pila_tope(pila) == NULL,
			     "Devuelve NULL si la pila esta vacia");

		pila_apilar(pila, (void *)1);
		pa2m_afirmar(
			pila_tope(pila) == (void *)1,
			"Devuelve el elemento correcto luego de apilar 1 elemento");
		pila_apilar(pila, (void *)2);
		pa2m_afirmar(
			pila_tope(pila) == (void *)2,
			"Devuelve el elemento correcto luego de apilar 2 elementos");
		pila_apilar(pila, (void *)3);
		pa2m_afirmar(
			pila_tope(pila) == (void *)3,
			"Devuelve el elemento correcto luego de apilar 3 elementos");
		pila_apilar(pila, (void *)4);
		pa2m_afirmar(
			pila_tope(pila) == (void *)4,
			"Devuelve el elemento correcto luego de apilar 4 elementos");
		pila_apilar(pila, (void *)5);
		pa2m_afirmar(
			pila_tope(pila) == (void *)5,
			"Devuelve el elemento correcto luego de apilar 5 elementos");
		pila_destruir(pila);
	}
}

void prueba_pila_tamanio()
{
	pila_t *pila = pila_crear();
	if (pila) {
		pa2m_afirmar(pila_tamanio(pila) == 0,
			     "Devuelve 0 si la pila esta vacia");
		pila_apilar(pila, (void *)1);
		pa2m_afirmar(pila_tamanio(pila) == 1,
			     "Devuelve 1 si tiene un elemento");
		pila_apilar(pila, (void *)2);
		pa2m_afirmar(pila_tamanio(pila) == 2,
			     "Devuelve 2 si tiene dos elementos");
		pila_apilar(pila, (void *)3);
		pa2m_afirmar(pila_tamanio(pila) == 3,
			     "Devuelve 3 si tiene tres elementos");
		pila_apilar(pila, (void *)4);
		pa2m_afirmar(pila_tamanio(pila) == 4,
			     "Devuelve 4 si tiene cuatro elementos");
		pila_apilar(pila, (void *)5);
		pa2m_afirmar(pila_tamanio(pila) == 5,
			     "Devuelve 5 si tiene cinco elementos");
		pila_destruir(pila);
	}
}

void prueba_pila_vacia()
{
	pila_t *pila = pila_crear();
	if (pila) {
		pa2m_afirmar(pila_vacia(pila), "La pila esta vacia");
		pila_apilar(pila, (void *)1);
		pa2m_afirmar(!pila_vacia(pila), "La pila esta no vacia");
		pila_destruir(pila);
	}
}

int main()
{
	pa2m_nuevo_grupo("\nLISTA_VACIA");
	prueba_lista_vacia();
	pa2m_nuevo_grupo("\nCREAR LISTA");
	prueba_crear_lista();
	pa2m_nuevo_grupo("\nLISTA INSERTAR");
	prueba_insertar_lista_nula();
	prueba_insertar_lista_vacia();
	prueba_insertar_al_final();
	pa2m_nuevo_grupo("\nLISTA INSERTAR EN POSICION");
	prueba_lista_insertar_en_posicion();
	pa2m_nuevo_grupo("\nLISTA QUITAR");
	prueba_lista_quitar();
	pa2m_nuevo_grupo("\nLISTA QUITAR DE POSICION");
	prueba_lista_quitar_de_posicion();
	pa2m_nuevo_grupo("\nLISTA ELEMENTO EN POSICION");
	prueba_lista_elemento_en_posicion();
	pa2m_nuevo_grupo("\nLISTA BUSCAR ELEMENTO");
	prueba_lista_buscar_elemento(comparador);
	pa2m_nuevo_grupo("\nLISTA PRIMERO");
	prueba_lista_primero();
	pa2m_nuevo_grupo("\nLISTA ULTIMO");
	prueba_lista_ultimo();
	pa2m_nuevo_grupo("\nLISTA TAMANIO");
	pruebas_lista_tamanio();
	pa2m_nuevo_grupo("\nLISTA ITERADOR CREAR");
	prueba_lista_iterador_crear();
	pa2m_nuevo_grupo("\nLISTA ITERADOR TIENE SIGUIENTE");
	prueba_lista_iterador_tiene_siguiente();
	pa2m_nuevo_grupo("\nLISTA ITERADOR AVANZAR");
	prueba_lista_iterador_avanzar();
	pa2m_nuevo_grupo("\nLISTA ITERADOR ELEMENTO ACTUAL");
	prueba_lista_iterador_elemento_actual();
	pa2m_nuevo_grupo("\nLISTA CON CADA ELEMENTO");
	prueba_lista_con_cada_elemento(funcion);
	pa2m_nuevo_grupo("\nCOLA CREAR");
	prueba_cola_crear();
	pa2m_nuevo_grupo("\nCOLA ENCOLAR");
	prueba_cola_encolar();
	pa2m_nuevo_grupo("\nCOLA DESENCOLAR");
	prueba_cola_desencolar();
	pa2m_nuevo_grupo("\nCOLA FRENTE");
	prueba_cola_frente();
	pa2m_nuevo_grupo("\nCOLA TAMAÑO");
	prueba_cola_tamanio();
	pa2m_nuevo_grupo("\nCOLA VACIA");
	prueba_cola_vacia();
	pa2m_nuevo_grupo("PILA CREAR");
	prueba_pila_crear();
	pa2m_nuevo_grupo("PILA APILAR");
	prueba_pila_apilar();
	pa2m_nuevo_grupo("PILA DESAPILAR");
	prueba_pila_desapilar();
	pa2m_nuevo_grupo("PILA TOPE");
	prueba_pila_tope();
	pa2m_nuevo_grupo("PILA TAMAÑO");
	prueba_pila_tamanio();
	pa2m_nuevo_grupo("PILA VACIA");
	prueba_pila_vacia();

	return pa2m_mostrar_reporte();
}
