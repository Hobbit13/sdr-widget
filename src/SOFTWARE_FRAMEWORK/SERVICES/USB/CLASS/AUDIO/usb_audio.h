/* -*- mode: c++; tab-width: 4; c-basic-offset: 4 -*- */
/* This header file is part of the ATMEL AVR32-SoftwareFramework-AT32UC3-1.X.X Release */

/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Management of the generic USB Audio features.
 *
 * This file manages the generic USB Audio features.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with a USB module can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *							Modified for USB Audio Class V2.0 by
 *							Ken McGuire
 *
 *
 ******************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 *
 * Modified by Alex Lee 20 Feb 2010
 * To enumerate as a USB composite device with 4 interfaces:
 * CDC
 * HID (generic HID interface, compatible with Jan Axelson's generichid.exe test programs
 * DG8SAQ (libusb API compatible interface for implementing DG8SAQ EP0 type of interface)
 * Audio (Start with Audio Class v1.  Will progress to Audio Class V2.  Tweaked for
 * 		compatibility when running at HIGH speed USB.)
 * For SDR-Widget and SDR-Widget-lite, custom boards based on the AT32UC3A3256
 *
 * See http://code.google.com/p/sdr-widget/
 *
 * Modified by Alex Lee and sdr-widget team since Feb 2010.  Copyright General Purpose Licence v2.
 * Please refer to http://code.google.com/p/sdr-widget/
 *
 * Modified by Ken McGuire and Loftur Jonasson 2010
 */

#ifndef _USB_AUDIO_H_
#define _USB_AUDIO_H_


//_____ I N C L U D E S ________________________________________________________


//_____ M A C R O S ____________________________________________________________
#define CS_INTERFACE                    0x24
#define CS_ENDPOINT                     0x25
#define GENERAL_SUB_TYPE                0x01
#define FORMAT_SUB_TYPE                 0x02
#define HEADER_SUB_TYPE                 0x01
#define MIXER_UNIT_SUB_TYPE             0x04
#define FEATURE_UNIT_SUB_TYPE           0x06
#define INPUT_TERMINAL_SUB_TYPE         0x02
#define OUTPUT_TERMINAL_SUB_TYPE        0x03



//!Audio volume ctrl configuration
#define CS_MUTE   0x0100
#define CS_VOLUME 0x0200

//#define  AUDIO_CLASS_REVISION                   0x0100  //!< Revision of class specification - 1.0
#define  AUDIO_CLASS_REVISION_2                 0x0200  //!< Revision of class specification - 2.0

/*  UAC 1
#define BR_REQUEST_GET_CUR        0x81
#define BR_REQUEST_GET_MIN        0x82
#define BR_REQUEST_GET_MAX        0x83
#define BR_REQUEST_GET_RES        0x84
#define BR_REQUEST_SET_CUR        0x01
#define BR_REQUEST_SET_MIN        0x02
#define BR_REQUEST_SET_MAX        0x03
#define BR_REQUEST_SET_RES        0x04
*/

//! \name Constants used in Descriptor
//! @{
   //! \name Standard Endpoint Descriptor Types
   //! @{
#define  ENDPOINT_TYPE_NO_SYNC            0x00
#define  ENDPOINT_TYPE_ASYNCHRONOUS       0x01
#define  ENDPOINT_TYPE_ADAPTIVE           0x02
#define  ENDPOINT_TYPE_SYNCHRONOUS        0x03
#define  ENDPOINT_TYPE_OFFSET                2
   //! @}

   //! \name Audio Function Class Code pp. A.1
   //! @{
#define  AUDIO_FUNCTION                         0x01
   //! @}

   //! \name Audio Function Subclass Code pp. A.2
   //! @{
#define  AUDIO_FUNCTION_SUBCLASS_UNDEFINED      0x00
   //! @}

   //! \name Audio Function Protocol Code pp. A.3
   //! @{
#define  AUDIO_FUNCTION_PROTOCOL_UNDEFINED      0x00
#define  AUDIO_FUNCTION_VERSION_02_00			0x20
   //! @}

   //! \name Audio Interface Class Code pp. A.4
   //! @{
#define  AUDIO_INTERFACE                        0x01
   //! @}

   //! \name Audio Interface Subclass Code pp. A.5
   //! @{
#define  AUDIO_INTERFACE_SUBCLASS_UNDEFINED         0x00
#define  AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL      0x01
#define  AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING    0x02
#define  AUDIO_INTERFACE_SUBCLASS_MIDISTREAMING     0x03
   //! @}

   //! \name Audio Interface Protocol Code pp. A.6
   //! @{
#define  AUDIO_INTERFACE_PROTOCOL_UNDEFINED         0x00
#define  AUDIO_INTERFACE_IP_VERSION_02_00           0x20
#define  IP_VERSION_02_00	AUDIO_INTERFACE_IP_VERSION_02_00
   //! @}

   //! \name Audio Function Category Code pp. A.7
   //! @{
#define  AUDIO_FUNCTION_SUBCLASS_UNDEFINED                   0x00
#define  AUDIO_FUNCTION_SUBCLASS_DESKTOP_SPEAKER             0x01
#define  AUDIO_FUNCTION_SUBCLASS_HOME_THEATER                0x02
#define  AUDIO_FUNCTION_SUBCLASS_MICROPHONE                  0x03
#define  AUDIO_FUNCTION_SUBCLASS_HEADSET                     0x04
#define  AUDIO_FUNCTION_SUBCLASS_TELEPHONE                   0x05
#define  AUDIO_FUNCTION_SUBCLASS_CONVERTER                   0x06
#define  AUDIO_FUNCTION_SUBCLASS_VOICESOUND_RECORDER         0x07
#define  AUDIO_FUNCTION_SUBCLASS_IO_BOX                      0x08
#define  AUDIO_FUNCTION_SUBCLASS_MUSICAL_INSTRUMENT          0x09
#define  AUDIO_FUNCTION_SUBCLASS_PROAUDIO                    0x0A
#define  AUDIO_FUNCTION_SUBCLASS_AUDIO_VIDEO                 0x0B
#define  AUDIO_FUNCTION_SUBCLASS_CONTROL_PANEL               0x0C
#define  AUDIO_FUNCTION_SUBCLASS_OTHER                       0xFF
   //! @}

   //! \name Audio Class-Specific Descriptor Types pp. A.8
   //! @{
#define  DESCRIPTOR_AUDIO_UNDEFINED             0x20
#define  DESCRIPTOR_AUDIO_DEVICE                0x21
#define  DESCRIPTOR_AUDIO_CONFIGURATION         0x22
#define  DESCRIPTOR_AUDIO_STRING                0x23
#define  DESCRIPTOR_AUDIO_INTERFACE             0x24
#define  DESCRIPTOR_AUDIO_ENDPOINT              0x25
   //! @}

   //! \name Audio Class-Specific AC Interface Descriptor Subtypes pp. A.9
   //! @{
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_UNDEFINED              0x00
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_HEADER                 0x01
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_INPUT_TERMINAL         0x02
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_OUTPUT_TERMINAL        0x03
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_MIXER_UNIT             0x04
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_SELECTOR_UNIT          0x05
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_FEATURE_UNIT           0x06
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_EFFECT_UNIT            0x07
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_PROCESSING_UNIT        0x08
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_EXTENSION_UNIT         0x09
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_CLOCK_SOURCE           0x0A
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_CLOCK_SELECTOR         0x0B
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_CLOCK_MULTIPLIER       0x0C
#define  DESCRIPTOR_SUBTYPE_AUDIO_AC_SAMPLE_RATE_CONVERTE   0x0D
   //! @}

   //! \name Audio Class-Specific AS Interface Descriptor Subtypes pp. A.10
   //! @{
#define  DESCRIPTOR_SUBTYPE_AUDIO_AS_UNDEFINED              0x00
#define  DESCRIPTOR_SUBTYPE_AUDIO_AS_GENERAL                0x01
#define  DESCRIPTOR_SUBTYPE_AUDIO_AS_FORMAT_TYPE            0x02
#define  DESCRIPTOR_SUBTYPE_AUDIO_AS_ENCODER                0x03
#define  DESCRIPTOR_SUBTYPE_AUDIO_AS_DECODER                0x04
   //! @}

   //! \name Effect Unit Types pp. A.11
   //! @{
#define  AUDIO_EFFECT_UNIT_UNDEFINED                        0x00
#define  AUDIO_EFFECT_UNIT_PARAM_EQ                         0x01
#define  AUDIO_EFFECT_UNIT_REVERB                           0x02
#define  AUDIO_EFFECT_UNIT_MOD_DELAY                        0x03
#define  AUDIO_EFFECT_UNIT_DYN_RANGE_COMP                   0x04

#define  DESCRIPTOR_EFFECT_UNDEFINED                        0x00
#define  DESCRIPTOR_EFFECT_PARAM_EQ                         0x01
#define  DESCRIPTOR_EFFECT_REVERB                           0x02
#define  DESCRIPTOR_EFFECT_MOD_DELAY                        0x03
#define  DESCRIPTOR_EFFECT_DYN_RANGE_COMP                   0x04
   //! @}

   //! \name AProcessing Unit Types pp. A.12
   //! \name Processing Unit Process Types (in request DESCRIPTOR_AUDIO_INTERFACE + DESCRIPTOR_SUBTYPE_AUDIO_AC_PROCESSING_UNIT)
   //! @{
#define  AUDIO_PROCESSING_UNIT_UNDEFINED                    0x00
#define  AUDIO_PROCESSING_UNIT_UPDOWNMIX                    0x01
#define  AUDIO_PROCESSING_UNIT_DOLBY_PROLOGIC               0x02
#define  AUDIO_PROCESSING_UNIT_3D_STEREO_EXTENDER           0x03
#define  AUDIO_PROCESSING_UNIT_REVERBERATION                0x04
#define  AUDIO_PROCESSING_UNIT_CHORUS                       0x05
#define  AUDIO_PROCESSING_UNIT_DYN_RANGE_COMP               0x06

#define  DESCRIPTOR_PROCESS_UNDEFINED                       0x00
#define  DESCRIPTOR_PROCESS_UP_DOWNMIX                      0x01
#define  DESCRIPTOR_PROCESS_DOLBY_PROLOCIC                  0x02
#define  DESCRIPTOR_PROCESS_STEREO_EXTENDER                 0x03
   //! @}

   //! \name Audio Class-Specific Endpoint Descriptor Subtypes pp. A.13
   //! @{
#define  DESCRIPTOR_SUBTYPE_AUDIO_ENDP_UNDEFINED            0x00
#define  DESCRIPTOR_SUBTYPE_AUDIO_ENDP_GENERAL              0x01
   //! @}

   //! \name Audio Class-Specific Request Code pp. A.14
   //! @{
#define  AUDIO_CS_REQUEST_UNDEFINED                        0x00
#define  AUDIO_CS_REQUEST_CUR                              0x01
#define  AUDIO_CS_REQUEST_RANGE                            0x02
#define  AUDIO_CS_REQUEST_MEM                              0x03
   //! @}

   //! \name Audio Encoder Type Code pp. A.15
   //! @{
#define  AUDIO_ENCODER_UNDEFINED 0x00
#define  AUDIO_ENCODER_OTHER     0x01
#define  AUDIO_ENCODER_MPEG      0x02
#define  AUDIO_ENCODER_AC3       0x03
#define  AUDIO_ENCODER_WMA       0x04
#define  AUDIO_ENCODER_DTS       0x05
	//! @}

	//! \name Audio Decoder Typecode pp. A.16
	//! @{
#define  AUDIO_DECODER_UNDEFINED 0x00
#define  AUDIO_DECODER_OTHER     0x01
#define  AUDIO_DECODER_MPEG      0x02
#define  AUDIO_DECODER_AC3       0x03
#define  AUDIO_DECODER_WMA       0x04
#define  AUDIO_DECODER_DTS       0x05
	//! @}


//! @}


//! \name logical audio channels
//! There are twelve predefined spatial locations:
//! @{
#define  AUDIO_CHANNEL_NO_POSITION                          0x0000  // non-predefined spatial positions
#define  AUDIO_CHANNEL_L                                    0x0001  // Left Front (L)
#define  AUDIO_CHANNEL_R                                    0x0002  // Right Front (R)
#define  AUDIO_CHANNEL_C                                    0x0004  // Center Front (C)
#define  AUDIO_CHANNEL_LFE                                  0x0008  // Low Frequency Enhancement (LFE) [Super woofer]
#define  AUDIO_CHANNEL_LS                                   0x0010  // Left Surround (LS)
#define  AUDIO_CHANNEL_RS                                   0x0020  // Right Surround (RS)
#define  AUDIO_CHANNEL_LC                                   0x0040  // Left of Center (LC) [in front]
#define  AUDIO_CHANNEL_RC                                   0x0080  // Right of Center (RC) [in front]
#define  AUDIO_CHANNEL_S                                    0x0100  // Surround (S) [rear]
#define  AUDIO_CHANNEL_SL                                   0x0200  // Side Left (SL) [left wall]
#define  AUDIO_CHANNEL_SR                                   0x0400  // Side Right (SR) [right wall]
#define  AUDIO_CHANNEL_T                                    0x0800  // Top (T) [overhead]
//! @}



//! \name Terminal Types (from Device Class Definition for Terminal Types Release 2.0)
//! @{
   //! \name USB Terminal Types pp. 2.1
   //! @{
#define  AUDIO_TE_TYPE_USB_UNDEFINE                         0x0100  // I/O USB Terminal, undefined Type.
#define  AUDIO_TE_TYPE_USB_STREAMING                        0x0101  // I/O A Terminal dealing with a signal carried over an endpoint in an AudioStreaming interface. The AudioStreaming interface descriptor points to the associated Terminal through the bTerminalLink field.
#define  AUDIO_TE_TYPE_USB_VENDOR_SPECIFIC                  0x01FF  // I/O A Terminal dealing with a signal carried over a vendor-specific interface. The vendor-specific interface descriptor must contain a field that references the Terminal
   //! @}
   //! \name Input Terminal Types pp. 2.2
   //! @{
#define  AUDIO_TE_TYPE_INPUT_UNDEFINED                      0x0200  // I Input Terminal, undefined Type.
#define  AUDIO_TE_TYPE_INPUT_MICROPHONE                     0x0201  // I A generic microphone that does not fit under any of the other classifications.
#define  AUDIO_TE_TYPE_INPUT_DESKTOP_MICROPHONE             0x0202  // I A microphone normally placed on the desktop or integrated into the monitor.
#define  AUDIO_TE_TYPE_INPUT_PERSONAL_MICROPHONE            0x0203  // I A head-mounted or clip-on microphone.
#define  AUDIO_TE_TYPE_INPUT_OMNI_DIRECTIONAL_MICROPHONE    0x0204  // I A microphone designed to pick up voice from more than one speaker at relatively long ranges.
#define  AUDIO_TE_TYPE_INPUT_MICROPHONE_ARRAY               0x0205  // I An array of microphones designed for directional processing using host-based signal processing algorithms.
#define  AUDIO_TE_TYPE_INPUT_PROCESSING_MICROPHONE_ARRAY    0x0206  // I An array of microphones with an embedded signal processor.
   //! @}
   //! \name Output Terminal Types pp 2.3
   //! @{
#define  AUDIO_TE_TYPE_OUTPUT_UNDEFINED                     0x0300  // O Output Terminal, undefined Type.
#define  AUDIO_TE_TYPE_OUTPUT_SPEAKER                       0x0301  // O A generic speaker or set of speakers that does not fit under any of the other classifications.
#define  AUDIO_TE_TYPE_OUTPUT_HEADPHONES                    0x0302  // O A head-mounted audio output device.
#define  AUDIO_TE_TYPE_OUTPUT_HEAD_MOUNTED DISPLAY AUDIO    0x0303  // O The audio part of a VR head mounted display. The Associated Interfaces descriptor can be used to reference the HID interface used to report the position and orientation of the HMD.
#define  AUDIO_TE_TYPE_OUTPUT_DESKTOP_SPEAKER               0x0304  // O Relatively small speaker or set of speakers normally placed on the desktop or integrated into the monitor. These speakers are close to the user and have limited stereo separation.
#define  AUDIO_TE_TYPE_OUTPUT_ROOM_SPEAKER                  0x0305  // O Larger speaker or set of speakers that are heard well anywhere in the room.
#define  AUDIO_TE_TYPE_OUTPUT_COMMUNICATION_SPEAKER         0x0306  // O Speaker or set of speakers designed for voice communication.
#define  AUDIO_TE_TYPE_OUTPUT_LOW_FREQUENCY_EFFECTS_SPEAKER 0x0307  // O Speaker designed for low frequencies (subwoofer). Not capable of reproducing speech or music.
   //! @}
   //! \name Bi-directional Terminal Types pp 2.4
   //! @{
#define  AUDIO_TE_TYPE_BI_UNDEFINED                         0x0400  // I/O Bi-directional Terminal, undefined Type.
#define  AUDIO_TE_TYPE_BI_HANDSET                           0x0401  // I/O Hand-held bi-directional audio device.
#define  AUDIO_TE_TYPE_BI_HEADSET                           0x0402  // I/O Head-mounted bi-directional audio device.
#define  AUDIO_TE_TYPE_BI_SPEAKERPHONE_NO_ECHO_REDUCTION    0x0403  // I/O A hands-free audio device designed for host-based echo cancellation.
#define  AUDIO_TE_TYPE_BI_ECHO_SUPPRESSING_SPEAKERPHONE     0x0404  // I/O A hands-free audio device with echo suppression capable of half-duplex operation.
#define  AUDIO_TE_TYPE_BI_ECHO_CANCELING_SPEAKERPHONE       0x0405  // I/O A hands-free audio device with echo cancellation capable of full-duplex operation.
   //! @}
   //! \name Telephony Terminal Types pp 2.5
   //! @{
#define  AUDIO_TE_TYPE_TELEPHONY_UNDEFINED                  0x0500  // I/O Telephony Terminal, undefined Type.
#define  AUDIO_TE_TYPE_TELEPHONY_PHONE_LINE                 0x0501  // I/O May be an analog telephone line jack, an ISDN line, a proprietary PBX interface, or a wireless link.
#define  AUDIO_TE_TYPE_TELEPHONY_TELEPHONE                  0x0502  // I/O Device can be used as a telephone. When not in use as a telephone, handset is used as a bi-directional audio device.
#define  AUDIO_TE_TYPE_TELEPHONY_DOWN_LINE_PHONE            0x0503  // I/O A standard telephone set connected to the device. When not in use as a telephone, it can be used as a bidirectional audio device.
   //! @}
   //! \name External Terminal Types pp 2.6
   //! @{
#define  AUDIO_TE_TYPE_EXTERNAL_UNDEFINED                   0x0600  // I/O External Terminal, undefined Type.
#define  AUDIO_TE_TYPE_EXTERNAL_ANALOG_CONNECTOR            0x0601  // I/O A generic analog connector.
#define  AUDIO_TE_TYPE_EXTERNAL_DIGITAL_AUDIO_INTERFACE     0x0602  // I/O A generic digital audio interface.
#define  AUDIO_TE_TYPE_EXTERNAL_LINE_CONNECTOR              0x0603  // I/O An analog connector at standard line levels. Usually uses 3.5mm.
#define  AUDIO_TE_TYPE_EXTERNAL_LEGACY_AUDIO_CONNECTOR      0x0604  // I/O An input connector assumed to be connected to the lineout of the legacy audio system of the host computer. Used for backward compatibility.
#define  AUDIO_TE_TYPE_EXTERNAL_S_PDIF_INTERFACE            0x0605  // I/O An S/PDIF digital audio interface. The Associated Interface descriptor can be used to reference an interface used for controlling special functions of this interface.
#define  AUDIO_TE_TYPE_EXTERNAL_1394_DA_STREAM              0x0606  // I/O An interface to audio streams on a 1394 bus.
#define  AUDIO_TE_TYPE_EXTERNAL_1394_DV_STREAM_SOUNDTRACK   0x0607  // I/O An interface to soundtrack of A/V stream on a 1394 bus.
#define  AUDIO_TE_TYPE_EXTERNAL_ADAT_LITEPIPE               0x0608  // I/O An Optical interface to Alesis DAT.
#define  AUDIO_TE_TYPE_EXTERNAL_TDIF                        0x0609  // I/O An interface to Tascam.
#define  AUDIO_TE_TYPE_EXTERNAL_MADI                        0x060A  // I/O An interface to Multi-channel Audio Digital Interface as defined by AES.
//! @}
   //! \name Embedded Function Terminal Types pp. 2.7
   //! @{
#define  AUDIO_TE_TYPE_EMBEDDED_UNDEFINED                   0x0700  // I/O Embedded Terminal, undefined Type.
#define  AUDIO_TE_TYPE_EMBEDDED_LEVEL_CALIBRATION_NOISE_SRC 0x0701  // O Internal Noise source for level calibration (MPEG decoding, Dolby Prologic�, AC-3 etc.)
#define  AUDIO_TE_TYPE_EMBEDDED_EQUALIZATION NOISE          0x0702  // O Internal Noise source for measurements.
#define  AUDIO_TE_TYPE_EMBEDDED_CD_PLAYER                   0x0703  // I Audio compact disc player or CD-ROM capable of audio playback.
#define  AUDIO_TE_TYPE_EMBEDDED_DAT                         0x0704  // I/O Digital Audio Tape.
#define  AUDIO_TE_TYPE_EMBEDDED_DCC                         0x0705  // I/O Digital Compact Cassette.
#define  AUDIO_TE_TYPE_EMBEDDED_MINIDISK                    0x0706  // I/O Minidisk player.
#define  AUDIO_TE_TYPE_EMBEDDED_ANALOG_TAPE                 0x0707  // I/O Analog Audio Tape.
#define  AUDIO_TE_TYPE_EMBEDDED_PHONOGRAPH                  0x0708  // I Analog vinyl record player.
#define  AUDIO_TE_TYPE_EMBEDDED_VCR_AUDIO                   0x0709  // I Audio track of VCR.
#define  AUDIO_TE_TYPE_EMBEDDED_VIDEO_DISC_AUDIO            0x070A  // I Audio track of VideoDisc player.
#define  AUDIO_TE_TYPE_EMBEDDED_DVD_AUDIO                   0x070B  // I Audio track of DVD player.
#define  AUDIO_TE_TYPE_EMBEDDED_TV_TUNER_AUDIO              0x070C  // I Audio track of TV tuner.
#define  AUDIO_TE_TYPE_EMBEDDED_SATELLITE_RECEIVER_AUDIO    0x070D  // I Audio track of satellite receiver.
#define  AUDIO_TE_TYPE_EMBEDDED_CABLE_TUNER_AUDIO           0x070E  // I Audio track of cable tuner.
#define  AUDIO_TE_TYPE_EMBEDDED_DSS_AUDIO                   0x070F  // I Audio track of DSS receiver.
#define  AUDIO_TE_TYPE_EMBEDDED_RADIO_RECEIVER              0x0710  // I AM/FM radio receiver.
#define  AUDIO_TE_TYPE_EMBEDDED_RADIO_TRANSMITTER           0x0711  // O AM/FM radio transmitter.
#define  AUDIO_TE_TYPE_EMBEDDED_MULTI_TRACK_RECORDER        0x0712  // I/O A multi-track recording system.
#define  AUDIO_TE_TYPE_EMBEDDED_SYNTHESIZER                 0x0713  // I Synthesizer.
#define  AUDIO_TE_TYPE_EMBEDDED_PIANO                       0x0714  // I/O Piano
#define  AUDIO_TE_TYPE_EMBEDDED_GUITAR                      0x0715  // I/O Guitar
#define  AUDIO_TE_TYPE_EMBEDDED_DRUMS_RHYTHM                0x0716  // I/O Percussion Instrument
#define  AUDIO_TE_TYPE_EMBEDDED_OTHER                       0x0717
//! @}
//! @}


//! \name Additional Audio Device Class Codes (from USB Device Class Definition for Audio Data Formats Release 2.0)
//! @{

   //! \name Format Type Codes pp. A1
   //! @{
#define  AUDIO_FORMAT_TYPE_UNDEFINED                        0x00
#define  AUDIO_FORMAT_TYPE_I                                0x01
#define  AUDIO_FORMAT_TYPE_II                               0x02
#define  AUDIO_FORMAT_TYPE_III                              0x03
#define  AUDIO_FORMAT_TYPE_IV                               0x04
#define  AUDIO_FORMAT_EXT_TYPE_I                            0x81
#define  AUDIO_FORMAT_EXT_TYPE_II                           0x82
#define  AUDIO_FORMAT_EXT_TYPE_III                          0x83
   //! @}

   //! \name Audio Data Format Codes pp. A2.1
   //! @{
      //! \name Audio Data Format Type I Codes
      //! @{
#define  AUDIO_FORMAT_TI_UNDEFINE                           0x00000000
#define  AUDIO_FORMAT_TI_PCM                                0x00000001
#define  AUDIO_FORMAT_TI_PCM8                               0x00000002
#define  AUDIO_FORMAT_TI_IEEE_FLOAT                         0x00000004
#define  AUDIO_FORMAT_TI_ALAW                               0x00000008
#define  AUDIO_FORMAT_TI_MULAW                              0x00000010
#define  AUDIO_FORMAT_TI_RAW_DATA                           0x80000000
      //! @}
      //! \name Audio Data Format Type II Codes pp. A2.2
      //! @{
#define  AUDIO_FORMAT_TII_UNDEFINED                         0x00000000
#define  AUDIO_FORMAT_TII_MPEG                              0x00000001
#define  AUDIO_FORMAT_TII_AC_3                              0x00000002
#define  AUDIO_FORMAT_TII_WMA                               0x00000004
#define  AUDIO_FORMAT_TII_DTS                               0x00000008
#define  AUDIO_FORMAT_TII_RAW_DATA                          0x80000000
      //! @}
      //! \name Audio Data Format Type III Codes pp. A2.3
      //! @{
#define  AUDIO_FORMAT_TIII_UNDEFINED                        0x00000000
#define  AUDIO_FORMAT_TIII_IEC1937_AC_3                     0x00000001
#define  AUDIO_FORMAT_TIII_IEC1937_MPEG1_L1                 0x00000002
#define  AUDIO_FORMAT_TIII_IEC1937_MPEG1_L2_3_OR_MP_2_NOEXT 0x00000004
#define  AUDIO_FORMAT_TIII_IEC1937_MPEG2_EXT                0x00000008
#define  AUDIO_FORMAT_TIII_IEC1937_MPEG2_AAC_ADTS           0x00000010
#define  AUDIO_FORMAT_TIII_IEC1937_MPEG2_L1_LS              0x00000020
#define  AUDIO_FORMAT_TIII_IEC1937_MPEG2_L2_L3_LS           0x00000040
#define  AUDIO_FORMAT_TIII_IEC61937_DTS_I                   0x00000080
#define  AUDIO_FORMAT_TIII_IEC61937_DTS_II                  0x00000100
#define  AUDIO_FORMAT_TIII_IEC61937_DTS_III                 0x00000200
#define  AUDIO_FORMAT_TIII_IEC61937_ATRAC                   0x00000300
#define  AUDIO_FORMAT_TIII_IEC61937_ATRAC2_ATRAC3           0x00000400
#define  AUDIO_FORMAT_TIII_TYPE_III_WMA                     0x00000800

      //! @}
      //! \name Audio Data Format Type IV Codes pp. A2.4
      //! @{
#define  AUDIO_FORMAT_TIV_UNDEFINE                           0x00000000
#define  AUDIO_FORMAT_TIV_PCM                                0x00000001
#define  AUDIO_FORMAT_TIV_PCM8                               0x00000002
#define  AUDIO_FORMAT_TIV_IEEE_FLOAT                         0x00000004
#define  AUDIO_FORMAT_TIV_ALAW                               0x00000008
#define  AUDIO_FORMAT_TIV_MULAW                              0x00000010
#define  AUDIO_FORMAT_TIV_MPEG                               0x00000020
#define  AUDIO_FORMAT_TIV_AC_3                               0x00000040
#define  AUDIO_FORMAT_TIV_WMA                               0x00000080
#define  AUDIO_FORMAT_TIV_IEC1937_AC_3                     0x00000100
#define  AUDIO_FORMAT_TIV_IEC1937_MPEG1_L1                 0x00000200
#define  AUDIO_FORMAT_TIV_IEC1937_MPEG1_L2_3_OR_MP_2_NOEXT 0x00000400
#define  AUDIO_FORMAT_TIV_IEC1937_MPEG2_EXT                0x00000800
#define  AUDIO_FORMAT_TIV_IEC1937_MPEG2_AAC_ADTS           0x00001000
#define  AUDIO_FORMAT_TIV_IEC1937_MPEG2_L1_LS              0x00002000
#define  AUDIO_FORMAT_TIV_IEC1937_MPEG2_L2_L3_LS           0x00004000
#define  AUDIO_FORMAT_TIV_IEC61937_DTS_I                   0x00008000
#define  AUDIO_FORMAT_TIV_IEC61937_DTS_II                  0x00010000
#define  AUDIO_FORMAT_TIV_IEC61937_DTS_III                 0x00020000
#define  AUDIO_FORMAT_TIV_IEC61937_ATRAC                   0x00030000
#define  AUDIO_FORMAT_TIV_IEC61937_ATRAC2_ATRAC3           0x00040000
#define  AUDIO_FORMAT_TIV_TYPE_III_WMA                     0x00080000
#define  AUDIO_FORMAT_TIV_IEC60958_PCM                     0x00100000
      //! @}
   //! @}



   //! \name Format-Specific Control Selectors pp. A17.13.1
   //! @{
      //! \name MPEG Control Selectors
      //! @{
#define  AUDIO_FORMAT_CS_MP_UNDEFINED                       0x00
#define  AUDIO_FORMAT_CS_MP_DUAL_CHANNEL                    0x01
#define  AUDIO_FORMAT_CS_MP_SECOND_STEREO                   0x02
#define  AUDIO_FORMAT_CS_MP_MULTILINGUAL                    0x03
#define  AUDIO_FORMAT_CS_MP_DYN_RANGE                       0x04
#define  AUDIO_FORMAT_CS_MP_SCALING                         0x05
#define  AUDIO_FORMAT_CS_MP_HILO_SCALING                    0x06
#define  AUDIO_FORMAT_CS_MP_UNDERFLOW                       0x07
#define  AUDIO_FORMAT_CS_MP_OVERFLOW                        0x08
#define  AUDIO_FORMAT_CS_MP_DECODER_ERROR                   0x09
      //! @}
      //! \name AC-3 Control Selectors pp. A17.13.2
      //! @{
#define  AUDIO_FORMAT_CS_AD_CONTROL_UNDEFINED               0x00
#define  AUDIO_FORMAT_CS_AD_MODE                            0x01
#define  AUDIO_FORMAT_CS_AD_DYN_RANGE                       0x02
#define  AUDIO_FORMAT_CS_AD_SCALING                         0x03
#define  AUDIO_FORMAT_CS_AD_HILO_SCALING                    0x04
#define  AUDIO_FORMAT_CS_AD_UNDERFLOW                       0x05
#define  AUDIO_FORMAT_CS_AD_OVERFLOW                        0x06
#define  AUDIO_FORMAT_CS_AD_DECODER_ERROR                   0x07
      //! @}
      //! \name WMA Control Selectors pp. A17.13.3
      //! @{
#define  AUDIO_FORMAT_CS_WD_CONTROL_UNDEFINED               0x00
#define  AUDIO_FORMAT_CS_WD_UNDERFLOW                       0x01
#define  AUDIO_FORMAT_CS_WD_OVERFLOW                        0x02
#define  AUDIO_FORMAT_CS_WD_DECODER_ERROR                   0x03
      //! @}
      //! \name DTS Control Selectors pp. A17.13.4
      //! @{
#define  AUDIO_FORMAT_CS_DD_CONTROL_UNDEFINED               0x00
#define  AUDIO_FORMAT_CS_DD_UNDERFLOW                       0x01
#define  AUDIO_FORMAT_CS_DD_OVERFLOW                        0x02
#define  AUDIO_FORMAT_CS_DD_DECODER_ERROR                   0x03
      //! @}
   //! @}
//! @}



//! \name Specific setup requests from audio driver
//! USB_SETUP_SET_CLASS_INTER, USB_SETUP_GET_CLASS_INTER = directed to either the AudioControl interface or an AudioStreaming interface
//! USB_SETUP_SET_CLASS_ENDPOINT, USB_SETUP_GET_CLASS_ENDPOINT = directed to the isochronous endpoint of an AudioStreaming interface
//! @{

   //! \name AudioControl & AudioStreaming setup requests
   //! AudioControl requests :
   //! - Terminal Control requests
   //! - Mixer Unit Control requests
   //! - Selector Unit Control requests
   //! - Feature Unit Control requests
   //! - Processing Unit Control requests
   //! - Extension Unit Control requests
   //! AudioStreaming requests :
   //! - Interface Control Requests
   //! @{
#define  SETUP_AUDIO_SET_CUR                    0x01
#define  SETUP_AUDIO_SET_MIN                    0x02
#define  SETUP_AUDIO_SET_MAX                    0x03
#define  SETUP_AUDIO_SET_RES                    0x04
#define  SETUP_AUDIO_GET_CUR                    0x81
#define  SETUP_AUDIO_GET_MIN                    0x82
#define  SETUP_AUDIO_GET_MAX                    0x83
#define  SETUP_AUDIO_GET_RES                    0x84
   //! @}
   //! \name Additional setup Requests
   //! - Memory requests
   //! - Get status requests
   //! @{
#define  SETUP_AUDIO_SET_MEM                    0x05
#define  SETUP_AUDIO_SAMPLING_FREQ_CONTROL      0x01
#define  SETUP_AUDIO_GET_MEM                    0x85
#define  SETUP_AUDIO_GET_STAT                   0xFF
   //! @}

      //! \name Clock Source Control Selectors pp. A17.1
      //! @{
#define  AUDIO_CS_UNDEFINED                      0x00
#define  AUDIO_CS_CONTROL_SAM_FREQ               0x01
#define  AUDIO_CS_CONTROL_CLOCK_VALID            0x02
//! @}


      //! \name Clock Selector Control Selectors pp. A17.2
      //! @{
#define  AUDIO_CX_UNDEFINED                      0x00
#define  AUDIO_CX_CLOCK_SELECTOR                 0x01

//! @}


      //! \name Clock Multiplier Control Selectors pp. A17.3
      //! @{
#define  AUDIO_CM_UNDEFINED                      0x00
#define  AUDIO_CM_NUMERATOR                      0x01
#define  AUDIO_CM_DENOMINATOR                    0x02
//! @}

   //! \name Terminal Control requests pp. A17.4
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Mixer Terminal ID
   //! LSB(wValue) = 0, MSB(wValue) = Control Selectors
   //! @{
      //! \name Control Selectors
      //! @{
#define  AUDIO_TE_CONTROL_CS_UNDEFINED                      0x00
#define  AUDIO_TE_CONTROL_CS_COPY_PROTECT                   0x01
#define  AUDIO_TE_CONTROL_CS_CONNECTOR                      0x02
#define  AUDIO_TE_CONTROL_CS_OVERLOAD                       0x03
#define  AUDIO_TE_CONTROL_CS_CLUSTER                        0x04
#define  AUDIO_TE_CONTROL_CS_UNDERFLOW                      0x05
#define  AUDIO_TE_CONTROL_CS_OVERFLOW                       0x06
#define  AUDIO_TE_CONTROL_CS_LATENCY                        0x07
      //! @}

      //! \name The Copy Protect Control (AUDIO_TE_CONTROL_COPY_PROTECT) only supports the CUR attribute
      //! @{
#define  AUDIO_TE_CONTROL_CS_COPY_PROTECT_ATT_CPL0          0x00  // Copying is permitted without restriction. The material is either not copyrighted, or the copyright is not asserted
#define  AUDIO_TE_CONTROL_CS_COPY_PROTECT_ATT_CPL1          0x01  // One generation of copies may be made. The material is copyright protected and is the original.
#define  AUDIO_TE_CONTROL_CS_COPY_PROTECT_ATT_CPL2          0x02  // The material is copyright protected and no digital copying is permitted.
      //! @}
   //! @}


   //! \name Mixer Unit Control requests
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Mixer Unit ID
   //! LSB(wValue) = Output Channel Number (OCN), MSB(wValue) = Input Channel Number (ICN)
   //! @{
      //! \name Broadcast Channels (wValue)
      //! @{
#define  AUDIO_MIXER_CONTROL_IOCN_ALL_PROGRAM               0xFFFF   // To get or set all programmable Mixer Controls
#define  AUDIO_MIXER_CONTROL_IOCN_ALL                       0x0000   // To get all Mixer Controls
      //! @}
   //! @}


   //! \name Selector Unit Control requests
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Selector Unit ID
   //! wValue = 0
   //! @{
      //! \name bSelector Parameter
      //! @{
      //! @}
   //! @}


   //! \name Feature Unit Control requests pp A.17.7
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Feature Unit ID
   //! LSB(wValue) = Channel Number (CN), MSB(wValue) = Control Selector (CS)
   //! @{
      //! \name Control Selectors
      //! @{
#define  AUDIO_FU_CONTROL_CS_UNDEFINED                      0x00
#define  AUDIO_FU_CONTROL_CS_MUTE                           0x01
#define  AUDIO_FU_CONTROL_CS_VOLUME                         0x02
#define  AUDIO_FU_CONTROL_CS_BASS                           0x03
#define  AUDIO_FU_CONTROL_CS_MID                            0x04
#define  AUDIO_FU_CONTROL_CS_TREBLE                         0x05
#define  AUDIO_FU_CONTROL_CS_GRAPHIC_EQUALIZER              0x06
#define  AUDIO_FU_CONTROL_CS_AUTOMATIC_GAIN                 0x07
#define  AUDIO_FU_CONTROL_CS_DELAY                          0x08
#define  AUDIO_FU_CONTROL_CS_BASS_BOOST                     0x09
#define  AUDIO_FU_CONTROL_CS_LOUDNESS                       0x0A
#define  AUDIO_FU_CONTROL_CS_INPUT_GAIN                     0x0B
#define  AUDIO_FU_CONTROL_CS_INPUT_GAIN_PAD                 0x0C
#define  AUDIO_FU_CONTROL_CS_PHASE_INVERTER                 0x0D
#define  AUDIO_FU_CONTROL_CS_UNDERFLOW                      0x0E
#define  AUDIO_FU_CONTROL_CS_OVERFLOW                       0x0F
#define  AUDIO_FU_CONTROL_CS_LATENCY                        0x10
      //! @}
      //! \name Broadcast Channels (wValue)
      //! @{
#define  AUDIO_FU_CONTROL_CN_ALL                            0xFF   // To get or set all available Controls
      //! @}

      //! \name Bands parameter for AUDIO_FU_CONTROL_CS_GRAPHIC_EQUALIZER
      //! @{
#define  AUDIO_FU_CONTROL_BAND_EQ_25Hz          0x00000001  // band 14
#define  AUDIO_FU_CONTROL_BAND_EQ_31_5Hz        0x00000002  // band 15*
#define  AUDIO_FU_CONTROL_BAND_EQ_40Hz          0x00000004  // band 16
#define  AUDIO_FU_CONTROL_BAND_EQ_50Hz          0x00000008  // band 17
#define  AUDIO_FU_CONTROL_BAND_EQ_63Hz          0x00000010  // band 18*
#define  AUDIO_FU_CONTROL_BAND_EQ_80Hz          0x00000020  // band 19
#define  AUDIO_FU_CONTROL_BAND_EQ_100Hz         0x00000040  // band 20
#define  AUDIO_FU_CONTROL_BAND_EQ_125Hz         0x00000080  // band 21*
#define  AUDIO_FU_CONTROL_BAND_EQ_160Hz         0x00000100  // band 22
#define  AUDIO_FU_CONTROL_BAND_EQ_200Hz         0x00000200  // band 23
#define  AUDIO_FU_CONTROL_BAND_EQ_250Hz         0x00000400  // band 24*
#define  AUDIO_FU_CONTROL_BAND_EQ_315Hz         0x00000800  // band 25
#define  AUDIO_FU_CONTROL_BAND_EQ_400Hz         0x00001000  // band 26
#define  AUDIO_FU_CONTROL_BAND_EQ_500Hz         0x00002000  // band 27*
#define  AUDIO_FU_CONTROL_BAND_EQ_630Hz         0x00004000  // band 28
#define  AUDIO_FU_CONTROL_BAND_EQ_800Hz         0x00008000  // band 29
#define  AUDIO_FU_CONTROL_BAND_EQ_1000Hz        0x00010000  // band 30*
#define  AUDIO_FU_CONTROL_BAND_EQ_1250Hz        0x00020000  // band 31
#define  AUDIO_FU_CONTROL_BAND_EQ_1600Hz        0x00040000  // band 32
#define  AUDIO_FU_CONTROL_BAND_EQ_2000Hz        0x00080000  // band 33*
#define  AUDIO_FU_CONTROL_BAND_EQ_2500Hz        0x00100000  // band 34
#define  AUDIO_FU_CONTROL_BAND_EQ_3150Hz        0x00200000  // band 35
#define  AUDIO_FU_CONTROL_BAND_EQ_4000Hz        0x00400000  // band 36*
#define  AUDIO_FU_CONTROL_BAND_EQ_5000Hz        0x00800000  // band 37
#define  AUDIO_FU_CONTROL_BAND_EQ_6300Hz        0x01000000  // band 38
#define  AUDIO_FU_CONTROL_BAND_EQ_8000Hz        0x02000000  // band 39*
#define  AUDIO_FU_CONTROL_BAND_EQ_10000Hz       0x04000000  // band 40
#define  AUDIO_FU_CONTROL_BAND_EQ_12500Hz       0x08000000  // band 41
#define  AUDIO_FU_CONTROL_BAND_EQ_16000Hz       0x10000000  // band 42*
#define  AUDIO_FU_CONTROL_BAND_EQ_20000Hz       0x20000000  // band 43
      //! @}
      //! \name Bands parameter for AUDIO_FU_CONTROL_CS_DELAY
      //! The settings for the CUR, MIN, MAX, and RES attributes can range from zero (0x0000) to 1023.9844ms (0xFFFF) in steps of 1/64 ms (0x0001).
      //! @{
#define  AUDIO_FU_CONTROL_DELAY_0MS             0x0000      // 0 ms
#define  AUDIO_FU_CONTROL_DELAY_1MS             0x0040      // 1 ms
#define  AUDIO_FU_CONTROL_DELAY_MAX             0xFFFF      // 1023.9844 ms
      //! @}
   //! @}


   //! \name Processing Unit Control requests
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Processing Unit ID
   //! LSB(wValue) = 0, MSB(wValue) = Control Selector (CS)
   //! @{
      //! \name Up/Down-mix Processing Unit Control Selectors
      //! @{
#define  AUDIO_PU_CONTROL_CS_UD_UNDEFINED                   0x00
#define  AUDIO_PU_CONTROL_CS_UD_ENABLE                      0x01
#define  AUDIO_PU_CONTROL_CS_UD_MODE_SELECT                 0x02
      //! @}
      //! \name Dolby Prologic� Processing Unit Control Selectors
      //! @{
#define  AUDIO_PU_CONTROL_CS_DP_UNDEFINED                   0x00
#define  AUDIO_PU_CONTROL_CS_DP_ENABLE                      0x01
#define  AUDIO_PU_CONTROL_CS_DP_MODE_SELECT                 0x02
      //! @}
      //! \name 3D Stereo Extender Processing Unit Control Selectors
      //! @{
#define  AUDIO_PU_CONTROL_CS_3D_UNDEFINED                   0x00
#define  AUDIO_PU_CONTROL_CS_3D_ENABLE                      0x01
#define  AUDIO_PU_CONTROL_CS_3D_SPACIOUSNESS                0x03
      //! @}
      //! \name Reverberation Processing Unit Control Selectors
      //! @{
#define  AUDIO_PU_CONTROL_CS_RV_UNDEFINED                   0x00
#define  AUDIO_PU_CONTROL_CS_RV_ENABLE                      0x01
#define  AUDIO_PU_CONTROL_CS_RV_LEVEL                       0x02
#define  AUDIO_PU_CONTROL_CS_RV_TIME                        0x03
#define  AUDIO_PU_CONTROL_CS_RV_FEEDBACK                    0x04
      //! @}
      //! \name Chorus Processing Unit Control Selectors
      //! @{
#define  AUDIO_PU_CONTROL_CS_CH_UNDEFINED                   0x00
#define  AUDIO_PU_CONTROL_CS_CH_ENABLE                      0x01
#define  AUDIO_PU_CONTROL_CS_CH_LEVEL                       0x02
#define  AUDIO_PU_CONTROL_CS_CH_RATE                        0x03
#define  AUDIO_PU_CONTROL_CS_CH_DEPTH                       0x04
      //! @}
      //! \name Dynamic Range Compressor Processing Unit Control Selectors
      //! @{
#define  AUDIO_PU_CONTROL_CS_DR_UNDEFINED                   0x00
#define  AUDIO_PU_CONTROL_CS_DR_ENABLE                      0x01
#define  AUDIO_PU_CONTROL_CS_DR_COMPRESSION_RATE            0x02
#define  AUDIO_PU_CONTROL_CS_DR_MAXAMPL                     0x03
#define  AUDIO_PU_CONTROL_CS_DR_THRESHOLD                   0x04
#define  AUDIO_PU_CONTROL_CS_DR_ATTACK_TIME                 0x05
#define  AUDIO_PU_CONTROL_CS_DR_RELEASE_TIME                0x06
      //! @}
      //! \name bReverbType Parameter for AUDIO_PU_CONTROL_CS_RV_ENABLE  Control Selectors
      //! @{
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_ROOM1                  0     // simulates the reverberation of a small room.
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_ROOM2                  1     // simulates the reverberation of a medium room.
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_ROOM3                  2     // simulates the reverberation of a large room.
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_HALL1                  3     // simulates the reverberation of a medium concert hall.
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_HALL2                  4     // simulates the reverberation of a large concert hall.
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_PLATE                  5     // simulates a plate reverberation (a studio device using a metal plate).
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_DELAY                  6     // conventional delay that produces echo effects.
#define  AUDIO_PU_CONTROL_CS_RV_TYPE_PANNING_DELAY          7     // special delay in which the delayed sounds move left and right.
      //! @}
      //! \name Bands parameter for AUDIO_PU_CONTROL_CS_DR_RELEASE_TIME
      //! The settings for the CUR, MIN, MAX, and RES attributes can range from zero (0x0000) to 255.9961 ms (0xFFFF) in steps of 1/256 ms or 0.00390625 ms (0x0001)
      //! @{
#define  AUDIO_PU_CONTROL_CS_DR_RELEASE_TIME_DELAY_0MS             0x0000      // 0 ms
#define  AUDIO_PU_CONTROL_CS_DR_RELEASE_TIME_DELAY_MAX             0xFFFF      // 255.9961 ms
      //! @}
//! @}


   //! \name Extension Unit Control requests pp. A.17.10
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Extension Unit ID
   //! LSB(wValue) = 0, MSB(wValue) = Control Selector (CS)
   //! @{
      //! \name Control Selectors
      //! @{
#define  AUDIO_XU_CONTROL_CS_UNDEFINED                     0x00
#define  AUDIO_XU_CONTROL_CS_ENABLE                        0x01
#define  AUDIO_XU_CONTROL_CS_CLUSTER                       0x02
#define  AUDIO_XU_CONTROL_CS_UNDERFLW                      0x03
#define  AUDIO_XU_CONTROL_CS_OVERFLOW                      0x04
#define  AUDIO_XU_CONTROL_CS_LATENCY                       0x05
      //! @}
   //! @}


      //! \name AudioStreaming Interface Control Selectors pp. A.17.11
      //! @{
#define  AUDIO_AS_UNDEFINED                                0x00
#define  AUDIO_AS_ACT_ALT_SETTINGS                         0x01
#define  AUDIO_AS_VAL_ALT_SETTINGS                         0x02
#define  AUDIO_AS_AUDIO_DATA_FORMAT                        0x03
      //! @}




   //! \name Interface (endpoint) Control Requests pp. A.17.14
   //! wIndex = endpoint
   //! LSB(wValue) = 0, MSB(wValue) = Control Selector (CS)
   //! @{
      //! \name Control Selectors
      //! @{
#define  AUDIO_EP_CONTROL_CS_UNDEFINED                      0x00
#define  AUDIO_EP_CONTROL_CS_PITCH                          0x01
#define  AUDIO_EP_CONTROL_CS_OVERRUN                        0x02
#define  AUDIO_EP_CONTROL_CS_UNDERRUN                       0x03
      //! @}
   //! @}


   //! \name Memory Requests
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Entity ID (if Recipient of setup = INTERFACE)
   //! OR wIndex = endpoint (if Recipient of setup = ENDPOINT)
   //! wValue = Offset memory
   //! @{
   //! @}


   //! \name Get status Requests
   //! LSB(wIndex) = Interface, MSB(wIndex) =  Entity ID (if Recipient of setup = INTERFACE)
   //! OR wIndex = endpoint (if Recipient of setup = ENDPOINT)
   //! wValue = 0
   //! @{
   //! @}


   //! \name Level Parameter
   //! Used in Mixer Unit, Feature Unit Control requests
   //! @{
      //! \name Level 16bits
      //! Used in:
      //! - Mixer Unit Control requests
      //! - Feature Unit Control requests with AUDIO_FU_CONTROL_CS_VOLUME
      //!
      //! The settings for the CUR, MIN, and MAX attributes can range from +127.9961 dB (0x7FFF) down to -127.9961 dB (0x8001) in steps of 1/256 dB
      //! The range for the CUR attribute is extended by code 0x8000, representing silence, i.e., -� dB.
      //! The settings for the RES attribute can only take positive values and range from 1/256 dB (0x0001) to +127.9961 dB (0x7FFF).
      //! @{
#define  AUDIO_CONTROL_LEVEL16_DB_STEP                      (1L/256) //  1/256 dB
#define  AUDIO_CONTROL_LEVEL16_MAX                          0x7FFF   //  127.9961 dB
#define  AUDIO_CONTROL_LEVEL16_1DB                          0x0100   //         1 dB
#define  AUDIO_CONTROL_LEVEL16_0DB                          0x0000   //         0 dB
#define  AUDIO_CONTROL_LEVEL16_M1DB                         0xFE00   //        -1 dB
#define  AUDIO_CONTROL_LEVEL16_MIN                          0x8001   // -127.9961 dB
#define  AUDIO_CONTROL_LEVEL16_MUTE                         0x8000   // -infinit dB (CUR attribute only)
      //! @}
      //! \name Level 8bits
      //! Used in:
      //! - Feature Unit Control requests withAUDIO_FU_CONTROL_CS_BASS, _MID, _TREBLE
      //!
      //! The settings for the CUR, MIN, and MAX attributes can range from +31.75 dB (0x7F) down to -32.00 dB (0x80) in steps of 0.25 dB (0x01)
      //! The settings for the RES attribute can only take positive values and range from 0.25 dB (0x01) to +31.75 dB (0x7F)
      //! @{
#define  AUDIO_CONTROL_LEVEL8_MAX                           0x7F     // +31.75 dB
#define  AUDIO_CONTROL_LEVEL8_0DB                           0x00     //      0 dB
#define  AUDIO_CONTROL_LEVEL8_MIN                           0x80    //  -32.00 dB
      //! @}
   //! @}
//! @}


//_____ D E F I N I T I O N S __________________________________________________


//_____ D E C L A R A T I O N S ________________________________________________


#endif  // _USB_AUDIO_H_
