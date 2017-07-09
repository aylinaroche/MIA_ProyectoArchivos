/*
 * acciones.c
 *
 *  Created on: 6/06/2017
 *      Author: Aylin
 */

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "acciones.h"
#include "estructuras.h"
#include <setjmp.h>
#include <math.h>

char* order = NULL;
char* ruta = NULL;
char* size = NULL;
char* unit = NULL;
char* path = NULL;
char* type = NULL;
char* fit = NULL;
char* dele = NULL;
char* name = NULL;
char* add = NULL;
char* id = NULL;
int boolCrearDisco = 1;
int varLetra = 0;
int boolK = 0;
int boolM = 0;
int boolH = 0;
int boolI = 0;
char* nDirectorio = NULL;
char* fs = NULL;
char* p = NULL;
char* cont = NULL;
char* ugo = NULL;
char* R = NULL;
int boolR = 0;
char* filen = NULL;
int rf = 0;
char* dest = NULL;
char* iddest = NULL;
char* file1 = NULL;
char* file2 = NULL;
char* file3 = NULL;
char* allocation;
int contadorM = 0;
int boolExec = 0;
int bool = 0;
int correcto = 1;
int boolEditar = 0;
int contadorArchivo = 0;
char* contenidoUsers = NULL;
char* arch = "*";
int boolLs = 0;

void limpiarVariables() {
	ruta = NULL;
	size = NULL;
	unit = NULL;
	path = NULL;
	type = NULL;
	fit = NULL;
	dele = NULL;
	name = NULL;
	add = NULL;
	id = NULL;
	boolK = 0;
	boolM = 0;
	boolH = 0;
	boolI = 0;
	nDirectorio = NULL;
	p = NULL;
	cont = NULL;
	ugo = NULL;
	boolR = 0;
	rf = 0;
	dest = NULL;
	iddest = NULL;
	file1 = NULL;
	file2 = NULL;
	file3 = NULL;
	allocation = NULL;
	contadorM = 0;
//	boolEditar=0;
}

void atributoDisco(char* coman) {
//printf("atributo disco %s\n",coman);
	char* token1 = tolower(coman);
	char* com = coman;
	//printf("T1 = %s\n",token1);
	token1 = strtok(com, "=");
	//printf("T1 = %s\n",token1);
	if (token1 != NULL) {
		if (strcasecmp(token1, "$tamanio") == 0
				|| strcasecmp(token1, "@tamanio") == 0) { //Verifica cada atributo
			token1 = strtok(NULL, ">");
			size = token1;
		} else if (strcasecmp(token1, "$size") == 0
				|| strcasecmp(token1, "@size") == 0) { //Verifica cada atributo
			token1 = strtok(NULL, ">");
			size = token1;
		} else if (strcasecmp(token1, "@unit") == 0) {
			token1 = strtok(NULL, ">");
			unit = token1;
		} else if (strcasecmp(token1, "$path") == 0
				|| strcasecmp(token1, "@path") == 0
				|| strcasecmp(token1, "&path") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			path = token1;
		} else if (strcasecmp(token1, "@tipo") == 0) {
			token1 = strtok(NULL, ">");
			type = token1;
		} else if (strcasecmp(token1, "@type") == 0
				|| strcasecmp(token1, "&type") == 0) {
			token1 = strtok(NULL, ">");
			type = token1;
		} else if (strcasecmp(token1, "@fit") == 0) {
			token1 = strtok(NULL, ">");
			fit = token1;
		} else if (strcasecmp(token1, "@delete") == 0) {
			token1 = strtok(NULL, ">");
			dele = token1;
		} else if (strcasecmp(token1, "@name") == 0
				|| strcasecmp(token1, "$name") == 0) {
			token1 = strtok(NULL, ">");
			//printf("tok1 = %s\n",token1);
			char nombre[200];
			strcpy(nombre, token1);
			if (nombre[0] == '"') {
				int i = 0;
				while (nombre[i + 1] != '"') { //Le quita las comillas
					nombre[i] = nombre[i + 1];
					if (nombre[i] == ' ') {
						nombre[i] = '_';
					}
					i++;
				}
				nombre[i] = '\0';
				nombre[i + 1] = '\0';
			}
			//printf("tok1 = %s\n",token1);
			strcpy(token1, nombre);
			name = token1;

		} else if (strcasecmp(token1, "@add") == 0) {
			token1 = strtok(NULL, ">");
			add = token1;
		} else if (strcasecmp(token1, "$id") == 0
				|| strcasecmp(token1, "@id") == 0
				|| strcasecmp(token1, "&id") == 0) {
			token1 = strtok(NULL, ">");
			id = token1;
		} else if (strcasecmp(token1, "$id1") == 0
				|| strcasecmp(token1, "$id2") == 0
				|| strcasecmp(token1, "$id3") == 0
				|| strcasecmp(token1, "$id4") == 0
				|| strcasecmp(token1, "$id5") == 0
				|| strcasecmp(token1, "$id6") == 0
				|| strcasecmp(token1, "$id7") == 0
				|| strcasecmp(token1, "$id8") == 0) {

			token1 = strtok(NULL, ">");
			id = token1;

		} else if (boolExec == 1) { //********* MMM
			token1 = strtok(NULL, ">");
			printf("token1=%s\n", token1);
			char direccion[200];
			strcpy(direccion, token1);

			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			path = token1;

		} else if (strcasecmp(token1, "@k") == 0) {
			boolK = 1;
		} else if (strcasecmp(token1, "@m") == 0) {
			boolM = 1;
		} else if (strcasecmp(token1, "@h") == 0
				|| strcasecmp(token1, "$h") == 0) {
			boolH = 1;
		} else if (strcasecmp(token1, "@i") == 0) {
			boolI = 1;
		} else if (strcasecmp(token1, "@n") == 0) {
			token1 = strtok(NULL, ">");
			nDirectorio = token1;
		} else if (strcasecmp(token1, "@fs") == 0) {
			token1 = strtok(NULL, ">");
			fs = token1;
		} else if (strcasecmp(token1, "@r") == 0) {
			boolR = 1;
		} else if (strcasecmp(token1, "@p") == 0
				|| strcasecmp(token1, "$p") == 0) {
			p = "p";
		} else if (strcasecmp(token1, "@cont") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			cont = token1;
		} else if (strcasecmp(token1, "@rf") == 0) {
			rf = 1;
		} else if (strcasecmp(token1, "$dest") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			dest = token1;
		} else if (strcasecmp(token1, "$iddest") == 0) {
			token1 = strtok(NULL, ">");
			iddest = token1;
		} else if (strcasecmp(token1, "$ruta") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			ruta = token1;
		} else if (strcasecmp(token1, "$file1") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			file1 = token1;

		} else if (strcasecmp(token1, "$file2") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			file2 = token1;

		} else if (strcasecmp(token1, "$file3") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			file3 = token1;

		} else if (strcasecmp(token1, "$FILEID") == 0
				|| strcasecmp(token1, "fileid") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			file1 = token1;

		} else if (strcasecmp(token1, "@allocation") == 0) {
			token1 = strtok(NULL, ">");
			allocation = token1;
		} else if (strcasecmp(token1, "$order") == 0) {
			token1 = strtok(NULL, ">");
			order = token1;
		} else if (strcasecmp(token1, "+") == 0) {

		} else {
			printf("ERROR: El atributo \"%s\" es incorrecto.\n", token1);
		}

	}
}

void script() {
	if (path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = ejecutarScript(path);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int ejecutarScript(char *path) {
//printf("P=%s\n",path);
	FILE* archivo;
	char caracter[1000];
	archivo = fopen(path, "r+");
	if (archivo == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	} else {
		int j = 0;
		for (j = 0; j < 1000; j++) {
			caracter[j] = '\0';
		}
		int i = 0;
		while (feof(archivo) == 0) { // *feof* hasta que se acabe el archivo
			caracter[i] = fgetc(archivo); // *fgetc* lee lineapor linea
			printf(&caracter[i]);
			//caracter[i]= tolower(caracter[i]);
			if (caracter[i] == '\n') {
				//printf("\n");
				char com[1000];
				char com2[1000];
				caracter[i] = '\0';
				strcpy(com, caracter);
				strcpy(com2, com);
				char *comando = NULL;
				comando = strtok(com, " ");
				char *atr;
				if (comando != NULL) {
					atr = com2;
					//	printf("ATR=%s\n",comando);
					verificarComando(comando, atr);
				}
				for (j = 0; j < 1000; j++) {
					caracter[j] = '\0';
				}
				printf("\n");
				i = 0;
			} else if (caracter[i] == '\\') {
				caracter[i] = ' ';
			} else {
				i++;
			}
		}
	}
	return 0;
}

void crearDisco(int num) {
	boolCrearDisco = 1;
	if (size == NULL || path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (size > 0) {
			char pathNuevo[50];
			strcpy(pathNuevo, path);
			int d = crearArchivoBinario(size, path, name);
			if (d == 0) {
				printf(
						"-> Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				return;
			}
			if (num == 1) {
				//Recover
				FILE *archivo;
				char *recovery =
						concatenar(
								"/home/aylin/workspaceNeon/ProyectoArchivos/recovery/recovery",
								name);
				archivo = fopen(recovery, "w+");
				fclose(archivo);
				copiarFichero(path, recovery);

				//Copy
				char *nombre = concatenar(pathNuevo, name);
				name = concatenar("Copy", name);
				path = concatenar(pathNuevo, name);
				copiarFichero(nombre, path);
				printf("/");
				strcpy(path, pathNuevo);
			}
			printf("/\n");
		} else {
			printf("ERROR: El tamanio es incorrecto.\n");
		}
	}
}

int crearArchivoBinario(char* size, char* path, char* name) {

	int tam = atoi(size);

//COMPROBAR POSIBLES ERRORES
	if (tam < 8) {
		printf("ERROR: El tamanio minimo para un disco es de 8Mb.\n");
		boolCrearDisco = 0;
		return 0;
	} else {
		int b = multiploDeOcho(tam);
		if (b == 0) {
			printf("ERROR: El tamanio no es multiplo de 8.\n");
			boolCrearDisco = 0;
			return 0;
		}
	}

	char* ext = NULL;
	ext = name;
	int boolExt = 0;

	ext = strtok(name, ".");
	while (ext != NULL) {
		ext = strtok(NULL, ".");
		if (ext != NULL) {
			if (strcasecmp(ext, "dsk") == 0) {
				boolExt = 1;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: El nombre no tiene extension.\n");
		boolCrearDisco = 0;
		return 0;
	}
/////////////////////////////////////////////////////////////////

	if (boolCrearDisco == 1) {
		//char* nameCopy = (char*) malloc(sizeof(char*));
		//char* pathCopy = (char*) malloc(sizeof(char*));
		//strcat(pathCopy,path);

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		strcat(name, ".dsk");
		strcat(path, name);
		// printf("PATH = %s\n",path);
		strcpy(direcc, path);

		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//	printf("Ruta de Archivo: %s\n", aux);
				system(aux);
				free(aux);
			} else {
				direcc2[i] = direcc[i];
				if (direcc[i] == '\0') {
					break;
				}
			}
		}
		for (i = 0; i < 200; i++) {
			if (direcc2[i] == '\n') {
				direcc2[i] = '\0';
			}
		}

		mbr structDisco;
		structDisco.fecha = time(0);
		int as = 2; //aleatorio();// **
		structDisco.signature = as;
		i = 0;
		for (i = 0; i < 4; i++) {
			structDisco.part[i].size = 0;
			structDisco.part[i].auxiliar = 0;
			structDisco.part[i].start = 0;
			structDisco.part[i].fit = '0';
			structDisco.part[i].status = '0';
			structDisco.part[i].type = '0';
			int j = 0;
			for (j = 0; j < 20; j++) {
				structDisco.part[i].exten[j].status = '0';
				structDisco.part[i].exten[j].fit = '0';
				structDisco.part[i].exten[j].next = 0;
				structDisco.part[i].exten[j].size = 0;
				structDisco.part[i].exten[j].auxiliar = 0;
				structDisco.part[i].exten[j].start = 0;
			}
		}
		char buffer[1024];
		i = 0;
		for (i = 0; i < 1024; i++) {
			buffer[i] = '0';
		}

		FILE *disco;
		disco = fopen(path, "wb+");
		if (disco) {
		} else {
			printf("ERROR: Al crear archivo. %s\n", path);
			return 0;
		}

		//MegaBytes
		structDisco.size = tam * 1024 * 1024;
		tam = tam * 1024;
		i = 0;

		for (i = 0; i < tam; i++) {
			fwrite(&buffer, 1024, 1, disco);
		}
		//printf("SIZE = %d\n",sizeof(mbr));

		fseek(disco, 0, SEEK_SET);
		fwrite(&structDisco, sizeof(mbr), 1, disco);
		fclose(disco);
		printf("-> Se creo el disco correctamente.\n");
		//FILE *archivoCopia;
		//archivoCopia = fopen(nuevo, "wb+");
		//	copy_file(path, nuevo);
		//fclose(archivoCopia);
		return 1;
	}
	return 1;
}

char *concatenar(char* var1, char* var2) {
	char *cadena = (char *) malloc(1 + strlen(var1) + strlen(var2));
	strcpy(cadena, var1);
	strcat(cadena, var2);
	return cadena;
}

char *generarPath(char *direccion) {
	char aux[200];
	strcpy(aux, direccion);

	char* datos[10];
	int cont = 0;

	char* inst = NULL;
	inst = strtok(direccion, "/");
	datos[cont] = inst;

	while (inst != NULL) {
		cont++;
		inst = strtok(NULL, "/");
		datos[cont] = inst;
	}
	char *d = "/";
	char *rutaNueva = (char *) malloc(1 + strlen(aux) + strlen("copy"));
	rutaNueva = "/";

	int i = 0;
	for (i = 0; i < cont - 1; i++) {
		char *c1 = concatenar(datos[i], d);
		rutaNueva = concatenar(rutaNueva, c1);
	}
	rutaNueva = concatenar(rutaNueva, "Copy");
	rutaNueva = concatenar(rutaNueva, datos[cont - 1]);
	//rutaNueva=concatenar("/",rutaNueva);

	//printf("RUTA = %s\n", rutaNueva);
	strcpy(direccion, aux);
	return rutaNueva;

}

char *obtenerNombre(char *ruta) {
	char* datos[10];
	int cont = 0;

	char* inst = NULL;
	inst = strtok(ruta, "/");
	datos[cont] = inst;

	while (inst != NULL) {
		cont++;
		inst = strtok(NULL, "/");
		datos[cont] = inst;
	}
	return datos[cont - 1];
}

char *obtenerRuta(char *id) {
	char* ruta;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					//printf("R = %s\n", ruta);
					return ruta;
				}
			}
		}
	}
	return NULL;
}

int multiploDeOcho(int tam) {
	int i = 0;
	for (i = 8; i < 300; i = i + 8) {
		if (i == tam) {
			return 1;
		}
	}
	return 0;
}

int eliminarDisco() {
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	} else {
		char com[5];
		printf("-> ¿Desea continuar? [s/n]: \n");
		fgets(com, 5, stdin);
		if (com[0] == 's' || com[0] == 'S') {
			char* aux;
			aux = (char*) malloc(160);
			strcpy(aux, "rm ");
			strcat(aux, path);
			system(aux);
			printf("-> Disco eliminado con exito.\n");
		} else {
			printf("-> No se elimino el disco.\n");
		}
	}
	return 1;
}

