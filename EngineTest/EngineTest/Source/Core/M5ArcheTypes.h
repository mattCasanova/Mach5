/******************************************************************************/ 
/*! 
\file   M5ArcheTypes.h 
\author UserPreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the ArcheTypes in the 
current project.  UserPreBuild.bat looks for files of the type *.ini in the ArcheTypes folder 
and creates an enumeration value of AT_*. 
*/ 
/******************************************************************************/ 
#ifndef M5ARCHE_TYPES_H 
#define M5ARCHE_TYPES_H 
#include <string> 
 
 
enum M5ArcheTypes {  
AT_Splash, 
AT_INVALID 
}; 
 
 
inline M5ArcheTypes StringToArcheType(const std::string& string) { 
if(string == "Splash") return AT_Splash; 
return AT_INVALID; 
} 
#endif //M5ARCHE_TYPES_H 
