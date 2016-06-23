/* Funcion auxiliar para comprobar la firma del nombre 20 00 00 00 */
#include "Rar_File_Mising.hpp"

#include <string>
#include <sstream>
#define InicializarVariables unsigned long long Buffer = 0; unsigned long long Posicion = 22;unsigned int N = 0;unsigned char Tamanyo_Archivo; char Leer[256] = {0};

unsigned int Rar_File_Mising::ListarArchivos(string &Resultado)
{
    // Empezamos la parafernaria. Lo primero es verificar que el archivo de Lectura esta abierto

    if (ComprobarArchivoNoAbierto(Lectura))
        throw Excepcion("No hay ningun fichero abierto",ARCHIVO_NO_ABIERTO);

    // Lo segundo, es declarar las variables de control

    Variable_Progueso
    Variable_Tamanyo(Tamanyo_Nombre)

    MoverA(Lectura,22)

    InicializarVariables

    do
    {
                Read(Lectura,Leer,1)

                Posicion++; // Avanzamos una posicion

				if ((*Leer == 't' && Modo == 0) || (*Leer ==  Oculto && Modo == 1))
                {
                    /* Todo archivo no-oculto estara precedido por una 't', por lo que
                    tendremos que guardar las dirreciones de la 't', puesto que puede venir
                    un futuro archivo. En caso que este en modo oculto sera un 1 */

					Buffer = Posicion-1;
                }

                /* Comprobamos si encontramos los hexadecimales 20 00 00 00 que indica que se acerca un nuevo nombre.*/

				if (ComprobarFirmaNombre(Leer))
				{
				    // Ahora toca leer el tamanyo del archivo, movemos el puntero de archivo a dicha dirrecion
                    //cout<<"Miau"<<endl;
					unsigned long long aux = Posicion-25;

                    MoverA(Lectura,aux)

					/* Pequeña operacion para transformar los 4 bytes que indican su tamanyo teniendo
					en cuenta que se leen en orden inverso */

					unsigned int parapotencia = 1;
					unsigned int rest = 0;

					for(short k = 0; k <4; k++)
                    {
                        Read(Lectura,Leer,1)

						rest += Tamanyo_Archivo*parapotencia;
						parapotencia =parapotencia*256;
					}

					/* Asi mismo comprobaremos si 30 caracteres antes teniamos el byte clave (recordamos que Buffer apunta
                al ultimo byte clave lo contiene buffer). Si no se encontro es posible estemos ante
                un fichero oculto */

					if ((Posicion-30) == Buffer)
                    {

                        Archivo.push_back(Posicion); // Guardo el valor de nuestra posicion en el vector de archivos
                        Archivo[N] -= 30; // Y le restamos 30 para que apunte al caracter t...

                        /* Variable auxiliar para trabajar con los saltos aleatorios de archivo, por defecto
                         apuntara al byte que indica el tamaño de nobre */

                        aux = Archivo[N]+24;

                        // Movemos el puntero de archivo alli y leemos

                        MoverA(Lectura,aux)
                        Read(Lectura,&Tamanyo_Nombre,1)

                        // Ya tenemos todos los datos, volvemos a apuntar al nombre del archivo

                        aux = Archivo[N]+30;

                        MoverA(Lectura,aux)

                        // Mostramos el numero de archivo actual

                        stringstream Buff; // Variable auxiliar
                        Buff<<N+1<<": "; // Para pasar de numero a char
                        string bufff = Buff.str();
                        Resultado += bufff; // Escribimos el numero

                        //delete Buff; // Borrar variable auxiliar

                        // Ahora leemos el nombre

                        Read(Lectura,Leer,Tamanyo_Nombre)

                        /* Y lo mostramos en pantalla, debe ser elemento a elemento o mostraria los 256
                        caracteres del tiron */

                        for (short i = 0; i < Tamanyo_Nombre;i++)
                                Resultado +=Leer[i];

                        // Aumentamos el indicador de posicion

                        Posicion+= Tamanyo_Nombre;

                        Resultado += "\n"; // Salto de linea
                        N++;
                    }

                    // Queremos saltarnos el contenido del archivo puesto que nos interesa (recordamos que rest equivale a su tamaño)
                    aux = Posicion+rest;

                    // Si no nos pasamos el fichero

                    if (aux < Tamanyo)
                    {
                         MoverA(Lectura,aux)

                         Posicion += rest; // Actualizamos posicion
                    }

                    else // Si excedemos el fin de fichero, damos por terminada la tarea
                        break;

                }

    } while(Posicion < Tamanyo);

    MoverA(Lectura,0)

    return N; // Devolvemos el string con los ficheros
}

