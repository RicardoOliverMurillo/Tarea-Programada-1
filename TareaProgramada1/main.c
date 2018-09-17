/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Maria de la Paz Bloise, Ricardo Oliver y Anjelica Tristani
 *
 * Created on 14 de septiembre de 2018, 03:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/******************************************************************************/
/*ESTRUCTURAS*/

typedef struct paciente{
    char id_paciente[30];
    char nombre[30];
    char primer_apellido[30];
    char edad[30]; /*edad debe ser en años*/
    char telefono[30]; /*formato debe ser ####-####*/
    struct paciente* sig;
} Paciente;
Paciente* cabezaPaciente = NULL;

typedef struct doctor{
    char id_medico[30];
    char nombre[30];
    char primer_apellido[30];
    char especialidad[30];
    char turno[10];
    char cantCitas[10];
    struct doctor* sig;
} Doctor;
Doctor* cabezaDoctor = NULL;

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
    char id_medico[30];
    char id_paciente[30];
    char horaCita[100];
    char fechaCita[100];
    struct cita* sig;
}Cita;
Cita* cabezaCita = NULL;

typedef struct especialidad{
    char nombre[30];
    int cant;
    struct especialidad* sig;
}Especialidad;
Especialidad* cabezaEspecialidad = NULL;

/******************************************************************************/
/*FUNCIONES ESPECIALIDAD*/

/*Funcion que agrega la especialidad en la lista con la cantidad correcta*/
bool agregarEspecialidad(char especialidad[]){
    //estructura doctor que se va a agregar a la lista
    char nueva[30];
    Especialidad* nuevaEspecialidad = (Especialidad*)malloc(sizeof(Especialidad));
    Especialidad* temp = cabezaEspecialidad;
    strcpy(nueva, especialidad);

    while(temp != NULL){
        if(strcmp(temp->nombre, nueva) == 0){
            ++temp->cant;
            return true;
        }
        temp = temp->sig;
    }
    
    strcpy(nuevaEspecialidad->nombre, especialidad);
    nuevaEspecialidad->cant = 1;
    //se añade a la lista de doctores
    if(cabezaEspecialidad == NULL){
        cabezaEspecialidad = nuevaEspecialidad;
        cabezaEspecialidad->sig = NULL;
    }
    else{
        nuevaEspecialidad->sig = cabezaEspecialidad;
        cabezaEspecialidad = nuevaEspecialidad;
    }
    return false;
}

/*Funcion que devuelve el largo de la lista especialidad*/
void imprimirListaEspecialidad(Especialidad* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("El nombre de la especialidad es %s con %d cantidad de citas", ptr->nombre, ptr->cant);
        ptr = ptr ->sig;
    }
}
/******************************************************************************/
/*FUNCIONES DOCTOR*/

/*Función que agrega elementos a la lista doctores*/
void agregarDoctor(){
    //atributos para crear la estructura doctor
    char id_medico[30];
    char nombre[30];
    char primer_apellido[30];
    char especialidad[30];
    char turno[10];
    char cantCitas[10];
    
    //estructura doctor que se va a agregar a la lista
    Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
    
    //se capturan los datos en pantalla para agregar a la lista
    printf("Inserte el nombre del doctor: ");
    scanf("%s", &nombre);
    printf("Inserte el primer apellido del doctor: ");
    scanf("%s", &primer_apellido);
    printf("Inserte la especialidad del doctor: ");
    scanf("%s", &especialidad);
    printf("Inserte el turno del doctor: ");
    scanf("%s", &turno);
    printf("Inserte el id del doctor: ");
    scanf("%s", &id_medico);
    
    //se copian los datos en la estructura
    strcpy(nuevoDoctor->nombre, nombre);
    strcpy(nuevoDoctor->primer_apellido, primer_apellido);
    strcpy(nuevoDoctor->especialidad, especialidad);
    strcpy(nuevoDoctor->turno, turno);
    strcpy(nuevoDoctor->id_medico, id_medico);
    strcpy(nuevoDoctor->cantCitas, "0");
    
    //se añade a la lista de doctores
    if(cabezaDoctor == NULL){
        cabezaDoctor = nuevoDoctor;
        cabezaDoctor->sig = NULL;
    }
    else{
        nuevoDoctor->sig = cabezaDoctor;
        cabezaDoctor = nuevoDoctor;
    }
    
    agregarEspecialidad(nuevoDoctor->especialidad);
    printf("El médico se añadió exitosamente...\n");   
}

