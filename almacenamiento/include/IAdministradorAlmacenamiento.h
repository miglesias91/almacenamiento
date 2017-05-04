/// IAdministradorAlmacenamiento.h
/// 02-05-2017

#pragma once

// almacenamiento
#include <almacenamiento/include/IAlmacenableClaveValor.h>
#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

namespace almacenamiento
{

class IAdministradorAlmacenamiento
{
	public:

		static void iniciar(std::string path_configuracion)
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

		static void liberar()
		{
			if (false == administradorIniciado())
			{
				delete administrador;
			}
		}

		static void crearAdministradorAlmacenamientoLocal()
		{
			std::string path_db = "C:/temp/test_rocksdb";
			administrador = new AdministradorAlmacenamientoLocal(path_db);
		};

		static void crearAdministradorAlmacenamientoDistribuido() {};


		static bool administradorIniciado()
		{
			return administrador != NULL;
		}

		// GETTERS

		static IAdministradorAlmacenamiento* getInstancia()
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

		// SETTERS

		// METODOS

		virtual bool almacenar(IAlmacenableClaveValor* valor_a_almacenar) = 0;

		virtual bool recuperar(std::string clave_a_recuperar, IAlmacenableClaveValor* valor_recuperado) = 0;

		virtual bool modificar(std::string clave_a_modificar, IAlmacenableClaveValor* valor_modificado) = 0;

		virtual bool eliminar(std::string clave_a_eliminar) = 0;

		// CONSULTA

		virtual bool existe(std::string clave_a_chequear) = 0;

	private:
		// METODOS INTERNOS

		// ATRIBUTOS
		static IAdministradorAlmacenamiento* administrador;
};
};