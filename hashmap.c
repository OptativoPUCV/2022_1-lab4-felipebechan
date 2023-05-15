#include "hashmap.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMap HashMap;
int enlarge_called = 0;

struct HashMap {
  Pair **buckets;
  long size;     // cantidad de datos/pairs en la tabla
  long capacity; // capacidad de la tabla
  long current;  // indice del ultimo dato accedido
};

Pair *createPair(char *key, void *value) {
  Pair *new = (Pair *)malloc(sizeof(Pair));
  new->key = key;
  new->value = value;
  return new;
}

long hash(char *key, long capacity) {
  unsigned long hash = 0;
  char *ptr;
  for (ptr = key; *ptr != '\0'; ptr++) {
    hash += hash * 32 + tolower(*ptr);
  }
  return hash % capacity;
}

int is_equal(void *key1, void *key2) {
  if (key1 == NULL || key2 == NULL)
    return 0;
  if (strcmp((char *)key1, (char *)key2) == 0)
    return 1;
  return 0;
}

void insertMap(HashMap *map, char *key, void *value) {
  Pair *dato = createPair(key, value);     // crear par nuevo
  map->current = hash(key, map->capacity); // f.hash para posc de incs

  Pair **aux = map->buckets;
  long posicion = map->current; // pos actual

  // loop encontrar dispo
  while (aux[posicion] != NULL) {
    posicion++;
    if (posicion == (map->capacity))
      posicion = 0;
  }

  map->buckets[posicion] = dato; // se pone en dispo
  map->current = posicion;       // update pos actual
  map->size++;                   // ++
}

// done

void enlarge(HashMap *map) {
  enlarge_called = 1;               // no borrar (testing purposes)
  Pair **OldBuckets = map->buckets; // referencia oldb
  map->capacity *= 2;               // *2 capacidad
  Pair **newA =
      calloc(sizeof(Pair *), map->capacity); // nuevo arreglo de b con ++*2
  map->buckets = newA;
  // recorrer e insertar
  for (int i = 0; i < map->capacity / 2; i++) {
    if (OldBuckets[i] != NULL && OldBuckets[i]->key != NULL) {
      insertMap(map, OldBuckets[i]->key, OldBuckets[i]->value);
      // insertar again en mapa
    }
  }
}
// done

HashMap *createMap(long capacity) {
  // se explica solo ncfjfjf
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
  map->capacity = capacity;
  map->size = 0;
  map->current = -1;
  return map;
}

void eraseMap(HashMap *map, char *key) {}

Pair *searchMap(HashMap *map, char *key) { return NULL; }

Pair *firstMap(HashMap *map) { return NULL; }

Pair *nextMap(HashMap *map) { return NULL; }
