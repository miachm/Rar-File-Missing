#pragma once

#include "File_Mising.hpp"

using namespace std;

const unsigned int Oculto = 3;

/** Implementacion de ficheros ocultos para archivos RAR **/

class Rar_File_Mising : public File_Mising
{
private:
    bool ComprobarFirmaNombre(const char* Leer) const;
public:
    /** Constructor por defecto, llama a la clase base **/
    Rar_File_Mising(string Nombre,bool Opcion=0): File_Mising(Nombre,Opcion,"Rar!") {}

    /** Heredadas */

    unsigned int ListarArchivos(string &Resultado);
    unsigned int ListarArchivos(vector<string> &Resultado);
    unsigned int ListarArchivos(vector<string> &Resultado_Visibles,vector<string> &Resultado_Ocultos);

    /** Implementacion del metodo Generar de la clase File_Missing**/

    void Generar(vector<unsigned int> Numero);
    void Generar(vector<unsigned int> Ocultar,vector<unsigned int> Mostrar);
};
