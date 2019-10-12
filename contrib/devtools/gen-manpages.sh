#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

CLMD=${CLMD:-$SRCDIR/colombod}
CLMCLI=${CLMCLI:-$SRCDIR/colombo-cli}
CLMTX=${CLMTX:-$SRCDIR/colombo-tx}
CLMQT=${CLMQT:-$SRCDIR/qt/colombo-qt}

[ ! -x $CLMD ] && echo "$CLMD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
CLMVER=($($CLMCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for colombod if --version-string is not set,
# but has different outcomes for colombo-qt and colombo-cli.
echo "[COPYRIGHT]" > footer.h2m
$CLMD --version | sed -n '1!p' >> footer.h2m

for cmd in $CLMD $CLMCLI $CLMTX $CLMQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${CLMVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${CLMVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
