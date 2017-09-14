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

	ASSERT_EQ(true, almacenamiento::ConfiguracionAlmacenamiento::prefijoHabilitado());

	ASSERT_EQ(3, almacenamiento::ConfiguracionAlmacenamiento::prefijoTamanio());

	ASSERT_STREQ("con", almacenamiento::ConfiguracionAlmacenamiento::prefijoConcepto().c_str());
	
	ASSERT_STREQ("con", almacenamiento::ConfiguracionAlmacenamiento::prefijoConsulta().c_str());

	ASSERT_STREQ("gra", almacenamiento::ConfiguracionAlmacenamiento::prefijoGrafico().c_str());

	ASSERT_STREQ("sec", almacenamiento::ConfiguracionAlmacenamiento::prefijoSeccion().c_str());

	ASSERT_STREQ("ter", almacenamiento::ConfiguracionAlmacenamiento::prefijoTermino().c_str());
}

TEST(almacenamiento, AlmacenarYRecuperarCorrectamente)
{
	std::string clave = "id_uno";
	std::string valor = "valor_uno";
	std::string grupo = "ter";

	almacenamiento::IAdministradorAlmacenamiento::iniciar("configuracion_almacenamiento.json");

	almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, valor, grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->almacenar(clave_valor);

	almacenamiento::IAlmacenableClaveValor* clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, "", grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_recuperado);

	ASSERT_STREQ(clave.c_str(), clave_valor_recuperado->getClave().c_str());
	ASSERT_STREQ(valor.c_str(), clave_valor_recuperado->getValor().c_str());
	ASSERT_STREQ((grupo + clave).c_str(), clave_valor_recuperado->getClaveConPrefijo().c_str());
}

TEST(almacenamiento, AlmacenarYEliminarCorrectamente)
{
	std::string clave = "id_dos";
	std::string valor = "valor_dos";
	std::string grupo = "ter";

	almacenamiento::IAdministradorAlmacenamiento::iniciar("configuracion_almacenamiento.json");

	almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, valor, grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->almacenar(clave_valor);

	almacenamiento::IAlmacenableClaveValor* clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, "", grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_recuperado);

	std::string valor_recuperado_correcto = clave_valor_recuperado->getValor();

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->eliminar(clave_valor_recuperado);

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_recuperado);

	std::string valor_recuperado_eliminado = clave_valor_recuperado->getValor();

	ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
	ASSERT_STREQ("", valor_recuperado_eliminado.c_str());
}

TEST(almacenamiento, AlmacenarYModificarCorrectamente)
{
	std::string clave = "id_tres";
	std::string valor = "valor_tres";
	std::string grupo = "ter";

	almacenamiento::IAdministradorAlmacenamiento::iniciar("configuracion_almacenamiento.json");

	almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, valor, grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->almacenar(clave_valor);

	almacenamiento::IAlmacenableClaveValor* clave_valor_a_modificar = new almacenamiento::IAlmacenableClaveValor(clave, "", grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_a_modificar);

	std::string valor_recuperado_correcto = clave_valor_a_modificar->getValor();

	std::string valor_modificado = "valor_modif_tres";
	clave_valor_a_modificar->setValor(valor_modificado);

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->modificar(clave_valor_a_modificar);

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperar(clave_valor_a_modificar);
	std::string valor_modificado_correcto = clave_valor_a_modificar->getValor();

	ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
	ASSERT_STREQ(valor_modificado.c_str(), valor_modificado_correcto.c_str());
}

TEST(almacenamiento, RecuperarGrupoCorrectamente)
{
	std::string grupo = "ter";
	std::vector<almacenamiento::IAlmacenableClaveValor*> valores_recuperados;

	almacenamiento::IAdministradorAlmacenamiento::iniciar("configuracion_almacenamiento.json");

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->recuperarGrupo(grupo, valores_recuperados);

	ASSERT_EQ(6, valores_recuperados.size());

	ASSERT_STREQ("id_tres", valores_recuperados[4]->getClave().c_str());
	ASSERT_STREQ("valor_modif_tres", valores_recuperados[4]->getValor().c_str());
	ASSERT_STREQ("ter", valores_recuperados[4]->getGrupo().c_str());
	ASSERT_STREQ("terid_tres", valores_recuperados[4]->getClaveConPrefijo().c_str());

	ASSERT_STREQ("id_uno", valores_recuperados[5]->getClave().c_str());
	ASSERT_STREQ("valor_uno", valores_recuperados[5]->getValor().c_str());
	ASSERT_STREQ("ter", valores_recuperados[5]->getGrupo().c_str());
	ASSERT_STREQ("terid_uno", valores_recuperados[5]->getClaveConPrefijo().c_str());
}