/*
 * reportes.c
 *
 *  Created on: 16/06/2017
 *      Author: aylin
 */

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "reportes.h"
#include "estructuras.h"
#include "acciones.h"
#include <string.h>
#include "time.h"
#include "math.h"
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

int reporteDISK(char* id, char* name, char* path) {
//VERIFICA SI EL EL ID EXISTE
	//char* ruta;
	char* nom;
	char* direcc;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 30; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].loss == 1) {
					printf("ERROR: Existe un fallo en el disco.\n");
					return 0;
				}
				//printf("-> Se ha encontrado una particion con el id.\n");
				boolIgual = 1;
				nom = montar[i].name;
			}
			if (boolIgual == 1) {
				if (montar[i].estado == 1) {
					direcc = montar[i].path;
					break;
				}
			}
		}
	}
	if (boolIgual == 0) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	printf("path =%s\n", direcc);

//VERIFICA SI EL ARCHIVO EXISTE
	FILE* archivo;
	archivo = fopen(direcc, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	int j = 0;
	//CREA LA CARPETA SI NO EXISTE
	char direccion[200];
	char auxDirecc[200];
	for (i = 0; i < 200; i++) {
		auxDirecc[i] = '\0';
	}
	strcpy(direccion, path);
	char nombre[50];
	int n = 0;
	for (i = 0; i < 200; i++) {
		nombre[n] = direccion[i];
		if (direccion[i] == '/') {
			auxDirecc[i] = direccion[i];
			char *aux = (char*) malloc(150);
			strcpy(aux, "mkdir ");
			strcat(aux, auxDirecc);
			//   printf("auxD=%s\n",auxDirecc);
			system(aux);
			free(aux);
			n = 0;
		}
		auxDirecc[i] = direccion[i];
		n++;
		if (direccion[i] == '\0') {
			break;
		}
	}

	char d[200];
	strcpy(d, auxDirecc);
	char* ext = NULL;
	ext = &d;
	char* nam = NULL;
	nam = &d;
	//printf("EEEE=%s\n",ext);
	int boolExt = 0;
	char* auxName;
	char* extImg;
	ext = strtok(nam, ".");
	//printf("Ext=%s\n",ext);
	auxName = ext;

	while (ext != NULL) {
		ext = strtok(NULL, ".");
		//printf("ex =%s\n",ext);
		extImg = ext;
		if (ext != NULL) {
			if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
				boolExt = 1;
				break;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: La imagen no tiene extension.\n");
		return 0;
	}

	//printf("auxName= %s\n",auxName);
	char *e = ".dot";
	char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
	strcpy(dot, auxName);
	strcat(dot, e);
	//printf("dd=%s\n",dot);

	//CREA EL REPORTE
	int par = 0;
	FILE* report = fopen(dot, "w+");
	fprintf(report,
			"digraph particiones{\nrankdir=TB;\ncolor=blue;\n node[shape = record, color = cyan];\nsubgraph cluster{\n");
	fprintf(report, "label=\"%s\"", direcc);
	fprintf(report, "\nnode8[label=\"MBR");
	j = 3;
	char formato[15] = "Sin formato";

	for (j = 0; j < 4; j++) {
		superbloque sb;
		char ajuste;
		int posicion;

		posicion = structDisco.part[j].start;
		ajuste = structDisco.part[j].fit;
		fseek(archivo, structDisco.part[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);

		if (sb.magic == 201404368) {
			strcpy(formato, "Con formato");
		}

		if (structDisco.part[j].status == '1'
				&& (structDisco.part[j].type == 'P'
						|| structDisco.part[j].type == 'p')) {
			fprintf(report,
					"|PRIMARIA\n %s \n  %d  \n %s \n  %d  \n %d  \n %d  \n",
					structDisco.part[j].name, structDisco.part[j].size, formato,
					sb.bloquesCount, sb.bloquesCount - sb.freeBloquesCount,
					sb.freeBloquesCount);
			par++;

		} else if (structDisco.part[j].status == '0') {	//&& structDisco.part[j].size!=0){
			fprintf(report, "|LIBRE \n ---- \n 0000 ");
			par++;
		} else if (structDisco.part[j].status == '1'
				&& (structDisco.part[j].type == 'E'
						|| structDisco.part[j].type == 'e')) {
			fprintf(report,
					"|{EXTENDIDA \n %s \n %d \n %s \n  %d  \n %d  \n %d  \n |{",
					structDisco.part[j].name, structDisco.part[j].size, formato,
					sb.bloquesCount, sb.bloquesCount - sb.freeBloquesCount,
					sb.freeBloquesCount);
			int i;
			for (i = 0; i < 20; i++) {

				if (structDisco.part[j].exten[i].status == '1') {

					posicion = structDisco.part[j].exten[i].start;
					ajuste = structDisco.part[j].exten[i].fit;
					fseek(archivo, structDisco.part[j].exten[i].start,
					SEEK_SET);
					fread(&sb, sizeof(superbloque), 1, archivo);

					strcpy(formato, "Sin formato");
					if (sb.magic == 201404368) {
						strcpy(formato, "Con formato");
					}

					fprintf(report,
							"LOGICA \n %s \n  %d  \n %s \n %d  \n %d  \n %d  \n |",
							structDisco.part[j].exten[i].name,
							structDisco.part[j].exten[i].size, formato,
							sb.bloquesCount,
							sb.bloquesCount - sb.freeBloquesCount,
							sb.freeBloquesCount);
				} else if (structDisco.part[j].exten[i].status == '0'
						&& structDisco.part[j].exten[i].size != 0) {
					fprintf(report, "EBR|LIBRE |");
				}
			}
			strcpy(formato, "Sin formato");
			par++;
			fprintf(report, "}}");
		}

	}
	fprintf(report, "\"];\n\t}\n}");
	fclose(report);

	char *r1 = "dot -Tpng ";
	char *r2 = " -o ";
	char *ruta = (char*) malloc(
			1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
	strcpy(ruta, r1);
	strcat(ruta, dot);
	strcat(ruta, r2);
	strcat(ruta, path);
	printf("RUTA= %s\n", ruta);

	char consola[300];
	strcpy(consola, "");
	strcat(consola, ruta);
	printf("%s\n", consola);
	system(consola);
	printf("-> Se creo el reporte DISK correctamente.\n");
	char consola2[300];
	strcpy(consola2, "");
	strcat(consola2, "xdg-open ");
	strcat(consola2, auxDirecc);
	system(consola2);
	return 1;
}

int reporteMBR(char* id, char* name, char* path) {
	//printf("\nID = %s\n",id);

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 51; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].loss == 1) {
					printf("ERROR: Existe un fallo en el disco.\n");
					return 0;
				}
				boolIgual = 1;
			}
			if (boolIgual == 1) {
				if (montar[i].estado == 1) {
					direcc = montar[i].path;
					break;
				}
			}
		}
	}
	if (boolIgual == 0) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	printf("path =%s\n", direcc);

