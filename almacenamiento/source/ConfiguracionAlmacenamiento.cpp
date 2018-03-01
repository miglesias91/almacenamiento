#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>

using namespace almacenamiento;

// stl
#include <fstream>
#include <sstream>

// utiles
#include <utiles/include/Json.h>
#include <utiles/include/JsonMalFormado.h>
#include <utiles/include/ImposibleAbrirArchivo.h>

ConfiguracionAlmacenamiento::ConfiguracionAlmacenamiento(std::string path_archivo_configuracion)
{
    if (false == path_archivo_configuracion.empty())
    {
        this->leerConfiguracion(path_archivo_configuracion);
    }
}

ConfiguracionAlmacenamiento::~ConfiguracionAlmacenamiento()
{
}

void ConfiguracionAlmacenamiento::leerConfiguracion(std::string path_archivo_configuracion)
{
    std::ifstream archivo(path_archivo_configuracion);

    if (false == archivo.good())
    {
        throw herramientas::utiles::excepciones::ImposibleAbrirArchivo(path_archivo_configuracion);
    }

    std::ostringstream sstream;
    sstream << archivo.rdbuf();
    const std::string string_config(sstream.str());

    herramientas::utiles::Json * config_json = NULL;
    herramientas::utiles::Json * config_almacenamiento_json = NULL;

    try
    {
        config_json = new herramientas::utiles::Json(string_config);
        config_almacenamiento_json = config_json->getAtributoValorJson("almacenamiento");

        this->path_db = config_almacenamiento_json->getAtributoValorString(ConfiguracionAlmacenamiento::tagPathDB());
        this->almacenamiento_local = config_almacenamiento_json->getAtributoValorBool(ConfiguracionAlmacenamiento::tagAlmacenamientoLocal());
        this->almacenamiento_distribuido = config_almacenamiento_json->getAtributoValorBool(ConfiguracionAlmacenamiento::tagAlmacenamientoDistribuido());
        this->archivo_config_log = config_almacenamiento_json->getAtributoValorString(ConfiguracionAlmacenamiento::tagArchivoConfigLog());
    }
    catch (herramientas::utiles::excepciones::Excepcion & e)
    {
        delete config_almacenamiento_json;
        delete config_json;

        throw;
    }

    delete config_almacenamiento_json;
    delete config_json;
}

bool ConfiguracionAlmacenamiento::almacenamientoLocal()
{
	return this->almacenamiento_local;
}

bool ConfiguracionAlmacenamiento::almacenamientoDistribuido()
{
	return this->almacenamiento_distribuido;
}

std::string ConfiguracionAlmacenamiento::archivoConfigLog()
{
    return this->archivo_config_log;
}

std::string ConfiguracionAlmacenamiento::pathDB()
{
	return this->path_db;
}

void ConfiguracionAlmacenamiento::pathDB(std::string path_db)
{
    this->path_db = path_db;
}

std::string ConfiguracionAlmacenamiento::tagPathDB()
{
	return "path_db";
}

std::string ConfiguracionAlmacenamiento::tagAlmacenamientoLocal()
{
	return "almacenamiento_local";
}

std::string ConfiguracionAlmacenamiento::tagAlmacenamientoDistribuido()
{
	return "almacenamiento_distribuido";
}

std::string ConfiguracionAlmacenamiento::tagArchivoConfigLog()
{
    return "log_db";
}
