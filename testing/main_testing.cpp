
// gtest
#include <gtest/gtest.h>

#ifdef DEBUG | _DEBUG
// vld
#include <vld.h>
#endif

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

unsigned long long int handlersucho;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    unsigned long long int handler = almacenamiento::IAdministradorAlmacenamiento::iniciarNuevo("config_testing.json");
    unsigned long long int handler_2 = almacenamiento::IAdministradorAlmacenamiento::iniciarNuevo("config_testing_2.json");

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(handler)->abrir();
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(handler_2)->abrir();

    int result = RUN_ALL_TESTS();

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(handler)->cerrar();
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(handler_2)->cerrar();

    //almacenamiento::IAdministradorAlmacenamiento::liberar(handler);
    almacenamiento::IAdministradorAlmacenamiento::liberarTodos();

    std::getchar();

    return result;
}