unsigned int Rar_File_Mising::ListarArchivos(vector<string> &Resultado)
{
    // Empezamos la parafernaria. Lo primero es verificar que el archivo de Lectura esta abierto

    if (ComprobarArchivoNoAbierto(Lectura))
        throw Excepcion("No hay ningun fichero abierto",ARCHIVO_NO_ABIERTO);

    // Lo segundo, es declarar las variables de control

    Variable_Progueso
    Variable_Tamanyo(Tamanyo_Nombre)

    MoverA(Lectura,22)

    InicializarVariables

    do
    {
                Read(Lectura,Leer,1)

                Posicion++; // Avanzamos una posicion

				if ((*Leer == 't' && Modo == 0) || (*Leer ==  Oculto && Modo == 1))
                {
                    /* Todo archivo no-oculto estara precedido por una 't', por lo que
                    tendremos que guardar las dirreciones de la 't', puesto que puede venir
                    un futuro archivo. En caso que este en modo oculto sera un 1 */

					Buffer = Posicion-1;
                }

                /* Comprobamos si encontramos los hexadecimales 20 00 00 00 que indica que se acerca un nuevo nombre.*/

				if (ComprobarFirmaNombre(Leer))
				{
				    // Ahora toca leer el tamanyo del archivo, movemos el puntero de archivo a dicha dirrecion

					unsigned long long aux = Posicion-25;

                    MoverA(Lectura,aux)

					/* Pequeña operacion para transformar los 4 bytes que indican su tamanyo teniendo
					en cuenta que se leen en orden inverso */

					unsigned int parapotencia = 1;
					unsigned int rest = 0;

					for(short k = 0; k <4; k++)
                    {
                        Read(Lectura,Leer,1)

						rest += Tamanyo_Archivo*parapotencia;
						parapotencia =parapotencia*256;
					}

					/* Asi mismo comprobaremos si 30 caracteres antes teniamos el byte clave (recordamos que Buffer apunta
                al ultimo byte clave lo contiene buffer). Si no se encontro es posible estemos ante
                un fichero oculto */

					if ((Posicion-30) == Buffer)
                    {
                        string Texto_Enviar;

                        Archivo.push_back(Posicion); // Guardo el valor de nuestra posicion en el vector de archivos
                        Archivo[N] -= 30; // Y le restamos 30 para que apunte al caracter t...

                        /* Variable auxiliar para trabajar con los saltos aleatorios de archivo, por defecto
                         apuntara al byte que indica el tamaño de nobre */

                        aux = Archivo[N]+24;

                        // Movemos el puntero de archivo alli y leemos

                        MoverA(Lectura,aux)
                        Read(Lectura,&Tamanyo_Nombre,1)

                        // Ya tenemos todos los datos, volvemos a apuntar al nombre del archivo

                        aux = Archivo[N]+30;

                        MoverA(Lectura,aux)

                        // Ahora leemos el nombre

                        Read(Lectura,Leer,Tamanyo_Nombre)

                        /* Y lo mostramos en pantalla, debe ser elemento a elemento o mostraria los 256
                        caracteres del tiron */

                        for (short i = 0; i < Tamanyo_Nombre;i++)
                                Texto_Enviar +=Leer[i];

                        // Aumentamos el indicador de posicion

                        Posicion+= Tamanyo_Nombre;

                        Resultado.push_back(Texto_Enviar);
                        N++;
                    }

                    // Queremos saltarnos el contenido del archivo puesto que nos interesa (recordamos que rest equivale a su tamaño)
                    aux = Posicion+rest;

                    // Si no nos pasamos el fichero

                    if (aux < Tamanyo)
                    {
                         MoverA(Lectura,aux)

                         Posicion += rest; // Actualizamos posicion
                    }

                    else // Si excedemos el fin de fichero, damos por terminada la tarea
                        break;

                }

    } while(Posicion < Tamanyo);

    MoverA(Lectura,0)

    return N; // Devolvemos el string con los ficheros
}

