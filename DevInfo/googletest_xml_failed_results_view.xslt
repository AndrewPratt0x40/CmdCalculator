<?xml version="1.0" encoding="UTF-8" ?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="3.0">
	<xsl:output method="xml" doctype-public="XSLT-compat" omit-xml-declaration="yes" encoding="UTF-8" indent="yes" />

	<xsl:template match="/testsuites">
		<failures>
			<xsl:for-each select="testsuite/testcase">
				<xsl:if test="failure">
					<failure>
						<suite>
							<xsl:value-of select="@classname"/>
						</suite>
						<test>
							<xsl:value-of select="@name"/>
						</test>
						<xsl:if test="@type_param">
							<param>
								<xsl:value-of select="@type_param"/>
							</param>
						</xsl:if>
						<xsl:if test="@value_param">
							<param>
								<xsl:value-of select="@value_param"/>
							</param>
						</xsl:if>
						<message>
							<xsl:value-of select="failure/@message"/>
						</message>
					</failure>
				</xsl:if>
			</xsl:for-each>
		</failures>
	</xsl:template>
</xsl:transform>