/*Función para imprimir la lista de doctores*/
void imprimirListaDoctor(Doctor* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("El nombre del doctor es %s, %s, %s, %s, %s, %s", ptr->nombre, ptr->primer_apellido, ptr->especialidad,
                ptr->turno, ptr->id_medico, ptr->cantCitas);
        ptr = ptr ->sig;
    }
}

/*Función para guardar datos en medicos.txt*/
void guardarDatosDoctores(Doctor* cabeza){
    //atributos para crear el archivo txt
    Doctor* temp = cabeza;
    FILE* miarchivo; //puntero que se utiliza para manejar archivos
    char* nombrearchivo = "medicos.txt";
    miarchivo = fopen(nombrearchivo, "w"); //escribe sobre el txt y si no existe lo crea
    
    //recorre la lista de doctores
    while(temp != NULL){
        if(strcmp(temp->nombre, " ") != 0){
            fprintf(miarchivo, "%s %s %s %s %s %s\r\n", temp->nombre,temp->primer_apellido,temp->especialidad,
                temp->turno,temp->id_medico, temp->cantCitas);
        }
        temp = temp->sig;
    }
    //cierra el archivo
    fclose(miarchivo);
}

/*Funcion que recorre la linea de texto y separa las palabras cuando encuentra un espacio*/
/*Salida: estructura doctor*/
Doctor* leerStringDoctor(char linea[]){
    //atributos
    Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
    char * pch;
    pch = strtok(linea," ,.-");
    int contador = 0;
    
    //recorre la linea de texto
    while (pch != NULL)
    {
        //copia las palabras en el espacio correspondiente de la estructura
        switch(contador){
            case 0:
                strcpy(nuevoDoctor->nombre, pch);
            case 1:
                strcpy(nuevoDoctor->primer_apellido, pch);
            case 2:
                strcpy(nuevoDoctor->especialidad, pch);
            case 3:
                strcpy(nuevoDoctor->turno, pch);
            case 4:
                strcpy(nuevoDoctor->id_medico, pch);
            case 5:
                strcpy(nuevoDoctor->cantCitas, pch);

        }
        contador = contador+1;
        pch = strtok(NULL, " ,.-");
        
    }
    return nuevoDoctor;
}

/*Función que carga los datos de medicos.txt a memoria*/
void cargarDatosDoctores(){
    //atributos
    FILE* miarchivo;
    char linea[256];
    char* resultado;
    miarchivo = fopen("medicos.txt", "rt");
    //verifica que el archivo exista
    if (miarchivo == NULL) {
            printf("Error: No se ha podido crear el fichero doctores.txt");
    }else{
        //verifica que no haya llegado al final del archivo
        while (feof(miarchivo) == 0){
            resultado = fgets(linea, 256, miarchivo);
            Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
            if((resultado != NULL) && (*resultado != '#')){
                
                nuevoDoctor = leerStringDoctor(resultado);
                agregarEspecialidad(nuevoDoctor->especialidad);
                //se añade a la lista de doctores
                if(cabezaDoctor == NULL){
                    cabezaDoctor = nuevoDoctor;
                    cabezaDoctor->sig = NULL;
                }else{
                    nuevoDoctor->sig = cabezaDoctor;
                    cabezaDoctor = nuevoDoctor;
                }
            }
        }
    }
}

