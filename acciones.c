/*
 * acciones.c
 *
 *  Created on: 6/06/2017
 *      Author: tanya
 */

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "acciones.h"
#include "estructuras.h"
#include <setjmp.h>
#include <math.h>

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
char* usuario = NULL;
char* password = NULL;
char* grupo = NULL;
char* p = NULL;
char* cont = NULL;
char* ugo = NULL;
char* R = NULL;
int boolR = 0;
char* filen = NULL;
int rf = 0;
char* dest = NULL;
char* iddest = NULL;
char* perm = NULL;
char* user = NULL;
char* file1 = NULL;
char* file2 = NULL;
char* file3 = NULL;
char* allocation;
int contadorM = 0;
int boolExec = 0;
int boolLogin = 0;
char* usrLogin = NULL;
int correcto = 1;
int boolEditar = 0;
int contadorUsuario = 0;
int contadorGrupo = 0;
char* contenidoUsers = NULL;

void limpiarVariables() {
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
	usuario = NULL;
	password = NULL;
	grupo = NULL;
	p = NULL;
	cont = NULL;
	ugo = NULL;
	boolR = 0;
	rf = 0;
	dest = NULL;
	iddest = NULL;
	perm = NULL;
	user = NULL;
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
				|| strcasecmp(token1, "@path") == 0) {
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
		} else if (strcasecmp(token1, "@type") == 0) {
			token1 = strtok(NULL, ">");
			type = token1;
		} else if (strcasecmp(token1, "@fit") == 0) {
			token1 = strtok(NULL, ">");
			fit = token1;
		} else if (strcasecmp(token1, "@delete") == 0) {
			token1 = strtok(NULL, ">");
			dele = token1;
		} else if (strcasecmp(token1, "@nombre") == 0
				|| strcasecmp(token1, "$nombre") == 0) {
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
			//   printf("tok1 = %s\n",token1);
			strcpy(token1, nombre);
			name = token1;
		} else if (strcasecmp(token1, "@add") == 0) {
			token1 = strtok(NULL, ">");
			add = token1;
		} else if (strcasecmp(token1, "$id") == 0
				|| strcasecmp(token1, "@id") == 0) {
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
		} else if (strcasecmp(token1, "@perm") == 0) {
			token1 = strtok(NULL, ">");
			perm = token1;
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

		} else if (strcasecmp(token1, "@allocation") == 0) {
			token1 = strtok(NULL, ">");
			allocation = token1;
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

}

