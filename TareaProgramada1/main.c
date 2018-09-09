#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Función que activa el menú principal*/
/*Entradas: no cuenta con entradas principales, dentro de la función se solicita el número de opción que desea ejecutar*/
/*Salidas: menú principal de la aplicación, ejecuta funciones depende de la opción seleccionada*/

void imprimirMenu(){
        
    bool bandera = true;
    int opcionSeleccionada;
    int opcionEstadistica = 0;
    
    while(bandera == true){
        printf("###############################################################\n");
        printf("Bienvenido... Seleccione alguna de las siguientes opciones: \n");
        printf("1. Cargar datos \n2. Resgistar nuevo médico \n3. Programar citas \n4. Estadísticas \n5. Salir \n");
        printf("\nOpción seleccionada:");
        scanf("%d", &opcionSeleccionada);
        printf("###############################################################\n");
        
        switch(opcionSeleccionada){
            case 1:
                printf("###");
                break;
            case 2:
                printf("###");
                break;
            case 3:
                printf("###");
                break;
            case 4:
                printf("Seleccione la opción que desea ver: \n"
                "1. Médico con más citas y promedio general de citas\n 2. Especialidad con más citas y promedio de citas"
                        "por especialidad\n 3. Promedio de citas por paciente\n");
                scanf("d%", &opcionEstadistica);
                break;
            case 5:
                bandera = false;
                break;
        }
    }
}

/*ESTRUCTURAS*/

typedef struct doctor{
    int id_medico;
    char* nombre;
    char* primer_apellido;
    char* especialidad;
    char* turno;
} Doctor;

typedef struct paciente{
    int id_paciente;
    char* nombre;
    char* primer_apellido;
    int edad; /*edad debe ser en años*/
    char* telefono; /*formato debe ser ####-####*/
} Paciente;

typedef struct tiempo{
    int hora;
    int minutos;
    /*deben ser solo de las 08.00 a 19.00*/
}Tiempo;

typedef struct fecha{
    int dia;
    int mes;
    int anio;
    /*formato debe ser dd-mm-aaaa*/
}Fecha;

typedef struct cita{
    int id_medico;
    int id_paciente;
    Tiempo horaCita;
    Fecha fechaCita;
}Cita;


int main(int argc, char** argv) {
    imprimirMenu();
    return 0;
}

