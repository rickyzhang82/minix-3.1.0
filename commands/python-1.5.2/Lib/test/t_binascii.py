#! /usr/bin/env python
"""Test script for the binascii C module

   Uses the mechanism of the python binhex module
   Roger E. Masse
"""
import binhex
import tempfile
from t_support import verbose

def test():

    try:
        fname1 = tempfile.mktemp()
        fname2 = tempfile.mktemp()
        f = open(fname1, 'w')
    except:
        raise ImportError, "Cannot test binascii without a temp file"

    start = 'Jack is my hero'
    f.write(start)
    f.close()
    
    binhex.binhex(fname1, fname2)
    if verbose:
        print 'binhex'

    binhex.hexbin(fname2, fname1)
    if verbose:
        print 'hexbin'

    f = open(fname1, 'r')
    finish = f.readline()

    if start <> finish:
        print 'Error: binhex <> hexbin'
    elif verbose:
        print 'binhex == hexbin'

    try:
        import os
        os.unlink(fname1)
        os.unlink(fname2)
    except:
        pass
test()
