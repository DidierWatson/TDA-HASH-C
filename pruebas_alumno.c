#include "pa2m.h"
#include "src/hash.h"

void dado_hash_null_pruebo_las_primitivas_obtengo_resultado_esperado()
{
	hash_t *hash_nulo = NULL;
	pa2m_afirmar(hash_insertar(hash_nulo, "ABC", (void *)34, NULL) == NULL,
		     "No se pueden insertar elementos en hash nulo.");
	pa2m_afirmar(hash_quitar(hash_nulo, "ABC") == NULL,
		     "No se pueden quitar elementos de un hash nulo.");
	pa2m_afirmar(hash_obtener(hash_nulo, "ABC") == NULL,
		     "No se pueden obtener los elementos dado un hash nulo.");
	pa2m_afirmar(
		hash_cantidad(hash_nulo) == 0,
		"La cantidad de elementos almacencados de un hash nulo es 0.");
	pa2m_afirmar(
		hash_con_cada_clave(hash_nulo, false, NULL) == 0,
		"La canitdad de elementos recorridos con el iterador interno de un hash nulo es 0.");
}

void dada_capacidad_inicial_valida_y_destructor_nulo_se_crea_un_hash_correctamente()
{
	hash_t *hash_uno = hash_crear(1);
	pa2m_afirmar(
		hash_uno != NULL,
		"Crear un hash con capacidad menor a la minima y destructor nulo crea un hash correctamente.");
	hash_t *hash_quince = hash_crear(15);
	pa2m_afirmar(
		hash_quince != NULL,
		"Crear un hash con capacidad valida y destructor nulo crea un hash correctamente.");
	hash_destruir(hash_uno);
	hash_destruir(hash_quince);
}

void dado_valores_validos_se_insertan_correctamente_los_elementos()
{
	hash_t *hash = hash_crear(7);
	pa2m_afirmar(hash != NULL, "Se crea un hash correctamente");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Un  hash recien creado tiene 0 elementos.");
	pa2m_afirmar(hash_insertar(hash, "ABCD", (void *)3, NULL) != NULL,
		     "Se inserta correctamente un elemento.");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos del hash es 1.");
	pa2m_afirmar(hash_insertar(hash, "EFGH", (void *)1, NULL) != NULL,
		     "Se inserta correctamente un elemento.");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos del hash es 2.");
	pa2m_afirmar(hash_insertar(hash, "IJKL", (void *)5, NULL) != NULL,
		     "Se inserta correctamente un elemento.");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos del hash es 3.");

	printf("\n");
	hash_destruir(hash);
}

void dado_valores_validos_se_insertan_elementos_en_hash_con_menor_capacidad()
{
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea un hash nuevo correctamente.");
	pa2m_afirmar(hash_insertar(hash, "HOLA", (void *)3, NULL) != NULL,
		     "Se inserta correctamente un elemento[1].");
	pa2m_afirmar(hash_insertar(hash, "ESTO", (void *)2, NULL) != NULL,
		     "Se inserta correctamente un elemento[2].");
	pa2m_afirmar(hash_insertar(hash, "ES", (void *)6, NULL) != NULL,
		     "Se inserta correctamente un elemento[3].");
	pa2m_afirmar(hash_insertar(hash, "UNA", (void *)7, NULL) != NULL,
		     "Se inserta correctamente un elemento[4].");
	pa2m_afirmar(hash_insertar(hash, "PRUEBA", (void *)3, NULL) != NULL,
		     "Se inserta correctamente un elemento[5].");
	pa2m_afirmar(hash_insertar(hash, "DEL", (void *)1, NULL) != NULL,
		     "Se inserta correctamente un elemento[6].");
	pa2m_afirmar(hash_insertar(hash, "HASH", (void *)4, NULL) != NULL,
		     "Se inserta correctamente un elemento[7].");
	pa2m_afirmar(hash_insertar(hash, "INSERTAR", (void *)8, NULL) != NULL,
		     "Se inserta correctamente un elemento[8].");
	pa2m_afirmar(hash_cantidad(hash) == 8,
		     "La cantidad de elementos en el hash es 8.");

	hash_destruir(hash);
}

