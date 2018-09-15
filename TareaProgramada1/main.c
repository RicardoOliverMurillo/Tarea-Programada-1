#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct doctor{
    int id_medico;
    char nombre[30];
    char primer_apellido[30];
    char especialidad[30];
    char turno[10];   
    struct doctor* sig;
} Doctor;
Doctor* cabezaDoctor = NULL;

typedef struct paciente{
    int id_paciente;
    char nombre[30];
    char primer_apellido[30];
    int edad; /*edad debe ser en años*/
    char telefono[30]; /*formato debe ser ####-####*/
    struct paciente* sig;
} Paciente;
Paciente* cabezaPaciente = NULL;

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
    char horaCita[100];
    char fechaCita[100];
    struct cita* sig;
}Cita;
Cita* cabezaCita = NULL;

/*Función que agrega un nuevo doctor a la lista de doctores*/
/*Entradas: no contiene entradas*/
/*Salidas: se almacena el nuevo doctor en la lista*/
void agregarDoctor(){
    char nombreDoctor[30];
    char primerApellido[30];
    char especialidadDoctor[30];
    char turno[10];
    int id_doctor;
    
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
    
    if(cabezaDoctor == NULL){
        cabezaDoctor = nuevoDoctor;
        cabezaDoctor->sig = NULL;
    }
    else{
        nuevoDoctor->sig = cabezaDoctor;
        cabezaDoctor = nuevoDoctor;
    }
    printf("El médico se añadió exitosamente...\n");
}

/*Función que se encarga de escribir en un txt los pacientes que se registran*/
/*Entradas: no tiene entradas*/
/*Salidas: Se escribe en el txt los datos*/
void agregarPaciente(){
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char telefono[30];
    int edad; 
    int id_paciente;
    
    Paciente* nuevoPaciente = (Paciente*)malloc(sizeof(Paciente));
    
    printf("Ingrese el nombre del paciente: ");
    scanf("%s", &nombrePaciente);
    printf("Ingrese el apellido del paciente: ");
    scanf("%s", &apellidoPaciente);
    printf("Ingrese el teléfono del paciente (respete el formato ####-####): ");
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
    if(cabezaPaciente == NULL){
        cabezaPaciente = nuevoPaciente;
        cabezaPaciente->sig = NULL;
    }
    else{
        nuevoPaciente->sig = cabezaPaciente;
        cabezaPaciente = nuevoPaciente;
    }
    printf("El paciente se añadió exitosamente...\n");
}

/*Funcion para buscar al doctor en el sistema*/
bool estaDoctor(Doctor* Doctor, char* nombreDoctor){
        while (Doctor != NULL){
        if (strcmp(Doctor->nombre, nombreDoctor)==0){
            return true;
        }
        else{
            Doctor=Doctor->sig;
        }
    }
    return false;
}
/*Funcion para buscar el paciente en el sistema*/
bool estaPaciente(Paciente* tempPaciente, char* nombrePaciente){
    while (tempPaciente != NULL){
        if (strcmp(tempPaciente->nombre, nombrePaciente)==0){
            return true;
        }
        else{
            tempPaciente=tempPaciente->sig;
        }
    }
    return false;
}
/*Funcion para agregar una cita*/
void generarCita(){
    char doctorSolicitado [20];
    char nombrePaciente[20];
    int id_doctor;
    int id_cliente;
    char fecha[100];
    char hora[100];
    /*verifica que el paciente este en el sistema, en caso de no estarlo debe crear al usuario*/
    printf("Inserte el nombre del paciente: ");
    scanf("%s", &nombrePaciente);
    if (estaPaciente(cabezaPaciente, nombrePaciente)==false){
        agregarPaciente();
    }
    /*Verifica que el doctor se encuentre en el sistema, en caso de no estarlo lo crea*/
    printf("Inserte el nombre del doctor:");
    scanf("%s", &doctorSolicitado);
    if (estaDoctor(cabezaDoctor, doctorSolicitado)==false){
        printf("El doctor no se encuentra registrado\n");
        agregarDoctor();
    }
    printf("Inserte la fecha de la cita: ");
    scanf("%s", &fecha);
    printf("Inserte la hora: ");
    scanf("%s", &hora);
    /*crea la estructura cita para almacenar la informacion en el sistema de citas*/
    Cita* nuevaCita = (Cita*)malloc(sizeof(Cita));
    strcpy(nuevaCita->fechaCita, fecha);
    strcpy(nuevaCita->horaCita, hora);
    nuevaCita->id_medico=cabezaDoctor->id_medico;
    nuevaCita->id_paciente=cabezaPaciente->id_paciente;
    if(cabezaCita == NULL){
        cabezaCita = nuevaCita;
        cabezaCita->sig = NULL;
    }
    else{
        nuevaCita->sig = cabezaCita;
        cabezaCita = nuevaCita;
    }
    printf("hice la cita");
}

