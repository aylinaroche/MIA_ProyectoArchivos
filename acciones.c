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
boolExec = 0;
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
		if (strcasecmp(token1, "-tamanio") == 0
				|| strcasecmp(token1, "–tamanio") == 0
				|| strcasecmp(token1, "+tamanio") == 0) { //Verifica cada atributo
			token1 = strtok(NULL, ">");
			size = token1;
		} else if (strcasecmp(token1, "+unit") == 0) {
			token1 = strtok(NULL, ">");
			unit = token1;
		} else if (strcasecmp(token1, "-path") == 0
				|| strcasecmp(token1, "–path") == 0
				|| strcasecmp(token1, "+path") == 0) {
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
		} else if (strcasecmp(token1, "+tipo") == 0) {
			token1 = strtok(NULL, ">");
			type = token1;
		} else if (strcasecmp(token1, "+fit") == 0) {
			token1 = strtok(NULL, ">");
			fit = token1;
		} else if (strcasecmp(token1, "+delete") == 0) {
			token1 = strtok(NULL, ">");
			dele = token1;
		} else if (strcasecmp(token1, "-nombre") == 0
				|| strcasecmp(token1, "–nombre") == 0) {
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
		} else if (strcasecmp(token1, "+add") == 0) {
			token1 = strtok(NULL, ">");
			add = token1;
		} else if (strcasecmp(token1, "-id") == 0
				|| strcasecmp(token1, "–id") == 0) {
			token1 = strtok(NULL, ">");
			id = token1;
		} else if (strcasecmp(token1, "-id1") == 0
				|| strcasecmp(token1, "-id2") == 0
				|| strcasecmp(token1, "-id3") == 0
				|| strcasecmp(token1, "-id4") == 0
				|| strcasecmp(token1, "-id5") == 0
				|| strcasecmp(token1, "-id6") == 0
				|| strcasecmp(token1, "-id7") == 0
				|| strcasecmp(token1, "-id8") == 0) {

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

		} else if (strcasecmp(token1, "+k") == 0) {
			boolK = 1;
		} else if (strcasecmp(token1, "+m") == 0) {
			boolM = 1;
		} else if (strcasecmp(token1, "+h") == 0
				|| strcasecmp(token1, "-h") == 0
				|| strcasecmp(token1, "–h") == 0) {
			boolH = 1;
		} else if (strcasecmp(token1, "+i") == 0) {
			boolI = 1;
		} else if (strcasecmp(token1, "+n") == 0) {
			token1 = strtok(NULL, ">");
			nDirectorio = token1;
		} else if (strcasecmp(token1, "+fs") == 0) {
			token1 = strtok(NULL, ">");
			fs = token1;
		} else if (strcasecmp(token1, "-usr") == 0
				|| strcasecmp(token1, "–usr") == 0) {
			token1 = strtok(NULL, ">");
			usuario = token1;
		} else if (strcasecmp(token1, "-pwd") == 0
				|| strcasecmp(token1, "–pwd") == 0) {
			token1 = strtok(NULL, ">");
			password = token1;
		} else if (strcasecmp(token1, "-grp") == 0
				|| strcasecmp(token1, "–grp") == 0) {
			token1 = strtok(NULL, ">");
			grupo = token1;
		} else if (strcasecmp(token1, "-ugo") == 0
				|| strcasecmp(token1, "–ugo") == 0) {
			token1 = strtok(NULL, ">");
			ugo = token1;
		} else if (strcasecmp(token1, "+r") == 0) {
			boolR = 1;
		} else if (strcasecmp(token1, "+p") == 0
				|| strcasecmp(token1, "-p") == 0
				|| strcasecmp(token1, "–p") == 0) {
			p = "p";
		} else if (strcasecmp(token1, "+cont") == 0) {
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
		} else if (strcasecmp(token1, "+rf") == 0) {
			rf = 1;
		} else if (strcasecmp(token1, "-dest") == 0) {
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
		} else if (strcasecmp(token1, "-iddest") == 0) {
			token1 = strtok(NULL, ">");
			iddest = token1;
		} else if (strcasecmp(token1, "+perm") == 0) {
			token1 = strtok(NULL, ">");
			perm = token1;
		} else if (strcasecmp(token1, "+user") == 0) {
			token1 = strtok(NULL, ">");
			user = token1;
		} else if (strcasecmp(token1, "-file1") == 0) {
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

		} else if (strcasecmp(token1, "-file2") == 0) {
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

		} else if (strcasecmp(token1, "-file3") == 0) {
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

		} else if (strcasecmp(token1, "+allocation") == 0) {
			token1 = strtok(NULL, ">");
			allocation = token1;
		} else {
			printf("ERROR: El atributo \"%s\" es incorrecto.\n", token1);
		}

	}
}

