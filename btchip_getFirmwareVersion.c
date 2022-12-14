/*
 * Copyright (c) 2014 UBINITY SAS All rights reserved.
 * This source code is the property of UBINITY SAS. 
 * Redistribution and use in source (source code) or binary (object code)
 * forms with or without modification, for commercial, educational or
 * research purposes is not permitted without the prior written consent
 * of UBINITY SAS. 
 */

#include "dongleComm.h"
#include "hexUtils.h"
#include "btchipApdu.h"
#include "btchipArgs.h"

int main(int argc, char **argv) {
	dongleHandle dongle;
	unsigned char in[260];
	unsigned char out[260];
	int result;
	int sw;
	int apduSize;	

	initDongle();
	dongle = getFirstDongle();
	if (dongle == NULL) {
		fprintf(stderr, "No dongle found\n");
		return 0;
	}
	apduSize = 0;
	in[apduSize++] = BTCHIP_CLA;
	in[apduSize++] = 0x01;
	in[apduSize++] = 0x00;
	in[apduSize++] = 0x00;
	in[apduSize++] = 0x00;
	result = sendApduDongle(dongle, in, apduSize, out, sizeof(out), &sw);
	closeDongle(dongle);
	exitDongle();
	if (result < 0) {
		fprintf(stderr, "I/O error\n");
		return 0;
	}
	if (sw == SW_UNKNOWN) {
		// Initial firmware did not support this command
		out[0] = 0x00;		
		out[1] = 0x00;		
		out[2] = 0x01;		
		out[3] = 0x04;
		out[4] = 0x03;
		out[5] = 0x01;
		out[6] = 0x43;
	}
	else
	if (sw != SW_OK) {
		fprintf(stderr, "Dongle application error : %.4x\n", sw);
		return 0;
	}
	printf("Firmware version %s %d.%d.%d\n", (out[1] != 0 ? "Ledger" : ""), out[2], out[3], out[4]);
	if (result > 5) {
		printf("Loader ID %d.%d.%d\n", (out[5] & 0x0F), (out[6] >> 4), (out[6] & 0x0F));
	}
	printf("Using compressed keys : %s\n", (out[0] == 0x01 ? "yes" : "no"));

	return 1;
}

