// gtest
#include <gtest/gtest.h>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

TEST(almacenamiento, ConfigurarCorrectamente)
{ // este test tmb inicializa la db.
	almacenamiento::ConfiguracionAlmacenamiento::leerConfiguracion("configuracion_almacenamiento.json");

	ASSERT_STREQ("C:/temp/test_rocksdb", almacenamiento::ConfiguracionAlmacenamiento::pathDB().c_str());

	ASSERT_EQ(true, almacenamiento::ConfiguracionAlmacenamiento::almacenamientoLocal());

	ASSERT_EQ(false, almacenamiento::ConfiguracionAlmacenamiento::almacenamientoDistribuido());
}

TEST(almacenamiento, AlmacenarYRecuperarCorrectamente)
{
	std::string clave = "id_uno";
	std::string valor = "valor_uno";
	std::string grupo = "abc";

	almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->almacenar(clave_valor);
	delete clave_valor;

	almacenamiento::IAlmacenableClaveValor* clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_recuperado);

	ASSERT_STREQ(clave.c_str(), clave_valor_recuperado->getClave().c_str());
	ASSERT_STREQ(valor.c_str(), clave_valor_recuperado->getValor().c_str());
	ASSERT_STREQ((grupo + clave).c_str(), clave_valor_recuperado->getClaveConPrefijo().c_str());
	delete clave_valor_recuperado;
}

TEST(almacenamiento, AlmacenarYEliminarCorrectamente)
{
	std::string clave = "id_dos";
	std::string valor = "valor_dos";
	std::string grupo = "abc";

	almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->almacenar(clave_valor);
	delete clave_valor;

	almacenamiento::IAlmacenableClaveValor* clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_recuperado);

	std::string valor_recuperado_correcto = clave_valor_recuperado->getValor();

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->eliminar(clave_valor_recuperado);

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_recuperado);

	std::string valor_recuperado_eliminado = clave_valor_recuperado->getValor();
	delete clave_valor_recuperado;

	ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
	ASSERT_STREQ("", valor_recuperado_eliminado.c_str());
}

TEST(almacenamiento, AlmacenarYModificarCorrectamente)
{
	std::string clave = "id_tres";
	std::string valor = "valor_tres";
	std::string grupo = "abc";

	almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->almacenar(clave_valor);
	delete clave_valor;

	almacenamiento::IAlmacenableClaveValor* clave_valor_a_modificar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_a_modificar);

	std::string valor_recuperado_correcto = clave_valor_a_modificar->getValor();

	std::string valor_modificado = "valor_modif_tres";
	clave_valor_a_modificar->setValor(valor_modificado);

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->modificar(clave_valor_a_modificar);

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_a_modificar);
	std::string valor_modificado_correcto = clave_valor_a_modificar->getValor();
	delete clave_valor_a_modificar;


	ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
	ASSERT_STREQ(valor_modificado.c_str(), valor_modificado_correcto.c_str());
}

TEST(almacenamiento, RecuperarGrupoCorrectamente)
{
	std::string grupo = "abc";
	std::vector<almacenamiento::IAlmacenableClaveValor*> valores_recuperados;

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperarGrupo(grupo, valores_recuperados);

	ASSERT_EQ(6, valores_recuperados.size());

	ASSERT_STREQ("id_tres", valores_recuperados[4]->getClave().c_str());
	ASSERT_STREQ("valor_modif_tres", valores_recuperados[4]->getValor().c_str());
	ASSERT_STREQ("abc", valores_recuperados[4]->getGrupo().c_str());
	ASSERT_STREQ("abcid_tres", valores_recuperados[4]->getClaveConPrefijo().c_str());

	ASSERT_STREQ("id_uno", valores_recuperados[5]->getClave().c_str());
	ASSERT_STREQ("valor_uno", valores_recuperados[5]->getValor().c_str());
	ASSERT_STREQ("abc", valores_recuperados[5]->getGrupo().c_str());
	ASSERT_STREQ("abcid_uno", valores_recuperados[5]->getClaveConPrefijo().c_str());

	for (std::vector<almacenamiento::IAlmacenableClaveValor*>::iterator it = valores_recuperados.begin(); it != valores_recuperados.end(); it++)
	{
		delete (*it);
	}
	valores_recuperados.clear();
}