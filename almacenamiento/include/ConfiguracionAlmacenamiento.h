#pragma once

// stl
#include <string>

namespace almacenamiento
{
class ConfiguracionAlmacenamiento
{
public:

    ConfiguracionAlmacenamiento(std::string path_archivo_configuracion = "");
    virtual ~ConfiguracionAlmacenamiento();

    // METODOS

    void leerConfiguracion(std::string path_archivo_configuracion);

    // CONFIGURACIONES

    std::string pathDB();

    void pathDB(std::string path_db);

    bool almacenamientoLocal();
    bool almacenamientoDistribuido();

    std::string archivoConfigLog();

    // TAGS

    std::string tagPathDB();
    std::string tagAlmacenamientoLocal();
    std::string tagAlmacenamientoDistribuido();
    std::string tagArchivoConfigLog();

private:

    std::string path_db;
    bool almacenamiento_local;
    bool almacenamiento_distribuido;
    std::string archivo_config_log;
};
};
