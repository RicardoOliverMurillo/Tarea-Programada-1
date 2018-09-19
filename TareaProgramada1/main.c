/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Maria de la Paz Bloise, Ricardo Oliver y Anjelica Tristani
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <regex.h>

/******************************************************************************/
/*ESTRUCTURAS*/

/*Estructura para crear la lista enlazada de pacientes*/
typedef struct paciente{
    char id_paciente[30];
    char nombre[30];
    char primer_apellido[30];
    char edad[30]; 
    char telefono[30];
    struct paciente* sig;
} Paciente;
Paciente* cabezaPaciente = NULL;

/*Estructura para crear la lista enlazada de medicos*/
typedef struct doctor{
    char id_medico[30];
    char nombre[30];
    char primer_apellido[30];
    char especialidad[30];
    char turno[20];
    char cantCitas[10];
    struct doctor* sig;
} Doctor;
Doctor* cabezaDoctor = NULL;

/*Estructura para crear la lista enlazada de citas*/
typedef struct cita{
    char id_medico[30];
    char id_paciente[30];
    char horaCita[100];
    char fechaCita[100];
    struct cita* sig;
}Cita;
Cita* cabezaCita = NULL;

/*Estructura para crear la lista enlazada de especialidades*/
typedef struct especialidad{
    char nombre[30];
    int cant;
    int cantMedicos; 
    struct especialidad* sig;
}Especialidad;
Especialidad* cabezaEspecialidad = NULL;

/******************************************************************************/
/*FUNCIONES ESPECIALIDAD*/

/*
 * Funcion que agrega la especialidad en la lista enlazada, aumenta la cantidad si ya
 * existe y aumenta el total de doctores
 * Entradas: el nombre de la especialidad
 * Salidas: true (si la especialidad ya existe) y false (si la especialidad no existe)
 */
bool agregarEspecialidad(char especialidad[]){
    char nueva[30]; //arreglo donde se almacena el nombre de especialidad
    Especialidad* nuevaEspecialidad = (Especialidad*)malloc(sizeof(Especialidad)); //reserva espacio de memoria
    Especialidad* temp = cabezaEspecialidad; //temporal para recorrer la lista especialidad
    strcpy(nueva, especialidad);
    while(temp != NULL){
        if(strcmp(temp->nombre, nueva) == 0){
            ++temp->cant;
            ++temp->cantMedicos;
            return true;
        }
        temp = temp->sig;
    }
    //Se agrega la especialidad en la lista si no existe previamente
    strcpy(nuevaEspecialidad->nombre, especialidad);
    nuevaEspecialidad->cant = 1;
    nuevaEspecialidad->cantMedicos = 1;

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

/*
 * Funcion que devuelve el largo de la lista especialidad
 * Entradas: la cabeza de la lista especialidad
 * Salidas: Imprime en consola los atributos de la lista
 */
void imprimirListaEspecialidad(Especialidad* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("El nombre de la especialidad es %s con %d cantidad de citas", ptr->nombre, ptr->cant);
        ptr = ptr ->sig;
    }
}


/*
 * Funcion que compara el formato de telefono que se introduce y verifica que sea
 * compatible con el utilizado en el sistema
 * Entrada: un arreglo de char con el telefono que se ingresó desde consola
 * Salida: true (si el formato es correcto) y false (si el formato es incorrecto) 
 */
bool compararTelefono(char* tempTelefono){
    regex_t regex;
    int reti;
    char mensaje[100];
    //Compila la expresion regular dentro de los limitantes
    reti = regcomp(&regex, "^([0-9]{4})-([[0-9]{4})$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "No se pudo compilar\n");
        exit(1);
    }
    //Ejecuta la expresion regular
    reti = regexec(&regex, tempTelefono, 0, NULL, 0);
    if (!reti) {
        return true;
    }
    else if (reti == REG_NOMATCH) {
        return false;
    }
    else {
        regerror(reti, &regex, mensaje, sizeof(mensaje));
        fprintf(stderr, "Fallo en la compilacion: %s\n", mensaje);
        exit(1);
    }
    //Libera el espacio en memoria
    regfree(&regex);
}

/*
 * Funcion que compara el formato de la fecha que se introduce y verifica que sea
 * compatible con el utilizado en el sistema
 * Entrada: un arreglo de char con la fecha que se ingresó desde consola
 * Salida: true (si el formato es correcto) y false (si el formato es incorrecto) 
 */
