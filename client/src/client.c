#include "client.h"

int main(void)
{
  /// repaso PUNTEROS
	int un_nro = 2;// Variable entera
	//int *int_ptr;  Puntero a entero
	//int_ptr =  &un_nro;
	int *int_ptr = &un_nro;  //Asignando la posicion de mem de la variable


printf("REPASO PUNTEROS: \n");
printf("int_ptr=%p\n",int_ptr); // Por pantalla se visualizará la posición de memoria de
							    //la variable un_nro, dado que eso apunta nuestro puntero.

		// COMO ES NUM %d
printf("*int_ptr=%d\n",*int_ptr); // Por pantalla se visualizará "lo que tiene dentro"
								//nuestro puntero, es decir, el valor 2
   // COMO ES PUNTERO %p
printf("&int_ptr=%p\n",&int_ptr); // Por pantalla se visualizará la dirección de memoria de
								//nuestro puntero

//RECORDAR PONER %d para que muestre valor de la variable
printf("Valor de la variable a la que apunta el puntero: %d\n",*int_ptr);
(*int_ptr)++; // n = 3
printf("Voy a incrementar la variable desde el puntero:(*p)++, por lo que ahora, la variable vale:   %d\n",*int_ptr);

//free(int_ptr);

//// REPASO ESTRUCTURAS

//estructuras estaticas
typedef struct {
    uint32_t dni;
    uint32_t pasaporte;
    uint8_t edad;
    char nombre[14];
} t_persona;

//t_persona *p1 = (t_persona*) malloc(sizeof(t_persona));

t_persona p1;
p1.dni=35478921;
p1.pasaporte=3547892;
p1.edad=25;
strcpy(p1.nombre,"John Doe");

printf("ESTRUCTURA ESTATICA PERSONA : \n");
printf("PERSONA:   \n");
printf("DNI: %d\n", p1.dni);
printf("PASAPORTE: %d\n", p1.pasaporte);
printf("EDAD: %d\n", p1.edad);
printf("NOMBRE: %s\n", p1.nombre);

//free(p1);

//ESTRUCTURAS DINAMICAS

typedef struct t_Package {
    char* username;
    uint32_t username_long;
    char* message;
    uint32_t message_long;
} t_package;

t_package pa1;
pa1.username = malloc(8+1);
pa1.message = malloc(19+1);

strcpy(pa1.username, "Maria");
pa1.username_long = strlen(pa1.username)+1;

strcpy(pa1.message, "Hola, soy Maria.");
pa1.message_long = strlen(pa1.message)+1;



printf("ESTRUCTURA DINAMICA PERSONA PAQUETE: \n");
printf("PERSONA: %s\n", pa1.username);
printf("MENSAJE: %s\n", pa1.message);
printf("message_long: %d\n", pa1.message_long);
printf("username_long: %d\n", pa1.username_long);


free(pa1.username);
free(pa1.message);


/*  COMENTO INICIO
// DECLARO OTRO PAQUETE

                         //void *malloc(size_t size);

t_package *ptr_paquete = (t_package*) malloc(sizeof(t_package));  //HACER FREEE X PUNTERO
// Se reserva memoria para poder apuntar a una estructura



(*ptr_paquete).username = "pepito";
ptr_paquete->message = "hola pepito";

printf("username: %s\n", ptr_paquete->username);
printf("message: %s\n", (*ptr_paquete).message);  //se puede escribir tamb asi


//void free(void *ptr);

// Si se tuviese la estructura dinámica ejemplificada anteriormente,
//se deberá hacer lo mismo con los punteros "internos"
free(ptr_paquete->username);
free(ptr_paquete->message);
free(ptr_paquete);

COMENTO FIN */

////////////////////////////////////practica

//estructura dinamica y estatica
/*typedef struct {
    uint32_t dni;
    uint8_t edad;
    uint32_t pasaporte;
    uint32_t nombre_length;
    char* nombre;
} t_personaCompleta; */


/*
Lo que haremos es usar un buffer temporal donde armar nuestro paquete.
En este caso tendremos:

4 bytes del dni;
1 byte de la edad;
4 bytes del pasaporte;
N bytes del nombre;
4 bytes de la longitud (N) del nombre.
*/

/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

//int conexion;

/* ---------------- LOGGING ---------------- */

logger = iniciar_logger(); //CUANDO QUIERO QUE SEA GLOBAL EL LOGGER NO PONGO  t_log*
//ya que lo declare extern en el .h

if(logger== NULL ) {
		perror("No se pudo crear el LOGGER\n");
	}else {
		log_info(logger, "Bienvenidos al archivo Logger del TPO\n" );
		log_info(logger, "Hola! Soy un logger!" );
	}

// Usando el logger creado previamente
// Escribi: "Hola! Soy un log"


/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

t_config* config = iniciar_config();
if(config == NULL){
	log_error(logger,"No se pudo encontrar la ruta del archivo CONFIG");
	exit(1);
}
else {
	log_info(logger, "Se inicio correctamente el archivo CONFIG del TP0");
}

// Usando el config creado previamente, leemos los valores del config y los
// dejamos en las variables 'ip', 'puerto' y 'valor'
char* ip = config_get_string_value(config, "IP");
char* puerto = config_get_string_value(config, "PUERTO");
char* valor = config_get_string_value(config, "CLAVE");
// Loggeamos el valor de config

log_info(logger, "El valor es: %s", valor);
log_info(logger, "El puerto es: %s ", puerto);
log_info(logger, "La IP es: %s", ip);

/* ---------------- LEER DE CONSOLA ---------------- */

leer_consola(logger);


/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

// Creamos una conexión hacia el servidor
int conexion = crear_conexion(ip, puerto);

// Enviamos al servidor el valor de CLAVE como mensaje
enviar_mensaje(valor,conexion);


	// Armamos y enviamos el paquete
printf("Arranca paquete a enviar a Servidor\n");
paquete(conexion);

//prueba_envio_handshake(conexion); // conexion es socket_cliente

terminar_programa(conexion,logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente


}

/*
Loguee en el archivo "tp0.log"
Muestre los logs por pantalla (y no solo los escriba en el archivo)
Muestre solo los logs a partir del nivel "info". */

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "LOGGER_TPO", 1, LOG_LEVEL_INFO);


	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config= config_create("cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	// La primera te la dejo de yapa
	char* leido = readline("> ");
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while (strcmp(leido,"")){
	//while (strcmp(leido,"") != 0){
		//log_info(logger, leido);
//		log_info(logger, (char*)leido);
		free(leido);
		leido = readline(">");
	}
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion){
	// Ahora toca lo divertido!
	char* leido =readline("> ");
	t_paquete* paquete = crear_paquete();
//	agregar_a_paquete(paquete, leido , strlen(leido)+1);

		// El resto, las vamos leyendo y agregando al paq hasta recibir un string vacío
		while (strcmp(leido,"")){
			agregar_a_paquete(paquete, leido , strlen(leido)+1);
			//log_info(logger, leido);
			free(leido);
//			agregar_a_paquete(paquete, leido , strlen(leido)+1);

			leido = readline("> ");

		}
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
		free(leido);
		enviar_paquete(paquete, conexion);
		eliminar_paquete(paquete);

//		enviar_paquete(paquete, conexion);
//		free(leido);
//		eliminar_paquete(paquete);

}






void terminar_programa( int conexion, t_log* logger, t_config* config){
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	log_destroy(logger);
	config_destroy(config);
    liberar_conexion(conexion);
}