//VERIFICA SI EL ARCHIVO EXISTE
	FILE* archivo;
	archivo = fopen(direcc, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//CREA LA CARPETA SI NO EXISTE
	char direccion[200];
	char auxDirecc[200];
	for (i = 0; i < 200; i++) {
		auxDirecc[i] = '\0';
	}
	strcpy(direccion, path);
	char nombre[50];
	int n = 0;
	for (i = 0; i < 200; i++) {
		nombre[n] = direccion[i];
		if (direccion[i] == '/') {
			auxDirecc[i] = direccion[i];
			char *aux = (char*) malloc(150);
			strcpy(aux, "mkdir ");
			strcat(aux, auxDirecc);
			//   printf("auxD=%s\n",auxDirecc);
			system(aux);
			free(aux);
			n = 0;
		}
		auxDirecc[i] = direccion[i];
		n++;
		if (direccion[i] == '\0') {
			break;
		}
	}

	char d[200];
	strcpy(d, auxDirecc);

	char* ext = NULL;
	ext = &d;
	char* nam = NULL;
	nam = &d;
//printf("EEEE=%s\n",ext);
	int boolExt = 0;
	char* auxName;
	char* extImg;
	ext = strtok(nam, ".");
//printf("Ext=%s\n",ext);
	auxName = ext;

	while (ext != NULL) {
		ext = strtok(NULL, ".");
		//printf("ex =%s\n",ext);
		extImg = ext;
		if (ext != NULL) {
			if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
				boolExt = 1;
				break;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: La imagen no tiene extension.\n");
		return 0;
	}

//printf("auxName= %s\n",auxName);
	char *e = ".dot";
	char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
	strcpy(dot, auxName);
	strcat(dot, e);
//printf("dd=%s\n",dot);

	char fecha[100] = "fecha";
	struct tm *timeinfo;
	timeinfo = localtime(&structDisco.fecha);
	strftime(fecha, 100, "%c", timeinfo);

//CREA EL REPORTE
	FILE* report;
	report = fopen(dot, "w+");
	fprintf(report, "digraph mbr{\n");
	fprintf(report, "rankdir = LR;\n");
	fprintf(report,
			"node [shape = record, fontsize=12,fontname=\"%s\", color=lightsalmon, height = 1.2]; \n",
			"UBUNTU");
	fprintf(report, "Particion[label=\"");

	fprintf(report,
			"{%s}"
					"|* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
					"|{NOMBRE | VALOR}"
					"|{MBR_tamanio:| %d }"
					"|{ MBR_fecha:| %s }"
					"|{ MBR_disk_signature: | %d }"
					"", direcc, structDisco.size, fecha, structDisco.signature);
	int a = 0;
	for (a = 0; a < 4; a++) {
		if (structDisco.part[a].status == '1') {
			//printf("TIPO = %c\n", structDisco.part[a].type);
			fprintf(report,
					"|{PART_status_%d: | %c}"
							"| { PART_type_%d: | %c}"
							"|{ PART_fit_%d : | %c}"
							"| { PART_start_%d :| %d}"
							"|{ PART_size_%d:| %d }"
							"|{ PART_name_%d :| %s}"
							"| * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
							"", a, structDisco.part[a].status, a,
					structDisco.part[a].type, a, structDisco.part[a].fit, a,
					structDisco.part[a].start, a, structDisco.part[a].size, a,
					structDisco.part[a].name);
		}
	}

	fprintf(report, "\"];\n");

	for (a = 0; a < 4; a++) {
		if (structDisco.part[a].type == 'E'
				|| structDisco.part[a].type == 'e') {
			//printf("Extendida\n");
			int i = 0;
			int ii = 0;
			for (i = 0; i < 20; i++) {
				if (structDisco.part[a].exten[i].status == '1') {
					//	printf("Logica %d\n", i);
					ii++;
					fprintf(report, "Particion%d[label=\"", ii);
					fprintf(report, "{EBR_%d}"
							"|{PART_status_%d: | %c}"
							"|{ PART_fit_%d : | %c}"
							"| { PART_start_%d :| %d}"
							"|{ PART_size_%d:| %d }"
							"|{ PART_next_%d:| %d }"
							"|{ PART_name_L%d :| %s} ", ii, ii,
							structDisco.part[a].exten[i].status, ii,
							structDisco.part[a].exten[i].fit, ii,
							structDisco.part[a].exten[i].start, ii,
							structDisco.part[a].exten[i].size, ii,
							structDisco.part[a].exten[i].next, ii,
							structDisco.part[a].exten[i].name);

					fprintf(report, "\"];\n");

					if (i > 0) {
						fprintf(report, "Particion%d ->  Particion%d;\n", i,
								ii);
					}
				}
			}
		}
	}
	fprintf(report, "}\n");
	fclose(report);

	char *r1 = "dot -Tpng ";
	char *r2 = " -o ";
	char *ruta = (char*) malloc(
			1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
	strcpy(ruta, r1);
	strcat(ruta, dot);
	strcat(ruta, r2);
	strcat(ruta, path);
	//printf("RUTA= %s\n", ruta);

	char consola[300];
	strcpy(consola, "");
	strcat(consola, ruta);
	//printf("%s\n", consola);
	system(consola);
	printf("-> Se creo el reporte MBR correctamente.\n");
	char consola2[300];
	strcpy(consola2, "");
	strcat(consola2, "xdg-open ");
	strcat(consola2, auxDirecc);
	system(consola2);

	return 1;
}

int reporteBITMAP_INODO(char* name, char* path, char* id) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
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
		//char* operacionrar = structDisco.part[i].name;
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
//CREA EL ARCHIVO
	superbloque sb;

	if (existeLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

//	printf("CrearArchivo");
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		strcpy(direcc, path);
		char nombre[50];
		int n = 0;
		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//printf("Ruta de Archivo: %s\n", aux);
				system(aux);
				free(aux);
				n = 0;
			}
			direcc2[i] = direcc[i];
			n++;
			if (direcc[i] == '\0') {
				break;
			}
		}
		char d[200];
		strcpy(d, direcc2);

		char* ext = NULL;
		ext = &d;
		char* nam = NULL;
		nam = &d;
		//printf("EEEE=%s\n",ext);
		int boolExt = 0;
		char* auxName;
		char* extImg;
		ext = strtok(nam, ".");
		//printf("Ext=%s\n",ext);
		auxName = ext;

		while (ext != NULL) {
			ext = strtok(NULL, ".");
			//printf("ex =%s\n",ext);
			extImg = ext;
			if (ext != NULL) {
				if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
					boolExt = 1;
					break;
				}
			}
		}
		if (boolExt == 0) {
			printf("ERROR: La imagen no tiene extension.\n");
			return 0;
		}

		//printf("auxName= %s\n",auxName);
		char *e = ".dot";
		char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
		strcpy(dot, auxName);
		strcat(dot, e);
		//printf("dd=%s\n",dot);

		fseek(archivo, sb.apuntadorBitTablaInodo, SEEK_SET);
		//journal bitacora;
		//fread(&bitacora, sizeof(bitacora), 1, archivo);
		FILE* reporte;
		reporte = fopen(dot, "w+");
		int cont = 1;
		fprintf(reporte, "digraph sb{\n");
		fprintf(reporte, "rankdir = LR;\n");
		fprintf(reporte,
				"node [shape = record, fontsize=12,fontname=\"%s\", color=yellow, height = 1.2]; \n",
				"UBUNTU");
		fprintf(reporte, "Particion[label=\"{");

		printf("Count = %d\n", sb.inodosCount);
		int j = 0;
		int contador = 0;
		for (j = 0; j < sb.inodosCount; j++) {

			char p;
			fread(&p, 1, 1, archivo);
			if (p == '0') {
				fprintf(reporte, " %c   Y%d |", '0', contador);
			} else {
				fprintf(reporte, " %c   Y%d |", '1', contador);
			}
			if (cont == 10) {
				fprintf(reporte, "}| {");
				cont = 0;
			}
			cont++;
			contador++;
			if (j > 398) {
				break;
			}
		}
		fprintf(reporte, "}");
		fclose(archivo);
		fprintf(reporte, "\"];\n}");

		fclose(reporte);

		char *r1 = "dot -Tpng ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		printf("RUTA= %s\n", ruta);

		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte BITMAP INODO correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, direcc2);
		system(consola2);
		return 1;

	} else {
		printf(
				"ERROR: ERROR: No se ha formateado la particion la particion.\n");
		return 0;
	}

}

