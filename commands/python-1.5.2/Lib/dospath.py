# Module 'dospath' -- common operations on DOS pathnames

import os
import stat
import string


# Normalize the case of a pathname.
# On MS-DOS it maps the pathname to lowercase, turns slashes into
# backslashes.
# Other normalizations (such as optimizing '../' away) are not allowed
# (this is done by normpath).
# Previously, this version mapped invalid consecutive characters to a 
# single '_', but this has been removed.  This functionality should 
# possibly be added as a new function.

def normcase(s):
	return string.lower(string.replace(s, "/", "\\"))


# Return wheter a path is absolute.
# Trivial in Posix, harder on the Mac or MS-DOS.
# For DOS it is absolute if it starts with a slash or backslash (current
# volume), or if a pathname after the volume letter and colon starts with
# a slash or backslash.

def isabs(s):
	s = splitdrive(s)[1]
	return s != '' and s[:1] in '/\\'


# Join two (or more) paths.

def join(a, *p):
	path = a
	for b in p:
		if isabs(b):
			path = b
		elif path == '' or path[-1:] in '/\\':
			path = path + b
		else:
			path = path + os.sep + b
	return path


# Split a path in a drive specification (a drive letter followed by a
# colon) and the path specification.
# It is always true that drivespec + pathspec == p

def splitdrive(p):
	if p[1:2] == ':':
		return p[0:2], p[2:]
	return '', p


# Split a path in head (everything up to the last '/') and tail (the
# rest).  After the trailing '/' is stripped, the invariant
# join(head, tail) == p holds.
# The resulting head won't end in '/' unless it is the root.

def split(p):
    d, p = splitdrive(p)
    # set i to index beyond p's last slash
    i = len(p)
    while i and p[i-1] not in '/\\':
        i = i - 1
    head, tail = p[:i], p[i:]  # now tail has no slashes
    # remove trailing slashes from head, unless it's all slashes
    head2 = head
    while head2 and head2[-1] in '/\\':
        head2 = head2[:-1]
    head = head2 or head
    return d + head, tail


# Split a path in root and extension.
# The extension is everything starting at the first dot in the last
# pathname component; the root is everything before that.
# It is always true that root + ext == p.

def splitext(p):
	root, ext = '', ''
	for c in p:
		if c in '/\\':
			root, ext = root + ext + c, ''
		elif c == '.' or ext:
			ext = ext + c
		else:
			root = root + c
	return root, ext


# Return the tail (basename) part of a path.

def basename(p):
	return split(p)[1]


# Return the head (dirname) part of a path.

def dirname(p):
	return split(p)[0]


# Return the longest prefix of all list elements.

def commonprefix(m):
	if not m: return ''
	prefix = m[0]
	for item in m:
		for i in range(len(prefix)):
			if prefix[:i+1] <> item[:i+1]:
				prefix = prefix[:i]
				if i == 0: return ''
				break
	return prefix


# Get size, mtime, atime of files.

def getsize(filename):
    """Return the size of a file, reported by os.stat()."""
    st = os.stat(filename)
    return st[stat.ST_SIZE]

def getmtime(filename):
    """Return the last modification time of a file, reported by os.stat()."""
    st = os.stat(filename)
    return st[stat.ST_MTIME]

def getatime(filename):
    """Return the last access time of a file, reported by os.stat()."""
    st = os.stat(filename)
    return st[stat.ST_MTIME]


# Is a path a symbolic link?
# This will always return false on systems where posix.lstat doesn't exist.

def islink(path):
	return 0


# Does a path exist?
# This is false for dangling symbolic links.

def exists(path):
	try:
		st = os.stat(path)
	except os.error:
		return 0
	return 1


# Is a path a dos directory?
# This follows symbolic links, so both islink() and isdir() can be true
# for the same path.

def isdir(path):
	try:
		st = os.stat(path)
	except os.error:
		return 0
	return stat.S_ISDIR(st[stat.ST_MODE])


# Is a path a regular file?
# This follows symbolic links, so both islink() and isdir() can be true
# for the same path.

def isfile(path):
	try:
		st = os.stat(path)
	except os.error:
		return 0
	return stat.S_ISREG(st[stat.ST_MODE])


# Is a path a mount point?
# XXX This degenerates in: 'is this the root?' on DOS

def ismount(path):
	return isabs(splitdrive(path)[1])


