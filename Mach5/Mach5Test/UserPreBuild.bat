::******************************************************************************
::Filename: UserPreBuild.bat
::author:   Matt Casanova 
::e-mail:   lazersquad@gmail.com
::Project:  Mach5 
::date:     2016/8/10
::
::Brief:
::The batch file recreate the file M5GameStages.h based on the Stages the user
::has created.
::******************************************************************************
@echo off

set OUTPUT=M5GameStages.h

::Change to source directory
cd Source


echo #ifndef M5_GAME_STAGES_H > %OUTPUT%
echo #define M5_GAME_STAGES_H >> %OUTPUT%
echo enum M5GameStages {  >> %OUTPUT%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( *Stage.h ) do (
  echo GS_%%~nf, >> %OUTPUT%
)
::Add one more to the end without the comma
echo GS_INVALID >> %OUTPUT%


echo }; >> %OUTPUT%
echo #endif //M5_GAME_STAGES_H >> %OUTPUT%
mv %OUTPUT% "..\..\Include\%OUTPUT%" > nul 2> nul