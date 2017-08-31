// gtest
#include <gtest/gtest.h>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>

TEST(almacenamiento, ConfigurarCorrectamente)
{
	almacenamiento::ConfiguracionAlmacenamiento::leerConfiguracion("C:/Users/Manuel/Documents/Visual Studio 2015/Projects/almacenamiento/almacenamiento/configuracion_almacenamiento.json");

	ASSERT_EQ(true, almacenamiento::ConfiguracionAlmacenamiento::almacenamientoLocal());

	ASSERT_EQ(false, almacenamiento::ConfiguracionAlmacenamiento::almacenamientoDistribuido());
}