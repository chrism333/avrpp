/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Christian Menard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <avrpp/hal/adcreader.h>
using namespace avrpp;

volatile uint16_t AdcReader::values[8] = {0};
volatile uint8_t AdcReader::updatedFlags = 0;

ISR(ADC_vect)
{
	static uint8_t currentChannel = 0;

	// read ADC value and set update flag
	AdcReader::values[currentChannel] = ADConverter::readValue();
	AdcReader::updatedFlags |= (1 << currentChannel);

	// Set to next channel
	currentChannel = (currentChannel + 1) & 0x07; // & 0x07 does the same as % 8, but is faster
	ADConverter::setChannel( (AdcChannel) (currentChannel));

	// Start a new conversion, so Interrupt is triggered again
	ADConverter::startConversion();
}
