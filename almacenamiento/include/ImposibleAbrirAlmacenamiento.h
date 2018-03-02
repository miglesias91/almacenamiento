#pragma once

// utiles
#include <utiles/include/Excepcion.h>

namespace almacenamiento
{
namespace excepciones
{

class ImposibleAbrirAlmacenamiento : public herramientas::utiles::excepciones::Excepcion
{
public:
    ImposibleAbrirAlmacenamiento(std::string nombre_db = "");
    virtual ~ImposibleAbrirAlmacenamiento();
};

};
};

