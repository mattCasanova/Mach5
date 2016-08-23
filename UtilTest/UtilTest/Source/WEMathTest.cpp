/******************************************************************************/
/*!
\file   M5MathTest.cpp
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2015/12/2

Function to test my math helper functions

*/
/******************************************************************************/
#include "M5Math.h"
#include "M5Vec2.h"
#include "M5Mtx44.h"
#include "M5Debug.h"
#include <cstdio>

void M5Mtx44Test(void)
{
  M5Mtx44 matrix1 = {0};
  M5Mtx44 matrix2;
  M5Mtx44 matrix3;
  M5Mtx44 translate, scale, rotate;
  bool flag; /*Used to get a return value from bool functions*/
  //int i; /*used to get a return value from int functions*/
  //float f;/*used to get the return value from float functions*/





  /*Test MakeZero*/
  M5Mtx44::MakeZero(matrix2);
  flag = M5Mtx44::IsEqual(matrix1, matrix2);
  M5Debug::TestResult(flag, "MakeZero");

  matrix3.MakeZero();
  flag = M5Mtx44::IsEqual(matrix3, matrix2);
  M5Debug::TestResult(flag, "MakeZero");

  matrix1.m[0][0] = matrix1.m[1][1] = matrix1.m[2][2] = 
    matrix1.m[3][3] = 1.0f;

  /*Test make identity*/
  M5Mtx44::MakeIdentity(matrix2);
  flag = M5Mtx44::IsEqual(matrix1, matrix2);
  M5DEBUG_ASSERT(flag, "Mtx Make Identity not working");

  /*Test Mtx44Equal*/
  matrix1.m[3][0] = matrix1.m[3][1] = 5.f;
  flag = M5Mtx44::IsEqual(matrix1, matrix2);
  M5DEBUG_ASSERT(!flag, "Mtx equal not working");

  /*Test make translate*/
  M5Mtx44::MakeTranslate(matrix2, 5.f, 5.f, 0.f);
  flag = M5Mtx44::IsEqual(matrix1, matrix2);
  M5DEBUG_ASSERT(flag, "Mtx Make translate not working");

  /*Test make scale*/
  matrix1.m[3][0] = matrix1.m[3][1] = 0.f;
  matrix1.m[0][0] = matrix1.m[1][1] = 3.f;
  M5Mtx44::MakeScale(matrix2, 3.f, 3.f);
  flag = M5Mtx44::IsEqual(matrix1, matrix2);
  M5DEBUG_ASSERT(flag, "Mtx Make scale not working");

  /*Test make rotate*/
  matrix1.m[0][0] = matrix1.m[1][1] = 0.f;
  matrix1.m[0][1] = 1.f;
  matrix1.m[1][0] = -1.f;
  matrix1.m[2][2] = matrix1.m[3][3] = 1.0f;
  M5Mtx44::MakeRotateZ(matrix2, M5Math::DegreeToRadian(90.f));
  flag = M5Mtx44::IsEqual(matrix1, matrix2);
  M5DEBUG_ASSERT(flag, "Mtx make rotate not working");

  /*Test copy*/
  rotate = matrix2;
  flag = M5Mtx44::IsEqual(rotate, matrix1);
  M5DEBUG_ASSERT(flag, "Mtx Copy not working");

  /*Test matrix mult*/

  /*Create separate translate scale and rotate matrices*/
  M5Mtx44::MakeTranslate(translate, 1.0f, 2.0f, 0.5f);
  M5Mtx44::MakeScale(scale, 1.0f, 2.0f);
  M5Mtx44::MakeRotateZ(rotate, M5Math::DegreeToRadian(90.f));

  /*Make a complete transform*/
  M5Mtx44::MakeTransform(matrix1, 1.0f, 2.0f,
    M5Math::DegreeToRadian(90.f),
    1.0f, 2.0f, 0.5f);

  /*The order to create a transform ((SR)T)*/
  M5Mtx44::Multiply(matrix2, scale, rotate);
  M5Mtx44::Multiply(matrix3, matrix2, translate);
  flag = M5Mtx44::IsEqual(matrix3, matrix1);
  M5DEBUG_ASSERT(flag, "Matrix mult not working");
}

