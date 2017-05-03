#include <almacenamiento/include/IAlmacenableClaveValor.h>

using namespace almacenamiento;

IAlmacenableClaveValor::IAlmacenableClaveValor() : clave(""), valor(""), familia("")
{
}


IAlmacenableClaveValor::IAlmacenableClaveValor(std::string clave, std::string valor, std::string familia) : clave(clave), valor(valor), familia(familia)
{
}

IAlmacenableClaveValor::~IAlmacenableClaveValor()
{
}

// GETTERS

std::string IAlmacenableClaveValor::getClave()
{
	return this->clave;
}

std::string IAlmacenableClaveValor::getValor()
{
	return this->valor;
}

std::string IAlmacenableClaveValor::getFamilia()
{
	return this->familia;
}

// SETTERS

void IAlmacenableClaveValor::setClave(std::string clave)
{
	this->clave = clave;
}

void IAlmacenableClaveValor::setValor(std::string valor)
{
	this->valor = valor;
}

void IAlmacenableClaveValor::setFamilia(std::string familia)
{
	this->familia = familia;
}

// METODOS

// CONSULTA

// METODOS INTERNOS