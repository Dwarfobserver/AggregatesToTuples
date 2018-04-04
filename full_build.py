
'''
Usage : python full_build.py <optional: max_arity = 50>
The script must be called from the build folder, created in the project's root directory.

This script execute in this order :
 - cmake -DMAKE_GENERATORS=1 ..
 - cmake --build .
 - ./make_arity_functions max_arity
 - ./make_single_header
 - cmake -DMAKE_GENERATORS=0 ..
 - cmake --build .
 - ctest -V
'''

import os
import sys
from subprocess import call

argc = len(sys.argv)

if argc > 2:
    print('Usage : python full_build.py <optional: max_arity = 50>')
    sys.exit(1)

max_arity = sys.argv[1] if argc == 2 else 50

def check(code):
    if code != 0: sys.exit(1)

check(call(['cmake', '-DMAKE_GENERATORS=1', '..']))
check(call(['cmake', '--build', '.']))
check(call(['./make_arity_functions', str(max_arity)]))
check(call(['./make_single_header']))
check(call(['cmake', '-DMAKE_GENERATORS=0', '..']))
check(call(['cmake', '--build', '.']))
check(call(['ctest', '-V']))
