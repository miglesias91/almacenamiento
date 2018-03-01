#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

using namespace almacenamiento;

// stl
#include <algorithm>
#include <iostream>

// almacenamiento
#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>
#include <almacenamiento/include/AlmacenamientoIniciadoPreviamente.h>

// utiles
#include <utiles/include/Excepcion.h>

std::unordered_map<unsigned long long int, IAdministradorAlmacenamiento*> IAdministradorAlmacenamiento::mapa_administradores;

IAdministradorAlmacenamiento::IAdministradorAlmacenamiento(ConfiguracionAlmacenamiento * configuracion) : configuracion(configuracion), log(NULL)
{
    this->log = herramientas::log::AdministradorLog::iniciarNuevo(configuracion->archivoConfigLog());
}

IAdministradorAlmacenamiento::~IAdministradorAlmacenamiento()
{
    if (NULL != this->configuracion)
    {
        delete this->configuracion;
        this->configuracion = NULL;
    }

    herramientas::log::AdministradorLog::liberarTodo();
}

unsigned long long int IAdministradorAlmacenamiento::iniciarNuevo(std::string path_configuracion)
{
    ConfiguracionAlmacenamiento * config = NULL;
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
		throw std::exception("Administrador de almacenamiento no inicializado.");
	}
}

IAdministradorAlmacenamiento * IAdministradorAlmacenamiento::getInstancia(std::string path_db)
{
    std::hash<std::string> hasheador;

    unsigned long long int handler = hasheador(path_db);

    return getInstancia(handler);
}