/*Funcion que devuelve el largo de la lista doctores*/
int largoDoctores(Doctor* cabeza){
    int largo = 0;
    Doctor* temp = cabeza;
    while(temp != NULL){
        ++largo;
        temp = temp->sig;
    }
    return largo;
}

void aumentarCita(Doctor* actual){
    
   
}
/******************************************************************************/
/*FUNCIONES PACIENTE*/

/*Funcion que verifica el id del paciente*/
bool verificarId(char id[], Paciente* cabeza){
    Paciente* temp = cabeza;
    char idNuevo[10];
    strcpy(idNuevo,id);
    while(temp != NULL){
        if(strcmp(temp->id_paciente, idNuevo)){
            return true;
        }
        temp = temp->sig;
    }
    return false;
}
/*Funcion que agrega un paciente a la lista de pacientes*/
void agregarPaciente(){
    //atributos
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char telefono[30];
    char edad[30]; 
    char id_paciente[30];
    
    Paciente* nuevoPaciente = (Paciente*)malloc(sizeof(Paciente));
    
    //se capturan los datos desde el teclado
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
    
    if(verificarId(id_paciente, cabezaPaciente)){
        printf("Error: id previamente rgistrado, ingrese un nuevo id: ");
        scanf("%s", &id_paciente);
    }
    
    //se almacenan los datos en los atributos de la estructura
    strcpy(nuevoPaciente->nombre, nombrePaciente);
    strcpy(nuevoPaciente->primer_apellido, apellidoPaciente);
    strcpy(nuevoPaciente->telefono, telefono);
    strcpy(nuevoPaciente->edad,edad);
    strcpy(nuevoPaciente->id_paciente,id_paciente);
    
    //se añade a la lista de doctores
    if(cabezaPaciente == NULL){
        cabezaPaciente = nuevoPaciente;
        cabezaPaciente->sig = NULL;
    }
    else{
        nuevoPaciente->sig = cabezaPaciente;
        cabezaPaciente = nuevoPaciente;
    }
    
    //mensaje de salida
    printf("El paciente se añadió exitosamente...\n");
}

/*Función para imprimir la lista de doctores*/
void imprimirListaPaciente(Paciente* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("El nombre del paciente es %s, %s, %s, %s, %s", ptr->nombre, ptr->primer_apellido, ptr->telefono,
                ptr->edad, ptr->id_paciente);
        ptr = ptr ->sig;
    }
}

/*Función para guardar datos en pacientes.txt*/
void guardarDatosPaciente(Paciente* cabeza){
    //atributos para crear el archivo txt
    Paciente* temp = cabeza;
    FILE* miarchivo; //puntero que se utiliza para manejar archivos
    char* nombrearchivo = "pacientes.txt";
    miarchivo = fopen(nombrearchivo, "w"); //escribe sobre el txt y si no existe lo crea
    
    //recorre la lista de doctores
    while(temp != NULL){
        fprintf(miarchivo, "%s %s %s %s %s\r\n", temp->nombre,temp->primer_apellido,temp->telefono,
                temp->edad,temp->id_paciente);
        temp = temp->sig;
    }
    //cierra el archivo
    fclose(miarchivo);
}

/*Funcion que recorre la linea de texto y separa las palabras cuando encuentra un espacio*/
/*Salida: estructura paciente*/
Paciente* leerStringPaciente(char linea[]){
    //atributos
    Paciente* nuevoPaciente = (Paciente*)malloc(sizeof(Paciente));
    char * pch;
    pch = strtok(linea," ,.");
    int contador = 0;
    
    //recorre la linea de texto
    while (pch != NULL)
    {
        //copia las palabras en el espacio correspondiente de la estructura
        switch(contador){
            case 0:
                strcpy(nuevoPaciente->nombre, pch);
            case 1:
                strcpy(nuevoPaciente->primer_apellido, pch);
            case 2:
                strcpy(nuevoPaciente->telefono, pch);
            case 3:
                strcpy(nuevoPaciente->edad, pch);
            case 4:
                strcpy(nuevoPaciente->id_paciente, pch);

        }
        contador = contador+1;
        pch = strtok(NULL, " ,.");
        
    }
    return nuevoPaciente;
}

