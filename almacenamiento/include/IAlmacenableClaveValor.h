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
		IAlmacenableClaveValor(std::string clave, std::string valor, std::string familia);
		virtual ~IAlmacenableClaveValor();

		// GETTERS

		std::string getClave();

		std::string getValor();

		std::string getFamilia();

		// SETTERS

		void setClave( std::string clave );

		void setValor( std::string valor );

		void setFamilia( std::string familia );

		// METODOS

		// CONSULTA

	private:
		// METODOS INTERNOS

		// ATRIBUTOS

		std::string clave;

		std::string valor;

		std::string familia;

};
};