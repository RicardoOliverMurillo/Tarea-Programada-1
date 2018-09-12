#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
                agregarDoctor();
                break;
            case 3:
                agregarPaciente();
                break;
            case 4:
                printf("Seleccione la opción que desea ver: \n"
                "1. Médico con más citas y promedio general de citas\n 2. Especialidad con más citas y promedio de citas"
                        "por especialidad\n 3. Promedio de citas por paciente\n");
                scanf("d%", &opcionEstadistica);
                break;
            case 5:
                /*Actualizar los datos del txt, con la informacion almacenada en las listas*/
                
                bandera = false;
                break;
        }
    }
}

/*ESTRUCTURAS*/

typedef struct doctor{
    int id_medico;
    int cantidad_citas;
    char nombre[100];
    char primer_apellido[100];
    char especialidad[100];
    char turno[10];    
    struct doctor sig;
} Doctor;

typedef struct paciente{
    int id_paciente;
    char nombre[100];
    char primer_apellido[100];
    int edad; /*edad debe ser en años*/
    char telefono[100]; /*formato debe ser ####-####*/
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

/*Almacena la informacion del doctor en un archivo 
 y genera una lista enlazada*/
void agregarDoctor(){
    char nombreDoctor[100];
    char primerApellido[100];
    char especialidadDoctor[100];
    char turno[10];
    int id_doctor;
    struct doctor sig = NULL;
    Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
    
    printf("Inserte el nombre del doctor: ");
    scanf("%s", &nombreDoctor);
    printf("Inserte el primer apellido del doctor: ");
    scanf("%s", &primerApellido);
    printf("Inserte la especialidad del doctor: ");
    scanf("%s", &especialidadDoctor);
    printf("Inserte el turno del doctor: ");
    scanf("%s", &turno);
    printf("Inserte el id del doctor: ");
    scanf("%d", &id_doctor);
    
    
    strcpy(nuevoDoctor->nombre, nombreDoctor);
    strcpy(nuevoDoctor->primer_apellido, primerApellido);
    strcpy(nuevoDoctor->especialidad, especialidadDoctor);
    strcpy(nuevoDoctor->turno, turno);
    nuevoDoctor->id_medico = id_doctor;
    
    /*Quitar cuando ya funcione como queremos*/
    
    FILE * miarchivo;
    char* nombrearchivo = "doctores.txt";
    
    miarchivo=fopen(nombrearchivo,"a");
    fprintf(miarchivo, "%s, %s, %s, %s, %d \r\n", 
            nuevoDoctor->nombre, nuevoDoctor->primer_apellido, nuevoDoctor->especialidad, nuevoDoctor->turno, nuevoDoctor->id_medico);
    fclose(miarchivo);
}

/*Función que se encarga de escribir en un txt los pacientes que se registran*/
/*Entradas: no tiene entradas*/
/*Salidas: Se escribe en el txt los datos*/
void agregarPaciente(){
    char nombrePaciente[100];
    char apellidoPaciente[100];
    char telefono[100];
    int edad; 
    int id_paciente;
    Paciente* nuevoPaciente = (Paciente*)malloc(sizeof(Paciente));
    
    printf("Ingrese el nombre del paciente: ");
    scanf("%s", &nombrePaciente);
    printf("Ingrese el apellido del paciente: ");
    scanf("%s", &apellidoPaciente);
    printf("Ingrese el teléfono del paciente (respete el formato ####-####: ");
    scanf("%s", &telefono);
    printf("Ingrese la edad en años del paciente: ");
    scanf("%d", &edad);
    printf("Ingrese el id del paciente: ");
    scanf("%d", &id_paciente);
    
    strcpy(nuevoPaciente->nombre, nombrePaciente);
    strcpy(nuevoPaciente->primer_apellido, apellidoPaciente);
    strcpy(nuevoPaciente->telefono, telefono);
    nuevoPaciente->edad = edad;
    nuevoPaciente->id_paciente = id_paciente;
    /*Se deben validar los formatos de los datos ingresados
     */
    
    FILE * miarchivo;
    char* nombrearchivo = "pacientes.txt";
    
    miarchivo = fopen(nombrearchivo, "a"); //agrega al final de la lista
    fprintf(miarchivo, "%s, %s, %s, %d, %d\r\n", 
            nuevoPaciente->nombre,nuevoPaciente->primer_apellido, nuevoPaciente->telefono, nuevoPaciente->edad, nuevoPaciente->id_paciente);
    fclose(miarchivo);
}

void buscarDoctor(){
    /*Un médico no puede tener dos citas en la misma fecha y hora
    Un médico no puede tener citas en horas diferentes a las de su turno*/
}

void buscarPaciente(){
    /*Un paciente no puede tener más de una cita en la misma fecha y hora un  
    paciente  no  puede  programar  una  cita  con  un  médico  que  no  esté registrado*/
    
}

void estaDoctor(Doctor* tempDoctor, char* nombre){
    /*Busca al doctor en el archivo de texto*/
    
}

void guardarPacientes(Paciente* ListaPacientes){
    /*Almacena pacientes en el pacientes.txt*/
}

void guardarDoctores(Doctor* ListaDoctores){
    /*Almacena doctores en el doctores.txt*/
}

void guardarCitas(Cita* ListaCitas){
    /*Almacena doctores en el citas.txt*/
}

void cargarDatos(){
    /*Cargar datos en memoria, crear listas enlazadas con los datos*/
}

void calcularPromedioDoctor(){
    /*cantidad_citas/cantidad_medicos, estadistica 1 (dentro de la progra)
     El  formato  del  mensaje  será:    Médico  con  más  citas  es nombre y apellido del médico, especialista en especialidad. 
     Tiene X citas. Promedio general es : promedio general citas por médico*/
}

void calcularPromedioEspecialidad(){
    /*Igual que el calcularPromedioDoctor solo que con especialidades*/
    /*El formato del mensaje de salida es el siguiente: 
    Especialidad con mas citas es especialidad
    Promedio de citas de la especialidad es promedio*/
}

void calcularPromedioPacientes(){
    /*dividir length(citas)/length(pacientes)
     El  formato  del  mensaje  es:  Promedio  de  citas  por  paciente  es promedio*/
}

int main(int argc, char** argv) {
    imprimirMenu();
    return 0;
}

