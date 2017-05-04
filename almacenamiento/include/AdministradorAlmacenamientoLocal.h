/// AdministradorAlmacenamientoLocal.h
/// 02-05-2017

#pragma once

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

namespace almacenamiento
{

class AdministradorAlmacenamientoLocal : public IAdministradorAlmacenamiento
{
	public:
		AdministradorAlmacenamientoLocal(std::string directorio);
		virtual ~AdministradorAlmacenamientoLocal();

		// GETTERS

		// SETTERS

		// METODOS

		virtual bool almacenar(IAlmacenableClaveValor* valor_a_almacenar);

		virtual bool recuperar(std::string clave_a_recuperar, IAlmacenableClaveValor* valor_recuperado);

		virtual bool modificar(std::string clave_a_modificar, IAlmacenableClaveValor* valor_modificado);

		virtual bool eliminar(std::string clave_a_eliminar);

		// CONSULTA

		virtual bool existe(std::string clave_a_chequear);

	private:
		// METODOS INTERNOS

		// ATRIBUTOS
};
};