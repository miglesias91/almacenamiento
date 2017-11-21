#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

using namespace almacenamiento;

// stl
#include <iostream>

// almacenamiento
#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>

IAdministradorAlmacenamiento* IAdministradorAlmacenamiento::administrador = NULL;

IAdministradorAlmacenamiento::IAdministradorAlmacenamiento()
{
}

IAdministradorAlmacenamiento::~IAdministradorAlmacenamiento()
{
}

void IAdministradorAlmacenamiento::iniciar(std::string path_configuracion)
{
	if (administradorIniciado())
	{
		// TODO agregar log.
		std::cout << "Administrador ya fue iniciado." << std::endl;
		return;
		// throw std::exception("Administrador ya fue iniciado.");
	}

	ConfiguracionAlmacenamiento::leerConfiguracion(path_configuracion);

	if (ConfiguracionAlmacenamiento::almacenamientoLocal())
	{
		crearAdministradorAlmacenamientoLocal();
	}
	else
	{
		crearAdministradorAlmacenamientoDistribuido();
	}
}

void IAdministradorAlmacenamiento::liberar()
{
	if (true == administradorIniciado())
	{
		delete administrador;
		administrador = NULL;
	}
}

void IAdministradorAlmacenamiento::crearAdministradorAlmacenamientoLocal()
{
	administrador = new AdministradorAlmacenamientoLocal(ConfiguracionAlmacenamiento::pathDB());
};

void IAdministradorAlmacenamiento::crearAdministradorAlmacenamientoDistribuido() {};


bool IAdministradorAlmacenamiento::administradorIniciado()
{
	return administrador != NULL;
}

// GETTERS

IAdministradorAlmacenamiento* IAdministradorAlmacenamiento::getInstancia()
{
	if (administradorIniciado())
	{
		return administrador;
	}
	else
	{
		throw std::exception("Administrador de almacenamiento no inicializado.");
	}
};