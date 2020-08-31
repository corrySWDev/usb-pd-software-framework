/***************************************************************************
  Power Delivery Source Pro Configurable globals Header File

  Company:
    Microchip Technology Inc.

  File Name:
    PSFSink_BootCfg.h

  Description:
    This header file contains user configurable globals and function prototypes.
************************************************************************** */
/*******************************************************************************
Copyright �  [2019-2020] Microchip Technology Inc. and its subsidiaries.

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

#ifndef _PSFSINK_BOOTCFG_H    /* Guard against multiple inclusion */
#define _PSFSINK_BOOTCFG_H

#define PRODUCT_ID              0x301CU
#define VENDOR_ID               0x0424U
#define PRODUCT_TYPE_VDO        0x0000U
#define PRODUCT_VDO             0x0000U  
#define CERT_STAT_VDO           0x0000U
#define ID_HEADER_VDO           0x0000U
#define HW_VERSION              0x00U
#define SILICON_VERSION         0x00U

#define CFG_PORT_POWER_ROLE                0U //Sink
#define CFG_PORT_RP_CURRENT_VALUE          (0U << TYPEC_PORT_RPVAL_POS) /*For Sink Rp value is 0*/
#define CFG_PORT_ENABLE                    (1U << TYPEC_PORT_ENDIS_POS)
#define CFG_PORT_SOURCE_NUM_OF_PDOS        4U
#define CFG_PORT_SOURCE_USB_SUSP           0U
#define CFG_PORT_SOURCE_UNCONSTARINED_PWR  1U
#define CFG_PORT_SOURCE_USB_COMM           0U

#define CFG_PORT_SOURCE_PDO_1_CURRENT      3000U 
#define CFG_PORT_SOURCE_PDO_2_CURRENT      3000U
#define CFG_PORT_SOURCE_PDO_3_CURRENT      3000U
#define CFG_PORT_SOURCE_PDO_4_CURRENT      3000U
#define CFG_PORT_SOURCE_PDO_5_CURRENT      0U
#define CFG_PORT_SOURCE_PDO_6_CURRENT      0U
#define CFG_PORT_SOURCE_PDO_7_CURRENT      0U

#define CFG_PORT_SOURCE_PDO_1_VOLTAGE      5000
#define CFG_PORT_SOURCE_PDO_2_VOLTAGE      9000
#define CFG_PORT_SOURCE_PDO_3_VOLTAGE      15000
#define CFG_PORT_SOURCE_PDO_4_VOLTAGE      20000
#define CFG_PORT_SOURCE_PDO_5_VOLTAGE      0
#define CFG_PORT_SOURCE_PDO_6_VOLTAGE      0
#define CFG_PORT_SOURCE_PDO_7_VOLTAGE      0

#define CFG_PORT_SINK_NUM_OF_PDOS          4U
#define CFG_PORT_SINK_HIGHER_CAPABILITY    1U
#define CFG_PORT_SINK_UNCONSTRAINED_PWR    1U //Set to 1
#define CFG_PORT_SINK_USB_COMM             0U

#define CFG_PORT_SINK_PDO_1_CURRENT        3000U 
#define CFG_PORT_SINK_PDO_2_CURRENT        3000U
#define CFG_PORT_SINK_PDO_3_CURRENT        3000U
#define CFG_PORT_SINK_PDO_4_CURRENT        3000U
#define CFG_PORT_SINK_PDO_5_CURRENT        0U
#define CFG_PORT_SINK_PDO_6_CURRENT        0U
#define CFG_PORT_SINK_PDO_7_CURRENT        0U

#define CFG_PORT_SINK_PDO_1_VOLTAGE        5000
#define CFG_PORT_SINK_PDO_2_VOLTAGE        9000
#define CFG_PORT_SINK_PDO_3_VOLTAGE        15000
#define CFG_PORT_SINK_PDO_4_VOLTAGE        20000
#define CFG_PORT_SINK_PDO_5_VOLTAGE        0
#define CFG_PORT_SINK_PDO_6_VOLTAGE        0
#define CFG_PORT_SINK_PDO_7_VOLTAGE        0

#define CFG_PORT_SINK_PDO_1_PREFERRED_MIN_CURRENT 2000
#define CFG_PORT_SINK_PDO_2_PREFERRED_MIN_CURRENT 2000
#define CFG_PORT_SINK_PDO_3_PREFERRED_MIN_CURRENT 2000
#define CFG_PORT_SINK_PDO_4_PREFERRED_MIN_CURRENT 2000
#define CFG_PORT_SINK_PDO_5_PREFERRED_MIN_CURRENT 0
#define CFG_PORT_SINK_PDO_6_PREFERRED_MIN_CURRENT 0
#define CFG_PORT_SINK_PDO_7_PREFERRED_MIN_CURRENT 0

