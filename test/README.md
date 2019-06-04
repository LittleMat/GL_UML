# How to use the test

## On windows

### Visual Studio 2019

1. Use Visual Studio and create a new project/solution for Google Test
2. Delete the "pch.h" "pch.cpp" "test.cpp" that came by default
3. Copy all files under src and the "unitTest.cpp" to the directory of the solution
4. Under Visual Studio, use "Project">"Add existing element" and add all these files
5. Remove the main function in any file
6. Right click on the project, go to "Properties", find "C/C++">"Precompiled headers" and disable it.
7. Go to "Test" and run all tests.

### Visual Studio 2015

1. Donwload files from github of googletest.
2. Dans "Fichier">"Nouveau">"Projet", create a new "Visual C++">"Win32">"Projet Win32".
3. Choose "Bibliotheque statique" for "Type d'application", choose "Projet vide" for "Options supplementaires".
4. Extract "googletest-master/googletest" under the directory of the project that was created.
5. In Visual Studio 2015, right click on the project, "Ajouter">""Element existant", add *gtest.cc* and *gtest-all.cc* under "googletest/src".
6. Right click on project, choose "Proprietes", under "Proprietes de configuration">"C/C++">"General",
   add the path to "googletest" and "googletest/include" in the "Autres repertoire Include".
7. Right click on project, choose "Proprietes", under "Proprietes de configuration">"General">"Parametres par defaut du projet", 
   choose "Bibliotheque statique(.lib)" for "Type de configuration".
8. Go to "Fichier">"Projet">"Visual C++">"General">"Projet vide", choose "Ajouter a la solution" for "Solution", create a new project.
9. Right click on "References" of the new project, choose "Ajouter une reference", in "Projets">"Solution", choose the project we created before.
10. Copy files of the source code (except for the ones that contain main except for unitTest.cpp) to the directory of this newly created project.
    Right click on project, choose "Ajouter">"Element existant", add all the source code.
11. Right click on the newly created project, choose "Generer", and the project is ready to be run.

## On linux

Under linux, run `make test/Makefile` and then run `test/unitTest`
