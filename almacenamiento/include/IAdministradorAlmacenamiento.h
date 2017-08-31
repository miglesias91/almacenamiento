/// IAdministradorAlmacenamiento.h
/// 02-05-2017

#pragma once

// almacenamiento
#include <almacenamiento/include/IAlmacenableClaveValor.h>

namespace almacenamiento
{

class IAdministradorAlmacenamiento
{
	public:

		static void iniciar(std::string path_configuracion);

		static void liberar();

		static void crearAdministradorAlmacenamientoLocal();

		static void crearAdministradorAlmacenamientoDistribuido();

		static bool administradorIniciado();

		// GETTERS

		static IAdministradorAlmacenamiento* getInstancia();

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