int reporteBITMAP_BLOQUE(char* name, char* path, char* id) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
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
		//char* operacionrar = structDisco.part[i].name;
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
	//CREA EL ARCHIVO
	superbloque sb;

	if (existeLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	printf("CrearArchivo");
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		strcpy(direcc, path);
		int n = 0;
		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//printf("Ruta de Archivo: %s\n", aux);
				system(aux);
				free(aux);
				n = 0;
			}
			direcc2[i] = direcc[i];
			n++;
			if (direcc[i] == '\0') {
				break;
			}
		}
		char d[200];
		strcpy(d, direcc2);

		char* ext = NULL;
		ext = &d;
		char* nam = NULL;
		nam = &d;
		//printf("EEEE=%s\n",ext);
		int boolExt = 0;
		char* auxName;
		char* extImg;
		ext = strtok(nam, ".");
		//printf("Ext=%s\n",ext);
		auxName = ext;

		while (ext != NULL) {
			ext = strtok(NULL, ".");
			//printf("ex =%s\n",ext);
			extImg = ext;
			if (ext != NULL) {
				if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
					boolExt = 1;
					break;
				}
			}
		}
		if (boolExt == 0) {
			printf("ERROR: La imagen no tiene extension.\n");
			return 0;
		}

		//printf("auxName= %s\n",auxName);
		char *e = ".dot";
		char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
		strcpy(dot, auxName);
		strcat(dot, e);
		//printf("dd=%s\n",dot);

		fseek(archivo, sb.s.apuntadorBitmapInodo, SEEK_SET);

		FILE* reporte;
		reporte = fopen(dot, "w+");
		int cont = 1;
		//fprintf(reporte, "Reporte BLOQUE: %s\n", ruta);
		printf("INODO = %d\n", sb.apuntadorBitTablaInodo);
		printf("BLOQUE = %d\n", sb.apuntadorBitBloques);
		fprintf(reporte, "digraph sb{\n");
		fprintf(reporte, "rankdir = LR;\n");
		fprintf(reporte,
				"node [shape = record, fontsize=12,fontname=\"%s\", color=orange, height = 1.2]; \n",
				"UBUNTU");
		fprintf(reporte, "Particion[label=\"{");

		printf("Count = %d\n", sb.bloquesCount);
		int j = 0;
		int contador = 0;
		for (j = 0; j < sb.inodosCount; j++) {

			char p;
			fread(&p, 1, 1, archivo);
			if (p == '0') {
				fprintf(reporte, " %c   B%d |", '0', contador);
			} else {
				fprintf(reporte, " %c   B%d |", '1', contador);
			}
			if (cont == 10) {
				fprintf(reporte, "}| {");
				cont = 0;
			}
			cont++;
			contador++;
			if (j > 398) {
				break;
			}
		}
		fprintf(reporte, "}");
		fclose(archivo);
		fprintf(reporte, "\"];\n}");

		fclose(reporte);

		char *r1 = "dot -Tpng ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		printf("RUTA= %s\n", ruta);

		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte BITMAP INODO correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, direcc2);
		system(consola2);
		return 1;

	} else {
		printf(
				"ERROR: ERROR: No se ha formateado la particion la particion.\n");
		return 0;
	}

}

int reporteSB(char* name, char* path, char* id) {
	//printf("sb");
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
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
	//CREA EL ARCHIVO
	superbloque sb;

	if (existeLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	//printf("CrearArchivo");
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

		char direccion[200];
		char auxDirecc[200];
		for (i = 0; i < 200; i++) {
			auxDirecc[i] = '\0';
		}
		strcpy(direccion, path);
		char nombre[50];
		int n = 0;
		for (i = 0; i < 200; i++) {
			nombre[n] = direccion[i];
			if (direccion[i] == '/') {
				auxDirecc[i] = direccion[i];
				char *aux = (char*) malloc(150);
				strcpy(aux, "mkdir ");
				strcat(aux, auxDirecc);
				//   printf("auxD=%s\n",auxDirecc);
				system(aux);
				free(aux);
				n = 0;
			}
			auxDirecc[i] = direccion[i];
			n++;
			if (direccion[i] == '\0') {
				break;
			}
		}

		char d[200];
		strcpy(d, auxDirecc);

		char* ext = NULL;
		ext = &d;
		char* nam = NULL;
		nam = &d;
		//printf("EEEE=%s\n",ext);
		int boolExt = 0;
		char* auxName;
		char* extImg;
		ext = strtok(nam, ".");
		//printf("Ext=%s\n",ext);
		auxName = ext;

		while (ext != NULL) {
			ext = strtok(NULL, ".");
			//printf("ex =%s\n",ext);
			extImg = ext;
			if (ext != NULL) {
				if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
					boolExt = 1;
					break;
				}
			}
		}
		if (boolExt == 0) {
			printf("ERROR: La imagen no tiene extension.\n");
			return 0;
		}

		//printf("auxName= %s\n",auxName);
		char *e = ".dot";
		char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
		strcpy(dot, auxName);
		strcat(dot, e);
		//printf("dd=%s\n",dot);

		FILE* reporte;
		reporte = fopen(dot, "w+");
		fprintf(reporte, "digraph sb{\n");
		fprintf(reporte, "rankdir = LR;\n");
		fprintf(reporte,
				"node [shape = record, fontsize=12,fontname=\"%s\", color=lightsalmon, height = 1.2]; \n",
				"UBUNTU");
		fprintf(reporte, "Particion[label=\"");
		char fecha[100] = "fecha";
		char fecha2[100];

		//printf("1\n");
		struct tm *timeinfo;
		struct tm *timeinfo2;
		timeinfo = localtime(&sb.FechaMontado);
		printf("2\n");
		strftime(fecha, 100, "%c", timeinfo);
		printf("2.1");
		timeinfo2 = localtime(&sb.FechaDesmontado);
		strftime(fecha2, 100, "%c", timeinfo2);
		printf("3\n");
		fprintf(reporte, "{%s}|{NOMBRE | VALOR}|", "REPORTE SB");
		fprintf(reporte, "{ ruta: | %s }|", ruta);
		fprintf(reporte, "{ s_inodes_count: | %d }|", sb.inodosCount);
		fprintf(reporte, "{ s_blocks_count: | %d }|", sb.bloquesCount);
		fprintf(reporte, "{ s_free_inodes_count: | %d }|", sb.freeInodosCount);
		fprintf(reporte, "{ s_free_blocks_count: | %d }|", sb.freeBloquesCount);
		fprintf(reporte, "{ s_mtime: | %s }|", fecha);
		fprintf(reporte, "{ s_umtime: | %s }|", fecha2);
		printf("4\n");
		fprintf(reporte, "{ s_mnt_count: | %d }|", 1);
		fprintf(reporte, "{ sb_magic:| %s }|", "0xEF53");
		fprintf(reporte, "{ s_inodes_size: | %d }|", sb.inodoSize);
		fprintf(reporte, "{ s_blocks_size: | %d }|", sb.bloqueSize);
		fprintf(reporte, "{ s_first_inode: | %d }|", sb.firstFreeBitTablaInodo);
		fprintf(reporte, "{ s_first_bloque: | %d }|", sb.firstFreeBitBloque);
		fprintf(reporte, "{ s_bm_inode_start: | %d }|",
				sb.apuntadorBitTablaInodo);
		fprintf(reporte, "{ s_bm_block_start: | %d }|", sb.apuntadorBitBloques);
		fprintf(reporte, "{ s_inode_start: | %d }|", sb.apuntadorTablaInodo);
		fprintf(reporte, "{ s_block_start: | %d }|", sb.apuntadorBloques);
		fprintf(reporte, "{ s_jourfirst: | %d }|", sb.jourfirst);
		fclose(archivo);
		fprintf(reporte, "\"];\n}");

		fclose(reporte);

		char *r1 = "dot -Tpng ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		//	printf("RUTA= %s\n", ruta);

		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte SB correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, auxDirecc);
		system(consola2);
		return 1;

	} else {
		printf(
				"ERROR: ERROR: No se ha formateado la particion la particion.\n");
		return 0;
	}

}

