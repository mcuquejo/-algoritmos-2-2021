CONCEPTOS TEORICOS:
Una tabla de hash es un TDA que permite al usuario acceder a los datos con una complejidad de O(1). Esto se consigue a traves de una funcion de hashing, la cual genera, en teoria, un codigo
unico para cada elemento a guardar. En la practica, al tener que guardar los elementos en una tabla con capacidad limitada, se generan colisiones, ya que dos elementos pueden caer sobre la misma posicion
una vez aplicada la funcion de hashing.

Es por esto que para las operaciones de insercion en una tabla de hash se debe manejar el comportamiento esperado al momento de caer en una colision. Cabe aclarar que una clave repetida no genera colision.
Dependiendo del comportamiento de la tabla de hash, al insertar una clave repetida o bien hay que actualizar el valor de la clave, o bien hay que desestimar la insercion.
La colision ocurre unicamente entre dos claves distintas que caen sobre la misma posicion de la tabla.

Hay distintos tipos de manejo de colision, entre los cuales están:
Probing Lineal: Si al intentar insertar un elemento nos encontramos con que su posicion se encuentra ocupada, se recorrerá el hash elemento a elemento, hasta encontrar una nueva posicion vacia.
Probing cuadrático: En este caso, se buscará una posicion que será el resultado de elevar al cuadrado la cantidad de fallos al intentar insertar el dato. Al fallar una vez, intentará avanzar 1 posicion,
para un segundo fallo, avanzará 4 posiciones; y así sucesivamente hasta encontrar un espacio vacio.
Zona de sobrecarga: Es un espacio, cercano al 10% de la capacidad total de la tabla de hash, en el cual se insertaran las claves que hayan colisionado.

Tener en cuenta que la cantidad de posiciones a avanzar, se deben dividir por la capacidad total del hash. El resto obtenido, sacaremos la posicion final de insercion. Esto es para evitar navegar
posiciones que esten por fuera de la tabla.

Ejemplo para un hash de 3 elementos:
Hash(clave) = 0 => posicion final = 0 % 3 = 0
Hash(clave) = 1 => posicion final = 1 % 3 = 1
Hash(clave) = 2 => posicion final = 2 % 3 = 2
Hash(clave) = 3 => posicion final = 3 % 3 = 0
Hash(clave) = 4 => posicion final = 4 % 3 = 1

La elección de la función de hashing es muy importante a la hora de definir un hash, ya que debe no solo ser eficiente, sino generar la menor cantidad posible de colisiones.

Hay dos tipos de tabla de hash. La de direccionamiento abierto (conocida como Hash cerrado) y la de direccionamiento cerrado (Hash abierto). La primera, guarda las claves en un array de posiciones.
Las claves pueden estar o no en la posicion asignada. Las inserciones, en el mejor de los casos son O(1). En el peor, O(n).
Si la tabla mantiene el estado (Vacio, Ocupado, Borrado), las eliminaciones son O(1) en el mejor de los casos y O(n), en el peor.
Si la tabla no mantiene el estado, al eliminar un dato, se deben rehashear los elementos consecutivos al dato, hasta encontrar un espacio vacio. Esto es porque este tipo de estructura no permite saber si una posicion vacia del hash
estuvo ocupada anteriormente. Los elementos podrian contiguos podrían haber colisionado y, ahora que se eliminó una clave, es un buen momento para verificar esto y, en caso positivo, reacomodar los mismos.

La tabla de direccionamiento cerrado, es un array de listas enlazadas. En este caso las colisiones se manejan de una forma mucho más sencilla. Si dos claves van a parar a la misma posicion, se agregan
en la lista correspondiente. Esto nos garantiza que los elementos siempre se encontraran en la posicion obtenida con la funcion de hashing. A lo sumo, habrá que iterar una lista para poder hallar el dato.

Tanto en los hash cerrados como en los abiertos se puede calcular un factor de carga, el cual es una relacion entre la cantidad de elementos insertados en la tabla de hash y la capacidad total.
A mayor factor de carga, mayor el costo para acceder a los datos.

Llegado cierto punto, es necesario agrandar la tabla de hash y reasignar los elementos nuevamente. Un factor de carga que permite no comprometer la performance de busqueda e insercion, ni la de rehasheo,
es del 75% de carga para un hash cerrado. De todas formas se pueden definir factores de carga mucho más complejos. Para un hash abierto, se puede tener un factor mucho mayor, ya que cada lista puede
contener varias claves, por lo que tranquilamente se puede dar un factor mayor al 100%.



CONSIDERACIONES GENERALES SOBRE EL TP:

Se definieron constantes para mejorar la legibilidad, intentando aprovechar feedback de tda abb.

Elegí la estructura de hash sin un atributo "estado", para realizar borrados fisicos y no lógicos, simplemente porque me pareció que iba a ser un poco más desafiante pensar el algoritmo.
Igualmente, no se si entendí completamente la funcionalidad, por lo cual puede que me haya quedado demasiado rebuscada. En consideraciones particulares, comento un poco qué es lo que interpreté.
Estoy intentando pensar una estructura más legible, aunque por ahora no se me ocurre una mejor forma de llevarla a cabo. Me da la sensación que en varios de los casos, se puede mejorar el código,
reduciendo la cantidad de lineas, o unificando algunas. El tema es que intenté ser lo más explícito posible con lo que quería hacer, llevando la forma de mis funciones a ser un poco repetitivas.
Estoy intentando corregir los casos en donde siento que se puede evitar esto, además me gustaría repensar la estructura de forma recursiva. Esto todavía me cuesta un poco, y no se si en este caso,
hacerlo, es un poco artificial. Pero por ahora Estoy intentando entregar un tda funcional, e ir mejorándolo con pruebas y QA en el código.

