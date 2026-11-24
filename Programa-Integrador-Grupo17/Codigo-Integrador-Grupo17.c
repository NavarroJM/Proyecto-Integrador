#include "TADColeccion.h"

//Declaracion del Menu
void Menu(tListaJuego **);

// Funcion Principal
int main(void) {
    tListaJuego *coleccion = NULL;

    GrabarColeccion(coleccion);

    Menu(&coleccion);

    return 0;
}

//Desarrollo del Menu
void Menu(tListaJuego **pColeccion) {
	
    int opcion;

    do {
    	
        printf("\n*** Menu de Coleccion ***\n\n");
        printf("1- Agregar Juego\n");
        printf("2- Eliminar Juego\n");
        printf("3- Buscar Juego en Coleccion\n");
        printf("4- Informe de Coleccion por Saga\n");
        printf("5- Informe de Coleccion por Genero\n");
        printf("0- Terminar Programa\n\n");

        printf("Ingrese una Opcion: ");

        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
        	
            case 1:
                AgregarJuego(pColeccion);
                OrdenarPorSaga(pColeccion);
                GrabarColeccion(*pColeccion);
                break;

            case 2:
                EliminarJuego(pColeccion);
                GrabarColeccion(*pColeccion);
                break;

            case 3:
                Busqueda(*pColeccion);
                break;

            case 4:
                OrdenarPorSaga(pColeccion);
                GrabarColeccion(*pColeccion);
                ProcesoCorteSaga();
                break;

            case 5:
                OrdenarPorGenero(pColeccion);
                GrabarColeccion(*pColeccion);
                ProcesoCorteGenero();
                break;

            case 0:
                Finalizacion(*pColeccion);
                break;

            default:
                printf("Opcion Invalida!\n");
        }

    } while (opcion != 0);
}
