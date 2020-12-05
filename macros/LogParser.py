#!/usr/bin/env python

# Copyright (C) 2014 Alexander Gude - gude@physics.umn.edu
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#
# The most recent version of this program is available at:
# https://github.com/UMN-CMS/LogParser

from datetime import datetime
import ROOT


class LogLine:
    """ Base LogLine class.

Members:
ll_type: The type of logfile the LogLine was created from. "PM" or
"APM".
datetime: A python datetime object representing the time when the
log line was written.
mac_address: A string of the MAC address of the PM/APM.
temperature: A float of the temperature of the PM/APM.
voltage_out: A float of the primary output voltage.
power_good: A bool indicating if "power good" was signaled.
margin_up: A bool indicating if the test was running in "margin up"
mode.
margin_down: A bool indicating if the test was running in "margin
down" mode.
load: An int indicating what mode the test was running in; 1 is
normal load, 2 is high load.
input_voltage: A float of the primary input voltage.
input_current: A float of the primary input current.
total_power: A float of the total power in Watts.
"""
    def __init__(self, text_line):
        """ Set up the object from a log file line.

args:
text_line: A string containing the line of text from the log
file.
"""
        # Set up the datetime format string
        self.format_str = "%a %b %d %H:%M:%S %Y"
        self.ll_type = None

        split_text = self.get_split_text(text_line)
        # Set up common variables
        # Date
        self.datetime = datetime.strptime(split_text[0], self.format_str)
        # MAC Address
        self.mac_address = split_text[1]
        # Temperature
        self.temperature = float(split_text[2].strip(" C"))
        # Vout
        self.voltage_out = float(split_text[3].strip(" V"))
        # PGOOD, we need to bool(int()) because bool("0") is True
        self.power_good = bool(int(split_text[4]))
        # Margin up and down
        self.margin_up = bool(int(split_text[5]))
        self.margin_down = bool(int(split_text[6]))
        # Load
        self.load = int(split_text[7])
        # Input power values
        self.input_current = float(split_text[8].strip(" A"))
        self.input_voltage = float(split_text[9].strip(" V"))
        # Total Power
        self.total_power = float(split_text[-1].strip(" W"))

    def get_split_text(self, text_line):
        """ Split a comma separated line into a string while stripping
whitespace around the entries.

args:
text_line: A string containing the line of text from the log
file.

returns:
split_text: A list of strings.
"""
        # Parse the text
        split_text = []
        for field in text_line.split(","):
            split_text.append(field.strip())

        return split_text


class APMLogLine(LogLine):
    """ A class to access one line of data in an APM log file.

Inherited Members:
ll_type: The type of logfile the LogLine was created from. "PM" or
"APM".
datetime: A python datetime object representing the time when the
log line was written.
mac_address: A string of the MAC address of the PM/APM.
temperature: A float of the temperature of the PM/APM.
voltage_out: A float of the primary output voltage.
power_good: A bool indicating if "power good" was signaled.
margin_up: A bool indicating if the test was running in "margin up"
mode.
margin_down: A bool indicating if the test was running in "margin
down" mode.
load: An int indicating what mode the test was running in; 1 is
normal load, 2 is high load.
input_voltage: A float of the primary input voltage.
input_current: A float of the primary input current.
total_power: A float of the total power in Watts.

Members:
aux_output_voltage_a: Value of the voltage for the auxiliary power
output a.
aux_output_voltage_b: Value of the voltage for the auxiliary power
output b.
aux_output_voltage_c: Value of the voltage for the auxiliary power
output c.
aux_output_voltage_d: Value of the voltage for the auxiliary power
output d.
"""
    def __init__(self, text_line):
        """ Set up the object from an APM log file line.

args:
text_line: A string containing the line of text from the log
file.
"""
        LogLine.__init__(self, text_line)
        split_text = self.get_split_text(text_line)
        self.ll_type = "APM"
        # Output
        self.aux_output_voltage_a = float(split_text[10].strip(" V"))
        self.aux_output_voltage_b = float(split_text[11].strip(" V"))
        self.aux_output_voltage_c = float(split_text[12].strip(" V"))
        self.aux_output_voltage_d = float(split_text[13].strip(" V"))


class PMLogLine(LogLine):
    """ A class to access one line of data in a PM log file.

Inherited Members:
ll_type: The type of logfile the LogLine was created from. "PM" or
"APM".
datetime: A python datetime object representing the time when the
log line was written.
mac_address: A string of the MAC address of the PM/APM.
temperature: A float of the temperature of the PM/APM.
voltage_out: A float of the primary output voltage.
power_good: A bool indicating if "power good" was signaled.
margin_up: A bool indicating if the test was running in "margin up"
mode.
margin_down: A bool indicating if the test was running in "margin
down" mode.
load: An int indicating what mode the test was running in; 1 is
normal load, 2 is high load.
input_voltage: A float of the primary input voltage.
input_current: A float of the primary input current.
total_power: A float of the total power in Watts.

Members:
secondary_input_current: A float of the secondary input current.
secondary_input_voltage: A float of the secondary input voltage.
"""
    def __init__(self, text_line):
        """ Set up the object from a PM log file line.

args:
text_line: A string containing the line of text from the log
file.
"""
        LogLine.__init__(self, text_line)
        split_text = self.get_split_text(text_line)
        self.ll_type = "PM"
        # Input power values
        self.secondary_input_current = float(split_text[10].strip(" A"))
        self.secondary_input_voltage = float(split_text[11].strip(" V"))


