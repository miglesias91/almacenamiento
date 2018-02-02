#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>

using namespace almacenamiento;

// stl
#include <fstream>
#include <sstream>

// rapidjson
#include <rapidjson/document.h>

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
        throw - 1;
    }

    std::ostringstream sstream;
    sstream << archivo.rdbuf();
    const std::string string_config(sstream.str());

    rapidjson::Document config_json;
    config_json.Parse(string_config.c_str());

    rapidjson::Value & config_almacenamiento_json = config_json["almacenamiento"];

    this->path_db = config_almacenamiento_json[ConfiguracionAlmacenamiento::tagPathDB().c_str()].GetString();
    this->almacenamiento_local = config_almacenamiento_json[ConfiguracionAlmacenamiento::tagAlmacenamientoLocal().c_str()].GetBool();
    this->almacenamiento_distribuido = config_almacenamiento_json[ConfiguracionAlmacenamiento::tagAlmacenamientoDistribuido().c_str()].GetBool();
}

bool ConfiguracionAlmacenamiento::almacenamientoLocal()
{
	return this->almacenamiento_local;
}

bool ConfiguracionAlmacenamiento::almacenamientoDistribuido()
{
	return this->almacenamiento_distribuido;
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
