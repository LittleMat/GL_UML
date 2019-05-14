SHELL=/bin/bash
EXENAME=analog

# default compiler flags
CPPFLAGS=-Wall -Wextra -pedantic -std=c++11
# variable that can be used to add more flags from the command line
FLAGS=

# directories
SRCDIR=src
BINDIR=bin
INSTALLDIR=/usr/bin
TESTDIR=tests

# man config
MANPAGE=${EXENAME}.1
MANDIR=/usr/share/man/man1

DEFAULT=main

default: ${DEFAULT}

main: main.o Parser.o
	@echo -e "\033[33mCompilation de main\033[0m"
	cd ${BINDIR} && \
	g++ ${CPPFLAGS} ${FLAGS} \
		*.o \
        -o ${EXENAME} \
	&& chmod +x ${EXENAME}

%.o: ${SRCDIR}/%.cpp
	@echo -e "\033[33mCompilation de $@\033[0m"
	if [[ ! -d ${BINDIR} ]]; then mkdir ${BINDIR}; fi
	g++ ${CPPFLAGS} ${FLAGS} -c $< -o ${BINDIR}/$@

clean:
	@if [[ -d ${BINDIR} ]]; then \
		echo -e "\033[33mNettoyage du répertoire de travail\033[0m"; \
		rm -f ${BINDIR}/*.o; \
		echo -e "\033[33mRépertoire de travail nettoyé :)\033[0m"; \
	else \
		echo -e "\033[33mRépertoire de travail inexistant\033[0m"; \
	fi;

install:
	@echo -e "Installing \033[36m${EXENAME}\033[0m to \033[33m${INSTALLDIR}\033[0m"
	cp ${BINDIR}/${EXENAME} ${INSTALLDIR}
	@echo -e "Installing \033[36mman\033[0m page"
	gzip -k ${MANPAGE}
	cp ${MANPAGE}.gz ${MANDIR}

uninstall:
	@echo -e "Deleting \033[36m${EXENAME}\033[0m from \033[33m${INSTALLDIR}\033[0m"
	rm ${INSTALLDIR}/${EXENAME}
	@echo -e "Deleting \033[36mman\033[0m page"
	rm ${MANDIR}/${MANPAGE}.gz

test:
	cd ${TESTDIR} && \
	./mktest.sh

help:
	@echo -e "\033[36mRègles make disponibles :\033[0m\n"

	@echo -e "\033[33mdefault :\033[0m"
	@echo -e "\texécute la cible par défaut \033[01m${DEFAULT}\033[0m\n"

	@echo -e "\033[33mmain :\033[0m"
	@echo -e "\tcompile tous les fichiers sources et crée l'exécutable \033[01m${EXENAME}\033[0m"
	@echo -e "\tle résultat des compilations est placé dans le sous-répertoire \033[01m${BINDIR}\033[0m\n"

	@echo -e "\033[33m<file>.o :\033[0m"
	@echo -e "\tcompile le fichier source <file>.cpp et crée le fichier objet <file>.o associé"
	@echo -e "\tle fichier source doit se trouver dans le sous-répertoire \033[01m${SRCDIR}\033[0m"
	@echo -e "\tle résultat de la compilation est placé dans le sous-répertoire \033[01m${BINDIR}\033[0m\n"

	@echo -e "\033[33mclean :\033[0m"
	@echo -e "\tsupprime tous les fichiers objets du répertoire \033[01m${BINDIR}\033[0m\n"

	@echo -e "\033[33minstall :\033[0m"
	@echo -e "\tinstalle l'exécutable \033[01m${EXENAME}\033[0m dans le répertoire \033[01m${INSTALLDIR}\033[0m"
	@echo -e "\tinstalle la page de manuel \033[01m${MANPAGE}\033[0m dans le répertoire \033[01m${MANDIR}\033[0m"
	@echo -e "\tpeut nécessiter des droits d'administrateur\n"

	@echo -e "\033[33muninstall :\033[0m"
	@echo -e "\tdésinstalle l'exécutable \033[01m${EXENAME}\033[0m du répertoire \033[01m${INSTALLDIR}\033[0m"
	@echo -e "\tdésinstalle la page de manuel \033[01m${MANPAGE}\033[0m du répertoire \033[01m${MANDIR}\033[0m"
	@echo -e "\tpeut nécessiter des droits d'administrateur\n"

	@echo -e "\033[33mtest :\033[0m"
	@echo -e "\texécute le script \033[01mmktest.sh\033[0m du répertoire \033[01m${TESTDIR}\033[0m\n"

	@echo -e "\033[33mhelp :\033[0m"
	@echo -e "\taffiche ce message d'aide\n"

main.o: ${SRCDIR}/main.h ${SRCDIR}/Parser.h ${SRCDIR}/Graph.h ${SRCDIR}/Node.h
