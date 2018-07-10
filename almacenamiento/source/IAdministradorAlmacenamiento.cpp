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

std::unordered_map<unsigned long long int, IAdministradorAlmacenamiento*> IAdministradorAlmacenamiento::mapa_administradores;

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

unsigned long long int IAdministradorAlmacenamiento::iniciarNuevo(std::string path_configuracion)
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

    unsigned long long int handler_admin = hasheador(config->pathDB());

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
    for (std::unordered_map<unsigned long long int, IAdministradorAlmacenamiento*>::iterator it = mapa_administradores.begin(); it != mapa_administradores.end(); it++)
    {
        delete it->second;
    }

    mapa_administradores.clear();

    herramientas::log::AdministradorLog::liberarTodo();
}

void IAdministradorAlmacenamiento::liberar(unsigned long long int handler)
{
	if (true == administradorIniciado(handler))
	{
		delete mapa_administradores[handler];
        mapa_administradores.erase(handler);
	}
}

void IAdministradorAlmacenamiento::crearAdministradorAlmacenamientoLocal(unsigned long long int handler, ConfiguracionAlmacenamiento * configuracion)
{
    IAdministradorAlmacenamiento * administrador = new AdministradorAlmacenamientoLocal(configuracion);

    mapa_administradores[handler] = administrador;
}

void IAdministradorAlmacenamiento::crearAdministradorAlmacenamientoDistribuido(unsigned long long int handler, ConfiguracionAlmacenamiento * configuracion) {};


bool IAdministradorAlmacenamiento::administradorIniciado(unsigned long long int handler)
{
    std::unordered_map<unsigned long long int, IAdministradorAlmacenamiento*>::iterator it = mapa_administradores.find(handler);

    return it != mapa_administradores.end();
}

// GETTERS

IAdministradorAlmacenamiento* IAdministradorAlmacenamiento::getInstancia(unsigned long long int handler)
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

    unsigned long long int handler = hasheador(path_db);

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
