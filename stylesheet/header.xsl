<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">

<xsl:output method="text" />


<xsl:template match="/xs:schema">

#include "separatista/elementdescriptor.h"

namespace Separatista
{
	namespace <xsl:value-of select="translate(substring(@targetNamespace,32), ':.', '__')" /> 
	{
		extern const wchar_t* g_Namespace;
		extern const Separatista::ElementDescriptor* DocumentElementDescriptor;
		<xsl:apply-templates />
	}
}
</xsl:template>

<xsl:template match="xs:element">
			
</xsl:template>

<xsl:template match="xs:simpleType">
			extern const Separatista::ElementDescriptor <xsl:value-of select="@name" />;
</xsl:template>

<xsl:template match="xs:complexType">
	<xsl:choose>
		<xsl:when test="xs:sequence">
			extern const Separatista::ElementDescriptor <xsl:value-of select="@name" />;
			extern const Separatista::ChildElementDescriptor <xsl:value-of select="concat(@name, 'ChildElements')" />[<xsl:value-of select="count(xs:sequence//xs:element)" />];
		</xsl:when>
		<xsl:when test="xs:simpleContent">
			extern const Separatista::ElementDescriptor <xsl:value-of select="@name" />;
		</xsl:when>
	</xsl:choose>
</xsl:template>





</xsl:stylesheet>
