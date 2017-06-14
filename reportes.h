/*
 * reportes.h
 *
 *  Created on: 8/06/2017
 *      Author: tanya
 */

#ifndef REPORTES_H_
#define REPORTES_H_

#include "estructuras.h"
int  reporteMBR(char* id, char* name, char* path);
int  reporteDISK(char* id, char* name, char* path);
int  reporteEXEC();
///////////////////////////////////////////////////
int  reporteBITACORA(char* name, char* path, char* id);
int  reporteBITMAP_INODO(char* name,char* path,char* id);
int  reporteBITMAP_BLOQUE(char* name,char* path,char* id);
int  reporteBITMAP_DETALLE(char* name,char* path,char* id);
int  reporteBITMAP_ARBOL(char* name,char* path,char* id);
int  reporteSB(char* name, char* path, char* id);
int  reporteTREE(char* name, char* path, char* id);
int  llenarTREE(char* ruta, char* texto, char* posicion);
int  reporteFILE(char*name,char* path,char*id,char*ruta);
int  reporteF(char*name,char*pa,char*id,char*ruta);
int  reporteDIRECTORIO(char* id, char* name, char* path);
char* completarDIRECTORIO(char* ruta, char*mensaje,int posicion);
int  reporteTREE_DIRECTORIO(char* id, char* name, char* path, char* ruta) ;
char* completarTreeD1(char* aux4, char* mensaje, int posicion,char*path) ;
char* completarTreeD2(char*aux4,char* mensaje,int posicion);
int  reporteINODO(char* id, char* name, char* path);
char* completarINODO(char* ruta, char* mensaje, int posicion);
int  reporteTREE_FILE(char* id, char* name, char* path, char* ruta);
char* completarTreeF1(char* ruta, char* mensaje, int posicion, char* path);
int  reporteTREE_F(char* id, char* name, char* path, char* ruta) ;
char* LlenarReporteFile(char*aux4,char*mensaje,int posicion,char*path1);
char* LlenarReporteFile2(char*aux4,char*mensaje,int posicion);

int  reporteINODE(char* id, char* name, char* path);
int  reporteBLOQUE(char* id, char* name, char* path);

int  reporteTREE_COMPLETE(char* id, char* name, char* path);
////////////

int   encontrarArchivo2(char* id,char* path, char* name, char* perm, char* user);
char* buscarCarpeta2(char* ruta,char* path, superbloque super,int posicion,char* msj, int espacio);
int   buscarRaizCarpeta2(char* ruta,superbloque super, int posicion,char* mensaje,int espacio);
int   buscarRaizArchivo2(char* ruta,superbloque super,int posicion,char*mensaje,int espacio);

#endif /* REPORTES_H_ */
