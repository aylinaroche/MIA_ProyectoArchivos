/*
 * acciones.h
 *
 *  Created on: 6/06/2017
 *      Author: tanya
 */

#ifndef ACCIONES_H_
#define ACCIONES_H_

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <time.h>
#include <math.h>
#include "estructuras.h"

void mostrarMontadas();
//int AgregarArch(int posicion,superbloque super, char* aux4, char* name,char ajuste, char* contenido, int size);
void atributoDisco(char* coman);
void crearDisco();
/*
 * int  crearArchivoBinario(char* size, char* path, char* nom);
int  multiploDeOcho(int tam);
void imprimirDatos();
void limpiarVariables();
void metodoPrueba();
void mostrarMontadas();
int  eliminarDisco();
void adminParticion();
int  crearParticion(char* path,char* name,char* size,char* unit,char* type,char* fit);
int  agregarParticion(char* add,char* unit,char* path,char* name);
int  eliminarParticion(char* delete,char* path,char* name);
void montarP();
int  montarParticion(char* path, char* name);
void desmontar();
int  desmontarParticion(char* id);
int  mm(char*pa,char*name);
int  miMontar(char *path, char *name);
char *letraDisco(int varLetra);
int  aleatorio();
void script();
int  ejecutarScript(char *path);
void atributoExec(char* coman);
char *numeroMontar(int num);
*/
/////////////////////////////////////////////////////////////////////////////////////
/**
void espacioLibre();
int  verEspacioLibre(char* id, char* path,int K, int M, int H, int I);
void espacioUsado();
int  verEspacioUsado(char *id,char *path, char* n,int boolH);
void formatear();
int  formatearDisco(char* id, char* type, char* add, char* unit, char* fs);
void login();
int  loginUsuario(char* usuario, char* password,char* id);
int  verificarLogin(char* atributos, char* usuario,char* password);
void logout();
void crearGrupo();
int  crearGrupoDisco(char* id, char* usuario);
void eliminarGrupo();
int  eliminarGrupoDisco(char* id, char* usuario);
int  eliminarG(char* atributos,char* usuario);
char* cambiarEliminado(char* atributos);
void crearUsuario();
int  crearUsuarioDisco(char* id, char* usuario, char* password, char* grupo);
int  verificarGrupo(char* grupo);
int  verificar(char* atributos, char* grupo);
void eliminarUsuario();
int  eliminarUsuarioDisco(char* id, char* usuario);
int  eliminarU(char* atributos, char* usuario);
int  obtenerArchivoUsers(char* id);
//////////////////////////////////////
void crearArchivo();
int  crearArchivoParticion(char* id,char* path,char* p,char* size,char* cont);
int  agregarContenido(int posicion,superbloque super, char* ruta, char* name,char ajuste, char* contenido, int siz);
int  crearCarpeta(char* ruta,superbloque super,avd apun,char*path,char*p,char ajuste, int inicio, int atras);
void permiso();
int  permisoArchivo(char* id,char* path,char* ugo, char* R);
int  cambiarPermiso(int posicion,superbloque super, char* ruta, char* nombre, char* permiso,int opcion);
void mostrarContenido();
int  mostrarContenidoArchivo(char* id, char* filen);
void remover();
int  removerArchivo(char* id,char* path, int rf);
int  eliminarArchivo(int posicion,superbloque super, char* ruta, char* name);
int  eliminarCarpeta(char* ruta,superbloque super,char* path,int posicion);
int  bitacora(int posicion, int operacion, char*nombre, char*contenido, superbloque super, char* aux4);
int  buscarArchivo(char* ruta,superbloque super,avd ap,char* path,char ajuste, int inicio, int atras);
int  primerAjuste(int bloque,char* ruta, int inicio, int archivo);
int  mejorAjuste(int bloque,char* ruta, int inicio, int archivo);
int  peorAjuste(int bloque, char *aux4, int inicio, int archivo);

void  copiar();
int   copiarArchivo(char* id, char* path,char* dest, char* iddest);
int   copiarCarpeta(char* ruta,superbloque super,char* path,int posicion,char* dest,char* iddest);
int   copiarRaizCarpeta(char* ruta,superbloque super,int posicion,char* iddest,char* dest);
int   crearCopia(char* id, char* path,char* p);
int   copiarRaizArchivo(char* ruta,superbloque super,int posicion,char* iddest,char* dest);
char* contenidoArchivo(char* mensaje,int posicion,superbloque super, char* ruta, char* name);
void  renombrar();
int   renombrarArchivo(char* id, char* path,char* name);
int   cambiarNombre(int posicion,superbloque super, char* ruta, char* nombre, char* nombreNuevo);
void  encontrar();
int   encontrarArchivo(char* id,char* path, char* name, char* perm, char* user);
char* buscarCarpeta(char* ruta,char* path, superbloque super,int posicion,char* msj, int espacio);
int   buscarRaizCarpeta(char* ruta,superbloque super, int posicion,char* mensaje,int espacio);
int   buscarRaizArchivo(char* ruta,superbloque super,int posicion,char*mensaje,int espacio);
int   buscarRaizArchivo(char* ruta,superbloque super,int posicion,char* mensaje,int espacio);
void  crearDirectorio();
int   crearDirectorioArchivo(char* id, char* path, char* p);
void  editar();
void  mover();
int   moverArchivo(char* id, char* path, char* dest, char* iddest);
//superbloque crearBloque();
*/
int  boolExec;
//mount montar[50];


#endif /* ACCIONES_H_ */
