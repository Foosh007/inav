/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define EXBUS_HEADER_LEN                6
#define EXBUS_CRC_LEN                   2
#define EXBUS_OVERHEAD                  (EXBUS_HEADER_LEN + EXBUS_CRC_LEN)
#define EXBUS_MAX_CHANNEL_FRAME_SIZE    (EXBUS_HEADER_LEN + JETIEXBUS_CHANNEL_COUNT*2 + EXBUS_CRC_LEN)
#define EXBUS_MAX_REQUEST_FRAME_SIZE    32 //9

#define EXBUS_EX_REQUEST                (0x3A)

enum exBusHeader_e {
    EXBUS_HEADER_SYNC = 0,
    EXBUS_HEADER_REQ,
    EXBUS_HEADER_MSG_LEN,
    EXBUS_HEADER_PACKET_ID,
    EXBUS_HEADER_DATA_ID,
    EXBUS_HEADER_SUBLEN,
    EXBUS_HEADER_DATA
};

enum {
    EXBUS_STATE_ZERO = 0,
    EXBUS_STATE_IN_PROGRESS,
    EXBUS_STATE_RECEIVED,
    EXBUS_STATE_PROCESSED
};

extern volatile uint8_t jetiExBusRequestState;
extern volatile uint32_t jetiTimeStampRequest;
extern uint8_t jetiExBusRequestFrame[EXBUS_MAX_REQUEST_FRAME_SIZE];
struct serialPort_s;
extern struct serialPort_s *jetiExBusPort;

extern volatile bool jetiExBusCanTx;

uint16_t jetiExBusCalcCRC16(uint8_t *pt, uint8_t msgLen);
bool jetiExBusInit(const rxConfig_t *rxConfig, rxRuntimeConfig_t *rxRuntimeConfig);