void crearDisco() {
	boolCrearDisco = 1;
	if (size == NULL || path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (size > 0) {
			int d = crearArchivoBinario(size, path, name);
			if (d == 0) {
				printf(
						"-> Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
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
		char* nameCopy = (char*) malloc(sizeof(char*));
		char* pathCopy = (char*) malloc(sizeof(char*));
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
			printf("ERROR: Al crear archivo.\n");
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

		strcpy(nameCopy, "Copy");
		strcat(nameCopy, name);
		strcat(pathCopy, nameCopy);
		/*printf("name = %s\n", name);
		 printf("nameCopy = %s\n", nameCopy);
		 printf("path = %s\n", path);
		 printf("pathCopy = %s\n", pathCopy);
		 */
		copy_file(path, pathCopy);

		return 1;
	}
	return 1;
}

int copy_file(char* pathOrigen, char* pathDestino) {
	FILE *origen, *destino;
	char c;

	if (!(origen = fopen(pathOrigen, "rt"))
			|| !(destino = fopen(pathDestino, "wt"))) {
		printf("ERROR: Apertura de ficheros\n");

	} else {
		while ((c = fgetc(origen)) != EOF && !ferror(origen) && !ferror(destino))
			fputc(c, destino);

		if (ferror(origen) || ferror(origen))
			return 1;

		fclose(origen);
		fclose(destino);
	}
	return 0;
}

int multiploDeOcho(int tam) {
	int i = 0;
	for (i = 8; i < 105; i = i + 8) {
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
}

int crearParticion(char* path, char* name, char* size, char* unit, char* type,
		char* fit) {
	int tam = atoi(size);
	int libre = 0;

	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
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
		if (tam < 2097152) { //2 *1024 *1024
			printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
			return 0;
		} else {
			bytes = tam;
		}

	} else if (strcasecmp(unit, "k") == 0 || strcasecmp(unit, "k\n") == 0
			|| strcasecmp(unit, "k\r") == 0) { //byte -> 8bits
		if (tam < 2048) { //2 * 1024
			printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
			return 0;
		} else {
			bytes = tam * 1024;
		}
	} else if (strcasecmp(unit, "m") == 0 || strcasecmp(unit, "m\n") == 0
			|| strcasecmp(unit, "m\r") == 0) { //megabyte -> 1024 Kb
		if (tam < 2) {
			printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
			return 0;
		} else {
			bytes = tam * 1024 * 1024;
		}
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
							j = 0;
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
		printf("ERROR: No existe el disco.\n");
		return 0;
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
	if (esLogica > 0) {
		if (bytes > 0) {
			if (j < 20) { //j depende de donde encontro el nombre
				printf("j = %d\n", j);
				if (structDisco.part[i].exten[j + 1].start != 0) { //Si no es la primer particion
					int siguiente = structDisco.part[i].exten[j].start
							+ structDisco.part[i].exten[j].auxiliar;
					int anterior = structDisco.part[i].exten[j + 1].start;

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

				} else { //Si es la primer particion

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
			} else { //Si es la primera particion
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
		} else { //Si los bytes son 0
			if (j < 20) {
				if (structDisco.part[i].exten[j + 1].start != 0) { //Si no es la primer particion
					int resta = structDisco.part[i].exten[j].auxiliar + bytes;
					if (resta > 0) {
						structDisco.part[i].exten[j].auxiliar = resta;
					} else {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
				} else { //Si es la primer particion
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
			if (i < 3) {
				if (structDisco.part[i + 1].start != 0) {
					int siguiente = structDisco.part[i].auxiliar
							+ structDisco.part[i].start;
					int anterior = structDisco.part[i + 1].start;
					int resta = anterior - siguiente;
					if (resta < bytes) {
						printf("No hay espacio disponible.\n");
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
						printf("No hay espacio disponible.\n");
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
			} else {
				int k = 0;
				int suma = 0;
				for (k = 0; k < 4; k++) {
					suma = suma + structDisco.part[k].size;
				}
				int resta = structDisco.size - suma;
				if (resta < bytes) {
					printf("No hay espacio disponible.\n");
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
		} else {
			if (i < 3) {
				if (structDisco.part[i + 1].start != 0) {
					int resta = bytes + structDisco.part[i].auxiliar;
					int k = 0;
					int sumadora = 0;
					for (k = 0; k < 8; k++) {
						if (structDisco.part[i].exten[k].size > 0) {
							sumadora = sumadora
									+ structDisco.part[i].exten[k].size;
						}
					}
					if (resta > sumadora) {
						structDisco.part[i].auxiliar = resta;
					} else {
						printf("No hay espacio para borrar ");
						return 0;
					}
				} else {
					int resta = bytes + structDisco.part[i].auxiliar;
					int k = 0;
					int sumadora = 0;
					for (k = 0; k < 8; k++) {
						sumadora = sumadora + structDisco.part[i].exten[k].size;
					}
					if (resta > sumadora) {
						structDisco.part[i].auxiliar = resta;
						structDisco.part[i].size = resta;
					} else {
						printf("No hay espacio para disponible.\n");
						return 0;
					}
				}
			} else {
				int resta = bytes + structDisco.part[i].auxiliar;
				int k = 0;
				int sumadora = 0;
				for (k = 0; k < 8; k++) {
					sumadora = sumadora + structDisco.part[i].exten[k].size;
				}
				if (resta > sumadora) {
					structDisco.part[i].auxiliar = resta;
					structDisco.part[i].size = resta;
				} else {
					printf("No hay espacio disponible.\n");
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
		printf("ERROR: No existe el disco.\n");
		return 0;
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
		printf("ERROR: Falta un atributo obligatorio.\n");
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
		printf("ERROR: No existe el disco\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICA SI EL NOMBRE DE LA PARTICION EXISTE
	int boolExten = 0;
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

				boolExten = 1;
				break;
			}
			if (boolExten == 1) {
				break;
			}
		}
	}
	if (i == 4 && boolExten == 0) {
		printf("ERROR: No existe el nombre de la particion.\n");
		fclose(archivo);
		return 0;
	}
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
		} else {
			setbuf(stdin, NULL);
			fflush(NULL);
			//crearArchivoParticion(id, "/home/users.txt", "si", "16384", NULL);
			//		boolEditar=1;
			fflush(NULL);
			//	crearGrupoDisco(id,"root");
			//crearUsuarioDisco(id,"root","201404368","root");
			//crearArchivoParticion(id, "/home/users.txt", "si", "16384", "/home/aylin/users.txt");
			//"/home/aylin/usuarios.txt"
		}

	}
}

int formatearDisco(char* id, char* type, char* add, char* unit, char* fs) {
	//CREAR USUARIO

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
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		//printf("COMPARAR Mkfs:: %s - %s\n", structDisco.part[i].name, nombre);
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
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
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	//printf("N1:: %s\n",structDisco.part[i].name);

	superbloque sb; // = crearBloque();
	int pos = 0;
	int n = 0;
	int tam = 0;
	if (existeLogica == 1) { //Si la particion es logica
		n = structDisco.part[i].exten[j].auxiliar - sizeof(superbloque);
		int m = (1 + sizeof(journal) + 3 + sizeof(inodo) + 3 * sizeof(datos));
		int nn = n / m;
	//	tam = floor(nn);

		printf("tam1== %d\n", tam);
		pos = tam;
		//sb.nombre = name;
		sb.inodosCount = tam;
		sb.bloquesCount = tam * 3;
		sb.freeBloquesCount = tam - 1;
		sb.freeInodosCount = (tam * 3) - 10;
		sb.mountCount = 0;
		sb.magic = 201404368;  //0xEF53
		sb.inodoSize = sizeof(inodo);
		sb.bloqueSize = sizeof(datos);
		//sb.apuntadorBitTablaInodo = sb.apuntadorDetalleDirectorio				+ sizeof(detalle);
		sb.apuntadorTablaInodo = sb.apuntadorBitTablaInodo + tam;
		sb.firstFreeBitTablaInodo = 1;
		sb.firstFreeBitBloque = 1;

		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);

		//fseek(archivo, sb.apuntadorCopia, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);

	} else {
		printf("Entro aqui\n");
		n = structDisco.part[i].exten[j].auxiliar - sizeof(superbloque);
		int m = (1 + sizeof(journal) + 3 + sizeof(inodo) + 3 * sizeof(datos));
		int nn = n / m;
		//tam = floor(nn);
		printf("tam1== %d\n", tam);
		pos = tam;
		//sb.nombre = name;
		sb.inodosCount = tam;
		sb.bloquesCount = tam * 3;
		sb.freeBloquesCount = tam - 1;
		sb.freeInodosCount = (tam * 3) - 10;
		sb.mountCount = 0;
		sb.magic = 201404368;  //0xEF53
		sb.inodoSize = sizeof(inodo);
		sb.bloqueSize = sizeof(datos);
		//sb.apuntadorBitTablaInodo = sb.apuntadorDetalleDirectorio
			//	+ sizeof(detalle);
		sb.apuntadorTablaInodo = sb.apuntadorBitTablaInodo + tam;
		sb.firstFreeBitTablaInodo = 1;
		sb.firstFreeBitBloque = 1;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);
		//fseek(archivo, sb.apuntadorCopia, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);

	}
	printf("-> Se ha dado formato a la particion correctamente.\n");

	char bit = '0';
	char bitmap = '1';
	int io = 0;
	/*fseek(archivo, sb.apuntadorBitArbolDirectorio, SEEK_SET);
	fwrite(&bitmap, 1, 1, archivo);

	for (io = 0; io < (pos) - 1; io++) {
		fwrite(&bit, 1, 1, archivo);
	}

	fseek(archivo, sb.apuntadorBitDetalleDirectorio, SEEK_SET);		//carpeta
	for (io = 0; io < (pos); io++) {
		fwrite(&bit, 1, 1, archivo);
	}
*/
	fseek(archivo, sb.apuntadorBitTablaInodo, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bit, 1, 1, archivo);
	}
/*
	fseek(archivo, sb.apuntadorBitmapInodo, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bit, 1, 1, archivo);
	}

avd insertar;
	insertar.apuntadorAVD = -1;
	insertar.fechaCreacion = time(0);
	insertar.directorio = 0;
	strcpy(insertar.name, "/");
	int ip = 0;
	for (ip = 0; ip < 4; ip++) {
		insertar.subDirectorios[ip] = 0;
	}
	fseek(archivo, sb.apuntadorAVD, SEEK_SET);
	fwrite(&insertar, sizeof(avd), 1, archivo);
*/
	//CAMBIOS EN EL JOURNALING
	journal bitacora;

	bitacora.operacion = 1;
	bitacora.tipo = 0;
	bitacora.fecha = time(0);
	//if(usrLogin!=NULL){
	//	strcpy(bitacora.usuario,usrLogin);
	//}
	//strcpy(bitacora.permiso,"664");
	strcpy(bitacora.nombre, "Formatear");
	strcpy(bitacora.contenido, "Formatear");

	//fseek(archivo, sb.apuntadorLog, SEEK_SET); //**
	//fwrite(&bitacora, sizeof(journal), 1, archivo);

	fclose(archivo);
	//printf("MM= %d\n", sb.magic);
	//strcpy(structDisco.part[i].name, montar[i].name);
	//metodoPrueba();
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
	fflush(NULL);
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
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
		for (j = 0; j < 10; j++) { //logica
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
	printf("MAGIC = %d\n", sb.magic);
	sb.magic = 201404368;
	if (sb.magic == 201404368) {
		//fseek(archivo, sb.apuntadorAVD, SEEK_SET);
		//avd ap;
		//fread(&ap, sizeof(ap), 1, archivo);

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
		printf("crearCarpeta ="); //XXX
		setbuf(stdin, NULL);
		//informacion = crearCarpeta(ruta, sb, ap, rutaC, p, ajuste, posicion,
			//	sb.apuntadorAVD);
		printf("%d\n",correcto);
		if (correcto > 0) {
			rutaC = strtok(verificar2, "/");
			//posicion = inicio & apuntador =atras
			printf("buscarArchivo\n"); //XXX
			setbuf(stdin, NULL);
			fflush(NULL);
			//datos = buscarArchivo(ruta, sb, ap, rutaC, ajuste, posicion,
				//	sb.apuntadorAVD);

			if (datos > 0) {
				rutaC = strtok(crear, "/");
				//verificar si ruta es igual a NULO
				while ((strstr(rutaC, ".") == 0x0 || strstr(rutaC, ".") == ""
						|| strstr(rutaC, ".") == NULL) && rutaC != NULL) {
					rutaC = strtok(NULL, "/");
					//		printf("rutaC= %s\n",rutaC);
					if (rutaC == NULL || rutaC == 0x0) {
						break;
					}
				}
				char leer[tamanio];
				//fflush(NULL);
				if (archivoCont != NULL) {
					fseek(archivoCont, 0, SEEK_SET);
					fread(&leer, tamanio, 1, archivoCont);
				} else {
					printf("Sin contenido.\n");
					int r, c = 0;
					for (r = 0; r < tamanio; r++) {
						leer[r] = (char) (c + 48);
						c++;
						if (c > 9) {
							c = 0;
						}
					}
				}
				fflush(NULL);
				//		printf("archivoCont ==  %s*\n",leer);
				char contenido[100];
				printf("ruta= %s\n",ruta);
				if (archivoCont != NULL || archivoCont != 0x0) {
				//	setbuf(stdin, NULL);
					//fflush(NULL);
					printf("AgregarArch\n");
					///agregarContenido(datos, sb, ruta, rutaC, ajuste, leer,tamanio);
					//cambiarPermiso(datos,sb,ruta, rutaC, "664","0");
					fflush(NULL);
					//printf("Contenido = %s\n",contenido);
					if (size == 0x0 || size == NULL) {
						strcat(contenido, "-cont:");
						strcat(contenido, cont);
					} else {
						strcat(contenido, "-size:");
						strcat(contenido, size);
					}

				printf("-> Se ha creado el archivo correctamente.\n");


				//bitacora(sb.apuntadorLog, 1, path, contenido, sb, ruta);
				} else {
					//FILE* archivoCont;
						//archivoCont = fopen("/home/aylin/vacio.txt", "r");

					printf("else\n");
					rutaC = "/home/aylin/vacio.txt";
					//agregarContenido(datos, sb, ruta, rutaC, ajuste, leer,tamanio);

					//contenido[0]= 'n';
				}
				////	printf("Contenido = %s\n",contenido);

			} else {
				printf("ERROR: No se ha podido crear el archivo.\n");
			}
		}
	} else {
		printf("ERROR: No se ha formateado la particion.\n");
	}
	return 1;
}
/*
int agregarContenido(int posicion, superbloque super, char* ruta, char* name,
		char ajuste, char* contenido, int size) {

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	fflush(NULL);
	int i = 0, k = 0;
	int j = 0;
	for (i = 0; i < 5; i++) { //Maneja 5 inodos

		if (carp.archivos[i].inodo > 1) {
			if (strcasecmp(carp.archivos[i].name, name) == 0) {
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
			setbuf(stdin, NULL);
			fflush(NULL);
			printf("agregar1\n");
			return agregarContenido(carp.detalle, super, ruta, name, ajuste, contenido,
					size);
		} else {
			printf("else1\n");
			detalle carp;
			carp.detalle = 0;
			int a = 0;
			for (a = 0; a < 5; a++) {
				carp.archivos[a].inodo = -1;
			}
			int posicion = 0;
			fclose(archivo);
			setbuf(stdin, NULL);
			if (ajuste == 'w') {
				posicion = peorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitDetalleDirectorio, 1);
			} else if (ajuste == 'f') {
				posicion = primerAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitDetalleDirectorio, 1);
			} else {
				posicion = mejorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitDetalleDirectorio, 1);
			}
			FILE* disco;
			disco = fopen(ruta, "rb+");

			carp.detalle = super.apuntadorDetalleDirectorio
					+ 100 * posicion * sizeof(detalle);
			fseek(disco, posicion, SEEK_SET);
			fwrite(&carp, sizeof(detalle), 1, disco);

			fseek(disco,
					super.apuntadorDetalleDirectorio
							+ 100 * posicion * sizeof(detalle), SEEK_SET);
			fwrite(&carp, sizeof(detalle), 1, disco);
			fclose(disco);
			setbuf(stdin, NULL);
			printf("agregar2\n");
			return agregarContenido(carp.detalle, super, ruta, name, ajuste, contenido,
					size);
			fflush(NULL);
		}
	} else { //Se crean los inodos
		printf("Creando inodos\n");
		strcpy(carp.archivos[j].name, name);
		int pos = 0;
		//setbuf(stdin, NULL);
		//carp.archivos[j].fechaCreacion = time(0);
		//carp.archivos[j].fechaModifica = time(0);

		fclose(archivo);
		if (ajuste == 'w') {
			pos = peorAjuste(super.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		} else if (ajuste == 'f') {
			pos = primerAjuste(super.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		} else {
			pos = mejorAjuste(super.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		}
		FILE* disco;
		disco = fopen(ruta, "rb+");
		carp.archivos[j].inodo = super.apuntadorTablaInodo
				+ 100 * pos * sizeof(inodo);
		fseek(disco, posicion, SEEK_SET);
		fwrite(&carp, sizeof(detalle), 1, disco);
		fclose(disco);

		inodo ino;
		ino.noAsignados = pos;
		ino.size = size;
		int aux = size / 25;

		if (size % 25) {
			aux++;
		}

		datos arch;
		char conten[200];
		strcpy(conten, contenido);
		int l, m = 0;
		int pos2 = 0;
		if (aux < 5) {

			ino.noInodo = size / 25;
			if (size % 25 > 0) {
				ino.noInodo++;
			}
			printf("NoInodo = %d\n",ino.noInodo);
			ino.indirecto = 0;
			setbuf(stdin, NULL);
			for (l = 0; l < ino.noInodo; l++) {
				if (ajuste == 'w') {
					pos2 = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos2 = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else {
					pos2 = mejorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
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
			}

		} else {
			printf("Si es el ultimo inodo\n");
			ino.noInodo = 4;
			setbuf(stdin, NULL);
			//p//rintf("1 = %d\n", super.apuntadorBitmapInodo);
			for (l = 0; l < 4; l++) {
				if (ajuste == 'w') {
					pos2 = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos2 = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitDetalleDirectorio, 1);
				} else {
					pos2 = mejorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
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
			}
			printf("2\n");
			int pos3 = 0;
			//setbuf(stdin, NULL);
			if (ajuste == 'w') {
				pos3 = peorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			} else if (ajuste == 'f') {
				pos3 = primerAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			} else {
				pos3 = mejorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			}
			printf("3\n");
			inodo ino2;
			ino2.noAsignados=pos3;
			ino2.size = size;
			ino2.indirecto = 0;
			ino2.noInodo = (size - 100) / 25;
			if ((size - 100) % 25 > 0) {
				ino2.noInodo++;
			}
			if (ino2.noInodo > 4) {
				ino2.noInodo = 4;
			}
			int pos4 = 0;
			setbuf(stdin, NULL);
			for (l = 0; l < ino2.noInodo; l++) {
				if (ajuste == 'w') {
					pos4 = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos4 = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else {
					pos4 = mejorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				}
				printf("4\n");
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
				printf("5\n");
			}

			disco = fopen(ruta, "rb+");
			ino.indirecto = super.apuntadorDetalleDirectorio
					+ 100 * pos3 * sizeof(inodo);
			fseek(disco,
					super.apuntadorDetalleDirectorio
							+ 100 * pos3 * sizeof(inodo), SEEK_SET);
			fwrite(&ino2, sizeof(inodo), 1, disco);
			fclose(disco);
			printf("6\n");
		}
		disco = fopen(ruta, "rb+");
		fseek(disco, super.apuntadorTablaInodo + 100 * pos * sizeof(inodo),
		SEEK_SET);
		fwrite(&ino, sizeof(inodo), 1, disco);
		fclose(disco);
		fflush(NULL);
		printf("-> Se agrego el archivo correctamente.\n");
		printf("7\n");
		return 1;
	}
}

*/

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

		if (sig >= archivo) {
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
