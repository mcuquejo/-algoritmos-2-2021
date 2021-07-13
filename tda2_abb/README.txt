CONCEPTOS TEORICOS:-----------------------------------------------------------------------------------------------------------------------------------------

Árbol:
    Los árboles son estructuras parcial o totalmente recursivas. Está compuesto por un nodo, que hará de raiz, y que contendrá un puntero a un dato
    y luego una serie de punteros a sus nodos hijos, los cuales pueden ser desde dos (arbol binario) a n hijos (arbol n-ario). Armado de esta forma, el
    arbol sería totalmente recursivo. Luego, se podría separar en un struct aparte a la raiz, junto con otras variables que podrian ser de utilidad, según
    la implementación, tales como una función de destrucción.
    Entre los nodos, se pueden destacar dos tipos:
    Se llama raiz al nodo del arbol que no tiene un nodo padre. Haría de base en una estructura árbol.
    Se llaman hojas a los nodos que no apuntan a ningún nodo hijo.
    Se llaman hermanos a dos nodos que son nodos hijos del mismo nodo padre.
    Se llama camino a la secuencia de nodos que debe recorrer un nodo, para alcanzar a otro. La longitud del mismo se corresponde con la cantidad de nodos
    por los que tuvo que pasar, hasta llegar a destino. Hay un solo camino entre un nodo y un subnodo.
    Se llama profundidad a la longitud entre el nodo raiz y un nodo al que se quiera alcanzar.
    Se llama altura del árbol a la longitud entre el nodo raiz y el nodo hoja cuya longitud de camino sea la más alta.

    Hay tres formas de recorrer un árbol que son estándar:
    In orden: Sería primero acceder a los hijos izquierdos, luego al nodo en cuestión, por último a los hijos derechos.
    Pre orden: Sería acceder a los hijos izquierdos, luego a los hijos derechos y por último al nodo en cuestión.
    Post orden: Se accede primero al nodo en cuestión. Luego a los hijos izquierdos y por último a los derechos.

    De las mismas se puede invertir el recorrido de los hijos. Es decir, derecho antes que izquierdo.
    También se puede recorrer por niveles, que sería primero la raiz, luego la primera serie de hijos, y así hasta llegar hasta las hojas.

    Por último, se puede hablar de una propiedad de balanceo, la cual está relacionada con la altura de cada uno de los hijos de un nodo. Un arbol está balanceado
    cuando diferencia de altura entre sus hijos es de entre 0 y 1 nodo. Si la misma es mayor, se dice que el árbol no se encuentra balanceado.
    Un arbol desbalanceado se ve afectado en el orden en que se ejecutan sus operaciones. En el peor de los casos, un arbol puede verse como una lista, por lo que
    su recorrido sera de Orden Lineal.


Árbol Binario:
    Un árbol binario es un subtipo de árbol, el cual en cada nodo tiene referencias a un hijo izquierdo y un hijo derecho. El mismo cumple
    con todas las condiciones detalladas anteriormente.

    Como particularidad, por su condicion binaria, estando balanceado, la altura puede ser definida como el Log2(n), donde n es la cantidad de nodos.

    Este tipo de estructuras sigue teniendo una referencia a elementos sin un orden definido.

Árbol binario de búsqueda:
    Es un Árbol binario, por lo que cumple con todas las condiciones anteriormente mencionadas, pero además mantiene en su estructura información que le permite
    insertar los datos siguiendo un orden definido. Esto permite acceder a los datos de forma más eficiente, ya que estando ordenados, se pueden descartar
    subárboles enteros, manteniendo un Órden Logarítmico, ya que acceder a un dato será tan costoso como navegar por una única rama del árbol.


En conclusión, un ABB, es un tipo de implementación de AB, que a su vez es un árbol. Los tres comparten características, pero el ABB está pensado para acceder
de forma muy eficiente a la información contenida.


CONSIDERACIONES SOBRE EL ARCHIVO ABB.C----------------------------------------------------------------------------------------------
abb_con_cada_elemento: Me costó la implementación, en principio, porque pensé que se podía realizar de forma similar a la del tp lista,
aunque realmente no supe cómo abordarlo de esta forma. Luego tuve inconvenientes al momento de verificar cómo podía actualizar
adecuadamente el contador. Por último, tuve problemas al verificar que pese a que la funcion visitar retornara true, el resto de las
llamadas previamente apiladas continuaba ejecutandose. Creo que la solución que elegí es correcta, utilizando punteros que se vayan
actualizando A medida que se ejecutan las llamadas, y solo permitiendo continuar aumentando el contador siempre que en alguna llamada
previa no se haya devuelto true desde la funcion visitar.
Esta ultima implementacion tuve problemas porque me equivoqué en el modo en que armé mi función visitar y estuve sufriendo bastante hasta
que me di cuenta Me gustaría entender cómo se podría realizar la otra implementación, con funciones con retorno size_t. Y de paso repreguntar
el tema de los punteros a punteros. Porque pese a que yo utilice un puntero contador, en las llamadas se actualizó correctamente y me quedó
en el aire algo que comentó lucas al respecto de que en realidad yo estoy pasando copias.

La eliminación de los nodos (funcion eliminar_nodo) tambien me generó algunos inconvenientes, porque habia intentado definirla ajustando el nodo padre en vez de implementar
una solucion como la que realizó lucas en el video correspondiente a la Práctica de ABB. Luego de estudiarla un poco, me di cuenta que era mucho mas sencillo para leer
de esa forma. Lo unico, mantuve la validacion de un hijo o dos, aunque entiendo que es redundante.

Para el resto de las funciones, pude aplicar sin problemas el método de TDD, con su correspondiente documentación y gráficos.


CONSIDERACIONES SOBRE EL ARCHIVO PRUEBAS.C------------------------------------------------------------------------------------------
Se intentaron abordar el mayor numero de pruebas posibles, pero siempre intentando con un caso básico de un tipo de dato (elementos de tipo INT).

Al final de las pruebas, se probó especificamente con otro tipo de dato y generando desde el heap, para poder verificar que
la implementacion elimine correctamente y con un comparador adecuado, se puedan insertar (y posteriormente recorrer en los ordenes especificados)
los elementos.