void guardarPacientes(Paciente* ListaPacientes){
    /*Almacena pacientes en el pacientes.txt*/
    FILE * miarchivo;
    char* nombrearchivo = "pacientes.txt";
    Paciente* temp = ListaPacientes;
    
    while(temp != NULL){
       miarchivo = fopen(nombrearchivo, "a"); //agrega al final de la lista
        fprintf(miarchivo, "%s, %s, %s, %d, %d\r\n", 
            temp->nombre,temp->primer_apellido, temp->telefono, temp->edad, temp->id_paciente);
        temp = temp->sig;
    }
    fclose(miarchivo);
}

void guardarDoctores(Doctor* ListaDoctores){
    /*Almacena doctores en el doctores.txt*/
    
    FILE* miarchivo;
    char* nombrearchivo = "doctores.txt";
    Doctor* temp = ListaDoctores;
    while(temp != NULL){
        miarchivo=fopen(nombrearchivo,"a");
        fprintf(miarchivo, "%s, %s, %s, %s, %d \r\n", 
            temp->nombre, temp->primer_apellido, temp->especialidad, temp->turno, temp->id_medico);
        temp = temp->sig;
    }
    fclose(miarchivo);
    
}

void guardarCitas(Cita* nuevaCita){
    /*Almacena doctores en el citas.txt*/
    
    FILE* miarchivo;
    char* nombrearchivo = "Citas.txt";
    Cita* temp = nuevaCita;
    while(temp != NULL){
        miarchivo=fopen(nombrearchivo,"a");
        fprintf(miarchivo, "%d, %d, %s, %s \r\n", 
            temp->id_medico, temp->id_paciente, temp->fechaCita, temp->horaCita);
        temp = temp->sig;
    }
    fclose(miarchivo);
}

void separarString(char linea[]){
    char * pch;
    pch = strtok (linea," ,.-");
    while (pch != NULL)
    {
        printf ("%s\n",pch);
        pch = strtok (NULL, " ,.-");
    }
}
void cargarDatos(){
    FILE *miarchivo;
    char linea[256];
    char *resultado;

    miarchivo = fopen("doctores.txt", "rt");

    if (miarchivo == NULL) {
            printf("Error: No se ha podido crear el fichero doctores.txt");
    } else {
            resultado = fgets(linea, 256, miarchivo);

            while (resultado != NULL) {
                    printf("%s", linea);
                    separarString(linea);
                    resultado = fgets(linea, 256, miarchivo);
            }
            fclose(miarchivo);
    }
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
                system("clear");
                cargarDatos();
                
                break;
            case 2:
                system("clear");
                agregarDoctor();
                break;
            case 3:
                system("clear");
                generarCita();
                break;
            case 4:
                printf("Seleccione la opción que desea ver: \n"
                "1. Médico con más citas y promedio general de citas\n 2. Especialidad con más citas y promedio de citas"
                        "por especialidad\n 3. Promedio de citas por paciente\n");
                scanf("d%", &opcionEstadistica);
                break;
            case 5:
                /*Actualizar los datos del txt, con la informacion almacenada en las listas*/
                guardarDoctores(cabezaDoctor);
                guardarPacientes(cabezaPaciente);
                guardarCitas(cabezaCita);
                bandera = false;
                break;
        }
    }
}

int main(int argc, char** argv) {
    imprimirMenu();
    return 0;
}

