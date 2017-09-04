#include <almacenamiento/include/IAlmacenableClaveValor.h>

using namespace almacenamiento;

IAlmacenableClaveValor::IAlmacenableClaveValor() : clave(""), valor(""), grupo("")
{
}


IAlmacenableClaveValor::IAlmacenableClaveValor(std::string clave, std::string valor, std::string grupo) : clave(clave), valor(valor), grupo(grupo)
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

std::string IAlmacenableClaveValor::getClaveConPrefijo()
{
	return this->getGrupo() + this->getClave();
}

std::string IAlmacenableClaveValor::getValor()
{
	return this->valor;
}

std::string IAlmacenableClaveValor::getGrupo()
{
	return this->grupo;
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

void IAlmacenableClaveValor::setGrupo(std::string grupo)
{
	this->grupo = grupo;
}

// METODOS

// CONSULTA

// METODOS INTERNOS