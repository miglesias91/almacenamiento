#pragma once

// utiles
#include <utiles/include/Excepcion.h>

namespace almacenamiento
{
namespace excepciones
{

class ImposibleCerrarAlmacenamiento : public herramientas::utiles::excepciones::Excepcion
{
public:
    ImposibleCerrarAlmacenamiento(std::string nombre_db = "");
    virtual ~ImposibleCerrarAlmacenamiento();
};

};
};

