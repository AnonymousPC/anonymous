#if defined(__GNUC__) and not defined(__clang__)
    #error "not coded yet"
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wunknown-pragmas"
#elif defined(_MSC_VER) and not defined(__clang__)
    #error "not coded yet"
#endif

#ifdef _WIN32
    #error "not coded yet"
#elif defined(__linux__) or defined(__MACH__)
    #pragma build "mkdir -p $anonymous/bin/$type/cmake/icu-build"
    #pragma build "cd $anonymous/bin/$type/cmake/icu-build"
    #pragma build "sh $anonymous/third_party/git/icu/icu4c/source/configure --prefix=$anonymous/bin/$type/cmake/icu-install --disable-icu-config --disable-shared --enable-static --disable-tools --disable-tests --disable-samples"
    #pragma build "make -j8"
    #pragma build "make install"
    #pragma build "cp $anonymous/bin/$type/cmake/icu-install/lib/libicudata.$library_suffix $anonymous/bin/$type/module/icu.data.$library_suffix"
    #pragma build "cp $anonymous/bin/$type/cmake/icu-install/lib/libicui18n.$library_suffix $anonymous/bin/$type/module/icu.internationalization.$library_suffix"
    #pragma build "cp $anonymous/bin/$type/cmake/icu-install/lib/libicuio.$library_suffix   $anonymous/bin/$type/module/icu.io.$library_suffix"
    #pragma build "cp $anonymous/bin/$type/cmake/icu-install/lib/libicutest.$library_suffix $anonymous/bin/$type/module/icu.test.$library_suffix"
    #pragma build "cp $anonymous/bin/$type/cmake/icu-install/lib/libicutu.$library_suffix   $anonymous/bin/$type/module/icu.tools.$library_suffix"
    #pragma build "cp $anonymous/bin/$type/cmake/icu-install/lib/libicuuc.$library_suffix   $anonymous/bin/$type/module/icu.common.$library_suffix"
#endif

