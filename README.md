<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# NOMBRE TP/TDA

## Repositorio de Basterra Sebastian Nahuel - 110428 - sbasterra@fi.uba.ar

- Para compilar:

```bash
gcc src/*.c --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
```

- Para ejecutar:

```bash
./a.out
```

- Para ejecutar con valgrind:
```bash
make 
make valgrind-chanutron
```
---
##  Funcionamiento

El codigo se encarga de manejar listas en general, a travez de las distintas funciones proporcionadas uno puede realizar todo tipo de acciones para el manejo de listas, utilizando nodos ubicados en memoria y liberando esta misma cuando ya no sea necesaria. 
Para recorrer los nodos en las listas creé un nodo auxiliar igualado al primer nodo de la lista, y utilizando bucles voy reemplazando el valor de este auxiliar por el de su siguiente, dependiendo la funcion y el uso que se necesite, esta iteracion termina para realizar la accion correspondiente, como quitar, añadir o listar elemento en determinada posicion dada.

Para completar la pila y cola utilice las funciones ya hechas de la lista.c, casteé los elementos y funciones de manera que puedan utilizarse correctamente en los mencionados casos de pila y cola.

                                       Diagrama de pila
<div align="center">
<img width="50%" src="https://media.discordapp.net/attachments/1073796859916722198/1157769750093500607/image.png?ex=6519d09a&is=65187f1a&hm=bca652a716cf9b9094bcf7c950c9b1f74a33bea57a724bde57b0bbd7df422144&=&width=548&height=499">
</div>

Como bien voy a explicar en el apartado de respuestas teoricas, normalmente la accion de pop con pila, es de $O(n)$ sin embargo en mi implementacion es de $O(1)$ ya que añado y elimino la primera ubicacion, asi como cuando tengo que mostrar el ultimo elemento, muestro el "primero". De esta manera podemos ahorrar complejidad.

                                     Diagrama de cola
<div align="center">
<img width="50%" src="https://cdn.discordapp.com/attachments/1073796859916722198/1157769785858343023/image.png?ex=6519d0a3&is=65187f23&hm=bf2cf9ad34bf76bd203bef74d06de38efa2d980be9f682f3960433c6921100f2&">
</div>
En la cola al igual que con la pila, utilice las funciones de la lista.c para completarla sin embaro no tuve que realizar cambios para mejorar la complejidad debido que se agregan elementos en la ultima posicion (siempre queda guardada) y se quita el elemento de la primera posicion.


---



## Respuestas a las preguntas teóricas
-Una *lista* es una estructura de datos lineal conformada de nodos los cuales almacenan un elemento y la direccion a otro nodo, estas pueden ser enlazadas o doblemente enlazadas.
 Una *pila* Es una estructura que sigue el principio de "last in first out" en donde solo se puede acceder al elemento en la parte superior de la pila.
 Una *cola* en contraparte con la pila, sigue la condicion de "first in first out" en donde los elementos que se insertan al final de la cola solo se eliminan desde el principio.

 -En mi implementacion la complejidad de insertar/obtener nodo al final es de $O[1]$ ya que guardo en lista_t la posicion del nodo final, pero para la eliminacion hay que recorrer todo nuevamente para dar con la posicion del nodo anterior al final por lo tanto seria de $O(n)$. Sin embargo si no se guardase, la complejidad seria de $O[n]$ para listas simplemente enlazadas.
 Insertar/obtener/eliminar al principio es $O[1]$ en listas simple, y doblemente enlazadas mientras que en los vectores dinamicos es de $O[n]$, para que la complejidad de los vectores dinamicos sea de $O[1]$ se debe de eliminar la ultima posicion, o agregar elemento siempre que el vector no este lleno.

 -La complejidad computacional tanto de la cola como de la fila es de $O[1]$ para cualquiera de sus acciones en mi implementacion ya sea de insercion como de eliminacion, ya que en ambos casos los elementos se encuentran en la posicion 0, y para realizar la accion requerida y no es necesario recorrer nada.