int reporteBITACORA(char* name, char* path, char* id) {
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
		//char* operacionrar = structDisco.part[i].name;
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

	sb.magic = 201404368;
	if (sb.magic == 201404368) {
		fseek(archivo, sb.jourfirst, SEEK_SET);
		journal bitacora;
		fread(&bitacora, sizeof(bitacora), 1, archivo);

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		strcpy(direcc, path);

		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//printf("Ruta de Archivo: %s\n", aux);
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

		//printf("CrearArchivo");
//CREA EL ARCHIVO
		FILE* reporte;
		reporte = fopen(path, "w+");
		char fecha[100];
		struct tm *timeinfo;
		timeinfo = localtime(&bitacora.fecha);
		strftime(fecha, 100, "%c", timeinfo);
		//printf("a");
		int cont = 0;
		while (bitacora.tipo > 0) { //MIENTRAS SEA CARPETA
			cont += 1;
			char operacion[100];
			char tipoOperacion[100];
			if (bitacora.operacion == 1) {
				strcpy(operacion, "mkfile");
			} else if (bitacora.operacion == 2) {
				strcpy(operacion, "cat");
			} else if (bitacora.operacion == 3) {
				strcpy(operacion, "rm");
			} else if (bitacora.operacion == 5) {
				strcpy(operacion, "ren");
			} else if (bitacora.operacion == 6) {
				strcpy(operacion, "mkdir");
			} else {
				strcpy(operacion, "formatear");
			}
			printf("* %d\n", cont);
			int a = 0;
			int b = 0;
			char nombre[100];
			strcpy(nombre, bitacora.nombre);
			for (b = 0; b < 100; b++) {
				if (nombre[b] == '.') {
					a++;
				}
			}
			if (a > 0) {
				strcpy(tipoOperacion, "archivo");
			} else {
				strcpy(tipoOperacion, "carpeta");
			}
			fprintf(reporte,
					"OPERACION: \"%s\" \n TIPO: \"%s\" \n NOMBRE : \"%s\" \n CONTENIDO: \"%s\" \n FECHA: \"%s\" \n ",
					operacion, tipoOperacion, bitacora.nombre,
					bitacora.contenido, asctime(timeinfo));

			fprintf(reporte, "\n");

			fseek(archivo, bitacora.tipo, SEEK_SET);
			fread(&bitacora, sizeof(bitacora), 1, archivo);

			if (cont == 20) {
				break;
			}
		}
		printf("c");
		char operacion[100];
		char tipoOperacion[100];
		if (bitacora.operacion == 1) {
			strcpy(operacion, "mkfile");
		} else if (bitacora.operacion == 2) {
			strcpy(operacion, "cat");
		} else if (bitacora.operacion == 3) {
			strcpy(operacion, "rm");
		} else if (bitacora.operacion == 5) {
			strcpy(operacion, "ren");
		} else if (bitacora.operacion == 6) {
			strcpy(operacion, "mkdir");
		}
		int a = 0;
		int b = 0;
		char nombre[100];
		strcpy(nombre, bitacora.nombre);
		for (b = 0; b < 100; b++) {
			if (nombre[b] == '.') {
				a++;
			}
		}
		if (a > 0) {
			strcpy(tipoOperacion, "archivo");
		} else {
			strcpy(tipoOperacion, "carpeta");
		}

		fprintf(reporte,
				"OPERACION: \"%s\" \n TIPO: \"%s\" \n NOMBRE : \"%s\" \n CONTENIDO: \"%s\" \n FECHA: \"%s\"",
				operacion, tipoOperacion, bitacora.nombre, bitacora.contenido,
				fecha);
		fprintf(reporte, "\n\n");

		fclose(reporte);

		printf("-> Se creo el reporte BITACORA correctamente.\n");
		char consola[300];
		strcpy(consola, "");
		strcat(consola, "xdg-open ");
		strcat(consola, direcc2);
		system(consola);
	} else {
		printf("ERROR: La particion no se ha formateado.\n");
	}

	return 1;
}

int reporteFILE(char* name, char* path, char* id, char* filen) {
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
			if (strcasecmp(structDisco.part[i].exten[j].name, name) == 0) {
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
		//printf("crear = %s\n",filen);
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
		int datos = 0;
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
				char mensaje[200];
				//		printf("contenidoArchivo.\n");
				strcpy(mensaje, contenidoArchivo(" ", datos, sb, ruta, ruta2));
				printf("* * * * * * * * * * * * * * * * * * * * * *\n%s\n",
						mensaje);

//////////////////////////////////////////////////////

				char direcc[200];
				char direcc2[200];
				int i = 0;
				for (i = 0; i < 200; i++) {
					direcc2[i] = '\0';
				}
				strcpy(direcc, path);

				for (i = 0; i < 200; i++) {
					if (direcc[i] == '/') {
						direcc2[i] = direcc[i];
						char *aux = (char*) malloc(200);
						strcpy(aux, "mkdir ");
						strcat(aux, direcc2);
						//printf("Ruta de Archivo: %s\n", aux);
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

				FILE* reporte;
				reporte = fopen(path, "w+");
				fprintf(reporte, "Reporte FILES: %s\n\n", ruta);
				fprintf(reporte, "%s", mensaje);
				fclose(reporte);

				printf("-> Se creo el reporte FILE correctamente.\n");
				char consola[300];
				strcpy(consola, "");
				strcat(consola, "xdg-open ");
				strcat(consola, direcc2);
				system(consola);
				return 1;

			}
		} else {
			printf("ERROR: La ruta no existe.\n");
		}
	} else {
		printf("ERROR: La particion no esta formateada.\n");
	}
	return 1;
}

char* LlenarReporteFile(char*aux4, char*mensaje, int posicion, char*path1) {
	FILE* disco;
	disco = fopen(aux4, "rb+");
	detalle con;
	fseek(disco, posicion, SEEK_SET);
	fread(&con, sizeof(detalle), 1, disco);
	char auxiliatura[10000];
	char cosas[25];
	sprintf(cosas, "%d", posicion);
	strcpy(auxiliatura, "node");
	strcat(auxiliatura, cosas);
	strcat(auxiliatura, " [label=\" {<f0> nombre} ");
	int i = 0;
	for (i = 0; i < 5; i++) {
		int mostrar = con.content[i].inodo;
		char* mostrar2 = con.content[i].name;

		if (con.content[i].inodo > 1) {
			if (strcasecmp(con.content[i].name, path1) == 0) {
				strcat(auxiliatura, "|{");
				strcat(auxiliatura, con.content[i].name);
				strcat(auxiliatura, "}");
				break;
			}
		}
	}
	strcat(auxiliatura, "\"]; \n");
	fclose(disco);
	if (i < 5) {
		char cosas2[25];
		char cosas3[25];
		sprintf(cosas2, "%d", i);
		sprintf(cosas3, "%d", con.content[i].inodo);
		strcat(auxiliatura, " node");
		strcat(auxiliatura, cosas);
		strcat(auxiliatura, " -> node");
		strcat(auxiliatura, cosas3);
		strcat(auxiliatura, ":f0 ;");
		strcat(auxiliatura,
				LlenarReporteFile2(aux4, " ", con.content[i].inodo));
	} else {
		if (con.detalle > 0) {
			char cosas2[25];
			char cosas3[25];
			sprintf(cosas2, "%d", i);
			sprintf(cosas3, "%d", con.detalle);
			strcat(auxiliatura, " node");
			strcat(auxiliatura, cosas);
			strcat(auxiliatura, " -> node");
			strcat(auxiliatura, cosas3);
			strcat(auxiliatura, ";");
			strcat(auxiliatura,
					LlenarReporteFile(aux4, " ", con.detalle, path1));
		}
	}
	return auxiliatura;

}