void adminParticion() {
	//Atributos opcionales
	if (unit == NULL) {
		unit = "k"; //kilobytes
	}
	if (type == NULL) {
		type = "p"; //primaria
	}
	if (fit == NULL) {
		fit = "wf"; //peor ajuste
	}
	if (allocation == NULL) {
		allocation = "ix"; //indexada
	}

	//Atributos obligatorios
	if (add == NULL && dele == NULL) {
		if (path == NULL || size == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = crearParticion(path, name, size, unit, type, fit);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	} else if (dele == NULL) {
		if (path == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = agregarParticion(add, unit, path, name);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	} else if (add == NULL) {
		if (path == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = eliminarParticion(dele, path, name);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	} else {
		if (path == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = agregarParticion(add, unit, path, name);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	}
	//Recover
	char pathAux[100];
	strcpy(pathAux, path);
	char *nombre = obtenerNombre(path);
	char *recovery = concatenar(
			"/home/aylin/workspaceNeon/ProyectoArchivos/recovery/recovery",
			nombre);
	copiarFichero(pathAux, recovery);
	//Copy
	char pathAux2[100];
	strcpy(pathAux2, pathAux);
	char *ruta = generarPath(pathAux);
	copiarFichero(pathAux2, ruta);
}

int crearParticion(char* path, char* name, char* size, char* unit, char* type,
		char* fit) {
	int tam = atoi(size);
	int libre = 0;

	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		path = generarPath(path);
		archivo = fopen(path, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);
	int tipo = 0;
	char ajuste[5];

//VERIFICAR EL TIPO
	if (strcasecmp(type, "P\n") == 0 || strcasecmp(type, "p") == 0
			|| strcasecmp(type, "p\r") == 0) { //primaria
		tipo = 1;
	} else if (strcasecmp(type, "L\n") == 0 || strcasecmp(type, "l") == 0
			|| strcasecmp(type, "l\r") == 0) { //logica
		tipo = 2;
		//printf("tipo 2\n");
	} else if (strcasecmp(type, "E\n") == 0 || strcasecmp(type, "e") == 0
			|| strcasecmp(type, "e\r") == 0) { //extendida
		tipo = 3;
	} else {
		printf("ERROR: Tipo de particion incorrecta.%s**\n", type);

		return 0;
	}

	//VERIFICAR LA UNIDAD

	int bytes = 0;
	if (strcasecmp(unit, "b") == 0 || strcasecmp(unit, "b\n") == 0
			|| strcasecmp(unit, "b\r") == 0) { //Kilobyte -> 1024 bytes
		bytes = tam;
		/*if (tam < 2097152) { //2 *1024 *1024
		 printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
		 return 0;
		 } else {
		 bytes = tam;
		 }*/

	} else if (strcasecmp(unit, "k") == 0 || strcasecmp(unit, "k\n") == 0
			|| strcasecmp(unit, "k\r") == 0) { //byte -> 8bits
		bytes = tam * 1024;
		/*if (tam < 2048) { //2 * 1024
		 printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
		 return 0;
		 } else {
		 bytes = tam * 1024;
		 }*/
	} else if (strcasecmp(unit, "m") == 0 || strcasecmp(unit, "m\n") == 0
			|| strcasecmp(unit, "m\r") == 0) { //megabyte -> 1024 Kb
		bytes = tam * 1024 * 1024;
		/*if (tam < 2) {
		 printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
		 return 0;
		 } else {
		 bytes = tam * 1024 * 1024;
		 }*/
	} else {
		printf("ERROR: La unidad no existe.%s**\n", unit);
		return 0;
	}

//VERIFICAR AJUSTE
	if (strcasecmp(fit, "BF\n") == 0 || strcasecmp(fit, "bf") == 0
			|| strcasecmp(fit, "bF") == 0 || strcasecmp(fit, "bf\r") == 0) {
		strcpy(ajuste, "B");
	} else if (strcasecmp(fit, "FF\n") == 0 || strcasecmp(fit, "ff") == 0
			|| strcasecmp(fit, "fF") == 0 || strcasecmp(fit, "Ff\r") == 0) {
		strcpy(ajuste, "F");
	} else if (strcasecmp(fit, "WF\n") == 0 || strcasecmp(fit, "wf") == 0
			|| strcasecmp(fit, "wF") == 0 || strcasecmp(fit, "Wf\r") == 0) {
		strcpy(ajuste, "W");
	} else {
		printf("ERROR: No existe el ajuste indicado.%s**\n", fit);
		return 0;
	}
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(name, structDisco.part[i].name) == 0) {
			printf("ERROR: Ya existe el nombre.\n");
			return 0;
		}
	}
//Limpiar
	/*for (i = 0; i < 4; i++) {
	 if (structDisco.part[i].type != 'e' && structDisco.part[i].type != 'p'
	 && structDisco.part[i].type != 'l') {
	 printf("Es diferente = %c\n", structDisco.part[i].type);
	 structDisco.part[i].status = '0';
	 structDisco.part[i].type = 'l';
	 }
	 }*/
//VERIFICAR NOMBRE REPETIDO
	if (tipo == 1) { //primaria
		for (i = 0; i < 4; i++) {
			///  printf("Primaria= %s\n",structDisco.part[i].name);
			if (strcasecmp(name, structDisco.part[i].name) == 0) {
				printf("ERROR: Ya existe el nombre.\n");
				return 0;
			}
		}
	} else if (tipo == 3) { //extendida
		for (i = 0; i < 4; i++) {
			//  printf("Extendida= %s\n",structDisco.part[i].name);
			if (structDisco.part[i].type == 'E'
					|| structDisco.part[i].type == 'e'
					|| strcasecmp(name, structDisco.part[i].name) == 0) {
				printf("ERROR: Ya existe una particion extendida.\n");
				return 0;
			}
		}
	} else {
		for (i = 0; i < 4; i++) {
			if (structDisco.part[i].type == 'E'
					|| structDisco.part[i].type == 'e') {
				int j = 0;
				for (j = 0; j < 20; j++) {
					if (strcasecmp(name, structDisco.part[i].exten[j].name)
							== 0) {
						printf("ERROR: Ya existe el nombre.\n");
						return 0;
					}
				}
				break;
			}
		}
		if (i == 4) {
			printf("ERROR: No existe una particion extendida.\n");
			return 0;
		}
	}
	//VERIFICAR EL TAMANIO DE LA PARTICION Y LA CANTIDAD DE PARTICIONES
	int particion = 0;
	int contParticion = 0;
	for (i = 0; i < 4; i++) {
		if (structDisco.part[i].status == '1') {
			//		printf("No = %d , Tipo = %c\n", contParticion + 1,structDisco.part[i].type);
			particion = particion + structDisco.part[i].size;
			contParticion++;
		}
	}
	if (contParticion == 4 && tipo != 2) {
		printf("ERROR: Ya existen 4 particiones. %d\n", tipo);
		return 0;
	}

//VERIFICAR TAMANIO DE PARTICION
	libre = structDisco.size - particion;
	int esp = 0; //espacio

	if (tipo == 1 || tipo == 3) { // Si la particion es primaria o extendida
		if (libre < bytes) {
			printf("ERROR: No hay tamaño disponible1.\n");
			return 0;
		}

//ASINGAR TIPO, AJUSTE, TAMANIO
		for (i = 0; i < 4; i++) {
			if (structDisco.part[i].status == '0') {
				if (structDisco.part[i].size == 0
						|| bytes < structDisco.part[i].size) {
					if (ajuste[0] == 'F') {
						structDisco.part[i].fit = 'F';
					} else if (ajuste[0] == 'B') {
						structDisco.part[i].fit = 'B';
					} else {
						structDisco.part[i].fit = 'W';
					}
					strcpy(structDisco.part[i].name, name);
					//printf("Asignacion ==  %s\n",structDisco.part[i].name);
					structDisco.part[i].size = bytes;
					structDisco.part[i].auxiliar = bytes;
					if (i == 0) {
						//printf("Size of=%d\n",sizeof(mbr));
						structDisco.part[i].start = sizeof(mbr) + 1;
						esp = 1;
					} else {
						structDisco.part[i].start =
								structDisco.part[i - 1].start
										+ structDisco.part[i - 1].size;
						esp = 1;
					}
					structDisco.part[i].status = '1';

					if (strcasecmp(type, "E") == 0
							|| strcasecmp(type, "e") == 0) {
						structDisco.part[i].type = 'e';
					} else {
						structDisco.part[i].type = 'p';
					}
					esp = 1;
					break;
				}
			}
		}
	} else { //Si la particion es logica
		for (i = 0; i < 4; i++) {
			if (structDisco.part[i].type == 'E'
					|| structDisco.part[i].type == 'e') { //Si existe una extendida antes
				int j = 0;
				for (j = 0; j < 20; j++) {
					int k = 0;
					int espa = 0; //suma de todas las particiones extendidas
					for (k = 0; k < 20; k++) {
						espa = espa + structDisco.part[i].exten[k].size;
					}
					espa = structDisco.part[i].auxiliar - espa;
					if (espa < bytes) {
						printf("ERROR: No hay tamaño disponible2.\n");
						return 0;
					}

					if (structDisco.part[i].exten[j].status == '0') {
						if (structDisco.part[i].exten[j].size == 0
								|| bytes < structDisco.part[i].exten[j].size) {

							if (ajuste[0] == 'F') { //Primer ajuste
								structDisco.part[i].exten[j].fit = 'F';
							} else if (ajuste[0] == 'B') { //Mejor Ajuste
								structDisco.part[i].exten[j].fit = 'B';
							} else {
								structDisco.part[i].exten[j].fit = 'W'; //Peor ajuste
							}
							strcpy(structDisco.part[i].exten[j].name, name);
							structDisco.part[i].exten[j].size = bytes;
							structDisco.part[i].exten[j].auxiliar = bytes;

							if (j == 0) { //
								structDisco.part[i].exten[j].start =
										structDisco.part[i].start + 1;
								structDisco.part[i].exten[j].next = -1;
								esp = 1;
							} else {
								structDisco.part[i].exten[j].start =
										structDisco.part[i].exten[j - 1].start
												+ structDisco.part[i].exten[j
														- 1].size;
								structDisco.part[i].exten[j - 1].next =
										structDisco.part[i].exten[j - 1].start
												+ structDisco.part[i].exten[j
														- 1].size;
								esp = 1;
							}
							//j = 0;
							structDisco.part[i].exten[j].status = '1';
							esp = 1;
							break;
						}
					}
				}
			}
		}
	}
	if (esp == 0) {
		printf("ERROR: Espacio insuficiente.");
		return 0;
	}

	fseek(archivo, 0, SEEK_SET);
	//printf("Size2 = %d\n",sizeof(mbr));
	fwrite(&structDisco, sizeof(mbr), 1, archivo);
	fclose(archivo);
	printf("-> Se creo la particion correctamente.\n");
	return 1;

}

int agregarParticion(char* add, char* unit, char* path, char* name) {

	int tam = atoi(add);

//VERIFICA SI EL DISCO EXISTE
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		path = generarPath(path);
		archivo = fopen(path, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICA LA UNIDAD DEL DISCO
	int bytes = 0;
	if (strcasecmp(unit, "k") == 0 || strcasecmp(unit, "K") == 0) {
		bytes = tam * 1024;
	} else if (strcasecmp(unit, "m") == 0 || strcasecmp(unit, "M") == 0) {
		bytes = tam * 1024 * 1024;
	} else if (strcasecmp(unit, "b") == 0 || strcasecmp(unit, "B") == 0) {
		bytes = tam;
	} else {
		printf("ERROR: Unidad incorrecta.\n");
		return 0;
	}
	int i = 0, j = 0;
	int esLogica = 0;

//VERIFICA SI EL NOMBRE EXISTE
	for (i = 0; i < 4; i++) {
		if (strcasecmp(name, structDisco.part[i].name) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(name, structDisco.part[i].exten[j].name) == 0) {
				esLogica = 1;
				break;
			}
		}
		if (esLogica > 0) {
			break;
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: El nombre indicado no existe.\n");
		return 0;
	}

//VERIFICAR SI EL ESPACIO ES SUFICIENTE
	if (esLogica > 0) { // Si es logica
		if (bytes > 0) {
			//printf("j0 = %d\n", j);
			if (j < 20) { //j depende de donde encontro el nombre
				if (structDisco.part[i].exten[j + 1].start != 0) { //Si no es la primer particion
					int siguiente = structDisco.part[i].exten[j].start
							+ structDisco.part[i].exten[j].auxiliar;
					int anterior = structDisco.part[i].exten[j + 2].start;

					int resta = anterior - siguiente;

					if (resta < bytes) {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
					structDisco.part[i].exten[j].auxiliar =
							structDisco.part[i].exten[j].auxiliar + bytes;

					if (structDisco.part[i].exten[j].auxiliar
							> structDisco.part[i].exten[j].size) {
						structDisco.part[i].exten[j].size =
								structDisco.part[i].exten[j].size
										+ (structDisco.part[i].exten[j].auxiliar
												- structDisco.part[i].exten[j].size);
					}

				} else { //Si es la ultima particion
					printf("Ultima logica\n");
					int k = 0;
					int suma = 0;
					for (k = 0; k < 20; k++) {
						suma = suma + structDisco.part[i].exten[k].size;
					}
					int resta = structDisco.part[i].auxiliar - suma;
					//printf(" suma = %d\n size = %d\n resta = %d\n aux = %d\n bytes =  %d\n",suma,structDisco.part[i].size,resta,structDisco.part[i].auxiliar,bytes);
					//printf(" sizeE = %d\n auxE = %d\n bytes =  %d\n",structDisco.part[i].exten[j].size,structDisco.part[i].exten[j].auxiliar,bytes);
					if (resta < bytes) {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
					structDisco.part[i].exten[j].auxiliar =
							structDisco.part[i].exten[j].auxiliar + bytes;
					if (structDisco.part[i].exten[j].auxiliar
							> structDisco.part[i].exten[j].size) {
						structDisco.part[i].exten[j].size =
								structDisco.part[i].exten[j].size
										+ (structDisco.part[i].exten[j].auxiliar
												- structDisco.part[i].exten[j].size);
						structDisco.part[i].exten[j].auxiliar = resta - bytes;

					}
				}
			} else { //Si es la ultima particion logica
				int j = 0;
				int suma = 0;
				for (j = 0; j < 20; j++) {
					suma = suma + structDisco.part[i].exten[j].size;
				}
				int resta = structDisco.part[i].auxiliar - suma;
				if (resta < bytes) {
					printf("ERROR: No hay espacio disponible.\n");
					return 0;
				}
				structDisco.part[i].exten[j].auxiliar =
						structDisco.part[i].exten[j].auxiliar + bytes;
				if (structDisco.part[i].exten[j].auxiliar
						> structDisco.part[i].exten[j].size) {
					structDisco.part[i].exten[j].size =
							structDisco.part[i].exten[j].size
									+ (structDisco.part[i].exten[j].auxiliar
											- structDisco.part[i].exten[j].size);
				}

			}
		} else { //Si es un add negativo de particion logica
			printf("negativo j=%d\n", j);
			if (j < 20) {
				if (structDisco.part[i].exten[j + 1].start != 0) { //
					int resta = structDisco.part[i].exten[j].auxiliar + bytes;
					//printf("resta = %d\n",resta);
					if (resta > 0) {
						structDisco.part[i].exten[j].auxiliar = resta;
						structDisco.part[i].exten[j].size = resta;
					} else {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
				} else { //Si es la ultima particion
					int resta = bytes + structDisco.part[i].exten[j].auxiliar;
					if (resta > 0) {
						structDisco.part[i].exten[j].auxiliar = resta;
						structDisco.part[i].exten[j].size = resta;
					} else {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
				}
			} else {
				int resta = bytes + structDisco.part[i].exten[j].auxiliar;
				//
				if (resta > 0) {
					structDisco.part[i].exten[j].auxiliar = resta;
					structDisco.part[i].exten[j].size = resta;
				} else {
					printf("ERROR: No hay espacio disponible.\n");
					return 0;
				}
			}
		}
	} else {
		if (bytes > 0) {
			if (i < 3) { //Si no es la ultima particon
				if (structDisco.part[i + 1].start != 0) {
					int siguiente = structDisco.part[i].auxiliar
							+ structDisco.part[i].start;
					int anterior = structDisco.part[i + 2].start;
					int resta = anterior - siguiente;

					printf("sig = %d\n ant = %d\n resta = %d\n bytes = %d\n",
							siguiente, anterior, resta, bytes);
					if (resta < bytes) {
						printf(
								"ERROR: No hay espacio disponible en medio de las particiones [P].\n");
						return 0;
					}
					structDisco.part[i].auxiliar = structDisco.part[i].auxiliar
							+ bytes;
					if (structDisco.part[i].auxiliar
							> structDisco.part[i].size) {
						structDisco.part[i].size = structDisco.part[i].size
								+ (structDisco.part[i].auxiliar
										- structDisco.part[i].size);
					}
				} else {
					int k = 0;
					int suma = 0;
					for (k = 0; k < 4; k++) {
						suma = suma + structDisco.part[k].size;
					}
					int resta = structDisco.size - suma;
					if (resta < bytes) {
						printf("No hay espacio disponible al final.\n");
						return 0;
					}
					structDisco.part[i].auxiliar = structDisco.part[i].auxiliar
							+ bytes;
					if (structDisco.part[i].auxiliar
							> structDisco.part[i].size) {
						structDisco.part[i].size = structDisco.part[i].size
								+ (structDisco.part[i].auxiliar
										- structDisco.part[i].size);
					}
				}
			} else { //Si es la ultima particion
				int k = 0;
				int suma = 0;
				for (k = 0; k < 4; k++) {
					suma = suma + structDisco.part[k].size;
				}
				int resta = structDisco.size - suma;
				if (resta < bytes) {
					printf(
							"ERROR: No hay espacio disponible para agregar al final.\n");
					return 0;
				}
				structDisco.part[i].auxiliar = structDisco.part[i].auxiliar
						+ bytes;
				if (structDisco.part[i].auxiliar > structDisco.part[i].size) {
					structDisco.part[i].size = structDisco.part[i].size
							+ (structDisco.part[i].auxiliar
									- structDisco.part[i].size);
				}
			}
		} else { //Si es add negativo
			if (i < 3) {
				printf("negativo\n");
				if (structDisco.part[i + 1].start != 0) {
					int resta = bytes + structDisco.part[i].auxiliar;
					int k = 0;
					int sumadora = 0;
					for (k = 0; k < 20; k++) {
						if (structDisco.part[i].exten[k].size > 0) {
							sumadora = sumadora
									+ structDisco.part[i].exten[k].size;
						}
					}
					printf("resta = %d\n", resta);
					if (resta > sumadora) {
						structDisco.part[i].auxiliar = resta;
						structDisco.part[i].size = resta;
					} else {
						printf("ERROR: No hay espacio para borrar.\n");
						return 0;
					}
				} else {
					int resta = bytes + structDisco.part[i].auxiliar;
					int k = 0;
					int sumadora = 0;
					for (k = 0; k < 20; k++) {
						sumadora = sumadora + structDisco.part[i].exten[k].size;
					}
					if (resta > sumadora) {
						structDisco.part[i].auxiliar = resta;
						structDisco.part[i].size = resta;
					} else {
						printf(
								"ERROR: No hay espacio para disponible para borrar.\n");
						return 0;
					}
				}
			} else {
				int resta = bytes + structDisco.part[i].auxiliar;
				int k = 0;
				int sumadora = 0;
				for (k = 0; k < 20; k++) {
					sumadora = sumadora + structDisco.part[i].exten[k].size;
				}
				if (resta > sumadora) {
					structDisco.part[i].auxiliar = resta;
					structDisco.part[i].size = resta;
				} else {
					printf("ERROR: No hay espacio disponible.\n");
					return 0;
				}
			}
		}
	}
//*****************************************************
	fseek(archivo, 0, SEEK_SET);
	fwrite(&structDisco, sizeof(mbr), 1, archivo);
	fclose(archivo);
	printf("-> Se realizo la modificacion correctamente.\n");
	return 1;

}

int eliminarParticion(char* dele, char* path, char* name) {

//VERIFICA SI EXISTE EL DISCO
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		path = generarPath(path);
		archivo = fopen(path, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	int esLogica = 0;
	int tipoDelete = 0;
	int i = 0;
	int j = 0;

//VERIFICA TIPO DE ELIMINAR
	if (strcasecmp(dele, "full") == 0) {
		tipoDelete = 1;
	} else if (strcasecmp(dele, "fast") == 0) {
		tipoDelete = 2;
	} else {
		printf("ERROR: Tipo de Delete incorrecto.\n");
		return 0;
	}

//VERIFICA SI EL NOMBRE EXISTE
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, name) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, name) == 0) {
				esLogica = 1;
				break;
			}
		}
		if (esLogica == 1) {
			break;
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre.\n");
		return 0;
	}

//SI EXISTE...

	if (esLogica == 1) {
		//si hay extendida
		if (j < 20) { //i , j lugar donde encontro la particion
			//LIMPIAR VARIABLES
			if (structDisco.part[i].exten[j + 1].status != '0') {
				structDisco.part[i].exten[j].status = '0';
				strcpy(structDisco.part[i].exten[j].name, " ");
			} else {
				structDisco.part[i].exten[j].status = '0';
				structDisco.part[i].exten[j].start = 0;
				structDisco.part[i].exten[j].size = 0;
				structDisco.part[i].exten[j].auxiliar = 0;
				strcpy(structDisco.part[i].exten[j].name, " ");
			}
		} else { //Si no hay extendida
			structDisco.part[i].exten[j].status = '0';
			structDisco.part[i].exten[j].start = 0;
			structDisco.part[i].exten[j].size = 0;
			structDisco.part[i].exten[j].auxiliar = 0;
			strcpy(structDisco.part[i].exten[j].name, " ");
		}
	} else { // Si no existe
		if (i < 3) {
			if (structDisco.part[i + 1].status != '0') {
				if (structDisco.part[i].type == 'e'
						|| structDisco.part[i].type == 'E') {
					int k = 0;
					structDisco.part[i].type = '0'; //+
					for (k = 0; k < 20; k++) {
						structDisco.part[i].exten[k].status = '0';
						structDisco.part[i].exten[k].start = 0;
						structDisco.part[i].exten[k].size = 0;
						structDisco.part[i].exten[k].auxiliar = 0;
						strcpy(structDisco.part[i].exten[k].name, " ");
					}
				}
				structDisco.part[i].status = '0';
				structDisco.part[i].type = '0';
				strcpy(structDisco.part[i].name, " ");
			} else {
				if (structDisco.part[i].type == 'e'
						|| structDisco.part[i].type == 'E') {
					int k = 0;
					structDisco.part[i].type = '0'; //+
					for (k = 0; k < 20; k++) {
						structDisco.part[i].exten[k].status = '0';
						structDisco.part[i].exten[k].start = 0;
						structDisco.part[i].exten[k].size = 0;
						structDisco.part[i].exten[k].auxiliar = 0;
						strcpy(structDisco.part[i].exten[k].name, " ");
					}
				}
				structDisco.part[i].status = '0';
				structDisco.part[i].start = 0;
				structDisco.part[i].size = 0;
				structDisco.part[i].auxiliar = 0;
				structDisco.part[i].type = '0';
				strcpy(structDisco.part[i].name, " ");
			}
		} else {
			if (structDisco.part[i].type == 'e'
					|| structDisco.part[i].type == 'E') {
				int k = 0;
				for (k = 0; k < 8; k++) {
					structDisco.part[i].exten[k].status = '0';
					structDisco.part[i].exten[k].start = 0;
					structDisco.part[i].exten[k].size = 0;
					structDisco.part[i].exten[k].auxiliar = 0;
					strcpy(structDisco.part[i].exten[k].name, " ");
				}
			}
			structDisco.part[i].status = '0';
			structDisco.part[i].start = 0;
			structDisco.part[i].size = 0;
			structDisco.part[i].auxiliar = 0;
			structDisco.part[i].type = '0';
			strcpy(structDisco.part[i].name, " ");
		}
	}
	fseek(archivo, 0, SEEK_SET);
	fwrite(&structDisco, sizeof(mbr), 1, archivo);
	fclose(archivo);
	printf("-> Se elimino correctamente.\n");
	return 1;
}

void montarP() {
	if (path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio. %s - %s\n", name, path);
	} else {
		//	printf("else\n");
		int d = montarParticion(path, name);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int montarParticion(char* path, char* name) {
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		path = generarPath(path);
		archivo = fopen(path, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICA SI EL NOMBRE DE LA PARTICION EXISTE
	int existeLogica = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < 4; i++) {
		//printf("%s * * * %s\n", structDisco.part[i].name, name);
		if (strcasecmp(structDisco.part[i].name, name) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, name) == 0) {
				//printf("%s * * * %s\n", structDisco.part[i].exten[j].name, name);
				existeLogica = 1;
				break;
			}
			if (existeLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre de la particion.\n");
		fclose(archivo);

		return 0;
	}
	/*superbloque sb;
	 char ajuste;

	 int posicion;
	 if (existeLogica == 1) {
	 posicion = structDisco.part[i].exten[j].start;
	 ajuste = structDisco.part[i].exten[j].fit;
	 fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
	 fread(&sb, sizeof(superbloque), 1, archivo);
	 } else {
	 posicion = structDisco.part[i].start;
	 ajuste = structDisco.part[i].fit;
	 fseek(archivo, structDisco.part[i].start, SEEK_SET);
	 fread(&sb, sizeof(superbloque), 1, archivo);
	 }

	 sb.FechaMontado = time(0);
	 */
	//VERIFICAR SI EL PATH Y LA PARTICION YA ESTA REGISTRADO
	int pop = 0;
	for (pop = 0; pop < 31; pop++) {

		if (strcasecmp(montar[pop].path, path) == 0
				&& strcasecmp(montar[pop].name, name) == 0) {
			if (montar[pop].estado == 1) {
				printf("-> La particion ya esta montada:: %s\n",
						montar[pop].vdID);
			} else {
			}
			fclose(archivo);
			return 0;
		}
	}
	int a = 0, c = 0;
	int v = 0, boolExistePath = 0;

	for (a = 0; a < 31; a++) {
		if (strcasecmp(montar[a].path, path) == 0) {
			c++;
			boolExistePath = 1;
			v = montar[a].var;
		} else {
		}
	}

	if (boolExistePath == 1) {
		for (a = 0; a < 31; a++) {
			if (montar[a].uso == 0) {
				break;
			}
		}
		int cont = 0;
		for (pop = 0; pop < 31; pop++) {
			if (path != NULL) {
				if (strcasecmp(montar[pop].path, path) == 0) {
					cont++;
				}
			}
		}

		montar[a].estado = 1;
		montar[a].uso = '1';
		strcpy(montar[a].path, path);
		strcpy(montar[a].name, name);
		int p;
		p = montar[a].part;
		p = p + 1;
		montar[a].part++;
		//printf("v= %d\n", v);
		char *letra = letraDisco(v);
		char *num = numeroMontar(cont);
		char *str = (char *) malloc(1 + strlen(letra) + strlen(num));
		strcpy(str, letra);
		strcat(str, num);
		montar[a].vdID = str;
		montar[a].var = v;
		printf("-> Se monto la particion con id::%s correctamente.\n", str);

	} else {
		for (a = 0; a < 31; a++) {
			if (montar[a].uso == 0) {
				break;
			}
		}
		varLetra++;
		v = varLetra;
		montar[a].estado = 1;
		montar[a].uso = '1';
		strcpy(montar[a].path, path);
		montar[a].var = v;
		montar[a].part = 1;
		strcpy(montar[a].name, name);

		char *letra = letraDisco(varLetra);
		char *num = "1";
		char *str = (char *) malloc(1 + strlen(letra) + strlen(num));
		strcpy(str, letra);
		strcat(str, num);
		montar[a].vdID = str;
		printf("-> Se monto la particion con id::%s correctamente.\n", str);
	}

	fclose(archivo);
	contadorM += 1;
	return 1;
}

void mostrarMontadas() {
	int j = 0;
	int bool = 0;
	for (j = 0; j < 10; j++) {
		if (montar[j].estado == 1) {
			printf("M%d * id= %s  path= %s  nombre= %s \n", j, montar[j].vdID,
					montar[j].path, montar[j].name);
			bool = 1;
		}
	}
	if (bool == 0) {
		printf("-> No existe ninguna particion montada.\n");
	}
}

char *numeroMontar(int num) {
	char *numero;
	switch (num) {
	case 0:
		numero = "1";
		break;

	case 1:
		numero = "2";
		break;
	case 2:
		numero = "3";
		break;
	case 3:
		numero = "4";
		break;
	case 4:
		numero = "5";
		break;
	case 5:
		numero = "6";
		break;
	case 6:
		numero = "7";
		break;
	case 7:
		numero = "8";
		break;
	case 8:
		numero = "9";
		break;
	case 9:
		numero = "10";
		break;
	case 10:
		numero = "11";
		break;
	case 11:
		numero = "12";
		break;
	case 12:
		numero = "13";
		break;
	}
	return numero;
}

char *letraDisco(int varLetra) {
	char *letra;
	switch (varLetra) {
	case 0:
		letra = "vd";
		break;
	case 1:
		letra = "vda";
		break;
	case 2:
		letra = "vdb";
		break;
	case 3:
		letra = "vdc";
		break;
	case 4:
		letra = "vdd";
		break;
	case 5:
		letra = "vde";
		break;
	case 6:
		letra = "vdf";
		break;
	case 7:
		letra = "vdg";
		break;
	case 8:
		letra = "vdh";
		break;
	case 9:
		letra = "vdi";
		break;
	case 10:
		letra = "vdj";
		break;
	case 11:
		letra = "vdk";
		break;
	case 12:
		letra = "vdl";
		break;
	}

	return letra;
}

void desmontar() {
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = desmontarParticion(id);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
	mostrarMontadas();
	contadorM -= 1;
}

int desmontarParticion(char* id) {
//printf("ID=%s\n", id);
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			char *inst = NULL;
			inst = strtok(id, "\n");
			//printf("NOT NULL -> %s-%s-\n", montar[i].vdID, inst);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				//	printf("igual\n");
				if (montar[i].estado == 1) {
					montar[i].estado = 0;
					montar[i].vdID = NULL;
					strcpy(montar[i].path, "");
					strcpy(montar[i].name, "");
					printf("-> Se ha desmontado la particion correctamente.\n");
					return 1;
				}
			}
		}
	}
	printf("ERROR: El ID no existe.\n");
	return 0;

}

int aleatorio() {
	srand(time(NULL));
	int test = rand() % 20;
	return test;
}

void formatear() {
	//Atributos opcionales
	if (type == NULL) {
		type = "full"; //kilobytes
	}
	if (unit == NULL) {
		unit = "k"; //kilobytes
	}

	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		fflush(NULL);
		int d = formatearDisco(id, type, add, unit, fs);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			return;
		} else {
			printf("-> Se ha dado formato a la particion correctamente.\n");
			crearArchivoParticion(id, "/home/users.txt", "si", "10",
					"/home/aylin/vacio.txt");
			printf("-> Se ha creado el archivo USERS correctamente.\n");

		}

//		//Recover :: No se actualiza
		path = obtenerRuta(id);
		char pathAux[100];
		strcpy(pathAux, path);
		char *nombre = obtenerNombre(path);
		char *recovery = concatenar(
				"/home/aylin/workspaceNeon/ProyectoArchivos/recovery/recovery",
				nombre);
//		copiarFichero(pathAux, recovery);
		strcpy(path, pathAux);
		//Copy
		char pathAux2[100];
		strcpy(pathAux2, path);
		ruta = generarPath(path);
		copiarFichero(pathAux2, ruta);

		strcpy(path, pathAux2);
		strcpy(ruta, pathAux2);

		/////////////////////////////////////////////////////////

	}
}

int formatearDisco(char* id, char* type, char* add, char* unit, char* fs) {

	if (strcasecmp(type, "full") == 0 || strcasecmp(type, "fast") == 0) {
	} else {
		printf("ERROR: Tipo no existe.\n");
		return 0;
	}
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		//printf("COMPARAR Mkfs:: %s - %s\n",structDisco.part[i].name,nombre);
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}

	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	//printf("N1:: %s\n",structDisco.part[i].name);

	superbloque sb;
	int pos = 0;
	int n = 0;
	int tam = 0;
	if (existeLogica == 1) { //Si la particion es journalica
		n = structDisco.part[i].exten[j].auxiliar - sizeof(superbloque);
		int m = (1 + sizeof(journal) + 3 + sizeof(inodo) + 3 * sizeof(datos));
		int nn = n / m;

		tam = floor(nn);
		//printf("tam1== %d\n", tam);
		pos = tam;
		sb.s.arbolVirtualCount = tam;
		sb.s.detalleDirectorioCount = tam * 2;
		sb.inodosCount = tam;
		sb.bloquesCount = tam * 3;
		sb.freeBloquesCount = tam - 1;
		sb.freeInodosCount = (tam * 3) - 10;
		sb.FechaMontado = time(0);
		sb.FechaDesmontado = time(0);
		sb.mountCount = 0;
		sb.magic = 201404368;  //0xEF53
		sb.inodoSize = sizeof(inodo);
		sb.bloqueSize = sizeof(datos);
		sb.jourfirst = sb.apuntadorBloques + sizeof(datos);
		sb.s.apuntadorBitArbolDirectorio = structDisco.part[i].exten[j].start
				+ sizeof(superbloque);
		sb.s.apuntador = structDisco.part[i].exten[j].start
				+ sizeof(superbloque) + tam;
		sb.s.apuntadorBitDetalleDirectorio = structDisco.part[i].exten[j].start
				+ sizeof(superbloque) + tam + sizeof(apunt);
		sb.s.apuntadorDetalleDirectorio = sb.s.apuntadorBitDetalleDirectorio
				+ tam;
		sb.apuntadorBitTablaInodo = sb.s.apuntadorDetalleDirectorio
				+ sizeof(detalle);
		sb.apuntadorTablaInodo = sb.apuntadorBitTablaInodo + tam;
		sb.s.apuntadorBitmapInodo = sb.apuntadorTablaInodo + sizeof(inodo);
		sb.firstFreeBitTablaInodo = 1;
		sb.firstFreeBitBloque = 1;

		//USUARIOS-GRUPOS
		sb.s.contadorU = 0;
		strcpy(sb.user[sb.s.contadorU].usuario.id, "1");
		strcpy(sb.user[sb.s.contadorU].usuario.tipo, "G");
		strcpy(sb.user[sb.s.contadorU].usuario.grupo, "root");
		sb.s.contadorU++;
		strcpy(sb.user[sb.s.contadorU].usuario.id, "1");
		strcpy(sb.user[sb.s.contadorU].usuario.tipo, "U");
		strcpy(sb.user[sb.s.contadorU].usuario.grupo, "root");
		strcpy(sb.user[sb.s.contadorU].usuario.usuario, "root");
		strcpy(sb.user[sb.s.contadorU].usuario.clave, "201404368");
		sb.s.contadorU++;
		sb.s.contadorP = 0;

		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);

	} else {
		n = structDisco.part[i].auxiliar - sizeof(superbloque);
		int m = (1 + sizeof(journal) + 3 + sizeof(inodo) + 3 * sizeof(datos));
		int nn = n / m;
		tam = floor(nn);
		printf("tam1== %d\n", tam);

		pos = tam;
		//sb.nombre = name;
		sb.s.arbolVirtualCount = tam;
		sb.s.detalleDirectorioCount = tam * 2;
		sb.inodosCount = tam;
		sb.bloquesCount = tam * 3;
		sb.freeBloquesCount = tam - 1;
		sb.freeInodosCount = (tam * 3) - 10;
		sb.FechaDesmontado = time(0);
		sb.FechaMontado = time(0);
		sb.mountCount = 0;
		sb.magic = 201404368;  //0xEF53
		sb.inodoSize = sizeof(inodo);
		sb.bloqueSize = sizeof(datos);
		sb.jourfirst = sb.apuntadorBloques + sizeof(datos);
		sb.s.apuntadorBitArbolDirectorio = structDisco.part[i].start
				+ sizeof(superbloque);
		sb.s.apuntador = structDisco.part[i].start + sizeof(superbloque) + tam;
		sb.s.apuntadorBitDetalleDirectorio = structDisco.part[i].start
				+ sizeof(superbloque) + tam + sizeof(apunt);
		sb.s.apuntadorDetalleDirectorio = sb.s.apuntadorBitDetalleDirectorio
				+ tam;
		sb.apuntadorBitTablaInodo = sb.s.apuntadorDetalleDirectorio
				+ sizeof(detalle);
		sb.apuntadorTablaInodo = sb.apuntadorBitTablaInodo + tam;
		sb.s.apuntadorBitmapInodo = sb.apuntadorTablaInodo + sizeof(inodo);
		sb.firstFreeBitTablaInodo = 1;
		sb.firstFreeBitBloque = 1;

		//USUARIOS-GRUPOS
		sb.s.contadorU = 0;
		strcpy(sb.user[sb.s.contadorU].usuario.id, "1");
		strcpy(sb.user[sb.s.contadorU].usuario.tipo, "G");
		strcpy(sb.user[sb.s.contadorU].usuario.grupo, "root");
		sb.s.contadorU++;
		strcpy(sb.user[sb.s.contadorU].usuario.id, "1");
		strcpy(sb.user[sb.s.contadorU].usuario.tipo, "U");
		strcpy(sb.user[sb.s.contadorU].usuario.grupo, "root");
		strcpy(sb.user[sb.s.contadorU].usuario.usuario, "root");
		strcpy(sb.user[sb.s.contadorU].usuario.clave, "201404368");
		sb.s.contadorU++;
		sb.s.contadorP = 0;

		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);

	}
	sb.s.contadorJ = 0;

	char bitm = '0';
	char bitm1 = '1';
	fseek(archivo, sb.s.apuntadorBitArbolDirectorio, SEEK_SET);
	fwrite(&bitm1, 1, 1, archivo);
	int io = 0;
	for (io = 0; io < (pos) - 1; io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	fseek(archivo, sb.s.apuntadorBitDetalleDirectorio, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	fseek(archivo, sb.apuntadorBitTablaInodo, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	fseek(archivo, sb.s.apuntadorBitmapInodo, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	apunt insertar;
	insertar.apuntador = -1;
	insertar.directorio = 0;
	strcpy(insertar.pointer, "/");
	int ip = 0;
	for (ip = 0; ip < 4; ip++) {
		insertar.subDirectorios[ip] = 0;
	}
	fseek(archivo, sb.s.apuntador, SEEK_SET);
	fwrite(&insertar, sizeof(apunt), 1, archivo);

//CAMBIOS EN EL JOURNALING
	journal bitacora;

	bitacora.operacion = 1;
	bitacora.tipo = 0;
	bitacora.fecha = time(0);
	strcpy(bitacora.nombre, "Formatear");
	strcpy(bitacora.contenido, "Formatear");
	fseek(archivo, sb.jourfirst, SEEK_SET); //**
	fwrite(&bitacora, sizeof(journal), 1, archivo);

	fclose(archivo);
	strcpy(structDisco.part[i].name, montar[i].name);
	return 1;
}

void crearArchivo() {
	if (id == NULL || path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = crearArchivoParticion(id, path, p, size, cont);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int crearArchivoParticion(char* id, char* path, char* p, char* size, char* cont) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//		printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		//printf("Comparar= *%s* - *%s*\n", montar[i].name, nombre);
		if (strcasecmp(structDisco.part[i].name, nombre) == 0
				|| strcmp(nombre, structDisco.part[i].name) == 0) {
			//	printf("eureka\n");
			break;
		}
		for (j = 0; j < 20; j++) { //logica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}
	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado (CAP).\n");
		return 0;
	}
	superbloque sb;
	char ajuste;

	int posicion;
	if (existeLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	FILE* archivoCont;
	archivoCont = fopen(cont, "r");
	int existeCont = 1;

	if (cont == NULL) {
		existeCont = 0;
	} else if (archivoCont == NULL) {
		printf("ERROR: No existe ruta de cont.\n");
		return 0;
	}

	int tamanio;
	if (existeCont > 0) {
		fseek(archivoCont, 0, SEEK_END);
		tamanio = ftell(archivoCont);
	} else {
		tamanio = atoi(size);
	}

	if (tamanio < 0) {
		printf("ERROR: El tamanio es incorrecto.\n");
		return 0;
	}
	//printf("MAGIC = %d\n", sb.magic);
//	sb.magic = 201404368;
	if (sb.magic == 201404368) {
		fseek(archivo, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100] = "";
		char verificar[100] = "";
		char verificar2[100] = "";
		strcpy(crear, path);

		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') {
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}
		char* rutaC;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			p = "si";
			rutaC = strtok(crear, "/");
		} else {
			rutaC = strtok(verificar, "/");
		}
		fclose(archivo);
		int informacion = 0;
		int datos = 0;

		correcto = 1; //**
		//printf("crearCarpeta ="); //
		//setbuf(stdin, NULL);
		informacion = crearCarpeta(ruta, sb, ap, rutaC, p, ajuste, posicion,
				sb.s.apuntador);
		//printf("%d\n", correcto);
		if (correcto > 0) {
			rutaC = strtok(verificar2, "/");
			//printf("buscar\n");
			datos = buscarArchivo(ruta, sb, ap, rutaC, ajuste, posicion,
					sb.s.apuntador);

			if (datos > 0) {
				rutaC = strtok(crear, "/");	//verificar si ruta es igual a NULO
				while ((strstr(rutaC, ".") == 0x0 || strstr(rutaC, ".") == ""
						|| strstr(rutaC, ".") == NULL) && rutaC != NULL) {
					rutaC = strtok(NULL, "/");
					//		printf("rutaC= %s\n",rutaC);
					if (rutaC == NULL || rutaC == 0x0) {
						break;
					}
				}
				char leer[tamanio];
				if (archivoCont != NULL) {
					fseek(archivoCont, 0, SEEK_SET);
					fread(&leer, tamanio, 1, archivoCont);
				} else {
					printf("Sin contenido.\n");
					int r, c = 0;
					for (r = 0; r < 64; r++) {
						leer[r] = (char) (c + 48);
						c++;
						if (c > 9) {
							c = 0;
						}
					}
				}
				char contenido[100];
				//printf("ruta= %s\n", ruta);
				if (rutaC != NULL || rutaC != 0x0) {
					//				printf("agregarContenido\n");
					agregarContenido(datos, sb, ruta, rutaC, ajuste, leer,
							tamanio, structDisco);
					if (size == 0x0 || size == NULL) {
						strcat(contenido, "-cont:");
						strcat(contenido, cont);
					} else {
						strcat(contenido, "-size:");
						strcat(contenido, size);
					}
					printf("-> Se ha creado el archivo correctamente.\n");

					//journaling(ruta, posicion, sb, 1, path, leer, id, 0);

				} else {
				}

			} else {
				printf("ERROR: No se ha podido crear el archivo.\n");
			}
		}
	} else {
		printf("ERROR: No se ha formateado la particion.\n");
	}
	return 1;
}

int agregarContenido(int posicion, superbloque super, char* ruta, char* name,
		char ajuste, char* contenido, int size, mbr structDisco) {

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	fflush(NULL);
	int i = 0, k = 0;
	int j = 0;
	for (i = 0; i < 5; i++) { //Maneja 5 inodos

		if (carp.content[i].inodo > 1) {
			if (strcasecmp(carp.content[i].name, name) == 0) {
				if (boolEditar == 0) {
					printf("ERROR: El nombre ya existe.\n");
					return 0;
				} else {
				}
				break;
			}
			k++;

		} else {
			j = i;
		}
	}
	if (k > 4) {
		if (carp.detalle > 0) {
			fclose(archivo);
			return agregarContenido(carp.detalle, super, ruta, name, ajuste,
					contenido, size, structDisco);
		} else {
			detalle carp;
			carp.detalle = 0;
			int a = 0;
			for (a = 0; a < 5; a++) {
				carp.content[a].inodo = -1;
			}
			int posicion = 0;
			fclose(archivo);

			if (ajuste == 'w' || ajuste == 'W') {
				posicion = peorAjuste(super.s.arbolVirtualCount, ruta,
						super.s.apuntadorBitDetalleDirectorio, 1);
			} else if (ajuste == 'f' || ajuste == 'F') {
				posicion = primerAjuste(super.s.arbolVirtualCount, ruta,
						super.s.apuntadorBitDetalleDirectorio, 1);
			} else {
				posicion = mejorAjuste(super.s.arbolVirtualCount, ruta,
						super.s.apuntadorBitDetalleDirectorio, 1);
			}
//			printf("ArbolCount1 = %d\n",super.s.arbolVirtualCount);
			FILE* disco;
			disco = fopen(ruta, "rb+");

			carp.detalle = super.s.apuntadorDetalleDirectorio
					+ 100 * posicion * sizeof(detalle);
			fseek(disco, posicion, SEEK_SET);
			fwrite(&carp, sizeof(detalle), 1, disco);

			fseek(disco,
					super.s.apuntadorDetalleDirectorio
							+ 100 * posicion * sizeof(detalle), SEEK_SET);
			fwrite(&carp, sizeof(detalle), 1, disco);
			fclose(disco);
			setbuf(stdin, NULL);
			printf("agregar2\n");
			return agregarContenido(carp.detalle, super, ruta, name, ajuste,
					contenido, size, structDisco);
		}
	} else { //Se crean los inodos
		printf("Creando inodos\n");
		strcpy(carp.content[j].name, name);
		int pos = 0;
		fclose(archivo);
		//	printf("ArbolCount2 = %d\n",super.s.arbolVirtualCount);
		if (ajuste == 'w' || ajuste == 'W') {
			pos = peorAjuste(super.s.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		} else if (ajuste == 'f' || ajuste == 'F') {
			pos = primerAjuste(super.s.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		} else {
			pos = mejorAjuste(super.s.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		}
		FILE* disco;
		disco = fopen(ruta, "rb+");
		carp.content[j].inodo = super.apuntadorTablaInodo
				+ 100 * pos * sizeof(inodo);
		fseek(disco, posicion, SEEK_SET);
		fwrite(&carp, sizeof(detalle), 1, disco);
		fclose(disco);
		//printf("ArbolCount3 = %d\n",super.s.arbolVirtualCount);
		inodo ino;
		ino.noAsignados = pos;
		ino.size = size;
		ino.indirecto = 0;
		int aux = size / 25;

		if (size % 25) {
			aux++;
		}
		datos arch;
		char conten[20000] = "";
		//printf("ArbolCount3.1 = %d\n",super.s.arbolVirtualCount);
		//
		//printf("tam = %d - aux =%d\n", strlen(contenido), aux);

		strcpy(conten, contenido);
//		printf("ArbolCount3.2 = %d\n",super.s.arbolVirtualCount);
		int l, m = 0;
		int pos2 = 0;

		if (aux < 5) {

			ino.noInodo = size / 25;
			if (size % 25 > 0) {
				ino.noInodo++;
			}
			//printf("NoInodo = %d\n", ino.noInodo);
			ino.indirecto = 0;
//			setbuf(stdin, NULL);
			//printf("Count4 = %d\n",super.s.arbolVirtualCount);
			for (l = 0; l < ino.noInodo; l++) {
				if (ajuste == 'w' || ajuste == 'W') {
					pos2 = peorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f' || ajuste == 'F') {
					pos2 = primerAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				} else {
					pos2 = mejorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(ruta, "rb+");
				for (m = 0; m < 25; m++) {
					arch.data[m] = conten[l * 25 + m];
				}
				//return 1;
				ino.bloques[l] = super.apuntadorBloques
						+ 100 * pos2 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos2 * sizeof(datos),
						SEEK_SET);
				fwrite(&arch, sizeof(datos), 1, disco);
				fclose(disco);
				//return 1;
				//	printf("ArbolCount5 = %d\n",super.s.arbolVirtualCount);
			}

		} else {
			printf("Si es el ultimo inodo\n");
			ino.noInodo = 4;
			for (l = 0; l < 4; l++) {
				if (ajuste == 'w' || ajuste == 'W') {
					pos2 = peorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f' || ajuste == 'F') {
					pos2 = primerAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				} else {
					pos2 = mejorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(ruta, "rb+");
				for (m = 0; m < 25; m++) {
					arch.data[m] = conten[l * 25 + m];
				}
				ino.bloques[l] = super.apuntadorBloques
						+ 100 * pos2 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos2 * sizeof(datos),
						SEEK_SET);
				fwrite(&arch, sizeof(datos), 1, disco);
				fclose(disco);
				//printf("ArbolCount7 = %d\n",super.s.arbolVirtualCount);
			}
			//printf("2**");
			int pos3 = 0;
			if (ajuste == 'w' || ajuste == 'W') {
				pos3 = peorAjuste(super.s.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			} else if (ajuste == 'f' || ajuste == 'F') {
				pos3 = primerAjuste(super.s.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			} else {
				pos3 = mejorAjuste(super.s.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			}
			//printf("3**");
			inodo ino2;
			ino2.noAsignados = pos3;
			ino2.size = size;
			ino2.indirecto = 0;
			ino2.noInodo = (size - 100) / 25;
			if ((size - 100) % 25 > 0) {
				ino2.noInodo++;
			}
			if (ino2.noInodo > 4) {
				ino2.noInodo = 4;
			}
			//printf("ArbolCount8 = %d\n",super.s.arbolVirtualCount);
			int pos4 = 0;
			//setbuf(stdin, NULL);
			for (l = 0; l < ino2.noInodo; l++) {
				if (ajuste == 'w' || ajuste == 'W') {
					pos4 = peorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f' || ajuste == 'F') {
					pos4 = primerAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				} else {
					pos4 = mejorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitmapInodo, 1);
				}
				//printf("4**");
				FILE* disco;
				disco = fopen(ruta, "rb+");
				int m = 0;
				for (m = 0; m < 25; m++) {
					arch.data[m] = conten[l * 25 + m + 100];
				}
				ino2.bloques[l] = super.apuntadorBloques
						+ 100 * pos4 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos4 * sizeof(datos),
						SEEK_SET);
				fwrite(&arch, sizeof(datos), 1, disco);
				fclose(disco);
				//printf("ArbolCount9 = %d\n",super.s.arbolVirtualCount);
				//printf("5\n");
			}

			disco = fopen(ruta, "rb+");
			ino.indirecto = super.s.apuntadorDetalleDirectorio
					+ 100 * pos3 * sizeof(inodo);
			fseek(disco,
					super.s.apuntadorDetalleDirectorio
							+ 100 * pos3 * sizeof(inodo), SEEK_SET);
			fwrite(&ino2, sizeof(inodo), 1, disco);
			fclose(disco);
			//printf("6\n");
//			printf("ArbolCount10 = %d\n",super.s.arbolVirtualCount);
		}
		disco = fopen(ruta, "rb+");
		fseek(disco, super.apuntadorTablaInodo + 100 * pos * sizeof(inodo),
		SEEK_SET);
		fwrite(&ino, sizeof(inodo), 1, disco);
		fclose(disco);
		fflush(NULL);
		printf("-> Se agrego el contenido correctamente.\n");
		//printf("7\n");
		return 1;
	}
}

int agregarArchivo(int posicion, superbloque super, char* aux4, char* name,
		char ajuste, char* contenido, int size) {
	FILE* disco;
	disco = fopen(aux4, "rb+");
	detalle con;
	fseek(disco, posicion, SEEK_SET);
	fread(&con, sizeof(detalle), 1, disco);
	int i = 0;
	int k = 0;
	int w = 0;
	for (i = 0; i < 5; i++) {

		if (con.content[i].inodo > 1) {
			if (strcasecmp(con.content[i].name, name) == 0) {
				printf("Ya existe ese nombre");
				return 0;
				break;
			}
			k++;
		} else {
			w = i;
		}
	}
	if (k > 4) {
		if (con.detalle > 0) {
			fclose(disco);
			return agregarArchivo(con.detalle, super, aux4, name, ajuste,
					contenido, size);
		} else {
			detalle conx;
			conx.detalle = 0;
			int uy = 0;
			for (uy = 0; uy < 5; uy++) {
				conx.content[uy].inodo = -1;
			}
			int pos = 0;
			fclose(disco);
			if (ajuste == 'w') {
				pos = peorAjuste(super.s.arbolVirtualCount, aux4,
						super.s.apuntadorBitDetalleDirectorio, 1);
			} else if (ajuste == 'f') {
				pos = primerAjuste(super.s.arbolVirtualCount, aux4,
						super.s.apuntadorBitDetalleDirectorio, 1);
			} else {
				pos = mejorAjuste(super.s.arbolVirtualCount, aux4,
						super.s.apuntadorBitDetalleDirectorio, 1);
			}
			FILE* disco;
			disco = fopen(aux4, "rb+");

			con.detalle = super.s.apuntadorDetalleDirectorio
					+ 100 * pos * sizeof(detalle);
			fseek(disco, posicion, SEEK_SET);
			fwrite(&con, sizeof(detalle), 1, disco);

			fseek(disco,
					super.s.apuntadorDetalleDirectorio
							+ 100 * pos * sizeof(detalle), SEEK_SET);
			fwrite(&conx, sizeof(detalle), 1, disco);
			fclose(disco);
			return agregarArchivo(con.detalle, super, aux4, name, ajuste,
					contenido, size);
		}
	} else {
		//aqui crear inodos y esas cosas;
		//con.archivos[w].fechaCreacion = time(0);
		//con.archivos[w].fechaModifica = time(0);
		strcpy(con.content[w].name, name);

		int pos = 0;
		fclose(disco);
		if (ajuste == 'w') {
			pos = peorAjuste(super.s.arbolVirtualCount, aux4,
					super.apuntadorBitTablaInodo, 1);
		} else if (ajuste == 'f') {
			pos = primerAjuste(super.s.arbolVirtualCount, aux4,
					super.apuntadorBitTablaInodo, 1);
		} else {
			pos = mejorAjuste(super.s.arbolVirtualCount, aux4,
					super.apuntadorBitTablaInodo, 1);
		}
		FILE* disco;
		disco = fopen(aux4, "rb+");

		con.content[w].inodo = super.apuntadorTablaInodo
				+ 100 * pos * sizeof(inodo);
		fseek(disco, posicion, SEEK_SET);
		fwrite(&con, sizeof(detalle), 1, disco);
		fclose(disco);
		inodo conx;
		conx.noAsignados = pos;
		conx.size = size;
		int axulii = size / 25;
		if (size % 25) {
			axulii++;
		}
		datos conq;
		char q[200];
		strcpy(q, contenido);
		int yu, qw = 0;
		int pos2 = 0;
		if (axulii < 5) {
			conx.noInodo = size / 25;
			if (size % 25 > 0) {
				conx.noInodo++;
			}
			conx.indirecto = 0;
			for (yu = 0; yu < conx.noInodo; yu++) {
				if (ajuste == 'w') {
					pos2 = peorAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos2 = primerAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				} else {
					pos2 = mejorAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(aux4, "rb+");
				for (qw = 0; qw < 25; qw++) {
					conq.data[qw] = q[yu * 25 + qw];
				}
				conx.bloques[yu] = super.apuntadorBloques
						+ 100 * pos2 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos2 * sizeof(datos),
						SEEK_SET);
				fwrite(&conq, sizeof(datos), 1, disco);
				fclose(disco);
			}
		} else {
			conx.noInodo = 4;
			for (yu = 0; yu < 4; yu++) {
				if (ajuste == 'w') {
					pos2 = peorAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos2 = primerAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				} else {
					pos2 = mejorAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(aux4, "rb+");
				for (qw = 0; qw < 25; qw++) {
					conq.data[qw] = q[yu * 25 + qw];
				}
				conx.bloques[yu] = super.apuntadorBloques
						+ 100 * pos2 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos2 * sizeof(datos),
						SEEK_SET);
				fwrite(&conq, sizeof(datos), 1, disco);
				fclose(disco);
			}
			int pos3 = 0;
			if (ajuste == 'w') {
				pos3 = peorAjuste(super.s.arbolVirtualCount, aux4,
						super.apuntadorBitTablaInodo, 1);
			} else if (ajuste == 'f') {
				pos3 = primerAjuste(super.s.arbolVirtualCount, aux4,
						super.apuntadorBitTablaInodo, 1);
			} else {
				pos3 = mejorAjuste(super.s.arbolVirtualCount, aux4,
						super.apuntadorBitTablaInodo, 1);
			}
			inodo conxw;
			conxw.noAsignados = pos3;
			conxw.size = size;
			conxw.indirecto = 0;
			conxw.noInodo = (size - 100) / 25;
			if ((size - 100) % 25 > 0) {
				conxw.noInodo++;
			}
			if (conxw.noInodo > 4) {
				conxw.noInodo = 4;
			}
			int pos4 = 0;
			for (yu = 0; yu < conxw.noInodo; yu++) {
				if (ajuste == 'w') {
					pos4 = peorAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos4 = primerAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				} else {
					pos4 = mejorAjuste(super.s.arbolVirtualCount, aux4,
							super.s.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(aux4, "rb+");
				int qw = 0;
				for (qw = 0; qw < 25; qw++) {
					conq.data[qw] = q[yu * 25 + qw + 100];
				}
				conxw.bloques[yu] = super.apuntadorBloques
						+ 100 * pos4 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos4 * sizeof(datos),
						SEEK_SET);
				fwrite(&conq, sizeof(datos), 1, disco);
				fclose(disco);
			}

			disco = fopen(aux4, "rb+");
			conx.indirecto = super.s.apuntadorDetalleDirectorio
					+ 100 * pos3 * sizeof(inodo);
			fseek(disco,
					super.s.apuntadorDetalleDirectorio
							+ 100 * pos3 * sizeof(inodo), SEEK_SET);
			fwrite(&conxw, sizeof(inodo), 1, disco);
			fclose(disco);
		}

		disco = fopen(aux4, "rb+");
		fseek(disco, super.apuntadorTablaInodo + 100 * pos * sizeof(inodo),
		SEEK_SET);
		fwrite(&conx, sizeof(inodo), 1, disco);
		fclose(disco);

		printf("-> Se creo el archivo correctamente.\n");
	}

}

int crearCarpeta(char* ruta, superbloque super, apunt apun, char* path, char* p,
		char ajuste, int inicio, int atras) {
//	printf("p == %s\n",p);
	char* patito = path;

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap;
//	int m = super.apuntador;
	//printf("m= %d\n", m);
	if (atras > 800000000) {
		return 0;
	}
	fseek(archivo, atras, SEEK_SET);
	fread(&apun, sizeof(apunt), 1, archivo);
	int i = 0, x = 0, w = 0, qw = 0;

	for (i = 0; i < 4; i++) {
		//	printf("sub carpeta =%d\n",apun.subDirectorios[i]);
		if (apun.subDirectorios[i] > 0) {	//Si ya existe la carpeta
			fseek(archivo, apun.subDirectorios[i], SEEK_SET);
			fread(&ap, sizeof(ap), 1, archivo);
			char point[16] = "";
			strcpy(point, ap.pointer);
			if (strcasecmp(point, path) == 0) {
				break;
			}
		} else if (x == 0) {
			x = 1;
			w = i;
			qw++;
		} else {
			qw++;
		}
	}
	//printf("i = %d\n",i);
	if (i < 4) {
		path = strtok(NULL, "/");
		//	printf("path=%s\n", path);
		if (path != NULL && path != 0x0) {
			fclose(archivo);
			crearCarpeta(ruta, super, ap, path, p, ajuste, inicio,
					apun.subDirectorios[i]);
		} else {
			//	printf("NULO\n");
//			correcto=0;
			return 1;
		}
	} else if (i > 3 && x > 0) {
		if (p != NULL) {
			int pos = 0;
			fclose(archivo);
			if (ajuste == 'w') {
				pos = peorAjuste(super.s.arbolVirtualCount, ruta,
						super.s.apuntadorBitArbolDirectorio, 1);
			} else if (ajuste == 'f') {
				pos = primerAjuste(super.s.arbolVirtualCount, ruta,
						super.s.apuntadorBitArbolDirectorio, 1);
			} else {
				pos = mejorAjuste(super.s.arbolVirtualCount, ruta,
						super.s.apuntadorBitArbolDirectorio, 1);
			}
			FILE* archivo;
			archivo = fopen(ruta, "rb+");
			ap.apuntador = -1;
			ap.directorio = 0;
			//ap.fechaCreacion = time(0);
			strcpy(ap.pointer, "");
			strcpy(ap.pointer, path);
			int au = 0;
			for (au = 0; au < 4; au++) {
				ap.subDirectorios[au] = -1;
			}

			apun.subDirectorios[w] = super.s.apuntador
					+ 100 * pos * sizeof(apunt);
			fseek(archivo, atras, SEEK_SET);
			fwrite(&apun, sizeof(apunt), 1, archivo);

			fseek(archivo, super.s.apuntador + 100 * pos * sizeof(apunt),
			SEEK_SET);
			fwrite(&ap, sizeof(apunt), 1, archivo);
			path = strtok(NULL, "/");
			fclose(archivo);
			if (path != NULL) {
				//printf("hola\n");
				crearCarpeta(ruta, super, apun, path, p, ajuste, inicio,
						apun.subDirectorios[w]);
			} else {
				printf("-> Se creo la carpeta correctamente. %s\n", patito);
				return 1;
			}
		} else {
			correcto = 0;
			printf("*ERROR: La ruta indicada no existe.\n");
			return 0;
		}
	} else if (i > 3 && x < 1) {
		//printf("apun == %d\n",apun.apuntadorA);

		if (apun.apuntador < 0) {
			if (p != NULL) {
				int pos = 0;
				fclose(archivo);
				if (ajuste == 'w') {
					pos = peorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitArbolDirectorio, 1);
				} else if (ajuste == 'f') {
					pos = primerAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitArbolDirectorio, 1);
				} else {
					pos = mejorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitArbolDirectorio, 1);
				}
				FILE* disco;
				disco = fopen(ruta, "rb+");

				ap.apuntador = -1;
				ap.directorio = 0;
				//ap.fechaCreacion = time(0);
				strcpy(ap.pointer, apun.pointer);
				int aux = 0;
				for (aux = 0; aux < 6; aux++) {
					ap.subDirectorios[aux] = -1;
				}
				apun.apuntador = super.s.apuntador + 100 * pos * sizeof(apunt);

				fseek(disco, atras, SEEK_SET);
				fwrite(&apun, sizeof(apunt), 1, disco);

				fseek(disco, super.s.apuntador + 100 * pos * sizeof(apunt),
				SEEK_SET);
				fwrite(&ap, sizeof(apunt), 1, disco);

				if (path != NULL) {
					fclose(disco); //XXX
					crearCarpeta(ruta, super, ap, path, p, ajuste, inicio,
							apun.apuntador);
				}
			} else {
				correcto = 0;
				printf("/ERROR: La ruta indicada no existe.\n");
				return 0;
			}
		} else {
			fclose(archivo);
			crearCarpeta(ruta, super, apun, path, p, ajuste, inicio,
					apun.apuntador);
		}
	} else {
		correcto = 0;
		printf("ERROR: No se ha podido crear la carpeta.\n");
		return 0;
	}

	return 1;

}

int buscarArchivo(char* ruta, superbloque super, apunt ap, char* path,
		char ajuste, int inicio, int atras) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap2;
	//printf("apuntador = %d\n", super.apuntadorArbolDirectorio);
	fseek(archivo, atras, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, archivo);
	int i = 0, x = 0, qw = 0;

	for (i = 0; i < 6; i++) {
		//printf("sub = %d, ", ap.subDirectorios[i]);
		if (ap.subDirectorios[i] > 0) {
			fseek(archivo, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(apunt), 1, archivo);
			if (strcasecmp(ap2.pointer, path) == 0) {
				break;
			}
		} else if (x == 0) {
			x = 1;
			qw++;
		} else {
			qw++;
		}
	}
	//printf("i = %d\n", i);
	if (i < 6) {
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(archivo);
			//printf("return1\n");
			return buscarArchivo(ruta, super, ap2, path, ajuste, inicio,
					ap.subDirectorios[i]);
		} else {
			if (ap2.directorio > 0) {
				fclose(archivo);
				return ap2.directorio;
			} else {
				detalle c;
				c.detalle = 0;
				int uy = 0;
				for (uy = 0; uy < 5; uy++) {
					c.content[uy].inodo = -1; //+
				}
				int pos = 0;
				fclose(archivo);
				if (ajuste == 'w') {
					pos = peorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitDetalleDirectorio, 1);
				} else if (ajuste == 'f') {
					pos = primerAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitDetalleDirectorio, 1);
				} else {
					pos = peorAjuste(super.s.arbolVirtualCount, ruta,
							super.s.apuntadorBitDetalleDirectorio, 1);
				}
				FILE* archivo;
				archivo = fopen(ruta, "rb+");

				ap2.directorio = super.s.apuntadorDetalleDirectorio
						+ 100 * pos * sizeof(detalle);
				fseek(archivo, ap.subDirectorios[i], SEEK_SET);
				fwrite(&ap2, sizeof(apunt), 1, archivo);
				fclose(archivo);

				archivo = fopen(ruta, "rb+");
				fseek(archivo,
						super.s.apuntadorDetalleDirectorio
								+ 100 * pos * sizeof(detalle), SEEK_SET);
				fwrite(&c, sizeof(detalle), 1, archivo);
				fclose(archivo);
				return ap2.directorio;
			}
		}
	} else {
		//	printf("apuntador = %d\n", ap.apuntadorA);
		if (ap.apuntador < 1) {
			printf("ERROR: No existe carpeta \n");
			return 0;
		} else {
			fclose(archivo);
			return buscarArchivo(ruta, super, ap, path, ajuste, inicio,
					ap.apuntador);
		}
	}

}

int primerAjuste(int bloque, char* ruta, int inicio, int arch) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	int sig = 0;
	char leer;
	fseek(archivo, inicio, SEEK_SET);

	int i = 0;
	int posicion = 0;
	for (i = 0; i < bloque; i++) {
		fread(&leer, 1, 1, archivo);
		if (leer == '0') {		//Si es vacio
			sig++;
		} else {
			sig = 0;
		}
		if (sig == arch) {
			posicion = (i - (sig - 1));
			break;
		}
	}
	fseek(archivo, inicio + posicion, SEEK_SET);
	leer = '1';
	fwrite(&leer, 1, 1, archivo);
	fclose(archivo);
	return posicion;
}

