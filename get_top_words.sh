#!/bin/bash

FILE1=$1
k=$2


words="i
me
my
myself
we
our
ours
ourselves
you
your
yours
yourself
yourselves
he
him
his
himself
she
her
hers
herself
it
its
itself
they
them
their
theirs
themselves
what
which
who
whom
this
that
these
those
am
is
are
was
were
be
been
being
have
has
had
having
do
does
did
doing
a
an
the
and
but
if
or
because
as
until
while
of
at
by
for
with
about
against
between
into
through
during
before
after
above
below
to
from
up
down
in
out
on
off
over
under
again
further
then
once
here
there
when
where
why
how
all
any
both
each
few
more
most
other
some
such
no
nor
not
only
own
same
so
than
too
very
s
t
can
will
just
don
should
now"

touch ./tmpfile0
FILE2=./tmpfile0
echo "$words" > $FILE2

touch ./tmpfile
FILE3=./tmpfile
touch ./tmpfile2
FILE4=./tmpfile2
touch ./tmpfile3
FILE5=./tmpfile3

touch ./tmpfile4
FILE6=./tmpfile4
# remove caps
tr '[A-Z]' '[a-z]' <$FILE1> $FILE3
# remove punctuation
tr -d '[:punct:]' <$FILE3> $FILE4
tr ' ' '\n' <$FILE4> $FILE5
# newline each word
# remove same words
grep -Fvxf $FILE2 $FILE5 > $FILE6

# Get sorted word counts
sort $FILE6 | uniq -c | sort -k1,1nr -k2 > $FILE6.counts 

# Print top occurrence count word  
head -n 1 $FILE6.counts | awk '{print $2}'

# Print remaining top N-1 words alphabetically
tail -n +2 $FILE6.counts | head -n $((k-1)) | sort -k2 | awk '{print $2}'