char* LlenarReporteFile2(char*aux4, char*mensaje, int posicion) {
	FILE* disco;
	disco = fopen(aux4, "rb+");
	inodo con;
	fseek(disco, posicion, SEEK_SET);
	fread(&con, sizeof(inodo), 1, disco);
	char auxiliatura[10000];
	char cosas[25];
	char cosas2[25];
	sprintf(cosas, "%d", posicion);
	strcpy(auxiliatura, "node");
	strcat(auxiliatura, cosas);
	strcat(auxiliatura,
			" [label=\" inodo <p0>|<f0>|<f1>|<f2>|<f3>|<f4> \"]; \n ");
	int i = 0;
	int k = 0;
	int w = 0;
	if (con.noInodo > 4) {
		con.noInodo = 4;
	}
	for (i = 0; i < con.noInodo; i++) {
		if (con.bloques[i] > 50) {
			datos cons;
			fseek(disco, con.bloques[i], SEEK_SET);
			fread(&cons, sizeof(datos), 1, disco);
			sprintf(cosas2, "%d", con.bloques[i]);
			strcat(auxiliatura, "node");
			strcat(auxiliatura, cosas2);
			strcat(auxiliatura, " [label=\"");
			char* pop = cons.data;
			strcat(auxiliatura, cons.data);
			strcat(auxiliatura, "\"]; \n");

			char cosas4[25];
			char cosas3[25];
			sprintf(cosas4, "%d", i);
			sprintf(cosas3, "%d", con.bloques[i]);
			strcat(auxiliatura, " node");
			strcat(auxiliatura, cosas);
			strcat(auxiliatura, ":f");
			strcat(auxiliatura, cosas4);
			strcat(auxiliatura, " -> node");
			strcat(auxiliatura, cosas3);
			strcat(auxiliatura, ";\n");

		}
	}
	if (con.indirecto > 50) {

		inodo con2;
		fseek(disco, con.indirecto, SEEK_SET);
		fread(&con2, sizeof(inodo), 1, disco);
		char cosasa[25];
		char cosas2b[25];
		sprintf(cosasa, "%d", con.indirecto);
		strcat(auxiliatura, "node");
		strcat(auxiliatura, cosasa);
		fclose(disco);
		strcat(auxiliatura,
				" [label=\"; inodo <p0>|<f0>|<f1>|<f2>|<f3>|<f4> \"]; \n ");
		int ia = 0;
		int ka = 0;
		int wa = 0;

		char cosas34[25];
		sprintf(cosas34, "%d", con.indirecto);
		strcat(auxiliatura, " node");
		strcat(auxiliatura, cosas);
		strcat(auxiliatura, ":f4 -> node");
		strcat(auxiliatura, cosas34);
		strcat(auxiliatura, ";");

		for (ia = 0; ia < con2.noInodo; ia++) {
			if (con2.bloques[ia] > 50) {
				datos cons;
				disco = fopen(aux4, "rb+");
				fseek(disco, con2.bloques[ia], SEEK_SET);
				fread(&cons, sizeof(datos), 1, disco);
				sprintf(cosas2b, "%d", con2.bloques[ia]);
				strcat(auxiliatura, "node");
				strcat(auxiliatura, cosas2b);
				strcat(auxiliatura, " [label=\"");
				strcat(auxiliatura, cons.data);
				strcat(auxiliatura, "\"]; \n");

				char cosas4[25];
				char cosas3[25];
				sprintf(cosas4, "%d", ia);
				sprintf(cosas3, "%d", con2.bloques[ia]);
				strcat(auxiliatura, " node");
				strcat(auxiliatura, cosasa);
				strcat(auxiliatura, ":f");
				strcat(auxiliatura, cosas4);
				strcat(auxiliatura, " -> node");
				strcat(auxiliatura, cosas3);
				strcat(auxiliatura, ";\n");
				fclose(disco);
			}
		}

	}
	return auxiliatura;
}

int reporteJOURNALING(char* name, char* path, char* id) {
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
		//char* operacionrar = structDisco.part[i].name;
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

	sb.magic = 201404368;
	if (sb.magic == 201404368) {

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		strcpy(direcc, path);

		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//printf("Ruta de Archivo: %s\n", aux);
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

		//printf("CrearArchivo");
//CREA EL ARCHIVO
		char fecha[100];
		struct tm *timeinfo;
		//timeinfo = localtime(&sb.j[]);
		//strftime(fecha, 100, "%c", timeinfo);

		FILE* reporte;
		reporte = fopen(path, "w+");
		int k = 0;
		printf("Contador J = %d\n", sb.s.contadorJ);
		for (k = 0; k < sb.s.contadorJ; k++) {
			journal bitacora = sb.j[k].bitacora;
//printf("a");
			int cont = 0;
			//while (bitacora.tipo > 0) { //MIENTRAS SEA CARPETA
			cont += 1;
			char operacion[100] = "";
			char tipoOperacion[100] = "";
			if (bitacora.operacion == 1) {
				strcpy(operacion, "mkfile");
			} else if (bitacora.operacion == 2) {
				strcpy(operacion, "cat");
			} else if (bitacora.operacion == 3) {
				strcpy(operacion, "rm");
			} else if (bitacora.operacion == 4) {
				strcpy(operacion, "cp");
			} else if (bitacora.operacion == 5) {
				strcpy(operacion, "mv");
			} else if (bitacora.operacion == 6) {
				strcpy(operacion, "mkdir");
			} else {
				strcpy(operacion, "formatear");
			}
			//printf("* %d\n", cont);
			int a = 0;
			int b = 0;
			char nombre[100];
			strcpy(nombre, bitacora.nombre);
			for (b = 0; b < 100; b++) {
				if (nombre[b] == '.') {
					a++;
				}
			}
			if (a > 0) {
				strcpy(tipoOperacion, "archivo");
			} else {
				strcpy(tipoOperacion, "carpeta");
			}
			char contenido[64] = "";
			strcpy(contenido, bitacora.contenido);
			fprintf(reporte,
					" OPERACION: \"%s\" \n TIPO: \"%s\" \n NOMBRE : \"%s\" \n CONTENIDO: \"%s\" \n  PADRE: \"%s\"  \n TAMANIO: \"%d\" \n FECHA: \"%s\" \n",
					operacion, tipoOperacion, bitacora.nombre, contenido,
					bitacora.padre, bitacora.tamanio, "");

			fprintf(reporte, "\n");
			//if(cont==19){
			///break;
			//}
			//bitacora = sb.j[cont].bitacora;
		}
		//}
		fprintf(reporte, "\n\n");

		fclose(reporte);

		printf("-> Se creo el reporte JOURNALING correctamente.\n");
		char consola[300];
		strcpy(consola, "");
		strcat(consola, "xdg-open ");
		strcat(consola, direcc2);
		system(consola);
	} else {
		printf("ERROR: La particion no se ha formateado.\n");
	}

	return 1;
}

///////////////

int reporteArbol(char* id, char* name, char* path) {
	//printf("\nID = %s\n",id);

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	char* nombres;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].loss == 1) {
					printf("ERROR: Existe un fallo en el disco.\n");
					return 0;
				}
				boolIgual = 1;
			}
			if (boolIgual == 1) {
				if (montar[i].estado == 1) {
					direcc = montar[i].path;
					nombres = montar[i].name;
					break;
				}
			}
		}
	}
	if (boolIgual == 0) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	//printf("path =%s\n", direcc);

//VERIFICA SI EL ARCHIVO EXISTE
	FILE* archivo1;
	archivo1 = fopen(direcc, "rb+");
	if (archivo1 == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo1, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo1);

//VERIFICA EL NOMBRE DE LA PARTICION
	int esLogica = 0;
	i = 0;
	int j = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombres) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombres) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: El nombre no existe.\n");
		return 0;
	}

	superbloque sb;
	if (esLogica == 1) {
		fseek(archivo1, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo1);

	} else {
		//int mos = structDisco.part[i].start;
		fseek(archivo1, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo1);
	}

//CREA LA CARPETA SI NO EXISTE
	char direccion[200];
	char auxDirecc[200];
	for (i = 0; i < 200; i++) {
		auxDirecc[i] = '\0';
	}
	strcpy(direccion, path);
	char nombre[50];
	int n = 0;
	for (i = 0; i < 200; i++) {
		nombre[n] = direccion[i];
		if (direccion[i] == '/') {
			auxDirecc[i] = direccion[i];
			char *aux = (char*) malloc(150);
			strcpy(aux, "mkdir ");
			strcat(aux, auxDirecc);
			//   printf("auxD=%s\n",auxDirecc);
			system(aux);
			free(aux);
			n = 0;
		}
		auxDirecc[i] = direccion[i];
		n++;
		if (direccion[i] == '\0') {
			break;
		}
	}
//VERIFICA LA EXTENSION DEL ARCHIVO
	char d[200];
	strcpy(d, auxDirecc);

	char* ext = NULL;
	ext = &d;
	char* nam = NULL;
	nam = &d;
//printf("EEEE=%s\n",ext);
	int boolExt = 0;
	char* auxName;
	char* extImg;
	ext = strtok(nam, ".");
