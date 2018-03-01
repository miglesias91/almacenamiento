/// IAdministradorAlmacenamiento.h
/// 02-05-2017

#pragma once

// stl
#include <vector>
#include <unordered_map>

// log
#include <log/include/AdministradorLog.h>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>
#include <almacenamiento/include/IAlmacenableClaveValor.h>

namespace almacenamiento
{

    class IAdministradorAlmacenamiento
    {
    public:

        IAdministradorAlmacenamiento(ConfiguracionAlmacenamiento * configuracion);
        virtual ~IAdministradorAlmacenamiento();

        static unsigned long long int iniciarNuevo(std::string path_configuracion);

        static void liberarTodos();

        static void liberar(unsigned long long int handler);

        static void crearAdministradorAlmacenamientoLocal(unsigned long long int handler, ConfiguracionAlmacenamiento * configuracion);

        static void crearAdministradorAlmacenamientoDistribuido(unsigned long long int handler, ConfiguracionAlmacenamiento * configuracion);

        static bool administradorIniciado(unsigned long long int handler);

        // GETTERS

        static IAdministradorAlmacenamiento* getInstancia(unsigned long long int handler);

        static IAdministradorAlmacenamiento* getInstancia(std::string path_db);

        herramientas::log::Logger * log;

        // SETTERS

        // METODOS

        virtual bool abrir() = 0;

        virtual bool cerrar() = 0;

        virtual bool borrar() = 0;

		virtual bool almacenar(IAlmacenableClaveValor* valor_a_almacenar) = 0;

		virtual bool recuperar(IAlmacenableClaveValor* valor_recuperado) = 0;

		virtual bool recuperar(std::vector<IAlmacenableClaveValor*> & valores_recuperados) = 0;

		virtual bool recuperarGrupo(std::string prefijo_grupo, std::vector<IAlmacenableClaveValor*> & valores_recuperados) = 0;

		virtual bool modificar(IAlmacenableClaveValor* nuevo_valor) = 0;

		virtual bool eliminar(IAlmacenableClaveValor* clave_a_eliminar) = 0;

		// CONSULTA

		virtual bool existe(IAlmacenableClaveValor* clave_a_chequear) = 0;

        virtual bool bdAbierta() = 0;

    protected:

        ConfiguracionAlmacenamiento * configuracion;

	private:
		// METODOS INTERNOS

		// ATRIBUTOS

        static std::unordered_map<unsigned long long int, IAdministradorAlmacenamiento*> mapa_administradores;
};
};