class LogFile:
    def __init__(self, filename):
        """ Read in a log file. """
        with open(filename, "r") as input_file:
            cont = input_file.read().splitlines()

        self.lines = []
        # Check the type of file
        pm_type = None
        if filename.startswith("Power"):
            pm_type = "PM"
        elif filename.startswith("Aux"):
            pm_type = "APM"
        else:
            err_str = "Input log file starts with neither 'Power' nor 'Aux'."
            raise RuntimeError(err_str)

        # Create a LogLine object for each line while rejecting the header line
        for text_line in cont:
            if "Date," not in text_line:
                if pm_type == "PM":
                    ll = PMLogLine(text_line)
                elif pm_type == "APM":
                    ll = APMLogLine(text_line)
                self.lines.append(ll)

    # Allow access to the underlying list of log lines
    def __len__(self):
        return self.lines.__len__()

    def __getitem__(self, key):
        return self.lines.__getitem__(key)

    def __setitem__(self, key, value):
        return self.lines.__setitem(key, value)

    def __delitem__(self, key):
        return self.lines.__delitem__(key)

    def __iter__(self):
        return self.lines.__iter__()

    def __reversed__(self):
        return self.lines.__reversed__()

    def __contains__(self, item):
        return self.lines.__contains__(item)


if __name__ == '__main__':
    # Allows command line options to be parsed.
    from optparse import OptionParser # Command line parsing

    usage = "usage: %prog -i input_file -o output_file"
    parser = OptionParser(usage=usage, version="")
    parser.add_option(
            "-i",
            "--input-file",
            action="store",
            type="string",
            dest="input_file",
            help="input log file"
            )
    parser.add_option(
            "-o",
            "--output-file",
            action="store",
            type="string",
            dest="output_file",
            help="output root file"
            )

    (options, args) = parser.parse_args()

    # Make our output file
    output_tfile = ROOT.TFile(options.output_file, "RECREATE")
    output_tfile.cd()

    # Make the arrays to us in our TTree. Arrays are required because TTrees
    # need to work with a memory address.
    # See: http://wlav.web.cern.ch/wlav/pyroot/tpytree.html
    from array import array
    DOUBLE = "d" # double
    BOOL = "b" # signed char
    INT = "i" # signed int
    temperature_array = array(DOUBLE, [-1])
    voltage_out_array = array(DOUBLE, [-1])
    power_good_array = array(BOOL, [False])
    margin_up_array = array(BOOL, [False])
    margin_down_array = array(BOOL, [False])
    load_array = array(INT, [-1])
    input_voltage_array = array(DOUBLE, [-1])
    input_current_array = array(DOUBLE, [-1])
    total_power_array = array(DOUBLE, [-1])
    aux_output_voltage_a_array = array(DOUBLE, [-1])
    aux_output_voltage_b_array = array(DOUBLE, [-1])
    aux_output_voltage_c_array = array(DOUBLE, [-1])
    aux_output_voltage_d_array = array(DOUBLE, [-1])
    secondary_input_current_array = array(DOUBLE, [-1])
    secondary_input_voltage_array = array(DOUBLE, [-1])

    # Make the TTree
    ttree = ROOT.TTree("outtree", "Output Tree")
    ttree.Branch("temperature", temperature_array, "temperature/D")
    ttree.Branch("voltage_out", voltage_out_array, "voltage_out/D")
    ttree.Branch("power_good", power_good_array, "power_good/O")
    ttree.Branch("margin_up", margin_up_array, "margin_up/O")
    ttree.Branch("margin_down", margin_down_array, "margin_down/O")
    ttree.Branch("load", load_array, "load_array/I")
    ttree.Branch("input_voltage", input_voltage_array, "input_voltage/D")
    ttree.Branch("input_current", input_current_array, "input_current/D")
    ttree.Branch("total_power", total_power_array, "total_power/D")
    ttree.Branch("aux_output_voltage_a", aux_output_voltage_a_array, "aux_output_voltage_a/D")
    ttree.Branch("aux_output_voltage_b", aux_output_voltage_b_array, "aux_output_voltage_b/D")
    ttree.Branch("aux_output_voltage_c", aux_output_voltage_c_array, "aux_output_voltage_c/D")
    ttree.Branch("aux_output_voltage_d", aux_output_voltage_d_array, "aux_output_voltage_d/D")
    ttree.Branch("secondary_input_current", secondary_input_current_array, "secondary_input_current/D")
    ttree.Branch("secondary_input_voltage", secondary_input_voltage_array, "secondary_input_voltage/D")

    # Read in the first argument as a log file
    lf = LogFile(options.input_file)
    for line in lf:
        temperature_array[0] = line.temperature
        voltage_out_array[0] = line.voltage_out
        power_good_array[0] = line.power_good
        margin_up_array[0] = line.margin_up
        margin_down_array[0] = line.margin_down
        load_array[0] = line.load
        input_voltage_array[0] = line.input_voltage
        input_current_array[0] = line.input_current
        total_power_array[0] = line.total_power
        if line.ll_type == "APM":
            aux_output_voltage_a_array[0] = line.aux_output_voltage_a
            aux_output_voltage_b_array[0] = line.aux_output_voltage_b
            aux_output_voltage_c_array[0] = line.aux_output_voltage_c
            aux_output_voltage_d_array[0] = line.aux_output_voltage_d
            secondary_input_current_array[0] = -1
            secondary_input_voltage_array[0] = -1
        elif line.ll_type == "PM":
            aux_output_voltage_a_array[0] = -1
            aux_output_voltage_b_array[0] = -1
            aux_output_voltage_c_array[0] = -1
            aux_output_voltage_d_array[0] = -1
            secondary_input_current_array[0] = line.secondary_input_current
            secondary_input_voltage_array[0] = line.secondary_input_voltage
        # Fill the TTree
        ttree.Fill()

    # Close our TFile
    output_tfile.Write()
    output_tfile.Close()
