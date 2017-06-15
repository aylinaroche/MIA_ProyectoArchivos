/*
 * estructuras.h
 *
 *  Created on: 6/06/2017
 *      Author: tanya
 */

#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

//BLOQUE DE CARPETAS

typedef struct ARCHIVO { //archivo //content
	char name[12];
	int inodo;
} archivo;

typedef struct CARPETA { //*detalle
	archivo content[4]; //16  //archivo
	int detalle; //Si ya no caben apunta a otro detalle
} detalle;

//BLOQUE DE ARCHIVOS

typedef struct APUNTADOR { //av
	char pointer[16]; //name
	int subDirectorios[6];
	int directorio;
	int apuntadorAVD;
} apunt;

typedef struct DATOS { //bloque de archivos
	char data[64]; //content
} datos;


typedef struct INODO {
	int noInodo;
	int size;
	int noAsignados; //numero de bloques asignados ///****
	int bloques[15];
	int indirecto; //apuntador indirecto por si ocupa mas de 4 //****
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
	char vdID[5];
	char padre[50];
	int tamanio;
} journal;

typedef struct DETALLE_SP { //Cola para realizar el mount
	int arbolVirtualCount;//
	int detalleDirectorioCount;
	int apuntadorBitArbolDirectorio;//
	int apuntador;//********
	int apuntadorBitDetalleDirectorio; //
	int apuntadorDetalleDirectorio;//
	int apuntadorBitmapInodo; //
	int contadorJ;
} detalleSB;

typedef struct JOURN{
	journal bitacora;
}journ;

typedef struct SUPERBLOQUE {
	int inodosCount; //
	int bloquesCount; //
	int freeBloquesCount; //
	int freeInodosCount; //
	time_t FechaMontado; //
	time_t FechaDesmontado; //
	int mountCount; //
	int apuntadorBitTablaInodo;	//
	int apuntadorTablaInodo;	//
	int apuntadorBitBloques;	//
	int apuntadorBloques;	//
	int inodoSize; //
	int bloqueSize; //
	int firstFreeBitTablaInodo;	//
	int firstFreeBitBloque;	//
	int magic; //
	int jourfirst;//
	journ j[50];
	detalleSB s;
} superbloque;

typedef struct LIST{
	char nombre[20];
}list;

typedef struct MONTAR { //Cola para realizar el mount
	char path[70];
	char name[40];
	int var;
	int part;
	char *vdID;
	int estado;
	int uso;
} mount;

typedef struct EBR { //20 maximo
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
