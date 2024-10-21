// "El proyecto"
// Se decidió crear un juego similar a Los Sims, y para esto se nos entregó la tarea de hacer una estructura de datos
// que permita guardar el diseño del vecindario. Esto permite que el vecindario sea cargado en memoria al momento de jugar
// y luego debería facilitar el guardado en disco del mismo.
// Cada vecindario debe poner tener muchas casas, donde cada casa pueda albergar muchos inquilinos y muebles dentro

// "El problema"
// Uno de nuestros compañeros realizó los algoritmos de inserción y eliminación de inquilinos
// Además, diseñó las estructuras de datos que usaremos en nuestro proyecto
// Ahora, nos está pidiendo que revisemos su código, ya que no logra que compile
// Finalmente, como equipo que somos, debemos avisarle también si encontramos alguna forma de mejorar la solución que nos propuso

// ¿La solución?
// De aqui en adelante, está el código de "nuestro compañero". ¡Éxitos!
// Asuman, por facilidad, que está todo el proyecto en un solo archivo y que aquí están tanto las funciones como el programa principal ("main")

//Librerías a utilizar
#include <iostream>
using namespace std;

//Estructuras de Datos
enum TipoMueble
{
    misc = -1,
    sofa = 0,
    silla = 1,
    mesa = 2,
    lampara = 3,
    ventana = 4,
    cama = 5
};

struct NodoMueble
{
    string material; //Para calcular los eventos de "incendio" es importante saber si los muebles son de madera, plástico, acero, caucho, tela...
    TipoMueble tipo;
    float precio;

    NodoMueble* prox;
};

struct NodoInquilino
{
    string nombre;
    string trabajo; //Al igual que en Los Sims, cada persona puede tener un trabajo; es necesario guardar esos datos entre partidas

    NodoInquilino* prox;
    NodoInquilino* prev;
    NodoMueble* interno;
};

struct NodoCasa
{
    string nombre;
    float precio;
    string tipoCasa; //Hay diferencias en el juego si es un edificio, una casa de un piso, casa de dos pisos, cabaña, chalet...

    NodoCasa* prox;
    NodoInquilino* interno;
};

struct NodoVecindario
{
    string cod_postal;
    int poblacion;

    NodoVecindario* prox;
    NodoVecindario* prev;
    NodoCasa* cabezaCasa;
};

// Funciones
// Crear objetos
NodoVecindario* crearVecindario (string cod_postal, int poblacion)
{
    NodoVecindario* nuevo = new NodoVecindario;
    nuevo->cod_postal = cod_postal;
    nuevo->poblacion = poblacion;

    return nuevo;
}
NodoCasa* crearCasa (string nombre, float precio, string tipoCasa)
{
    NodoCasa* nuevo = new NodoCasa;
    nuevo->nombre = nombre;
    nuevo->precio = precio;
    nuevo->tipoCasa = tipoCasa;
    
    return nuevo;
}
NodoInquilino* crearInquilino (string nombre, string trabajo)
{
    NodoInquilino* nuevo = new NodoInquilino;
    nuevo->nombre = nombre;
    nuevo->trabajo = trabajo;

    nuevo->prev = NULL;
    nuevo->prox = NULL;
    nuevo->interno = NULL;

    return nuevo;
}
NodoMueble* crearMueble (string material, TipoMueble tipo, float precio)
{
    NodoMueble* nuevo = new NodoMueble;
    nuevo->material = material;
    nuevo->tipo = tipo;
    nuevo->precio = precio;

    nuevo->prox = NULL;

    return nuevo;
}

// Insertar/Eliminar
//Inserto al nuevo inquilino en la casa indicada por el nodo dado
void insertarInquilino(NodoVecindario** vecindarioPtr, NodoCasa* casaObj, NodoInquilino* nuevo)
{
    bool insertado = false;
    NodoVecindario* vecindario = *vecindarioPtr;
    while ( (vecindario != NULL)&&(!insertado) )
    {
        NodoCasa* casaActual = vecindario->cabezaCasa;
        while ( (casaActual != NULL)&&(!insertado) )
        {
            if (casaActual == casaObj) //Encontre la casa donde deseo insertar al nuevo inquilino
            {
                NodoInquilino* inquilinoActual = casaActual->interno;
                if (inquilinoActual == NULL)
                {
                    casaActual->interno = nuevo;
                    insertado = true;
                    cout << "Inquilino insertado con exito\n";
                    break;
                }
                else
                {
                    while (inquilinoActual->prox != NULL)
                    {
                        inquilinoActual = inquilinoActual->prox; 
                    }
                    //Estoy ubicado en el ultimo inquilino de esa casa, puedo insertar
                    inquilinoActual->prox = nuevo;
                    nuevo->prev = inquilinoActual;
                    insertado = true;
                    cout << "Inquilino insertado con exito\n";
                }
            }
            casaActual = casaActual->prox;
        }
        vecindario = vecindario->prox;
    }
    if (!insertado)
    {
        cout << "No se ha logrado insertar al inquilino\n";
    }
}