//printf("Ext=%s\n",ext);
	auxName = ext;

	while (ext != NULL) {
		ext = strtok(NULL, ".");
		//printf("ex =%s\n",ext);
		extImg = ext;
		if (ext != NULL) {
			if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
				boolExt = 1;
				break;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: La imagen no tiene extension.\n");
		return 0;
	}

//printf("auxName= %s\n",auxName);
	char *e = ".dot";
	char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
	strcpy(dot, auxName);
	strcat(dot, e);
//printf("dd=%s\n",dot);

//VERIFICA SI SE HA FORMATEADO LA PARTICION
	if (sb.magic == 201404368) {
		fseek(archivo1, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo1);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, "/home");
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
		fclose(archivo1);

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
		contI = 1;
		contB = 1;
		int f = 0;
		for (f = 0; f < 50; f++) {
			ino inodo;
			inodo.noInodo = -1;
			inodo.size = -1;
			int g = 0;
			for (g = 0; g < 15; g++) {
				inodo.apuntadores[g] = -1;
				inodo.bloques[g] = -1;
			}
			listaInodos[f] = inodo;

			blo bloque;
			bloque.cont = -1;
			bloque.noBloque = -1;
			bloque.noAsignados = 0;
			for (g = 0; g < 15; g++) {
				archivo a;
				bloque.datos[g] = a;
			}
			listaBloques[f] = bloque;
		}
		boolUltimo = 0;
		if (strcasecmp(path, "/") == 0) {
			//printf("raiz\n");
			buscarRaizCarpetaTree(direcc, sb, sb.s.apuntador, aux2, 0, 0, 0, 1,
					1);
		} else {
			//printf("carp\n");
			buscarCarpetaTree(direcc, ruta1, sb, sb.s.apuntador, aux2, 0);
		}
//CREA EL REPORTE
		FILE* report;
		report = fopen(dot, "w+");
		fprintf(report, "digraph directorio{\n");
		fprintf(report, "rankdir = LR;\n");
		fprintf(report,
				"node [shape = record, fontsize=12,fontname=\"%s\", color=orange, height = 0.7]; ",
				"UBUNTU");

		char *r = recorrerLista();
		//printf(r);
		fprintf(report, r);

		fprintf(report, "\n}");
		fclose(report);

		char *r1 = "dot -Tpng ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		printf("RUTA= %s\n", ruta);

		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte DIRECTORIO correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, auxDirecc);
		system(consola2);
	} else {
		printf("ERROR: No se ha formateado la particion la particion.\n");
	}
	return 1;
}

char* buscarCarpetaTree(char* ruta, char* path, superbloque super, int posicion,
		char* mensaje, int espacio) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap, ap2;
	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, archivo);

	int i = 0;
	int j = 0;
	for (j = 0; j < espacio; j++) {
		printf(" ");
	}
	printf("|_%s *\n", ap.pointer);

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
			buscarCarpetaTree(ruta, path, super, ap.subDirectorios[i], mensaje,
					espacio + 2);
		} else {
			int a = ap.subDirectorios[i];
			fclose(archivo);

			buscarRaizCarpetaTree(ruta, super, a, mensaje, espacio + 2, 0, 0, 0,
					0);
		}
	} else {
		if (ap.apuntador < 1) {
			printf("ERROR: No existe la carpeta indicada.\n");
			//return "";
		} else {
			fclose(archivo);
			int p = ap.apuntador;
			buscarCarpetaTree(ruta, path, super, p, mensaje, espacio);
		}
	}
	//listaInodos[cI] = inodo;
	//listaBloques[cB] = bloque;

	return "";
}

int buscarRaizCarpetaTree(char* ruta, superbloque super, int posicion,
		char* mensaje, int espacio, int posBloque, int noApunt, int noInodo,
		int noBloque) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	apunt ap2, ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(apunt), 1, archivo);

	int i = 0;
	int j = 0;

	for (j = 0; j < espacio; j++) {
		printf(" ");
	}
	printf("|_%s ~ \n", ap.pointer);
	fclose(archivo);

//Agregar * & ** en bloque

//	if (noInodo == 0) {
//		if (posBloque == 0) {
//			strcpy(listaBloques[noBloque].datos[0].name, "   *  ");
//			//strcpy(listaBloques[noBloque].datos[posBloque].name, "  *  * ");
//			//posBloque++;
//		}
//	} else {
//		if (posBloque == 1) {
//			strcpy(listaBloques[noBloque].datos[1].name, "   *  ");
//			//strcpy(listaBloques[noBloque].datos[posBloque].name, "  *  * ");
//			//posBloque++;
//		}
//	}
//	posBloque++;
//Si es el ultimo bloque
	if (boool == 1) {
		if (contBoool == 1) {
			int i = 0;
			int contB = 0;

			for (i = 0; i < 50; i++) {
				if (listaBloques[i].noBloque > 0) {
					contB++;
				}
			}
			noBloque = contB;
			contBoool++;
			auxB = noBloque;
		} else if (contBoool > 1) {
			noBloque = auxB;
			//contBoool++;
		} else {
			contBoool++;
		}
	}

//Agregar inodo y bloque
	listaInodos[noInodo].noInodo = noInodo + 1;

	if (listaInodos[noInodo].apuntadores[noApunt] != 1) {
		listaInodos[noInodo].bloques[noApunt] = noBloque + 1;
		//printf("I%d -> B%d\n", noInodo, noBloque);
	}
	listaInodos[noInodo].apuntadores[noApunt] = 1;
	//printf("AD%d\n", noApunt);

	listaBloques[noBloque].noBloque = noBloque + 1;
	strcpy(listaBloques[noBloque].datos[posBloque].name, ap.pointer);
	int contB = 0;
	for (i = 0; i < 50; i++) {
		if (listaBloques[i].noBloque > 0) {
			contB++;
		}
	}
	if (boool == 1) {
		if (contBoool >= 2) {

			int contI = 0;
			for (i = 0; i < 50; i++) {
				if (listaInodos[i].noInodo > 0) {
					contI++;
				}
			}
			int n =contBoool-1;
			noInodo = contI-n;
			contBoool++;
		}
	}
	for (i = 0; i < 4; i++) {

		if (ap.subDirectorios[i] > 500) {
			boolUltimo = 0;
			if (i != 3) {
				listaBloques[noBloque].datos[posBloque].inodo = noInodo + 1 + 1;
				//printf("B%d -> I%d\n", noBloque, noInodo + 1);
			}
			archivo = fopen(ruta, "rb+");
			fseek(archivo, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, archivo);

			fclose(archivo);

			buscarRaizCarpetaTree(ruta, super, ap.subDirectorios[i], mensaje,
					espacio + 2, i + 1, noApunt, noInodo + 1, noBloque + 1);
			//break;
			//return 1;
		}
	}

	if (ap.directorio > 100) {
		buscarRaizArchivoTree(ruta, super, ap.directorio, mensaje, espacio + 2);
	}
	if (ap.apuntador > 100) {
		boool = 1;
		contBoool = 0;
		//noInodo++;
		int i = 0;
		int contI = 0;
		int contB = 0;
		for (i = 0; i < 50; i++) {
			if (listaInodos[i].noInodo > 0) {
				contI++;
			}
		}
		int c = contI - (noInodo + 1);
		int c2 = contB - (noBloque + 1);
		//cont

		//printf("C = %d\n", contI);
		///listaInodos[noInodo+1].apuntadores[noApunt + 1] = 1;
		//listaInodos[noInodo+1].bloques[posBloque + 1] = contB;

		buscarRaizCarpetaTree(ruta, super, ap.apuntador, mensaje, espacio, 0,
				noApunt + 1, noInodo, noBloque);
		boool = 0;
		contBoool = 0;
	}
	if (i == 4 && boolUltimo == 0) {
		boolUltimo = 1;
		//posBloque--;
		noInodo = noInodo + posBloque;
		noBloque = noBloque + posBloque;
		listaInodos[noInodo].noInodo = noInodo + 1;

		if (listaInodos[noInodo].apuntadores[noApunt] != 1) {
			listaInodos[noInodo].bloques[posBloque] = noBloque + 1;
		}
		listaInodos[noInodo].apuntadores[noApunt] = 1;

		listaBloques[noBloque].noBloque = noBloque + 1;
		strcpy(listaBloques[noBloque].datos[1].name, "  * ");
		strcpy(listaBloques[noBloque].datos[2].name, " *  * ");
		listaBloques[noBloque - posBloque].datos[posBloque].inodo = noInodo + 1;
		//printf("I%d -> B%d\n", noInodo + 2, noBloque + 1);

	}

}

