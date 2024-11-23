.PHONY: all report

all: report

report: report.html

report.html: report.xml style.xslt
	@xsltproc -o $@ style.xslt $< 

report.xml: ../Debug/Test_Cygwin.exe
	../Debug/Test_Cygwin.exe --gtest_output=xml:report.xml
