#include "Lenguaje.hpp"

#ifdef WINDOWS
    #include <windows.h>
    #include <locale.h>
#endif

Lenguaje::Lenguaje(unsigned short idioma) : Idioma(idioma)
{

    switch (Idioma)
    {
        case Espanyol:
                Mensaje_Inicio = "Bienvenido a Rar File Missing, tu programa de esteganografia de archivos rar";
                Contacto = "Pueden contactar conmigo en la dirrecion de correo";
                Buscando = "Buscando archivos Rar en la carpeta...";

                Error_NoArchivos = "Error, no se ha encontrado ningun archivo";
                Error_BadEntry = "Error, entrada incorrecta";
                Error_Inesperado = "Error inesperado";
                Error_Parametros_por_consola = "Error, la sintaxis era: . Nombre_Fichero_Rar Modo mostrar/ocultar \n NombreArchivo1 NombreArchivo2 NombreArchivo3...";

                Seleccionar_Archivo = "Introduzca el numero de archivo que desea abrir:";

                Mensaje_Opcion = "Ocultar (0) o Mostrar (1)?";

                LoadingFiles = "Cargando archivos conforme a la opcion escogida...";
                WarningZip = "PRECAUCION: Los archivos zip se encuentran en fase de depuracion";

                Seleccionar_Numero_Archivo = "Indica el numero del archivo: ";
                Seleccionar_Numero_Archivo2 = "Indica otro archivo (introduzca 0 para terminar):";

                Finalizado = "El proceso ha finalizado correctamente";
                Press_One_Key = "Pulsa enter para salir...";

                break;

        case English:
                Mensaje_Inicio = "Welcome to Rar File Missing, your steganography software of rar files";
                Contacto = "You can contact me by email: ";
                Buscando = "Searching Files in the curent folder...";

                Error_NoArchivos = "Error, files not found";
                Error_BadEntry = "Error, bad entry";
                Error_Inesperado = "Error unexpected error";
                Error_Parametros_por_consola = "Error, sintax was: . Nombre_Fichero_Rar Modo mostrar/ocultar \n NombreArchivo1 NombreArchivo2 NombreArchivo3...";

                Seleccionar_Archivo = "Insert number of file for open:";

                Mensaje_Opcion = "Hide (0) or Show (1)?";

                LoadingFiles = "Loading files with current settings...";
                WarningZip = "WARNING: Zip files are EXPERIMENTAL";

                Seleccionar_Numero_Archivo = "Insert file number: ";
                Seleccionar_Numero_Archivo2 = "Insert another number file (insert 0 for end):";

                Finalizado = "Finished correctly";
                Press_One_Key = "Press enter for exit...";

                break;
    }
}

unsigned int Lenguaje::ObtenerIdiomaSistema()
{
    #ifdef WINDOWS
    char idioma[30]={0};
    GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SNATIVELANGNAME  , idioma,
    sizeof(idioma));

     if (idioma[0] == 'e' && idioma[1] == 's')
       return Espanyol;
    else
        return English;
    #else
    char* Informacion = getenv("LANG");

    if (Informacion[0] == 'e' && Informacion[1] == 's')
        return Espanyol;
    else
        return English;
    #endif
}