int buscarRaizArchivoTree(char* ruta, superbloque super, int posicion,
		char* mensaje, int espacio) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(detalle), 1, archivo);
	int i = 0;
	int x = 0;
	int j = 0;

	inodo ino;
	fseek(archivo, ap.detalle, SEEK_SET);
	fread(&ino, sizeof(inodo), 1, archivo);
	fseek(archivo, posicion, SEEK_SET);
	fread(&ino, sizeof(inodo), 1, archivo);

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

char * recorrerLista() {
	char cadena[10000] = "";
	int i = 0;

	for (i = 0; i < 50; i++) {
		ino inodo = listaInodos[i];
		if (inodo.noInodo > 0) {
			char buffer[10];
			char aux[20];
			//strcpy(cadena, "Inodo");
			sprintf(buffer, "\nInodo%d", inodo.noInodo);
			strcpy(aux, buffer);
			strcat(cadena, aux);
			strcpy(buffer, "");
			char b2[50] = "";
			sprintf(b2, "[label=\" {INODO_%d", inodo.noInodo - 1);
			strcpy(aux, b2);
			strcat(cadena, aux);
			strcat(cadena, "}| {Tipo: | 1}| {Tamanio : | 0}|");
			int j = 0;
			for (j = 0; j < 15; j++) {
				int ap = inodo.apuntadores[j];
				if (ap == 1) {
					sprintf(buffer, "{AD%d", j);
					strcpy(aux, buffer);
					strcat(cadena, aux);
					strcat(cadena, ":| 1 } |");
				}
			}
			strcat(cadena, "\"];");
		}
	}
	for (i = 0; i < 50; i++) {
		blo bloque = listaBloques[i];
		if (bloque.noBloque > 0) {
			char buffer[20];
			char aux[20];
			sprintf(buffer, "\nBloque%d[color = green,", bloque.noBloque);
			strcpy(aux, buffer);
			strcat(cadena, aux);
			sprintf(buffer, "label=\" {BLOQUE_%d", bloque.noBloque - 1);
			strcpy(aux, buffer);
			strcat(cadena, aux);
			strcat(cadena, "}|");
			int j = 0;
			int j2 = 5;
			int l = 0;
			if (i == 0) {
				j2 = 4;
			} else {
				l = 1;
			}
			for (j = l; j < j2; j++) {
				strcat(cadena, bloque.datos[j].name);
				if (j < j2 - 1) {
					strcat(cadena, "|");
				}

			}
			strcat(cadena, "\"];");
		}
	}
	//Conexiones
	for (i = 0; i < 50; i++) {
		ino inodo = listaInodos[i];
		if (inodo.noInodo > 0) {
			char buffer[10];
			char aux[20];
			int j = 0;
			for (j = 0; j < 15; j++) {
				int ap = inodo.bloques[j];
				if (ap > 0 && ap < 15) {
					sprintf(buffer, "\nInodo%d -> ", inodo.noInodo);
					strcpy(aux, buffer);
					strcat(cadena, aux);

					sprintf(buffer, "Bloque%d", inodo.bloques[j]);
					strcpy(aux, buffer);
					strcat(cadena, aux);
				}
			}
		}
	}
	for (i = 0; i < 50; i++) {
		blo bloque = listaBloques[i];
		if (bloque.noBloque > 0) {
			char buffer[10];
			char aux[20];
			int j = 0;
			for (j = 0; j < 5; j++) {
				int ap = bloque.datos[j].inodo;
				if (ap > 0 && ap < 15) {
					sprintf(buffer, "\nBloque%d -> ", bloque.noBloque);
					strcpy(aux, buffer);
					strcat(cadena, aux);
					sprintf(buffer, "Inodo%d\n", ap);
					strcpy(aux, buffer);
					strcat(cadena, aux);
				}
			}
		}
	}
	//printf(cadena);
	return cadena;
}
//
int reporteINODO(char* id, char* name, char* path) {
	//printf("\nID = %s\n",id);

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	char* nombres;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].loss == 1) {
					printf("ERROR: Existe un fallo en el disco.\n");
					return 0;
				}
				boolIgual = 1;
			}
			if (boolIgual == 1) {
				if (montar[i].estado == 1) {
					direcc = montar[i].path;
					nombres = montar[i].name;
					break;
				}
			}
		}
	}
	if (boolIgual == 0) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	//printf("path =%s\n", direcc);

//VERIFICA SI EL ARCHIVO EXISTE
	FILE* archivo1;
	archivo1 = fopen(direcc, "rb+");
	if (archivo1 == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo1, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo1);

//VERIFICA EL NOMBRE DE LA PARTICION
	int esLogica = 0;
	i = 0;
	int j = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombres) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombres) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: El nombre no existe.\n");
		return 0;
	}

	superbloque sb;
	if (esLogica == 1) {
		fseek(archivo1, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo1);

	} else {
		//int mos = structDisco.part[i].start;
		fseek(archivo1, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo1);
	}

//CREA LA CARPETA SI NO EXISTE
	char direccion[200];
	char auxDirecc[200];
	for (i = 0; i < 200; i++) {
		auxDirecc[i] = '\0';
	}
	strcpy(direccion, path);
	char nombre[50];
	int n = 0;
	for (i = 0; i < 200; i++) {
		nombre[n] = direccion[i];
		if (direccion[i] == '/') {
			auxDirecc[i] = direccion[i];
			char *aux = (char*) malloc(150);
			strcpy(aux, "mkdir ");
			strcat(aux, auxDirecc);
			//   printf("auxD=%s\n",auxDirecc);
			system(aux);
			free(aux);
			n = 0;
		}
		auxDirecc[i] = direccion[i];
		n++;
		if (direccion[i] == '\0') {
			break;
		}
	}
//VERIFICA LA EXTENSION DEL ARCHIVO
	char d[200];
	strcpy(d, auxDirecc);

	char* ext = NULL;
	ext = &d;
	char* nam = NULL;
	nam = &d;
//printf("EEEE=%s\n",ext);
	int boolExt = 0;
	char* auxName;
	char* extImg;
	ext = strtok(nam, ".");
//printf("Ext=%s\n",ext);
	auxName = ext;

	while (ext != NULL) {
		ext = strtok(NULL, ".");
		//printf("ex =%s\n",ext);
		extImg = ext;
		if (ext != NULL) {
			if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
				boolExt = 1;
				break;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: La imagen no tiene extension.\n");
		return 0;
	}

//printf("auxName= %s\n",auxName);
	char *e = ".dot";
	char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
	strcpy(dot, auxName);
	strcat(dot, e);
//printf("dd=%s\n",dot);

//VERIFICA SI SE HA FORMATEADO LA PARTICION
	if (sb.magic == 201404368) {
		fseek(archivo1, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo1);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, "/home");
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
		fclose(archivo1);

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
		contI = 1;
		contB = 1;
		int f = 0;
		for (f = 0; f < 50; f++) {
			ino inodo;
			inodo.noInodo = -1;
			inodo.size = -1;
			int g = 0;
			for (g = 0; g < 15; g++) {
				inodo.apuntadores[g] = -1;
				inodo.bloques[g] = -1;
			}
			listaInodos[f] = inodo;

			blo bloque;
			bloque.cont = -1;
			bloque.noBloque = -1;
			bloque.noAsignados = 0;
			for (g = 0; g < 15; g++) {
				archivo a;
				bloque.datos[g] = a;
			}
			listaBloques[f] = bloque;
		}
		boolUltimo = 0;
		if (strcasecmp(path, "/") == 0) {
			//printf("raiz\n");
			buscarRaizCarpetaTree(direcc, sb, sb.s.apuntador, aux2, 0, 0, 0, 1,
					1);
		} else {
			//printf("carp\n");
			buscarCarpetaTree(direcc, ruta1, sb, sb.s.apuntador, aux2, 0);
		}
//CREA EL REPORTE
		FILE* report;
		report = fopen(dot, "w+");
		fprintf(report, "digraph directorio{\n");
		fprintf(report, "rankdir = LR;\n");
		fprintf(report,
				"node [shape = record, fontsize=12,fontname=\"%s\", color=orange, height = 0.7]; ",
				"UBUNTU");

		char *r = recorrerInodos();
		//printf(r);
		fprintf(report, r);

		fprintf(report, "\n}");
		fclose(report);

		char *r1 = "dot -Tpng ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		printf("RUTA= %s\n", ruta);

		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte de INODOS correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, auxDirecc);
		system(consola2);
	} else {
		printf("ERROR: No se ha formateado la particion la particion.\n");
	}
	return 1;
}

