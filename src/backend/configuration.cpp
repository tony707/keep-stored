/**
 * \file configuration.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The configuration class.
 */

#include "configuration.hpp"
#include "category.hpp"

#include <systools/xml_document.hpp>
#include <systools/xml_document_writer.hpp>
#include <systools/xml_xpath.hpp>

#include <boost/foreach.hpp>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


Configuration::Configuration()
{
}

QDir Configuration::rootConfigurationDirectory()
{
#if defined(UNIX) && !defined(MACINTOSH)
	QDir dir(QDir::homePath() + "/.keep-stored");
#elif defined(WINDOWS)
	QDir dir(".");

	OSVERSIONINFO osVersion;

	osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osVersion);

	assert(osVersion.dwMajorVersion > 5 || (osVersion.dwMajorVersion == 5 && osVersion.dwMinorVersion > 0));

	if (osVersion.dwMajorVersion == 5)
	{
		/* Windows XP */
		dir.setPath(QDir::homePath() + "/Application Data/KeepStored");
	}
	else if (osVersion.dwMajorVersion > 5)
	{
		/* Windows Vista and 7 */
		dir.setPath(QDir::homePath() + "/AppData/Roaming/KeepStored");
	}
#elif defined(MACINTOSH)
	QDir dir(QDir::homePath() + "/Library/Application Support/KeepStored");
#endif

	if (!dir.exists())
	{
		dir.mkpath(dir.path());
	}

	return dir;
}

std::string Configuration::configurationFilePath()
{
	return rootConfigurationDirectory().path().toStdString() + "/" + CONFIGURATION_FILE;
}

QList<boost::shared_ptr<Category> > Configuration::loadConfigurationFile()
{
	QList<boost::shared_ptr<Category> > category_list;

	if (rootConfigurationDirectory().exists(QString::fromStdString(CONFIGURATION_FILE)))
	{
		boost::shared_ptr<systools::xml::XmlDocument> xml_document = systools::xml::XmlDocument::createFromFile(configurationFilePath());

		xml_document->getXPath()->registerNamespace("ks", KEEPSTORED_XML_NAMESPACE);

		std::list<boost::shared_ptr<systools::xml::XmlNode> > category_node_list = xml_document->getXPath()->evaluate("/ks:configuration/ks:category");


		BOOST_FOREACH(boost::shared_ptr<systools::xml::XmlNode> category, category_node_list)
		{
			category_list.push_back(Category::createFromXmlNode(category));
		}
	}

	return category_list;
}

void Configuration::saveConfigurationFile(QList<boost::shared_ptr<Category> > category_list)
{
	boost::shared_ptr<systools::xml::XmlDocumentWriter> xml_writer(new systools::xml::XmlDocumentWriter("UTF-8"));

	xml_writer->startDocument();
	xml_writer->startElement("configuration");
	xml_writer->writeAttribute("xmlns", KEEPSTORED_XML_NAMESPACE);

	BOOST_FOREACH(boost::shared_ptr<Category> category, category_list)
	{
		Category::saveToXml(category, xml_writer);
	}

	xml_writer->endElement(); //configuration
	xml_writer->endDocument();

	systools::xml::XmlDocument::saveToFile(xml_writer->getResultAsDocument(), configurationFilePath());
}

