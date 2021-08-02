

typedef struct regla regla_t;

typedef int (*enfrentar)(void* pokemon, void* rival, void* extra);

typedef struct menu_reglas menu_reglas_t;

menu_reglas_t* menu_reglas_crear();

void menu_agregar_regla(menu_reglas_t* menu_reglas, const char* nombre, const char* descripcion, int (*enfrentamiento)(void* pokemon, void* rival, void* extra));

void menu_reglas_con_cada_elemento(menu_reglas_t* menu_reglas, void* resultado);

void menu_reglas_destruir(menu_reglas_t* menu_reglas);