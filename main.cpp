#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "SRC/Rar_File_Mising.hpp"
#include "SRC/Zip_File_Missing.hpp"

#define RAR 1
#define ZIP 2

#ifdef WINDOWS
#include <windows.h>
#else
#include <dirent.h>
#endif

using namespace std;

#include "SRC/Lenguaje.hpp"

/*  Cosas que hacer:

    Compatibilidad con archivos de tamaño ENORME
    Compatibilidad con rar a "trozos"
*/

string listarDirectorio(string Cosa,vector<string> &Archivos);
int Extension(string Nombre);

int main(int argc, char *argv[])
{
    bool Opcion; // Opcion a escoger
    vector<string> Archivos; // Lista de archivos Rar en la carpeta
    vector<unsigned int> Lista; // Lista de archivos a ocultar/desocultar
    unsigned short N_Archivos; // Numero de archivos que contiene el rar
    string Resultado; // String que contiene la lista de los archivos del rar en formato texto
    unsigned short Contador = 0; // Cuenta los archivos que llevo seleccionados
    int Numero = 0; // Variable auxiliar para leer los archivos que meto en la lista y tambien para seleccionar el archivo a abrir

    Lenguaje Idioma(Lenguaje::ObtenerIdiomaSistema());

    // Pantalla de bienvenida

    if (argc == 0 || argc == 1)
    {
        cout<<Idioma.GetMensaje_Inicio()<<endl;
        cout<<Idioma.GetContacto() + " miachm3@gmail.com"<<endl<<endl;

        cout<<Idioma.GetBuscando()<<endl<<endl;
        cout<<listarDirectorio("*",Archivos)<<endl;

        if (Archivos.size() == 0)
        {
            cout<<Idioma.GetError_NoArchivos()<<endl;
            cin.get();
            exit(-1);
        }
        if (Archivos.size() > 1)
        {
            cout<<Idioma.GetSeleccionar_Archivo() + " "<<endl;
            cin>>Numero;

            Numero--;
        }
        else
            Numero = 0;

        cout<<Idioma.GetMensaje_Opcion() + " "<<endl;
        cin>>Opcion;

        cout<<Idioma.GetLoading_Files()<<endl<<endl;

        // Una vez tomados los datos, empezamos con lo Hardcore

        try
        {
            /* Creamos un nuevo objeto de "File Mising". Le pasaremos como parametros
            el nombre de nuestro archivo Rar y la opcion que hemos escogido (ocultar o mostrar)*/

           File_Mising* Nuevo;

           if (Extension(Archivos[Numero]) == RAR)
               Nuevo = new Rar_File_Mising(Archivos[Numero],Opcion); // Si es un rar creamos el tipo Rar_File_Missing
           else if (Extension(Archivos[Numero]) == ZIP)
           {
                Nuevo = new Zip_File_Mising(Archivos[Numero],Opcion); // Si es un zip creamos el tipo Zip_File_Missing
                cout<<Idioma.GetWarningZip()<<endl<<endl;
           }

            N_Archivos = Nuevo->ListarArchivos(Resultado);

            if (N_Archivos != 0)
            {
                // Ahora mostramos todos los ficheros por pantalla:
                cout<<Resultado;

                // Toca ahora seleccionar los archivos que se van a usar

                cout<<endl<<Idioma.GetSeleccionar_Numero_Archivo() + " ";
                cin>>Numero;

                if ((Numero-1) < 0 || (Numero-1) > (Nuevo->NumeroDeArchivos()))
                {
                    cout<<Idioma.GetError_BadEntry()<<endl;
                }
                else
                {
                    Lista.push_back(Numero-1);
                    Contador = 1; // Reseteamos el contador de archivos escogidos
                }

                // Bucle para introducir los archivos, no se saldra de el hasta que se introduzca un cero

                do
                {
                    // Añadimos un nuevo archivo a la lista, en la primera entrada de bucle se guardara el archivo anteriormente proporcionado
                    cout<<endl<<Idioma.GetSeleccionar_Numero_Archivo2() + " ";
                    cin>>Numero;

                    if (Numero > 0 && Numero < (Nuevo->NumeroDeArchivos()+1))
                    {
                        Contador++; // Incrementamos el numero de archivos leidos
                        Lista.push_back(Numero-1);
                    }
                    else if (Numero != 0)
                        cout<<Idioma.GetError_BadEntry()<<endl;

                }while (Numero != 0 && Contador < N_Archivos);

                // Fin del bucle, Oculto/Muestro los archivos seleccionados
                Nuevo->Generar(Lista);

                delete Nuevo; // Borramos el objeto tras finalizar

                cout<<Idioma.GetFinalizado()<<endl<<endl; // Si no se ha lanzado ninguna excepcion
            }
            else
                cout<<Idioma.GetError_NoArchivos()<<endl;

            cout <<Idioma.GetPress_One_Key();
            cin.get();
            cin.get();
        }

        catch(Rar_File_Mising::Excepcion &E)
        {
            cout<<E.Mensaje<<endl;
        }
        catch(...)
        {
            cout<<Idioma.GetError_Inesperado()<<endl;
        }

    }

 else if (argc == 2)
        cout<<Idioma.GetError_Parametros_por_consola()<<endl<<endl;
    else
    {
        bool Modo;
        bool Todos;
        if (strcmp(argv[2],"ocultar") == 0 && argc > 2)
        {
            Modo = 0;
            Todos = 0;
        }
        else if (strcmp(argv[2],"mostrar") == 0 && argc > 2)
        {
            Modo = 1;
            Todos = 0;
        }
        else if (strcmp(argv[2],"ocultar/todos") == 0)
        {
            Modo = 0;
            Todos = 1;
        }
        else if (strcmp(argv[2],"mostrar/todos") == 0)
        {
            Modo = 1;
            Todos = 1;
        }
		else if (strcmp(argv[2],"Listar") == 0)
		{
			try
			{
				if (strcmp(argv[3],"0") == 0)
				{
					string cosa = argv[1];
					string mostrar;
					Rar_File_Mising Nuevo(cosa,0);
					cout<<nuevo.ListarArchivos(mostrar)<<endl;
					cout<<mostrar;
				}
				else
				{
					string cosa = argv[1];
					string mostrar;
					Rar_File_Mising Nuevo(cosa,1);
					cout<<nuevo.ListarArchivos(mostrar)<<endl;
					cout<<mostrar;
				}
				return 0;
			}
			catch(Rar_File_Mising::Excepcion &E)
			{
				cout<<E.Mensaje<<endl;
			}
			catch(...)
			{
				cout<<Idioma.GetError_Inesperado()<<endl;
			}
		}
        else
        {
                cout<<Idioma.GetError_Parametros_por_consola()<<endl<<endl;
                exit(-1);
        }
        try
        {
            string cosa = argv[1];
            Rar_File_Mising Nuevo(cosa,Modo);

            cout<<Nuevo.BuscarYEjecutar(argv,argc,Todos)<<Idioma.GetEncontrados_Y_Procesados();
        }
        catch(Rar_File_Mising::Excepcion &E)
        {
            cout<<E.Mensaje<<endl;
        }
        catch(...)
        {
            cout<<Idioma.GetError_Inesperado()<<endl;
        }
    }

    Archivos.clear();
    Lista.clear();

    //getline(cin,Nombre);

    return 0;
}