/* 
>>> ./third_party/git/icu/icu4c/source/configure -h
'configure' configures ICU 78.0.1 to adapt to many kinds of systems.

Usage: ./third_party/git/icu/icu4c/source/configure [OPTION]... [VAR=VALUE]...

To assign environment variables (e.g., CC, CFLAGS...), specify them as
VAR=VALUE.  See below for descriptions of some of the useful variables.

Defaults for the options are specified in brackets.

Configuration:
  -h, --help              display this help and exit
      --help=short        display options specific to this package
      --help=recursive    display the short help of all the included packages
  -V, --version           display version information and exit
  -q, --quiet, --silent   do not print 'checking ...' messages
      --cache-file=FILE   cache test results in FILE [disabled]
  -C, --config-cache      alias for '--cache-file=config.cache'
  -n, --no-create         do not create output files
      --srcdir=DIR        find the sources in DIR [configure dir or '..']

Installation directories:
  --prefix=PREFIX         install architecture-independent files in PREFIX
                          [/usr/local]
  --exec-prefix=EPREFIX   install architecture-dependent files in EPREFIX
                          [PREFIX]

By default, 'make install' will install all the files in
'/usr/local/bin', '/usr/local/lib' etc.  You can specify
an installation prefix other than '/usr/local' using '--prefix',
for instance '--prefix=$HOME'.

For better control, use the options below.

Fine tuning of the installation directories:
  --bindir=DIR            user executables [EPREFIX/bin]
  --sbindir=DIR           system admin executables [EPREFIX/sbin]
  --libexecdir=DIR        program executables [EPREFIX/libexec]
  --sysconfdir=DIR        read-only single-machine data [PREFIX/etc]
  --sharedstatedir=DIR    modifiable architecture-independent data [PREFIX/com]
  --localstatedir=DIR     modifiable single-machine data [PREFIX/var]
  --runstatedir=DIR       modifiable per-process data [LOCALSTATEDIR/run]
  --libdir=DIR            object code libraries [EPREFIX/lib]
  --includedir=DIR        C header files [PREFIX/include]
  --oldincludedir=DIR     C header files for non-gcc [/usr/include]
  --datarootdir=DIR       read-only arch.-independent data root [PREFIX/share]
  --datadir=DIR           read-only architecture-independent data [DATAROOTDIR]
  --infodir=DIR           info documentation [DATAROOTDIR/info]
  --localedir=DIR         locale-dependent data [DATAROOTDIR/locale]
  --mandir=DIR            man documentation [DATAROOTDIR/man]
  --docdir=DIR            documentation root [DATAROOTDIR/doc/icu4c]
  --htmldir=DIR           html documentation [DOCDIR]
  --dvidir=DIR            dvi documentation [DOCDIR]
  --pdfdir=DIR            pdf documentation [DOCDIR]
  --psdir=DIR             ps documentation [DOCDIR]

System types:
  --build=BUILD     configure for building on BUILD [guessed]
  --host=HOST       cross-compile to build programs to run on HOST [BUILD]

Optional Features:
  --disable-option-checking  ignore unrecognized --enable/--with options
  --disable-FEATURE       do not include FEATURE (same as --enable-FEATURE=no)
  --enable-FEATURE[=ARG]  include FEATURE [ARG=yes]
  --disable-icu-config    do not install icu-config
  --enable-debug          build debug libraries and enable the U_DEBUG define
  --disable-release       do not build release libraries
  --disable-strict        do not compile with strict compiler options
  --enable-64bit-libs     (deprecated, use --with-library-bits) build 64-bit libraries default= platform default
  --disable-shared        do not build shared libraries
  --enable-static         build static libraries
  --enable-auto-cleanup   enable auto cleanup of libraries
  --disable-draft         do not enable draft APIs (and internal APIs)
  --disable-renaming      do not add a version suffix to symbols
  --enable-tracing        enable function and data tracing
  --enable-plugins        enable plugins
  --disable-dyload        disable dynamic loading
  --enable-rpath          use rpath when linking default is only if necessary
  --enable-weak-threads   weakly reference the threading library
  --disable-extras        do not build ICU extras
  --disable-icuio         do not build ICU's icuio library
  --enable-layoutex       build ICU's Paragraph Layout library.
            icu-le-hb must be installed via pkg-config. See http://harfbuzz.org

  --disable-tools         do not build ICU's tools
  --enable-fuzzer         build ICU's fuzzer test targets
  --disable-tests         do not build ICU tests
  --disable-samples       do not build ICU samples

Additionally, the variable FORCE_LIBS may be set before calling configure.
If set, it will REPLACE any automatic list of libraries.

Optional Packages:
  --with-PACKAGE[=ARG]    use PACKAGE [ARG=yes]
  --without-PACKAGE       do not use PACKAGE (same as --with-PACKAGE=no)
  --with-cross-build=dir specify an absolute path to the build directory of an ICU built for the current platform default=no cross dir
  --with-library-bits=bits specify how many bits to use for the library (32, 64, 64else32, nochange) default=nochange
  --with-data-packaging     specify how to package ICU data. Possible values:
        files    raw files (.res, etc)
        archive  build a single icudtXX.dat file
        library  shared library (.dll/.so/etc.)
        static   static library (.a/.lib/etc.)
        auto     build shared if possible (default)
           See https://unicode-org.github.io/icu/userguide/icu_data for more info.
  --with-library-suffix=suffix    tag a suffix to the library names default=

Some influential environment variables:
  CC          C compiler command
  CFLAGS      C compiler flags
  LDFLAGS     linker flags, e.g. -L<lib dir> if you have libraries in a
              nonstandard directory <lib dir>
  LIBS        libraries to pass to the linker, e.g. -l<library>
  CPPFLAGS    (Objective) C/C++ preprocessor flags, e.g. -I<include dir> if
              you have headers in a nonstandard directory <include dir>
  CXX         C++ compiler command
  CXXFLAGS    C++ compiler flags
  PKG_CONFIG  path to pkg-config utility
  PKG_CONFIG_PATH
              directories to add to pkg-config's search path
  PKG_CONFIG_LIBDIR
              path overriding pkg-config's built-in search path
  ICULEHB_CFLAGS
              C compiler flags for ICULEHB, overriding pkg-config
  ICULEHB_LIBS
              linker flags for ICULEHB, overriding pkg-config
  CPP         C preprocessor

Use these variables to override the choices made by 'configure' or to help
it to find libraries and programs with nonstandard names/locations.

Report bugs to <https://icu.unicode.org/bugs>.
ICU home page: <https://icu.unicode.org/>.
*/