//Elimino a un inquilino dado su nombre
void eliminarInquilinoNombre(NodoVecindario** vecindarioPtr, string nombre)
{
    bool eliminado = false;
    NodoVecindario* vecindario = *vecindarioPtr;
    while ( (vecindario != NULL)&&(!eliminado) )
    {
        NodoCasa* casaActual = vecindario->cabezaCasa;
        while ( (casaActual != NULL)&&(!eliminado) )
        {
            NodoInquilino* inquilinoActual = casaActual->interno;
            while ( (inquilinoActual != NULL)&&(!eliminado) )
            {
                if (inquilinoActual->nombre == nombre) //Encontre al inquilino que deseo eliminar
                {
                    (inquilinoActual->prev)->prox = inquilinoActual->prox;
                    (inquilinoActual->prox)->prev = inquilinoActual->prev;
                    eliminado = true;
                    cout << "Eliminado con exito\n";
                }
                inquilinoActual = inquilinoActual->prox; 
            }
            casaActual = casaActual->prox;
        }
        vecindario = vecindario->prox;
    }
    if (!eliminado)
    {
        cout << "No se ha logrado eliminar al inquilino\n";
    }
}

//Elimino a un inquilino dado su trabajo
void eliminarInquilinoTrabajo(NodoVecindario** vecindarioPtr, string trabajo)
{
    bool eliminado = false;
    NodoVecindario* vecindario = *vecindarioPtr;
    while ( (vecindario != NULL)&&(!eliminado) )
    {
        NodoCasa* casaActual = vecindario->cabezaCasa;
        while ( (casaActual != NULL)&&(!eliminado) )
        {
            NodoInquilino* inquilinoActual = casaActual->interno;
            while ( (inquilinoActual != NULL)&&(!eliminado) )
            {
                if (inquilinoActual->trabajo == trabajo) //Encontre al inquilino que deseo eliminar
                {
                    (inquilinoActual->prev)->prox = inquilinoActual->prox;
                    (inquilinoActual->prox)->prev = inquilinoActual->prev;
                    eliminado = true;
                    cout << "Eliminado con exito\n";
                }
                inquilinoActual = inquilinoActual->prox; 
            }
            casaActual = casaActual->prox;
        }
        vecindario = vecindario->prox;
    }
    if (!eliminado)
    {
        cout << "No se ha logrado eliminar al inquilino\n";
    }
}

// Mostrar estructura
void imprimirVecindario(NodoVecindario* vecindario)
{
    cout << "MIS VECINDARIOS\n";
    while (vecindario != NULL)
    {
        cout << "Codigo Postal " << vecindario->cod_postal << ". Poblacion " << vecindario->poblacion << "\n";

        NodoCasa* casaActual = vecindario->cabezaCasa;
        while (casaActual != NULL)
        {
            cout << "  " << casaActual->tipoCasa << " '" << casaActual->nombre << "' [Valor " << casaActual->precio << "$]\n";

            NodoInquilino* inquilinoActual = casaActual->interno;
            while (inquilinoActual != NULL)
            {
                cout << "    " << inquilinoActual->nombre << " (" << inquilinoActual ->trabajo << ")\n";
                
                inquilinoActual = inquilinoActual->prox; 
            }
            casaActual = casaActual->prox;
        }
        vecindario = vecindario->prox;
    }
}

// Programa principal
int main()
{
    //Crear vecindario de prueba
    NodoVecindario* prueba = crearVecindario("1061", 0);
    NodoCasa* miCasita = crearCasa("mi casita", 90, "Apartamento");
    prueba->cabezaCasa = miCasita;

    //Insertar tres inquilinos a mi casita
    insertarInquilino(&prueba, miCasita, crearInquilino("Pedro", "Profesor"));
    insertarInquilino(&prueba, miCasita, crearInquilino("Maria", "artista"));
    insertarInquilino(&prueba, miCasita, crearInquilino("Luis", "COCINERO"));
    imprimirVecindario(prueba);

    //Eliminar a Maria
    eliminarInquilinoNombre(&prueba, "Maria");
    imprimirVecindario(prueba);

    //Eliminar al profesor
    eliminarInquilinoTrabajo(&prueba, "profesor");
    imprimirVecindario(prueba);

    return 0;
}