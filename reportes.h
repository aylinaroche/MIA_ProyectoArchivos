/*
 * reportes.h
 *
 *  Created on: 16/06/2017
 *      Author: aylin
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
char* LlenarReporteFile(char*aux4,char*mensaje,int posicion,char*path1);
char* LlenarReporteFile2(char*aux4,char*mensaje,int posicion);
int  reporteINODE(char* id, char* name, char* path);
int  reporteBLOQUE(char* id, char* name, char* path);
int  reporteTREE_COMPLETE(char* id, char* name, char* path);
////////////
int   reporteArbol(char* id, char* name, char* path);
int   encontrarArchivoTree(char* id,char* path, char* name, char* perm, char* user);
char* buscarCarpetaTree(char* ruta,char* path, superbloque super,int posicion,char* msj, int espacio);
int   buscarRaizCarpetaTree(char* ruta,superbloque super, int posicion,char* mensaje,int espacio,int c,int noA,int noI, int noB);
int   buscarRaizArchivoTree(char* ruta,superbloque super,int posicion,char*mensaje,int espacio);
int   reporteINODO(char* id, char* name, char* path);
int   reporteBLOQUE(char* id, char* name, char* path);

int reporteJOURNALING(char* name, char* path, char* id);

char * recorrerLista();
char * recorrerInodos();
char * recorrerBloques();

ino listaInodos[50];
blo listaBloques[50];
int contI;
int contB;
int contLinea;
int boolUltimo;
int boool;
int contBoool;
int auxB;
#endif /* REPORTES_H_ */
