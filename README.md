<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# NOMBRE TP/TDA

## Repositorio de Basterra Sebastian Nahuel - 110428 - sbasterra@fi.uba.ar

- Para compilar:

```bash
línea de compilación
```

- Para ejecutar:

```bash
línea de ejecución
```

- Para ejecutar con valgrind:
```bash
make 
make valgrind-chanutron
```
---
##  Funcionamiento



---

## Respuestas a las preguntas teóricas
-Una *lista* es una estructura de datos lineal conformada de nodos los cuales almacenan un elemento y la direccion a otro nodo, estas pueden ser enlazadas o doblemente enlazadas.
 Una *pila* Es una estructura que sigue el principio de "last in first out" en donde solo se puede acceder al elemento en la parte superior de la pila.
 Una *cola* en contraparte con la pila, sigue la condicion de "first in first out" en donde los elementos que se insertan al final de la cola solo se eliminan desde el principio.

 -En mi implementacion la complejidad de insertar/obtener/eliminar nodo al final es de $O[1]$ ya que guardo en lista_t la posicion del nodo final. Sin embargo si no se guardase, la complejidad seria de $O[n]$ para listas simplemente enlazadas.
 Insertar/obtener/eliminar al principio es $O[1]$ en listas simple, y doblemente enlazadas mientras que en los vectores dinamicos es de $O[n]$, para que la complejidad de los vectores dinamicos sea de $O[1]$ se debe de eliminar la ultima posicion, o agregar elemento siempre que el vector no este lleno.

 -La complejidad computacional tanto de la cola como de la fila es de $O[1]$ para cualquiera de sus acciones ya sea de insercion como de eliminacion, ya que en ambos casos solo se puede acceder a ese ultimo/primer elemento para realizar la accion requerida y no es necesario recorrer nada.