bool compararFecha(char* tempFecha){
    regex_t regex;
    int reti;
    char mensaje[100];
    //Compila la expresion regular dentro de los limitantes
    reti = regcomp(&regex, "^([0-9]{1}|[0-9]{2})-([0-9]{1}|[0-9]{2})-([0-9]{4})$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    //Ejecuta la expresion regular
    reti = regexec(&regex, tempFecha, 0, NULL, 0);
    if (!reti) {
        return true;
    }
    else if (reti == REG_NOMATCH) {
        return false;
    }
    else {
        regerror(reti, &regex, mensaje, sizeof(mensaje));
        fprintf(stderr, "Regex match failed: %s\n", mensaje);
        exit(1);
    }
    //Libera el espacio en memoria
    regfree(&regex);
}


/******************************************************************************/
/*FUNCIONES DOCTOR*/

/*
 * Funcion que verifica el id del doctor
 * Entradas: el id del nuevo doctor y la cabeza de la lista doctor
 * Salidas: true (si existe un doctor con ese id) y false (si el id esta disponible)
 */
bool verificarIdDoc(char id[], Doctor* cabeza){
    Doctor* temp = cabeza;
    char idNuevo[20];
    strcpy(idNuevo,id);
    while(temp != NULL){
        if(strcmp(temp->id_medico, idNuevo)==0){
            return true;
        }
        temp = temp->sig;
    }
    return false;
}

/*
 * Función que agrega elementos a la lista doctores
 * Entradas: no tiene entradas
 * Salidas: no tiene salidas
 */
void agregarDoctor(){
    //atributos para crear la estructura doctor
    char id_medico[30];
    char nombre[30];
    char primer_apellido[30];
    char especialidad[30];
    char turno[10];
    
    //estructura doctor que se va a agregar a la lista
    Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
    
    //se capturan los datos en pantalla para agregar a la lista
    printf("Inserte el nombre del doctor: ");
    scanf("%s", &nombre);
    printf("Inserte el primer apellido del doctor: ");
    scanf("%s", &primer_apellido);
    printf("Inserte la especialidad del doctor: ");
    scanf("%s", &especialidad);
    printf("Elija el número de la opción para el turno del doctor\n");
    printf("    1. Día\n");
    printf("    2. Tarde\n");
    printf("    3. Todo el día\n");
    printf("Respuesta: ");
    scanf("%s", &turno);
    printf("Inserte el id del doctor: ");
    scanf("%s", &id_medico);
    
    if(verificarIdDoc(id_medico, cabezaDoctor) == true){
        printf("Error: id previamente registrado, ingrese un nuevo id: ");
        scanf("%s", &id_medico);
    }
    
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
    printf("El médico se añadió exitosamente...\n");   
}

/*
 * Funcion que devuelve el largo de la lista doctores
 * Entradas: la cabeza de la lista doctores
 * Salidas: Imprime en consola los atributos de la lista
 */
void imprimirListaDoctor(Doctor* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("El nombre del doctor es %s, %s, %s, %s, %s, %s", ptr->nombre, ptr->primer_apellido, ptr->especialidad,
                ptr->turno, ptr->id_medico, ptr->cantCitas);
        ptr = ptr ->sig;
    }
}

/*
 * Función para guardar datos en el txt correspondiente (medicos.txt)
 * Entrada: la cabeza de la lista doctores
 * Salidas: no tiene salidas
 */
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
                temp->turno,temp->id_medico, temp->cantCitas); //escribe en el txt
        }
        temp = temp->sig;
    }
    //cierra el archivo
    fclose(miarchivo);
}

/*
 * Funcion que recorre la linea de texto y separa las palabras cuando encuentra un espacio
 * Entradas: la linea del txt
 * Salida: estructura doctor con los datos extraidos del txt
 */
