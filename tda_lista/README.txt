TP LISTA SIMPLEMENTE ENLAZADA.
--------------------------------------------------------------------------------------------------------------------------------------
CONCEPTOS TEORICOS:

Las listas son estructuras dinamicas de nodos que pueden generarse tanto de forma recursiva (el ejemplo de las cadenitas) como semi recursiva (este TP).
Cada nodo contiene, como minimo, informacion sobre si mismo y sobre el siguiente nodo. En las estructuras semi recursivas, ademas hay referencias a los
extremos inicial y final de dicha lista, aunque esto depende tambien sobre que tipo de estructura se trabaje, por ejemplo en una pila no tiene sentido
referenciar al primer elemento, ya que siempre se trabaja sobre el último.

Hay tres tipos de lista:

Lista Simplemente enlazada: Los nodos solo conocen al siguiente elemento.
Lista Doblemente enlazada: Los nodos contienen informacion del siguiente elemento, pero ademas conocen al anterior.
Lista Circular Simplemente enlazada: El último nodo tiene referencia hacia el primero.
Lista Circular Doblemente enlazada: El último nodo tiene referencia hacia el primero, y el primero hacia el ultimo.



--------------------------------------------------------------------------------------------------------------------------------------
SOLUCION IMPLEMENTADA:

consideraciones sobre LISTA.C:

• lista_crear: solicita en heap el espacio necesario para almacenar un elemento de tipo lista_t y devuelve un puntero. Esto lo
  hace con calloc, para inicializar todos los elementos en 0 / NULL.

• nodo_crear: solicita en heap el espacio necesario para almacenar un elemento de tipo nodo_t y devuelve un puntero. Esto lo
  hace con calloc, para inicializar todos los elementos en 0 / NULL.

• lista_insertar: Inserto al final de la lista. Contemplo como caso borde que la lista este vacia, caso en el cual voy a tener que
  actualizar el nodo inicio.

• lista_insertar_al_inicio Inserto al inicio de la lista. La cree como funcion privada para reutilizarla luego en la estructura de pila.
  si la lista estaba vacia, llamo a la funcion lista insertar, para evitar reescribir codigo de forma innecesaria.

• obtener_nodo_anterior_posicion: es una funcion recursiva que devuelve el nodo anterior al que este buscando. La voy a usar, para
  actualizar el lista->nodo_ultimo al eliminar un elemento al final de la lista, o para insertar/eliminar un elemento en una posicion que no sea la
  primera o la ultima de la lista. Tambien la uso para obtener el elemento de una posicion. Tal vez hubiera sido mas entendible obtener la posicion
  buscada, pero me parecio mejor reutilizar esta funcion y a costa de tener que solicitar el posicion_anterior->siguiente->elemento, en vez de un
  posicion_actual->elemento.

• lista_insertar_en_posicion: reutilizo el codigo de insertar_al_inicio e insertar al final para los casos bordes. En caso contrario creo un nodo y
  actualizo las referencias del anterior aprovechando obtener_nodo__anterior_posicion.

• lista_borrar_primero: borra el primer elemento de la lista y actualiza las referencias en caso de corresponder. Se usa en la cola o en la destruccion
  para realizar las operaciones en tiempo constante.

• lista_borrar: borra el ultimo elemento de una lista. Como casos borde se contempla que se esten borrando el anteultimo o el ultimo elemento.

• lista_borrar_de_posicion: Se contemplaron como casos borde la eliminacion del primer o del ultimo elemento, reutilizando codigo en los mismos.
  Se considero que si no se está eliminando el primero ni el ultimo elemento es porque necesariamente la lista tiene mas de dos elementos, lo cual
  no se contempla la posibilidad de tener que actualizar los nodos de la lista en estos casos.

• lista_elemento_en_posicion: Se aprovecha la funcionalidad de lista_ultimo y lista_primero para obtener O(1) estos elementos. Para el resto se navega
  al elemento anterior con obtener_nodo_anterior_posicion y se retorna el siguiente, que seria el nodo buscado.

• lista_ultimo: retorna el ultimo elemento o NULL si la lista esta vacia.
• lista_primero: retorna el primer elemento o NULL si la lista esta vacia.

