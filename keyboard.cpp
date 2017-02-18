/* USB EHCI Host for Teensy 3.6
 * Copyright 2017 Paul Stoffregen (paul@pjrc.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <Arduino.h>
#include "USBHost.h"


KeyboardController::KeyboardController()
{
	// TODO: free Device_t, Pipe_t & Transfer_t we will need
	driver_ready_for_device(this);
}

bool KeyboardController::claim(Device_t *dev, int type, const uint8_t *descriptors)
{
	Serial.print("KeyboardController claim this=");
	Serial.println((uint32_t)this, HEX);

	// only claim at interface level
	if (type != 1) return false;

	return false;

	uint32_t endpoint=1;
	datapipe = new_Pipe(dev, 3, endpoint, 1, 8, 64);
	queue_Data_Transfer(datapipe, report, 8, this);
	return true;
}

void KeyboardController::callback(const Transfer_t *transfer)
{
	Serial.println("KeyboardController Callback (static)");
	if (transfer->driver) {
		((KeyboardController *)(transfer->driver))->new_data(transfer);
	}
}

void KeyboardController::new_data(const Transfer_t *transfer)
{
	Serial.println("KeyboardController Callback (member)");
	// TODO: parse the new data
	queue_Data_Transfer(datapipe, report, 8, this);
}

void KeyboardController::disconnect()
{
	// TODO: free resources
}



