TP SALON DE LA FAMA POKEMON.

SOLUCION IMPLEMENTADA:

consideraciones sobre UTIL.C:
• vtrlen castea el puntero void* a void** (tuve problemas con este punto, ya que no sabia que void era tan flexible).
  Luego recorro los elementos no nulos del vector dinamico y devuelvo la cantidad

• vtradd toma el largo del vector + dos posiciones extra, la del nuevo elemento y la de la posicion de corte del vector
  dinamico.

• vtrfree recorre un vector dinamico y lo libera. Solo lo utilizo con los vectores de lineas leidas o split, ya que los
  vectores dinamicos de los entrenadores y pokemones de un salon los proceso con liberar salon de otra forma.
• duplicar_texto_hasta recibe un string y las posiciones desde y hasta donde debe duplicar el texto.

• split tal vez tenga que corregir su funcionamiento, pero la idea es que recorra el string hasta el ultimo separador y
  almacene los fragmentos de texto. Una vez que llega hasta este punto, pueden ocurrir dos cosas, o que este al final
  del string, por lo que agrego un string vacio al vector, o que haya mas texto luego del ultimo separador. En este caso
  ejecuto una vez mas el duplicar_texto_hasta, llegando hasta el final del string.

• fgets_alloc es literalmente la funcion mostrada en el video. Se intento realizar modificaciones, la unica diferencia
  remarcable, es que yo no elimino el \n al final de la linea.

• fclosen simplemente verifica que si el archivo esta abierto, sea cerrado.

consideraciones sobre SALON.C
• salon_leer_archivo abre el archivo, crea un salon vacio y procesa las lineas. Si es un entrenador, lo crea y lo agrega
  al salon, si es un pokemon, lo crea y lo agrega al entrenador. Todas las funciones de creacion y de carga fueron
  modularizadas.

• salon_guardar_archivo crea un archivo en modo escritura y por cada entrenador, lo agrega con fprintf, aprovechando el
  formato de escritura que nos fue mostrado en la clase de nivelacion de C. Realiza lo mismo con los pokemon. Luego
  retorna la cantidad de entrenadores insertada.

• salon_agregar_entrenador es la que más problemas me trajo. Terminé decidiendo que si hay un entrenador para insertar, se
  lo haga al final del vector dinamico. Luego, a traves de la fucnion, ordenar_entrenadores, creo un array en donde me
  guardo referencias a los punteros del vector dinamico de entrenadores (salon->entrenadores) y al recorrerlo, comparo las
  victorias contra las del nuevo entrenador. Primero inserto los menores o iguales al entrenador agregado, luego agrego al
  entrenador, y luego guardo al resto de entrenadores.

• salon_obtener_entrenadores_mas_ganadores recorre a todos los entrenadores y agrega en un vector dinamico a aquellos que
  cumplan la condicion minima de victorias.

• salon_mostrar_entrenador muestra al entrenador pasado por argumento formateado segun si tiene o no pokemones.

• salon_destruir primero libera los pokemones, luego los entrenadores, y por ultimo al salon.



ACLARACIONES:
• Es probable que me haya excedido con la cantidad de frees agregados en las validaciones. Tuve muchos problemas con la memoria
  y fui agregando en distintos lugares, probando. A la fecha, estoy intentando ir rompiendo las pruebas para poder verificar
  que sean correctos, pero me demoré con el agregado de entrenadores en orden ascendente. Realmente tuve muchos problemas con
  la memoria en esa funcion.

• Aclaro que agregar al squirtle no me llevó tiempo, je. Fue un vil copy&paste. Digo porque realmente estoy peleando ahora para
  dejar los frees minimos y necesarios.


CONCEPTOS TEORICOS:
1. Heap y stack: ¿Para qué y cómo se utiliza cada uno?
• Stack: es memoria estática, que usamos para guardar variables, y todos los punteros que vamos generando a lo largo del ciclo de vida
  de nuestra funcion. Estos elementos quedan dentro del ambito de la misma, por lo cual es importante prestar atencion a mantener las
  referencias de punteros a memoria dinámica que hayamos solicitado, ya que una vez que salimos de las funciones, si no los guardamos,
  no podemos recuperarlos. Dicha memoria es limitada (o más bien el sector reservado para el stack lo es. La memoria es toda la misma),
  y tenemos que prestar especial atencion al momento de realizar trabajos de recursividad, ya que se apilan los llamados en la misma y
  puede dar overflow (esto siempre teniendo en cuenta que si el compilador lo permite, se puede aplicar recursividad de cola y que la
  llamada recursiva se comporte como una iterativa, es decir, no se apile en el stack).

• Heap: Es la memoria dinámica. Tan ilimitada como memoria física tengamos en nuestro equipo. Es en donde guardamos los elementos que
  necesitemos mantener fuera del ambito de una funcion, como structs, arrays, o elementos en general que necesitemos mantener mientras
  el main esté vivo.

2. Malloc/Realloc/Free: ¿Cómo y para qué se utilizan?
• malloc requiere un parametro: el tamaño de memoria que necesitamos solicitar. Se utiliza para reservar memoria dinamica. le tenemos
  que decir cuanto espacio vamos a solicitar. Por ejemplo, sizeof(char)*3, equivale a 3 bytes reservados.

• realloc, recibe un puntero a memoria dinamica y el nuevo tamaño que se quiere reservar. Devuelve un puntero a un sector de memoria del
  tamaño solicitado o NULL, si falla o se solicitara un tamaño de 0 bytes.

• free es la funcion que se encarga de liberar la memoria dinamica reservada. recibe el puntero hacia ese sector de memoria.