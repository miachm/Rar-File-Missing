#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdio.h>

#include "Funciones Archivo-Multiplataforma.hpp"
#include "File_Mising Codigos De Error.hpp"

using namespace std;

/** Esta es una interfaz que sirve como base para las operaciones genéricas de ocultacion en un archivo comprimido.

Es necesario implementar las funciones especificas para un determinado formato (Rar, Zip...)

**/

class File_Mising
{
private:

    bool ComprobarFormato(const char* Formato); // Comprueba que se trata del archivo dado
    bool CambiarModo() {if (Modo) Modo =false; else Modo = true;}

protected:

    CrearArchivos

    vector<unsigned long long> Archivo; // Este vector lo usaremos como lista para guardar las dirreciones de los archivos
    unsigned long long Tamanyo; // Tamanyo del archivo
    string Nombre; // Nombre del archivo
    bool Modo; // Modo seleccionado: 0 significa Ocultación y 1 significa Desocultar.
    void OrdenarVector(vector<unsigned int> &Numero);

       // bool ComprobarFirmaNombre(const char* Leer); //Comprobar si se aproxima un nuevo archivo
public:


    /** Constructor, se le transmite el nombre del archivo y la opcion escogida. Lo abre y comprueba
    que se trata de un archivo del formato especificado. Si falla lanzará una excepción con los siguientes códigos de error:

    - ARCHIVO_NO_ENCONTRADO
    - ERROR_DE_APERTURA (Solo en Windows y en caso de que no se dispongan de permisos)

     **/

    File_Mising(string Nombre,bool Opcion,const char* Formato);

    /** La siguiente función lista los archivos del paquete en un string para mostrar (que se pasa por referencia).
     Esta función devuelve el numero de archivos encontrados*/

    virtual unsigned int ListarArchivos(string &Resultado) = 0;

     /** Similar a la anterior, pero devuelve solo los nombres en*/

    virtual unsigned int ListarArchivos(vector<string> &Resultado) = 0;

    /** Similar a la anterior, pero sobrecargada para devolver los dos resultados en nombres */

    virtual unsigned int ListarArchivos(vector<string> &Resultado_Visibles,vector<string> &Resultado_Ocultos) = 0;

    /** Funcion express, busca y oculta/muestra los archivos con los nombres correspondientes **/

    unsigned int BuscarYEjecutar(char* Ficheros[],unsigned int N_Ficheros,bool Todos);

    /** Devuelve el numero de archivos listados */

    inline unsigned short NumeroDeArchivos() const {return Archivo.size();}

    /** Dada una lista de archivos (Generada previamente por la función ListarArchivos()) y un nombre para el archivo de salida. Genera un nuevo Archivo con los archivos
    ocultos/mostrados segun el modo que se haya escogido. Esta función puede lanzar excepciones con los siguientes códigos de error:

    - SIN_ARCHIVOS: No se ha llamado a la función ListarArchivos para crear la lista, o bien el paquete no contiene archivos
    - ERROR_DE_APERTURA: Fallo al abrir el paquete en modo escritura**/

    virtual void Generar(vector<unsigned int> Numero) = 0;

    /** Similar a la función anterior, pero puedes indicar la lista de archivos a
    ocultar y a mostrar */

    virtual void Generar(vector<unsigned int> Ocultar,vector<unsigned int> Mostrar) = 0;

    /** Objeto para lanzar excepciones. Podemos mostrar un mensaje de error por pantalla y capturar
    el tipo de error observando la variable int. Los valores de la variable int se definen en el fichero
    de cabecera "File_Mising Codigos De Error.hpp" **/

    struct Excepcion
    {
        /** Los codigos de error se encuentrar en el archivo de cabecera "File_Mising Codigos De Error.hpp" */
        unsigned int N_Error;
        /** Mensaje de error **/
        string Mensaje;
        /** Constructor de excepciones**/
        Excepcion(string mensaje,unsigned int Error) : Mensaje(mensaje),N_Error(Error) {};
    };

    /** Destructor por defecto **/

    ~File_Mising();

};
