#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

using namespace almacenamiento;

// stl
#include <algorithm>
#include <iostream>

// almacenamiento
#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>
#include <almacenamiento/include/AlmacenamientoIniciadoPreviamente.h>
#include <almacenamiento/include/AlmacenamientoNoInicializado.h>

// utiles
#include <utiles/include/Excepcion.h>

std::unordered_map<uintmax_t, IAdministradorAlmacenamiento*> IAdministradorAlmacenamiento::mapa_administradores;

IAdministradorAlmacenamiento::IAdministradorAlmacenamiento(ConfiguracionAlmacenamiento * configuracion) : configuracion(configuracion), log(nullptr)
{
    this->log = herramientas::log::AdministradorLog::iniciarNuevo(configuracion->archivoConfigLog());
}

IAdministradorAlmacenamiento::~IAdministradorAlmacenamiento()
{
    if (nullptr != this->configuracion)
    {
        delete this->configuracion;
        this->configuracion = nullptr;
    }

    herramientas::log::AdministradorLog::liberarLogger(this->log->getNombre());
}

uintmax_t almacenamiento::IAdministradorAlmacenamiento::iniciarNuevo(const ConfiguracionAlmacenamiento & configuracion)
{
    ConfiguracionAlmacenamiento * config = new ConfiguracionAlmacenamiento();
    config->pathDB(configuracion.pathDB());
    config->almacenamientoLocal(configuracion.almacenamientoLocal());
    config->almacenamientoDistribuido(configuracion.almacenamientoDistribuido());
    config->soloLectura(configuracion.soloLectura());
    config->archivoConfigLog(configuracion.archivoConfigLog());

    std::hash<std::string> hasheador;

    uintmax_t handler_admin = hasheador(config->pathDB());

    if (administradorIniciado(handler_admin))
    {
        delete config;

        throw excepciones::AlmacenamientoIniciadoPreviamente(config->pathDB());
    }

    if (config->almacenamientoLocal())
    {
        crearAdministradorAlmacenamientoLocal(handler_admin, config);
    }
    else
    {
        crearAdministradorAlmacenamientoDistribuido(handler_admin, config);
    }

    return handler_admin;
}

uintmax_t IAdministradorAlmacenamiento::iniciarNuevo(const std::string & path_configuracion)
{
    ConfiguracionAlmacenamiento * config = nullptr;
    try
    {
        config = new ConfiguracionAlmacenamiento(path_configuracion);
    }
    catch (herramientas::utiles::excepciones::Excepcion & e)
    {
        throw;
    }

    std::hash<std::string> hasheador;

    uintmax_t handler_admin = hasheador(config->pathDB());

    if (administradorIniciado(handler_admin))
	{
        delete config;

        throw excepciones::AlmacenamientoIniciadoPreviamente(config->pathDB());
	}

	if (config->almacenamientoLocal())
	{
		crearAdministradorAlmacenamientoLocal(handler_admin, config);
	}
	else
	{
		crearAdministradorAlmacenamientoDistribuido(handler_admin, config);
	}

    return handler_admin;
}

void IAdministradorAlmacenamiento::liberarTodos()
{
    for (std::unordered_map<uintmax_t, IAdministradorAlmacenamiento*>::iterator it = mapa_administradores.begin(); it != mapa_administradores.end(); it++)
    {
        delete it->second;
    }

    mapa_administradores.clear();

    herramientas::log::AdministradorLog::liberarTodo();
}

void IAdministradorAlmacenamiento::liberar(uintmax_t handler)
{
	if (true == administradorIniciado(handler))
	{
		delete mapa_administradores[handler];
        mapa_administradores.erase(handler);
	}
}

void IAdministradorAlmacenamiento::crearAdministradorAlmacenamientoLocal(uintmax_t handler, ConfiguracionAlmacenamiento * configuracion)
{
    IAdministradorAlmacenamiento * administrador = new AdministradorAlmacenamientoLocal(configuracion);

    mapa_administradores[handler] = administrador;
}

void IAdministradorAlmacenamiento::crearAdministradorAlmacenamientoDistribuido(uintmax_t handler, ConfiguracionAlmacenamiento * configuracion) {};


bool IAdministradorAlmacenamiento::administradorIniciado(uintmax_t handler)
{
    std::unordered_map<uintmax_t, IAdministradorAlmacenamiento*>::iterator it = mapa_administradores.find(handler);

    return it != mapa_administradores.end();
}

// GETTERS

IAdministradorAlmacenamiento* IAdministradorAlmacenamiento::getInstancia(uintmax_t handler)
{
	if (administradorIniciado(handler))
	{
		return mapa_administradores[handler];
	}
	else
	{
        throw excepciones::AlmacenamientoNoInicializado(handler);
	}
}

IAdministradorAlmacenamiento * IAdministradorAlmacenamiento::getInstancia(std::string path_db)
{
    std::hash<std::string> hasheador;

    uintmax_t handler = hasheador(path_db);

    IAdministradorAlmacenamiento * admin = nullptr;
    try
    {
        admin = getInstancia(handler);
    }
    catch (herramientas::utiles::excepciones::Excepcion & e)
    {
        throw excepciones::AlmacenamientoNoInicializado(path_db);
    }

    return admin;
}

ConfiguracionAlmacenamiento * IAdministradorAlmacenamiento::config() {
    return this->configuracion;
}
