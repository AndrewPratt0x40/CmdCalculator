<?xml version="1.0" encoding="utf-8" ?>
<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
	<xsl:output method="html" doctype-public="XSLT-compat" omit-xml-declaration="yes" encoding="UTF-8" indent="yes" />

	<!--See: https://www.w3schools.com/howto/howto_js_treeview.asp-->
	
	<xsl:template match="/testsuites">
		<hmtl>
			<head>
				<title>Test Results</title>
					<style>
.tree-node-container {
	list-style-type: none;
}

.tree-node.parent {
	cursor: pointer;
	user-select: none;
}

.tree-node-label {
	display: inline;
}

.tree-node.parent::before {
	content: "\25B6";
	display: inline-block;
	margin-right: 6px;
}

.expanded.tree-node.parent {
	display: block;
}

.collapsed.tree-node.parent {
	display: block;
}

.expanded.tree-node.parent::before {
	transform: rotate(90deg);
}
					</style>
			</head>
			<body>
				<ul class="tree-node-container">
					<xsl:apply-templates/>
				</ul>

				<script>

				</script>
			</body>
		</hmtl>
	</xsl:template>

	<xsl:template match="testsuite">
		<li class="tree-node parent">
			<div class="tree-node-content">
				<span><xsl:value-of select="@name"/></span>
			</div>
			<ul class="tree-node-container">
				<xsl:apply-templates/>
			</ul>
		</li>
	</xsl:template>
</xsl:transform>