int mejorAjuste(int bloque, char* ruta, int inicio, int arch) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	int posicion = 0;
	int sig = 0;
	int i = 0;
	int menor = bloque;
	char leer;
	fseek(archivo, inicio, SEEK_SET);
	for (i = 0; i < bloque; i++) {
		fread(&leer, 1, 1, archivo);
		if (leer == '0') {
			sig++;
		} else {
			if (menor > sig && sig != 0) {
				menor = sig;
				if (menor >= arch || menor == arch) {
					posicion = i - menor;
				}
			} else if (menor == bloque) {
				posicion = i + 1;
			}
			sig = 0;
		}

	}
	fseek(archivo, inicio + posicion, SEEK_SET);
	leer = '1';
	fwrite(&leer, 1, 1, archivo);
	fclose(archivo);
	return posicion;

}

int peorAjuste(int bloque, char* ruta, int inicio, int arch) {
	if (bloque > 20000) {
		printf("bloque = %d\n", bloque);
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	int posicion = 0;
	int sig = 0;
	int i = 0;
	int mayor = 0;
	int aux = 0;
	char leer;
	fseek(archivo, inicio, SEEK_SET);
	for (i = 0; i < bloque; i++) {
		fread(&leer, 1, 1, archivo);
		if (leer == '0') {
			sig++;

		} else {
			aux = i + 1;
			if (mayor < sig) {
				mayor = sig;
				if (mayor >= arch || mayor == arch) {
					posicion = i - mayor;
				}
			} else if (mayor == 0) {
				posicion = i + 1;
			}
			sig = 0;

		}

		if (sig >= arch) {
			if (aux == 0) {
				posicion = 0;
			} else {
				posicion = aux;
			}
		}

	}
	fseek(archivo, inicio + posicion, SEEK_SET);
	leer = '1';
	fwrite(&leer, 1, 1, archivo);
	fclose(archivo);
	return posicion;
}

void remover() {
	if (id == NULL || file1 == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = removerArchivo(id, file1, rf);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int removerArchivo(char* id, char* path, int rf) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				//	 printf("igual\n");
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}
	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb = crearBloque();
	char ajuste;

	int posicion;
	if (existeLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}
	//printf("M= %d\n", sb.magic);
	if (sb.magic == 201404368) {
		fseek(archivo, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);

		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') {
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}

		char* ruta1;
		char* ruta2;
		char auxPath[100];
		strcpy(auxPath, path);
		a = 0; //nuevas variables
		b = 0;
		for (a = 0; a < 100; a++) {
			if (auxPath[a] == '.') {
				b++;
			}
		}
		fclose(archivo);

		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		ruta2 = strtok(crear, ".");

		int datos = 0;

		if (b < 1) {
			ruta1 = strtok(crear, "/");
			printf("Eliminar Carpeta.\n");
			eliminarCarpeta(ruta, sb, ruta1, sb.s.apuntador);
			//bitacora(sb.apuntadorLog, 3, path, " ", sb, ruta); ///****
			journaling(ruta, posicion, sb, 3, path, "", id, 1);
		} else {
			ruta1 = strtok(verificar2, "/");

			//printf("Buscar Archivo.\n");
			datos = buscarArchivo(ruta, sb, ap, ruta1, ajuste, posicion,
					sb.s.apuntador);
			if (datos > 0) {
				char pathAux[200] = "";
				strcpy(pathAux, path);
				ruta1 = strtok(path, "/");
				//retorna un puntero - strstr
				while ((strstr(ruta1, ".") == 0x0 || strstr(ruta1, ".") == ""
						|| strstr(ruta1, ".") == NULL) && ruta1 != NULL
						&& ruta1 != 0x0) {
					ruta1 = strtok(NULL, "/");
					if (ruta1 == NULL) {
						break;
					}
				}
				strcpy(path, pathAux);
				if (ruta1 != NULL) {
					printf("Eliminar Archivo.\n");
					eliminarArchivo(datos, sb, ruta, ruta1);
					//	bitacora(sb.apuntadorJournal, 3, auxPath, " ", sb, ruta);
					journaling(ruta, posicion, sb, 3, path, "", id, 0);
					//printf("o");
				}
			} else {
				printf("ERROR: No existe la ruta indicada.\n");
			}
		}
	} else {
		printf("ERROR: La particion no ha sido formateada.\n");
	}

	return 1;
}

