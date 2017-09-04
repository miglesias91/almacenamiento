/// IAdministradorAlmacenamiento.h
/// 02-05-2017

#pragma once

// stl
#include <vector>

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

		virtual bool recuperar(IAlmacenableClaveValor* valor_recuperado) = 0;

		virtual bool recuperar(std::vector<IAlmacenableClaveValor*> & valores_recuperados) = 0;

		virtual bool recuperarGrupo(std::string prefijo_grupo, std::vector<IAlmacenableClaveValor*> & valores_recuperados) = 0;

		virtual bool modificar(IAlmacenableClaveValor* nuevo_valor) = 0;

		virtual bool eliminar(IAlmacenableClaveValor* clave_a_eliminar) = 0;

		// CONSULTA

		virtual bool existe(IAlmacenableClaveValor* clave_a_chequear) = 0;

	private:
		// METODOS INTERNOS

		// ATRIBUTOS
		static IAdministradorAlmacenamiento* administrador;
};
};