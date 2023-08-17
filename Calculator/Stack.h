/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
//#ifndef XC_HEADER_TEMPLATE_H
//#define	XC_HEADER_TEMPLATE_H
//
//#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

//#ifdef	__cplusplus
//extern "C" {
//#endif /* __cplusplus */
//
//    // TODO If C++ is being used, regular C code needs function names to have C 
//    // linkage so the functions can be used by the c code. 
//
//#ifdef	__cplusplus
//}
//#endif /* __cplusplus */
//
//#endif	/* XC_HEADER_TEMPLATE_H */
#include <stdint.h>
#include <stdint.h>
#include <math.h>

#define MAX 15
#define datatype uint8_t

typedef struct {
    datatype elements[MAX];
    int8_t top;
}Stak;
/*--------------------------------------------------------------*/
void StakInit(Stak *);
int IsEmtyStak(Stak);
int IsFullStak(Stak);
int push(datatype , Stak *);
int pop(Stak *,datatype *);
void staktop(Stak *,datatype *);
int StakSiz(Stak);
/*--------------------------------------------------------------*/
uint8_t Precedent(char a, char b);
uint8_t Isdigit(char a);
/*--------------------------------------------------------------*/
uint8_t operation_MultiDigit(uint8_t a, uint8_t b, uint8_t c);
void TORPN_MutiDigit(char exp[], char rpn[]);
uint8_t Calc_RPN_MutiDigit(char rpn[]);