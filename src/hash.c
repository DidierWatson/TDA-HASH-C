#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define CAPACIDAD_MIN 3
#define FACTOR_CARGA_MAXIMO 0.7

typedef struct nodo
{
	char *clave;
	void *elemento;
	struct nodo **siguiente;
} nodo_t;

struct hash
{
	struct nodo **vector;
	size_t cantidad;
	size_t capacidad;
};

char *copiar_clave(const char *clave)
{
	if (!clave)
		return NULL;
	char *copia = malloc(strlen(clave) + 1);
	if (!copia)
		return NULL;
	strcpy(copia, clave);

	return copia;
}

nodo_t *nodo_crear(const char *clave, void *elemento)
{
	if (!clave)
		return NULL;
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;
	nodo->clave = copiar_clave(clave);
	nodo->elemento = elemento;

	return nodo;
}

hash_t *hash_crear(size_t capacidad)
{
	return NULL;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;

	return NULL;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;

	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;

	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;

	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return 0;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	size_t n = 0;
	if (!hash || !f)
		return n;

	return n;
}
