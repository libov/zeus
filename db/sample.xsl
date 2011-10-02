<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <body>
  <h2>Samples available for analysis</h2>
  <table border="1">
    <tr bgcolor="#9acd32">
      <th>Year</th>
      <th>Type</th>
      <th>CN version</th>
      <th>Flavour</th>
      <th>Q2</th>
      <th>Luminosity</th>
      <th>Luminosity Recalculated</th>
      <th>Name pattern</th>
    </tr>
    <xsl:for-each select="dataset/sample">
    <tr>
      <td><xsl:value-of select="year"/></td>
      <td><xsl:value-of select="type"/></td>
      <td><xsl:value-of select="CN_version"/></td>
      <td><xsl:value-of select="flavour"/></td>
      <td><xsl:value-of select="q2"/></td>
      <td><xsl:value-of select="luminosity"/></td>
      <td><xsl:value-of select="luminosity_recalculated"/></td>
      <td><xsl:value-of select="name_pattern"/></td>
    </tr>
    </xsl:for-each>
  </table>
  </body>
  </html>
</xsl:template>

</xsl:stylesheet>

