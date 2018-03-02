#include <almacenamiento/include/ImposibleCerrarAlmacenamiento.h>

using namespace almacenamiento::excepciones;

ImposibleCerrarAlmacenamiento::ImposibleCerrarAlmacenamiento(std::string nombre_db) : Excepcion("almacenamiento{ path_db = '" + nombre_db + "'}: imposible cerrar.")
{
}

ImposibleCerrarAlmacenamiento::~ImposibleCerrarAlmacenamiento()
{
}
