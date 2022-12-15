"""

This is a quick script for determining the value of the hysteresis
resistor. R1 is the high resistor, R2 is the low resistor, R3 is the
feedback resistor. k is the attenuation factor of the resistor divider
this is being compared to.

It uses the constants set below to determine the perfect resistor
values. It then allows you to enter the real values for R2 and R3,
and prints out the actual low and high hysteresis points.

You shouldn't ever need to use this unless you are changing the
resistor values for the charge detection, but I've included it just
in case.

Joe Pater <joe@jpater.com>

"""


r1 = 2718e3

vin = 600
vcc = 12

k = 33e3 / (2718e3 + 33e3)

low = 0.955
high = 0.965

r3 = (r1 * vcc) / ((high/low - 1) * vin)
r2 = 1 / (1 / (low * k * r1) - 1 / r1 - 1 / r3)

print("R1: {}  R2: {}  R3: {}".format(r1, r2, r3))

r2 = float(input("Enter R2: "))
r3 = float(input("Enter R3: "))

parallel = 1 / (1/r1 + 1/r2 + 1/r3)

low = (1/r1/k) * parallel
high = (vcc/r3 + vin/r1) * parallel / (vin * k)

print("Low: {}  High: {}".format(low, high))
