#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define Max_Char 41

// Declaracion de Tipos
typedef char tString[Max_Char];

typedef struct {
	
    tString saga;
    tString titulo;
    tString genero;
    int ano;
    int minJugados;
    
} tJuego;

typedef struct nodoJuego {
	
    tJuego game;
    struct nodoJuego *siguiente;
    
} tListaJuego;


// Variables Globales
FILE *archColeccion;
tJuego juego, juegoAnterior;

int minTotales, cantJuegos, masMinutos;
int acumMasMin, acumMasMinCorte, acumCantJuegos;
tString masMinJuego, masMinCorte;


// Declaracion de Funciones
void LimpiarBuffer();

bool ListaVacia(tListaJuego *);
void AgregarJuego(tListaJuego **);
tJuego IngresarJuego();
void EliminarJuego(tListaJuego **);

void OrdenarPorSaga(tListaJuego **);
void OrdenarPorGenero(tListaJuego **);

void Busqueda(tListaJuego *);
bool ExisteJuego(tListaJuego *, tListaJuego **);

void GrabarColeccion(tListaJuego *);

void PrincipioCorte();
void unJuego();

void ProcesoCorteSaga();
void ProcesoCorteGenero();

void FinCorteSaga();
void FinCorteGenero();

void FinalCorteSaga();
void FinalCorteGenero();

void Finalizacion(tListaJuego *);


// Desarrollo de Funciones
void LimpiarBuffer() {
    int caracter;

    while ((caracter = getchar()) != '\n' && caracter != EOF) {
        // Descarta los Caracteres Restantes de la Linea.
    }
}


bool ListaVacia(tListaJuego *pColeccion) {
	
    return (pColeccion == NULL);
}


void AgregarJuego(tListaJuego **pColeccion) {
	
    tListaJuego *nuevoNodo;

    nuevoNodo = (tListaJuego *) malloc(sizeof(tListaJuego));

    if (nuevoNodo == NULL) {
    	
        printf("Error al Reservar Memoria.\n");
        return;
    }

    nuevoNodo->game = IngresarJuego();
    
    nuevoNodo->siguiente = *pColeccion;
    *pColeccion = nuevoNodo;

    printf("\nJuego Agregado a la Coleccion.\n");
}

//Ingreso de los Datos por Juego
tJuego IngresarJuego() {
	
    tJuego juegoIngresado;

    printf("\nIngresar Saga del Juego: ");
    fgets(juegoIngresado.saga, Max_Char, stdin);
    juegoIngresado.saga[strcspn(juegoIngresado.saga, "\n")] = '\0';

    printf("Ingresar Titulo del Juego: ");
    fgets(juegoIngresado.titulo, Max_Char, stdin);
    juegoIngresado.titulo[strcspn(juegoIngresado.titulo, "\n")] = '\0';

    printf("Ingresar Genero del Juego: ");
    fgets(juegoIngresado.genero, Max_Char, stdin);
    juegoIngresado.genero[strcspn(juegoIngresado.genero, "\n")] = '\0';

    printf("Ingresar Ano del Juego: ");
    if (scanf("%d", &juegoIngresado.ano) != 1) {
    	
        juegoIngresado.ano = 0;
    }
    LimpiarBuffer();

    printf("Ingresar Minutos Jugados del Juego: ");
    if (scanf("%d", &juegoIngresado.minJugados) != 1) {
    	
        juegoIngresado.minJugados = 0;
    }
    LimpiarBuffer();

    return juegoIngresado;
}


// Ordenamiento por Insercion Directa segun Saga
void OrdenarPorSaga(tListaJuego **pColeccion) {
	
    tListaJuego *actual;
    tListaJuego *ordenada;
    tListaJuego *aux;
    tListaJuego *anterior;

    actual = *pColeccion;
    ordenada = NULL;

    while (actual != NULL) {
        aux = actual;
        actual = actual->siguiente;

        if (ordenada == NULL || strcmp(aux->game.saga, ordenada->game.saga) < 0) {
        	
            aux->siguiente = ordenada;
            ordenada = aux;
            
        } else {
        	
            anterior = ordenada;
            while (anterior->siguiente != NULL && strcmp(anterior->siguiente->game.saga, aux->game.saga) <= 0) {
            	
                anterior = anterior->siguiente;
            }
            aux->siguiente = anterior->siguiente;
            anterior->siguiente = aux;
        }
    }

    *pColeccion = ordenada;
}


