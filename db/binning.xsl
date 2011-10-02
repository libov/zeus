<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <body>
  <h2>Results</h2>
  <table border="1">
    <tr bgcolor="#9acd32">
      <th>Bin ID</th>
      <th>Variable</th>
      <th>Low Edge</th>
      <th>Up Edge</th>
      <th>k_uds</th>
      <th>k_c</th>
      <th>k_b</th>
    </tr>
    <xsl:for-each select="binning/bin_group/bin">
        <tr bgcolor="#FFFF00">
        <td><xsl:value-of select="@id"/></td> 
        <td><xsl:value-of select="subbin/variable"/></td> 
        <td><xsl:value-of select="subbin/low_edge"/></td> 
        <td><xsl:value-of select="subbin/up_edge"/></td> 
        <td><xsl:value-of select="k_uds"/> +- <xsl:value-of select="k_uds_err"/></td> 
        <td><xsl:value-of select="k_c"/> +- <xsl:value-of select="k_c_err"/></td> 
        <td><xsl:value-of select="k_b"/> +- <xsl:value-of select="k_b_err"/></td> 
        </tr>
  </xsl:for-each>
  </table>

  <h2>Results (inclusive bins)</h2>
  <table border="1">
    <tr bgcolor="#9acd32">
      <th>Bin ID</th>
      <th>Variable</th>
      <th>Low Edge</th>
      <th>Up Edge</th>
      <th>k_uds</th>
      <th>k_c</th>
      <th>k_b</th>
    </tr>
    <xsl:for-each select="binning/bin">
        <tr bgcolor="#FFFF00">
        <td><xsl:value-of select="@id"/></td> 
        <td><xsl:value-of select="subbin/variable"/></td> 
        <td><xsl:value-of select="subbin/low_edge"/></td> 
        <td><xsl:value-of select="subbin/up_edge"/></td> 
        <td><xsl:value-of select="k_uds"/> +- <xsl:value-of select="k_uds_err"/></td> 
        <td><xsl:value-of select="k_c"/> +- <xsl:value-of select="k_c_err"/></td> 
        <td><xsl:value-of select="k_b"/> +- <xsl:value-of select="k_b_err"/></td> 
        </tr>
  </xsl:for-each>
  </table>

  </body>
  </html>
</xsl:template>

</xsl:stylesheet>

