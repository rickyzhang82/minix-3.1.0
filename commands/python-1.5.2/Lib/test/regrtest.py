#! /usr/bin/env python

"""Regression test.

This will find all modules whose name is "t_*" in the test
directory, and run them.  Various command line options provide
additional facilities.

Command line options:

-v: verbose  -- run tests in verbose mode with output to stdout
-q: quiet    -- don't print anything except if a test fails
-g: generate -- write the output file for a test instead of comparing it
-x: exclude  -- arguments are tests to *exclude*
-s: single   -- run only a single test (see below)

If non-option arguments are present, they are names for tests to run,
unless -x is given, in which case they are names for tests not to run.
If no test names are given, all tests are run.

-v is incompatible with -g and does not compare test output files.

-s means to run only a single test and exit.  This is useful when Purifying
the Python interpreter.  The file /tmp/pynexttest is read to find the next
test to run.  If this file is missing, the first t_*.py file in testdir or
on the command line is used.  (actually tempfile.gettempdir() is used instead
of /tmp).

"""

import sys
import string
import os
import getopt
import traceback

import t_support

def main(tests=None, testdir=None):
    """Execute a test suite.

    This also parses command-line options and modifies its behaviour
    accordingly. 

    tests -- a list of strings containing test names (optional)
    testdir -- the directory in which to look for tests (optional)

    Users other than the Python test suite will certainly want to
    specify testdir; if it's omitted, the directory containing the
    Python test suite is searched for.  

    If the tests argument is omitted, the tests listed on the
    command-line will be used.  If that's empty, too, then all *.py
    files beginning with t_ will be used.
    
    """
    
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'vgqxs')
    except getopt.error, msg:
        print msg
        print __doc__
        return 2
    verbose = 0
    quiet = 0
    generate = 0
    exclude = 0
    single = 0
    for o, a in opts:
        if o == '-v': verbose = verbose+1
        if o == '-q': quiet = 1; verbose = 0
        if o == '-g': generate = 1
        if o == '-x': exclude = 1
        if o == '-s': single = 1
    if generate and verbose:
        print "-g and -v don't go together!"
        return 2
    good = []
    bad = []
    skipped = []

    if single:
        from tempfile import gettempdir
        filename = os.path.join(gettempdir(), 'pynexttest')
        try:
            fp = open(filename, 'r')
            next = string.strip(fp.read())
            tests = [next]
            fp.close()
        except IOError:
            pass
    for i in range(len(args)):
        # Strip trailing ".py" from arguments
        if args[i][-3:] == '.py':
            args[i] = args[i][:-3]
    stdtests = STDTESTS[:]
    nottests = NOTTESTS[:]
    if exclude:
        for arg in args:
            if arg in stdtests:
                stdtests.remove(arg)
        nottests[:0] = args
        args = []
    tests = tests or args or findtests(testdir, stdtests, nottests)
    if single:
        tests = tests[:1]
    t_support.verbose = verbose      # Tell tests to be moderately quiet
    for test in tests:
        if not quiet:
            print test
        ok = runtest(test, generate, verbose, testdir)
        if ok > 0:
            good.append(test)
        elif ok == 0:
            bad.append(test)
        else:
            if not quiet:
                print "test", test,
                print "skipped -- an optional feature could not be imported"
            skipped.append(test)
    if good and not quiet:
        if not bad and not skipped and len(good) > 1:
            print "All",
        print count(len(good), "test"), "OK."
    if bad:
        print count(len(bad), "test"), "failed:",
        print string.join(bad)
    if skipped and not quiet:
        print count(len(skipped), "test"), "skipped:",
        print string.join(skipped)

    if single:
        alltests = findtests(testdir, stdtests, nottests)
        for i in range(len(alltests)):
            if tests[0] == alltests[i]:
                if i == len(alltests) - 1:
                    os.unlink(filename)
                else:
                    fp = open(filename, 'w')
                    fp.write(alltests[i+1] + '\n')
                    fp.close()
                break
        else:
            os.unlink(filename)

    return len(bad) > 0

STDTESTS = [
    't_grammar',
    't_opcodes',
    't_operation',
    't_builtin',
    't_exceptns',
    't_types',
   ]

NOTTESTS = [
    't_support',
    't_b1',
    't_b2',
    ]

def findtests(testdir=None, stdtests=STDTESTS, nottests=NOTTESTS):
    """Return a list of all applicable test modules."""
    if not testdir: testdir = findtestdir()
    names = os.listdir(testdir)
    tests = []
    for name in names:
        if name[:2] == "t_" and name[-3:] == ".py":
            modname = name[:-3]
            if modname not in stdtests and modname not in nottests:
                tests.append(modname)
    tests.sort()
    return stdtests + tests

def runtest(test, generate, verbose, testdir = None):
    """Run a single test.
    test -- the name of the test
    generate -- if true, generate output, instead of running the test
    and comparing it to a previously created output file
    verbose -- if true, print more messages
    testdir -- test directory
    """
    t_support.unload(test)
    if not testdir: testdir = findtestdir()
    outputdir = os.path.join(testdir, "output")
    outputfile = os.path.join(outputdir, test)
    try:
        if generate:
            cfp = open(outputfile, "w")
        elif verbose:
            cfp = sys.stdout
        else:
            cfp = Compare(outputfile)
    except IOError:
        cfp = None
        print "Warning: can't open", outputfile
    try:
        save_stdout = sys.stdout
        try:
            if cfp:
                sys.stdout = cfp
                print test              # Output file starts with test name
            __import__(test, globals(), locals(), [])
        finally:
            sys.stdout = save_stdout
    except ImportError, msg:
        return -1
    except KeyboardInterrupt, v:
        raise KeyboardInterrupt, v, sys.exc_info()[2]
    except t_support.TestFailed, msg:
        print "test", test, "failed --", msg
        return 0
    except:
        type, value = sys.exc_info()[:2]
        print "test", test, "crashed --", type, ":", value
        if verbose:
            traceback.print_exc(file=sys.stdout)
        return 0
    else:
        return 1

def findtestdir():
    if __name__ == '__main__':
        file = sys.argv[0]
    else:
        file = __file__
    testdir = os.path.dirname(file) or os.curdir
    return testdir

def count(n, word):
    if n == 1:
        return "%d %s" % (n, word)
    else:
        return "%d %ss" % (n, word)

class Compare:

    def __init__(self, filename):
        self.fp = open(filename, 'r')

    def write(self, data):
        expected = self.fp.read(len(data))
        if data <> expected:
            raise t_support.TestFailed, \
                    'Writing: '+`data`+', expected: '+`expected`

    def writelines(self, listoflines):
        map(self.write, listoflines)

    def flush(self):
        pass

    def close(self):
        leftover = self.fp.read()
        if leftover:
            raise t_support.TestFailed, 'Unread: '+`leftover`
        self.fp.close()

    def isatty(self):
        return 0

if __name__ == '__main__':
    sys.exit(main())
