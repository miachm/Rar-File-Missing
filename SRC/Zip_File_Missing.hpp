#ifndef ZIP_FILE_MISSING_H
#define ZIP_FILE_MISSING_H
#include "File_Mising.hpp"

class Zip_File_Mising : public File_Mising
{
private:
        bool ComprobarFirmaNombre(const char* Leer);
public:
        Zip_File_Mising(string Nombre,bool Opcion): File_Mising(Nombre,Opcion,"PK"){}

        unsigned int ListarArchivos(string &Resultado);
        unsigned int ListarArchivos(vector<string> &Resultado) {}
        unsigned int ListarArchivos(vector<string> &Resultado_Visibles,vector<string> &Resultado_Ocultos) {}

        void Generar(vector<unsigned int> Numero);
        void Generar(vector<unsigned int> Ocultar,vector<unsigned int> Mostrar){}
};

#endif // ZIP_FILE_MISSING_H
