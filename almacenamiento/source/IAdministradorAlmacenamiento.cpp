#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

using namespace almacenamiento;

#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

void IAdministradorAlmacenamiento::iniciar(std::string path_configuracion)
{
	//almacenamiento::ConfiguracionAlmacenamiento configuracion(path_configuracion);

	//if (configuracion.almacenamientoLocal())
	//{
	//	crearAdministradorAlmacenamientoLocal();
	//}
	//else
	//{
	//	crearAdministradorAlmacenamientoDistribuido();
	//}
	if (administradorIniciado())
	{
		throw std::exception("Administrador ya fue iniciado.");
	}
	crearAdministradorAlmacenamientoLocal();
}

void IAdministradorAlmacenamiento::liberar()
{
	if (false == administradorIniciado())
	{
		delete administrador;
	}
}

void IAdministradorAlmacenamiento::crearAdministradorAlmacenamientoLocal()
{
	std::string path_db = "C:/temp/test_rocksdb";
	administrador = new AdministradorAlmacenamientoLocal(path_db);
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