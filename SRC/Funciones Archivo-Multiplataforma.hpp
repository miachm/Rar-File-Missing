/* Define con unas funciones genéricas para tratar con archivos.

Dependiendo de la plataforma correspondiente, llamará a sus API correspondiente

CrearArchivos = Crea las variables para tratar con archivos
AbrirArchivo(Archivo,Titulo,Modo) = Abre un nuevo archivo dado por un indentificador*/

#ifndef Definido
#define Definido
#ifdef WINDOWS
#include <windows.h>

#define Modo_Lectura GENERIC_READ
#define Modo_Escritura GENERIC_WRITE

#define Variable_Progueso DWORD progueso;
#define Variable_Tamanyo(nombre) DWORD nombre;

#define Obtener_Tamanyo Tamanyo = GetFileSize(Lectura,NULL); SetFilePointer(Lectura,0,NULL,FILE_BEGIN);

#define CrearArchivos HANDLE Lectura; HANDLE Escritura;
#define AbrirArchivo(Archivo,Titulo,Modo) Archivo = CreateFile(Titulo,Modo,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
//#define AbrirArchivoEsc(Archivo,Titulo,Modo) Archivo = CreateFile(Titulo.c_str(),GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

#define ComprobarApertura(Archivo) if (Lectura == INVALID_HANDLE_VALUE){ if (GetLastError() == ERROR_ACCESS_DENIED) throw Excepcion("No se pudo acceder al fichero, es posible que otra aplicacion lo tenga abierto o no tenga permisos",ERROR_DE_APERTURA); else throw Excepcion("No se puedo encontrar el archivo",ARCHIVO_NO_ENCONTRADO);}
#define ComprobarArchivoNoAbierto(Archivo) Archivo == INVALID_HANDLE_VALUE

#define Read(Archivo,Variable,Cantidad) ReadFile(Archivo,Variable,Cantidad,&progueso,NULL);
//#define Read(Archivo,Variable,Cantidad) if (ReadFile(Archivo,Variable,Cantidad,&progueso,NULL) == false) throw Excepcion("Error de lectura",ERROR_DE_LECTURA);

#define Write(Archivo,Variable,Cantidad) WriteFile(Archivo,Variable,Cantidad,&progueso,NULL);
//#define Write(Archivo,Variable,Cantidad) if (WriteFile(Archivo,Variable,Cantidad,&progueso,NULL) == false) throw Excepcion("Error de escritura",ERROR_DE_ESCRITURA);

#define ObtenerPosicion(Archivo) SetFilePointer(Archivo,0,NULL,FILE_CURRENT);

#define MoverA(Archivo,Posicion) SetFilePointer(Archivo,Posicion,NULL,FILE_BEGIN);
#define MoverAEsc(Archivo,Posicion) SetFilePointer(Archivo,Posicion,NULL,FILE_BEGIN);

#define CerrarArchivo(Archivo) CloseHandle(Archivo);
#else
#include <fstream>

#define Modo_Lectura ios::binary
#define Modo_Escritura ofstream::in|ofstream::binary

#define Variable_Progueso char progueso;
#define Variable_Tamanyo(nombre) unsigned short nombre;

#define Obtener_Tamanyo Lectura.seekg(0,ios::end); Tamanyo = Lectura.tellg(); Lectura.seekg(0);

#define CrearArchivos  ifstream Lectura; ofstream Escritura;
#define AbrirArchivo(Archivo,Titulo,Modo)  Archivo.open(Titulo,Modo);
#define ComprobarApertura(Archivo) if (!Archivo.is_open()) throw Excepcion("No se encontro el fichero",ARCHIVO_NO_ENCONTRADO);
#define ComprobarArchivoNoAbierto(Archivo) !Archivo.is_open()

#define Read(Archivo,Variable,Cantidad) Archivo.read((char*)Variable,Cantidad);
#define Write(Archivo,Variable,Cantidad) Archivo.write((char*)Variable,Cantidad);

#define ObtenerPosicion(Archivo) Archivo.tellg();

#define MoverA(Archivo,Posicion) Archivo.seekg(Posicion);
#define MoverAEsc(Archivo,Posicion) Archivo.seekp(Posicion);

#define CerrarArchivo(Archivo) Archivo.close();
#endif
#endif