• lista_vacia: verifica que la cantidad de elementos sea 0.
• lista_elementos: retorna la cantidad de elementos de la lista o 0 en caso de error. Se usa el dato cantidad de
  elementos de la lista, para evitar validar consultando punteros (deberia ser lo mismo, si está bien implementada
  la solucion, pero se opto porque ademas considero mas entendible esta solucion).

• lista_apilar: llama a lista insertar al final.
• lista_desapilar: llama a lista borrar al final. Se tiene en cuenta que la forma de insercion de una pila es FIFO.
• lista_tope: llama lista_ultimo.

• lista_encolar: llama a insertar al final.
• lista_desencolar: llama a borrar al inicio. Se tiene en cuenta que la forma de insercion de una cola es LIFO.

• lista_destruir: borra todos los nodos llamando a borrar primero, para mantener un orden lineal para la eliminacion.

• lista_iterador_crear: solicita en heap el espacio necesario para almacenar un elemento de tipo lista_iterador_t y
  devuelve un puntero. Esto lo hace con calloc, para inicializar todos los elementos en 0 / NULL, aunque luego apunto
  a la lista y a su primer elemento.

• lista_iterador_tiene_siguiente: me fijo si el elemento actual no es nulo. Si es nulo, no puedo avanzar a un siguiente.

• lista_iterador_avanzar: Si hay siguiente, avanzo a dicho elemento.

• lista_iterador_elemento_actual: Si hay actual, muestro su dato.

• lista_iterador_destruir: como no tiene datos que se hayan generado en el heap, como los nodos de la lista, directamente
  libero al iterador.

• lista_con_cada_elemento: Si puede visitar el siguiente, procesa el dato de forma recursiva y al finalizar retorna la cantidad
  total de nodos recorridos.

--------------------------------------------------------------------------------------------------------------------------------------
consideraciones sobre PRUEBAS.C:

En las pruebas fui agregando las primitivas a medida que las iba probando. Por ejemplo, las pruebas de agregar elementos a
la lista no usan lista_elementos, sino lista->cantidad. Luego durante las pruebas de la primitiva, sí la uso. Trate de mantener
lo mas posible la legibilidad, pero variando la forma de probar lo mismo, como para garantizar en la medida de lo posible que
las estructuras se hayan generado de forma correcta y se mantenga su integridad a lo largo de la ejecucion.

Hice muchas pruebas que en principio son repetidas, pero porque son llamadas desde otras funciones, por ejemplo usar lista_insertar_en_posicion
como si fuera lista_insertar, o lista_insertar_al_inicio, pero porque por la clase de consulta me parecio que era necesario agregarlas.


--------------------------------------------------------------------------------------------------------------------------------------
Consideraciones finales luego de las entregas fallidas:

Luego del primer intento de entrega, se agregaron validaciones sobre la posibilidad de no existir la lista, el iterador externo o si es interno,
tambien verifico si la funcion visitar y el dato extra no fueron informados, porque por lo que entiendo, para este tda ambos son necesarios.

Luego del segundo reintento, se ajusto el iterador externo, para que al verificar si hay un siguiente elemento, en realidad verifique si el actual es NULL,
lo que implicaria que estoy al final de la lista.
Para el iterador interno, se reemplazo la implementacion por una recursiva, siguiendo la idea implementada durante la clase de listas, ya que el elemento
retornado por la funcion difería del obtenido recursivamente. Me gustaria entender un poco más por qué ocurrió esto. Mientras tanto, voy a estar haciendo
dibujos del heap y el stack, porque me imagino que en algun lugar el dato no es correctamente asignado.

para el tercer reintento, me equivoqué al llamar a la funcion visitar, pasando un nodo, en vez de un elemento. Aproveche para agregar una prueba sobre el
iterador interno que no recorra la lista hasta el final.
El iterador externo no entiendo el problema aun. Agregue pruebas para verificar que la cantidad de elementos recorridos coincida con la de la lista y que
los elementos actuales sean los correctos.

para el cuarto reintento lo que faltaba al final era que al avanzar retorne false si el siguiente elemento era el final de la lista.