# Directory tree walk.
# For each directory under top (including top itself, but excluding
# '.' and '..'), func(arg, dirname, filenames) is called, where
# dirname is the name of the directory and filenames is the list
# files files (and subdirectories etc.) in the directory.
# The func may modify the filenames list, to implement a filter,
# or to impose a different order of visiting.

def walk(top, func, arg):
	try:
		names = os.listdir(top)
	except os.error:
		return
	func(arg, top, names)
	exceptions = ('.', '..')
	for name in names:
		if name not in exceptions:
			name = join(top, name)
			if isdir(name):
				walk(name, func, arg)


# Expand paths beginning with '~' or '~user'.
# '~' means $HOME; '~user' means that user's home directory.
# If the path doesn't begin with '~', or if the user or $HOME is unknown,
# the path is returned unchanged (leaving error reporting to whatever
# function is called with the expanded path as argument).
# See also module 'glob' for expansion of *, ? and [...] in pathnames.
# (A function should also be defined to do full *sh-style environment
# variable expansion.)

def expanduser(path):
	if path[:1] <> '~':
		return path
	i, n = 1, len(path)
	while i < n and path[i] not in '/\\':
		i = i+1
	if i == 1:
		if not os.environ.has_key('HOME'):
			return path
		userhome = os.environ['HOME']
	else:
		return path
	return userhome + path[i:]


# Expand paths containing shell variable substitutions.
# The following rules apply:
#	- no expansion within single quotes
#	- no escape character, except for '$$' which is translated into '$'
#	- ${varname} is accepted.
#	- varnames can be made out of letters, digits and the character '_'
# XXX With COMMAND.COM you can use any characters in a variable name,
# XXX except '^|<>='.

varchars = string.letters + string.digits + '_-'

def expandvars(path):
	if '$' not in path:
		return path
	res = ''
	index = 0
	pathlen = len(path)
	while index < pathlen:
		c = path[index]
		if c == '\'':	# no expansion within single quotes
			path = path[index + 1:]
			pathlen = len(path)
			try:
				index = string.index(path, '\'')
				res = res + '\'' + path[:index + 1]
			except string.index_error:
				res = res + path
				index = pathlen -1
		elif c == '$':	# variable or '$$'
			if path[index + 1:index + 2] == '$':
				res = res + c
				index = index + 1
			elif path[index + 1:index + 2] == '{':
				path = path[index+2:]
				pathlen = len(path)
				try:
					index = string.index(path, '}')
					var = path[:index]
					if os.environ.has_key(var):
						res = res + os.environ[var]
				except string.index_error:
					res = res + path
					index = pathlen - 1
			else:
				var = ''
				index = index + 1
				c = path[index:index + 1]
				while c != '' and c in varchars:
					var = var + c
					index = index + 1
					c = path[index:index + 1]
				if os.environ.has_key(var):
					res = res + os.environ[var]
				if c != '':
					res = res + c
		else:
			res = res + c
		index = index + 1
	return res


# Normalize a path, e.g. A//B, A/./B and A/foo/../B all become A/B.
# Also, components of the path are silently truncated to 8+3 notation.

def normpath(path):
	path = string.replace(path, "/", "\\")
	prefix, path = splitdrive(path)
	while path[:1] == os.sep:
		prefix = prefix + os.sep
		path = path[1:]
	comps = string.splitfields(path, os.sep)
	i = 0
	while i < len(comps):
		if comps[i] == '.':
			del comps[i]
		elif comps[i] == '..' and i > 0 and \
					  comps[i-1] not in ('', '..'):
			del comps[i-1:i+1]
			i = i-1
		elif comps[i] == '' and i > 0 and comps[i-1] <> '':
			del comps[i]
		elif '.' in comps[i]:
			comp = string.splitfields(comps[i], '.')
			comps[i] = comp[0][:8] + '.' + comp[1][:3]
			i = i+1
		elif len(comps[i]) > 8:
			comps[i] = comps[i][:8]
			i = i+1
		else:
			i = i+1
	# If the path is now empty, substitute '.'
	if not prefix and not comps:
		comps.append('.')
	return prefix + string.joinfields(comps, os.sep)



# Return an absolute path.
def abspath(path):
    if not isabs(path):
        path = join(os.getcwd(), path)
    return normpath(path)
