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

call:CreateStageEnum
call:CreateComponentEnum
call:CreateRegisterStages
call:CreateRegisterComponent
goto:eof

::******************************************************************************
::Auto generates the RegisterStages.h files which registers all user 
::created stages with the StageManger
::******************************************************************************
:CreateRegisterStages
::Create output file
set REGISTERFILE=RegisterStages.h
::Add file header
echo /******************************************************************************/ > %REGISTERFILE%
echo /*! >> %REGISTERFILE%
echo \file   RegisterStages.h >> %REGISTERFILE%
echo \author UserPreBuild.bat >> %REGISTERFILE%
echo \par    email: lazersquad\@gmail.com >>%REGISTERFILE%
echo \par    Mach5 Game Engine >> %REGISTERFILE%
echo. >> %REGISTERFILE%
echo This file gets auto generated based on the names of the Stages in the >> %REGISTERFILE%
echo current project.  UserPreBuild.bat looks for files named *Stage.h >> %REGISTERFILE%
echo and registers those stages with the StageMgr. >> %REGISTERFILE%
echo */ >> %REGISTERFILE%
echo /******************************************************************************/ >> %REGISTERFILE%

::Add Code Guards
echo #ifndef REGISTER_STAGES_H >> %REGISTERFILE%
echo #define REGISTER_STAGES_H >> %REGISTERFILE%
echo. >> %REGISTERFILE%

::Add includes
echo #include "M5StageMgr.h" >> %REGISTERFILE%
echo #include "M5StageTypes.h" >> %REGISTERFILE%
echo #include "M5StageBuilder.h" >> %REGISTERFILE%

::Include all Stage header files
for %%f in ( *Stage.h ) do (
  echo #include "%%f" >> %REGISTERFILE%
)
echo. >> %REGISTERFILE%
echo. >> %REGISTERFILE%

echo inline void RegisterStages(void) {  >> %REGISTERFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( *Stage.h ) do (
  echo  M5StageMgr::AddStage^(ST_%%~nf, new M5StageTBuilder^< %%~nf ^>^(^) ^); >> %REGISTERFILE%
)


echo } >> %REGISTERFILE%
echo #endif //REGISTER_STAGES_H >> %REGISTERFILE%
goto:eof


::******************************************************************************
::Auto generates the enum for M5StageTypes based on the files that the user created.
::******************************************************************************
:CreateStageEnum
::Create 
set ENUMFILE=M5StageTypes.h
echo /******************************************************************************/ > %ENUMFILE%
echo /*! >> %ENUMFILE%
echo \file   M5StageType.h >> %ENUMFILE%
echo \author UserPreBuild.bat >> %ENUMFILE%
echo \par    email: lazersquad\@gmail.com >>%ENUMFILE%
echo \par    Mach5 Game Engine >> %ENUMFILE%
echo. >> %ENUMFILE%
echo This file gets auto generated based on the names of the Stages in the >> %ENUMFILE%
echo current project.  UserPreBuild.bat looks for files of the type *Stage.h >> %ENUMFILE%
echo and creates an enumeration value of ST_*Stage. >> %ENUMFILE%
echo */ >> %ENUMFILE%
echo /******************************************************************************/ >> %ENUMFILE%

echo #ifndef M5STAGE_TYPES_H >> %ENUMFILE%
echo #define M5STAGE_TYPES_H >> %ENUMFILE%
echo.
echo.
echo enum M5StageTypes {  >> %ENUMFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( *Stage.h ) do (
  echo ST_%%~nf, >> %ENUMFILE%
)
::Add one more to the end without the comma
echo ST_INVALID >> %ENUMFILE%


echo }; >> %ENUMFILE%
echo #endif //M5STAGE_TYPES_H >> %ENUMFILE%
mv %ENUMFILE% "..\..\Include\%ENUMFILE%" > nul 2> nul
goto:eof

