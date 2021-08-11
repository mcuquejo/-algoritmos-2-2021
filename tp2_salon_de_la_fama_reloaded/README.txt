Esta version es para verificar que efectivamente está todo lo solicitado, pero tiene muchas cosas a corregir que voy a tratar de meter antes del final del dia.

En principio:
*tengo que cambiar la funcion con la que armo el string devuelto por los comandos.
*tengo que reemplazar el iterador interno de lista o el de abb para que ambos tengan la misma condicion de corte, asi evito tener dos funciones distintas.
*Tengo que reacomodar las funciones auxiliares, porque quedaron mezcladas.
*tengo que ver si puedo unificar de alguna forma las funciones comando. Son demasiado parecidas y estoy seguro que se pueden dejar mucho más genéricas.
*tengo que agregar las pruebas pendientes del resto de las estructuras TDA que fui modificando. Sobre todo las de pokemon, entrenador, regla, menu. Pero tambien de los ajustes que hice sobre los tda.

Por ahora agregué los cambios que pregunté por slack con respecto a la longitud excesiva en mis funciones. Igualmente, hubieron casos en donde no pude pensar bien las mismas
y se repitieron estos problemas, sobre todo en los comandos.

Traté de meter todos los comandos y menues en sus propios TDAS, pero los comandos tienen argumentos que podria haber metido como subcomandos y termine usando bloques if
para poder validar eso. Quiero cambiarlo para que sea consecuente y aproveche el TDA.

Cada comando recibe argumentos. Para poder mantener cierto nivel de abstraccion, traté de utilizar listas y pasarlas como extra a las funciones, una vez en mi funcion,
las trabajo normalmente. Al principio, no entendia bien cómo trabajar esto y por ahi me quedaron algunas estructuras demasiado complicadas, pero estoy corrigiendolo
para que quede como en los comandos.

Al principio, habiendo arrancado muy tarde, me costó enfocarme en la solución y fue bastante caótico. Me trabé con cosas como la concatenacion de los strings y Terminé
dejando una funcion provisoria para poder enfocarme en el TDA. Ahora tengo que cambiarla. La verdad es que me desorganicé muchísimo y me costó mucho todo el comienzo, Pero
estoy seguro que al final algo me hizo clic y me ayudó a entender muchísimo mejor lo que estaba tratando de hacer.

Traté de crear reglas minimamente entretenidas, porque la verdad que fue la parte mas divertida de todo. Pero la de los dittos fue un poco reutilizar la anterior, Porque
no se me ocurrió nada mejor. Si hubiera tenido un poco más de tiempo, hubiera hecho una con puntos de salud y pociones, parecido a lo que hice con lo de los gimnasios.

El formato de C que quedó no lo elegí yo. Tuve problemas con mi vscode y terminé teniendo que crear un .clang-format para poder dejar las cosas más o menos ordenadas,
pero es completamente distinto el estilo de indentado al que vengo usando desde siempre. Te pido disculpas si es más incómodo de leer :S.

En una de las pruebas me tira un mensaje por la extension de las variables del stack, no se si se corregirá cambiando la funcion de concatenacion, pero me pedia ajustar
un argumento del tamaño del stack, asi que lo dejé asi.

Muchas de las recomendaciones que me hiciste, esta vez no las pude aplicar, porque realmente estuve trabajando con poquisimo tiempo. Estoy intentando agregar todo lo posible
para que quede algo muchisimo mejor.

Pendiente de agregar consideraciones particulares sobre las funciones. Ahora mismo estoy corrigiendo algunas, para que quede todo más prolijo.