#define CFG_MAX_PDO_COUNT                 7
#define CFG_OVER_VOLTAGE_FACTOR			  115
#define CFG_UNDER_VOLTAGE_FACTOR		  85
#define CFG_MAX_VBUS_POWER_FAULT_COUNT	  3
#define CFG_MAX_VCONN_FAULT_COUNT		  3
#define CFG_POWER_GOOD_TIMER_MS			  10000
#define CFG_PORT_SINK_MODE_A              0x00
#define CFG_PORT_SINK_MODE_B              0x01
#define CFG_PORT_SINK_GIVE_BACK_FLAG      0
#define CFG_PORT_SINK_USB_SUSP            0


/*********************DAC_I defines******************/
#define CFG_PORT_SINK_DAC_I_MAX_OP_VOLTAGE             2500
#define CFG_PORT_SINK_DAC_I_MIN_OP_VOLTAGE             0
#define CFG_PORT_SINK_DAC_I_CUR_INDICATION_MAX         5000
#define CFG_PORT_SINK_DAC_I_DIR_HIGH_AMP_MAX_VOLT      0
#define CFG_PORT_SINK_DAC_I_DIR_HIGH_AMP_MIN_VOLT      1

/*****************Sink Hardware defines**************/
#define CFG_PORT_SINK_MIN_OPERATING_CURRENT_InmA             1000
#define CFG_PORT_SINK_MAX_OPERATING_CURRENT_InmA             3000

#define CFG_PORT_UPD_FAULT_IN_PIO_NO       eUPD_PIO5
#define CFG_PORT_UPD_FAULT_IN_MODE         eFAULT_IN_ACTIVE_LOW
#define CFG_PORT_UPD_EN_SNK                eUPD_PIO6
#define CFG_PORT_UPD_EN_SNK_PIO_MODE       ePUSH_PULL_ACTIVE_HIGH

#define CFG_VCONN_OCS_ENABLE               1 << TYPEC_VCONN_OCS_EN_POS
#define CFG_VCONN_OCS_DEBOUNCE_IN_MS       2
#define CFG_FAULT_IN_OCS_DEBOUNCE_MS       5

#define CFG_PDO_VOLTAGE_POS                   10 
#define CFG_PDO_VOLTAGE_UNIT                  50
#define CFG_PDO_CURRENT_UNIT                  10
#define CFG_PDO_USB_SUSPEND_POS               28 
#define CFG_PDO_USB_COMMN_POS                 26 
#define CFG_PDO_UNCONSTRAINED_PWR_POS         27
#define CFG_PDO_HIGHER_CAPABILITY_POS         28

/* Macro used to form Source Fixed PDO 1 */
#define CFG_FORM_FIXED_PDO1(voltage,current,usbCommn,usbSusp,unconstrainedPwr)  (((usbSusp) << CFG_PDO_USB_SUSPEND_POS) | \
                                         ((unconstrainedPwr) << CFG_PDO_UNCONSTRAINED_PWR_POS) | \
                                         ((usbCommn) << CFG_PDO_USB_COMMN_POS) | \
                                         (((voltage)/CFG_PDO_VOLTAGE_UNIT) << CFG_PDO_VOLTAGE_POS) | \
                                         ((current)/CFG_PDO_CURRENT_UNIT))            

/* Macro used to form Sink Fixed PDO 1 */
#define CFG_FORM_SINK_FIXED_PDO1(current,voltage,usbCommn,unconstrainedPwr,HigherCapability)  \
                                         (((HigherCapability) << CFG_PDO_HIGHER_CAPABILITY_POS) | \
                                         ((unconstrainedPwr) << CFG_PDO_UNCONSTRAINED_PWR_POS) | \
                                         ((usbCommn) << CFG_PDO_USB_COMMN_POS) | \
                                         (((voltage)/CFG_PDO_VOLTAGE_UNIT) << CFG_PDO_VOLTAGE_POS) | \
                                         ((current)/CFG_PDO_CURRENT_UNIT))  

/* Macro used to form Fixed PDOs 2 to 7 */
#define CFG_FORM_FIXED_PDOx(voltage,current)        ((((voltage)/CFG_PDO_VOLTAGE_UNIT) << CFG_PDO_VOLTAGE_POS) | \
                                                            ((current)/CFG_PDO_CURRENT_UNIT))
void PSF_LoadConfig(); 

#endif /* _PSFSINK_BOOTCFG_H */

/* *****************************************************************************
 End of File
 */