int eliminarCarpeta(char* ruta, superbloque super, char* path, int posicion) {
	FILE* disco;
	disco = fopen(ruta, "rb+");
	apunt ap2, ap;
	fseek(disco, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, disco);

	int i = 0;
	for (i = 0; i < 4; i++) {
		if (ap.subDirectorios[i] > 0) {
			fseek(disco, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, disco);
			if (strcasecmp(ap2.pointer, path) == 0) {
				break;
			}
		}
	}
//	printf("i= %d\n", i);
	if (i < 4) {
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(disco);
			//return 1; //
			eliminarCarpeta(ruta, super, path, ap.subDirectorios[i]);
		} else {
			int c = ap.subDirectorios[i];
			ap.subDirectorios[i] = -1;
			fseek(disco, posicion, SEEK_SET);
			fwrite(&ap, sizeof(apunt), 1, disco);
			int pos = (c - super.s.apuntador) / (100 * sizeof(apunt));

			char ok = '0';
			/*fseek(disco, super.apuntadorBitArbolDirectorio, SEEK_SET);
			 fwrite(&ok, 1, 1, disco);
			 */ //fclose(disco);
			printf("-> Se elimino la carpeta correctamente.\n");
			return eliminarCarpetaCompleta(ruta, super, c);
		}
	} else {
		if (ap.apuntador < 1) {
			printf("ERROR: No existe la carpeta especificada.\n");
			return 0;
		} else {
			fclose(disco);
			return eliminarCarpeta(ruta, super, path, ap.apuntador);
		}

	}
	return 1;
}