/*Función que carga los datos de medicos.txt a memoria*/
void cargarDatosPacientes(){
    //atributos
    FILE* miarchivo;
    char linea[256];
    char* resultado;
    miarchivo = fopen("pacientes.txt", "rt");
    //verifica que el archivo exista
    if (miarchivo == NULL) {
            printf("Error: No se ha podido crear el fichero pacientes.txt");
    }else{
        //verifica que no haya llegado al final del archivo
        while (feof(miarchivo) == 0){
            resultado = fgets(linea, 256, miarchivo);
            Paciente* nuevoPaciente = (Paciente*)malloc(sizeof(Paciente));
            if((resultado != NULL) && (*resultado != '#')){
                
                nuevoPaciente = leerStringPaciente(resultado);
               
                //se añade a la lista de doctores
                if(cabezaPaciente == NULL){
                    cabezaPaciente = nuevoPaciente;
                    cabezaPaciente->sig = NULL;
                }else{
                    nuevoPaciente->sig = cabezaPaciente;
                    cabezaPaciente = nuevoPaciente;
                }
            }
        }
    }
}

/*Funcion que devuelve el largo de la lista doctores*/
int largoPacientes(Paciente* cabeza){
    int largo = 0;
    Paciente* temp = cabeza;
    while(temp != NULL){
        ++largo;
        temp = temp->sig;
    }
    return largo;
}
/******************************************************************************/
/*FUNCIONES CITA*/

