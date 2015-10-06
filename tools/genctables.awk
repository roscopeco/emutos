#
# genctables.awk - generate country tables
#
# Copyright (c) 2002-2015 The EmuTOS development team
#
# Authors:
#  LVL     Laurent Vogel
#
# This file is distributed under the GPL, version 2 or at your
# option any later version.  See doc/license.txt for details.
#

function now(   d)
{
    "date" | getline d
    close("date")
    return d
}

BEGIN {
    print "/*"
    print " * ctables.h - country tables for bios/country.h"
    print " *"
    print " * This file was automatically generated by genctables.awk on"
    print " * " now() " - do not alter!"
    print " */\n"
}

/^i18n_[^_]*_lang/ {
    country = toupper(substr($1,6))
    sub(/_.*/, "", country)
    sub(/^[^=]*= */, "")
    langs[country] = $0
}

/^i18n_[^_]*_keyb/ {
    sub(/^[^=]*= */, "")
    keybs[country] = $0
}

/^i18n_[^_]*_cset/ {
    sub(/^[^=]*= */, "")
    csets[country] = $0
}

/^i18n_[^_]*_idt/ {
    sub(/^[^=]*= */, "")
    idts[country] = $0
}

/^COUNTRIES/ {
    sub(/^[^=]*= */, "")
    $0 = toupper($0)
    ncountries = split($0, countries)
}

END {
    for(i = 1 ; i <= ncountries ; i++) {
        country = countries[i]
        needkeybs[keybs[country]] = 1
        needcsets[csets[country]] = 1
    }

    print "/* Indexes of keyboard layouts inside keytables[] */"
    i = 0
    for(keyb in needkeybs) {
        print "#define KEYB_" keyb " " i
        i++
    }
    print ""

    print "/* Indexes of font sets inside font_sets[] */"
    i = 0
    for(cset in needcsets) {
        print "#define CHARSET_" cset " " i
        i++
    }
    print ""

    print "#if CONF_MULTILANG"
    print "static const struct country_record countries[] = {"
    for(i = 1 ; i <= ncountries ; i++) {
        country = countries[i]
        print "    { COUNTRY_" country ", \"" langs[country] "\", " \
            "KEYB_" keybs[country] ", CHARSET_" csets[country] ", " \
            idts[country] "},"
    }
    print "};"
    print "#endif\n\n"

    for(keyb in needkeybs) {
        print "#if CONF_MULTILANG || CONF_KEYB == KEYB_" keyb
        print "#include \"keyb_" tolower(keyb) ".h\""
        print "#endif"
    }
    print "\nstatic const struct keytbl *keytables[] = {"
    for(keyb in needkeybs) {
        print "#if CONF_MULTILANG || CONF_KEYB == KEYB_" keyb
        print "    &keytbl_" tolower(keyb) ","
        print "#endif"
    }
    print "};\n\n"

    for(cset in needcsets) {
        lcset = tolower(cset)
        print "extern const Fonthead fnt_" lcset "_6x6;"
        print "extern const Fonthead fnt_" lcset "_8x8;"
        print "extern const Fonthead fnt_" lcset "_8x16;"
    }
    print "\nstatic const struct charset_fonts font_sets[] = {"
    for(cset in needcsets) {
        lcset = tolower(cset)
        print "#if CONF_MULTILANG || CONF_CHARSET == CHARSET_" cset
        print "    { &fnt_" lcset "_6x6, &fnt_" lcset \
            "_8x8, &fnt_" lcset "_8x16 },"
        print "#endif"
    }
    print "};"

}