int eliminarCarpetaCompleta(char*ruta, superbloque super, int posicion) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap2, ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, archivo);

	int i = 0;

	for (i = 0; i < 6; i++) {
		// int m=ap.subCarpetas[i];

		if (ap.subDirectorios[i] > 0) {
			int c = ap.subDirectorios[i];
			ap.subDirectorios[i] = -1;
			fseek(archivo, posicion, SEEK_SET);
			fwrite(&ap, sizeof(apunt), 1, archivo);
			int pos = (c - super.s.apuntador) / (100 * sizeof(apunt));

			char ok = '0';
			fseek(archivo, super.s.apuntadorBitArbolDirectorio + pos, SEEK_SET);
			fwrite(&ok, 1, 1, archivo);
			fclose(archivo);
			//printf("eliminar com\n");
			eliminarCarpetaCompleta(ruta, super, c);
		}
	}

	if (ap.apuntador > 0) {
		archivo = fopen(ruta, "rb+");
		int c = ap.apuntador;
		ap.apuntador = -1;
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&ap, sizeof(apunt), 1, archivo);
		int pos = (c - super.s.apuntador) / (100 * sizeof(apunt));
		char ok = '0';
		fseek(archivo, super.s.apuntadorBitArbolDirectorio + pos, SEEK_SET);
		fwrite(&ok, 1, 1, archivo);
		fclose(archivo);
		printf("eliminarC\n");
		//eliminarCarpetaCompleta(ruta, super, c);
	}
	if (ap.directorio > 50) {
		archivo = fopen(ruta, "rb+");
		int c = ap.directorio;
		ap.directorio = 0;
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&ap, sizeof(apunt), 1, archivo);
		int pos = (c - super.s.apuntadorDetalleDirectorio)
				/ (100 * sizeof(detalle));
		char yeah = '0';
		fseek(archivo, super.s.apuntadorBitDetalleDirectorio + pos, SEEK_SET);
		fwrite(&yeah, 1, 1, archivo);
		fclose(archivo);
	}
}