Doctor* leerStringDoctor(char linea[]){
    //atributos
    Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
    char * pch;
    pch = strtok(linea," ,.-"); //separa la linea al encontrar alguna de los simbolos
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

/*
 * Función que carga los datos de medicos.txt a memoria.
 * Entradas: no tiene entradas.
 * Salidas: no tiene salidas.
 */
void cargarDatosDoctores(){
    //atributos
    FILE* miarchivo;
    char linea[256];
    char* resultado;
    miarchivo = fopen("medicos.txt", "rt");
    //verifica que el archivo exista
    if (miarchivo == NULL) {
            printf("Archivo doctores.txt vacio\n");
    }else{ 
        while (feof(miarchivo) == 0){ //verifica que no haya llegado al final del archivo
           
            resultado = fgets(linea, 256, miarchivo); //extrae la linea del txt
            Doctor* nuevoDoctor = (Doctor*)malloc(sizeof(Doctor));
            if((resultado != NULL)){
                
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

/*
 * Funcion que devuelve el largo de la lista doctor
 * Entradas: la cabeza de la lista doctor
 * Salidas: un entero con el largo de la lista doctor
 */
int largoDoctores(Doctor* cabeza){
    int largo = 0; //variable para almacenar el largo
    Doctor* temp = cabeza;
    
    while(temp != NULL){ //ciclo que recorre la lista
        ++largo;
        temp = temp->sig;
    }
    return largo;
}

/******************************************************************************/
/*FUNCIONES PACIENTE*/

/*
 * Funcion que verifica el id del paciente
 * Entradas: el id del nuevo paciente y la cabeza de la lista doctor
 * Salidas: true (si existe un paciente con ese id) y false (si el id esta disponible)
 */
bool verificarId(char id[], Paciente* cabeza){
    Paciente* temp = cabeza;
    char idNuevo[10];
    strcpy(idNuevo,id);
    while(temp != NULL){
        if(strcmp(temp->id_paciente, idNuevo)==0){
            return true;
        }
        temp = temp->sig;
    }
    return false;
}

/*
 * Función que agrega elementos a la lista paciente
 * Entradas: no tiene entradas
 * Salidas: no tiene salidas
 */
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
    printf("Ingrese el teléfono del paciente (respete el formato ####-####): ");
    scanf("%s", &telefono);
    
    while(compararTelefono(telefono)==false){ //verifica el formato del telefono (####-####)
        printf("Inserte un formato de telefono valido (####-####): ");
        scanf("%s", &telefono);
    }
    
    printf("Ingrese la edad en años del paciente: ");
    scanf("%s", &edad);
    printf("Ingrese el id del paciente: ");
    scanf("%s", &id_paciente);
    
    if(verificarId(id_paciente, cabezaPaciente)){ //verifica la existencia del id
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

/*
 * Función para imprimir la lista de pacientes
 * Entrada: la cabeza de la lista paciente
 * Salida: imprime en consola los atributos de la lista paciente
 */
void imprimirListaPaciente(Paciente* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("El nombre del paciente es %s, %s, %s, %s, %s", ptr->nombre, ptr->primer_apellido, ptr->telefono,
                ptr->edad, ptr->id_paciente);
        ptr = ptr ->sig;
    }
}

/*
 * Función que carga los datos de pacientes.txt a memoria.
 * Entradas: la cabeza de la lista pacientes.
 * Salidas: no tiene salidas.
 */
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

/*
 * Funcion que separa la linea del txt para generar la nueva estructura paciente
 * Entradas: arreglo de char con la linea del txt
 * Salida: estructura paciente
 */
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

/*
 * Función que carga los datos de pacientes.txt a memoria.
 * Entradas: no tiene entradas.
 * Salidas: no tiene salidas.
 */
void cargarDatosPacientes(){
    //atributos
    FILE* miarchivo;
    char linea[256];
    char* resultado;
    miarchivo = fopen("pacientes.txt", "rt");
    //verifica que el archivo exista
    if (miarchivo == NULL) {
            printf("Archivo pacientes.txt vacio\n");
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

/*
 * Funcion que devuelve el largo de la lista paciente
 * Entradas: la cabeza de la lista paciemte
 * Salidas: un entero con el largo de la lista pacientes
 */
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

/*
 * Funcion para buscar al doctor en el sistema
 * Entradas: la cabeza de la lista doctor, el nombre del doctor, un entero para
 * verificar si se desea aumentar la cantidad de citas
 * Salidas: true (si el doctor es encontrado) y false (si el doctor no existe) 
 */
bool estaDoctor(char* nombreDoctor, int verificar){
    Doctor* temp = cabezaDoctor;
        while (temp != NULL){
        if (strcmp(temp->nombre, nombreDoctor)==0){
            if(verificar ==0){
               int num = (int)temp->cantCitas[0]-47;
                char c = '0'+num;
                temp->cantCitas[0]= c;
                return true;
            }
            else{
                return true;
            } 
        }
        temp=temp->sig;
    }
    return false;
}

/*
 * Funcion para buscar al paciente en el sistema
 * Entradas: la cabeza de la lista pacientes, el nombre del paciente
 * Salidas: true (si el paciente es encontrado) y false (si el paciente no existe) 
 */
bool estaPaciente(Paciente* tempPaciente, char* nombrePaciente){
    while (tempPaciente != NULL){
        if (strcmp(tempPaciente->nombre, nombrePaciente)==0){
            return true;
        }
        tempPaciente=tempPaciente->sig;
    }
    return false;
}

/*
 * Funcion que valida que el paciente no tenga una cita registrada al mismo dia en la misma hora
 * Entradas: un arreglo de char para la fecha, un arreglo de char para el id del paciente
 * y un arreglo de char con la hora
 * Salidas: true (si el paciente tiene una cita previa en esa hora y en esa fecha) y
 * false (si el paciente tiene el horario disponible)
 */
bool horarioRepetidoPaciente(char fecha[], char id_paciente[], char hora[]){
    Cita* temp = cabezaCita;
    while(temp != NULL){
        if(strcmp(temp->id_paciente, id_paciente)==0){
            if((strcmp(temp->fechaCita, fecha)==0) && (strcmp(temp->horaCita, hora)==0)){
                return true;
            }
        }
        temp = temp->sig;
    }
    return false;
}

/*
 * Funcion que valida que el doctor no tenga una cita registrada al mismo dia en la misma hora
 * Entradas: un arreglo de char para la fecha, un arreglo de char para el id del doctor
 * y un arreglo de char con la hora
 * Salidas: true (si el doctor tiene una cita previa en esa hora y en esa fecha) y
 * false (si el doctor tiene el horario disponible)
 */
bool horarioRepetidoDoctor(char fecha[], char id_medico[], char hora[]){
    Cita* temp = cabezaCita;
    while(temp != NULL){
        if(strcmp(temp->id_medico, id_medico)==0){
            if((strcmp(temp->fechaCita, fecha)==0) && (strcmp(temp->horaCita, hora)==0)){
                return true;
            }
        }
        temp = temp->sig;
    }
    return false;
}

/*
 * Funcion que valida que las horas de las citas sean compatibles con el horario del doctor
 * Entradas: un arreglo char con el turno y un arreglo char con la hora
 * Salida: true (si el horario es compatible) y false (si el horario no es compatible)
 */
bool validarTurno(char turno[], char hora[]){
    int numero;
    int opcion;
    numero = atoi(hora);
    opcion = atoi(turno);
    switch(opcion){
        case 1:
            if((numero>=8) && (numero<=12)){
                return true;
            }
        case 2:
            if((numero>=14) && (numero<=19)){
                return true;
            }
        case 3:
            if(((numero>=9) && (numero<=12)) || ((numero>=14) && (numero<=17))){
                return true;
            }
    }
    return false;
}

/*
 * Funcion para agregar una cita a la lista citas
 * Entradas: no tiene entradas
 * Salidas: no tiene salidas
 */
void generarCita(){
    //atributos
    char doctorSolicitado[20];
    char nombrePaciente[20];
    char id_doctor[30];
    char id_paciente[30];
    char fecha[100];
    char hora[100];
    
    //verifica que el paciente este en el sistema, en caso de no estarlo debe crear al usuario
    printf("Inserte el nombre del paciente: ");
    scanf("%s", &nombrePaciente);
    
    if (estaPaciente(cabezaPaciente, nombrePaciente)==false){
        printf("Paciente no registrado, ingrese su información personal...\n");
        agregarPaciente();
    }else{
        strcpy(id_paciente, cabezaPaciente->id_paciente);
        printf("ID DEL PACIENTE %s\n",cabezaPaciente->id_paciente);
    }
    //Verifica que el doctor se encuentre en el sistema, en caso de no estarlo lo crea
    printf("Inserte el nombre del doctor: ");
    scanf("%s", &doctorSolicitado);
    
    if (estaDoctor(cabezaDoctor, doctorSolicitado,1)==false){
        printf("El doctor no se encuentra registrado\n");
    }else{
        
        if (estaDoctor(cabezaDoctor, doctorSolicitado,0)==true){
            printf("ID DEL MEDICO %s\n",cabezaDoctor->id_medico);
            
            strcpy(id_doctor, cabezaDoctor->id_medico);
            agregarEspecialidad(cabezaDoctor->especialidad); //agrega la especialidad a la lista
        }
        printf("Inserte la fecha (dd-mm-aaaa): ");
        scanf("%s", &fecha);
        while(compararFecha(fecha)==false){ //verifica el formato de la fecha
            printf("Inserte un formato de fecha valido (dd-mm-aaaa): ");
            scanf("%s", &fecha);
        }
        printf("Inserte la hora: ");
        scanf("%s", &hora);
        
        int largo = strlen(hora); //verifica el formato de la hora
        while(largo != 2){ //de estar el formato incorrecto solicita la hora nuevamente
            printf("Inserte un formato de hora válido (##): ");
            scanf("%s", &hora);
            largo = strlen(hora);
        }
        
        //verifica que el paciente no tenga una cita previa en el horario que ingresa
        if(horarioRepetidoPaciente(fecha, cabezaPaciente->id_paciente, hora)== true){
            printf("El paciente tiene una cita previamente registrada a esa hora en esa fecha...\n"
                    "Ingrese un nuevo horario.\n");
            printf("Inserte la fecha (dd-mm-aaaa): ");
            scanf("%s", &fecha);
            printf("Inserte la hora: ");
            scanf("%s", &hora);
        }
        //verifica que le doctor no tenga una cita previa en el horario que ingresa
        if(horarioRepetidoDoctor(fecha, cabezaDoctor->id_medico, hora)== true){
            printf("El doctor tiene una cita previamente registrada a esa hora en esa fecha...\n"
                    "Ingrese un nuevo horario.\n");
            printf("Inserte la fecha (dd-mm-aaaa): ");
            scanf("%s", &fecha);
            printf("Inserte la hora: ");
            scanf("%s", &hora);
        }
        //valida que la hora que se ingresa corresponda al horario del doctor
        if(validarTurno(cabezaDoctor->turno, hora)==false){
            printf("El horario del doctor no es compatible con la hora\nIngrese otro horario: ");
            scanf("%s", &hora);
        }
        
        //crea la estructura cita para almacenar la informacion en el sistema de citas
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
        //mensaje de salida
        printf("Cita registrada\n");
    }
}

/*
 * Funcion que guarda los elementos de la lista citas en el archivo citas.txt
 * Entradas: la cabeza de la lista cita
 * Salidas: no tiene salidas
 */
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

/*
 * Funcion que recorre la linea de texto y separa las palabras cuando encuentra un espacio
 * Entradas: la linea del txt
 * Salida: estructura cita con los datos extraidos del txt
 */
Cita* leerStringCita(char linea[]){
    //atributos
    Cita* nuevaCita = (Cita*)malloc(sizeof(Cita));
    char * pch;
    pch = strtok(linea," ,.");
    int contador = 0;
    
    //recorre la linea de texto
    while (pch != NULL)
    {
        if(strcmp(pch, " ")!= 0){
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
        }
        contador = contador+1;
        pch = strtok(NULL, " ,.");
    }
    return nuevaCita;
}

/*
 * Funcion que agrega la especialidad a la lista a la hora de cargar los datos de cita
 * Entradas: id del medico de la cita
 * Salidas: no tiene salidas  
 */
void agregarEspecialidadCita(char idMedico[]){
    Doctor* temp = cabezaDoctor;
    while(temp != NULL){
        if(strcmp(temp->id_medico, idMedico)==0){ //encuentra el doctor en la lista
            agregarEspecialidad(temp->especialidad); //agrega la especialidad
        }
        temp= temp->sig;
    }
}

/*
 * Función que carga los datos de citas.txt a memoria.
 * Entradas: no tiene entradas.
 * Salidas: no tiene salidas.
 */
void cargarDatosCitas(){
    //atributos
    FILE* miarchivo;
    char linea[256];
    char* resultado;
    miarchivo = fopen("citas.txt", "rt");
    //verifica que el archivo exista
    if (miarchivo == NULL) {
            printf("Archivo citas.txt vacio\n");
    }else{
        //verifica que no haya llegado al final del archivo
        while (feof(miarchivo) == 0){
            resultado = fgets(linea, 256, miarchivo);
            Cita* nuevaCita = (Cita*)malloc(sizeof(Cita));
            if((resultado != NULL)){
                
                nuevaCita = leerStringCita(resultado);
                agregarEspecialidadCita(nuevaCita->id_medico);
               
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

/*
 * Funcion que devuelve el largo de la lista citas
 * Entradas: la cabeza de la lista cita
 * Salidas: Imprime en consola los atributos de la lista
 */
void imprimirListaCita(Cita* ptr){
    //recorre la lista hasta que se acaben las estructuras
    while (ptr != NULL){
        printf("Información sobre la cita: id medico: %s, id paciente: %s, fecha: %s, hora: %s\n", ptr->id_medico, ptr->id_paciente, 
                ptr->fechaCita, ptr->horaCita);
        ptr = ptr ->sig;
    }
}

/*
 * Funcion que devuelve el largo de la lista cita
 * Entradas: la cabeza de la lista cita
 * Salidas: un entero con el largo de la lista cita
 */
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

/*
 * Funcion que genera el promedio de pacientes con respecto a citas
 * Entradas: no tiene entradas
 * Slidas: no tiene salidas
 */
void promedioPacientes(){
    int pacientes = largoPacientes(cabezaPaciente);
    int citas = largoCitas(cabezaCita);
    float promedio = pacientes/citas;
    printf("Promedio de citas por paciente es %f \n", promedio);
}

/*
 * Funcion que muestra el médico con más citas y el promedio de citas entre doctores
 * Entradas: no tiene entradas
 * Salidas: no tiene salidas
 */
void promedioDoctores(){
    int mayor = 0; //limite para buscar el mayor
    Doctor* temp = cabezaDoctor; //recorre la lista de doctores
    //atributos
    char nombre[30];
    char apellido[30];
    char especialidad[30];
    int promedio = 0;
    
    while(temp != NULL){
        int num = (int)(temp->cantCitas[0]-48); //convierte el char a un int

        if(num > mayor){ //si el numero de citas que se encuentra es mayor, se actualizan los datos
            strlcpy(nombre, temp->nombre, sizeof(nombre));
            strlcpy(apellido, temp->primer_apellido,sizeof(apellido));
            strlcpy(especialidad, temp->especialidad, sizeof(especialidad));
            mayor = num;
        }
        temp = temp->sig;
    }
    //calcula promedio
    int citas = largoCitas(cabezaCita);
    int doc = largoDoctores(cabezaDoctor);
    promedio = citas/doc;
    
    //Valida si existen doctores con citas
    if(mayor>0){
        printf("Médico  con  más  citas  es %s  %s, especialista en %s. Tiene %d cita(as).\n", nombre, apellido, especialidad, mayor);
        printf("Promedio general es : %d citas por médico\n", promedio);
    }else{
        printf("Los medicos no tienen citas\n");
    }
}

/*
 * Funcion que muestra el promedio de especialidades
 * Entradas: no tiene entradas
 * Salidas: no tiene salidas
 */
void promedioEspecialidad(){
    /*Se crean la variables para almacenar los datos de la especialidad con más citas*/
    int cantCitas = 0;
    char nombreEspecialidad[30];
    /*Se crean las variables para almacenar los datos del promedio de citas de esa especialidad*/
    int totalMedicos = 0;
    int promedio = 0;
    /*Se crea el puntero*/
    Especialidad* ptr = cabezaEspecialidad;
    /*Se crea el ciclo para recorrer la lista*/
    while (ptr!= NULL){
        /*Compara si la cantidad de citas en especialidad es mayor a la variable*/
        if(ptr->cant > cantCitas){
            /*Si es mayor a la variable ingresa el nombre, la cantidad de citas y la cantidad de Medicos*/
            cantCitas = ptr->cant;
            strcpy(nombreEspecialidad, ptr->nombre);
            totalMedicos = ptr->cantMedicos;
        }
        /*Pasa al siguiente elemento de la lista*/
        ptr = ptr->sig;
    }
    /*Cuando ya se recorrió toda la lista se procede a hacer el promedio*/
    promedio = cantCitas/totalMedicos;
    /*SE IMPRIME EN CONSOLA EL RESULTADO*/
    printf("Especialidad con más citas es:  %s  \n" , nombreEspecialidad);
    printf("Promedio de citas de la especialidad es: %d \n", promedio);
}

/*
 * Función que imprime el menu de estadisticas
 * Entradas: no tiene entradas
 * Salidas: no tiene salidas
 */
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
  
    //verifica la estadistica que solicita segun los datos de consola
    switch(opcion){
        case 1:
            promedioDoctores();
            break;
        case 2:
            promedioEspecialidad();
            break;
        case 3:
            promedioPacientes();
            break;
    }
}
/******************************************************************************/
/*FUNCION PARA EL MAIN*/

/*
 * Función que imprime el menú principal de la aplicación
 * Entradas: no tiene entradas
 * Salidas: no tiene salidas
 */
void imprimirMenu(){
    bool bandera = true;
    int opcionSeleccionada;
    
    while(bandera == true){ //no se sale del ciclo hasta que el usuario lo desee
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
                //termina el ciclo
                bandera = false;
                break;
        }
    }
}

//funcion main para ejecutar el codigo
int main(int argc, char** argv) {
    imprimirMenu();
    return (EXIT_SUCCESS);
}

