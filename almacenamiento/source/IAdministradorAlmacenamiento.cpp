#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

using namespace almacenamiento;

// stl
#include <algorithm>
#include <iostream>

// almacenamiento
#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

std::unordered_map<unsigned long long int, IAdministradorAlmacenamiento*> IAdministradorAlmacenamiento::mapa_administradores;

IAdministradorAlmacenamiento::IAdministradorAlmacenamiento(ConfiguracionAlmacenamiento * configuracion) : configuracion(configuracion)
{
}

IAdministradorAlmacenamiento::~IAdministradorAlmacenamiento()
{
    if (NULL != this->configuracion)
    {
        delete this->configuracion;
        this->configuracion = NULL;
    }
}

unsigned long long int IAdministradorAlmacenamiento::iniciarNuevo(std::string path_configuracion)
{
    ConfiguracionAlmacenamiento * config = new ConfiguracionAlmacenamiento(path_configuracion);

    std::hash<std::string> hasheador;

    unsigned long long int handler_admin = hasheador(config->pathDB());

    if (administradorIniciado(handler_admin))
	{
		// TODO agregar log.
        std::cout << "Administrador de almacenamiento en el path " + config->pathDB() + " ya fue iniciado." << std::endl;

        delete config;

		return 0;
		// throw std::exception("Administrador ya fue iniciado.");
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