unsigned int Rar_File_Mising::ListarArchivos(vector<string> &Resultado_Visibles,vector<string> &Resultado_Ocultos)
{

    // Empezamos la parafernaria. Lo primero es verificar que el archivo de Lectura esta abierto

    if (ComprobarArchivoNoAbierto(Lectura))
        throw Excepcion("No hay ningun fichero abierto",ARCHIVO_NO_ABIERTO);

    // Lo segundo, es declarar las variables de control

    Variable_Progueso
    Variable_Tamanyo(Tamanyo_Nombre)

    MoverA(Lectura,22)

    InicializarVariables

    bool tipo;

    do
    {
                Read(Lectura,Leer,1)

                Posicion++; // Avanzamos una posicion

				if (*Leer == 't')
                {
                    tipo  = false;
                    Buffer = Posicion-1;
                }
                if (*Leer ==  Oculto)
                {
                    /* Todo archivo no-oculto estara precedido por una 't', por lo que
                    tendremos que guardar las dirreciones de la 't', puesto que puede venir
                    un futuro archivo. En caso que este en modo oculto sera un 1 */

                    tipo  = true;
					Buffer = Posicion-1;
                }

                /* Comprobamos si encontramos los hexadecimales 20 00 00 00 que indica que se acerca un nuevo nombre.*/

				if (ComprobarFirmaNombre(Leer))
				{
				    // Ahora toca leer el tamanyo del archivo, movemos el puntero de archivo a dicha dirrecion

					unsigned long long aux = Posicion-25;

                    MoverA(Lectura,aux)

					/* Pequeña operacion para transformar los 4 bytes que indican su tamanyo teniendo
					en cuenta que se leen en orden inverso */

					unsigned int parapotencia = 1;
					unsigned int rest = 0;

					for(short k = 0; k <4; k++)
                    {
                        Read(Lectura,Leer,1)

						rest += Tamanyo_Archivo*parapotencia;
						parapotencia =parapotencia*256;
					}

					/* Asi mismo comprobaremos si 30 caracteres antes teniamos el byte clave (recordamos que Buffer apunta
                al ultimo byte clave lo contiene buffer). Si no se encontro es posible estemos ante
                un fichero oculto */

					if ((Posicion-30) == Buffer)
                    {
                        string Texto_Enviar;

                        Archivo.push_back(Posicion); // Guardo el valor de nuestra posicion en el vector de archivos
                        Archivo[N] -= 30; // Y le restamos 30 para que apunte al caracter t...

                        /* Variable auxiliar para trabajar con los saltos aleatorios de archivo, por defecto
                         apuntara al byte que indica el tamaño de nobre */

                        aux = Archivo[N]+24;

                        // Movemos el puntero de archivo alli y leemos

                        MoverA(Lectura,aux)
                        Read(Lectura,&Tamanyo_Nombre,1)

                        // Ya tenemos todos los datos, volvemos a apuntar al nombre del archivo

                        aux = Archivo[N]+30;

                        MoverA(Lectura,aux)

                        // Ahora leemos el nombre

                        Read(Lectura,Leer,Tamanyo_Nombre)

                        /* Y lo mostramos en pantalla, debe ser elemento a elemento o mostraria los 256
                        caracteres del tiron */

                        for (short i = 0; i < Tamanyo_Nombre;i++)
                                Texto_Enviar +=Leer[i];

                        // Aumentamos el indicador de posicion

                        Posicion+= Tamanyo_Nombre;

                        if (tipo == true)
                            Resultado_Visibles.push_back(Texto_Enviar);
                        else if (tipo == false)
                                Resultado_Ocultos.push_back(Texto_Enviar);
                        N++;
                    }

                    // Queremos saltarnos el contenido del archivo puesto que nos interesa (recordamos que rest equivale a su tamaño)
                    aux = Posicion+rest;

                    // Si no nos pasamos el fichero

                    if (aux < Tamanyo)
                    {
                         MoverA(Lectura,aux)

                         Posicion += rest; // Actualizamos posicion
                    }

                    else // Si excedemos el fin de fichero, damos por terminada la tarea
                        break;

                }

    } while(Posicion < Tamanyo);

    MoverA(Lectura,0)

    return N; // Devolvemos el string con los ficheros
}

