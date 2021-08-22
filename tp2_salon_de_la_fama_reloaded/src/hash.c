#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include <stdio.h>

#define SETEO_CAPACIDAD (capacidad_inicial >= TAM_MINIMO_HASH) ? capacidad_inicial : TAM_MINIMO_HASH
#define HASH_ELEMENTO_OBTENIDO (hash->tabla[posicion]) ? hash->tabla[posicion]->valor : NULL
#define HASH_CONTIENE_CLAVE hash_obtener(hash, clave) != NULL
#define HASH_CANTIDAD (hash) ? hash->cantidad : 0

const int ERROR = -1;
const int EXITO = 0;
const int TAM_MINIMO_HASH = 3;
const bool DESTRUIR_VALOR = true;
const long FNV_offset_basis = 2166136261;
const long FNV_prime = 16777619;

typedef struct par
{
  const char *clave;
  void *valor;
} par_t;

struct hash
{
  hash_destruir_dato_t destructor;
  size_t cantidad;
  size_t capacidad;
  par_t **tabla;
};

long fnv_hashing(const char *clave)
{
  long hash = FNV_offset_basis;
  size_t n = strlen(clave);
  for (size_t i = 0; i < n; i++)
  {
    hash *= FNV_prime;
    hash ^= clave[i];
  }
  return hash;
}

char *strdup_c99(const char *string)
{
  if (!string)
    return NULL;
  char *copia = malloc(strlen(string) + 1);
  strcpy(copia, string);
  return copia;
}

par_t *par_crear(const char *clave, void *valor)
{
  par_t *par = calloc(1, sizeof(par_t));
  if (!par)
    return NULL;
  par->clave = strdup_c99(clave);
  if (!par->clave)
  {
    free(par);
    return NULL;
  }
  par->valor = valor;
  return par;
}

void borrar_tabla(par_t **tabla, size_t capacidad, hash_destruir_dato_t destructor, bool destruir_valor)
{
  for (size_t i = 0; i < capacidad; i++)
  {
    if (tabla[i])
    {
      if (destruir_valor && destructor)
      {
        destructor(tabla[i]->valor);
      }
      free((void *)tabla[i]->clave);
    }
    free(tabla[i]);
  }
  free(tabla);
}

hash_t *hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial)
{
  hash_t *hash = calloc(1, sizeof(hash_t));
  if (!hash)
    return NULL;
  hash->destructor = destruir_elemento;
  hash->capacidad = SETEO_CAPACIDAD;
  hash->tabla = calloc(hash->capacidad, sizeof(par_t *));
  if (!hash->tabla)
  {
    free(hash);
    return NULL;
  }
  return hash;
}

size_t nueva_posicion(hash_t *hash, size_t tope, size_t posicion, const char *clave)
{
  posicion = (posicion + 1) % tope;

  while (hash->tabla[posicion] && strcmp(hash->tabla[posicion]->clave, clave) != 0)
    posicion = (posicion + 1) % tope;
  return posicion;
}

bool rehashear(hash_t *hash)
{
  par_t **par_aux = hash->tabla;
  size_t cant_aux = hash->cantidad;
  size_t cap_aux = hash->capacidad;

  hash->tabla = calloc(hash->capacidad * 2, sizeof(par_t));
  if (!hash->tabla)
  {
    hash->tabla = par_aux;
    return false;
  }

  hash->capacidad *= 2;
  hash->cantidad = 0;

  for (size_t i = 0; i < cap_aux; i++)
  {
    if (par_aux[i])
    {
      int resultado_rehash = hash_insertar(hash, par_aux[i]->clave, par_aux[i]->valor);
      if (resultado_rehash == ERROR)
      {
        borrar_tabla(hash->tabla, hash->capacidad, hash->destructor, !DESTRUIR_VALOR);
        hash->capacidad = cap_aux;
        hash->cantidad = cant_aux;
        hash->tabla = par_aux;
        return false;
      }
    }
  }

  borrar_tabla(par_aux, cap_aux, hash->destructor, !DESTRUIR_VALOR);

  return true;
}

size_t hash_obtener_posicion(const char *clave, size_t tope)
{
  long fnv_hash = fnv_hashing(clave);
  fnv_hash = (fnv_hash > 0) ? fnv_hash : fnv_hash * -1;
  size_t posicion = (size_t)fnv_hash % tope;
  return posicion;
}