int eliminarArchivo(int posicion, superbloque super, char* ruta, char* name) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	int contenidoInodo;
	char* contenidoNombre;

	for (i = 0; i < 5; i++) {
		contenidoInodo = carp.content[i].inodo;
		contenidoNombre = carp.content[i].name;
		if (carp.content[i].inodo > 1) {
			if (strcasecmp(carp.content[i].name, name) == 0) {
				break;
			}
		}
	}
	char v = '0';
	if (i < 5) {
		carp.content[i].inodo = -1;
		strcpy(carp.content[i].name, "");
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&carp, sizeof(detalle), 1, archivo);

		inodo ino;
		fseek(archivo, contenidoInodo, SEEK_SET);
		fread(&ino, sizeof(ino), 1, archivo);

		int cont = ino.noAsignados;
		ino.noAsignados = -1;
		fseek(archivo, super.apuntadorBitTablaInodo + cont, SEEK_SET);
		fwrite(&v, 1, 1, archivo);
		fseek(archivo, contenidoInodo, SEEK_SET);
		fwrite(&ino, sizeof(ino), 1, archivo);

		int j = 0;
		for (j = 0; j < ino.noInodo; j++) {
			//	  int mou=ino.bloque[j];
			//  int cl=super.inicioTablaBloque;
			int pos = (ino.bloques[j] - super.apuntadorBloques)
					/ (100 * sizeof(datos));
			fseek(archivo, super.s.apuntadorBitmapInodo + pos, SEEK_SET);
			fwrite(&v, 1, 1, archivo);
		}
		// int most =conx.indirecto;
		inodo inodo2;
		if (ino.indirecto > 0) {

			fseek(archivo, ino.indirecto, SEEK_SET);
			fread(&inodo2, sizeof(inodo), 1, archivo);
			cont = inodo2.noAsignados;
			inodo2.noAsignados = -1;
			//inodo2.fechaModificado = time(0);
			fseek(archivo, super.apuntadorBitTablaInodo + cont, SEEK_SET);
			fwrite(&v, 1, 1, archivo);

			for (j = 0; j < inodo2.noInodo; j++) {
				int aux = (inodo2.bloques[j] - super.apuntadorBloques)
						/ (100 * sizeof(datos));
				fseek(archivo, super.s.apuntadorBitmapInodo + aux, SEEK_SET);
				fwrite(&v, 1, 1, archivo);
			}
			fseek(archivo, ino.indirecto, SEEK_SET);
			fwrite(&inodo2, sizeof(inodo), 1, archivo);
		}
		fclose(archivo);
		printf("-> Se ha eliminado el archivo correctamente.\n");
		return 1;

	} else {
		if (carp.detalle > 0) {
			fclose(archivo);
			//   int om=carp.d;
			return eliminarArchivo(carp.detalle, super, ruta, name);
		} else {
			fclose(archivo);
			printf("ERROR: No se ha encontrado el archivo.\n");
			return 0;
		}
	}
}

void encontrar() {
	//printf("enc");
	if (id == NULL || path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = encontrarArchivo(id, path, name, "", "");
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int encontrarArchivo(char* id, char* path, char* name, char* perm, char* user) {
	//printf("encont");
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);
	//	printf("t");
	//VERIFICAR LA PARTICION
	i = 0;
	int j = 0;
	int esLogica = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	//printf("r");
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;
	int posicion;
	if (esLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	if (sb.magic == 201404368) {
		fseek(archivo, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);
		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') { //Hasta que llegue al final
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}
		char* ruta1;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		fclose(archivo);

		char aux[10];
		char aux2[10];
		int k = 0;
		for (k = 0; k < 10; k++) {
			aux[k] = '\0';
			aux2[k] = '\0';
		}
		strcpy(aux, name);
		k = 1;
		if (aux[0] == '"') {
			while (aux[k] != '"') {
				aux2[k - 1] = aux[k];
				k++;
			}
		} else {
			strcpy(aux2, aux);
		}
		if (strcasecmp(path, "/") == 0) {
			//printf("raiz\n");
			//return 0;
			buscarRaizCarpeta(ruta, sb, sb.s.apuntador, aux2, 0);
		} else {
			//printf("carp\n");
			buscarCarpeta(ruta, ruta1, sb, sb.s.apuntador, aux2, 0);
		}

	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}

}

char* buscarCarpeta(char* ruta, char* path, superbloque super, int posicion,
		char* mensaje, int espacio) {
//	printf("ruta = %s\n path= %s\n", ruta, path);

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap, ap2;
	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, archivo);

	//char* n=con.name;
	int i = 0;
	int j = 0;

	if (boolLs == 0) {
		for (j = 0; j < espacio; j++) {
			printf(" ");
		}
		printf("|_%s *\n", ap.pointer);
	} else {
		//	strcpy(listaArchivo[contadorArchivo].nombre, ap.name);
//		contadorArchivo++;
	}

	char nombre[50];
	strcpy(nombre, ap.pointer);
	if (nombre[0] == '0' || nombre[15] == '0') {
		return "";
	}

	for (i = 0; i < 6; i++) {
		//int sc=ap.subCarpetas[i];
		if (ap.subDirectorios[i] > 50) {
			fseek(archivo, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, archivo);

			if (strcasecmp(ap2.pointer, path) == 0) {
				break;
			}
		}
	}
	if (i < 6) {
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(archivo);
			return buscarCarpeta(ruta, path, super, ap.subDirectorios[i],
					mensaje, espacio + 2);
		} else {
			int a = ap.subDirectorios[i];
			fclose(archivo);
			return buscarRaizCarpeta(ruta, super, a, mensaje, espacio + 2);
		}
	} else {
		if (ap.apuntador < 1) {
			printf("ERROR: No existe la carpeta indicada.\n");
			return "";
		} else {
			fclose(archivo);
			int p = ap.apuntador;
			return buscarCarpeta(ruta, path, super, p, mensaje, espacio);
		}
	}
	return "";
}

int buscarRaizCarpeta(char* ruta, superbloque super, int posicion,
		char* mensaje, int espacio) {
//	int boolCarpeta = 0;

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap2, ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, archivo);
	//   char* n=ap.puntero;
	//  printf("nombre = %s\n",n);
	int i = 0;
	int j = 0;

	for (j = 0; j < espacio; j++) {
		printf(" ");
	}
	if (boolLs == 0) {
		printf("|_%s . \n", ap.pointer);
	} else {
		if (strcmp(arch, ap.pointer) == 0) {
			bool = 1;
		}
		if (bool == 2) {
			//printf("_%s\n", ap.name);
			strcpy(listaArchivo[contadorArchivo].nombre, ap.pointer);
			contadorArchivo++;
			//bool--;
		}
	}
	fclose(archivo);
	for (i = 0; i < 4; i++) {

		if (ap.subDirectorios[i] > 500) {
			archivo = fopen(ruta, "rb+");
			fseek(archivo, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, archivo);
			fclose(archivo);
			bool++;
			buscarRaizCarpeta(ruta, super, ap.subDirectorios[i], mensaje,
					espacio + 2);
			bool--;
		}
	}
	if (ap.directorio > 100) {
		bool++;
		buscarRaizArchivo(ruta, super, ap.directorio, mensaje, espacio + 2);
		bool--;
	}
	if (ap.apuntador > 100) {
		bool++;
		buscarRaizCarpeta(ruta, super, ap.apuntador, mensaje, espacio);
		bool--;
	}
}

int buscarRaizArchivo(char* ruta, superbloque super, int posicion,
		char* mensaje, int espacio) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle ap2, ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(detalle), 1, archivo);
	int i = 0;
	int x = 0;
	int j = 0;

	fclose(archivo);
	for (i = 0; i < 5; i++) {
		if (ap.content[i].inodo > 50) {
			char aux[10];
			char aux2[16];
			for (j = 0; j < 10; j++) {
				aux[j] = '\0';
			}
			for (j = 0; j < 16; j++) {
				aux2[j] = '\0';
			}
			strcpy(aux2, ap.content[i].name);
			strcpy(aux, mensaje);

			if (aux[0] == '?' && aux[1] == '\0') {
				if (aux2[1] == '\0') {
					for (j = 0; j < espacio; j++) {
						printf(" ");
					}
					printf("|_ %s &\n", ap.content[i].name);
					//printf(ap.archivos[i].name);
					//printf("\n");
				}
			} else if (aux[0] == '*' && aux[1] == '\0') {
				for (j = 0; j < espacio; j++) {
					printf(" ");
				}
				printf("|_%s @\n", ap.content[i].name);
				//printf("\n");
			} else {
				j = 0;
				x = 0;
				while (aux[j] != '\0') {
					if (aux[j] == '?') {
						if (aux[j + 1] == aux2[x + 1]) {
							j++;
							x++;
						} else {
							break;
						}
					} else if (aux[j] == '*') {
						j++;
						while (aux[j] != aux2[x] && '\0' != aux2[x]) {
							x++;
						}
					} else if (aux[j] == aux2[x]) {
						j++;
						x++;
					} else {
						break;
					}
				}
				if (aux[j] == '\0') {
					int h;
					for (h = 0; h < espacio; h++) {
						printf(" ");
					}
					printf("|_%s #\n", ap.content[i].name);
				}
			}
		}
	}
}

void crearDirectorio() {
	if (id == NULL || path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = crearDirectorioArchivo(id, path, p);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int crearDirectorioArchivo(char* id, char* path, char* p) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR LA PARTICION
	i = 0;
	int j = 0;
	int esLogica = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;
	int posicion;
	if (esLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	if (sb.magic == 201404368) {
		fseek(archivo, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100] = "";
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);
		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') { //Hasta que llegue al final
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}
		fflush(NULL);
		char* ruta2;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta2 = strtok(crear, "/");
		} else {
			ruta2 = strtok(verificar, "/");
		}

		int datos;
		correcto = 1;
		if (p == NULL) {
			datos = crearCarpeta(ruta, sb, ap, ruta2, p, ajuste, posicion,
					sb.s.apuntador);
			ruta2 = strtok(crear, "/");
			if (correcto > 0) {
				datos = crearCarpeta(ruta, sb, ap, ruta2, "si", ajuste,
						posicion, sb.s.apuntador);
			}
		} else {
			fflush(NULL);
			ruta2 = strtok(crear, "/");
			datos = crearCarpeta(ruta, sb, ap, ruta2, p, ajuste, posicion,
					sb.s.apuntador);
		}
		//bitacora(sb.jourfirst, 6, path, " ", sb, ruta, id);
		journaling(ruta, posicion, sb, 6, path, "", id, 1);
		return 1;
	} else {
		printf("No ha formateado la particion");
		return 0;
	}
}

void copiar() {
//Error raiz archivo
	if (id == NULL || path == NULL || dest == NULL || iddest == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = copiarArchivo(id, path, dest, iddest);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		} else {
			printf("-> Se ha copiado el archivo correctamente.\n");
		}
	}

}

int copiarArchivo(char* id, char* path, char* dest, char* iddest) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR LA PARTICION
	i = 0;
	int j = 0;
	int esLogica = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb = crearBloque();
	char ajuste;
	int posicion;
	if (esLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	if (sb.magic == 201404368) {
		fseek(archivo, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);
		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') { //Hasta que llegue al final
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}
		char* ruta1;
		char* ruta2;
		char auxPath[100];
		strcpy(auxPath, path);
		a = 0; //nuevas variables
		b = 0;
		for (a = 0; a < 100; a++) {
			if (auxPath[a] == '.') {
				b++;
			}
		}
		fclose(archivo);
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		ruta2 = strtok(crear, ".");

		int datos = 0;
		if (b < 1) {
			ruta1 = strtok(crear, "/");
			//printf("copiar\n");
			copiarCarpeta(ruta, sb, ruta1, sb.s.apuntador, dest, iddest);
			journaling(ruta, posicion, sb, 4, path, "", id, 1);
			//bitacora(sb.s.apuntadorLog, 3, path, " ", sb, ruta); ///****
		} else {
			//printf("buscar\n");
			ruta1 = strtok(verificar2, "/");
			datos = buscarArchivo(ruta, sb, ap, ruta1, posicion, ajuste,
					sb.s.apuntador);
			if (datos > 0) {
				ruta1 = strtok(path, "/");
				//retorna un puntero - strstr
				while ((strstr(ruta1, ".") == 0x0 || strstr(ruta1, ".") == ""
						|| strstr(ruta1, ".") == NULL) && ruta1 != NULL
						&& ruta1 != 0x0) {
					ruta1 = strtok(NULL, "/");
				}
				if (ruta1 != NULL) {
					char mensaje[200];
					int j = 0;
					for (j = 0; j < 200; j++) {
						mensaje[j] = '\0';
					}
					//printf("contenido\n");
					strcpy(mensaje,
							contenidoArchivo(" ", datos, sb, ruta, ruta1));
					FILE* reporte;
					reporte = fopen("/home/aylin/auxContenido.txt", "w+");
					fprintf(reporte, mensaje);
					fclose(reporte);
					char auxRuta[100];
					for (j = 0; j < 100; j++) {
						auxRuta[j] = '\0';
					}
					strcat(auxRuta, dest);
					strcat(auxRuta, "/");
					strcat(auxRuta, ruta1);
					//printf("crear\n");
					crearArchivoParticion(iddest, auxRuta, NULL, NULL,
							"/home/aylin/auxContenido.txt");
				}
			} else {
				printf("ERROR: No existe la ruta indicada.\n");
				return 0;
			}
		}
	} else {
		printf("ERROR: La particion no ha sido formateada.\n");
		return 0;
	}
	return 1;
}

