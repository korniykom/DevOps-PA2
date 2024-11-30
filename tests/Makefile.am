AUTOMAKE_OPTIONS = foreign

# Define the check program(s)
check_PROGRAMS = trigprogramtest1

trigprogramtest1_SOURCES = main.cpp $(top_builddir)/TrigFunction.cpp $(top_builddir)/TrigFunction.h $(top_builddir)/HTTP_server.cpp

trigprogramtest1_LDADD = -lcurl

TESTS = trigprogramtest1
