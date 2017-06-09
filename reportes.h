/*
 * reportes.h
 *
 *  Created on: 8/06/2017
 *      Author: tanya
 */

#ifndef REPORTES_H_
#define REPORTES_H_

#include "estructuras.h"

int reporteMBR(char* id, char* name, char* path);
int reporteDISK(char* id, char* name, char* path);
int reporteEXEC();
///////////////////////////////////////////////////
int reporteJOURNAL(char* name, char* path, char* id);
int reporteBITMAP_INODO(char* name,char* path,char* id);
int reporteBITMAP_BLOQUE(char* name,char* path,char* id);
int reporteSB(char* name, char* path, char* id);
int reporteTREE(char* name, char* path, char* id);
char* llenarTREE(char* ruta, char* texto, char* posicion);


#endif /* REPORTES_H_ */