int copiarCarpeta(char* ruta, superbloque super, char* path, int posicion,
		char* dest, char* iddest) {
	FILE* disco;
	disco = fopen(ruta, "rb+");
	apunt ap, ap2;

	fseek(disco, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, disco);
	// char* n=ap.name;
	int i = 0;
	for (i = 0; i < 6; i++) {
		//int n=ap.subdirectorios[i];
		if (ap.subDirectorios[i] > 50) {
			fseek(disco, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, disco);
			//char* m=ap2.puntero;

			if (strcasecmp(ap2.pointer, path) == 0) {
				break;
			}
		}
	}
	if (i < 6) {
		char* copia = path;
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(disco);
			return copiarCarpeta(ruta, super, path, ap.subDirectorios[i], dest,
					iddest);
		} else {
			int sub = ap.subDirectorios[i];
			//printf("else\n");
			printf("-> Se copio la carpeta correctamentee.\n");
			fclose(disco);
			return copiarRaizCarpeta(ruta, super, sub, iddest, dest);
		}
	} else {
		if (ap.apuntador < 1) {
			printf("ERROR: No existe la carpeta.\n");
			return 0;
		} else {
			fclose(disco);
			return copiarCarpeta(ruta, super, path, ap.apuntador, dest, iddest);
		}
	}
}

int copiarRaizCarpeta(char* ruta, superbloque super, int posicion, char* iddest,
		char* dest) {
//	printf("raizCarpeta\n");
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, archivo);

	int i = 0;
	int j = 0;

	char llenar[50];
	for (j = 0; j < 50; j++) {
		llenar[j] = '\0';
	}
	strcpy(llenar, dest);
	strcat(llenar, "/");
	strcat(llenar, ap.pointer);
	fclose(archivo);
	crearCopia(iddest, llenar, NULL);
	printf("holi\n");

	for (i = 0; i < 6; i++) {
		//int n=con.subdirectorios[i];
		if (ap.subDirectorios[i] > 0) {
			int sub = ap.subDirectorios[i];
			copiarRaizCarpeta(ruta, super, sub, iddest, llenar);
		}
	}
	//int lol = ap.apuntadorA;
	//printf("lol = %d = %d\n",ap.apuntadorA, ap.directorio);
	if (ap.apuntador > 0) {
		copiarRaizCarpeta(ruta, super, ap.apuntador, iddest, dest);
	}
	if (ap.directorio > 0) {
		copiarRaizArchivo(ruta, super, ap.directorio, iddest, llenar);
	}
	//printf("casi\n");
	return 1;
}

int crearCopia(char* id, char* path, char* p) {
	//printf("crearCopia\n");
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR LA PARTICION
	i = 0;
	int j = 0;
	int esLogica = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;
	int posicion;
	if (esLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	if (sb.magic == 201404368) {
		fseek(archivo, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);
		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') { //Hasta que llegue al final
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}
		char* ruta1;
		strcpy(verificar2, verificar);
		if (verificar[0] == '\0') {
			p = "si";
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		fclose(archivo);

		int datos;
		correcto = 1;
		if (p == NULL) {
			//		printf("p=NULL\n");
			datos = crearCarpeta(ruta, sb, ap, ruta1, p, ajuste, posicion,
					sb.s.apuntador);
			ruta1 = strtok(crear, "/");
			if (correcto > 0) {
//				printf("correctooooo= %d\n", correcto);

				datos = crearCarpeta(ruta, sb, ap, ruta1, "si", ajuste,
						posicion, sb.s.apuntador);
				//		printf("murio\n");

			}
		} else {
			//	printf("p!=NULL\n");
			ruta1 = strtok(crear, "/");
			datos = crearCarpeta(ruta, sb, ap, ruta1, p, ajuste, posicion,
					sb.s.apuntador);
		}
		//	bitacora(sb.s.apuntadorLog, 6, path, " ", sb, ruta);
		journaling(ruta, posicion, sb, 6, path, "", id, 1);
	} else {
		printf("ERROR: No se ha formateado la particion.");
	}
	return 1;
}

int copiarRaizArchivo(char* ruta, superbloque super, int posicion, char* iddest,
		char* dest) {
	//printf("raizArchivo\n");
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;

	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	int j = 0;

	fclose(archivo);
	for (i = 0; i < 5; i++) {
		//	printf("FOR = %d\n", carp.archivos[i].inodo);
		if (carp.content[i].inodo > 50) {
			char mensaje[200];
			for (j = 0; j < 200; j++) {
				mensaje[j] = '\0';
			}
			//	printf("contenido\n");
			strcpy(mensaje,
					contenidoArchivo(" ", posicion, super, ruta,
							carp.content[i].name));
			FILE* reporte;
			reporte = fopen("/home/aylin/archivoAux.txt", "w+");
			fprintf(reporte, mensaje);
			fclose(reporte);
			char aux[100];
			for (j = 0; j < 100; j++) {
				aux[j] = '\0';
			}
			strcpy(aux, dest);
			strcat(aux, "/");
			strcat(aux, carp.content[i].name);
			char* enviado = aux;
			//printf("crear\n");
			crearArchivoParticion(iddest, enviado, NULL, NULL,
					"/home/aylin/archivoAux.txt");
			//printf("fin crearr\n");
		}
	}
	//printf("carpeta = %d\n", carp.detalle);
	if (carp.detalle > 50) {
		copiarRaizArchivo(ruta, super, carp.detalle, iddest, dest);
	}
	return 1;
}

char* contenidoArchivo(char* contenido, int posicion, superbloque super,
		char* ruta, char* name) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	for (i = 0; i < 5; i++) {
		// char* m =carp.archivos[i].name;
		if (carp.content[i].inodo > 1) {
			if (strcasecmp(carp.content[i].name, name) == 0) {
				break;
			}
		}
	}
	if (i < 5) {
		//se supone que obtiene el contenido
		inodo ino;
		fseek(archivo, carp.content[i].inodo, SEEK_SET);
		fread(&ino, sizeof(inodo), 1, archivo);
		if (ino.size > 100) {
			int i = 0;
			char texto[2000];
			for (i = 0; i < 2000; i++) {
				texto[i] = '\0';
			}
			if (ino.noInodo > 4) {
				ino.noInodo = 4;
			}
			setbuf(stdin, NULL);
			for (i = 0; i < ino.noInodo; i++) {
				datos arch;
				fseek(archivo, ino.bloques[i], SEEK_SET);
				fread(&arch, sizeof(datos), 1, archivo);
				//char *ar=arch.contenido;
				strcat(texto, arch.data);
				contenido = &texto;
			}
			inodo ino2;
			fseek(archivo, ino.indirecto, SEEK_SET);
			fread(&ino2, sizeof(inodo), 1, archivo);
			if (ino2.noInodo > 4) {
				ino2.noInodo = 4;
			}
			for (i = 0; i < ino2.noInodo; i++) {
				datos arch;
				fseek(archivo, ino2.bloques[i], SEEK_SET);
				fread(&arch, sizeof(datos), 1, archivo);
				//char *ar=arch.contenido;
				strcat(texto, arch.data);
				setbuf(stdin, NULL);
				contenido = &texto;
			}
			fclose(archivo);
			return contenido;

		} else {
			char texto[2000];
			int i = 0;
			for (i = 0; i < ino.noInodo; i++) {
				datos arch;
				fseek(archivo, ino.bloques[i], SEEK_SET);
				fread(&arch, sizeof(datos), 1, archivo);
				//   char *ar=arch.contenido;
				strcat(texto, arch.data);
				setbuf(stdin, NULL);
				contenido = &texto;
				if (i > 3) {
					break;
				}
			}
			fclose(archivo);
			return contenido;
		}
	} else {
		if (carp.detalle > 0) {
			fclose(archivo);
			setbuf(stdin, NULL);
			return contenidoArchivo(contenido, carp.detalle, super, ruta, name);
		} else {
			printf("ERROR: El archivo no existe.\n");
			return "";
		}
	}
}

void mostrarContenido() {
	int cont = 0;
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (file1 != NULL) {
			int d = mostrarContenidoArchivo(id, file1);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
			cont++;
		}
		if (file2 != NULL) {
			int d = mostrarContenidoArchivo(id, file2);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
			cont++;
		}
		if (file3 != NULL) {
			int d = mostrarContenidoArchivo(id, file3);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
			cont++;
		}
		if (cont == 0) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		}
	}
}

int mostrarContenidoArchivo(char* id, char* filen) {
//	printf("filen= %s\n",filen);
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICAR LA PARTICION
	i = 0;
	int j = 0;
	int esLogica = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;
	int posicion;
	if (esLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	if (sb.magic == 201404368) {
		fseek(archivo, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, filen);
		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') { //Hasta que llegue al final
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}
		char* ruta2;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta2 = strtok(crear, "/");
		} else {
			ruta2 = strtok(verificar, "/");
		}
		fclose(archivo);
		int datos;
		ruta2 = strtok(verificar2, "/");
		//	printf("buscarArchivo\n");
		//	printf("ruta::%s, ruta2::%s\n",ruta,ruta2);
		datos = buscarArchivo(ruta, sb, ap, ruta2, ajuste, posicion,
				sb.s.apuntador);

		if (datos > 0) {
			ruta2 = strtok(crear, "/");
			while ((strstr(ruta2, ".") == 0x0 || strstr(ruta2, ".") == ""
					|| strstr(ruta2, ".") == NULL) && ruta2 != NULL) {
				ruta2 = strtok(NULL, "/");
			}
			if (ruta2 != NULL) {
				char mensaje[2000] = "";
				//		printf("contenidoArchivo.\n");
				strcpy(mensaje, contenidoArchivo(" ", datos, sb, ruta, ruta2));
				printf("* * * * * * * * * * * * * * * * * * * * * *\n%s\n",
						mensaje);

				//	bitacora(sb.apuntadorJournal, 2, filen, "", sb, ruta);
//				journaling(ruta, posicion, sb, 2, path, "", id, 0);
			}
		} else {
			printf("ERROR: La ruta no existe.\n");
		}
	} else {
		printf("ERROR: La particion no esta formateada.\n");
	}
	return 1;
}

void mover() {
	if (id == NULL || path == NULL || dest == NULL || iddest == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		boolEditar = 1;
		int d = moverArchivo(id, path, dest, iddest);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int moverArchivo(char* id, char* path, char* dest, char* iddest) {
	printf("-> Copiar\n");
	char pathAux[200] = "";
	strcpy(pathAux, path);
	int a = copiarArchivo(id, path, dest, iddest);
	printf("-> Eliminar\n");
	strcpy(path, pathAux);
	int b = removerArchivo(id, path, 0);
	strcpy(path, pathAux);
	if (a == 1 && b == 1) {
		return 1;
	} else {
		return 0;
	}
}

void listar() {
	//printf("enc");
	if (id == NULL || path == NULL || order == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		contadorArchivo = 0;
		char *comando = NULL;
		comando = strtok(path, "/");
		while (comando != NULL) {
			arch = comando;
			comando = strtok(NULL, "/");
		}
		boolLs = 1;
		//printf("File=%s\n P = %s\n", arch, path);
		int d = encontrarArchivo(id, path, "*", "", "");
		boolLs = 0;
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			return;
		}
		printf("\n");
		imprimirLista();
	}
}

void imprimirLista() {
	int i = 0;

	if (strcasecmp(order, "f") == 0 || strcasecmp(order, "f\r") == 0) {
		for (i = 0; i < contadorArchivo; i++) {
			printf(" ->  %s\n", listaArchivo[i].nombre);
		}
	} else if (strcasecmp(order, "c") == 0 || strcasecmp(order, "c\r") == 0) {
		time_t tiempo = time(0);
		struct tm *tlocal = localtime(&tiempo);
		char output[128];
		strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);

		for (i = 0; i < contadorArchivo; i++) {
			printf(" ->  %s		%s\n", listaArchivo[i].nombre, output);
		}
	} else if (strcasecmp(order, "r") == 0 || strcasecmp(order, "r\r") == 0) { //extendida
		char *nombres[15];
		char nombre[25];
		char *letra;
		int i, j = 0;

		for (i = 0; i < contadorArchivo; i++) {
			strcpy(nombre, listaArchivo[i].nombre);
			nombres[i] = strdup(nombre);
		}
		for (i = 0; i < contadorArchivo; i++) //Ciclo q realiza el proceso de ordenamiento, recorre el apuntador la cadena para ordenar
			for (j = contadorArchivo - 1; j > 0; j--)
				if (strcmp(nombres[j], nombres[j - 1]) < 0) {
					letra = nombres[j];
					nombres[j] = nombres[j - 1];
					nombres[j - 1] = letra;

				}
		for (i = 0; i < contadorArchivo; i++) { //ciclo q muestra los nombres ya ordenados
			printf(" ->  %s\n", nombres[i]);
		}
	} else {
		printf("ERROR: Tipo de orden incorrecto.%s*\n", order);
		return;
	}
	//printf("\ncontador = %d\n", contadorArchivo);

}