void M5Vec2Test(void)
{
  printf("Test Vec2 Functions**********\n");

  float f; //my float result

  M5Vec2 vec0, vec1, result, testValue;
  /*Test set*/
  M5Vec2::Set(vec0, 0.0f, 1.0f);
  M5Vec2::Set(vec1, 1.0f, 0.0f);
  M5Vec2::Set(testValue, 1.0f, 0.0f);
  bool flag;


  /*Test Equal*/
  flag = M5Vec2::IsEqual(vec1, testValue);
  M5Debug::TestResult(flag, "Vec2::IsEqual");

  flag = M5Vec2::IsEqual(vec1, vec0);
  M5Debug::TestResult(!flag, "M5Vec2::IsEqual");

  testValue.y = .0000000000000001f;

  M5Debug::TestResult(vec1 == testValue, "Vec2::operator==");
  M5Debug::TestResult(!(vec0 == testValue), "Vec2::operator==");

  M5Vec2::Set(testValue, 1.0f, M5Math::EPSILON);




  /*Test Not equal*/
  flag = M5Vec2::IsNotEqual(vec0, testValue);
  M5Debug::TestResult(flag, "Vec2NotEqual");

  flag = M5Vec2::IsNotEqual(vec0, vec0);
  M5Debug::TestResult(!flag, "Vec2NotEqual");

  M5Vec2::Set(testValue, 1.0f, 0.f);

  M5Debug::TestResult(vec0 != testValue, "Vec2::operator!=");
  M5Debug::TestResult(!(vec1 != testValue), "Vec2::operator!=");




  /*Test add*/
  M5Vec2::Add(result, vec0, vec1);
  testValue.x = testValue.y = 1.0f;
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2Add");

  result = vec0 + vec1;
  M5Debug::TestResult(result == testValue, "Vec2::operator+");




  /*Test subtract*/
  M5Vec2::Sub(result, testValue, testValue);
  testValue.x = testValue.y = 0.0f;
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2Sub not working");

  testValue.x = testValue.y = 1.5f;
  result = testValue - testValue;
  testValue.x = testValue.y = 0.f;
  M5Debug::TestResult(result == testValue, "Vec2::operator-");




  /*Test isZero*/
  flag = M5Vec2::IsZero(result);
  M5Debug::TestResult(flag, "Vec2::IsZero");
  M5Debug::TestResult(result.IsZero(), "Vec2::IsZero");

  flag = M5Vec2::IsZero(vec0);
  M5Debug::TestResult(!flag, "Vec2IsZero");
  M5Debug::TestResult(!vec0.IsZero(), "Vec2::IsZero");




  /*Test scale*/
  testValue.x = testValue.y = 1.0f;
  M5Vec2::Scale(result, testValue, 2.35f);
  testValue.x = testValue.y = 2.35f;
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2Scale");

  testValue.x = testValue.y = 1.0f;
  result = testValue * 2.35f;
  testValue.x = testValue.y = 2.35f;
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2::operator*");

  testValue.x = testValue.y = 1.0f;
  result = 2.35f * testValue;
  testValue.x = testValue.y = 2.35f;
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2::operator*");
  



  /*Test negate*/
  result.x = result.y = 1.f;
  testValue.x = testValue.y = -1.0f;
  M5Vec2::Negate(result, result);
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2Negate");

  result.x = result.y = 1.f;
  testValue.x = testValue.y = -1.0f;
  result = -result;
  M5Debug::TestResult(result == testValue, "Vec2::operator-");




  /*Test normalize and length*/
  M5Vec2::Normalize(result, result);
  f = M5Vec2::Length(result);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.0f),"Normalize");

  result.Set(37.f, 26.f);
  result.Normalize();
  f = result.Length();
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.0f), "Normalize");

  testValue.Set(0, 2);




  /*Test normalize*/
  M5Vec2::Normalize(result, testValue);
  testValue.y = 1.0f;

  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2::Normlize");

  result.Set(0, 2);
  result.Normalize();
  testValue.y = 1.0f;
  M5Debug::TestResult(result == testValue, "Vec2::Normlize");




  /*Test length*/
  f = M5Vec2::Length(result);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.0f), "Vec2Length");

  f = result.Length();
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.0f), "Vec2Length");




  /*Test length squared*/
  M5Debug::TestResult(M5Math::IsFloatEqual(f*f, M5Vec2::LengthSquared(result)),
    "Vec2LengthSquared");

  result.Set(1, 2);
  f = result.Length();
  M5Debug::TestResult(M5Math::IsFloatEqual(f*f, result.LengthSquared()),
    "Vec2LengthSquared");




  /*Test project*/
  vec0.x = vec0.y = 2.0f;
  vec1.x = 4;
  vec1.y = 0.0f;
  M5Vec2::Project(result, vec0, vec1);
  testValue.x = 2.0f;
  testValue.y = 0.0f;
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2Project");





  /*Test Perpendicular Project*/
  M5Vec2::PerpProject(testValue, vec0, vec1);
  M5Vec2::Add(result, result, testValue);
  flag = M5Vec2::IsEqual(result, vec0);
  M5Debug::TestResult(flag, "Vec2PerpProject");




  /*Test linear interpolation */
  vec0.x = vec0.y = 0;
  vec1.x = vec1.y = 5.f;
  M5Vec2::Lerp(result, vec0, vec1, .5f);
  testValue.x = testValue.y = 2.5f;
  flag = M5Vec2::IsEqual(result, testValue);
  M5Debug::TestResult(flag, "Vec2Lerp");




  /*Test dot*/
  vec0.x = 1.f;
  vec0.y = 0.f;
  vec1.x = 0.f;
  vec1.y = 1.f;

  f = M5Vec2::Dot(vec0, vec1);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 0.f),"Vec2Dot");

  f = vec0.Dot(vec1);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 0.f), "Vec2Dot");



  /*Test Cross*/
  f = M5Vec2::CrossZ(vec0, vec1);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.0f), "Vec2Cross");

  f = M5Vec2::CrossZ(vec1, vec0);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, -1.0f), "Vec2Cross");

  f = vec0.CrossZ(vec1);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.0f), "Vec2Cross");

  f = vec1.CrossZ(vec0);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, -1.0f), "Vec2Cross");




  /*Test distance*/
  f = M5Vec2::Distance(vec0, vec1);
  /*1.41 is the square root of 2*/
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.4142135f), "Vec2Distance");

  f = vec0.Distance(vec1);
  M5Debug::TestResult(M5Math::IsFloatEqual(f, 1.4142135f), "Vec2Distance");



  /*Test distance squared*/
  M5Debug::TestResult(M5Math::IsFloatEqual(f*f,
    M5Vec2::DistanceSquared(vec0, vec1)),
    "Vec2DistanceSquared");

  M5Debug::TestResult(M5Math::IsFloatEqual(f*f,
    vec0.DistanceSquared(vec1)), "Vec2DistanceSquared");

}

