/*******************************************************************************
 User Interface File

  Company:
    Microchip Technology Inc.

  File Name:
    psf_adc.c

  Summary:
    This file interacts with user through the terminal.

  Description:
    This file is based on UART functionality which interacts with user through the terminal.
 *******************************************************************************/
/*******************************************************************************
Copyright © [2022] Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software and
any derivatives exclusively with Microchip products. It is your responsibility
to comply with third party license terms applicable to your use of third party
software (including open source software) that may accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES
OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE. IN
NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN
ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST
EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU
HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdlib.h>		// Defines EXIT_FAILURE
#include <string.h>
#include <math.h>
#include "definitions.h"	// SYS function prototypes
#include "psf_stdinc.h"		// PSF include file
#include "psf_adc.h"
#include "psf_control_terminal.h"

/*******************************************************************/
/******************* Global variables********************************/
/*******************************************************************/
extern UINT8 gu8PDContract;
UINT8 gu8CurrentPos;

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: defines                                                */
/* ************************************************************************** */
/* ************************************************************************** */

#define   ADC_VREF         (3300U)	// 3300mV (3.3V)

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

void PSF_SinkSelectMode()
{
    UINT8 u8SrcPower[DPM_MAX_PDO_CNT][DPM_2_DIMENSION_TO_STORE_INDEX_AND_PWR] = {SET_TO_ZERO};
    UINT8 u8SinkPower[DPM_MAX_PDO_CNT][DPM_2_DIMENSION_TO_STORE_INDEX_AND_PWR] = {SET_TO_ZERO};
    UINT8 u8SinkIndex = SET_TO_ZERO;
    UINT8 u8SourcePDOIndex;
    UINT32 u32RcvdSrcPDO;
    UINT8 u8SinkPDOIndex;
    UINT32 u32SinkPDO;

    UINT8 u8SinkMode = (gasCfgStatusData.sPerPortData[PORT0].u8SinkConfigSel & DPM_SINK_CONFIG_SINK_MODE_SEL_MASK);
    /* Calculate and sort the power of Sink PDOs */
    DPM_CalculateAndSortPower (gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt, gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO, u8SinkPower, u8SinkMode);
    
    /* Calculate and sort the received source PDOs power */
    DPM_CalculateAndSortPower (gasCfgStatusData.sPerPortData[PORT0].u8PartnerSourcePDOCnt, gasCfgStatusData.sPerPortData[PORT0].u32aPartnerSourcePDO, u8SrcPower, u8SinkMode);
    
    /* Storing PDO index of the Source PDO which has maximum power.*/
    u8SourcePDOIndex = u8SrcPower[DPM_PDO_WITH_MAX_PWR][DPM_PDO_INDEX];
    /* Storing Source PDO which has maximum power*/
    u32RcvdSrcPDO = gasCfgStatusData.sPerPortData[PORT0].u32aPartnerSourcePDO[u8SourcePDOIndex];
    for (u8SinkIndex = SET_TO_ZERO; u8SinkIndex < gasCfgStatusData.sPerPortData[PORT0].u8SinkPDOCnt; u8SinkIndex++)
    {
        /* Comparing whether any of Sink power is less than or 
         * equal to maximum Source power*/
        if (u8SinkPower[u8SinkIndex][DPM_PDO_PWR] <= u8SrcPower[DPM_PDO_WITH_MAX_PWR][DPM_PDO_PWR])
        {
            u8SinkPDOIndex = u8SinkPower[u8SinkIndex][DPM_PDO_INDEX];
            u32SinkPDO = gasCfgStatusData.sPerPortData[PORT0].u32aSinkPDO[u8SinkPDOIndex];
            if ((DPM_GET_PDO_VOLTAGE(u32SinkPDO) == DPM_GET_PDO_VOLTAGE(u32RcvdSrcPDO)) && \
                (DPM_GET_PDO_CURRENT(u32SinkPDO)) <= DPM_GET_PDO_CURRENT(u32RcvdSrcPDO))
            { 
                /*Update Negotiated value*/
                gasCfgStatusData.sPerPortData[PORT0].u16NegoVoltageInmV = (DPM_GET_PDO_VOLTAGE(u32SinkPDO) * DPM_PDO_VOLTAGE_UNIT);
                /*Update Negotiated value*/
                gasCfgStatusData.sPerPortData[PORT0].u16NegoCurrentInmA = (DPM_GET_PDO_CURRENT(u32SinkPDO) * DPM_PDO_CURRENT_UNIT);               
                /*Advertise the sink PDO in switch case*/
            }
        }
    }
    return;
}
void PSF_ADCRun()
{
    //If the ADC is in the same position,no renegotiation happens, else it renegotiates.
    UINT8 u8PrevPos = gu8CurrentPos; 
	UINT16 u16adc_count;
	UINT32 u32input_voltage;
	UINT8 *pu8PrintString;
	static ADC_RUN_STATE u8State = eADC_INIT;
	UINT8 StrPrint[] = "\n\n\r> Knob Voltage 0x";
    
	switch (u8State) 
    {
        case eADC_INIT:
        {
            ADC_Enable();
            ADC_ConversionStart();
            u8State = eADC_WAIT_FOR_CONVERSION;
            break;
        }
        case eADC_WAIT_FOR_CONVERSION:
        {
            if (!ADC_ConversionStatusGet()) 
            {
                u8State = eADC_WAIT_FOR_CONVERSION;
            } 
            else 
            {
                u8State = eADC_SET_NEW_PDO;
            }
            break;
        }
        case eADC_SET_NEW_PDO:
        {
            /*
             * Read the ADC Result 
             */
            u16adc_count = ADC_ConversionResultGet();
            u32input_voltage = u16adc_count * ADC_VREF / 4095U;
            memset(gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO,0,7*4);
            
            if(!(gu8PDContract == true))
            {
                u8State = eADC_INIT;
                break;
            }
            gasCfgStatusData.sPerPortData[PORT0].u8SinkConfigSel = CFG_PORT_0_SINK_CONFIG_SEL;
            
            if (300U < u32input_voltage && u32input_voltage < 600U) 
            {
                /*Position 1*/
                /*Supported PDO is (5V,3A)*/
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
                gasCfgStatusData.sPerPortData[PORT0].u8NewSinkPDOCnt = 1;
                gu8CurrentPos = 1; 
            } 
            else if (700U < u32input_voltage && u32input_voltage < 1000U)
            {
                /*Position 2*/
                /*Supported PDOs are (5V,3A), (9V,3A)*/
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
                gasCfgStatusData.sPerPortData[PORT0].u8NewSinkPDOCnt = 2;
                gu8CurrentPos = 2;
            } 
            else if (1100U < u32input_voltage && u32input_voltage < 1400U)  
            {
                /*Position 3*/
                /*Supported PDOs are (5V,3A), (15V,3A)*/
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[1] = CFG_PORT_0_SINK_PDO_3;
                gasCfgStatusData.sPerPortData[PORT0].u8NewSinkPDOCnt = 2;
                gu8CurrentPos = 3;
            } 
            else if (1625U < u32input_voltage && u32input_voltage < 1800U) 
            {
                /*Position 4*/
                /*Supported PDOs are (5V,3A), (20V,3A)*/
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[1] = CFG_PORT_0_SINK_PDO_4;
                gasCfgStatusData.sPerPortData[PORT0].u8NewSinkPDOCnt = 2;
                gu8CurrentPos = 4;
            }
            else if (1900U < u32input_voltage && u32input_voltage < 2200U) 
            {
                /*Position 5*/
                /*Operates in Sink Mode A*/
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[2] = CFG_PORT_0_SINK_PDO_3;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[3] = CFG_PORT_0_SINK_PDO_4;
                gasCfgStatusData.sPerPortData[PORT0].u8NewSinkPDOCnt = 4;
                /* BIT[1:0] - Sink Selection mode for operation.
                1. '0x00' Mode A: Prefer Higher Voltage and Wattage
                2. '0x01' Mode B: Prefer Lower Voltage and Wattage */
                gasCfgStatusData.sPerPortData[PORT0].u8SinkConfigSel = CFG_PORT_0_SINK_CONFIG_SEL;
                gu8CurrentPos = 5;
            } 
            else if (2100U < u32input_voltage && u32input_voltage < 2700U)  
            {
                /*Position 6*/
                /*Operates in Sink Mode B*/
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[0] = CFG_PORT_0_SINK_PDO_1;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[1] = CFG_PORT_0_SINK_PDO_2;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[2] = CFG_PORT_0_SINK_PDO_3;
                gasCfgStatusData.sPerPortData[PORT0].u32aNewSinkPDO[3] = CFG_PORT_0_SINK_PDO_4;
                gasCfgStatusData.sPerPortData[PORT0].u8NewSinkPDOCnt = 4;
                /* BIT[1:0] - Sink Selection mode for operation.
                1. '0x00' Mode A: Prefer Higher Voltage and Wattage
                2. '0x01' Mode B: Prefer Lower Voltage and Wattage */
                gasCfgStatusData.sPerPortData[PORT0].u8SinkConfigSel = CFG_PORT_0_SINK_CONFIG_SEL;
                gu8CurrentPos = 6;
            } 
            else
            {
                /*Do nothing*/
            }

            if (gu8CurrentPos != u8PrevPos)
            {
                u8PrevPos = gu8CurrentPos;
                /*
                 * modify the pdo list as per the new position 
                 * User application may request PSF to renegotiate based
                 * on default PDOs
                 * gasCfgStatusData.sPerPortData[u8PortNum].u32aSinkPDO)
                 * or
                 * gasCfgStatusData.sPerPortData[u8PortNum].u32aNewSinkPDO).
                 * 
                 * To renegotiate with new PDOs, user application must
                 * ensure that new PDOs
                 * (gasCfgStatusData.sPerPortData[u8PortNum].u32aNewSinkPDO) 
                 * are configured and BIT(10) in
                 * gasCfgStatusData.sPerPortData[u8PortNum].u32CfgData
                 * variable is set. Then BIT(5) in
                 * gasCfgStatusData.sPerPortData[u8PortNum].u32ClientRequest
                 * variable needs to be set by the user application. 
                 */
                gasCfgStatusData.sPerPortData[PORT0].u32CfgData |= DPM_CFG_NEGOTIATE_USING_NEW_PDOS;
                gasCfgStatusData.sPerPortData[PORT0].u32ClientRequest |= DPM_CLIENT_REQ_RENEGOTIATE;
                

                DEBUG_PRINT_PORT_STR(PSF_APPLICATION_LAYER_DEBUG_MSG,PORT0,"\n\n\r> Client Req set");

                /*clear the variables since the request is handled */
                gu8PDContract = false;
                
                /*Print the selected knob voltage*/
                pu8PrintString = HextoAscii(u32input_voltage,sizeof(u32input_voltage));
                PCTWrite(StrPrint,(UINT8 *) & pu8PrintString[0],sizeof(pu8PrintString),sizeof(StrPrint));
            }
            u8State = eADC_INIT;
            break;
        }
	}
}
/*Gets the ADC position for boot time PDO configuration */
UINT8 Get_ADCPosition()
{
	UINT16 u16adc_count;
	UINT32 u32input_voltage;
    
    ADC_Enable();
    ADC_ConversionStart();
    while (!ADC_ConversionStatusGet()) ;
    u16adc_count = ADC_ConversionResultGet();
    u32input_voltage = u16adc_count * ADC_VREF / 4095U;
    
    if (300U < u32input_voltage && u32input_voltage < 600U) 
    {
        gu8CurrentPos = 1;
    } 
    else if (700U < u32input_voltage && u32input_voltage < 1000U) 
    {
        gu8CurrentPos = 2;
    } 
    else if (1100U < u32input_voltage && u32input_voltage < 1400U) 
    {
        gu8CurrentPos = 3;
    } 
    else if (1625U < u32input_voltage && u32input_voltage < 1800U) 
    {
        gu8CurrentPos = 4;
    }
    else if (1900U < u32input_voltage && u32input_voltage < 2200U) 
    {
        gu8CurrentPos = 5;
    } 
    else if (2100U < u32input_voltage && u32input_voltage < 2700U) 
    {
        gu8CurrentPos = 6;
    } 
    return gu8CurrentPos;
}