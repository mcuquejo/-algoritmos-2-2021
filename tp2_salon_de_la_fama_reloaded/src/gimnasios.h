#ifndef GIM_H
#define GIM_H

typedef struct gimnasio gimnasio_t;

gimnasio_t **gimnasio_inicializar_gimnasios();

const char *gimnasio_obtener_tipo(gimnasio_t *gimnasio);

double gimnasio_obtener_efectividad_rival(gimnasio_t *gimnasio, const char *tipo_rival);

void gimnasio_destruir_gimnasios(gimnasio_t **gimnasios);

#endif /* GIM_H */