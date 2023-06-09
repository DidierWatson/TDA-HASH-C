#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define CAPACIDAD_MIN 3
#define FACTOR_CARGA_MAXIMO 0.7

typedef unsigned long ulong;

typedef struct nodo
{
	char *clave;
	void *elemento;
	struct nodo **siguiente;
} nodo_t;

struct hash
{
	nodo_t **vector;
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

void nodo_destruir(nodo_t *nodo)
{
	if (!nodo)
		return;
	return;
}

hash_t *rehashear(hash_t *hash)
{
	hash_t *nuevo_hash = hash_crear(hash->capacidad * 2);
	if (!nuevo_hash)
		return NULL;

	return NULL;
}
ulong hashear(const char *clave)
{
	ulong hashValue = 5381;
	int c;

	while ((c = *clave++) != '\0')
	{
		hashValue = ((hashValue << 5) + hashValue) + (ulong)c;
	}

	return hashValue;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (capacidad < CAPACIDAD_MIN)
		capacidad = CAPACIDAD_MIN;
	hash->capacidad = capacidad;
	hash->vector = calloc(1, sizeof(nodo_t *) * capacidad);

	return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;
	size_t posicion = hashear(clave) % hash->capacidad;

	float carga = (float)(hash->cantidad / hash->capacidad);

	if (carga > FACTOR_CARGA_MAXIMO)
	{
		if (!rehashear(hash))
			return NULL;
	}

	nodo_t *nodo = nodo_crear(clave, elemento);
	if (hash->vector[posicion] == NULL)
	{
		hash->vector[posicion] = nodo;
		return hash;
	}

	struct nodo *actual = hash->vector[posicion];
	while (actual != NULL)
	{
		if (!strcmp(actual->clave, clave) == 0)
		{
			actual->elemento = elemento;
			return hash;
		}
	}
	nodo->siguiente = hash->vector[posicion];
	hash->vector[posicion] = nodo;
	hash->capacidad++;

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash)
		return NULL;

	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = hashear(clave) % hash->capacidad;
	if (!hash->vector[posicion])
		return NULL;
	nodo_t *actual = hash->vector[posicion];
	while (actual)
	{
		if (strcmp(actual->clave, clave) == 0)
		{
			return actual->elemento;
		}
		actual = actual->siguiente;
	}
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
	return (!hash) ? 0 : hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash || !destructor)
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
