#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*ESTRUCTURAS*/

typedef struct doctor{
    char id_medico[30];
    char nombre[30];
    char primer_apellido[30];
    char especialidad[30];
    char turno[10];   
    struct doctor* sig;
} Doctor;
Doctor* cabezaDoctor = NULL;

typedef struct paciente{
    char id_paciente[30];
    char nombre[30];
    char primer_apellido[30];
    char edad[30]; /*edad debe ser en años*/
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
    Tiempo horaCita;
    Fecha fechaCita;
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
    char id_doctor[30];
    
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
    scanf("%s", &id_doctor);
    
    
    strcpy(nuevoDoctor->nombre, nombreDoctor);
    strcpy(nuevoDoctor->primer_apellido, primerApellido);
    strcpy(nuevoDoctor->especialidad, especialidadDoctor);
    strcpy(nuevoDoctor->turno, turno);
    strcpy(nuevoDoctor->id_medico,id_doctor);
    
    if(cabezaDoctor == NULL){
        cabezaDoctor = nuevoDoctor;
        cabezaDoctor->sig = NULL;
    }
    else{
        cabezaDoctor->sig = nuevoDoctor;
        nuevoDoctor->sig = NULL;
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
    char edad[30]; 
    char id_paciente[30];
    
    Paciente* nuevoPaciente = (Paciente*)malloc(sizeof(Paciente));
    
    printf("Ingrese el nombre del paciente: ");
    scanf("%s", &nombrePaciente);
    printf("Ingrese el apellido del paciente: ");
    scanf("%s", &apellidoPaciente);
    printf("Ingrese el teléfono del paciente (respete el formato ####-####: ");
    scanf("%s", &telefono);
    printf("Ingrese la edad en años del paciente: ");
    scanf("%s", &edad);
    printf("Ingrese el id del paciente: ");
    scanf("%s", &id_paciente);
    
    strcpy(nuevoPaciente->nombre, nombrePaciente);
    strcpy(nuevoPaciente->primer_apellido, apellidoPaciente);
    strcpy(nuevoPaciente->telefono, telefono);
    strcpy(nuevoPaciente->edad,edad);
    strcpy(nuevoPaciente->id_paciente,id_paciente);
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

bool buscarPaciente(char* nombrePaciente, Paciente* ListaPaciente){
    /*Un paciente no puede tener más de una cita en la misma fecha y hora un  
    paciente  no  puede  programar  una  cita  con  un  médico  que  no  esté registrado*/
}

bool buscarDoctor(char* nombreDoctor, Doctor* ListaDoctor){
    /*Un paciente no puede tener más de una cita en la misma fecha y hora un  
    paciente  no  puede  programar  una  cita  con  un  médico  que  no  esté registrado*/
}

/*Funcion que agrega una cita a la lista de citas
 */
void agregarCita(){
    
}

void estaDoctor(Doctor* tempDoctor, char* nombre){
    /*Busca al doctor en el archivo de texto*/
    
}

/*Función que almacena los pacientes de la lista en un txt
 * Entradas: la cabeza de la lista de pacientes
 * Salidas: los datos almacenados en el txt
 */
void guardarPacientes(Paciente* ListaPacientes){
    /*Almacena pacientes en el pacientes.txt*/
    FILE * miarchivo;
    char* nombrearchivo = "pacientes.txt";
    Paciente* temp = ListaPacientes;
    miarchivo = fopen(nombrearchivo, "w"); //agrega al final de la lista
    
    while(temp != NULL){
        fprintf(miarchivo, "%s, %s, %s, %s, %s\r\n", 
            temp->nombre,temp->primer_apellido, temp->telefono, temp->edad, temp->id_paciente);
        temp = temp->sig;
    }
    fclose(miarchivo);
}

/*Función que almacena los doctorres de la lista en un txt
 * Entradas: la cabeza de la lista de doctores
 * Salidas: los datos almacenados en el txt
 */
void guardarDoctores(Doctor* ListaDoctores){
    /*Almacena doctores en el doctores.txt*/
    
    FILE* miarchivo;
    char* nombrearchivo = "doctores.txt";
    Doctor* temp = ListaDoctores;
    miarchivo=fopen(nombrearchivo,"w");
    
    while(temp != NULL){
            fprintf(miarchivo, "%s, %s, %s, %s, %s \r\n", 
                temp->nombre, temp->primer_apellido, temp->especialidad, temp->turno, temp->id_medico);
            temp = temp->sig;
    }
    fclose(miarchivo);
    
}

void guardarCitas(Cita* ListaCitas){
    /*Almacena doctores en el citas.txt*/
}

/*Funcion que separa la linea de texto del txt correspondiente y devuelve una estructura Doctor
 Entradas: la linea de texto
 Salida: estructura Doctor*/

Doctor* separarStringDoctor(char linea[]){
    char* nombreDoctor;
    char* primerApellido;
    char* especialidadDoctor;
    char* turno;
    char* id_doctor;
    
    Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
    
    char * pch;
    pch = strtok (linea," ,.-");
    int contador = 0;
    
    while (pch != NULL)
    {
        switch(contador){
            case 0:
                nombreDoctor = pch;
                strcpy(nuevoDoctor->nombre, nombreDoctor);
                //printf("%s\n", nombreDoctor);
            case 1:
                primerApellido = pch;
                strcpy(nuevoDoctor->primer_apellido, primerApellido);
            case 2:
                especialidadDoctor = pch;
                strcpy(nuevoDoctor->especialidad, especialidadDoctor);
            case 3:
                turno = pch;
                strcpy(nuevoDoctor->turno, turno);
            case 4:
                id_doctor = pch;
                strcpy(nuevoDoctor->id_medico, id_doctor);
              
        }
        contador = contador+1;
        //printf ("%s\n",pch);
        pch = strtok (NULL, " ,.-");
        
    }
    return nuevoDoctor;
}

/*Función que imprime la lista doctores
 */
void imprimirLista(Doctor* ptr){
    while (ptr != NULL){
        printf("El nombre del doctor es %s, %s, %s, %s, %s\n", ptr->nombre, ptr->primer_apellido, ptr->especialidad,
                ptr->turno, ptr->id_medico);
        ptr = ptr ->sig;
    }
}

/*Función que imprime la lista pacientes
 */
void imprimirListaPaciente(Paciente* ptr){
    while (ptr != NULL){
        printf("El nombre del paciente es %s, %s, %s, %s, %s\n", ptr->nombre, ptr->primer_apellido, ptr->telefono,
                ptr->edad, ptr->id_paciente);
        ptr = ptr ->sig;
    }
}

/*Función que lee el txt y carga los datos en memoria
 * Entradas: no tiene entradas
 * Salidas: los datos cargados en memoria
 */
void cargarDatosDoctor(){
    FILE *miarchivo;
    char linea[256];
    char *resultado;

    miarchivo = fopen("doctores.txt", "rt");

    if (miarchivo == NULL) {
            printf("Error: No se ha podido crear el fichero doctores.txt");
    } else {
            resultado = fgets(linea, 256, miarchivo);

            while (resultado != NULL) {
                    //printf("%s", linea);
                    Doctor* doc = separarStringDoctor(linea);
                    
                    if(cabezaDoctor == NULL){
                        cabezaDoctor = doc;
                        cabezaDoctor->sig = NULL;
                    }
                    else{
                        doc->sig = cabezaDoctor;
                        cabezaDoctor = doc;
                    }
                    resultado = fgets(linea, 256, miarchivo);
            }
            fclose(miarchivo);
            imprimirLista(cabezaDoctor);
    }
}

/*Funcion que separa la linea de texto del txt correspondiente y devuelve una estructura Paciente
 Entradas: la linea de texto
 Salida: estructura Paciente*/

Paciente* separarStringPaciente(char linea[]){
    char* nombrePaciente;
    char* apellidoPaciente;
    char* telefono;
    char* edad; 
    char* id_paciente;
    
    Paciente* nuevoPaciente = (Paciente*)malloc(sizeof(Paciente));
    
    char * pch;
    pch = strtok (linea," ,.-");
    int contador = 0;
    
    while (pch != NULL)
    {
        switch(contador){
            case 0:
                nombrePaciente = pch;
                strcpy(nuevoPaciente->nombre, nombrePaciente);
            case 1:
                apellidoPaciente = pch;
                strcpy(nuevoPaciente->primer_apellido, apellidoPaciente);
            case 2:
                telefono = pch;
                strcpy(nuevoPaciente->telefono, telefono);
            case 3:
                edad = pch;
                strcpy(nuevoPaciente->edad, edad);
            case 4:
                id_paciente = pch;
                strcpy(nuevoPaciente->id_paciente,id_paciente);
              
        }
        contador = contador+1;
        //printf ("%s\n",pch);
        pch = strtok (NULL, " ,.-");
        
    }
    return nuevoPaciente;
}

/*Función que lee el txt y carga los datos en memoria
 * Entradas: no tiene entradas
 * Salidas: los datos cargados en memoria
 */
void cargarDatosPaciente(){
    FILE *miarchivo;
    char linea[256];
    char *resultado;

    miarchivo = fopen("pacientes.txt", "rt");

    if (miarchivo == NULL) {
            printf("Error: No se ha podido crear el fichero doctores.txt");
    } else {
            resultado = fgets(linea, 256, miarchivo);

            while (resultado != NULL) {
                    //printf("%s", linea);
                    Paciente* paciente = separarStringPaciente(linea);
                    
                    if(cabezaPaciente == NULL){
                        cabezaPaciente = paciente;
                        cabezaPaciente->sig = NULL;
                    }
                    else{
                        paciente->sig = cabezaPaciente;
                        cabezaPaciente = paciente;
                    }
                    resultado = fgets(linea, 256, miarchivo);
            }
            fclose(miarchivo);
            imprimirListaPaciente(cabezaPaciente);
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
                cargarDatosDoctor();
                cargarDatosPaciente();
                break;
            case 2:
                agregarDoctor();
                break;
            case 3:
                //agregarPaciente();
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
                bandera = false;
                break;
        }
    }
}

int main(int argc, char** argv) {
    imprimirMenu();
    return 0;
}

