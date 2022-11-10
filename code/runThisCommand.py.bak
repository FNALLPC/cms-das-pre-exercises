#!/usr/bin/env python

import warnings
warnings.filterwarnings('ignore', category=FutureWarning)

import sys
import zlib



if len(sys.argv) < 2:
    print "Error: You must provide the secret key"
    sys.exit()

key = ''.join(sys.argv[1:])
crc32 = zlib.crc32(key)

key = 'asdf;klasdjf;kakjsdf;akjf;aksdljf;asldjfqewradsfafaw4efaefawefzdxffasdfw4ffawefawe4fawasdffadsfef'
#print "crc32", crc32, crc32.__class__.__name__

if crc32 != zlib.crc32 (key):
    print "Error: You didn't paste the correct input string"
    sys.exit()

import getpass
user = getpass.getuser()
other = ''
for letter in user:
    number = ord (letter)
    if 65 <= number <= 77 or 97 <= number <= 109:
        number += 13
    elif 78 <= number <= 90 or 110 <= number <= 122:
        number -= 13
    other += chr (number)
print "success: %s %s" % (user, other)
