/*
     File:       vecLib/vBasicOps.h
 
     Contains:   Basic Algebraic Operations for AltiVec
 
     Version:    vecLib-138.1~9
 
     Copyright:  ? 1999-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VBASICOPS__
#define __VBASICOPS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __VEC__
/*                                                                                  
  This section is a collection of algebraic functions that uses the AltiVec       
  instruction set, and is designed to facilitate vector processing in             
  mathematical programming. Following table indicates which functions are covered
  by AltiVec instruction set and which ones are performed by vBasicOps library:

Legend:
    H/W   = Hardware
    LIB  = vBasicOps Library
    NRel  = Next Release of vBasicOps Library
    N/A   = Not Applicable

+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
| Data Type/    | U8  | S8  | U16 | S16 | U32 | S32 | U64 | S64 | U128 | S128 |
| Function      |     |     |     |     |     |     |     |     |      |      |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Add        | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  |  LIB |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    AddS       | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Sub        | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    SubS       | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|  Mul(Half)    | LIB | LIB | LIB | LIB | LIB | LIB | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|Mul Even (Full)| H/W | H/W | H/W | H/W | LIB | LIB | LIB | LIB |  N/A |  N/A |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|Mul Odd  (Full)| H/W | H/W | H/W | H/W | LIB | LIB | LIB | LIB |  N/A |  N/A |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Divide     | LIB | LIB | LIB | LIB | LIB | LIB | LIB |NRel | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Shift      | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Rotate     | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+



Following is a short description of functions in this section:
                                                                         
      Add:      It takes two vectors of data elements and adds each element         
                of the second vector to the corresponding element of the first      
                vector and puts the result in the associated data element of the    
                destination register.

      Subtract: It takes two vectors of data elements and subtracts each element    
                of the second vector from the corresponding element of the first    
                vector and puts the result in the associated data element of the    
                destination register.

      Multiply: It takes two vectors of data elements and multiplies each element   
                of the first vector by the corresponding element of the second      
                vector and puts the result in the associated data element of the    
                destination register. 

      Divide:   It takes two vectors of data elements and divides each element      
                of the first vector by the corresponding element of the second      
                vector and puts the result in the associated data element of the    
                destination register. A pointer is passed to the function to get   
                the remainder.

      Shift:    It takes a vector of two 64-bit data elements or one 128-bit
                data element and shifts it to right or left, in a logical or 
                algebraic manner, using a shift factor that is passed as an
                arguement to the function.

      Rotate:   It takes a vector of two 64-bit data elements or one 128-bit
                data element and rotates it to right or left, using a shift 
               factor that is passed as an arguement to the function.


   Following abbreviations are used in the names of functions in this section:   
                                                                                 
      v            Vector                                                        
      U            Unsigned                                                      
      S            Signed                                                        
      8            8-bit                                                         
      16           16-bit                                                        
      32           32-bit                                                        
      64           64-bit                                                        
      128          128-bit                                                       
      Add          Addition                                                      
      AddS         Addition with Saturation                                      
      Sub          Subtraction                                                   
      SubS         Subtraction with Saturation                                   
      Mul          Multiplication                                                
      Divide       Division                                                      
      Half         Half (multiplication, width of result is the same as width of 
                      operands)                                                  
      Full         Full (multiplication, width of result is twice width of each  
                      operand)                                                   
      Even         Multiplication is performed on EVEN data elements of vector   
                      (Please note that Big endian is used. So the left-most     
                      data element is labled as element 0)                       
      Odd          Multiplication is performed on ODD  data elements of vector.  
      A            Algebraic      
      LL           Logical Left     
      LR           Logical Right     
      Shift        Shift by one factor     
      Shift2       Shift by two factors( only apply to 64 bit operation )     
      Rotate       Rotate by one factor     
      Rotate2      Rotate by two factors( only apply to 64 bit operation )     
                                                                                 
*/

