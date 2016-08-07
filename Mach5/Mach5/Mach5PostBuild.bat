::******************************************************************************
::Filename: PostBuild.bat
::author:   Matt Casanova 
::e-mail:   mcasanov@digipen.edu
::Course:   cs180
::date:     2012/3/21
::
::Brief:
::This helper batch file will move .h and lib files from the Engine directory
::To the demo directory.
::******************************************************************************
@echo off

::Make sure all of the folders I need exist
mkdir "..\Include" > nul 2> nul
mkdir "..\Lib" > nul 2> nul
mkdir "..\Debug" > nul 2> nul
mkdir "..\Release" > nul 2> nul 

::Change to source directory
cd Source

::Run Tablen and copy all h files
echo Running Tablen
::Copy all .h files
type nul > Tablen.txt
for %%f in ( *.h ) do (
  ::Tablen %%f >> Tablen.txt
  copy %%f "..\..\Include\%%f" > nul 2> nul
)

::for %%f in ( *.cpp ) do (
::  Tablen %%f >> Tablen.txt
::)



::Run doxygen and copy files
echo Running Doxygen
doxygen > nul 2> DoxyErrors.txt

::Step into doxygen directory and get index.chm
cd html
copy index.chm "..\..\..\Include\Mach5Dox.chm" > nul 2> nul

::Step out
cd..

::Delete doxygen folder
rmdir /S /Q html

::Copy all .lib files
::Move to solution directory Release and Debug folders
cd .. 
cd .. 

::Copy Debug lib
echo Copying Libs
cd Debug
for %%f in (*.lib) do (
  copy %%f "..\Lib\%%f" > nul 2> nul
)
cd ..

cd Release
for %%f in (*.lib) do (
  copy %%f "..\Lib\%%f" > nul 2> nul
)
cd ..

