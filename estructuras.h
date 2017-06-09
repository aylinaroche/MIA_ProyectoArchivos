/*
 * estructuras.h
 *
 *  Created on: 6/06/2017
 *      Author: tanya
 */

#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_


typedef struct ARCHIVO { //archivo //content
	char name[12];
	int inodo;
} archivo;

typedef struct APUNTADOR { //av
	int point[16];
} apunt;

typedef struct DATOS { //bloque de archivos
	char data[64];
} datos;

typedef struct CARPETA { //*detalle
	archivo archivos[4]; //16  //contenido
	int detalle; //Si ya no caben apunta a otro detalle
} detalle;


typedef struct INODO {
	int noInodo;
	int size;
	//int noAsignados; //numero de bloques asignados
	int bloques[15];
	//int indirecto; //apuntador indirecto por si ocupa mas de 4
	//int contador;
	int uid;
	int gid;
	time_t fechaLeido;
	time_t fechaCreado;
	time_t fechaModificado;
	char type;
} inodo;


typedef struct JOURNAL {
	int operacion;
	int tipo; //0 archivo / 1 directorio
	char nombre[50];
	char contenido[50];
	time_t fecha;
//
	char propietario[50];
	char permisos[50];
} journal;


typedef struct SUPERBLOQUE {
	//char* nombre;
	//int arbolVirtualCount;//
	//int detalleDirectorioCount;
	int inodosCount; //
	int bloquesCount; //
	//int freeArbolCount;
	//int freeDetalleDirectorioCount;
	int freeBloquesCount; //
	int freeInodosCount; //
	time_t FechaMontado; //
	time_t FechaDesmontado; //
	int mountCount; //
	//int apuntadorBitArbolDirectorio;//
	//int apuntadorAVD;//
	//int apuntadorBitDetalleDirectorio; //
	//int apuntadorDetalleDirectorio;//
	int apuntadorBitTablaInodo;//
	int apuntadorTablaInodo;//
	int apuntadorBitBloques;//
	int apuntadorBloques;//
	//int apuntadorLog;//
	//int arbolDirectorioSize;
	//int detalleDirectorioSize;
	int inodoSize; //
	int bloqueSize; //
	//int firstFreeBitArbol;
	//int firstFreeBitDetalleDirectorio;
	int firstFreeBitTablaInodo;//
	int firstFreeBitBloque;//
	int magic; //
	//int apuntadorCopia;//
	//int apuntadorBitmapInodo; //
} superbloque;


typedef struct MONTAR { //Cola para realizar el mount
	char path[70];
	char name[40];
	int var;
	int part;
	char *vdID;
	int estado;
	int uso;
} mount;


typedef struct EBR { //Cambiar
	char status;
	char fit;
	int start;
	int size;
	int auxiliar;
	int next; //Byte en el que esta el sigueinte ebr -1 si no hay
	char name[16];
} ebr;


typedef struct PARTICION {
	char status; //1 activa, 0
	char type;
	char fit; //ajuste
	int start; //en que byte inicia
	int size;
	int auxiliar;
	char name[16];
	ebr exten[20];
} particion;


typedef struct MBR { //Master Boot Record -> Registro de arranque principal
	int size;
	time_t fecha;
	int signature;
	particion part[4];
	char* nameCopy;
} mbr;

#endif /* ESTRUCTURAS_H_ */
