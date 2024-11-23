<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  
  <!-- Root element: Match the "testsuites" tag -->
  <xsl:template match="/testsuites">
    <html>
      <head>
        <title>Test Report</title>
        <style>
          body { font-family: Arial, sans-serif; }
          table { width: 100%; border-collapse: collapse; margin-bottom: 20px; }
          th, td { border: 1px solid black; padding: 8px; text-align: left; }
          th { background-color: #f2f2f2; }
          .failure { color: red; font-weight: bold; }
          .passed { color: black; font-weight: bold; }
        </style>
      </head>
      <body>
        <h1>Test Report Summary</h1>
        <p>Total Tests: <xsl:value-of select="@tests"/></p>
        <p>Failures: <xsl:value-of select="@failures"/></p>
        <p>Disabled: <xsl:value-of select="@disabled"/></p>
        <p>Errors: <xsl:value-of select="@errors"/></p>
        <p>Execution Time: <xsl:value-of select="@time"/> seconds</p>
        <p>Timestamp: <xsl:value-of select="@timestamp"/></p>

        <!-- Iterate through each "testsuite" -->
        <xsl:for-each select="testsuite">
          <h2>Test Suite: <xsl:value-of select="@name"/></h2>
          <table>
            <thead>
              <tr>
                <th>Test Case</th>
                <th>Status</th>
                <th>Result</th>
                <th>Time</th>
                <th>Details</th>
              </tr>
            </thead>
            <tbody>
              <!-- Iterate through each "testcase" in the suite -->
              <xsl:for-each select="testcase">
                <tr>
                  <td><xsl:value-of select="@name"/></td>
                  <td><xsl:value-of select="@status"/></td>
                  <td>
                    <!-- Determine if the test passed or failed -->
                    <xsl:choose>
                      <xsl:when test="failure">
                        <span class="failure">Failed</span>
                      </xsl:when>
                      <xsl:otherwise>
                        <span class="passed">Passed</span>
                      </xsl:otherwise>
                    </xsl:choose>
                  </td>
                  <td><xsl:value-of select="@time"/> seconds</td>
                  <td>
                    <!-- Display failure details if available -->
                    <xsl:if test="failure">
                      <span class="failure">
                        <xsl:value-of select="failure/@message"/>
                        <pre><xsl:value-of select="failure"/></pre>
                      </span>
                    </xsl:if>
                  </td>
                </tr>
              </xsl:for-each>
            </tbody>
          </table>
        </xsl:for-each>
      </body>
    </html>
  </xsl:template>

</xsl:stylesheet>
