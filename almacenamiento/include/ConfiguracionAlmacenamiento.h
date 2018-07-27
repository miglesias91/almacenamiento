#pragma once

// stl
#include <string>

namespace almacenamiento
{
class ConfiguracionAlmacenamiento
{
public:

    ConfiguracionAlmacenamiento(const std::string & path_archivo_configuracion = "");
    virtual ~ConfiguracionAlmacenamiento();

    // METODOS
    void leerConfiguracion(std::string path_archivo_configuracion);

    // CONFIGURACIONES
    void pathDB(const std::string & path_db);
    void almacenamientoLocal(bool local);
    void almacenamientoDistribuido(bool distribuido);
    void soloLectura(bool solo_lectura);
    void archivoConfigLog(const std::string& path);

    std::string pathDB() const;
    bool almacenamientoLocal() const;
    bool almacenamientoDistribuido() const;
    bool soloLectura() const;
    std::string archivoConfigLog() const;

    // TAGS
    std::string tagPathDB();
    std::string tagAlmacenamientoLocal();
    std::string tagAlmacenamientoDistribuido();
    std::string tagSoloLectura();
    std::string tagArchivoConfigLog();

private:

    std::string path_db;
    bool almacenamiento_local;
    bool almacenamiento_distribuido;
    bool solo_lectura;
    std::string archivo_config_log;
};
};