void generarReporte() {

	if (path == NULL || name == NULL || id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (strcasecmp(name, "mbr") == 0 || strcasecmp(name, "mbr\n") == 0) {
			//printf("entro");
			int d = reporteMBR(id, name, path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "disk") == 0
				|| strcasecmp(name, "disk\n") == 0) {
			int d = reporteDISK(id, name, path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "inode") == 0
				|| strcasecmp(name, "inode\n") == 0) {
			int d = reporteINODO(id, "*", path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "block") == 0
				|| strcasecmp(name, "block\n") == 0) {
			int d = reporteBLOQUE(id, "*", path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}

		} else if (strcasecmp(name, "journaling") == 0
				|| strcasecmp(name, "journaling\n") == 0) {
			int d = reporteJOURNALING(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "bm_inode") == 0
				|| strcasecmp(name, "bm_inode\n") == 0) {
			int d = reporteBITMAP_INODO(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "bm_block") == 0
				|| strcasecmp(name, "Bm_block\n") == 0) {
			int d = reporteBITMAP_BLOQUE(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}/*
			 } else if (strcasecmp(name, "tree") == 0
			 || strcasecmp(name, "tree\n") == 0) {
			 int d = reporteTREE(name, path, id);
			 if (d == 0) {
			 printf(
			 "Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			 }*/
		} else if (strcasecmp(name, "sb") == 0
				|| strcasecmp(name, "sb\n") == 0) {
			int d = reporteSB(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "file") == 0
				|| strcasecmp(name, "file\n") == 0) {
			//printf("HOLIWI = %s\n",ruta);
			if (ruta != NULL) {
				int d = reporteFILE(name, path, id, ruta);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}

			} else {
				printf("Falta el atributo ruta.\n");
			}
		} else if (strcasecmp(name, "tree") == 0
				|| strcasecmp(name, "tree\n") == 0) {
			int d = reporteArbol(id, "*", path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else {
			printf("ERROR: nombre incorrecto = %s\n", name);
			//printf("x\n");
		}
	}
}

superbloque crearBloque() {
	superbloque sb;
	sb.inodosCount = 0;
	sb.bloquesCount = 0;
	sb.freeBloquesCount = 0;
	sb.freeInodosCount = 0;
	sb.mountCount = 0;
	sb.magic = 0;
	sb.inodoSize = 0;
	sb.bloqueSize = 0;
	sb.apuntadorBitTablaInodo = 0;
	sb.apuntadorTablaInodo = 0;
	sb.firstFreeBitTablaInodo = 0;
	sb.firstFreeBitBloque = 0;

	return sb;
}

int bitacora(int posicion, int operacion, char* nombre, char* contenido,
		superbloque super, char* ruta, char* vdID) {
	printf("Bitacora = (%d, %d, %s, %s, %s , ->%s<- )\n", posicion, operacion,
			nombre, contenido, ruta, vdID);

	FILE* disco;
	disco = fopen(ruta, "rb+");
	journal bitacora;
	fseek(disco, posicion, SEEK_SET);
	fread(&bitacora, sizeof(journal), 1, disco);

	journal aux = bitacora;

	int a = 1;
	int b = posicion;
	int tipo = bitacora.tipo;
	//printf("1");
//	printf("tipo = %d\n",bitacora.tipo);
	while (bitacora.tipo > 0) { //Si es carpeta
		//for(i=0;i<15;i++){
		//	printf("tipo = %d\n",bitacora.tipo);
		b = bitacora.tipo;
		fseek(disco, bitacora.tipo, SEEK_SET);
		fread(&bitacora, sizeof(journal), 1, disco);
		a++;
		if (a == 10000) {
			printf("Limite\n");
			bitacora = aux;
			break;
		}
	}

	if (a != 10000) {
		printf("Menor\n");
		//printf("* * * * * * *\n");
		bitacora.tipo = super.jourfirst + 100 * a * sizeof(journal);
		fseek(disco, b, SEEK_SET);
		fwrite(&bitacora, sizeof(journal), 1, disco);
		//printf("3");
		journal bita;
		bita.operacion = operacion;
		strcpy(bita.vdID, vdID);
		strcpy(bita.nombre, nombre);
		strcpy(bita.contenido, contenido);
		//printf("4\n");
		bita.fecha = time(0);
		bita.tipo = 0;
		fseek(disco, bitacora.tipo, SEEK_SET);
		fwrite(&bita, sizeof(journal), 1, disco);
	} else {
		fseek(disco, tipo, SEEK_SET);
		printf("Mayor\n");
	}
	fclose(disco);
	return 1;
}

void journaling(char *ruta, int posicion, superbloque sb, int ope, char *path,
		char *contenido, char *id, int tipo) {
	printf("Posicion = %d - Path = %s - ", posicion, path);
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return;
		}
	}
	if (strlen(contenido) == 0) {
		char pathAux[100];
		strcpy(pathAux, path);
		fseek(archivo, posicion, SEEK_SET);
		printf("Contador = %d\n", sb.s.contadorJ);
		sb.j[sb.s.contadorJ].bitacora.tipo = tipo; //0 archivo, 1 D
		sb.j[sb.s.contadorJ].bitacora.operacion = ope;
		sb.j[sb.s.contadorJ].bitacora.fecha = time(0);
		strcpy(sb.j[sb.s.contadorJ].bitacora.vdID, id);
		strcpy(sb.j[sb.s.contadorJ].bitacora.path, path);
		strcpy(sb.j[sb.s.contadorJ].bitacora.nombre, obtenerNombre(path));
		strcpy(path, pathAux);
		strcpy(sb.j[sb.s.contadorJ].bitacora.padre, obtenerPadre(path));
		strcpy(path, pathAux);
		strcpy(sb.j[sb.s.contadorJ].bitacora.contenido, "");
		sb.s.contadorJ++;
		fwrite(&sb, sizeof(superbloque), 1, archivo);
	} else {
		//printf("Tamanio = %d\n",strlen(contenido));
		char content[strlen(contenido)];
		strcpy(content, contenido);
		char datos[64] = "";
		int i, j = 0;
		for (i = 0; i < strlen(contenido); i++) {
			//char content[64]
			for (j = 0; j < 64; j++) {
				//	if()
				datos[j] = content[i];
				i++;
				if (i == strlen(contenido)) {
					break;
				}
			}
			//i = i + 64;
			char pathAux[100];
			strcpy(pathAux, path);

			fseek(archivo, posicion, SEEK_SET);
			printf("Contador = %d\n", sb.s.contadorJ);
			sb.j[sb.s.contadorJ].bitacora.tipo = tipo; //0 archivo, 1 D
			sb.j[sb.s.contadorJ].bitacora.operacion = ope;
			sb.j[sb.s.contadorJ].bitacora.fecha = time(0);
			sb.j[sb.s.contadorJ].bitacora.tamanio = j;
			strcpy(sb.j[sb.s.contadorJ].bitacora.vdID, id);
			strcpy(sb.j[sb.s.contadorJ].bitacora.path, path);
			strcpy(sb.j[sb.s.contadorJ].bitacora.nombre, obtenerNombre(path));
			strcpy(path, pathAux);
			strcpy(sb.j[sb.s.contadorJ].bitacora.padre, obtenerPadre(path));
			strcpy(path, pathAux);
			strcpy(sb.j[sb.s.contadorJ].bitacora.contenido, datos);

			sb.s.contadorJ++;
			fwrite(&sb, sizeof(superbloque), 1, archivo);
		}
	}

	fclose(archivo);
}

void actualizar() {

	if (id != NULL) {
		//	printf("Actualizar %s\n", id);
		char *ruta1 = obtenerRuta(id);
		if (ruta1 != NULL) {
			char rutaAux[200];
			strcpy(rutaAux, ruta1);
			char *nombre = generarPath(ruta1);
			copiarFichero(rutaAux, nombre);
			strcpy(ruta1, rutaAux);
		}
	}
}

void loss() {
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int i = 0;
		for (i = 0; i < 31; i++) {
			if (montar[i].vdID != NULL) {
				//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
				if (strcasecmp(montar[i].vdID, id) == 0) {
					if (montar[i].estado == 1) {
						montar[i].loss = 1;
						break;
					}
				}
			}
		}
		if (i == 31) {
			printf("ERROR: El ID no existe.\n");
			return;
		}
	}
}

void recovery() {
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		char* ruta;
		char* nombre;
		int i = 0;
		for (i = 0; i < 31; i++) {
			if (montar[i].vdID != NULL) {
				//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
				if (strcasecmp(montar[i].vdID, id) == 0) {
					if (montar[i].estado == 1) {
						montar[i].loss = 0;
						ruta = montar[i].path; //%%%
						nombre = montar[i].name;
						break;
					}
				}
			}
		}
		if (i == 31) {
			printf("ERROR: El ID no existe.\n");
			return;
		}

		FILE* archivo;
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			ruta = generarPath(ruta);
			archivo = fopen(ruta, "rb+");
			if (archivo == NULL) {
				printf("ERROR: No existe el disco.\n");
				return;
			}
		}
		mbr structDisco;
		fseek(archivo, 0, SEEK_SET);
		fread(&structDisco, sizeof(mbr), 1, archivo);

		//VERIFICAR LA PARTICION
		i = 0;
		int j = 0;
		int esLogica = 0;
		for (i = 0; i < 4; i++) {
			if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
				break;
			}
			for (j = 0; j < 20; j++) {
				if (strcasecmp(structDisco.part[i].exten[j].name, nombre)
						== 0) {
					esLogica = 1;
					break;
				}
				if (esLogica == 1) {
					break;
				}
			}
		}
		if (i == 4 && esLogica == 0) {
			printf("ERROR: No existe el nombre indicado.\n");
			return;
		}
		superbloque sb;
		if (esLogica == 1) {
			fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
			fread(&sb, sizeof(superbloque), 1, archivo);
		} else {
			fseek(archivo, structDisco.part[i].start, SEEK_SET);
			fread(&sb, sizeof(superbloque), 1, archivo);
		}

		fclose(archivo);
		char rutaAux[100];
		strcpy(rutaAux, ruta);
		char *nameR = obtenerNombre(ruta);
		strcpy(ruta, rutaAux);
		char *recovery = concatenar(
				"/home/aylin/workspaceNeon/ProyectoArchivos/recovery/recovery",
				nameR);
		copiarFichero(ruta, recovery);
		formatearDisco(id, "full", "", "k", "");

		for (i = 0; i < sb.s.contadorJ; i++) {
			journal bitacora = sb.j[i].bitacora;

			if (bitacora.operacion == 1) {
				crearArchivo();
			} else if (bitacora.operacion == 2) { // mkfile
				crearArchivoParticion(bitacora.vdID, bitacora.nombre, "p", 0,
						bitacora.contenido);
			} else if (bitacora.operacion == 3) { //rm
				removerArchivo(bitacora.vdID, bitacora.nombre, 0);
			} else if (bitacora.operacion == 4) { //cp
				//copiarArchivo(bitacora.vdID,bitacora.nombre)
			} else if (bitacora.operacion == 5) { //mv
				//moverArchivo(bitacora.vdID,bitacora.nombre,"","")''
			} else if (bitacora.operacion == 6) { // mkdir
				char p[100] = "";
				strcpy(p, bitacora.path);
				crearDirectorioArchivo(bitacora.vdID, p, "p");
			} else {
				//strcpy(operacion, "formatear");
			}
		}

	}

}

void copiarFichero(char *origen, char *destino) {
	FILE *arch1 = NULL;
	FILE *arch2 = NULL;
	arch1 = fopen(origen, "r");
	arch2 = fopen(destino, "r");
	if (arch1 != NULL && arch2 != NULL) {

		char *cadena = concatenar("cp ", origen);
		cadena = concatenar(cadena, " ");
		cadena = concatenar(cadena, destino);
		//printf(cadena);
		system(cadena);

		fclose(arch1);
		fclose(arch2);
	}
}

char *obtenerPadre(char *ruta) {
	char* datos[10];
	int cont = 0;

	char* inst = NULL;
	inst = strtok(ruta, "/");
	datos[cont] = inst;

	while (inst != NULL) {
		cont++;
		inst = strtok(NULL, "/");
		datos[cont] = inst;
	}
	return datos[cont - 2];
}

void load() {
	if (id == NULL || path == NULL || type == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = loadData(id, path, type);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int loadData(char* id, char* path, char* type) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}
	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;
	int posicion;

	if (existeLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	if (sb.magic == 201404368) {

		if (strcasecmp(type, "usr") == 0) {

			//OBTENER ARCHIVO
			FILE* archivoCargar;
			char caracter[1000];
			archivoCargar = fopen(path, "r+");
			if (archivoCargar == NULL) {
				printf("ERROR: No existe el archivo a cargar.\n");
				return 0;
			} else {
				int j = 0;
				for (j = 0; j < 1000; j++) {
					caracter[j] = '\0';
				}
				int i = 0;
				fseek(archivo, posicion, SEEK_SET);

				while (feof(archivoCargar) == 0) { // *feof* hasta que se acabe el archivo
					caracter[i] = fgetc(archivoCargar); // *fgetc* lee lineapor linea
					printf(&caracter[i]);

					if (caracter[i] == '\n') {
						//printf("\n\n");
						char com[1000];
						char com2[1000];
						caracter[i] = '\0';
						strcpy(com, caracter);
						strcpy(com2, com);
						char *comando = NULL;
						int contador = 1;
						comando = strtok(com, ",");
						//printf("%s\n", comando);
						strcpy(sb.user[sb.s.contadorU].usuario.id, comando);

						while (comando != NULL) {
							//strcpy(sb.user[sb.s.contadorU].usuario.id, comando);
							comando = strtok(NULL, ",");
							if (comando != NULL) {
								//printf("%s\n", comando);
								switch (contador) {
								case 0:
									break;
								case 1:
									strcpy(sb.user[sb.s.contadorU].usuario.tipo,
											comando);
									break;
								case 2:
									strcpy(
											sb.user[sb.s.contadorU].usuario.grupo,
											comando);
									break;
								case 3:
									strcpy(
											sb.user[sb.s.contadorU].usuario.usuario,
											comando);
									break;
								case 4:
									strcpy(
											sb.user[sb.s.contadorU].usuario.clave,
											comando);
									break;
								}
							}
							contador++;
						}
						sb.s.contadorU++;

						for (j = 0; j < 1000; j++) {
							caracter[j] = '\0';
						}
						printf("\n");
						i = 0;
					} else if (caracter[i] == '\\') {
						caracter[i] = ' ';
					} else {
						i++;
					}
				}
				fwrite(&sb, sizeof(superbloque), 1, archivo);
			}

			fclose(archivo);
			fclose(archivoCargar);
			printf("-> Se han cargado los USUARIOS correctamente.\n");
			return 1;

		} else if (strcasecmp(type, "perm") == 0) {
			boolEditar = 1;
			crearArchivoParticion(id, "/home/permisos.txt", "si", "10",
					"/home/aylin/vacio.txt");
			////
			FILE* archivoCargar;
			char caracter[1000];
			archivoCargar = fopen(path, "r+");
			if (archivoCargar == NULL) {
				printf("ERROR: No existe el archivo a cargar.\n");
				return 0;
			} else {
				int j = 0;
				for (j = 0; j < 1000; j++) {
					caracter[j] = '\0';
				}
				int i = 0;
				fseek(archivo, posicion, SEEK_SET);

				while (feof(archivoCargar) == 0) { // *feof* hasta que se acabe el archivo
					caracter[i] = fgetc(archivoCargar); // *fgetc* lee lineapor linea
					printf(&caracter[i]);

					if (caracter[i] == '\n') {
						//printf("\n\n");
						char com[1000];
						char com2[1000];
						caracter[i] = '\0';
						strcpy(com, caracter);
						strcpy(com2, com);
						char *comando = NULL;
						int contador = 1;
						comando = strtok(com, ",");
						//printf("%s\n", comando);
						strcpy(sb.perm[sb.s.contadorP].permiso.usuario,
								comando);
						while (comando != NULL) {

							comando = strtok(NULL, ",");
							if (comando != NULL) {
								//printf("%s\n", comando);
								switch (contador) {
								case 1:
									strcpy(sb.perm[sb.s.contadorP].permiso.ruta,
											comando);
									break;
								case 2:
									strcpy(
											sb.perm[sb.s.contadorP].permiso.permiso,
											comando);
									break;
								}
							}
							contador++;
						}
						sb.s.contadorP++;

						for (j = 0; j < 1000; j++) {
							caracter[j] = '\0';
						}
						printf("\n");
						i = 0;
					} else if (caracter[i] == '\\') {
						caracter[i] = ' ';
					} else {
						i++;
					}
				}
				fwrite(&sb, sizeof(superbloque), 1, archivo);
			}

			fclose(archivo);
			fclose(archivoCargar);

			printf("-> Se han cargado los PERMISOS correctamente.\n");
			return 1;
		} else {
			printf("ERROR: Tipo no existe.\n");
			return 0;
		}
	} else {
		printf("ERROR: La particion no ha sido formateada.\n");
	}

	return 1;
}

void syncron() {
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = syncronice(id);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int syncronice(char* id) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					if (montar[i].loss == 1) {
						printf("ERROR: Existe un fallo en el disco.\n");
						return 0;
					}
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		ruta = generarPath(ruta);
		archivo = fopen(ruta, "rb+");
		if (archivo == NULL) {
			printf("ERROR: No existe el disco.\n");
			return 0;
		}
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}
	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;
	int posicion;

	if (existeLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	if (sb.magic == 201404368) {

		//USUARIOS

		FILE *archivoUsuario;
		archivoUsuario = fopen(
				"/home/aylin/workspaceNeon/ProyectoArchivos/Usuarios.txt",
				"w+");

		int i, j, c = 0;
		for (i = 0; i < sb.s.contadorU; i++) {

			if (strcasecmp(sb.user[i].usuario.tipo, "U") == 0) {

				fprintf(archivoUsuario, sb.user[i].usuario.id);
				c = 5 - strlen(sb.user[i].usuario.id);
				for (j = 0; j < c; j++) {
					fprintf(archivoUsuario, " ");
				}
				fprintf(archivoUsuario, sb.user[i].usuario.grupo);
				c = 20 - strlen(sb.user[i].usuario.grupo);
				for (j = 0; j < c; j++) {
					fprintf(archivoUsuario, " ");
				}
				fprintf(archivoUsuario, sb.user[i].usuario.usuario);
				c = 20 - strlen(sb.user[i].usuario.usuario);
				for (j = 0; j < c; j++) {
					fprintf(archivoUsuario, " ");
				}
				fprintf(archivoUsuario, sb.user[i].usuario.clave);
				c = 20 - strlen(sb.user[i].usuario.clave);
				for (j = 0; j < c; j++) {
					fprintf(archivoUsuario, " ");
				}
				fprintf(archivoUsuario, "\n");
			}
		}

		fclose(archivoUsuario);

		//PERMISOS

		FILE *archivoPermiso;
		archivoPermiso = fopen(
				"/home/aylin/workspaceNeon/ProyectoArchivos/Permisos.txt",
				"w+");

		for (i = 0; i < sb.s.contadorP; i++) {

			fprintf(archivoPermiso, sb.perm[i].permiso.usuario);
			c = 20 - strlen(sb.perm[i].permiso.usuario);
			for (j = 0; j < c; j++) {
				fprintf(archivoPermiso, " ");
			}
			fprintf(archivoPermiso, sb.perm[i].permiso.ruta);
			c = 20 - strlen(sb.perm[i].permiso.ruta);
			for (j = 0; j < c; j++) {
				fprintf(archivoPermiso, " ");
			}
			fprintf(archivoPermiso, sb.perm[i].permiso.permiso);
			c = 5 - strlen(sb.perm[i].permiso.permiso);
			for (j = 0; j < c; j++) {
				fprintf(archivoPermiso, " ");
			}

			fprintf(archivoPermiso, "\n");

		}

		fclose(archivoPermiso);

	} else {
		printf("ERROR: La particion no ha sido formateada.\n");
	}

	return 1;
}
