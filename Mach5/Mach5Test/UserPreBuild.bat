::******************************************************************************
::Filename: UserPreBuild.bat
::author:   Matt Casanova 
::e-mail:   lazersquad@gmail.com
::Project:  Mach5 
::date:     2016/8/10
::
::Brief:
::The batch file recreate the file M5GameStages.h based on the Stages the user
::has created and then Register those Stages with the StageManager
::******************************************************************************
@echo off

::Change to source directory
cd Source

call:CreateEnum
call:CreateRegisterStages
goto:eof


:CreateRegisterStages
::Create output file
set REGISTERFILE=RegisterGameWithEngine.h
::Add file header
echo /******************************************************************************/ > %REGISTERFILE%
echo /*! >> %REGISTERFILE%
echo \file   RegisterGameWithEngine.h >> %REGISTERFILE%
echo \author UserPreBuild.bat >> %REGISTERFILE%
echo \par    email: lazersquad\@gmail.com >>%REGISTERFILE%
echo \par    Mach5 Game Engine >> %REGISTERFILE%
echo. >> %REGISTERFILE%
echo This file gets auto generated based on the names of the Stages in the >> %REGISTERFILE%
echo current project.  UserPreBuild.bat looks for files of the type *Stage.h >> %REGISTERFILE%
echo and registers those stages with the StageMgr. >> %REGISTERFILE%
echo */ >> %REGISTERFILE%
echo /******************************************************************************/ >> %REGISTERFILE%

::Add Code Guards
echo #ifndef REGISTER_GAME_WITH_ENGINE_H >> %REGISTERFILE%
echo #define REGISTER_GAME_WITH_ENGINE_H >> %REGISTERFILE%
echo. >> %REGISTERFILE%

::Add includes
echo #include "M5StageMgr.h" >> %REGISTERFILE%
echo #include "M5GameStages.h" >> %REGISTERFILE%
echo #include "M5TemplateBuilder.h" >> %REGISTERFILE%

::Include all Stage header files
for %%f in ( *Stage.h ) do (
  echo #include "%%f" >> %REGISTERFILE%
)

echo inline void RegisterGameWithEngine(void) {  >> %REGISTERFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( *Stage.h ) do (
  ::echo  M5StageMgr::AddStage(GS_%%~nf, new M5TemplateBuilder^< %%~nf ^>()); >> %REGISTERFILE%
  echo  M5StageMgr::AddStage^(GS_%%~nf, new M5TemplateBuilder^< %%~nf ^>^(^) ^); >> %REGISTERFILE%
)


echo } >> %REGISTERFILE%
echo #endif //REGISTER_GAME_WITH_ENGINE_H >> %REGISTERFILE%
goto:eof

:CreateEnum
::Create 
set ENUMFILE=M5GameStages.h
echo /******************************************************************************/ > %ENUMFILE%
echo /*! >> %ENUMFILE%
echo \file   GSGameStages.h >> %ENUMFILE%
echo \author UserPreBuild.bat >> %ENUMFILE%
echo \par    email: lazersquad\@gmail.com >>%ENUMFILE%
echo \par    Mach5 Game Engine >> %ENUMFILE%
echo. >> %ENUMFILE%
echo This file gets auto generated based on the names of the Stages in the >> %ENUMFILE%
echo current project.  UserPreBuild.bat looks for files of the type *Stage.h >> %ENUMFILE%
echo and creates an enumeration value of GS_*Stage. >> %ENUMFILE%
echo */ >> %ENUMFILE%
echo /******************************************************************************/ >> %ENUMFILE%

echo #ifndef M5_GAME_STAGES_H >> %ENUMFILE%
echo #define M5_GAME_STAGES_H >> %ENUMFILE%
echo enum M5GameStages {  >> %ENUMFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( *Stage.h ) do (
  echo GS_%%~nf, >> %ENUMFILE%
)
::Add one more to the end without the comma
echo GS_INVALID >> %ENUMFILE%


echo }; >> %ENUMFILE%
echo #endif //M5_GAME_STAGES_H >> %ENUMFILE%
mv %ENUMFILE% "..\..\Include\%ENUMFILE%" > nul 2> nul
goto:eof