// Ordenamiento por Insercion Directa segun Genero
void OrdenarPorGenero(tListaJuego **pColeccion) {
	
    tListaJuego *actual;
    tListaJuego *ordenada;
    tListaJuego *aux;
    tListaJuego *anterior;

    actual = *pColeccion;
    ordenada = NULL;

    while (actual != NULL) {
    	
        aux = actual;
        actual = actual->siguiente;

        if (ordenada == NULL || strcmp(aux->game.genero, ordenada->game.genero) < 0) { 
        
			aux->siguiente = ordenada;
            ordenada = aux;
            
        } else {
        	
            anterior = ordenada;
            while (anterior->siguiente != NULL && strcmp(anterior->siguiente->game.genero, aux->game.genero) <= 0) {
            	
                anterior = anterior->siguiente;
            }
            aux->siguiente = anterior->siguiente;
            anterior->siguiente = aux;
        }
    }

    *pColeccion = ordenada;
}

//Busqueda Secuencial segun el Titulo
void Busqueda(tListaJuego *pColeccion) {
	
    tListaJuego *aux;

    if (ExisteJuego(pColeccion, &aux)) {
    	
        printf("\nJuego Encontrado:\n");
        printf("Saga: %s\n", aux->game.saga);
        printf("Titulo: %s\n", aux->game.titulo);
        printf("Genero: %s\n", aux->game.genero);
        printf("Ano: %d\n", aux->game.ano);
        printf("Minutos Jugados: %d\n", aux->game.minJugados);
        
    } else {
    	
        printf("\nEl Juego NO Existe en la Coleccion.\n");
    }
}


bool ExisteJuego(tListaJuego *pColeccion, tListaJuego **pEncontrado) {
	
    tListaJuego *aux;
    tString tituloBuscar;

    printf("Ingresar Titulo del Juego a Buscar: ");
    fgets(tituloBuscar, Max_Char, stdin);
    tituloBuscar[strcspn(tituloBuscar, "\n")] = '\0';

    aux = pColeccion;

    while (aux != NULL) {
    	
        if (strcmp(aux->game.titulo, tituloBuscar) == 0) {
        	
            *pEncontrado = aux;
            return true;
   		}
        aux = aux->siguiente;
    }

    *pEncontrado = NULL;
    return false;
}

//Grabado de la coleccion en un Archivo Binario
void GrabarColeccion(tListaJuego *pColeccion) {
	
    tListaJuego *aux;

    archColeccion = fopen("Coleccion.dat", "wb");

    if (archColeccion == NULL) {
    	
        printf("No se Puede Iniciar el Archivo.\n");
        exit(EXIT_FAILURE);
    }

    aux = pColeccion;

    while (aux != NULL) {
    	
        if (fwrite(&aux->game, sizeof(tJuego), 1, archColeccion) != 1) {
        	
            printf("Error al Grabar la Coleccion.\n");
            fclose(archColeccion);
            exit(EXIT_FAILURE);
        }

        aux = aux->siguiente;
    }

    fclose(archColeccion);
}

//Eliminar los Datos de un Juego
void EliminarJuego(tListaJuego **pColeccion) {
	
    tListaJuego *aux;
    tListaJuego *anteriorAux;

    if (ExisteJuego(*pColeccion, &aux)) {
    	
        if (aux == *pColeccion) {
        	
            *pColeccion = aux->siguiente;
        } else {
        	
            anteriorAux = *pColeccion;
            while (anteriorAux->siguiente != aux) {
            	
                anteriorAux = anteriorAux->siguiente;
            }
            anteriorAux->siguiente = aux->siguiente;
        }

        free(aux);
        printf("\nJuego Eliminado de la Coleccion.\n");
        
    } else {
    	
        printf("\nEl Juego NO Existe en la Coleccion.\n");
    }
}


// Funciones para los cortes de Control
void PrincipioCorte() {
	
    minTotales = 0;
    cantJuegos = 0;
    masMinutos = -1;
    strcpy(masMinJuego, juego.titulo);
}

void unJuego() {
	
    minTotales += juego.minJugados;
    cantJuegos++;

    if (masMinutos < juego.minJugados) {
    	
        masMinutos = juego.minJugados;
        strcpy(masMinJuego, juego.titulo);
    }
}

