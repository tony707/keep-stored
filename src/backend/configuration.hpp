/**
 * \file configuration.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The configuration class.
 */

#ifndef KEEP_STORED_CONFIGURATION_HPP
#define KEEP_STORED_CONFIGURATION_HPP

#include <QDir>

#include <boost/shared_ptr.hpp>

#include <systools/string.hpp>

static const std::string CONFIGURATION_FILE = "configuration.xml";
static const systools::String KEEPSTORED_XML_NAMESPACE = "http://github.com/tinoutinou/keep-stored";

class AbstractCategory;

namespace systools
{
	namespace xml
	{
		class XmlSchema;
	}
}

class Configuration
{
	public:

		/**
		 * \brief Constructor.
		 */
		Configuration();

		 /**
			* \brief Load the application configuration.
			*/
		 QList<boost::shared_ptr<AbstractCategory> > loadConfigurationFile();

		 /**
			* \brief Load the application configuration.
			*/
		 void saveConfigurationFile(QList<boost::shared_ptr<AbstractCategory> > category_list);

	private:

		 /**
			* \brief The associated xml_schema.
			*/
		static const boost::shared_ptr<systools::xml::XmlSchema> SCHEMA;

		/**
		 * \brief Get the root configuration directory.
		 */
		QDir rootConfigurationDirectory();

		/**
		 * \brief Get the root configuration directory.
		 */
		std::string configurationFilePath();

};

#endif /* KEEP_STORED_CONFIGURATION_HPP */

