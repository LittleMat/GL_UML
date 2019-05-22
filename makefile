EXENAME=exec

# default compiler flags
CPPFLAGS=-Wall -Wextra -pedantic -std=c++11
# variable that can be used to add more flags from the command line
FLAGS=

# directories
SRCDIR=src
BINDIR=bin


# man config
#MANPAGE=${EXENAME}.1
#MANDIR=/usr/share/man/man1

DEFAULT=main

default: ${DEFAULT}

main: main.o Capteur.o FileReader.o Mesure.o Point.o Service.o Territoire.o Attribut.o
	@echo -e "\033[33mCompilation de main\033[0m"
	cd ${BINDIR} && \
	g++ ${CPPFLAGS} ${FLAGS} \
		*.o \
        -o ../${EXENAME} \
	&& chmod +x ../${EXENAME}

%.o: ${SRCDIR}/%.cpp
	@echo -e "\033[33mCompilation de $@\033[0m"
	if [[ ! -d ${BINDIR} ]]; then mkdir ${BINDIR}; fi
	g++ ${CPPFLAGS} ${FLAGS} -c $< -o ${BINDIR}/$@

clean:
	@if [ -d ${BINDIR} ]; then \
		echo -e "\033[33mNettoyage du répertoire de travail\033[0m"; \
		rm -f ${BINDIR}/*.o; \
		echo -e "\033[33mRépertoire de travail nettoyé :)\033[0m"; \
	else \
		echo -e "\033[33mRépertoire de travail inexistant\033[0m"; \
	fi;


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

	@echo -e "\033[33mtest :\033[0m"
	@echo -e "\texécute le script \033[01mmktest.sh\033[0m du répertoire \033[01m${TESTDIR}\033[0m\n"

	@echo -e "\033[33mhelp :\033[0m"
	@echo -e "\taffiche ce message d'aide\n"

main.o: ${SRCDIR}/main.h ${SRCDIR}/Capteur.h ${SRCDIR}/FileReader.h ${SRCDIR}/Mesure.h ${SRCDIR}/Point.h ${SRCDIR}/Service.h ${SRCDIR}/Territoire.h ${SRCDIR}/Attribut.h