module;
#undef in
#include <unicode/appendable.h>
#include <unicode/brkiter.h>
#include <unicode/bytestream.h>
#include <unicode/bytestrie.h>
#include <unicode/bytestriebuilder.h>
#include <unicode/caniter.h>
#include <unicode/casemap.h>
#include <unicode/char16ptr.h>
#include <unicode/chariter.h>
#include <unicode/dbbi.h>
#include <unicode/docmain.h>
#include <unicode/dtintrv.h>
#include <unicode/edits.h>
#include <unicode/enumset.h>
#include <unicode/errorcode.h>
#include <unicode/filteredbrk.h>
#include <unicode/icudataver.h>
#include <unicode/icuplug.h>
#include <unicode/idna.h>
#include <unicode/localebuilder.h>
#include <unicode/localematcher.h>
#include <unicode/localpointer.h>
#include <unicode/locdspnm.h>
#include <unicode/locid.h>
#include <unicode/messagepattern.h>
#include <unicode/normalizer2.h>
#include <unicode/normlzr.h>
#include <unicode/parseerr.h>
#include <unicode/parsepos.h>
#include <unicode/platform.h>
#include <unicode/ptypes.h>
#include <unicode/putil.h>
#include <unicode/rbbi.h>
#include <unicode/rep.h>
#include <unicode/resbund.h>
#include <unicode/schriter.h>
#include <unicode/simpleformatter.h>
#include <unicode/std_string.h>
#include <unicode/strenum.h>
#include <unicode/stringoptions.h>
#include <unicode/stringpiece.h>
#include <unicode/stringtriebuilder.h>
#include <unicode/symtable.h>
#include <unicode/ubidi.h>
#include <unicode/ubiditransform.h>
#include <unicode/ubrk.h>
#include <unicode/ucasemap.h>
#include <unicode/ucat.h>
#include <unicode/uchar.h>
#include <unicode/ucharstrie.h>
#include <unicode/ucharstriebuilder.h>
#include <unicode/uchriter.h>
#include <unicode/uclean.h>
#include <unicode/ucnv_cb.h>
#include <unicode/ucnv_err.h>
#include <unicode/ucnv.h>
#include <unicode/ucnvsel.h>
#include <unicode/uconfig.h>
#include <unicode/ucpmap.h>
#include <unicode/ucptrie.h>
#include <unicode/ucurr.h>
#include <unicode/udata.h>
#include <unicode/udisplaycontext.h>
#include <unicode/uenum.h>
#include <unicode/uidna.h>
#include <unicode/uiter.h>
#include <unicode/uldnames.h>
#include <unicode/uloc.h>
#include <unicode/ulocale.h>
#include <unicode/ulocbuilder.h>
#include <unicode/umachine.h>
#include <unicode/umisc.h>
#include <unicode/umutablecptrie.h>
#include <unicode/unifilt.h>
#include <unicode/unifunct.h>
#include <unicode/unimatch.h>
#include <unicode/uniset.h>
#include <unicode/unistr.h>
#include <unicode/unorm.h>
#include <unicode/unorm2.h>
#include <unicode/uobject.h>
#include <unicode/urename.h>
#include <unicode/urep.h>
#include <unicode/ures.h>
#include <unicode/uscript.h>
#include <unicode/uset.h>
#include <unicode/usetiter.h>
#include <unicode/ushape.h>
#include <unicode/usprep.h>
#include <unicode/ustring.h>
#include <unicode/ustringtrie.h>
#include <unicode/utext.h>
#include <unicode/utf_old.h>
#include <unicode/utf.h>
#include <unicode/utf16.h>
#include <unicode/utf32.h>
#include <unicode/utf8.h>
#include <unicode/utfiterator.h>
#include <unicode/utrace.h>
#include <unicode/utypes.h>
#include <unicode/uvernum.h>
#include <unicode/uversion.h>
#include <unicode/alphaindex.h>
#include <unicode/basictz.h>
#include <unicode/calendar.h>
#include <unicode/choicfmt.h>
#include <unicode/coleitr.h>
#include <unicode/coll.h>
#include <unicode/compactdecimalformat.h>
#include <unicode/curramt.h>
#include <unicode/currpinf.h>
#include <unicode/currunit.h>
#include <unicode/datefmt.h>
#include <unicode/dcfmtsym.h>
#include <unicode/decimfmt.h>
#include <unicode/displayoptions.h>
#include <unicode/dtfmtsym.h>
#include <unicode/dtitvfmt.h>
#include <unicode/dtitvinf.h>
#include <unicode/dtptngen.h>
#include <unicode/dtrule.h>
#include <unicode/fieldpos.h>
#include <unicode/fmtable.h>
#include <unicode/format.h>
#include <unicode/formattednumber.h>
#include <unicode/formattedvalue.h>
#include <unicode/fpositer.h>
#include <unicode/gender.h>
#include <unicode/gregocal.h>
#include <unicode/listformatter.h>
#include <unicode/measfmt.h>
#include <unicode/measunit.h>
#include <unicode/measure.h>
#include <unicode/messageformat2_arguments.h>
#include <unicode/messageformat2_data_model_names.h>
#include <unicode/messageformat2_data_model.h>
#include <unicode/messageformat2_formattable.h>
#include <unicode/messageformat2_function_registry.h>
#include <unicode/messageformat2.h>
#include <unicode/msgfmt.h>
#include <unicode/nounit.h>
#include <unicode/numberformatter.h>
#include <unicode/numberrangeformatter.h>
#include <unicode/numfmt.h>
#include <unicode/numsys.h>
#include <unicode/plurfmt.h>
#include <unicode/plurrule.h>
#include <unicode/rbnf.h>
#include <unicode/rbtz.h>
#include <unicode/regex.h>
#include <unicode/region.h>
#include <unicode/reldatefmt.h>
#include <unicode/scientificnumberformatter.h>
#include <unicode/search.h>
#include <unicode/selfmt.h>
#include <unicode/simplenumberformatter.h>
#include <unicode/simpletz.h>
#include <unicode/smpdtfmt.h>
#include <unicode/sortkey.h>
#include <unicode/stsearch.h>
#include <unicode/tblcoll.h>
#include <unicode/timezone.h>
#include <unicode/tmunit.h>
#include <unicode/tmutamt.h>
#include <unicode/tmutfmt.h>
#include <unicode/translit.h>
#include <unicode/tzfmt.h>
#include <unicode/tznames.h>
#include <unicode/tzrule.h>
#include <unicode/tztrans.h>
#include <unicode/ucal.h>
#include <unicode/ucol.h>
#include <unicode/ucoleitr.h>
#include <unicode/ucsdet.h>
#include <unicode/udat.h>
#include <unicode/udateintervalformat.h>
#include <unicode/udatpg.h>
#include <unicode/udisplayoptions.h>
#include <unicode/ufieldpositer.h>
#include <unicode/uformattable.h>
#include <unicode/uformattednumber.h>
#include <unicode/uformattedvalue.h>
#include <unicode/ugender.h>
#include <unicode/ulistformatter.h>
#include <unicode/ulocdata.h>
#include <unicode/umsg.h>
#include <unicode/unirepl.h>
#include <unicode/unum.h>
#include <unicode/unumberformatter.h>
#include <unicode/unumberoptions.h>
#include <unicode/unumberrangeformatter.h>
#include <unicode/unumsys.h>
#include <unicode/upluralrules.h>
#include <unicode/uregex.h>
#include <unicode/uregion.h>
#include <unicode/ureldatefmt.h>
#include <unicode/usearch.h>
#include <unicode/usimplenumberformatter.h>
#include <unicode/uspoof.h>
#include <unicode/utmscale.h>
#include <unicode/utrans.h>
#include <unicode/vtzone.h>
#include <unicode/ustdio.h>
#include <unicode/ustream.h>

export module icu;