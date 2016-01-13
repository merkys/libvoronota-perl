TARGET = example

I_FILE   = ${TARGET}.i
CPP_FILE = ${TARGET}.cpp
CXX_FILE = ${TARGET}_wrap.cxx
PM_FILE  = ${TARGET}.pm
SO_FILE  = ${TARGET}.so
CPP_O_FILE = ${CPP_FILE:%.cpp=%.o}
CXX_O_FILE = ${CXX_FILE:%.cxx=%.o}

all: ${PM_FILE} ${SO_FILE}

${PM_FILE} ${CXX_FILE}: ${I_FILE} ${CPP_FILE}
	swig -c++ -perl $<

${CPP_O_FILE} ${CXX_O_FILE}: ${CPP_FILE} ${CXX_FILE}
	g++ -c $+ \
		`perl -MConfig -e 'print join(" ", @Config{qw(ccflags optimize cccdlflags)}, "-I$$Config{archlib}/CORE")'`

${SO_FILE}: ${CPP_O_FILE} ${CXX_O_FILE}
	g++ `perl -MConfig -e 'print $$Config{lddlflags}'` $+ -o $@

clean:
	rm -f ${CXX_FILE} ${CPP_O_FILE} ${CXX_O_FILE}

distclean cleanAll: clean
	rm -f ${PM_FILE} ${SO_FILE}

try: all
	./example.pl