::******************************************************************************
::Auto generates the RegisterComponents.h files which registers all user 
::created components with the ObjectManager
::******************************************************************************
:CreateRegisterComponent
::Create output file
set REGISTERFILE=RegisterComponents.h
::Add file header
echo /******************************************************************************/ > %REGISTERFILE%
echo /*! >> %REGISTERFILE%
echo \file   %REGISTERFILE% >> %REGISTERFILE%
echo \author UserPreBuild.bat >> %REGISTERFILE%
echo \par    email: lazersquad\@gmail.com >>%REGISTERFILE%
echo \par    Mach5 Game Engine >> %REGISTERFILE%
echo. >> %REGISTERFILE%
echo This file gets auto generated based on the names of the Components in the >> %REGISTERFILE%
echo Include folder and current project.  UserPreBuild.bat looks for files named *Component.h >> %REGISTERFILE%
echo and registers those with the ObjectManager. >> %REGISTERFILE%
echo */ >> %REGISTERFILE%
echo /******************************************************************************/ >> %REGISTERFILE%

::Add Code Guards
echo #ifndef REGISTER_COMPONENTS_H >> %REGISTERFILE%
echo #define REGISTER_COMPONENTS_H >> %REGISTERFILE%
echo. >> %REGISTERFILE%

::Add includes
echo #include "M5ObjectManager.h" >> %REGISTERFILE%
echo #include "M5ComponentTypes.h" >> %REGISTERFILE%
echo #include "M5ComponentBuilder.h" >> %REGISTERFILE%

::All Component header files from the Include folder
for %%f in ( ..\..\Include\*???Component.h ) do (
  echo #include "%%~nxf" >> %REGISTERFILE%
)
::All Component header files from the current project
for %%f in ( *???Component.h ) do (
  echo #include "%%f" >> %REGISTERFILE%
)
echo. >> %REGISTERFILE%
echo. >> %REGISTERFILE%

echo inline void RegisterComponents(void) {  >> %REGISTERFILE%

::All Component header files from the Include folder
for %%f in ( ..\..\Include\*???Component.h ) do (
  echo  M5ObjectManager::AddComponent^(CT_%%~nf, new M5ComponentTBuilder^< %%~nf ^>^(^) ^); >> %REGISTERFILE%
)
::All Component header files from the current project
for %%f in ( *???Component.h ) do (
  echo  M5ObjectManager::AddComponent^(CT_%%~nf, new M5ComponentTBuilder^< %%~nf ^>^(^) ^); >> %REGISTERFILE%
)


echo } >> %REGISTERFILE%
echo #endif //REGISTER_COMPONENTS_H >> %REGISTERFILE%
goto:eof


::******************************************************************************
::Auto generates the enum for M5ComponentTypes based on the files that
:: the user created.
::******************************************************************************
:CreateComponentEnum
::Create 
set ENUMFILE=M5ComponentTypes.h
echo /******************************************************************************/ > %ENUMFILE%
echo /*! >> %ENUMFILE%
echo \file   M5ComponentTypes.h >> %ENUMFILE%
echo \author UserPreBuild.bat >> %ENUMFILE%
echo \par    email: lazersquad\@gmail.com >>%ENUMFILE%
echo \par    Mach5 Game Engine >> %ENUMFILE%
echo. >> %ENUMFILE%
echo This file gets auto generated based on the names of the Components in the >> %ENUMFILE%
echo current project.  UserPreBuild.bat looks for files of the type *Component.h >> %ENUMFILE%
echo and creates an enumeration value of CT_*Component. >> %ENUMFILE%
echo */ >> %ENUMFILE%
echo /******************************************************************************/ >> %ENUMFILE%

echo #ifndef M5COMPONENT_TYPE_H >> %ENUMFILE%
echo #define M5COMPONENT_TYPE_H >> %ENUMFILE%
echo.
echo.
echo enum M5ComponentTypes {  >> %ENUMFILE%

::Get all files with the name *Stage in it and output just the file name
for %%f in ( ..\..\Include\*???Component.h ) do (
  echo CT_%%~nf, >> %ENUMFILE%
)

for %%f in ( *Component.h ) do (
  echo CT_%%~nf, >> %ENUMFILE%
)
::Add one more to the end without the comma
echo CT_INVALID >> %ENUMFILE%


echo }; >> %ENUMFILE%
echo #endif //M5COMPONENT_TYPE_H >> %ENUMFILE%
mv %ENUMFILE% "..\..\Include\%ENUMFILE%" > nul 2> nul
goto:eof