int reporteBLOQUE(char* id, char* name, char* path) {
	//printf("\nID = %s\n",id);

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	char* nombres;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].loss == 1) {
					printf("ERROR: Existe un fallo en el disco.\n");
					return 0;
				}
				boolIgual = 1;
			}
			if (boolIgual == 1) {
				if (montar[i].estado == 1) {
					direcc = montar[i].path;
					nombres = montar[i].name;
					break;
				}
			}
		}
	}
	if (boolIgual == 0) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	//printf("path =%s\n", direcc);

//VERIFICA SI EL ARCHIVO EXISTE
	FILE* archivo1;
	archivo1 = fopen(direcc, "rb+");
	if (archivo1 == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo1, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo1);

//VERIFICA EL NOMBRE DE LA PARTICION
	int esLogica = 0;
	i = 0;
	int j = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombres) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombres) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: El nombre no existe.\n");
		return 0;
	}

	superbloque sb;
	if (esLogica == 1) {
		fseek(archivo1, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo1);

	} else {
		//int mos = structDisco.part[i].start;
		fseek(archivo1, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo1);
	}

//CREA LA CARPETA SI NO EXISTE
	char direccion[200];
	char auxDirecc[200];
	for (i = 0; i < 200; i++) {
		auxDirecc[i] = '\0';
	}
	strcpy(direccion, path);
	char nombre[50];
	int n = 0;
	for (i = 0; i < 200; i++) {
		nombre[n] = direccion[i];
		if (direccion[i] == '/') {
			auxDirecc[i] = direccion[i];
			char *aux = (char*) malloc(150);
			strcpy(aux, "mkdir ");
			strcat(aux, auxDirecc);
			//   printf("auxD=%s\n",auxDirecc);
			system(aux);
			free(aux);
			n = 0;
		}
		auxDirecc[i] = direccion[i];
		n++;
		if (direccion[i] == '\0') {
			break;
		}
	}
//VERIFICA LA EXTENSION DEL ARCHIVO
	char d[200];
	strcpy(d, auxDirecc);

	char* ext = NULL;
	ext = &d;
	char* nam = NULL;
	nam = &d;
//printf("EEEE=%s\n",ext);
	int boolExt = 0;
	char* auxName;
	char* extImg;
	ext = strtok(nam, ".");
//printf("Ext=%s\n",ext);
	auxName = ext;

	while (ext != NULL) {
		ext = strtok(NULL, ".");
		//printf("ex =%s\n",ext);
		extImg = ext;
		if (ext != NULL) {
			if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
				boolExt = 1;
				break;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: La imagen no tiene extension.\n");
		return 0;
	}

//printf("auxName= %s\n",auxName);
	char *e = ".dot";
	char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
	strcpy(dot, auxName);
	strcat(dot, e);
//printf("dd=%s\n",dot);

//VERIFICA SI SE HA FORMATEADO LA PARTICION
	if (sb.magic == 201404368) {
		fseek(archivo1, sb.s.apuntador, SEEK_SET);
		apunt ap;
		fread(&ap, sizeof(ap), 1, archivo1);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, "/home");
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
		fclose(archivo1);

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
		contI = 1;
		contB = 1;
		int f = 0;
		for (f = 0; f < 50; f++) {
			ino inodo;
			inodo.noInodo = -1;
			inodo.size = -1;
			int g = 0;
			for (g = 0; g < 15; g++) {
				inodo.apuntadores[g] = -1;
				inodo.bloques[g] = -1;
			}
			listaInodos[f] = inodo;

			blo bloque;
			bloque.cont = -1;
			bloque.noBloque = -1;
			bloque.noAsignados = 0;
			for (g = 0; g < 15; g++) {
				archivo a;
				bloque.datos[g] = a;
			}
			listaBloques[f] = bloque;
		}
		boolUltimo = 0;
		if (strcasecmp(path, "/") == 0) {
			//printf("raiz\n");
			buscarRaizCarpetaTree(direcc, sb, sb.s.apuntador, aux2, 0, 0, 0, 1,
					1);
		} else {
			//printf("carp\n");
			buscarCarpetaTree(direcc, ruta1, sb, sb.s.apuntador, aux2, 0);
		}
//CREA EL REPORTE
		FILE* report;
		report = fopen(dot, "w+");
		fprintf(report, "digraph directorio{\n");
		fprintf(report, "rankdir = LR;\n");
		fprintf(report,
				"node [shape = record, fontsize=12,fontname=\"%s\", color=orange, height = 0.7]; ",
				"UBUNTU");

		char *r = recorrerBloques();
		//printf(r);
		fprintf(report, r);

		fprintf(report, "\n}");
		fclose(report);

		char *r1 = "dot -Tpng ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		printf("RUTA= %s\n", ruta);

		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte de BLOQUES correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, auxDirecc);
		system(consola2);
	} else {
		printf("ERROR: No se ha formateado la particion la particion.\n");
	}
	return 1;
}
//
char * recorrerInodos() {
	char cadena[10000] = "";
	int i = 0;
	int cantidad = 0;
	for (i = 0; i < 50; i++) {
		ino inodo = listaInodos[i];
		if (inodo.noInodo > 0) {
			cantidad++;
			char buffer[10];
			char aux[20];
			//strcpy(cadena, "Inodo");
			sprintf(buffer, "\nInodo%d", inodo.noInodo);
			strcpy(aux, buffer);
			strcat(cadena, aux);
			strcpy(buffer, "");
			char b2[50] = "";
			sprintf(b2, "[label=\" {INODO_%d", inodo.noInodo - 1);
			strcpy(aux, b2);
			strcat(cadena, aux);
			strcat(cadena, "}| {Tipo: | 1}| {Tamanio : | 0}|");
			int j = 0;
			for (j = 0; j < 15; j++) {
				int ap = inodo.apuntadores[j];
				if (ap == 1) {
					sprintf(buffer, "{AD%d", j);
					strcpy(aux, buffer);
					strcat(cadena, aux);
					strcat(cadena, ":| 1 } |");
				}
			}
			strcat(cadena, "\"];");
		}
	}
	//Conexiones
	for (i = 0; i < cantidad - 1; i++) {
		ino inodo = listaInodos[i];
		char buffer[10];
		char aux[20];

		sprintf(buffer, "\nInodo%d -> ", i + 1);
		strcpy(aux, buffer);
		strcat(cadena, aux);

		sprintf(buffer, "Inodo%d", i + 2);
		strcpy(aux, buffer);
		strcat(cadena, aux);

	}
	//printf(cadena);
	return cadena;
}

char * recorrerBloques() {
	char cadena[10000] = "";
	int i = 0;
	int cantidad = 0;
	for (i = 0; i < 50; i++) {
		blo bloque = listaBloques[i];
		if (bloque.noBloque > 0) {
			cantidad++;
			char buffer[20];
			char aux[20];
			sprintf(buffer, "\nBloque%d[color = green,", bloque.noBloque);
			strcpy(aux, buffer);
			strcat(cadena, aux);
			sprintf(buffer, "label=\" {BLOQUE_%d", bloque.noBloque - 1);
			strcpy(aux, buffer);
			strcat(cadena, aux);
			strcat(cadena, "}|");
			int j = 0;
			int j2 = 5;
			int l = 0;
			if (i == 0) {
				j2 = 4;
			} else {
				l = 1;
			}
			for (j = l; j < j2; j++) {
				strcat(cadena, bloque.datos[j].name);
				if (j < j2 - 1) {
					strcat(cadena, "|");
				}

			}
			strcat(cadena, "\"];");
		}
	}
	//Conexiones
	for (i = 0; i < cantidad - 1; i++) {
		//ino inodo = listaBloques[i];
		char buffer[10];
		char aux[20];

		sprintf(buffer, "\nBloque%d -> ", i + 1);
		strcpy(aux, buffer);
		strcat(cadena, aux);

		sprintf(buffer, "Bloque%d", i + 2);
		strcpy(aux, buffer);
		strcat(cadena, aux);

	}
	//printf(cadena);
	return cadena;
}