void M5MathTest(void)
{
  float f;     //my float result
  int i;       //my int result
  bool result; //my bool result

  using namespace M5Math;

  printf("Test Basic Math Functions**********\n");

  //Test IsFloatEqual
  result = IsFloatEqual(0, 0);
  M5Debug::TestResult(result == true, "IsFloatEqual");

  result = IsFloatEqual(0, 0 + EPSILON);
  M5Debug::TestResult(result != true, "IsFloatEqual");

  result = IsFloatEqual(1.0000001f, 1.0f);
  M5Debug::TestResult(result == true, "IsFloatEqual");




  /*Test radian to degree and degree to radian*/
  f = RadianToDegree(HALF_PI);
  M5Debug::TestResult(IsFloatEqual(f, 90.f), "RadianToDegree");

  f = DegreeToRadian(60.f);
  M5Debug::TestResult(IsFloatEqual(f, PI / 3.f), "DegreeToRadian");

  f = RadianToDegree(DegreeToRadian(90.f));
  M5Debug::TestResult(IsFloatEqual(f, 90.f), "Radian/Degree");




  /*Test clamp*/
  f = Clamp(1.25f, 1.0f, 2.0f);
  M5Debug::TestResult(IsFloatEqual(f, 1.25f), "Clamp");

  f = Clamp(-1.25, 1.0f, 2.0f);
  M5Debug::TestResult(IsFloatEqual(f, 1.0f), "Clamp");

  f = Clamp(400.25, 1.0f, 2.1f);
  M5Debug::TestResult(IsFloatEqual(f, 2.1f), "Clamp");




  /*Test Wrap*/
  f = Wrap(1.25f, 1.0f, 2.0f);
  M5Debug::TestResult(IsFloatEqual(f, 1.25f), "Wrap");

  f = Wrap(-1.25, 1.0f, 2.1f);
  M5Debug::TestResult(IsFloatEqual(f, 2.1f), "Wrap");

  f = Wrap(4.25, 1.3f, 2.1f);
  M5Debug::TestResult(IsFloatEqual(f, 1.3f), "Wrap");




  /*Test min*/
  f = Min(1.25f, 2.25f);
  M5Debug::TestResult(IsFloatEqual(f, 1.25f), "Min");

  f = Min(2.34f, 2.29f);
  M5Debug::TestResult(IsFloatEqual(f, 2.29f), "Min");




  /*Test max*/
  f = M5Math::Max(1.25f, 2.25f);
  M5Debug::TestResult(IsFloatEqual(f, 2.25f), "Max");

  f = M5Math::Max(4.25f, 2.25f);
  M5Debug::TestResult(IsFloatEqual(f, 4.25f), "Max");




  /*Test InRange*/
  result = IsInRange(1.0f, 0.0f, 10.0f);
  M5Debug::TestResult(result == true, "IsInRange");

  result = IsInRange(-1.0f, 0.0f, 10.0f);
  M5Debug::TestResult(result == false, "IsInRange");

  result = IsInRange(10.1f, 0.0f, 10.0f);
  M5Debug::TestResult(result == false, "IsInRange");




  /*Test IsPowerof2*/
  result = IsPowerOf2(1024);
  M5Debug::TestResult(result == true, "IsPowerOfTwo");
  
  result = IsPowerOf2(1023);
  M5Debug::TestResult(result == false, "IsPowerOfTwo");




  /*Test get next power of two */
  i = GetNextPowerOf2(0);
  M5Debug::TestResult(i == 1, "GetNextPowerOf2");

  i = M5Math::GetNextPowerOf2(1);
  M5Debug::TestResult(i == 2, "GetNextPowerOf2");

  i = M5Math::GetNextPowerOf2(5);
  M5Debug::TestResult(i == 8, "GetNextPowerOf2");
}
