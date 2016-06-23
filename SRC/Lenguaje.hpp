#ifndef LENGUAJE_H
#define LENGUAJE_H

#include <iostream>
#include <cstdlib>

using namespace std;

#define Espanyol 1
#define English 2

class Lenguaje
{
    private:
        unsigned short Idioma;

        string Mensaje_Inicio;
        string Contacto;
        string Buscando;

        string Error_NoArchivos;
        string Error_BadEntry;
        string Error_Inesperado;

        string Error_Parametros_por_consola;
        string Encontrados_Y_Procesados;

        string Seleccionar_Archivo;

        string Mensaje_Opcion;

        string LoadingFiles;
        string WarningZip;

        string Seleccionar_Numero_Archivo;
        string Seleccionar_Numero_Archivo2;

        string Finalizado;
        string Press_One_Key;

    public:
        Lenguaje(unsigned short idioma);

        static unsigned int ObtenerIdiomaSistema();

        string GetMensaje_Inicio() { return Mensaje_Inicio;}
        string GetContacto() { return Contacto;}
        string GetBuscando() { return Buscando;}

        string GetError_NoArchivos() { return Error_NoArchivos;}
        string GetError_BadEntry() { return Error_BadEntry;}
        string GetError_Inesperado() { return Error_Inesperado;}

        string GetError_Parametros_por_consola() { return Error_Parametros_por_consola;}
        string GetEncontrados_Y_Procesados(){ return Encontrados_Y_Procesados;}

        string GetSeleccionar_Archivo() { return Seleccionar_Archivo;}

        string GetMensaje_Opcion() { return Mensaje_Opcion;}

        string GetLoading_Files() { return LoadingFiles;}
        string GetWarningZip(){ return WarningZip;}

        string GetSeleccionar_Numero_Archivo() { return Seleccionar_Numero_Archivo;}
        string GetSeleccionar_Numero_Archivo2() { return Seleccionar_Numero_Archivo2;}


        string GetFinalizado() { return Finalizado;}
        string GetPress_One_Key() { return Press_One_Key;}
};

#endif // LENGUAJE_H