/*Funcion para buscar al doctor en el sistema*/
bool estaDoctor(Doctor* Doctor, char* nombreDoctor, int verificar){
        while (Doctor != NULL){
        if (strcmp(Doctor->nombre, nombreDoctor)==0){
            if(verificar ==0){
               int num = (int)Doctor->cantCitas[0]-47;
                char c = '0'+num;
                Doctor->cantCitas[0]= c;
                return true;
            }
            else{
                return true;
            } 
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
    char doctorSolicitado[20];
    char nombrePaciente[20];
    char id_doctor[30];
    char id_paciente[30];
    char fecha[100];
    char hora[100];
    
    /*verifica que el paciente este en el sistema, en caso de no estarlo debe crear al usuario*/
    printf("Inserte el nombre del paciente: ");
    scanf("%s", &nombrePaciente);
    if (estaPaciente(cabezaPaciente, nombrePaciente)==false){
        printf("Paciente no registrado, ingrese su información personal...\n");
        agregarPaciente();
    }else{
        strcpy(id_paciente, cabezaPaciente->id_paciente);
    }
    /*Verifica que el doctor se encuentre en el sistema, en caso de no estarlo lo crea*/
    printf("Inserte el nombre del doctor:");
    scanf("%s", &doctorSolicitado);
    if (estaDoctor(cabezaDoctor, doctorSolicitado,1)==false){
        printf("El doctor no se encuentra registrado\n");
        //agregarDoctor();
    }else{
        if (estaDoctor(cabezaDoctor, doctorSolicitado,0)==true){
            strcpy(id_doctor, cabezaDoctor->id_medico);
            
            
        }
        printf("Inserte la fecha de la cita: ");
        scanf("%s", &fecha);
        printf("Inserte la hora: ");
        scanf("%s", &hora);
        
        /*crea la estructura cita para almacenar la informacion en el sistema de citas*/
        Cita* nuevaCita = (Cita*)malloc(sizeof(Cita));
        
        strcpy(nuevaCita->fechaCita, fecha);
        strcpy(nuevaCita->horaCita, hora);
        strcpy(nuevaCita->id_medico, cabezaDoctor->id_medico);
        strcpy(nuevaCita->id_paciente, cabezaPaciente->id_paciente);
        
        if(cabezaCita == NULL){
            cabezaCita = nuevaCita;
            cabezaCita->sig = NULL;
        }
        else{
            nuevaCita->sig = cabezaCita;
            cabezaCita = nuevaCita;
        }
        printf("Cita registrada\n");
    }
}

/*Funcion que guarda los elementos de la lista citas en el archivo citas.txt*/
void guardarCitas(Cita* cabeza){
    FILE* miarchivo;
    char* nombrearchivo = "citas.txt";
    Cita* temp = cabeza;
    miarchivo=fopen(nombrearchivo,"w");
    
    while(temp != NULL){
        fprintf(miarchivo, "%s %s %s %s\r\n", 
            temp->id_medico, temp->id_paciente, temp->fechaCita, temp->horaCita);
        temp = temp->sig;
    }
    fclose(miarchivo);
}

/*Funcion que recorre la linea de texto y separa las palabras cuando encuentra un espacio*/
/*Salida: estructura cita*/
Cita* leerStringCita(char linea[]){
    //atributos
    Cita* nuevaCita = (Cita*)malloc(sizeof(Cita));
    char * pch;
    pch = strtok(linea," ,.");
    int contador = 0;
    
    //recorre la linea de texto
    while (pch != NULL)
    {
        //copia las palabras en el espacio correspondiente de la estructura
        switch(contador){
            case 0:
                strcpy(nuevaCita->id_medico, pch);
            case 1:
                strcpy(nuevaCita->id_paciente, pch);
            case 2:
                strcpy(nuevaCita->fechaCita, pch);
            case 3:
                strcpy(nuevaCita->horaCita, pch);

        }
        contador = contador+1;
        pch = strtok(NULL, " ,.");
        
    }
    return nuevaCita;
}

/*Función que carga los datos de citas.txt a memoria*/
void cargarDatosCitas(){
    //atributos
    FILE* miarchivo;
    char linea[256];
    char* resultado;
    miarchivo = fopen("citas.txt", "rt");
    //verifica que el archivo exista
    if (miarchivo == NULL) {
            printf("Error: No se ha podido crear el fichero citas.txt");
    }else{
        //verifica que no haya llegado al final del archivo
        while (feof(miarchivo) == 0){
            resultado = fgets(linea, 256, miarchivo);
            Cita* nuevaCita = (Cita*)malloc(sizeof(Cita));
            if((resultado != NULL) && (*resultado != '#')){
                
                nuevaCita = leerStringCita(resultado);
               
                //se añade a la lista de doctores
                if(cabezaCita == NULL){
                    cabezaCita = nuevaCita;
                    cabezaCita->sig = NULL;
                }else{
                    nuevaCita->sig = cabezaCita;
                    cabezaCita = nuevaCita;
                }
            }
        }
    }
}

/*Función para imprimir la lista de citas*/
void imprimirListaCita(Cita* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("Información sobre la cita: id medico: %s, id paciente: %s, fecha: %s, hora: %s\n", ptr->id_medico, ptr->id_paciente, 
                ptr->fechaCita, ptr->horaCita);
        ptr = ptr ->sig;
    }
}

/*Funcion que devuelve el largo de la lista citas*/
int largoCitas(Cita* cabeza){
    int largo = 0;
    Cita* temp = cabeza;
    while(temp != NULL){
        ++largo;
        temp = temp->sig;
    }
    return largo;
}
/******************************************************************************/
/*FUNCIONES ESTADISTICAS*/

/*Funcion que genera el promedio de pacientes con respecto a citas*/
void promedioPacientes(){
    int pacientes = largoPacientes(cabezaPaciente);
    int citas = largoCitas(cabezaCita);
    float promedio = pacientes/citas;
    printf("Promedio de citas por paciente es %f \n", promedio);
}

/*Funcion que muestra el médico con más citas y el promedio de citas entre doctores*/
void promedioDoctores(){
    int mayor = -1;
    Doctor* temp = cabezaDoctor;
    char nombre[30];
    char apellido[30];
    char especialidad[30];
    int promedio = 0;
    
    while(temp != NULL){
        int num = (int)(temp->cantCitas[0]-48); //convierte el char a un int
        
        //printf("Numero: %d y nombre: %s\n", num, temp->nombre);
        if(num > mayor){
            strlcpy(nombre, temp->nombre, sizeof(nombre));
            strlcpy(apellido, temp->primer_apellido,sizeof(apellido));
            strlcpy(especialidad, temp->especialidad, sizeof(especialidad));
            mayor = num;
        }
        temp = temp->sig;
    }
    
    int citas = largoCitas(cabezaCita);
    int doc = largoDoctores(cabezaDoctor);
    promedio = citas/doc;
    
    //Valida si existen dolores con citas
    if(mayor>0){
        printf("Médico  con  más  citas  es %s  %s, especialista en %s. Tiene %d cita(as).\n", nombre, apellido, especialidad, mayor);
        printf("Promedio general es : %d citas por médico\n", promedio);
    }else{
        printf("Los medicos no tienen citas\n");
    }
}

/*Funcion que muestra el promedio de especialidades*/
void promedioEspecialidad(){
    
}

/*Función que imprime el menu de estadisticas*/
void imprimirMenuEstadisticas(){
    int opcion;
    printf("###############################################################\n");
    printf("Estadísticas...\n");
    printf("  1.Médico con más citas y promedio general de citas\n");
    printf("  2.Especialidad con más citas y promedio de citas por especialidad\n");
    printf("  3.Promedio de citas por paciente\n");
    printf("\nRespuesta:");
    scanf("%d", &opcion);
    printf("###############################################################\n");
  
    switch(opcion){
        case 1:
            promedioDoctores();
            break;
        case 2:
            printf("No disponible/n");
            break;
        case 3:
            promedioPacientes();
            break;
    }
}
/******************************************************************************/
/*FUNCION PARA EL MAIN*/

/*Función que imprime el menú principal de la aplicación*/
void imprimirMenu(){
    bool bandera = true;
    int opcionSeleccionada;
    
    while(bandera == true){
        printf("###############################################################\n");
        printf("Bienvenido... Seleccione alguna de las siguientes opciones: \n");
        printf("1.Cargar datos\n");
        printf("2.Resgistar nuevo médico\n");
        printf("3.Programar citas\n");
        printf("4.Estadísticas\n");
        printf("5.Salir\n");
        printf("\nRespuesta:");
        scanf("%d", &opcionSeleccionada);
        printf("###############################################################\n");
        
        switch(opcionSeleccionada){
            case 1:
                cargarDatosDoctores();
                cargarDatosPacientes();
                cargarDatosCitas();
                //largo de listas para verificar que haya infromacion para mostrar
                int largoDoc = largoDoctores(cabezaDoctor);
                int largoPaciente = largoPacientes(cabezaPaciente);
                int largoCita = largoCitas(cabezaCita);
                
                if((largoDoc == 0)&& (largoPaciente == 0) && (largoCita == 0)){
                    printf("No existen datos disponibles para cargar...\n");
                }else{
                    printf("Sus datos fueron cargados a memoria...\n");
                }
                break;
            case 2:
                agregarDoctor();
                break;
            case 3:
                generarCita();
                break;
            case 4:
                imprimirMenuEstadisticas();
                break;
            case 5:
                guardarDatosDoctores(cabezaDoctor);
                guardarDatosPaciente(cabezaPaciente);
                guardarCitas(cabezaCita);
                
                bandera = false;
                break;
        }
    }
}

int main(int argc, char** argv) {
    imprimirMenu();
    return (EXIT_SUCCESS);
}

