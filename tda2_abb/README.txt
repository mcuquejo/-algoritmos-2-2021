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

