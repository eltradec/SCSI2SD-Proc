//	Copyright (C) 2016 Michael McMaster <michael@codesrc.com>
//
//	This file is part of SCSI2SD.
//
//	SCSI2SD is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	SCSI2SD is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with SCSI2SD.  If not, see <http://www.gnu.org/licenses/>.

#include "device.h"
#include "scsi.h"
#include "vendor.h"


// Callback after the DATA OUT phase is complete.
static void doAssignDiskParameters(void)
{
	scsiDev.phase = STATUS;
}

int scsiVendorCommand()
{
	int commandHandled = 1;

	uint8 command = scsiDev.cdb[0];

	if (command == 0xC0)
	{
		// Define flexible disk format
		// OMTI-5204 controller
		// http://bitsavers.informatik.uni-stuttgart.de/pdf/sms/OMTI_5x00.pdf
		// Stub. Sectors-per-track should be configured by scsi2sd-util
	}
	else if (command == 0xC2)
	{
		// Assign Disk Parameters command
		// OMTI-5204 controller
		// http://bitsavers.informatik.uni-stuttgart.de/pdf/sms/OMTI_5x00.pdf
		// Stub to read and discard 10 bytes.
		scsiDev.dataLen = 10;
		scsiDev.phase = DATA_OUT;
		scsiDev.postDataOutHook = doAssignDiskParameters;
	}
	else if (command == 0x0C)
	{
		// Initialize Drive Characteristics
		// XEBEC S1410 controller
		// http://bitsavers.informatik.uni-stuttgart.de/pdf/xebec/104524C_S1410Man_Aug83.pdf
		scsiDev.dataLen = 8;
		scsiDev.phase = DATA_OUT;
	}
	else if (command == 0xE0)
	{
		// RAM Diagnostic
		// XEBEC S1410 controller
		// http://bitsavers.informatik.uni-stuttgart.de/pdf/xebec/104524C_S1410Man_Aug83.pdf
		// Stub, return success
	}
	else if (command == 0xE4)
	{
		// Drive Diagnostic
		// XEBEC S1410 controller
		// Stub, return success
	}
	else
	{
		commandHandled = 0;
	}

	return commandHandled;
}

