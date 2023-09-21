#include <string.h>
#include <stdlib.h>

#include "hash.h"

#define CAPACIDAD_MIN 3
#define FACTOR_CARGA_MAXIMO 0.7

typedef unsigned long ulong;

typedef struct nodo {
	char *clave;
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	nodo_t **vector;
	size_t cantidad;
	size_t capacidad;
};

char *_copiar_clave(const char *clave)
{
	if (!clave)
		return NULL;
	char *copia = malloc(strlen(clave) + 1);
	if (!copia)
		return NULL;
	strcpy(copia, clave);

	return copia;
}

nodo_t *_nodo_crear(const char *clave, void *elemento)
{
	if (!clave)
		return NULL;
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo)
		return NULL;
	nodo->clave = _copiar_clave(clave);
	if (!nodo->clave) {
		free(nodo);
		return NULL;
	}
	nodo->elemento = elemento;
	nodo->siguiente = NULL;
	return nodo;
}

void _nodo_destruir(nodo_t *nodo)
{
	if (!nodo)
		return;
	free(nodo->clave);
	free(nodo);
}

ulong _hashear(const char *clave)
{
	ulong hashValue = 5381;
	int c;

	while ((c = *clave++) != '\0') {
		hashValue = ((hashValue << 5) + hashValue) + (ulong)c;
	}

	return hashValue;
}

hash_t *_rehashear(hash_t *hash)
{
	if (!hash)
		return NULL;

	hash_t *nuevo_hash = hash_crear((hash->capacidad) * 2);

	if (!nuevo_hash)
		return NULL;

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->vector[i];
		while (actual) {
			void *anterior = NULL;
			if (!hash_insertar(nuevo_hash, actual->clave,
					   actual->elemento, &anterior))
				return NULL;
			actual = actual->siguiente;
		}
	}

	hash_t aux = *hash;
	*hash = *nuevo_hash;
	*nuevo_hash = aux;

	hash_destruir(nuevo_hash);

	return hash;
}

hash_t *hash_crear(size_t capacidad)
{
	if (capacidad < CAPACIDAD_MIN)
		capacidad = CAPACIDAD_MIN;
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash)
		return NULL;

	hash->vector = calloc(capacidad, sizeof(nodo_t *));
	if (!hash->vector) {
		free(hash);
		return NULL;
	}

	hash->capacidad = capacidad;
	return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;

	float carga = (float)hash->cantidad / (float)hash->capacidad;

	if (carga > FACTOR_CARGA_MAXIMO) {
		if (!_rehashear(hash)) {
			hash_destruir(hash);
			return NULL;
		}
	}

	size_t posicion = _hashear(clave) % hash->capacidad;

	if (hash->vector[posicion] == NULL) {
		nodo_t *nodo = _nodo_crear(clave, elemento);
		if (!nodo)
			return NULL;

		hash->vector[posicion] = nodo;
		hash->cantidad++;
		if (anterior)
			*anterior = NULL;
		return hash;
	}

	nodo_t *actual = hash->vector[posicion];
	while (actual) {
		if (strcmp(actual->clave, clave) == 0) {
			void *elemento_anterior = actual->elemento;
			actual->elemento = elemento;
			if (anterior)
				*anterior = elemento_anterior;
			return hash;
		}
		actual = actual->siguiente;
	}

	nodo_t *nodo = _nodo_crear(clave, elemento);
	if (!nodo)
		return NULL;
	nodo->siguiente = hash->vector[posicion];
	hash->vector[posicion] = nodo;
	hash->cantidad++;
	if (anterior)
		*anterior = NULL;
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = _hashear(clave) % hash->capacidad;
	nodo_t *actual = hash->vector[posicion];
	nodo_t *anterior = NULL;

	while (actual) {
		if (strcmp(actual->clave, clave) == 0) {
			if (anterior)
				anterior->siguiente = actual->siguiente;
			else
				hash->vector[posicion] = actual->siguiente;

			void *elemento = actual->elemento;

			_nodo_destruir(actual);
			hash->cantidad--;

			return elemento;
		}

		anterior = actual;
		actual = actual->siguiente;
	}
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t posicion = _hashear(clave) % hash->capacidad;
	nodo_t *actual = hash->vector[posicion];

	while (actual) {
		if (actual->clave && strcmp(actual->clave, clave) == 0) {
			return actual->elemento;
		}
		actual = actual->siguiente;
	}
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return false;

	size_t posicion = _hashear(clave) % hash->capacidad;
	nodo_t *actual = hash->vector[posicion];

	while (actual) {
		if (actual->clave && strcmp(actual->clave, clave) == 0)
			return true;
		actual = actual->siguiente;
	}

	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	return (!hash) ? 0 : hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	if (!hash)
		return;
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->vector[i];
		while (actual) {
			nodo_t *siguiente = actual->siguiente;
			if (destructor)
				destructor(actual->elemento);
			_nodo_destruir(actual);
			actual = siguiente;
		}
	}
	free(hash->vector);
	free(hash);
	hash = NULL;
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	size_t claves_iteradas = 0;
	if (!hash || !f)
		return claves_iteradas;
	for (size_t i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->vector[i];

		while (actual) {
			if (!f(actual->clave, actual->elemento, aux)) {
				claves_iteradas++;
				return claves_iteradas;
			}

			claves_iteradas++;
			actual = actual->siguiente;
		}
	}
	return claves_iteradas;
}
