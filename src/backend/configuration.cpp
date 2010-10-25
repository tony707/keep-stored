/**
 * \file configuration.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief The configuration class.
 */

#include "configuration.hpp"
#include "abstract_category.hpp"
#include "search_category.hpp"

#include <systools/xml_document.hpp>
#include <systools/xml_document_writer.hpp>
#include <systools/xml_xpath.hpp>
#include <systools/xml_schema.hpp>

#include <boost/foreach.hpp>

#include <QMessageBox>

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
	<xs:element name=\"configuration\"> \
		<xs:complexType> \
			<xs:sequence> \
				<xs:element minOccurs=\"0\" name=\"category\"> \
					<xs:complexType > \
						<xs:sequence> \
							<xs:element name=\"type\" type=\"xs:int\" /> \
							<xs:element name=\"title\" type=\"xs:string\" /> \
							<xs:element minOccurs=\"0\" name=\"resource\" > \
								<xs:complexType> \
									<xs:sequence> \
										<xs:element name=\"type\" type=\"xs:int\" /> \
										<xs:element name=\"title\" type=\"xs:string\" /> \
										<xs:element name=\"author\" type=\"xs:string\" /> \
										<xs:element name=\"location\" type=\"xs:string\" /> \
										<xs:element minOccurs=\"0\" maxOccurs=\"1\" name=\"tagList\" > \
											<xs:complexType> \
												<xs:sequence> \
													<xs:element minOccurs=\"0\" name=\"tag\" type=\"xs:string\" /> \
												</xs:sequence> \
											</xs:complexType> \
										</xs:element> \
									</xs:sequence> \
								</xs:complexType> \
							</xs:element> \
						</xs:sequence> \
					</xs:complexType> \
				</xs:element> \
				<xs:any minOccurs=\"0\" maxOccurs=\"unbounded\" processContents=\"skip\" /> \
			</xs:sequence> \
		</xs:complexType> \
	</xs:element> \
 \
</xs:schema> \
";


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

QList<boost::shared_ptr<AbstractCategory> > Configuration::loadConfigurationFile()
{
	QList<boost::shared_ptr<AbstractCategory> > category_list;

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
			return QList<boost::shared_ptr<AbstractCategory> >();
		}

		bool has_one_search_category = false;

		BOOST_FOREACH(boost::shared_ptr<systools::xml::XmlNode> category_node, category_node_list)
		{
			boost::shared_ptr<AbstractCategory> category = AbstractCategory::createFromXmlNode(category_node);

			if(category->type() == AbstractCategory::Search)
			{
				has_one_search_category = true;
			}

			category_list.push_back(category);
		}

		if (!has_one_search_category)
		{
			category_list.push_front(boost::shared_ptr<AbstractCategory>(new SearchCategory("Search results")));
		}
	}

	return category_list;
}

void Configuration::saveConfigurationFile(QList<boost::shared_ptr<AbstractCategory> > category_list)
{
	boost::shared_ptr<systools::xml::XmlDocumentWriter> xml_writer(new systools::xml::XmlDocumentWriter());

	xml_writer->startDocument();
	xml_writer->startElement("configuration");
	xml_writer->writeAttribute("xmlns", KEEPSTORED_XML_NAMESPACE);

	BOOST_FOREACH(boost::shared_ptr<AbstractCategory> category, category_list)
	{
		AbstractCategory::saveToXml(category, xml_writer);
	}

	xml_writer->endElement(); //configuration
	xml_writer->endDocument();

	systools::xml::XmlDocument::saveToFile(xml_writer->getResultAsDocument(), configurationFilePath());
}