CONSIDERACIONES SOBRE FUNCIONES EN PARTICULAR:

fnv_hashing: La elegí porque vi que realizando operaciones sobre numeros primos muy grandes, se disminuye un poco el nivel de colisión y además leí que era bastante eficiente, teniendo un número
bastante bajo de colisiones.

Hash           Lowercase      Random UUID  Numbers
=============  =============  ===========  ==============
FNV-1             184 ns      730 ns          92 ns
                    1 collis    5 collis       0 collis▪

Con un hash de tamaño:
Hash Size
===========
32-bit
    prime: 2^24 + 2^8 + 0x93 = 16777619
    offset: 2166136261

Articulo de donde lo saqué: https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed

strdup_c99: Tomé de base la funcion de duplicar_string del hash_minipruebas. Igualmente ya habiamos hecho la misma funcion.

borrar_tabla: Es una funcion que hice para reutilizar un poco de código. Le dejé un parámetro destruir_valor, porque en algunas llamadas simplemente quería destruir la clave (durante el rehash) y
para la eliminacion, sí solicitaba eliminar el valor con la funcion destruccion, si correspondia.

nueva_posicion: Recorro el hash mientras haya un elemento y ese elemento tenga una clave distinta a la que estaba buscando. Esto me va a devolver una posicion vacia, o una posicion con mi clave,
en donde probablemente me corresponda actualizar el valor contenido en dicha posicion.

rehashear: Es una de las funciones que estoy repensando, ya que lucas comentó que la mejor forma de hacer el rehash es copiando los pares de un hash al otro. En el momento en el que la creé, no
quise duplicar toda la lógica de insercion y por ello volvi a insertar los datos en mi nueva tabla. Igualmente, más adelante en mi funcion de actualizar_elementos que invoco al eliminar un dato,
pude copiar los pares. Estaba viendo si podia hacer algo similar sin romper toda la logica o hacer algo demasiado ilegible por querer reutilizar código.
Durante el rehash utilizo la funcion borrar_tabla, ante un fallo, para borrar la tabla nueva. Esto, es aprovechando que realicé la insercion del dato, por lo cual habia copiado una nueva clave,
permitiendo eliminar las claves y luego la tabla creada, para reasignarle el puntero a la tabla original.
si termina de forma exitosa, tambien uso borrar_tabla, pero esta vez para liberar la tabla auxiliar.

hash_insertar: En esta funcion estoy haciendo un rehash preventivo. Es decir, antes de insertar el dato. Me pareció que aunque fuera uno solo, me estaba ahorrando insertar el dato nuevo dos veces.
Esto me generó una complicacion, porque las llamadas a hash_insertar que simplemente hicieran actualizaciones, también podian disparar el rehash y me daban errores de lectura invalida. Lo intenté
arreglar verificando previamente la existencia de la clave, que, a riesgo de ser O(n), si la funcion funciona correctamente, debería tender a O(1).
Acá es una de las funciones donde tambien estoy repensando la lógica, ya que una vez que tengo la posicion, hago lo siguiente.
Si no existe -> creo par e inserto.
Si existe y es la misma clave -> actualizo valor
si existe y no es la misma clave -> busco nueva posicion.
Si no existe -> creo par e inserto
Si existe y es la misma clave -> actualizo valor ------> Esta creo que está de más, pero por como hice la funcion nueva_posicion, no puedo garantizar que no se de el caso y por eso verifico nuevamente.

actualizar_elementos: Es otra de las funciones que estoy reviendo. Simplemente recorro el hash desde la posicion eliminada, hasta la siguiente posicion vacia. Para cada posicion, verifico que la
funcion hash de un valor distinto. Si es distinto, voy a ver si la nueva posicion obtenida, no tenia elementos. De tener un elemento, vuelvo a buscar la nueva posicion y swapeo los pares, siempre y cuando
no haya caido nuevamente en la posicion desde donde partí. Es por eso que vuelvo a validad que posicion no sea igual a nueva_posicion. Con la eliminacion masiva de claves, este caso me fallaba si no validaba
eso.

hash_quitar: si encuentra la clave, elimina el elemento y actualiza los consecutivos. Si en el lugar donde buscó, había otra clave, busca nueva posicion y elimina si encuentra la clave, para luego
actualizar los consecutivos.

hash_obtener: Si encuentra la clave devuelve el dato, si en la posicion habia otra clave, busca nueva posicion y si encuentra la clave, devuelve el dato.

hash_contiene: Reutilicé hash_obtener. Si no es NULL, es porque el hash contiene la clave.

En esta version, corregi en la creacion la asignacion de espacio del hash, ya que antes verificaba la capacidad menor a 3, pero la tabla la creaba con el valor dado por el usuario. Ahora asigno
hash->capacidad.
Además, corregi el iterador interno porque entendi totalmente al reves la condicion de corte. Pensé que iteraba while true, y era while false, que es lo que retorna la funcion visitar.