int hash_insertar(hash_t *hash, const char *clave, void *elemento)
{
  if (!hash || !clave)
    return ERROR;

  if (!hash_contiene(hash, clave) && (hash->cantidad + 1) / hash->capacidad >= 0.75)
  {
    bool exito = rehashear(hash);
    if (!exito)
      return ERROR;
  }

  size_t posicion = hash_obtener_posicion(clave, hash->capacidad); // fnv_hashing(clave) % hash->capacidad;

  if (!hash->tabla[posicion])
  {
    par_t *par = par_crear(clave, elemento);
    if (!par)
      return ERROR;
    hash->tabla[posicion] = par;
    hash->cantidad++;
    return EXITO;
  }
  if (strcmp(hash->tabla[posicion]->clave, clave) == 0)
  {
    void *valor_aux = hash->tabla[posicion]->valor;
    hash->tabla[posicion]->valor = elemento;
    if (hash->destructor)
      hash->destructor(valor_aux);
    return EXITO;
  }

  posicion = nueva_posicion(hash, hash->capacidad, posicion, clave);

  if (!hash->tabla[posicion])
  {
    par_t *par = par_crear(clave, elemento);
    if (!par)
      return ERROR;
    hash->tabla[posicion] = par;
    hash->cantidad++;
    return EXITO;
  }

  void *valor_aux = hash->tabla[posicion]->valor;
  hash->tabla[posicion]->valor = elemento;
  if (hash->destructor)
    hash->destructor(valor_aux);
  return EXITO;
}

void actualizar_elementos(hash_t *hash, size_t posicion, size_t tope)
{
  posicion = (posicion + 1) % tope;

  while (hash->tabla[posicion])
  {
    size_t posicion_nueva = hash_obtener_posicion(hash->tabla[posicion]->clave, tope); //fnv_hashing(hash->tabla[posicion]->clave) % tope;
    if (posicion_nueva != posicion)
    {
      if (hash->tabla[posicion_nueva])
      {
        posicion_nueva = nueva_posicion(hash, hash->capacidad, posicion_nueva, hash->tabla[posicion]->clave);
      }
      if (posicion_nueva != posicion)
      {
        hash->tabla[posicion_nueva] = hash->tabla[posicion];
        hash->tabla[posicion] = NULL;
      }
    }
    posicion = (posicion + 1) % tope;
  }
}

int hash_quitar(hash_t *hash, const char *clave)
{
  if (!hash || !clave)
    return ERROR;

  size_t posicion = hash_obtener_posicion(clave, hash->capacidad); //fnv_hashing(clave) % hash->capacidad;

  if (!hash->tabla[posicion])
  {
    return ERROR;
  }

  if (strcmp(hash->tabla[posicion]->clave, clave) == 0)
  {
    if (hash->destructor)
      hash->destructor(hash->tabla[posicion]->valor);
    free((void *)hash->tabla[posicion]->clave);
    free(hash->tabla[posicion]);
    hash->tabla[posicion] = NULL;
    hash->cantidad--;
    actualizar_elementos(hash, posicion, hash->capacidad);
    return EXITO;
  }

  posicion = nueva_posicion(hash, hash->capacidad, posicion, clave);

  if (!hash->tabla[posicion] || strcmp(hash->tabla[posicion]->clave, clave) != 0)
    return ERROR;

  if (hash->destructor)
    hash->destructor(hash->tabla[posicion]->valor);
  free((void *)hash->tabla[posicion]->clave);
  free((void *)hash->tabla[posicion]);
  hash->tabla[posicion] = NULL;
  hash->cantidad--;
  actualizar_elementos(hash, posicion, hash->capacidad);

  return EXITO;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
  if (!hash || !clave)
    return NULL;

  size_t posicion = hash_obtener_posicion(clave, hash->capacidad); //fnv_hashing(clave) % hash->capacidad;

  if (!hash->tabla[posicion])
    return NULL;

  if (strcmp(hash->tabla[posicion]->clave, clave) == 0)
    return hash->tabla[posicion]->valor;

  posicion = nueva_posicion(hash, hash->capacidad, posicion, clave);

  return HASH_ELEMENTO_OBTENIDO;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
  return HASH_CONTIENE_CLAVE;
}

size_t hash_cantidad(hash_t *hash)
{
  return HASH_CANTIDAD;
}

void hash_destruir(hash_t *hash)
{
  if (!hash)
    return;
  borrar_tabla(hash->tabla, hash->capacidad, hash->destructor, DESTRUIR_VALOR);
  free(hash);
}

size_t hash_con_cada_clave(hash_t *hash, bool (*funcion)(hash_t *hash, const char *clave, void *aux), void *aux)
{
  size_t contador = 0;
  size_t posicion = 0;
  bool continuar = true;
  if (!hash || !funcion)
    return contador;

  while (posicion < hash->capacidad && continuar)
  {
    if (hash->tabla[posicion])
    {
      continuar = funcion(hash, hash->tabla[posicion]->clave, aux);
      contador++;
    }
    posicion++;
  }

  return contador;
}