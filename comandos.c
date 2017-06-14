/*
 * comandos.c
 *
 *  Created on: 6/06/2017
 *      Author: tanya
 */

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "comandos.h"
#include <unistd.h>
#include <fcntl.h>

char *com1 = NULL;
char *com2 = NULL;
char *com3 = NULL;
char *com4 = NULL;
char *com5 = NULL;
char *com6 = NULL;
char *com7 = NULL;
char *com8 = NULL;

void verificarComando(char *com, char *atributos) {
	limpiarVariables();
	//	 printf("comando\n");

	char* inst = NULL;
	int cont = 1;
	if (strcasecmp(com, "prueba") == 0) {
		//metodoPrueba();
	}
	if (strcasecmp(com, "mkdisk") == 0 || strcasecmp(com, "Mkdisk") == 0
			|| strcasecmp(com, "MKDISK") == 0
			|| strcasecmp(com, "MKdisk") == 0) {
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				int k = j + 1;
				while (atr[k] != '\n') {
					atr[k] = ' ';
					k++;
				}
				atr[k] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");

		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			}
		}
		// imprimirDatos();
		crearDisco();

	} else if (strcasecmp(com, "rmdisk") == 0 || strcasecmp(com, "Rmdisk") == 0
			|| strcasecmp(com, "RMdisk") == 0
			|| strcasecmp(com, "RMDISK") == 0) {
		//	 printf("rmdisk\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		//  printf("ATR= %s\n",atributos);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		//  printf("inst = %s\n",inst);
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			}
		}
		//   imprimirDatos();
		eliminarDisco();

	}

	else if (strcasecmp(com, "fdisk") == 0 || strcasecmp(com, "Fdisk") == 0
			|| strcasecmp(com, "FDISK") == 0 || strcasecmp(com, "FDisk") == 0) {
		//      printf("fdisk\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		//   printf("ATR= %s\n",atributos);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		//  printf("inst = %s\n",inst);
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			case 6:
				com6 = inst;
				break;
			case 7:
				com7 = inst;
				break;
			case 8:
				com8 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			} else if (i == 5) {
				atributoDisco(com5);
			} else if (i == 6) {
				atributoDisco(com6);
			} else if (i == 7) {
				atributoDisco(com7);
			} else if (i == 8) {
				atributoDisco(com8);
			}
		}
		//      imprimirDatos();
		adminParticion();
		//montarFormato();
		//formatearDisco("vda1", "full", "0","k","3fs");

	} else if (strcasecmp(com, "mount") == 0 || strcasecmp(com, "MOUNT") == 0) {
		//  	 printf("mount\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		int bool = 0;
		while (inst != NULL) {
			inst = strtok(NULL, " ");

			if (inst != NULL) {
				if (strcmp(inst, "+") == 0) {
					mostrarMontadas();
					bool = 1;
					cont=-2;
				} else {
					switch (cont) {
					case 1:
						com1 = inst;
						break;
					case 2:
						com2 = inst;
						break;
					}
				}
				cont++;
			}
		}
		int i;
		//printf("cont = %d\n",cont);
		for (i = 1; i < cont; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			}
		}

		if (bool != 1) {
			montarP();
			//	mostrarMontadas();
		}

	} else if (strcasecmp(com, "umount") == 0 || strcasecmp(com, "UMOUNT") == 0
			|| strcasecmp(com, "UNmount") == 0) {
		//   printf("unmount\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		//printf("atr = %s\n", atributos);
		inst = strtok(atr, " ");

		// printf("inst1 =%s\n",inst);

		while (inst != NULL) {
			inst = strtok(NULL, " ");
			//printf("inst2 =%s\n",inst);
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			case 6:
				com6 = inst;
				break;
			case 7:
				com7 = inst;
				break;
			case 8:
				com8 = inst;
				break;
			}
			cont++;
		}
		int i;

		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
				desmontar(com1);
			} else if (i == 2) {
				atributoDisco(com2);
				desmontar(com2);
			} else if (i == 3) {
				atributoDisco(com3);
				desmontar(com3);
			} else if (i == 4) {
				atributoDisco(com4);
				desmontar(com4);
			} else if (i == 5) {
				atributoDisco(com5);
				desmontar(com5);
			} else if (i == 6) {
				atributoDisco(com6);
				desmontar(com6);
			} else if (i == 7) {
				atributoDisco(com7);
				desmontar(com7);
			} else if (i == 8) {
				atributoDisco(com8);
				desmontar(com8);
			}
		}

	} else if (strcasecmp(com, "REP") == 0 || strcasecmp(com, "rep") == 0) {
		//      printf("rep\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			}
		}
		//    imprimirDatos();
		generarReporte();

	} else if (strcasecmp(com, "exec") == 0 || strcasecmp(com, "EXEC") == 0) {
		//printf("exec\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}

		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			}
			cont++;
		}
		// boolExec=1;
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				//	  printf("a==%s\n",com1);
				atributoDisco(com1);
			}
		}
		script();

	} else if (strcasecmp(com, "df") == 0) {
		//   printf("disk free\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			}
		}
		//	imprimirDatos();
		//espacioLibre();

	} else if (strcasecmp(com, "du") == 0) {
		//  printf("disk used\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			}
		}
		//	imprimirDatos();
		//espacioUsado();

	} else if (strcasecmp(com, "mkfs") == 0) {
		// printf("mkfs\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			} else if (i == 5) {
				atributoDisco(com5);
			}
		}
		// imprimirDatos();
		formatear();

	} else if (strcasecmp(com, "chmod") == 0) {
		//         printf("chmod\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			}
		}
		//imprimirDatos();
		//permiso();

	} else if (strcasecmp(com, "mkfile") == 0) {
		//       printf("mkfile\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			} else if (i == 5) {
				atributoDisco(com5);
			}
		}
		//    imprimirDatos();
		crearArchivo();

	} else if (strcasecmp(com, "cat") == 0) {
		//   printf("cat - mostrar\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			} else if (i == 5) {
				atributoDisco(com5);
			}
		}
		//	imprimirDatos();
		mostrarContenido();

	} else if (strcasecmp(com, "rm") == 0) {
		//       printf("rm - Eliminar archivo\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
				//remover();
			} else if (i == 2) {
				atributoDisco(com2);
				remover();
			} else if (i == 3) {
				atributoDisco(com3);
				remover();
			} else if (i == 4) {
				atributoDisco(com4);
				remover();
			} else if (i == 5) {
				atributoDisco(com5);
				remover();
			}
		}
		//imprimirDatos();
		//remover();

	} else if (strcasecmp(com, "ls") == 0) {
		//	printf("editar\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			} else if (i == 5) {
				atributoDisco(com5);
			}
		}
		//      	 imprimirDatos();
		listar();

	} else if (strcasecmp(com, "mkdir") == 0) {
		//   printf("crear carpeta\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			}
		}
		//imprimirDatos();
		crearDirectorio();

	} else if (strcasecmp(com, "cp") == 0) {
		//      printf("copy\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			}
		}
		// imprimirDatos();
		copiar();

	} else if (strcasecmp(com, "mv") == 0) {
		//     printf("move\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			}
		}
		//imprimirDatos();
//		mover();

	} else if (strcasecmp(com, "find") == 0) {
		//	printf("find \n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			case 2:
				com2 = inst;
				break;
			case 3:
				com3 = inst;
				break;
			case 4:
				com4 = inst;
				break;
			case 5:
				com5 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			} else if (i == 2) {
				atributoDisco(com2);
			} else if (i == 3) {
				atributoDisco(com3);
			} else if (i == 4) {
				atributoDisco(com4);
			} else if (i == 5) {
				atributoDisco(com5);
			}
		}
		//imprimirDatos();
		//	 printf("que ");
		encontrar();

	} else if (strcasecmp(com, "recovery") == 0) {
		//     printf("Recuperar sistema\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			}
		}
		//imprimirDatos();

	} else if (strcasecmp(com, "loss") == 0) {
		//     printf("Perdida\n");
		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		strcpy(aux, atributos);
		inst = strtok(atributos, " ");
		while (inst != NULL) {
			inst = strtok(NULL, " ");
			switch (cont) {
			case 1:
				com1 = inst;
				break;
			}
			cont++;
		}
		int i;
		for (i = 1; i < cont - 1; i++) {
			if (i == 1) {
				atributoDisco(com1);
			}
		}
//		imprimirDatos();

	}

}