/*
 *  vU8Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned char 
vU8Divide(
  vector unsigned char    vN,
  vector unsigned char    vD,
  vector unsigned char *  vRemainder)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS8Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed char 
vS8Divide(
  vector signed char    vN,
  vector signed char    vD,
  vector signed char *  vRemainder)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU16Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned short 
vU16Divide(
  vector unsigned short    vN,
  vector unsigned short    vD,
  vector unsigned short *  vRemainder)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS16Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed short 
vS16Divide(
  vector signed short    vN,
  vector signed short    vD,
  vector signed short *  vRemainder)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU32Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU32Divide(
  vector unsigned int    vN,
  vector unsigned int    vD,
  vector unsigned int *  vRemainder)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS32Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS32Divide(
  vector signed int    vN,
  vector signed int    vD,
  vector signed int *  vRemainder)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU64Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64Divide(
  vector unsigned int    vN,
  vector unsigned int    vD,
  vector unsigned int *  vRemainder)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64Divide(
  vector signed int    vN,
  vector signed int    vD,
  vector signed int *  vRemainder)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU128Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU128Divide(
  vector unsigned int    vN,
  vector unsigned int    vD,
  vector unsigned int *  vRemainder)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS128Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS128Divide(
  vector signed int    vN,
  vector signed int    vD,
  vector signed int *  vRemainder)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vU8HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned char 
vU8HalfMultiply(
  vector unsigned char   vA,
  vector unsigned char   vB)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS8HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed char 
vS8HalfMultiply(
  vector signed char   vA,
  vector signed char   vB)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU16HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned short 
vU16HalfMultiply(
  vector unsigned short   vA,
  vector unsigned short   vB)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS16HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed short 
vS16HalfMultiply(
  vector signed short   vA,
  vector signed short   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU32HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU32HalfMultiply(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS32HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS32HalfMultiply(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU32FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU32FullMulEven(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU32FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU32FullMulOdd(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS32FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS32FullMulEven(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS32FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS32FullMulOdd(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU64FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64FullMulEven(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU64FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64FullMulOdd(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU64HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64HalfMultiply(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64HalfMultiply(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64FullMulEven(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64FullMulOdd(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU128HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU128HalfMultiply(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS128HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS128HalfMultiply(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vU64Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64Sub(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU64SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64SubS(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU128Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU128Sub(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU128SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU128SubS(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64Sub(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS128Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS128Sub(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64SubS(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS128SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS128SubS(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vU64Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64Add(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU64AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU64AddS(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU128Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU128Add(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vU128AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vU128AddS(
  vector unsigned int   vA,
  vector unsigned int   vB)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64Add(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS64AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS64AddS(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS128Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS128Add(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vS128AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector signed int 
vS128AddS(
  vector signed int   vA,
  vector signed int   vB)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vLL64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vLL64Shift(
  vector unsigned int    vA,
  vector unsigned char   vShiftFactor)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vA64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vA64Shift(
  vector unsigned int    vA,
  vector unsigned char   vShiftFactor)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLR64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vLR64Shift(
  vector unsigned int    vA,
  vector unsigned char   vShiftFactor)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLL64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vLL64Shift2(
  vector unsigned int    vA,
  vector unsigned char   vShiftFactor)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vA64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vA64Shift2(
  vector unsigned int    vA,
  vector unsigned char   vShiftFactor)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vLR64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vLR64Shift2(
  vector unsigned int    vA,
  vector unsigned char   vShiftFactor)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vA128Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vA128Shift(
  vector unsigned int    vA,
  vector unsigned char   vShiftFactor)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  vL64Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vL64Rotate(
  vector unsigned int    vA,
  vector unsigned char   vRotateFactor)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vR64Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vR64Rotate(
  vector unsigned int    vA,
  vector unsigned char   vRotateFactor)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vL64Rotate2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vL64Rotate2(
  vector unsigned int    vA,
  vector unsigned char   vRotateFactor)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vR64Rotate2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vR64Rotate2(
  vector unsigned int    vA,
  vector unsigned char   vRotateFactor)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vL128Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vL128Rotate(
  vector unsigned int    vA,
  vector unsigned char   vRotateFactor)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vR128Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with Carbon
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vector unsigned int 
vR128Rotate(
  vector unsigned int    vA,
  vector unsigned char   vRotateFactor)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#endif  /* defined(__VEC__) */


#ifdef __cplusplus
}
#endif

#endif /* __VBASICOPS__ */