void ProcesoCorteSaga() {
	
    archColeccion = fopen("Coleccion.dat", "rb");

    if (archColeccion == NULL) {
    	
        printf("No se Encuentra el Archivo.\n");
        return;
    }

    if (fread(&juego, sizeof(tJuego), 1, archColeccion) != 1) {
    	
        printf("La Coleccion Esta Vacia.\n");
        fclose(archColeccion);
        return;
    }
	juegoAnterior = juego;
	
    acumMasMinCorte = -1;
    acumMasMin = 0;
    acumCantJuegos = 0;

    PrincipioCorte();

    while (!feof (archColeccion)){
		
		PrincipioCorte ();
		while (!feof (archColeccion) && strcmp(juego.saga, juegoAnterior.saga) == 0){
			
			unJuego();
			juegoAnterior = juego;
			fread (&juego, sizeof(tJuego), 1, archColeccion);
		}
		
		FinCorteSaga();
	}
	
	FinalCorteSaga();
}

void FinCorteSaga() {
	
    acumMasMin += minTotales;
    acumCantJuegos += cantJuegos;

    if (acumMasMinCorte < minTotales) {
        acumMasMinCorte = minTotales;
        strcpy(masMinCorte, juegoAnterior.saga);
    }

    printf("\n*** Informe Saga %s ***\n\n", juegoAnterior.saga);
    printf("Cantidad de Juegos de la Saga: %d\n", cantJuegos);
    printf("Minutos Totales en la Saga: %d\n", minTotales);
    printf("Juego mas Jugado de la Saga: %s (%d Minutos)\n",masMinJuego, masMinutos);
    
    juegoAnterior = juego;
}

void FinalCorteSaga() {
	
    printf("\n*** Informe Coleccion ***\n\n");
    printf("Minutos Totales de la Coleccion: %d\n", acumMasMin);
    printf("Cantidad de Juegos en la Coleccion: %d\n", acumCantJuegos);
    printf("Saga mas Jugada de la Coleccion: %s (%d Minutos)\n", masMinCorte, acumMasMinCorte);

    fclose(archColeccion);
}

void ProcesoCorteGenero() {
	
    archColeccion = fopen("Coleccion.dat", "rb");

    if (archColeccion == NULL) {
        printf("No se Encuentra el Archivo.\n");
        return;
    }

    if (fread(&juego, sizeof(tJuego), 1, archColeccion) != 1) {
    	
        printf("La Coleccion esta Vacia.\n");
        fclose(archColeccion);
        return;
    }

    juegoAnterior = juego;
    acumMasMinCorte = -1;
    acumMasMin = 0;
    acumCantJuegos = 0;

    PrincipioCorte();

    while (!feof (archColeccion)){
		
		PrincipioCorte ();
		while (!feof (archColeccion) && strcmp(juego.genero, juegoAnterior.genero) == 0){
			
			unJuego();
			juegoAnterior = juego;
			fread (&juego, sizeof(tJuego), 1, archColeccion);
		}
		
		FinCorteGenero();
	}
	
	FinalCorteGenero();
}

void FinCorteGenero() {
	
    acumMasMin += minTotales;
    acumCantJuegos += cantJuegos;

    if (acumMasMinCorte < minTotales) {
        acumMasMinCorte = minTotales;
        strcpy(masMinCorte, juegoAnterior.genero);
    }

    printf("\n*** Informe Genero %s ***\n\n", juegoAnterior.genero);
    printf("Cantidad de Juegos del Genero: %d\n", cantJuegos);
    printf("Minutos Totales en el Genero: %d\n", minTotales);
    printf("Juego mas Jugado en el Genero: %s (%d Minutos)\n", masMinJuego, masMinutos);
    
	juegoAnterior = juego;
}

void FinalCorteGenero() {
	
    printf("\n*** Informe Coleccion ***\n\n");
    printf("Minutos Totales de la Coleccion: %d\n", acumMasMin);
    printf("Cantidad de Juegos en la Coleccion: %d\n", acumCantJuegos);
    printf("El Genero mas Jugado de la Coleccion: %s (%d Minutos)\n", masMinCorte, acumMasMinCorte);

    fclose(archColeccion);
}

// Finalizacion del programa
void Finalizacion(tListaJuego *pColeccion) {
	
    tListaJuego *aux;

    while (pColeccion != NULL) {
        aux = pColeccion;
        pColeccion = pColeccion->siguiente;
        free(aux);
    }

    printf("\nMemoria liberada correctamente.\n");
    printf("Programa finalizado.\n");
}
