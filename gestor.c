#include <stdio.h>
#define MAX 50
struct Incidencia {
    int id;
    int prioridad;
    int estado;
};
void introducir_incidencia (struct Incidencia lista[], int *total);
void listar_incidencia (struct Incidencia lista[], int total);
void cerrar_incidencia (struct Incidencia lista[], int total, int id);

int main() {
    struct Incidencia lista[MAX];
    int menu=0;
    int total=0;

        printf("Bienvenid@ al gestor de incidencias\n");
    do {
        printf("Elige un numero para acceder\n");
        printf("1. Introducir incidencia\n");
        printf("2. Listado de la incidencia\n");
        printf("3. Modificar estado de la incidencia\n");
        printf("4. Salir\n");
        scanf("%d",&menu);


        switch (menu) {

            case 1:{
                introducir_incidencia(lista, &total);


                break;
            }
            case 2: {
                listar_incidencia(lista, total);

                break;
            }
            case 3: {
                int id;
                printf("Ingrese el id del incidencia que deseas modificar \n");
                scanf("%d",&id);
                cerrar_incidencia(lista, total,id);

                break;
            }
            case 4: {
                printf("Saliendo\n");
                break;
            }
            default: {
                printf("Opcion no valida\n");
            }
        }
    }while (menu!=4);

    return 0;
}

void introducir_incidencia (struct Incidencia lista[], int *total) {
    printf("Da de dalta en el sistema la incidencia \n");

    if (*total >= MAX) { //si el valor de total es mayor al del array no hay espacio
        printf("No hay espacio para mas incidencias\n");
        return;
    }

                    do {
                        printf("Ingrese el id de la  incidencia \n");
                        scanf("%d",&lista[*total].id);

                    }while(lista[*total].id<=0); //si es menor o igual de cero no se admite

                         for (int i=0; i<*total; i++) {
                            if (lista[i].id == lista[*total].id) {
                            printf("ERROR,numero de incidencia repetido \n");
                                return;
                            }
                         }

                    do {
                        printf("Introduce el nivel de prioridad que desea aplicar a la incidencia\n");
                        printf("1-ALTA,2-MEDIA,3-BAJA\n ");
                        scanf("%d",&lista[*total].prioridad);
                    }while (lista[*total].prioridad<1 || lista[*total].prioridad>3);

                    lista[*total].estado =0;
                    printf("Incidencia numero %d insertada correctamente\n",lista[*total].id);
                    (*total)++;

}



void listar_incidencia (struct Incidencia lista[], int total) {
    for (int i=0; i<total; i++) {
        printf("-ID Incidencia: %d\n",lista[i].id);
        printf("-Prioridad: %d\n",lista[i].prioridad);
        if (lista[i].estado==0) {
            printf("ABIERTA\n");
        }
        else if (lista[i].estado==1) {
            printf("CERRADA\n");
        }
        printf("\n");
    }



}
void cerrar_incidencia (struct Incidencia lista[], int total,int id) {
    for (int i=0; i<total; i++) {
        if (lista[i].id==id) {
            do {
                printf("Modifique la incidencia %d\n",id);
                printf("0-ABIERTO 1-CERRADO, \n");
                scanf("%d",&lista[i].estado);
            }while (lista[i].estado<0 || lista[i].estado>1);
            return;
        }

    }
    printf("No existe el id de la incidencia \n");


}
