#!/usr/bin/env python3

import warnings
warnings.filterwarnings('ignore', category=FutureWarning)

import sys
import zlib

# Please comment the line below out by adding a '#' to the front of
# the line.
# raise RuntimeError, "You need to comment out this line with a #"

import getpass
user = getpass.getuser()
crc32 = zlib.crc32(bytes(user,'utf-8'))

print(f"success:  {user} 0x{crc32:X}")