/**
 * \file configuration.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The configuration class.
 */

#include "configuration.hpp"
#include "abstract_category.hpp"
#include "default_category.hpp"
#include "search_category.hpp"
#include "string_tools.hpp"

#include <systools/xml_document.hpp>
#include <systools/xml_document_writer.hpp>
#include <systools/xml_xpath.hpp>
#include <systools/xml_schema.hpp>

#include <boost/foreach.hpp>
#include <boost/smart_ptr.hpp>

#include <QMessageBox>
#include <QDebug>

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

static const systools::String SCHEMA_STRING = "<?xml version=\"1.0\"?> \
<xs:schema \
	xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" \
	targetNamespace=\"http://github.com/tinoutinou/keep-stored\" \
	xmlns=\"" + KEEPSTORED_XML_NAMESPACE + "\" \
	elementFormDefault=\"qualified\" \
	> \
	\
	<xs:complexType name=\"tagType\" > \
		<xs:sequence> \
			<xs:element minOccurs=\"0\" name=\"tag\" type=\"xs:string\" /> \
		</xs:sequence> \
	</xs:complexType> \
	\
	<xs:complexType name=\"resourceType\" > \
		<xs:sequence> \
			<xs:element name=\"type\" type=\"xs:int\" minOccurs=\"1\" /> \
			<xs:element name=\"title\" type=\"xs:string\" minOccurs=\"1\" /> \
			<xs:element name=\"author\" type=\"xs:string\" minOccurs=\"1\" /> \
			<xs:element name=\"location\" type=\"xs:string\" minOccurs=\"1\" /> \
			<xs:element minOccurs=\"0\" maxOccurs=\"1\" name=\"tagList\" type=\"tagType\" /> \
		</xs:sequence> \
	</xs:complexType> \
	\
	<xs:complexType name=\"categoryType\" mixed=\"true\" > \
		<xs:sequence> \
			<xs:element name=\"type\" type=\"xs:int\" minOccurs=\"1\" /> \
			<xs:element name=\"title\" type=\"xs:string\" minOccurs=\"1\" /> \
			<xs:element minOccurs=\"0\" name=\"resource\" type=\"resourceType\" /> \
			<xs:element name=\"category\" type=\"categoryType\" minOccurs=\"0\" /> \
		</xs:sequence> \
	</xs:complexType> \
	\
	<xs:element name=\"configuration\"> \
		<xs:complexType> \
			<xs:sequence> \
				<xs:element name=\"category\" type=\"categoryType\" minOccurs=\"0\" /> \
				<xs:any minOccurs=\"0\" maxOccurs=\"unbounded\" processContents=\"skip\" /> \
			</xs:sequence> \
		</xs:complexType> \
	</xs:element> \
 \
</xs:schema> \
";

static bool has_one_search_category = false;


Configuration::Configuration()
{
}

const boost::shared_ptr<systools::xml::XmlSchema> Configuration::SCHEMA(systools::xml::XmlSchema::createFromBuffer(SCHEMA_STRING.toUtf8()));

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

AbstractCategory* Configuration::loadConfigurationFile()
{
	AbstractCategory* root_category = new DefaultCategory();

	if (rootConfigurationDirectory().exists(QString::fromStdString(CONFIGURATION_FILE)))
	{
		boost::shared_ptr<systools::xml::XmlDocument> xml_document = systools::xml::XmlDocument::createFromFile(configurationFilePath());

		std::list<boost::shared_ptr<systools::xml::XmlNode> > category_node_list;

		try
		{
			EXCEPTION_ASSERT(SCHEMA->validate(xml_document), systools::ParsingErrorException, "Unrecognized XML document");

			xml_document->xpath()->registerNamespace("ks", KEEPSTORED_XML_NAMESPACE);

			category_node_list = xml_document->xpath()->evaluate("/ks:configuration/ks:category");
		}
		catch (systools::Exception e)
		{
			QMessageBox::critical(NULL, QObject::tr("Error!"), QObject::tr("Bad configuration file.\n\nThe error was:\n\n%1").arg(QString(e.what())));
			return 0;
		}

		BOOST_FOREACH(boost::shared_ptr<systools::xml::XmlNode> category_node, category_node_list)
		{
			AbstractCategory* category = AbstractCategory::createFromXmlNode(category_node);

			createChildCategory(category_node, category);

			if(category->type() == AbstractCategory::Search)
			{
				has_one_search_category = true;
			}

			root_category->appendChild(category);
		}

		if (!has_one_search_category)
		{
			root_category->prependChild(new SearchCategory("Search results"));
		}
	}

	return root_category;
}

void Configuration::createChildCategory(boost::shared_ptr<systools::xml::XmlNode> category_node, AbstractCategory* parent)
{
	std::list<boost::shared_ptr<systools::xml::XmlNode> > category_node_list = category_node->xpath()->evaluate("ks:category");

	if (category_node_list.size() > 0)
	{
		BOOST_FOREACH(boost::shared_ptr<systools::xml::XmlNode> category_node, category_node_list)
		{
			AbstractCategory* category = AbstractCategory::createFromXmlNode(category_node);
			parent->appendChild(category);

			createChildCategory(category_node, category);
		}
	}
}

void Configuration::saveConfigurationFile(AbstractCategory* root_category)
{
	boost::shared_ptr<systools::xml::XmlDocumentWriter> xml_writer(new systools::xml::XmlDocumentWriter());

	xml_writer->startDocument();
	xml_writer->startElement("configuration");
	xml_writer->writeAttribute("xmlns", KEEPSTORED_XML_NAMESPACE);

	BOOST_FOREACH(AbstractCategory* category, root_category->children())
	{
		AbstractCategory::saveToXml(category, xml_writer);
	}

	xml_writer->endElement(); //configuration
	xml_writer->endDocument();

	systools::xml::XmlDocument::saveToFile(xml_writer->getResultAsDocument(), configurationFilePath());
}

