<?xml version="1.0"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema">

<xsl:output method="text" />


<xsl:template match="/xs:schema">

#include "separatista/elementdescriptor.h"
#include "separatista/leafelement.h"
#include "separatista/attributedleafelement.h"
#include "separatista/branchelement.h"
#include "separatista/choiceelement.h"
#include "separatista/validator.h"
#include "<xsl:value-of select="substring(@targetNamespace, 32)" />.h"

namespace Separatista
{
	namespace <xsl:value-of select="translate(substring(@targetNamespace, 32), ':.', '__')" /> 
	{
		const wchar_t* Namespace = TEXT("<xsl:value-of select="@targetNamespace" />");
		<xsl:apply-templates />
	}
}
</xsl:template>

<xsl:template match="xs:element">
		const Separatista::ChildElementDescriptor DocumentElementDescriptor = 
		{
			SEPARATISTA_TAG("<xsl:value-of select="@name" />"), // Tag
			1,			// Min
			1,			// Max
			&amp;<xsl:value-of select="@type" />
		};
</xsl:template>

<xsl:template match="xs:simpleType">
		void <xsl:value-of select="concat('validate_', @name)" />(const wchar_t *pValue, Separatista::Element *pElement)
		{
			<xsl:apply-templates select="xs:restriction" />
		}

		static const Separatista::ElementDescriptor <xsl:value-of select="@name" /> = 
		{
			NULL,												// Parent type
			Separatista::LeafElement::createElement,							// Creator
			<xsl:value-of select="concat('validate_', @name)" /> ,	// Validator
			0,													// Child elements
			NULL												// ChildElement descriptors
		};
</xsl:template>

<xsl:template match="xs:restriction">
			Separatista::Validator::validate<xsl:value-of select="concat(translate(substring(@base, 4, 1), 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'), substring(@base, 5))" />(pValue, pElement);
			<xsl:choose>
				<xsl:when test="xs:enumeration">
					<xsl:apply-templates select="xs:enumeration" />
				</xsl:when>
				<xsl:otherwise>
					<xsl:for-each select="*">
			Separatista::Validator::validate<xsl:value-of select="concat(translate(substring(name(), 4, 1), 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'), substring(name(), 5))" />(pValue, TEXT("<xsl:call-template name="escapeBackslash"><xsl:with-param name="text" select="@value" /></xsl:call-template>"), pElement);
					</xsl:for-each>
				</xsl:otherwise>
			</xsl:choose>
</xsl:template>

<xsl:template match="xs:enumeration[position() = 1]">
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("<xsl:value-of select="@value" />"),
</xsl:template>

<xsl:template match="xs:enumeration[position() = last()]">
					TEXT("<xsl:value-of select="@value" />")
				},
				pElement);
</xsl:template>

<xsl:template match="xs:enumeration[position() = last() and position() = 1]">
			Separatista::Validator::validateEnumeration(
				pValue, 
				{
					TEXT("<xsl:value-of select="@value" />")
				},
				pElement);
</xsl:template>

<xsl:template match="xs:enumeration[position()&gt;1 and position()&lt;last()]">
					TEXT("<xsl:value-of select="@value" />"),
</xsl:template>

<xsl:template match="xs:complexType">
	<xsl:choose>
		<xsl:when test="xs:sequence">
		static const Separatista::ElementDescriptor <xsl:value-of select="@name" /> = 
		{
			NULL,												// Parent type
			<xsl:choose>
				<xsl:when test="xs:sequence/xs:choice">
			Separatista::ChoiceElement::createElement,						// Creator
				</xsl:when>
				<xsl:otherwise>
			Separatista::BranchElement::createElement,
				</xsl:otherwise>
			</xsl:choose>
			NULL,												// Validator
			<xsl:value-of select="count(xs:sequence//xs:element)" />,												// Child element count
			<xsl:value-of select="concat(@name, 'ChildElements')" />											// Child element descriptors
		};
		
		static const Separatista::ChildElementDescriptor <xsl:value-of select= "concat(@name, 'ChildElements')" />[] =
		{
				<xsl:apply-templates select="xs:sequence" />
		};
		</xsl:when>
		<xsl:when test="xs:simpleContent">
		static const Separatista::ElementDescriptor <xsl:value-of select="@name" /> =
		{
			&amp;<xsl:value-of select="xs:simpleContent/xs:extension/@base" />,				// Parent type
			Separatista::AttributedLeafElement::createElement,				// Creator
			NULL,															// Validator
			0,																// Child element count
			NULL															// Child element descriptors
		};
		</xsl:when>
	</xsl:choose>
</xsl:template>

<xsl:template match="xs:sequence/xs:choice/xs:element" >
				{
					SEPARATISTA_TAG("<xsl:value-of select="@name" />"),				// Tag
					1,																// Min
					1,																// Max
					&amp;<xsl:value-of select="@type" />							// ElementDescriptor
				},
				
</xsl:template>

<xsl:template match="xs:sequence/xs:element" >
				{
					SEPARATISTA_TAG("<xsl:value-of select="@name" />"),				// Tag
					<xsl:choose>
						<xsl:when test="@minOccurs">
							<xsl:value-of select="@minOccurs" />,										// Min
						</xsl:when>
						<xsl:otherwise>
							1,																		// Min
						</xsl:otherwise>
					</xsl:choose>
					<xsl:choose>
						<xsl:when test="@maxOccurs='unbounded'">
							0,																		//Max
						</xsl:when>
						<xsl:when test="@maxOccurs">
							<xsl:value-of select="@maxOccurs" />,										// Max
						</xsl:when>
						<xsl:otherwise>
							1,																		// Max
						</xsl:otherwise>
					</xsl:choose>	
					&amp;<xsl:value-of select="@type" />								// ElementDescriptor
				},
				
</xsl:template>

<xsl:template name="escapeBackslash">
	<xsl:param name="text" />
	<xsl:variable name="todo" select="substring-after($text, '\')" />
	<xsl:choose>
		<xsl:when test="$todo">
			<xsl:value-of select="substring-before($text, '\')" />\\<xsl:call-template name="escapeBackslash"><xsl:with-param name="text" select="$todo" /></xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$text" />
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

</xsl:stylesheet>
