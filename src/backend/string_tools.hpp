/**
 * \file string_tools.hpp
 * \author Anthony Demange <tinou@tinou.fr>
 * \brief Tools for manipulating string.
 */

#ifndef KEEP_STORED_STRING_TOOLS_HPP
#define KEEP_STORED_STRING_TOOLS_HPP

namespace systools
{
	class String;
}

class QString;

/**
 * \brief Convert a systools::String to a QString.
 * \param str The string to convert.
 * \return The string.
 */
QString toQString(const systools::String& str);

/**
 * \brief Convert a QString to a systools::String.
 * \param str The string to convert.
 * \return The string.
 */
systools::String fromQString(const QString& str);

#endif /* KEEP_STORED_STRING_TOOLS_HPP */

