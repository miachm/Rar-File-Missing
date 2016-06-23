#include "File_Mising.hpp"

/* Este es el archivo CPP por defecto de la clase Rar_File_Mising, aquí se muestra la implementación de dicha clase. */

// Constructor

File_Mising::File_Mising(string nombre,bool Opcion,const char* Formato)
{
    AbrirArchivo(Lectura,nombre.c_str(),Modo_Lectura)

    ComprobarApertura(Lectura)

    Nombre = nombre;

    if (ComprobarFormato(Formato) == false) // Comprobamos que se trate del formato adecuado
    {
        CerrarArchivo(Lectura)
        throw Excepcion("Este archivo no es de un formato valido",ARCHIVO_INVALIDO);
    }

    // Calculamos su tamaño

    Obtener_Tamanyo

    // Por ultimo asignamos la opcion elegida

    Modo = Opcion;
}

/* Funcion auxiliar al constructor, sirve para verificar que el archivo proporcionado es un Rar.
Para ello comprueba la firma que tiene todo archivo Rar: La cabecera "Rar!" */

bool File_Mising::ComprobarFormato(const char* Formato)
{
    // Comprobamos que esta abierto por si acaso
    char Leer[5] = {0}; // Nuestra variable de lectura, le asignamos el valor 0 para poder usar la funcion strcmp mas tarde

    Variable_Progueso

    ComprobarApertura(Lectura)

    Read(Lectura,Leer,strlen(Formato))

    if (strcmp(Leer,Formato) == 0) // Si la firma es correcta devolvemos verdadero y si no falso
        return true;
    else
        return false;
}


/* Función express, lista todos los ficheros y oculta los que se correspondan con una lista de nombres proporcionada.
Está adaptada para su uso con argumentos de programa, por ello elimina los 3 primeros nombres de la lista. */

unsigned int File_Mising::BuscarYEjecutar(char* Ficheros[],unsigned int N_Ficheros,bool Todos)
{
    Variable_Progueso
    Variable_Tamanyo(Tamanyo_Nombre)

    MoverA(Lectura,0)

    vector<unsigned int> Numero; // Archivos a procesar
    char Leer[256] = {0};
    string Aux;

    if (ListarArchivos(Aux) != 0) // Listamos los ficheros
    {
        if (Todos == false)
        {

        for (unsigned int i = 0;i < Archivo.size();i++)
        {
            MoverA(Lectura,Archivo[i]+24)
            Read(Lectura,&Tamanyo_Nombre,1)
            MoverA(Lectura,Archivo[i]+30)
            Read(Lectura,Leer,Tamanyo_Nombre)

            for (int j = 0;j < (N_Ficheros-3);j++) // Comprobamos que el fichero se corresponde con algunos de los proporcionados
            {
             //   string cdt = Leer;
               // cout<<cdt<<endl;
                if (strcmp(Leer,Ficheros[j+3]) == 0)
                {
                    Numero.push_back(i);
                }
            }
            memset(Leer,0,256);
        }
            if (Numero.size() != 0)
           Generar(Numero);

        }
        else
        {
            for (unsigned int i = 0; i < Archivo.size();i++)
                Numero.push_back(i);
            Generar(Numero);
        }


       #ifdef WINDOWS
        SetFilePointer(Lectura,0,NULL,FILE_BEGIN);
       #else
        Lectura.seekg(0,ios::beg);
       #endif
    }
    if (Todos == false)
        return Numero.size(); // Devolvemos el numero de ficheros procesados
    else
        return Archivo.size();
}

void File_Mising::OrdenarVector(vector<unsigned int> &Numero)
{
     unsigned int i = 0;
     unsigned int j = 0;
     unsigned int temp;
     for (i = 0; i < (Numero.size()-1); i++)
    {
        for (j = i + 1; j < Numero.size(); j++)
        {
            if (Numero[j] < Numero[i])
            {
                temp = Numero[j];
                Numero[j] = Numero[i];
                Numero[i] = temp;
            }
        }
    }

}

// Destructor, basicamente lo que hace es cerrar los archivos abiertos

File_Mising::~File_Mising()
{
   CerrarArchivo(Lectura)
   CerrarArchivo(Escritura)
}