// Esta funcion lista todos los archivos rar de la carpeta

#ifdef WINDOWS

string listarDirectorio(string Cosa,vector<string> &Archivos)
{
    // Variables del sistema

    WIN32_FIND_DATA findFileData;
    HANDLE          hFind;

    string Devolver; // El string a devolver
    string Buffer; // Donde se van guardando los nombres de fichero antes de verificar que son rar
    unsigned int N = 1; // Para ir contando los archivos
    char* Auxiliar = new char; // Variable auxiliar para pasar N a string

    // Iniciamos la busqueda y le pasamos un valor a nuestro Handle

    hFind = FindFirstFile(Cosa.c_str(), &findFileData);

    // Si no existe la carpeta

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "La carpeta no existe";
    }

    else
    {

        // Listamos todos los ficheros

        while (FindNextFile(hFind, &findFileData) != 0)
        {
            Buffer = findFileData.cFileName; // Metemos su nombre en el buffer
            if (Extension(Buffer) != 0)
            {
                Archivos.push_back(findFileData.cFileName); // Si es un rar, lo metemos en la lista
                itoa(N,Auxiliar,10); // Para pasar de numero a char
                Devolver += Auxiliar; // Escribimos el numero de archivo
                Devolver += ": ";
                Devolver += findFileData.cFileName; // Y su nombre
                Devolver += "\n";
                N++;
            }

        }
    }
    delete Auxiliar;
    return Devolver;
}

#else

string listarDirectorio(string Cosa,vector<string> &Archivos)
{
    // Variables del sistema

    string Devolver; // El string a devolver
    string Buffer; // Donde se van guardando los nombres de fichero antes de verificar que son rar
    unsigned int N = 0; // Para ir contando los archivos
    char Buff[10];
    // Iniciamos la busqueda y le pasamos un valor a nuestro Handle

    DIR *dir;
    struct dirent *directorio;

    if((dir = opendir(".")) == NULL)
    {
        perror("La ruta especificada no existe.\n");
        exit(-1);
    }

    //printf("Listado de: %s\n\n", argv[1]);

    while((directorio = readdir(dir)) != NULL)
    {
        if((strcmp(directorio->d_name, ".") != 0) && (strcmp(directorio->d_name, "..") != 0))
        {
            Buffer = directorio->d_name;
            if (Extension(Buffer) != 0)
            {
                sprintf (Buff,"%d",N+1);
                Devolver += Buff;
                Devolver += ": ";
                Devolver += Buffer;
                Devolver += "\n";
                Archivos.push_back(Buffer);
                N++;
            }
        }
    }

    return Devolver;
}
#endif

int Extension(string Nombre)
{
    char Buffer[3];

    for (short i = 0; i < 4; i++)
        Buffer[i] = Nombre[Nombre.size()-3+i];

    if (strcmp(Buffer,"rar") == 0)
        return RAR;
    else if (strcmp(Buffer,"zip") == 0)
        return ZIP;
    else
        return 0;
}
