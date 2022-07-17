from t_support import verbose, findfile
import tokenize, os, sys

if verbose:
    print 'starting...'
file = open(findfile('tok_tests.py'))
tokenize.tokenize(file.readline)
if verbose:
    print 'finished'

