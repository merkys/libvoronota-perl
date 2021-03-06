TARGET = Voronota

I_FILE   = ${TARGET}.i
CPP_FILE = ${TARGET}.cpp
CXX_FILE = ${TARGET}_wrap.cxx
PM_FILE  = ${TARGET}.pm
SO_FILE  = ${TARGET}.so
CPP_O_FILE = ${CPP_FILE:%.cpp=%.o}
CXX_O_FILE = ${CXX_FILE:%.cxx=%.o}

VORONOTA_SRC = src/externals/voronota/src

vendorarch = $(shell perl -le 'use Config; my $$p = $$Config{vendorarch}; $$p =~ s/^\/usr\///; print $$p')
PREFIX = /usr

all: ${PM_FILE} ${SO_FILE}

#------------------------------------------------------------------------------

${PM_FILE} ${CXX_FILE}: ${I_FILE} ${CPP_FILE}
	swig -c++ -perl $<

${CPP_O_FILE} ${CXX_O_FILE}: ${CPP_FILE} ${CXX_FILE}
	g++ -c $+ \
		`perl -MConfig -e 'print join(" ", @Config{qw(ccflags optimize cccdlflags)}, "-I$$Config{archlib}/CORE")'` -I${VORONOTA_SRC}/

${SO_FILE}: ${CPP_O_FILE} ${CXX_O_FILE}
	g++ `perl -MConfig -e 'print $$Config{lddlflags}'` $+ -o $@

#------------------------------------------------------------------------------

.PHONY: install

install: all
	mkdir --parents ${PREFIX}/${vendorarch}/auto/${TARGET}
	install --mode 644 ${PM_FILE} ${PREFIX}/${vendorarch}
	install ${SO_FILE} ${PREFIX}/${vendorarch}/auto/${TARGET}

#------------------------------------------------------------------------------

.PHONY: clean distclean cleanAll

clean:
	rm -f ${CXX_FILE} ${CPP_O_FILE} ${CXX_O_FILE}

distclean cleanAll: clean
	rm -f ${PM_FILE} ${SO_FILE}
