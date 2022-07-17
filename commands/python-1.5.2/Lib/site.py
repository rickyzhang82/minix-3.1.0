"""Append module search paths for third-party packages to sys.path.

****************************************************************
* This module is automatically imported during initialization. *
****************************************************************

In earlier versions of Python (up to 1.5a3), scripts or modules that
needed to use site-specific modules would place ``import site''
somewhere near the top of their code.  Because of the automatic
import, this is no longer necessary (but code that does it still
works).

This will append site-specific paths to to the module search path.  On
Unix, it starts with sys.prefix and sys.exec_prefix (if different) and
appends lib/python<version>/site-packages as well as lib/site-python.
On other platforms (mainly Mac and Windows), it uses just sys.prefix
(and sys.exec_prefix, if different, but this is unlikely).  The
resulting directories, if they exist, are appended to sys.path, and
also inspected for path configuration files.

A path configuration file is a file whose name has the form
<package>.pth; its contents are additional directories (one per line)
to be added to sys.path.  Non-existing directories (or
non-directories) are never added to sys.path; no directory is added to
sys.path more than once.  Blank lines and lines beginning with
\code{#} are skipped.

For example, suppose sys.prefix and sys.exec_prefix are set to
/usr/local and there is a directory /usr/local/lib/python1.5/site-packages
with three subdirectories, foo, bar and spam, and two path
configuration files, foo.pth and bar.pth.  Assume foo.pth contains the
following:

  # foo package configuration
  foo
  bar
  bletch

and bar.pth contains:

  # bar package configuration
  bar

Then the following directories are added to sys.path, in this order:

  /usr/local/lib/python1.5/site-packages/bar
  /usr/local/lib/python1.5/site-packages/foo

Note that bletch is omitted because it doesn't exist; bar precedes foo
because bar.pth comes alphabetically before foo.pth; and spam is
omitted because it is not mentioned in either path configuration file.

After these path manipulations, an attempt is made to import a module
named sitecustomize, which can perform arbitrary additional
site-specific customizations.  If this import fails with an
ImportError exception, it is silently ignored.

"""

import sys, os

def addsitedir(sitedir):
    if sitedir not in sys.path:
        sys.path.append(sitedir)        # Add path component
    try:
        names = os.listdir(sitedir)
    except os.error:
        return
    names = map(os.path.normcase, names)
    names.sort()
    for name in names:
        if name[-4:] == ".pth":
            addpackage(sitedir, name)

def addpackage(sitedir, name):
    fullname = os.path.join(sitedir, name)
    try:
        f = open(fullname)
    except IOError:
        return
    while 1:
        dir = f.readline()
        if not dir:
            break
        if dir[0] == '#':
            continue
        if dir[-1] == '\n':
            dir = dir[:-1]
        dir = os.path.join(sitedir, dir)
        if dir not in sys.path and os.path.exists(dir):
            sys.path.append(dir)

prefixes = [sys.prefix]
if sys.exec_prefix != sys.prefix:
    prefixes.append(sys.exec_prefix)
for prefix in prefixes:
    if prefix:
        if os.sep == '/':
            sitedirs = [os.path.join(prefix,
                                     "lib",
                                     "python" + sys.version[:3],
                                     "site-packages"),
                        os.path.join(prefix, "lib", "site-python")]
        else:
            sitedirs = [prefix]
        for sitedir in sitedirs:
            if os.path.isdir(sitedir):
                addsitedir(sitedir)

# Define new built-ins 'quit' and 'exit'.
# These are simply strings that display a hint on how to exit.
if os.sep == ':':
    exit = 'Use Cmd-Q to quit.'
elif os.sep == '\\':
    exit = 'Use Ctrl-Z plus Return to exit.'
else:
    exit = 'Use Ctrl-D (i.e. EOF) to exit.'
import __builtin__
__builtin__.quit = __builtin__.exit = exit
del exit

try:
    import sitecustomize                # Run arbitrary site specific code
except ImportError:
    pass                                # No site customization module

def _test():
    print "sys.path = ["
    for dir in sys.path:
        print "    %s," % `dir`
    print "]"

if __name__ == '__main__':
    _test()
