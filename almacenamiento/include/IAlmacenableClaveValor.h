/// IAlmacenableClaveValor.h
/// 2017-04-15

#pragma once

// stl
#include <string>

namespace almacenamiento
{

class IAlmacenableClaveValor
{
	public:
		IAlmacenableClaveValor();
		IAlmacenableClaveValor(std::string clave, std::string grupo = "", std::string valor = "");
		virtual ~IAlmacenableClaveValor();

		// GETTERS

		std::string getClave();
		std::string getClaveConPrefijo();

		std::string getValor();

		std::string getGrupo();

		// SETTERS

		void setClave( std::string clave );

		void setValor( std::string valor );

		void setGrupo( std::string grupo );

		// METODOS

		// CONSULTA

	private:
		// METODOS INTERNOS

		// ATRIBUTOS

		std::string clave;
		std::string valor;
		std::string grupo;
};
};