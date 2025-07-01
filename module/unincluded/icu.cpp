module;
#undef in
#include <unicode/umachine.h> // include this header first to avoid deprecation
#undef U_ATTRIBUTE_DEPRECATED // avoid deprecation
#define U_ATTRIBUTE_DEPRECATED // avoid deprecation
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

#define U_COMMON_IMPLEMENTATION
#define U_I18N_IMPLEMENTATION
#define U_IO_IMPLEMENTATION
#include <unicode/src/appendable.cpp>
#include <unicode/src/bmpset.cpp>
#include <unicode/src/brkeng.cpp>
#include <unicode/src/brkiter.cpp>
#include <unicode/src/bytesinkutil.cpp>
#include <unicode/src/bytestream.cpp>
#include <unicode/src/bytestrie.cpp>
#include <unicode/src/bytestriebuilder.cpp>
#include <unicode/src/bytestrieiterator.cpp>
#include <unicode/src/caniter.cpp>
#include <unicode/src/characterproperties.cpp>
#include <unicode/src/chariter.cpp>
#include <unicode/src/charstr.cpp>
#include <unicode/src/cmemory.cpp>
#include <unicode/src/cstr.cpp>
#include <unicode/src/cstring.cpp>
#include <unicode/src/cwchar.cpp>
#include <unicode/src/dictbe.cpp>
#include <unicode/src/dictionarydata.cpp>
#include <unicode/src/dtintrv.cpp>
#include <unicode/src/edits.cpp>
#include <unicode/src/emojiprops.cpp>
#include <unicode/src/errorcode.cpp>
#include <unicode/src/filteredbrk.cpp>
#include <unicode/src/filterednormalizer2.cpp>
#include <unicode/src/icudataver.cpp>
#include <unicode/src/icuplug.cpp>
#include <unicode/src/loadednormalizer2impl.cpp>
#include <unicode/src/localebuilder.cpp>
#include <unicode/src/localematcher.cpp>
#include <unicode/src/localeprioritylist.cpp>
#include <unicode/src/locavailable.cpp>
#include <unicode/src/locbased.cpp>
#include <unicode/src/locdispnames.cpp>
#include <unicode/src/locdistance.cpp>
#include <unicode/src/locdspnm.cpp>
#include <unicode/src/locid.cpp>
#include <unicode/src/loclikely.cpp>
#define gInitOnce gInitOnce_1 // avoid redefinition
#define cleanup cleanup_1 // avoid redifinition, later undef in <unicode/src/umutex.cpp>
#include <unicode/src/loclikelysubtags.cpp>
#include <unicode/src/locmap.cpp>
#include <unicode/src/locresdata.cpp>
#include <unicode/src/locutil.cpp>
#include <unicode/src/lsr.cpp>
#include <unicode/src/lstmbe.cpp>
#include <unicode/src/messagepattern.cpp>
#include <unicode/src/mlbe.cpp>
#include <unicode/src/normalizer2.cpp>
#include <unicode/src/normalizer2impl.cpp>
#include <unicode/src/normlzr.cpp>
#include <unicode/src/parsepos.cpp>
#include <unicode/src/patternprops.cpp>
#include <unicode/src/pluralmap.cpp>
#include <unicode/src/propname.cpp>
#include <unicode/src/propsvec.cpp>
#include <unicode/src/punycode.cpp>
#include <unicode/src/putil.cpp>
#include <unicode/src/rbbi_cache.cpp>
#include <unicode/src/rbbi.cpp>
#include <unicode/src/rbbidata.cpp>
#include <unicode/src/rbbinode.cpp>
#include <unicode/src/rbbirb.cpp>
#include <unicode/src/rbbiscan.cpp>
#include <unicode/src/rbbisetb.cpp>
#include <unicode/src/rbbistbl.cpp>
#include <unicode/src/rbbitblb.cpp>
#include <unicode/src/resbund_cnv.cpp>
#include <unicode/src/resbund.cpp>
#include <unicode/src/resource.cpp>
#include <unicode/src/restrace.cpp>
#include <unicode/src/ruleiter.cpp>
#include <unicode/src/schriter.cpp>
#include <unicode/src/serv.cpp>
#include <unicode/src/servlk.cpp>
#include <unicode/src/servlkf.cpp>
#include <unicode/src/servls.cpp>
#include <unicode/src/servnotf.cpp>
#include <unicode/src/servrbf.cpp>
#include <unicode/src/servslkf.cpp>
#include <unicode/src/sharedobject.cpp>
#include <unicode/src/simpleformatter.cpp>
#include <unicode/src/static_unicode_sets.cpp>
#include <unicode/src/stringpiece.cpp>
#include <unicode/src/stringtriebuilder.cpp>
#include <unicode/src/uarrsort.cpp>
#include <unicode/src/ubidi_props.cpp>
#include <unicode/src/ubidi.cpp>
#include <unicode/src/ubidiln.cpp>
#include <unicode/src/ubiditransform.cpp>
#include <unicode/src/ubidiwrt.cpp>
#include <unicode/src/ubrk.cpp>
#define _enumPropertyStartsRange _enumPropertyStartsRange_1 // avoid redefinition
#include <unicode/src/ucase.cpp>
#include <unicode/src/ucasemap_titlecase_brkiter.cpp>
#include <unicode/src/ucasemap.cpp>
#include <unicode/src/ucat.cpp>
#define dataVersion dataVersion_1 // This #define is later undef in <unicode/src/usprep.cpp>, because <unicode/src/usprep.cpp> needs `dataVersion` in both file.
#define _enumPropertyStartsRange_1 _enumPropertyStartsRange_2 // avoid redefinition
#include <unicode/src/uchar.cpp>
#include <unicode/src/ucharstrie.cpp>
#define compareElementStrings compareElementStrings_1 // avoid redefinition
#include <unicode/src/ucharstriebuilder.cpp>
#include <unicode/src/ucharstrieiterator.cpp>
#include <unicode/src/uchriter.cpp>
#include <unicode/src/ucln_cmn.cpp>
#include <unicode/src/ucmndata.cpp>
#undef DATA_TYPE // from src
#define DATA_TYPE DATA_TYPE_1 // avoid redefinition
#include <unicode/src/ucnv_bld.cpp>
#include <unicode/src/ucnv_cb.cpp>
#include <unicode/src/ucnv_cnv.cpp>
#include <unicode/src/ucnv_ct.cpp>
#include <unicode/src/ucnv_err.cpp>
#include <unicode/src/ucnv_ext.cpp>
#define DATA_TYPE_1 DATA_TYPE_2 // avoid redefinition
#include <unicode/src/ucnv_io.cpp>
#include <unicode/src/ucnv_lmb.cpp>
#include <unicode/src/ucnv_set.cpp>
#include <unicode/src/ucnv_u16.cpp>
#define UCNV_NEED_TO_WRITE_BOM UCNV_NEED_TO_WRITE_BOM_1 // avoid redefinition
#include <unicode/src/ucnv_u32.cpp>
#include <unicode/src/ucnv_u7.cpp>
#include <unicode/src/ucnv_u8.cpp>
#include <unicode/src/ucnv.cpp>
#undef CR // from src
#undef LF // from src
#include <unicode/src/ucnv2022.cpp>
#include <unicode/src/ucnvbocu.cpp>
#include <unicode/src/ucnvdisp.cpp>
#include <unicode/src/ucnvhz.cpp>
#define ZERO ZERO_1 // avoid redefinition
#include <unicode/src/ucnvisci.cpp>
#include <unicode/src/ucnvlat1.cpp>
#include <unicode/src/ucnvmbcs.cpp>
#include <unicode/src/ucnvscsu.cpp>
#include <unicode/src/ucnvsel.cpp>
#include <unicode/src/ucol_swp.cpp>
#include <unicode/src/ucptrie.cpp>
#include <unicode/src/ucurr.cpp>
#include <unicode/src/udata.cpp>
#include <unicode/src/udatamem.cpp>
#include <unicode/src/udataswp.cpp>
#include <unicode/src/uenum.cpp>
#include <unicode/src/uhash_us.cpp>
#include <unicode/src/uhash.cpp>
#include <unicode/src/uidna.cpp>
#include <unicode/src/uinit.cpp>
#include <unicode/src/uinvchar.cpp>
#include <unicode/src/uiter.cpp>
#include <unicode/src/ulist.cpp>
#include <unicode/src/uloc_keytype.cpp>
#include <unicode/src/uloc_tag.cpp>
#define UPRV_ISDIGIT UPRV_ISDIGIT_1 // avoid redefinition
#define UPRV_ISALPHANUM UPRV_ISALPHANUM_1 // avoid redefinition
#undef MINLEN // from src
#include <unicode/src/uloc.cpp>
#include <unicode/src/ulocale.cpp>
#undef EXTERNAL // from src
#undef INTERNAL // from src
#undef CONST_INTERNAL // from src
#include <unicode/src/ulocbuilder.cpp>
#include <unicode/src/umapfile.cpp>
#include <unicode/src/umath.cpp>
#define getRange getRange_1 // avoid redefinition
#include <unicode/src/umutablecptrie.cpp>
#undef cleanup // undef macro in <unicode/src/loclikelysubtags.cpp>, because `UMutex::cleanup` cannot be renamed.
#include <unicode/src/umutex.cpp>
#include <unicode/src/unames.cpp>
#include <unicode/src/unifiedcache.cpp>
#include <unicode/src/unifilt.cpp>
#include <unicode/src/unifunct.cpp>
#include <unicode/src/uniset_closure.cpp>
#define ASCII ASCII_1 // avoid redefinition
#include <unicode/src/uniset_props.cpp>
#define compareUnicodeString compareUnicodeString_1 // avoid redefinition
#undef _dbgct // from src
#include <unicode/src/uniset.cpp>
#include <unicode/src/unisetspan.cpp>
#include <unicode/src/unistr_case_locale.cpp>
#include <unicode/src/unistr_case.cpp>
#include <unicode/src/unistr_cnv.cpp>
#include <unicode/src/unistr_props.cpp>
#include <unicode/src/unistr_titlecase_brkiter.cpp>
#include <unicode/src/unistr.cpp>
#include <unicode/src/unorm.cpp>
#include <unicode/src/unormcmp.cpp>
#include <unicode/src/uobject.cpp>
#include <unicode/src/uprops.cpp>
#include <unicode/src/ures_cnv.cpp>
#define gCacheInitOnce gCacheInitOnce_1 // avoid redefinition
#define cache cache_1 // avoid redefinition, later undef in <unicode/src/measfmt.cpp>
#include <unicode/src/uresbund.cpp>
#define gEmptyString gEmptyString_1 // avoid redefinition
#define isAcceptable isAcceptable_1 // avoid redefinition
#define STACK_ROW_CAPACITY STACK_ROW_CAPACITY_1 // avoid redefinition
#include <unicode/src/uresdata.cpp>
#include <unicode/src/usc_impl.cpp>
#define UBIDI_RTL UBIDI_RTL_1 // avoid redefinition
#include <unicode/src/uscript_props.cpp>
#include <unicode/src/uscript.cpp>
#include <unicode/src/uset_props.cpp>
#include <unicode/src/uset.cpp>
#include <unicode/src/usetiter.cpp>
#include <unicode/src/ushape.cpp>
#define SHARED_DATA_HASHTABLE SHARED_DATA_HASHTABLE_1 // avoid redefinition
#define hashEntry hashEntry_1 // avoid redefinition
#define compareEntries compareEntries_1 // avoid redefinition
#define createCache createCache_1 // avoid redefinition
#define initCache initCache_1 // avoid redefinition
#undef dataVersion // see <unicode/src/uchar_props_data.h>
#include <unicode/src/usprep.cpp>
#include <unicode/src/ustack.cpp>
#include <unicode/src/ustr_cnv.cpp>
#include <unicode/src/ustr_titlecase_brkiter.cpp>
#include <unicode/src/ustr_wcs.cpp>
#include <unicode/src/ustrcase_locale.cpp>
#define CmpEquivLevel CmpEquivLevel_1 // avoid redefinition
#include <unicode/src/ustrcase.cpp>
#include <unicode/src/ustrenum.cpp>
#include <unicode/src/ustrfmt.cpp>
#include <unicode/src/ustring.cpp>
#include <unicode/src/ustrtrns.cpp>
#define gEmptyString_1 gEmptyString_2 // avoid redefinition
#include <unicode/src/utext.cpp>
#include <unicode/src/utf_impl.cpp>
#include <unicode/src/util_props.cpp>
#undef BACKSLASH // from src
#undef SPACE // from src
#define DIGITS DIGITS_1 // from src
#include <unicode/src/util.cpp>
#include <unicode/src/utrace.cpp>
#define ASCII_LIMIT ASCII_LIMIT_1 // avoid redefinition
#include <unicode/src/utrie_swap.cpp>
#include <unicode/src/utrie.cpp>
#define writeBlock writeBlock_1 // avoid redefinition
#define equal_uint32 equal_uint32_1 // avoid redefinition
#include <unicode/src/utrie2_builder.cpp>
#define enumSameValue enumSameValue_1 // avoid redefinition
#include <unicode/src/utrie2.cpp>
#include <unicode/src/uts46.cpp>
#include <unicode/src/utypes.cpp>
#undef HINT_KEY_POINTER // from src
#include <unicode/src/uvector.cpp>
#include <unicode/src/uvectr32.cpp>
#include <unicode/src/uvectr64.cpp>
#include <unicode/src/wintz.cpp>
#undef BASE // from src
#include <unicode/src/alphaindex.cpp>
#define ANY ANY_1 // avoid redefinition
#include <unicode/src/anytrans.cpp>
#include <unicode/src/astro.cpp>
#include <unicode/src/basictz.cpp>
#include <unicode/src/bocsu.cpp>
#include <unicode/src/brktrans.cpp>
#include <unicode/src/buddhcal.cpp>
#define gService gService_1 // avoid redefinition
#include <unicode/src/calendar.cpp>
#include <unicode/src/casetrn.cpp>
#include <unicode/src/cecal.cpp>
#define LIMITS LIMITS_1 // avoid redefinition
#define gSystemDefaultCenturyStart gSystemDefaultCenturyStart_1 // avoid redefinition
#define gSystemDefaultCenturyStartYear gSystemDefaultCenturyStartYear_1 // avoid redefinition
#define gSystemDefaultCenturyInit gSystemDefaultCenturyInit_1 // avoid redefinition
#define initializeSystemDefaultCentury initializeSystemDefaultCentury_1 // avoid redefinition
#include <unicode/src/chnsecal.cpp>
#undef MINUS // from src
#include <unicode/src/choicfmt.cpp>
#undef isDigit // from src
#include <unicode/src/coleitr.cpp>
#define gService_1 gService_2 // avoid redefinition
#define gServiceInitOnce gServiceInitOnce_1 // avoid redefinition
#define availableLocaleList availableLocaleList_1 // avoid redefinition
#define availableLocaleListCount availableLocaleListCount_1 // avoid redefinition
#define initService initService_1 // avoid redefinition
#define getService getService_1 // avoid redefinition
#define hasService hasService_1 // avoid redefinition
#include <unicode/src/coll.cpp>
#include <unicode/src/collation.cpp>
#include <unicode/src/collationbuilder.cpp>
#include <unicode/src/collationcompare.cpp>
#include <unicode/src/collationdata.cpp>
#include <unicode/src/collationdatabuilder.cpp>
#include <unicode/src/collationdatareader.cpp>
#include <unicode/src/collationdatawriter.cpp>
#include <unicode/src/collationfastlatin.cpp>
#include <unicode/src/collationfastlatinbuilder.cpp>
#include <unicode/src/collationfcd.cpp>
#include <unicode/src/collationiterator.cpp>
#include <unicode/src/collationkeys.cpp>
#include <unicode/src/collationroot.cpp>
#include <unicode/src/collationrootelements.cpp>
#include <unicode/src/collationruleparser.cpp>
#include <unicode/src/collationsets.cpp>
#include <unicode/src/collationsettings.cpp>
#include <unicode/src/collationtailoring.cpp>
#include <unicode/src/collationweights.cpp>
#undef DEFAULT_CAPACITY // from src
#undef SINGLE_QUOTE // from src
#undef SLASH // from src
#undef COMMA // from src
#undef HYPHEN // from src
#undef TILDE // from src
#include <unicode/src/compactdecimalformat.cpp>
#define gSystemDefaultCenturyStart_1 gSystemDefaultCenturyStart_2 // avoid redefinition
#define gSystemDefaultCenturyStartYear_1 gSystemDefaultCenturyStartYear_2 // avoid redefinition
#define gSystemDefaultCenturyInit_1 gSystemDefaultCenturyInit_2 // avoid redefinition
#define initializeSystemDefaultCentury_1 initializeSystemDefaultCentury_2 // avoid redefinition
#include <unicode/src/coptccal.cpp>
#include <unicode/src/cpdtrans.cpp>
#include <unicode/src/csdetect.cpp>
#include <unicode/src/csmatch.cpp>
#include <unicode/src/csr2022.cpp>
#include <unicode/src/csrecog.cpp>
#include <unicode/src/csrmbcs.cpp>
#include <unicode/src/csrsbcs.cpp>
#include <unicode/src/csrucode.cpp>
#include <unicode/src/csrutf8.cpp>
#include <unicode/src/curramt.cpp>
#include <unicode/src/currfmt.cpp>
#include <unicode/src/currpinf.cpp>
#include <unicode/src/currunit.cpp>
#define gWinterSolsticeCache gWinterSolsticeCache_1 // avoid redefinition
#define gNewYearCache gNewYearCache_1 // avoid redefinition
#define gAstronomerTimeZone gAstronomerTimeZone_1 // avoid redefinition
#define gAstronomerTimeZoneInitOnce gAstronomerTimeZoneInitOnce_1 // avoid redefinition
#define initOnce initOnce_1 // avoid redefinition
#include <unicode/src/dangical.cpp>
#include <unicode/src/datefmt.cpp>
#include <unicode/src/dayperiodrules.cpp>
#include <unicode/src/dcfmtsym.cpp>
#include <unicode/src/decContext.cpp>
#include <unicode/src/decimfmt.cpp>
#undef DECNUMBERLOC // from src
#define bcdnum bcdnum_1 // avoid redefinition
#include <unicode/src/decNumber.cpp>
#include <unicode/src/displayoptions.cpp>
#include <unicode/src/double-conversion-bignum-dtoa.cpp>
#include <unicode/src/double-conversion-bignum.cpp>
#include <unicode/src/double-conversion-cached-powers.cpp>
#include <unicode/src/double-conversion-double-to-string.cpp>
#include <unicode/src/double-conversion-fast-dtoa.cpp>
#include <unicode/src/double-conversion-string-to-double.cpp>
#include <unicode/src/double-conversion-strtod.cpp>
#define gNumberElementsTag gNumberElementsTag_1 // avoid redefinition
#define newUnicodeStringArray newUnicodeStringArray_1 // avoid redefinition
#include <unicode/src/dtfmtsym.cpp>
#define gCalendarTag gCalendarTag_1 // avoid redefinition
#define gGregorianTag gGregorianTag_1 // avoid redefinition
#include <unicode/src/dtitvfmt.cpp>
#define gCalendarTag_1 gCalendarTag_2 // avoid redefinition
#define gGregorianTag_1 gGregorianTag_2 // avoid redefinition
#include <unicode/src/dtitvinf.cpp>
#undef LOW_J // from src
#define initOnce_1 initOnce_2 // avoid redefinition
#include <unicode/src/dtptngen.cpp>
#include <unicode/src/dtrule.cpp>
#include <unicode/src/erarules.cpp>
#include <unicode/src/esctrn.cpp>
#define gSystemDefaultCenturyStart_2 gSystemDefaultCenturyStart_3 // avoid redefinition
#define gSystemDefaultCenturyStartYear_2 gSystemDefaultCenturyStartYear_3 // avoid redefinition
#define gSystemDefaultCenturyInit_2 gSystemDefaultCenturyInit_3 // avoid redefinition
#define initializeSystemDefaultCentury_2 initializeSystemDefaultCentury_3 // avoid redefinition
#include <unicode/src/ethpccal.cpp>
#include <unicode/src/fmtable_cnv.cpp>
#include <unicode/src/fmtable.cpp>
#include <unicode/src/format.cpp>
#include <unicode/src/formatted_string_builder.cpp>
#include <unicode/src/formattedval_iterimpl.cpp>
#include <unicode/src/formattedval_sbimpl.cpp>
#include <unicode/src/formattedvalue.cpp>
#include <unicode/src/fphdlimp.cpp>
#include <unicode/src/fpositer.cpp>
#undef AMPERSAND // from src
#include <unicode/src/funcrepl.cpp>
#include <unicode/src/gender.cpp>
#define gSystemDefaultCenturyStart_3 gSystemDefaultCenturyStart_4 // avoid redefinition
#define gSystemDefaultCenturyStartYear_3 gSystemDefaultCenturyStartYear_4 // avoid redefinition
#define gSystemDefaultCenturyInit_3 gSystemDefaultCenturyInit_4 // avoid redefinition
#define initializeSystemDefaultCentury_3 initializeSystemDefaultCentury_4 // avoid redefinition
#include <unicode/src/gregocal.cpp>
#include <unicode/src/gregoimp.cpp>
#define gCache gCache_1 // avoid redefinition
#define gSystemDefaultCenturyStart_4 gSystemDefaultCenturyStart_5 // avoid redefinition
#define gSystemDefaultCenturyStartYear_4 gSystemDefaultCenturyStartYear_5 // avoid redefinition
#define gSystemDefaultCenturyInit_4 gSystemDefaultCenturyInit_5 // avoid redefinition
#define initializeSystemDefaultCentury_4 initializeSystemDefaultCentury_5 // avoid redefinition
#include <unicode/src/hebrwcal.cpp>
#define LIMITS_1 LIMITS_2 // avoid redefinition
#define gSystemDefaultCenturyStart_5 gSystemDefaultCenturyStart_6 // avoid redefinition
#define gSystemDefaultCenturyStartYear_5 gSystemDefaultCenturyStartYear_6 // avoid redefinition
#define gSystemDefaultCenturyInit_5 gSystemDefaultCenturyInit_6 // avoid redefinition
#define initializeSystemDefaultCentury_5 initializeSystemDefaultCentury_6 // avoid redefinition
#include <unicode/src/indiancal.cpp>
#include <unicode/src/inputext.cpp>
#define LIMITS_2 LIMITS_3 // avoid redefinition
#define gSystemDefaultCenturyStart_6 gSystemDefaultCenturyStart_7 // avoid redefinition
#define gSystemDefaultCenturyStartYear_6 gSystemDefaultCenturyStartYear_7 // avoid redefinition
#define gSystemDefaultCenturyInit_6 gSystemDefaultCenturyInit_7 // avoid redefinition
#define initializeSystemDefaultCentury_6 initializeSystemDefaultCentury_7 // avoid redefinition
#include <unicode/src/islamcal.cpp>
#include <unicode/src/iso8601cal.cpp>
#define kGregorianEpoch kGregorianEpoch_1 // avoid redefinition
#include <unicode/src/japancal.cpp>
#include <unicode/src/listformatter.cpp>
#undef cache // undef macro in <unicode/src/uresbund.cpp>, because `MeasureFormat::cache` cannot be renamed, later re-define in <unicode/src/ucol_res.cpp>
#include <unicode/src/measfmt.cpp>
#include <unicode/src/measunit_extra.cpp>
#include <unicode/src/measunit.cpp>
#include <unicode/src/measure.cpp>
#include <unicode/src/messageformat2_arguments.cpp>
#undef CR // from src
#undef LF // from src
#undef COLON // from src
#undef PLUS // from src
#undef HYPHEN // from src
#undef PERCENT // from src
#undef LESS_THAN // from src
#include <unicode/src/messageformat2_checker.cpp>
#include <unicode/src/messageformat2_data_model.cpp>
#include <unicode/src/messageformat2_errors.cpp>
#include <unicode/src/messageformat2_evaluation.cpp>
#include <unicode/src/messageformat2_formattable.cpp>
#include <unicode/src/messageformat2_formatter.cpp>
#include <unicode/src/messageformat2_function_registry.cpp>
#include <unicode/src/messageformat2_parser.cpp>
#include <unicode/src/messageformat2_serializer.cpp>
#include <unicode/src/messageformat2.cpp>
#undef LEFT_CURLY_BRACE // from src
#undef RIGHT_CURLY_BRACE // from src
#include <unicode/src/msgfmt.cpp>
#undef SPACE // from src
#define SPACE SPACE_1 // avoid redefinition
#define _set_add _set_add_1 // avoid redefinition
#include <unicode/src/name2uni.cpp>
#include <unicode/src/nfrs.cpp>
#define gColon gColon_1 // avoid redefinition
#define gSemicolon gSemicolon_1 // avoid redefinition
#include <unicode/src/nfrule.cpp>
#include <unicode/src/nfsubs.cpp>
#include <unicode/src/nortrans.cpp>
#include <unicode/src/nultrans.cpp>
#include <unicode/src/number_affixutils.cpp>
#include <unicode/src/number_asformat.cpp>
#include <unicode/src/number_capi.cpp>
#define getIndex getIndex_1 // avoid adl, later undef in <unicode/src/numfmt.cpp>
#include <unicode/src/number_compact.cpp>
#include <unicode/src/number_currencysymbols.cpp>
#undef min // from src
#include <unicode/src/number_decimalquantity.cpp>
#include <unicode/src/number_decimfmtprops.cpp>
#include <unicode/src/number_formatimpl.cpp>
namespace U_ICU_NAMESPACE { namespace number { namespace impl_1 { using namespace icu::number::impl; } } }
#define impl impl_1 // avoid adl, later undef in <unicode/src/number_fluent.cpp>
#include <unicode/src/number_fluent.cpp>
#undef impl // undef macro in <unicode/src/number_fluent.cpp>
#include <unicode/src/number_grouping.cpp>
#include <unicode/src/number_integerwidth.cpp>
#include <unicode/src/number_longnames.cpp>
#include <unicode/src/number_mapper.cpp>
#include <unicode/src/number_modifiers.cpp>
#include <unicode/src/number_multiplier.cpp>
#include <unicode/src/number_notation.cpp>
#include <unicode/src/number_output.cpp>
#include <unicode/src/number_padding.cpp>
#include <unicode/src/number_patternmodifier.cpp>
#include <unicode/src/number_patternstring.cpp>
#include <unicode/src/number_rounding.cpp>
#include <unicode/src/number_scientific.cpp>
#include <unicode/src/number_simple.cpp>
#include <unicode/src/number_skeletons.cpp>
#include <unicode/src/number_symbolswrapper.cpp>
#include <unicode/src/number_usageprefs.cpp>
#include <unicode/src/number_utils.cpp>
#define gService_2 gService_3 // avoid redefinition
#define gServiceInitOnce_1 gServiceInitOnce_2 // avoid redefinition
#undef getIndex // undef macro in <unicode/src/number_compact.cpp>, because `ParsePosition::getIndex` cannot be renamed
#define kKeyValueLenMax kKeyValueLenMax_1 // avoid redefinition
#include <unicode/src/numfmt.cpp>
#include <unicode/src/numparse_affixes.cpp>
#include <unicode/src/numparse_compositions.cpp>
#include <unicode/src/numparse_currency.cpp>
#undef COMMA // from src
#undef PERIOD // from src
#include <unicode/src/numparse_decimal.cpp>
#include <unicode/src/numparse_impl.cpp>
#include <unicode/src/numparse_parsednumber.cpp>
#include <unicode/src/numparse_scientific.cpp>
#include <unicode/src/numparse_symbols.cpp>
#include <unicode/src/numparse_validators.cpp>
#include <unicode/src/numrange_capi.cpp>
#define NFS NFS_1 // avoid redefinition
#define LNF LNF_1 // avoid redefinition
#define UNF UNF_1 // avoid redefinition
namespace U_ICU_NAMESPACE { namespace number { namespace impl_2 = impl; } } // create alias
#define impl impl_2 // avoid adl, later undef in <unicode/src/scientificnumberformatter.cpp> 
#include <unicode/src/numrange_fluent.cpp>
#include <unicode/src/numrange_impl.cpp>
#define gNumberElements gNumberElements_1 // avoid redefinition
#define gLatn gLatn_1 // avoid redefinition
#include <unicode/src/numsys.cpp>
#include <unicode/src/olsontz.cpp>
#define gSystemDefaultCenturyStart_7 gSystemDefaultCenturyStart_8 // avoid redefinition
#define gSystemDefaultCenturyStartYear_7 gSystemDefaultCenturyStartYear_8 // avoid redefinition
#define gSystemDefaultCenturyInit_7 gSystemDefaultCenturyInit_8 // avoid redefinition
#define initializeSystemDefaultCentury_7 initializeSystemDefaultCentury_8 // avoid redefinition
#include <unicode/src/persncal.cpp>
#include <unicode/src/pluralranges.cpp>
#include <unicode/src/plurfmt.cpp>
#undef NONE // from src
#include <unicode/src/plurrule.cpp>
#include <unicode/src/quant.cpp>
#include <unicode/src/quantityformatter.cpp>
#define SPACE_1 SPACE_2 // avoid redefinition
#undef QUOTE // from src
#undef ERROR // from src
#define COMMA COMMA_1 // avoid redefinition
#include <unicode/src/rbnf.cpp>
#include <unicode/src/rbt_data.cpp>
#undef DOT // from src
#include <unicode/src/rbt_pars.cpp>
#include <unicode/src/rbt_rule.cpp>
#include <unicode/src/rbt_set.cpp>
#include <unicode/src/rbt.cpp>
#include <unicode/src/rbtz.cpp>
#undef RBBIRPT_H // fixme: see pull request of icu, this will be re-define soon.
#define kRuleSet_digit_char kRuleSet_digit_char_1 // avoid redefinition
#define kRuleSet_rule_char kRuleSet_rule_char_1 // avoid redefinition
#define doNOP doNOP_1 // avoid redefinition
#define doRuleError doRuleError_1 // avoid redefinition
#define doExit doExit_1 // avoid redefinition
#define doDotAny doDotAny_1 // avoid redefinition
#define rbbiLastAction rbbiLastAction_1 // avoid redefinition
#define gRuleParseStateTable gRuleParseStateTable_1 // avoid redefinition
#undef RBBISCAN_H // fixme: see pull request of icu, this will be re-define soon.
#define chCR chCR_1 // avoid redefinition
#define chLF chLF_1 // avoid redefinition
#define chPound chPound_1 // avoid redefinition
#define chBackSlash chBackSlash_1 // avoid redefinition
#define chNEL chNEL_1 // avoid redefinition
#define chLS chLS_1 // avoid redefinition
#include <unicode/src/regexcmp.cpp>
#include <unicode/src/regeximp.cpp>
#include <unicode/src/regexst.cpp>
#include <unicode/src/regextxt.cpp>
#define RANGE_MARKER RANGE_MARKER_1 // avoid redefinition
#define cTypeBufMax cTypeBufMax_1 // avoid redefinition
#include <unicode/src/region.cpp>
#include <unicode/src/reldatefmt.cpp>
#include <unicode/src/reldtfmt.cpp>
#undef BACKSLASH // from src
#define BACKSLASH BACKSLASH_1 // avoid redefinition
#include <unicode/src/rematch.cpp>
#include <unicode/src/remtrans.cpp>
#include <unicode/src/repattrn.cpp>
#include <unicode/src/rulebasedcollator.cpp>
#undef impl // undef macro in <unicode/src/numrange_fluent.cpp>, because `icu::numparse::impl` cannot be renamed
#include <unicode/src/scientificnumberformatter.cpp>
#include <unicode/src/scriptset.cpp>
#include <unicode/src/scrptrun.cpp>
#include <unicode/src/search.cpp>
#undef DOT // from src
#undef BACKSLASH // from src
#undef SPACE // from src
#undef COMMA // from src
#undef HYPHEN // from src
#undef COLON // from src
#undef LOW_J // from src
#include <unicode/src/selfmt.cpp>
#include <unicode/src/sharedbreakiterator.cpp>
#include <unicode/src/simpletz.cpp>
#undef QUOTE // from src
#undef free // from src
#define QUOTE QUOTE_1 // avoid redefinition
#include <unicode/src/smpdtfmt.cpp>
#include <unicode/src/smpdtfst.cpp>
#include <unicode/src/sortkey.cpp>
#define gZero gZero_1 // avoid redefinition
#include <unicode/src/standardplural.cpp>
#include <unicode/src/string_segment.cpp>
#include <unicode/src/strmatch.cpp>
#include <unicode/src/strrepl.cpp>
#include <unicode/src/stsearch.cpp>
#define kGregorianEpoch_1 kGregorianEpoch_2 // avoid redefinition
#define gSystemDefaultCenturyStart_8 gSystemDefaultCenturyStart_9 // avoid redefinition
#define gSystemDefaultCenturyStartYear_8 gSystemDefaultCenturyStartYear_9 // avoid redefinition
#define gSystemDefaultCenturyInit_8 gSystemDefaultCenturyInit_9 // avoid redefinition
#define initializeSystemDefaultCentury_8 initializeSystemDefaultCentury_9 // avoid redefinition
#include <unicode/src/taiwncal.cpp>
#undef MINUS // from src
#undef PLUS // from src
#undef COLON // from src
#include <unicode/src/timezone.cpp>
#include <unicode/src/titletrn.cpp>
#include <unicode/src/tmunit.cpp>
#include <unicode/src/tmutamt.cpp>
#define gPluralCountOther gPluralCountOther_1 // avoid redefinition
#include <unicode/src/tmutfmt.cpp>
#include <unicode/src/tolowtrn.cpp>
#include <unicode/src/toupptrn.cpp>
#define TARGET_SEP TARGET_SEP_1 // avoid redefinition
#define ID_DELIM ID_DELIM_1 // avoid redefinition
#define VARIANT_SEP VARIANT_SEP_1 // avoid redefinition
#include <unicode/src/translit.cpp>
#undef LOCALE_SEP // from src
#define ANY_1 ANY_2 // avoid redefinition
#include <unicode/src/transreg.cpp>
#define LOCK LOCK_1 // avoid redefinition
#include <unicode/src/tridpars.cpp>
#undef PLUS // from src
#undef MINUS // from src
#include <unicode/src/tzfmt.cpp>
#define gLock gLock_1 // avoid redefinition
#include <unicode/src/tzgnames.cpp>
#define gZoneStrings gZoneStrings_1 // avoid redefinition
#define ZNameInfo ZNameInfo_1 // avoid redefinition
#define ZMatchInfo ZMatchInfo_1 // avoid redefinition
#include <unicode/src/tznames_impl.cpp>
#define gAccessCount gAccessCount_1 // avoid redefinition
#define sweepCache sweepCache_1 // avoid redefinition
#include <unicode/src/tznames.cpp>
#include <unicode/src/tzrule.cpp>
#include <unicode/src/tztrans.cpp>
#define defaultKeywordValues defaultKeywordValues_1 // avoid redefinition
#include <unicode/src/ucal.cpp>
#undef __UCLN_IMP_H__ // from src
#define copyright copyright_1 // avoid redefinition
#include <unicode/src/ucln_in.cpp>
#define cache cache_1 // re-define macro in <unicode/src/measfmt.cpp>, because `CollationLoader::cache_1` cannot be renamed
#define defaultKeywordValues_1 defaultKeywordValues_2 // avoid redefinition
#include <unicode/src/ucol.cpp>
#include <unicode/src/ucol_res.cpp>
#include <unicode/src/ucol_sit.cpp>
#undef NEW_ARRAY // from src
#include <unicode/src/ucoleitr.cpp>
#undef NEW_ARRAY // from src
#include <unicode/src/ucsdet.cpp>
#include <unicode/src/udat.cpp>
#include <unicode/src/udateintervalformat.cpp>
#include <unicode/src/udatpg.cpp>
#include <unicode/src/ufieldpositer.cpp>
#include <unicode/src/uitercollationiterator.cpp>
#include <unicode/src/ulistformatter.cpp>
#include <unicode/src/ulocdata.cpp>
#include <unicode/src/umsg.cpp>
#define END END_1 // avoid redefinition
#include <unicode/src/unesctrn.cpp>
#define OPEN_DELIM OPEN_DELIM_1 // avoid redefinition
#define CLOSE_DELIM CLOSE_DELIM_1 // avoid redefinition
#include <unicode/src/uni2name.cpp>
#include <unicode/src/units_complexconverter.cpp>
#include <unicode/src/units_converter.cpp>
#include <unicode/src/units_data.cpp>
#include <unicode/src/units_router.cpp>
#include <unicode/src/unum.cpp>
#include <unicode/src/unumsys.cpp>
#include <unicode/src/upluralrules.cpp>
#undef BACKSLASH // from src
#define BACKSLASH BACKSLASH_1 // avoid redefinition
#include <unicode/src/uregex.cpp>
#include <unicode/src/uregexc.cpp>
#include <unicode/src/uregion.cpp>
#include <unicode/src/usearch.cpp>
#include <unicode/src/uspoof_build.cpp>
#include <unicode/src/uspoof_conf.cpp>
#include <unicode/src/uspoof_impl.cpp>
#include <unicode/src/uspoof.cpp>
#include <unicode/src/utf16collationiterator.cpp>
#include <unicode/src/utf8collationiterator.cpp>
#include <unicode/src/utmscale.cpp>
#include <unicode/src/utrans.cpp>
#undef COLON // from src
#undef COMMA // from src
#undef days // from src
#define PLUS PLUS_1 // avoid redefinition
#define MINUS MINUS_1 // avoid redefinition
#define COLON COLON_1 // avoid redefinition
#define COMMA COMMA_2 // avoid redefinition
#define days days_1 // avoid redefinition
#include <unicode/src/vtzone.cpp>
#include <unicode/src/vzone.cpp>
#include <unicode/src/windtfmt.cpp>
#include <unicode/src/winnmfmt.cpp>
#include <unicode/src/wintzimpl.cpp>
#include <unicode/src/zonemeta.cpp>
#include <unicode/src/zrule.cpp>
#include <unicode/src/ztrans.cpp>
#include <unicode/src/locbund.cpp>
#include <unicode/src/sprintf.cpp>
#include <unicode/src/srtest.cpp>
#include <unicode/src/sscanf.cpp>
#undef UCLN_TYPE // from src
#undef __UCLN_IMP_H__ // from src
#define copyright_1 copyright_2 // avoid redefinition
#define gCleanupFunctions gCleanupFunctions_1 // avoid redefinition
#include <unicode/src/ucln_io.cpp>
#include <unicode/src/ufile.cpp>
#include <unicode/src/ufmt_cmn.cpp>
#include <unicode/src/uprintf.cpp>
#undef PERCENT // from src
#undef DIGIT_ZERO // from src
#undef DIGIT_ONE // from src
#include <unicode/src/uprntf_p.cpp>
#undef ISFLAG // from src
#undef UFMT_SIMPLE_PERCENT // from src
#undef UFMT_STRING // from src
#undef UFMT_CHAR // from src
#undef UFMT_INT // from src
#undef UFMT_UINT // from src
#undef UFMT_OCTAL // from src
#undef UFMT_HEX // from src
#undef UFMT_DOUBLE // from src
#undef UFMT_SCIENTIFIC // from src
#undef UFMT_SCIDBL // from src
#undef UFMT_COUNT // from src
#undef UFMT_POINTER // from src
#undef UFMT_SPELLOUT // from src
#undef UFMT_PERCENT // from src
#undef UFMT_UCHAR // from src
#undef UFMT_USTRING // from src
#include <unicode/src/uscanf_p.cpp>
#include <unicode/src/uscanf.cpp>
#include <unicode/src/ustdio.cpp>
#include <unicode/src/ustream.cpp>

export module icu;