/* Funcion auxiliar para comprobar la firma del nombre 20 00 00 00
o bien B4 81 00 00 */

bool Rar_File_Mising::ComprobarFirmaNombre(const char* Leer) const
{
    static short Aciertos = 0;

    if (Aciertos == 3)
    {
        Aciertos = 0;

        if (*Leer == 0)
            return true;
    }

    if (Aciertos == 2)
            if (*Leer == 0)
						Aciertos++;
            else
						Aciertos = 0;

    if (Aciertos == 1)
            if (*Leer == 0 || *Leer == -127)
						Aciertos++;
            else
						Aciertos = 0;

    if ((*Leer == ' ' && Aciertos == 0) || (*Leer == -76 && Aciertos == 0))
                Aciertos++;

    return false;
}

void Rar_File_Mising::Generar(vector<unsigned int> Numero)
{
    if (Archivo.size() == 0)
        throw Excepcion("Error, no se ha creado ninguna lista de archivos o no existen archivos.",SIN_ARCHIVOS);

    AbrirArchivo(Escritura,Nombre.c_str(),Modo_Escritura)

    if (ComprobarArchivoNoAbierto(Escritura))
        throw Excepcion("Error al crear el fichero",ERROR_DE_APERTURA);

    Variable_Progueso

    CerrarArchivo(Lectura)

    short Porcentaje = 0;
    unsigned long long Posicion = 0;
    unsigned long long Contador_Progueso = 0;
    unsigned long long Contador_Porcentaje = 0;
    unsigned long long Aumento_Porcentaje = Tamanyo/100;
    unsigned long long Tamanyo_Lectura;
    unsigned int j = 0;

    char Leer;

    if (Modo == 0)
        Leer = Oculto;
    else
        Leer = 't';

    OrdenarVector(Numero);

    do
    {
        MoverAEsc(Escritura,Archivo[Numero[j]])

        Write(Escritura,&Leer,1)

        j++;
    }
    while(j < Numero.size());

    CerrarArchivo(Escritura)

}

void Rar_File_Mising::Generar(vector<unsigned int> Ocultar,vector<unsigned int> Mostrar)
{
    if (Archivo.size() == 0)
        throw Excepcion("Error, no se ha creado ninguna lista de archivos o no existen archivos.",SIN_ARCHIVOS);

    if (Ocultar.size() == 0 && Mostrar.size() != 0)
    {
        Generar(Mostrar);
        return;
    }
    else if (Mostrar.size() == 0 && Ocultar.size() != 0)
    {
        Generar(Ocultar);
        return;
    }
    else if (Mostrar.size() == 0 && Ocultar.size() == 0)
        throw Excepcion("Error, la lista de archivos proporcionadas estan vacías.",SIN_ARCHIVOS);

    AbrirArchivo(Escritura,Nombre.c_str(),Modo_Escritura)

    if (ComprobarArchivoNoAbierto(Escritura))
        throw Excepcion("Error al crear el fichero",ERROR_DE_APERTURA);

    Variable_Progueso

    CerrarArchivo(Lectura)

    short Porcentaje = 0;
    unsigned long long Posicion = 0;
    unsigned long long Contador_Progueso = 0;
    unsigned long long Contador_Porcentaje = 0;
    unsigned long long Aumento_Porcentaje = Tamanyo/100;
    unsigned long long Tamanyo_Lectura;
    unsigned int j = 0;

    char Leer;

    OrdenarVector(Ocultar);
    OrdenarVector(Mostrar);

    do
    {
        MoverAEsc(Escritura,Archivo[Ocultar[j]])

        Write(Escritura,&Oculto,1)

        j++;
    }
    while(j < Ocultar.size());

    j = 0;

    const char Signo_Mostrado = 't';

    do
    {
        MoverAEsc(Escritura,Archivo[Mostrar[j]])

        Write(Escritura,&Signo_Mostrado,1)

        j++;
    }
    while(j < Mostrar.size());

    CerrarArchivo(Escritura)
}