void dado_un_hash_se_quitan_elementos_obtengo_resultados_esperados()
{
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea correctamente un hash");
	pa2m_afirmar(hash_insertar(hash, "Prueba1", (void *)3, NULL) != NULL,
		     "Se inserta correctamente un elemento[1].");
	pa2m_afirmar(hash_insertar(hash, "Prueba2", (void *)2, NULL) != NULL,
		     "Se inserta correctamente un elemento[2].");
	pa2m_afirmar(hash_insertar(hash, "Prueba3", (void *)6, NULL) != NULL,
		     "Se inserta correctamente un elemento[3].");
	pa2m_afirmar(hash_insertar(hash, "Prueba4", (void *)7, NULL) != NULL,
		     "Se inserta correctamente un elemento[4].");
	pa2m_afirmar(hash_insertar(hash, "Prueba5", (void *)10, NULL) != NULL,
		     "Se inserta correctamente un elemento[5].");
	pa2m_afirmar(hash_insertar(hash, "Prueba6", (void *)1, NULL) != NULL,
		     "Se inserta correctamente un elemento[6].");
	pa2m_afirmar(hash_insertar(hash, "Prueba7", (void *)4, NULL) != NULL,
		     "Se inserta correctamente un elemento[7].");
	pa2m_afirmar(hash_insertar(hash, "Prueba8", (void *)8, NULL) != NULL,
		     "Se inserta correctamente un elemento[8].");
	pa2m_afirmar(hash_cantidad(hash) == 8,
		     "La cantidad de elementos en el hash es 8.");
	pa2m_afirmar(hash_quitar(hash, "Prueba1") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 7,
		     "La cantidad de elementos en el hash es 7.");
	pa2m_afirmar(hash_quitar(hash, "Prueba2") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 6,
		     "La cantidad de elementos en el hash es 6.");
	pa2m_afirmar(hash_quitar(hash, "Prueba5") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "La cantidad de elementos en el hash es 5.");
	pa2m_afirmar(hash_quitar(hash, "Prueba8") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad de elementos en el hash es 4.");
	pa2m_afirmar(hash_quitar(hash, "Prueba3") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad de elementos en el hash es 3.");
	pa2m_afirmar(hash_quitar(hash, "Prueba7") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad de elementos en el hash es 2.");
	pa2m_afirmar(hash_quitar(hash, "Prueba4") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad de elementos en el hash es 1.");
	pa2m_afirmar(hash_quitar(hash, "Prueba6") != NULL,
		     "Se quita correctamente un elemento del hash.");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad de elementos en el hash es 0.");
	pa2m_afirmar(
		hash_quitar(hash, "Prueba1") == NULL,
		"Se intenta quitar un elemento del hash que ya fue quitado, resultado ERROR.");
	hash_destruir(hash);
}

void dado_un_hash_se_obtienen_los_elementos_esperados()
{
	hash_t *hash = hash_crear(6);
	pa2m_afirmar(hash != NULL, "Se crea correctamente un hash");
	pa2m_afirmar(hash_insertar(hash, "PR-UNO", (void *)21, NULL) != NULL,
		     "Se inserta correctamente un elemento[1].");
	pa2m_afirmar(hash_insertar(hash, "PR-DOS", (void *)56, NULL) != NULL,
		     "Se inserta correctamente un elemento[2].");
	pa2m_afirmar(hash_insertar(hash, "PR-TRES", (void *)23, NULL) != NULL,
		     "Se inserta correctamente un elemento[3].");
	pa2m_afirmar(hash_insertar(hash, "PR-CUATRO", (void *)100, NULL) !=
			     NULL,
		     "Se inserta correctamente un elemento[4].");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad de elementos dentro del hash es 4.");
	pa2m_afirmar(
		hash_obtener(hash, "PR-DOS") == (void *)56,
		"Se obtiene el elemento correspondiente con la clave PR-DOS.");
	pa2m_afirmar(
		hash_obtener(hash, "PR-CUATRO") == (void *)100,
		"Se obtiene el elemento correspondiente con la clave PR-CUATRO.");
	pa2m_afirmar(
		hash_obtener(hash, "PR-TRES") == (void *)23,
		"Se obtiene el elemento correspondiente con la clave PR-TRES.");
	pa2m_afirmar(
		hash_obtener(hash, "PR-UNO") == (void *)21,
		"Se obtiene el elemento correspondiente con la clave PR-UNO.");

	hash_destruir(hash);
}

void dado_un_hash_contiene_los_elementos_correspondientes()
{
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea correctamente un hash");
	pa2m_afirmar(hash_insertar(hash, "E-UNO", "Elemento-uno", NULL) != NULL,
		     "Se inserta correctamente un elemento[1].");
	pa2m_afirmar(hash_insertar(hash, "E-DOS", "Elemento-dos", NULL) != NULL,
		     "Se inserta correctamente un elemento[2].");
	pa2m_afirmar(hash_insertar(hash, "E-TRES", "Elemento-tres", NULL) !=
			     NULL,
		     "Se inserta correctamente un elemento[3].");
	pa2m_afirmar(hash_insertar(hash, "E-CUATRO", "Elemento-cuatro", NULL) !=
			     NULL,
		     "Se inserta correctamente un elemento[4].");
	pa2m_afirmar(hash_insertar(hash, "E-CINCO", "Elemento-cinco", NULL) !=
			     NULL,
		     "Se inserta correctamente un elemento[5].");
	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "La cantidad de elementos dentro del hash es 5.");
	pa2m_afirmar(
		hash_contiene(hash, "E-DOS") == true,
		"Se consulta si contiene un elemento con la clave E-DOS, el resultado es el correspondiente.");
	pa2m_afirmar(hash_contiene(hash, "E-SEIS") == false,
		     "Se consulta si contiene un elemento no insertado.");
	pa2m_afirmar(hash_insertar(hash, "E-SEIS", "Elemento-seis", NULL) !=
			     NULL,
		     "Se inserta correctamente un elemento[6].");
	pa2m_afirmar(hash_contiene(hash, "E-SEIS") == true,
		     "Se consulta si contiene el elemento recien insertado.");
	pa2m_afirmar(hash_insertar(hash, "E-SIETE", "Elemento-siete", NULL) !=
			     NULL,
		     "Se inserta correctamente un elemento[7].");
	pa2m_afirmar(hash_contiene(hash, "E-SIETE") == true,
		     "Se consulta si contiene el elemento recien insertado.");
	pa2m_afirmar(hash_insertar(hash, "E-UNO", "Elemento-uno", NULL) != NULL,
		     "Se inserta correctamente un elemento[1].");
	hash_destruir(hash);
}

void pruebo_todas_las_funciones_de_hash()
{
	hash_t *hash = hash_crear(5);
	pa2m_afirmar(hash != NULL, "Se crea correctamente un hash");
	hash_insertar(hash, "1A", "Primer piso A", NULL);
	hash_insertar(hash, "1B", "Primer piso B", NULL);
	hash_insertar(hash, "1C", "Primer piso C", NULL);
	hash_insertar(hash, "2A", "Segundo piso A", NULL);
	hash_insertar(hash, "2B", "Segundo piso B", NULL);
	hash_insertar(hash, "2C", "Segundo piso C", NULL);
	hash_insertar(hash, "3A", "Tercer piso A", NULL);
	hash_insertar(hash, "3B", "Tercer piso B", NULL);
	hash_insertar(hash, "3C", "Tercer piso C", NULL);
	hash_insertar(hash, "4A", "Cuarto piso A", NULL);
	hash_insertar(hash, "4B", "Cuarto piso B", NULL);
	hash_insertar(hash, "4C", "Cuarto piso C", NULL);
	hash_insertar(hash, "5A", "Quinto piso A", NULL);
	hash_insertar(hash, "5B", "Quinto piso B", NULL);
	hash_insertar(hash, "5C", "Quinto piso C", NULL);

	void *elemento_a_consultar = "Segundo piso A";
	pa2m_afirmar(hash_cantidad(hash) == 15,
		     "La canitdad de los elementos en el haah es la correcta.");
	pa2m_afirmar(hash_contiene(hash, "2A") == true,
		     "Se consulta si contiene el elemento del departamento 2A");
	pa2m_afirmar(hash_obtener(hash, "2A") == elemento_a_consultar,
		     "El elemento dentro del depto 2A es el correspondiente.");
	hash_quitar(hash, "4C");
	hash_quitar(hash, "1B");
	pa2m_afirmar(hash_cantidad(hash) == 13,
		     "Se quitaron dos elementos del hash correctamente.");
	pa2m_afirmar(hash_contiene(hash, "Penthouse") == false,
		     "Se consulta si contiene un elemento no existente.");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo(" == TDA HASH == ");

	pa2m_nuevo_grupo("Pruebas con hash NULL");
	dado_hash_null_pruebo_las_primitivas_obtengo_resultado_esperado();

	pa2m_nuevo_grupo("Pruebas de creacion");
	dada_capacidad_inicial_valida_y_destructor_nulo_se_crea_un_hash_correctamente();

	pa2m_nuevo_grupo("Pruebas de insertar");
	dado_valores_validos_se_insertan_correctamente_los_elementos();
	dado_valores_validos_se_insertan_elementos_en_hash_con_menor_capacidad();

	pa2m_nuevo_grupo("Pruebas de quitar");
	dado_un_hash_se_quitan_elementos_obtengo_resultados_esperados();

	pa2m_nuevo_grupo("Pruebas de obtener");
	dado_un_hash_se_obtienen_los_elementos_esperados();

	pa2m_nuevo_grupo("Pruebas de contiene");
	dado_un_hash_contiene_los_elementos_correspondientes();

	pa2m_nuevo_grupo("Pruebas de todas las funciones en un unico hash");
	pruebo_todas_las_funciones_de_hash();

	return pa2m_mostrar_reporte();
}