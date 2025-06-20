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

#define U_COMMON_IMPLEMENTATION
#define U_I18N_IMPLEMENTATION
#include <unicode/src/appendable.cpp>
#include <unicode/src/bmpset.cpp>
#include <unicode/src/bmpset.h>
#include <unicode/src/brkeng.cpp>
#include <unicode/src/brkeng.h>
#include <unicode/src/brkiter.cpp>
#include <unicode/src/bytesinkutil.cpp>
#include <unicode/src/bytesinkutil.h>
#include <unicode/src/bytestream.cpp>
#include <unicode/src/bytestrie.cpp>
#include <unicode/src/bytestriebuilder.cpp>
#include <unicode/src/bytestrieiterator.cpp>
#include <unicode/src/caniter.cpp>
#include <unicode/src/capi_helper.h>
#include <unicode/src/characterproperties.cpp>
#include <unicode/src/chariter.cpp>
#include <unicode/src/charstr.cpp>
#include <unicode/src/charstr.h>
#include <unicode/src/charstrmap.h>
#include <unicode/src/cmemory.cpp>
#include <unicode/src/cmemory.h>
#include <unicode/src/cpputils.h>
#include <unicode/src/cstr.cpp>
#include <unicode/src/cstr.h>
#include <unicode/src/cstring.cpp>
#include <unicode/src/cstring.h>
#include <unicode/src/cwchar.cpp>
#include <unicode/src/cwchar.h>
#include <unicode/src/dictbe.cpp>
#include <unicode/src/dictbe.h>
#include <unicode/src/dictionarydata.cpp>
#include <unicode/src/dictionarydata.h>
#include <unicode/src/dtintrv.cpp>
#include <unicode/src/edits.cpp>
#include <unicode/src/emojiprops.cpp>
#include <unicode/src/emojiprops.h>
#include <unicode/src/errorcode.cpp>
#include <unicode/src/filteredbrk.cpp>
#include <unicode/src/filterednormalizer2.cpp>
#include <unicode/src/hash.h>
#include <unicode/src/icudataver.cpp>
#include <unicode/src/icuplug.cpp>
#include <unicode/src/icuplugimp.h>
#include <unicode/src/loadednormalizer2impl.cpp>
#include <unicode/src/localebuilder.cpp>
#include <unicode/src/localefallback_data.h>
#include <unicode/src/localematcher.cpp>
#include <unicode/src/localeprioritylist.cpp>
#include <unicode/src/localeprioritylist.h>
#include <unicode/src/localsvc.h>
#include <unicode/src/locavailable.cpp>
#include <unicode/src/locbased.cpp>
#include <unicode/src/locbased.h>
#include <unicode/src/locdispnames.cpp>
#include <unicode/src/locdistance.cpp>
#include <unicode/src/locdistance.h>
#include <unicode/src/locdspnm.cpp>
#include <unicode/src/locid.cpp>
#include <unicode/src/loclikely.cpp>
#define gInitOnce gInitOnce$1 // avoid redefinition
#define cleanup cleanup$1 // avoid redifinition, later cancelled in <unicode/src/umutex.cpp>
#include <unicode/src/loclikelysubtags.cpp>
#include <unicode/src/loclikelysubtags.h>
#include <unicode/src/locmap.cpp>
#include <unicode/src/locmap.h>
#include <unicode/src/locresdata.cpp>
#include <unicode/src/locutil.cpp>
#include <unicode/src/locutil.h>
#include <unicode/src/lsr.cpp>
#include <unicode/src/lsr.h>
#include <unicode/src/lstmbe.cpp>
#include <unicode/src/lstmbe.h>
#include <unicode/src/messageimpl.h>
#include <unicode/src/messagepattern.cpp>
#include <unicode/src/mlbe.cpp>
#include <unicode/src/mlbe.h>
#include <unicode/src/msvcres.h>
#include <unicode/src/mutex.h>
#include <unicode/src/norm2_nfc_data.h>
#include <unicode/src/norm2allmodes.h>
#include <unicode/src/normalizer2.cpp>
#include <unicode/src/normalizer2impl.cpp>
#include <unicode/src/normalizer2impl.h>
#include <unicode/src/normlzr.cpp>
#include <unicode/src/parsepos.cpp>
#include <unicode/src/patternprops.cpp>
#include <unicode/src/patternprops.h>
#include <unicode/src/pluralmap.cpp>
#include <unicode/src/pluralmap.h>
#include <unicode/src/propname_data.h>
#include <unicode/src/propname.cpp>
#include <unicode/src/propname.h>
#include <unicode/src/propsvec.cpp>
#include <unicode/src/propsvec.h>
#include <unicode/src/punycode.cpp>
#include <unicode/src/punycode.h>
#include <unicode/src/putil.cpp>
#include <unicode/src/putilimp.h>
#include <unicode/src/rbbi_cache.cpp>
#include <unicode/src/rbbi_cache.h>
#include <unicode/src/rbbi.cpp>
#include <unicode/src/rbbidata.cpp>
#include <unicode/src/rbbidata.h>
#include <unicode/src/rbbinode.cpp>
#include <unicode/src/rbbinode.h>
#include <unicode/src/rbbirb.cpp>
#include <unicode/src/rbbirb.h>
#include <unicode/src/rbbirpt.h>
#include <unicode/src/rbbiscan.cpp>
#include <unicode/src/rbbiscan.h>
#include <unicode/src/rbbisetb.cpp>
#include <unicode/src/rbbisetb.h>
#include <unicode/src/rbbistbl.cpp>
#include <unicode/src/rbbitblb.cpp>
#include <unicode/src/rbbitblb.h>
#include <unicode/src/resbund_cnv.cpp>
#include <unicode/src/resbund.cpp>
#include <unicode/src/resource.cpp>
#include <unicode/src/resource.h>
#include <unicode/src/restrace.cpp>
#include <unicode/src/restrace.h>
#include <unicode/src/ruleiter.cpp>
#include <unicode/src/ruleiter.h>
#include <unicode/src/schriter.cpp>
#include <unicode/src/serv.cpp>
#include <unicode/src/serv.h>
#include <unicode/src/servlk.cpp>
#include <unicode/src/servlkf.cpp>
#include <unicode/src/servloc.h>
#include <unicode/src/servls.cpp>
#include <unicode/src/servnotf.cpp>
#include <unicode/src/servnotf.h>
#include <unicode/src/servrbf.cpp>
#include <unicode/src/servslkf.cpp>
#include <unicode/src/sharedobject.cpp>
#include <unicode/src/sharedobject.h>
#include <unicode/src/simpleformatter.cpp>
#include <unicode/src/sprpimpl.h>
#include <unicode/src/static_unicode_sets.cpp>
#include <unicode/src/static_unicode_sets.h>
#include <unicode/src/stringpiece.cpp>
#include <unicode/src/stringtriebuilder.cpp>
#include <unicode/src/uarrsort.cpp>
#include <unicode/src/uarrsort.h>
#include <unicode/src/uassert.h>
#include <unicode/src/ubidi_props_data.h>
#include <unicode/src/ubidi_props.cpp>
#include <unicode/src/ubidi_props.h>
#include <unicode/src/ubidi.cpp>
#include <unicode/src/ubidiimp.h>
#include <unicode/src/ubidiln.cpp>
#include <unicode/src/ubiditransform.cpp>
#include <unicode/src/ubidiwrt.cpp>
#include <unicode/src/ubrk.cpp>
#include <unicode/src/ubrkimpl.h>
#include <unicode/src/ucase_props_data.h>
#define _enumPropertyStartsRange _enumPropertyStartsRange$1 // avoid redefinition
#include <unicode/src/ucase.cpp>
#include <unicode/src/ucase.h>
#include <unicode/src/ucasemap_imp.h>
#include <unicode/src/ucasemap_titlecase_brkiter.cpp>
#include <unicode/src/ucasemap.cpp>
#include <unicode/src/ucat.cpp>
#define dataVersion dataVersion$1 // This #define is later #undef in <unicode/src/usprep.cpp>, because <unicode/src/usprep.cpp> needs `dataVersion` in both file.
#include <unicode/src/uchar_props_data.h>
#define _enumPropertyStartsRange$1 _enumPropertyStartsRange$2 // avoid redefinition
#include <unicode/src/uchar.cpp>
#include <unicode/src/ucharstrie.cpp>
#define compareElementStrings compareElementStrings$1 // avoid redefinition
#include <unicode/src/ucharstriebuilder.cpp>
#include <unicode/src/ucharstrieiterator.cpp>
#include <unicode/src/uchriter.cpp>
#include <unicode/src/ucln_cmn.cpp>
#include <unicode/src/ucln_cmn.h>
// #include <unicode/src/ucln_imp.h>: this file can only be included once
#include <unicode/src/ucln.h>
#include <unicode/src/ucmndata.cpp>
#include <unicode/src/ucmndata.h>
#undef DATA_TYPE // from src
#define DATA_TYPE DATA_TYPE$1 // avoid redefinition
#include <unicode/src/ucnv_bld.cpp>
#include <unicode/src/ucnv_bld.h>
#include <unicode/src/ucnv_cb.cpp>
#include <unicode/src/ucnv_cnv.cpp>
#include <unicode/src/ucnv_cnv.h>
#include <unicode/src/ucnv_ct.cpp>
#include <unicode/src/ucnv_err.cpp>
#include <unicode/src/ucnv_ext.cpp>
#include <unicode/src/ucnv_ext.h>
#include <unicode/src/ucnv_imp.h>
#define DATA_TYPE$1 DATA_TYPE$2 // avoid redefinition
#include <unicode/src/ucnv_io.cpp>
#include <unicode/src/ucnv_io.h>
#include <unicode/src/ucnv_lmb.cpp>
#include <unicode/src/ucnv_set.cpp>
#include <unicode/src/ucnv_u16.cpp>
#define UCNV_NEED_TO_WRITE_BOM UCNV_NEED_TO_WRITE_BOM$1 // avoid redefinition
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
#define ZERO ZERO$1 // avoid redefinition
#include <unicode/src/ucnvisci.cpp>
#include <unicode/src/ucnvlat1.cpp>
#include <unicode/src/ucnvmbcs.cpp>
#include <unicode/src/ucnvmbcs.h>
#include <unicode/src/ucnvscsu.cpp>
#include <unicode/src/ucnvsel.cpp>
#include <unicode/src/ucol_data.h>
#include <unicode/src/ucol_swp.cpp>
#include <unicode/src/ucol_swp.h>
#include <unicode/src/ucptrie_impl.h>
#include <unicode/src/ucptrie.cpp>
#include <unicode/src/ucurr.cpp>
#include <unicode/src/ucurrimp.h>
#include <unicode/src/udata.cpp>
#include <unicode/src/udatamem.cpp>
#include <unicode/src/udatamem.h>
#include <unicode/src/udataswp.cpp>
#include <unicode/src/udataswp.h>
#include <unicode/src/uelement.h>
#include <unicode/src/uenum.cpp>
#include <unicode/src/uenumimp.h>
#include <unicode/src/uhash_us.cpp>
#include <unicode/src/uhash.cpp>
#include <unicode/src/uhash.h>
#include <unicode/src/uidna.cpp>
#include <unicode/src/uinit.cpp>
#include <unicode/src/uinvchar.cpp>
#include <unicode/src/uinvchar.h>
#include <unicode/src/uiter.cpp>
#include <unicode/src/ulayout_props.h>
#include <unicode/src/ulist.cpp>
#include <unicode/src/ulist.h>
#include <unicode/src/uloc_keytype.cpp>
#include <unicode/src/uloc_tag.cpp>
#define UPRV_ISDIGIT UPRV_ISDIGIT$1  // avoid redefinition
#define UPRV_ISALPHANUM UPRV_ISALPHANUM$1  // avoid redefinition
#undef MINLEN // from src
#include <unicode/src/uloc.cpp>
#include <unicode/src/ulocale.cpp>
#undef EXTERNAL // from src
#undef INTERNAL // from src
#undef CONST_INTERNAL // from src
#include <unicode/src/ulocbuilder.cpp>
#include <unicode/src/ulocimp.h>
#include <unicode/src/umapfile.cpp>
#include <unicode/src/umapfile.h>
#include <unicode/src/umath.cpp>
#define getRange getRange$1 // avoid redefinition
#include <unicode/src/umutablecptrie.cpp>
#undef cleanup // cancel macro in <unicode/src/loclikelysubtags.cpp>, because `UMutex::cleanup` cannot be renamed.
#include <unicode/src/umutex.cpp>
#include <unicode/src/umutex.h>
#include <unicode/src/unames.cpp>
#include <unicode/src/unifiedcache.cpp>
#include <unicode/src/unifiedcache.h>
#include <unicode/src/unifilt.cpp>
#include <unicode/src/unifunct.cpp>
#include <unicode/src/uniquecharstr.h>
#include <unicode/src/uniset_closure.cpp>
#define ASCII ASCII$1 // avoid redefinition
#include <unicode/src/uniset_props.cpp>
#define compareUnicodeString compareUnicodeString$1 // avoid redefinition
#undef _dbgct // from src
#include <unicode/src/uniset.cpp>
#include <unicode/src/unisetspan.cpp>
#include <unicode/src/unisetspan.h>
#include <unicode/src/unistr_case_locale.cpp>
#include <unicode/src/unistr_case.cpp>
#include <unicode/src/unistr_cnv.cpp>
#include <unicode/src/unistr_props.cpp>
#include <unicode/src/unistr_titlecase_brkiter.cpp>
#include <unicode/src/unistr.cpp>
#include <unicode/src/unistrappender.h>
#include <unicode/src/unorm.cpp>
#include <unicode/src/unormcmp.cpp>
#include <unicode/src/unormimp.h>
#include <unicode/src/uobject.cpp>
#include <unicode/src/uposixdefs.h>
#include <unicode/src/uprops.cpp>
#include <unicode/src/uprops.h>
#include <unicode/src/ures_cnv.cpp>
#define gCacheInitOnce gCacheInitOnce$1 // avoid redefinition
#define cache cache$1 // avoid redefinition, later cancelled in <unicode/src/measfmt.cpp>
#include <unicode/src/uresbund.cpp>
#define gEmptyString gEmptyString$1 // avoid redefinition
#define isAcceptable isAcceptable$1 // avoid redefinition
#define STACK_ROW_CAPACITY STACK_ROW_CAPACITY$1 // avoid redefinition
#include <unicode/src/uresdata.cpp>
#include <unicode/src/uresdata.h>
#include <unicode/src/uresimp.h>
#include <unicode/src/ureslocs.h>
#include <unicode/src/usc_impl.cpp>
#include <unicode/src/usc_impl.h>
#define UBIDI_RTL UBIDI_RTL$1 // avoid redefinition
#include <unicode/src/uscript_props.cpp>
#include <unicode/src/uscript.cpp>
#include <unicode/src/uset_imp.h>
#include <unicode/src/uset_props.cpp>
#include <unicode/src/uset.cpp>
#include <unicode/src/usetiter.cpp>
#include <unicode/src/ushape.cpp>
#define SHARED_DATA_HASHTABLE SHARED_DATA_HASHTABLE$1 // avoid redefinition
#define hashEntry hashEntry$1 // avoid redefinition
#define compareEntries compareEntries$1 // avoid redefinition
#define createCache createCache$1 // avoid redefinition
#define initCache initCache$1 // avoid redefinition
#undef dataVersion // see <unicode/src/uchar_props_data.h>
#include <unicode/src/usprep.cpp>
#include <unicode/src/ustack.cpp>
#include <unicode/src/ustr_cnv.cpp>
#include <unicode/src/ustr_cnv.h>
#include <unicode/src/ustr_imp.h>
#include <unicode/src/ustr_titlecase_brkiter.cpp>
#include <unicode/src/ustr_wcs.cpp>
#include <unicode/src/ustrcase_locale.cpp>
#define CmpEquivLevel CmpEquivLevel$1 // avoid redefinition
#include <unicode/src/ustrcase.cpp>
#include <unicode/src/ustrenum.cpp>
#include <unicode/src/ustrenum.h>
#include <unicode/src/ustrfmt.cpp>
#include <unicode/src/ustrfmt.h>
#include <unicode/src/ustring.cpp>
#include <unicode/src/ustrtrns.cpp>
#define gEmptyString$1 gEmptyString$2 // avoid redefinition
#include <unicode/src/utext.cpp>
#include <unicode/src/utf_impl.cpp>
#include <unicode/src/util_props.cpp>
#undef BACKSLASH // from src
#undef SPACE // from src
#define DIGITS DIGITS$1 // from src
#include <unicode/src/util.cpp>
#include <unicode/src/util.h>
#include <unicode/src/utrace.cpp>
#include <unicode/src/utracimp.h>
#define ASCII_LIMIT ASCII_LIMIT$1 // avoid redefinition
#include <unicode/src/utrie_swap.cpp>
#include <unicode/src/utrie.cpp>
#include <unicode/src/utrie.h>
#define writeBlock writeBlock$1 // avoid redefinition
#define equal_uint32 equal_uint32$1 // avoid redefinition
#include <unicode/src/utrie2_builder.cpp>
#include <unicode/src/utrie2_impl.h>
#define enumSameValue enumSameValue$1 // avoid redefinition
#include <unicode/src/utrie2.cpp>
#include <unicode/src/utrie2.h>
#include <unicode/src/uts46.cpp>
#include <unicode/src/utypeinfo.h>
#include <unicode/src/utypes.cpp>
#undef HINT_KEY_POINTER // from src
#include <unicode/src/uvector.cpp>
#include <unicode/src/uvector.h>
#include <unicode/src/uvectr32.cpp>
#include <unicode/src/uvectr32.h>
#include <unicode/src/uvectr64.cpp>
#include <unicode/src/uvectr64.h>
#include <unicode/src/wintz.cpp>
#include <unicode/src/wintz.h>
#undef BASE // from src
#include <unicode/src/alphaindex.cpp>
#define ANY ANY$1 // avoid redefinition
#include <unicode/src/anytrans.cpp>
#include <unicode/src/anytrans.h>
#include <unicode/src/astro.cpp>
#include <unicode/src/astro.h>
#include <unicode/src/basictz.cpp>
#include <unicode/src/bocsu.cpp>
#include <unicode/src/bocsu.h>
#include <unicode/src/brktrans.cpp>
#include <unicode/src/brktrans.h>
#include <unicode/src/buddhcal.cpp>
#include <unicode/src/buddhcal.h>
#define gService gService$1 // avoid redefinition
#include <unicode/src/calendar.cpp>
#include <unicode/src/casetrn.cpp>
#include <unicode/src/casetrn.h>
#include <unicode/src/cecal.cpp>
#define LIMITS LIMITS$1 // avoid redefinition
#include <unicode/src/cecal.h>
#define gSystemDefaultCenturyStart gSystemDefaultCenturyStart$1 // avoid redefinition
#define gSystemDefaultCenturyStartYear gSystemDefaultCenturyStartYear$1 // avoid redefinition
#define gSystemDefaultCenturyInit gSystemDefaultCenturyInit$1 // avoid redefinition
#define initializeSystemDefaultCentury initializeSystemDefaultCentury$1 // avoid redefinition
#include <unicode/src/chnsecal.cpp>
#include <unicode/src/chnsecal.h>
#undef MINUS // from src
#include <unicode/src/choicfmt.cpp>
#undef isDigit // from src
#include <unicode/src/coleitr.cpp>
#define gService$1 gService$2 // avoid redefinition
#define gServiceInitOnce gServiceInitOnce$1 // avoid redefinition
#define availableLocaleList availableLocaleList$1 // avoid redefinition
#define availableLocaleListCount availableLocaleListCount$1 // avoid redefinition
#define initService initService$1 // avoid redefinition
#define getService getService$1 // avoid redefinition
#define hasService hasService$1 // avoid redefinition
#include <unicode/src/coll.cpp>
#include <unicode/src/collation.cpp>
#include <unicode/src/collation.h>
#include <unicode/src/collationbuilder.cpp>
#include <unicode/src/collationbuilder.h>
#include <unicode/src/collationcompare.cpp>
#include <unicode/src/collationcompare.h>
#include <unicode/src/collationdata.cpp>
#include <unicode/src/collationdata.h>
#include <unicode/src/collationdatabuilder.cpp>
#include <unicode/src/collationdatabuilder.h>
#include <unicode/src/collationdatareader.cpp>
#include <unicode/src/collationdatareader.h>
#include <unicode/src/collationdatawriter.cpp>
#include <unicode/src/collationdatawriter.h>
#include <unicode/src/collationfastlatin.cpp>
#include <unicode/src/collationfastlatin.h>
#include <unicode/src/collationfastlatinbuilder.cpp>
#include <unicode/src/collationfastlatinbuilder.h>
#include <unicode/src/collationfcd.cpp>
#include <unicode/src/collationfcd.h>
#include <unicode/src/collationiterator.cpp>
#include <unicode/src/collationiterator.h>
#include <unicode/src/collationkeys.cpp>
#include <unicode/src/collationkeys.h>
#include <unicode/src/collationroot.cpp>
#include <unicode/src/collationroot.h>
#include <unicode/src/collationrootelements.cpp>
#include <unicode/src/collationrootelements.h>
#include <unicode/src/collationruleparser.cpp>
#include <unicode/src/collationruleparser.h>
#include <unicode/src/collationsets.cpp>
#include <unicode/src/collationsets.h>
#include <unicode/src/collationsettings.cpp>
#include <unicode/src/collationsettings.h>
#include <unicode/src/collationtailoring.cpp>
#include <unicode/src/collationtailoring.h>
#include <unicode/src/collationweights.cpp>
#include <unicode/src/collationweights.h>
#include <unicode/src/collunsafe.h>
#undef DEFAULT_CAPACITY // from src
#undef SINGLE_QUOTE // from src
#undef SLASH // from src
#undef COMMA // from src
#undef HYPHEN // from src
#undef TILDE // from src
#include <unicode/src/compactdecimalformat.cpp>
#define gSystemDefaultCenturyStart$1 gSystemDefaultCenturyStart$2 // avoid redefinition
#define gSystemDefaultCenturyStartYear$1 gSystemDefaultCenturyStartYear$2 // avoid redefinition
#define gSystemDefaultCenturyInit$1 gSystemDefaultCenturyInit$2 // avoid redefinition
#define initializeSystemDefaultCentury$1 initializeSystemDefaultCentury$2 // avoid redefinition
#include <unicode/src/coptccal.cpp>
#include <unicode/src/coptccal.h>
#include <unicode/src/cpdtrans.cpp>
#include <unicode/src/cpdtrans.h>
#include <unicode/src/csdetect.cpp>
#include <unicode/src/csdetect.h>
#include <unicode/src/csmatch.cpp>
#include <unicode/src/csmatch.h>
#include <unicode/src/csr2022.cpp>
#include <unicode/src/csr2022.h>
#include <unicode/src/csrecog.cpp>
#include <unicode/src/csrecog.h>
#include <unicode/src/csrmbcs.cpp>
#include <unicode/src/csrmbcs.h>
#include <unicode/src/csrsbcs.cpp>
#include <unicode/src/csrsbcs.h>
#include <unicode/src/csrucode.cpp>
#include <unicode/src/csrucode.h>
#include <unicode/src/csrutf8.cpp>
#include <unicode/src/csrutf8.h>
#include <unicode/src/curramt.cpp>
#include <unicode/src/currfmt.cpp>
#include <unicode/src/currfmt.h>
#include <unicode/src/currpinf.cpp>
#include <unicode/src/currunit.cpp>
#define gWinterSolsticeCache gWinterSolsticeCache$1 // avoid redefinition
#define gNewYearCache gNewYearCache$1 // avoid redefinition
#define gAstronomerTimeZone gAstronomerTimeZone$1 // avoid redefinition
#define gAstronomerTimeZoneInitOnce gAstronomerTimeZoneInitOnce$1 // avoid redefinition
#define initOnce initOnce$1 // avoid redefinition
#include <unicode/src/dangical.cpp>
#include <unicode/src/dangical.h>
#include <unicode/src/datefmt.cpp>
#include <unicode/src/dayperiodrules.cpp>
#include <unicode/src/dayperiodrules.h>
#include <unicode/src/dcfmtsym.cpp>
// #include <unicode/src/decContext.cpp>: fixme
// #include <unicode/src/decContext.h>: fixme
// #include <unicode/src/decimfmt.cpp>: fixme
// #include <unicode/src/decNumber.cpp>: fixme
// #include <unicode/src/decNumber.h>: fixme
// #include <unicode/src/decNumberLocal.h>: fixme
#include <unicode/src/displayoptions.cpp>
#include <unicode/src/double-conversion-bignum-dtoa.cpp>
#include <unicode/src/double-conversion-bignum-dtoa.h>
#include <unicode/src/double-conversion-bignum.cpp>
#include <unicode/src/double-conversion-bignum.h>
#include <unicode/src/double-conversion-cached-powers.cpp>
#include <unicode/src/double-conversion-cached-powers.h>
#include <unicode/src/double-conversion-diy-fp.h>
#include <unicode/src/double-conversion-double-to-string.cpp>
#include <unicode/src/double-conversion-double-to-string.h>
#include <unicode/src/double-conversion-fast-dtoa.cpp>
#include <unicode/src/double-conversion-fast-dtoa.h>
#include <unicode/src/double-conversion-ieee.h>
#include <unicode/src/double-conversion-string-to-double.cpp>
#include <unicode/src/double-conversion-string-to-double.h>
#include <unicode/src/double-conversion-strtod.cpp>
#include <unicode/src/double-conversion-strtod.h>
#include <unicode/src/double-conversion-utils.h>
#include <unicode/src/double-conversion.h>
#include <unicode/src/dt_impl.h>
#define gNumberElementsTag gNumberElementsTag$1 // avoid redefinition
#define newUnicodeStringArray newUnicodeStringArray$1 // avoid redefinition
#include <unicode/src/dtfmtsym.cpp>
#include <unicode/src/dtitv_impl.h>
#define gCalendarTag gCalendarTag$1 // avoid redefinition
#define gGregorianTag gGregorianTag$1 // avoid redefinition
#include <unicode/src/dtitvfmt.cpp>
#define gCalendarTag$1 gCalendarTag$2 // avoid redefinition
#define gGregorianTag$1 gGregorianTag$2 // avoid redefinition
#include <unicode/src/dtitvinf.cpp>
#undef LOW_J // from src
#include <unicode/src/dtptngen_impl.h>
#define initOnce$1 initOnce$2 // avoid redefinition
#include <unicode/src/dtptngen.cpp>
#include <unicode/src/dtrule.cpp>
#include <unicode/src/erarules.cpp>
#include <unicode/src/erarules.h>
#include <unicode/src/esctrn.cpp>
#include <unicode/src/esctrn.h>
#define gSystemDefaultCenturyStart$2 gSystemDefaultCenturyStart$3 // avoid redefinition
#define gSystemDefaultCenturyStartYear$2 gSystemDefaultCenturyStartYear$3 // avoid redefinition
#define gSystemDefaultCenturyInit$2 gSystemDefaultCenturyInit$3 // avoid redefinition
#define initializeSystemDefaultCentury$2 initializeSystemDefaultCentury$3 // avoid redefinition
#include <unicode/src/ethpccal.cpp>
#include <unicode/src/ethpccal.h>
#include <unicode/src/fmtable_cnv.cpp>
#include <unicode/src/fmtable.cpp>
#include <unicode/src/fmtableimp.h>
#include <unicode/src/format.cpp>
#include <unicode/src/formatted_string_builder.cpp>
#include <unicode/src/formatted_string_builder.h>
#include <unicode/src/formattedval_impl.h>
#include <unicode/src/formattedval_iterimpl.cpp>
#include <unicode/src/formattedval_sbimpl.cpp>
#include <unicode/src/formattedvalue.cpp>
#include <unicode/src/fphdlimp.cpp>
#include <unicode/src/fphdlimp.h>
#include <unicode/src/fpositer.cpp>
#undef AMPERSAND // from src
#include <unicode/src/funcrepl.cpp>
#include <unicode/src/funcrepl.h>
#include <unicode/src/gender.cpp>
#define gSystemDefaultCenturyStart$3 gSystemDefaultCenturyStart$4 // avoid redefinition
#define gSystemDefaultCenturyStartYear$3 gSystemDefaultCenturyStartYear$4 // avoid redefinition
#define gSystemDefaultCenturyInit$3 gSystemDefaultCenturyInit$4 // avoid redefinition
#define initializeSystemDefaultCentury$3 initializeSystemDefaultCentury$4 // avoid redefinition
#include <unicode/src/gregocal.cpp>
#include <unicode/src/gregoimp.cpp>
#include <unicode/src/gregoimp.h>
#define gCache gCache$1 // avoid redefinition
#define gSystemDefaultCenturyStart$4 gSystemDefaultCenturyStart$5 // avoid redefinition
#define gSystemDefaultCenturyStartYear$4 gSystemDefaultCenturyStartYear$5 // avoid redefinition
#define gSystemDefaultCenturyInit$4 gSystemDefaultCenturyInit$5 // avoid redefinition
#define initializeSystemDefaultCentury$4 initializeSystemDefaultCentury$5 // avoid redefinition
#include <unicode/src/hebrwcal.cpp>
#include <unicode/src/hebrwcal.h>
#define LIMITS$1 LIMITS$2 // avoid redefinition
#define gSystemDefaultCenturyStart$5 gSystemDefaultCenturyStart$6 // avoid redefinition
#define gSystemDefaultCenturyStartYear$5 gSystemDefaultCenturyStartYear$6 // avoid redefinition
#define gSystemDefaultCenturyInit$5 gSystemDefaultCenturyInit$6 // avoid redefinition
#define initializeSystemDefaultCentury$5 initializeSystemDefaultCentury$6 // avoid redefinition
#include <unicode/src/indiancal.cpp>
#include <unicode/src/indiancal.h>
#include <unicode/src/inputext.cpp>
#include <unicode/src/inputext.h>
#define LIMITS$2 LIMITS$3 // avoid redefinition
#define gSystemDefaultCenturyStart$6 gSystemDefaultCenturyStart$7 // avoid redefinition
#define gSystemDefaultCenturyStartYear$6 gSystemDefaultCenturyStartYear$7 // avoid redefinition
#define gSystemDefaultCenturyInit$6 gSystemDefaultCenturyInit$7 // avoid redefinition
#define initializeSystemDefaultCentury$6 initializeSystemDefaultCentury$7 // avoid redefinition
#include <unicode/src/islamcal.cpp>
#include <unicode/src/islamcal.h>
#include <unicode/src/iso8601cal.cpp>
#include <unicode/src/iso8601cal.h>
#define kGregorianEpoch kGregorianEpoch$1 // avoid redefinition
#include <unicode/src/japancal.cpp>
#include <unicode/src/japancal.h>
#include <unicode/src/listformatter.cpp>
#undef cache // cancel macro in <unicode/src/uresbund.cpp>, because `MeasureFormat::cache` cannot be renamed, later recorvered in <unicode/src/ucol_res.cpp>
#include <unicode/src/measfmt.cpp>
#include <unicode/src/measunit_extra.cpp>
#include <unicode/src/measunit_impl.h>
#include <unicode/src/measunit.cpp>
#include <unicode/src/measure.cpp>
#include <unicode/src/messageformat2_allocation.h>
#include <unicode/src/messageformat2_arguments.cpp>
#undef CR // from src
#undef LF // from src
#undef COLON // from src
#undef PLUS // from src
#undef HYPHEN // from src
#undef PERCENT // from src
#undef LESS_THAN // from src
#include <unicode/src/messageformat2_checker.cpp>
#include <unicode/src/messageformat2_checker.h>
#include <unicode/src/messageformat2_data_model.cpp>
#include <unicode/src/messageformat2_errors.cpp>
#include <unicode/src/messageformat2_errors.h>
#include <unicode/src/messageformat2_evaluation.cpp>
#include <unicode/src/messageformat2_evaluation.h>
#include <unicode/src/messageformat2_formattable.cpp>
#include <unicode/src/messageformat2_formatter.cpp>
#include <unicode/src/messageformat2_function_registry_internal.h>
#include <unicode/src/messageformat2_function_registry.cpp>
#include <unicode/src/messageformat2_macros.h>
#include <unicode/src/messageformat2_parser.cpp>
#include <unicode/src/messageformat2_parser.h>
#include <unicode/src/messageformat2_serializer.cpp>
#include <unicode/src/messageformat2_serializer.h>
#include <unicode/src/messageformat2.cpp>
#include <unicode/src/msgfmt_impl.h>
#undef LEFT_CURLY_BRACE // from src
#undef RIGHT_CURLY_BRACE // from src
#include <unicode/src/msgfmt.cpp>
#undef SPACE // from src
#define SPACE SPACE$1 // avoid redefinition
#define _set_add _set_add$1 // avoid redefinition
#include <unicode/src/name2uni.cpp>
#include <unicode/src/name2uni.h>
#include <unicode/src/nfrlist.h>
#include <unicode/src/nfrs.cpp>
#include <unicode/src/nfrs.h>
#define gColon gColon$1 // avoid redefinition
#define gSemicolon gSemicolon$1 // avoid redefinition
#include <unicode/src/nfrule.cpp>
#include <unicode/src/nfrule.h>
#include <unicode/src/nfsubs.cpp>
#include <unicode/src/nfsubs.h>
#include <unicode/src/nortrans.cpp>
#include <unicode/src/nortrans.h>
#include <unicode/src/nultrans.cpp>
#include <unicode/src/nultrans.h>
#include <unicode/src/number_affixutils.cpp>
#include <unicode/src/number_affixutils.h>
#include <unicode/src/number_asformat.cpp>
#include <unicode/src/number_asformat.h>
#include <unicode/src/number_capi.cpp>
#define getIndex getIndex$1 // avoid adl, later cancelled in <unicode/src/numfmt.cpp>
#include <unicode/src/number_compact.cpp>
#include <unicode/src/number_compact.h>
#include <unicode/src/number_currencysymbols.cpp>
#include <unicode/src/number_currencysymbols.h>
#undef min // from src
#include <unicode/src/number_decimalquantity.cpp>
#include <unicode/src/number_decimalquantity.h>
#include <unicode/src/number_decimfmtprops.cpp>
#include <unicode/src/number_decimfmtprops.h>
#include <unicode/src/number_decnum.h>
#include <unicode/src/number_fluent.cpp>
#include <unicode/src/number_formatimpl.cpp>
#include <unicode/src/number_formatimpl.h>
#include <unicode/src/number_grouping.cpp>
#include <unicode/src/number_integerwidth.cpp>
#include <unicode/src/number_longnames.cpp>
#include <unicode/src/number_longnames.h>
#include <unicode/src/number_mapper.cpp>
#include <unicode/src/number_mapper.h>
#include <unicode/src/number_microprops.h>
#include <unicode/src/number_modifiers.cpp>
#include <unicode/src/number_modifiers.h>
#include <unicode/src/number_multiplier.cpp>
#include <unicode/src/number_multiplier.h>
#include <unicode/src/number_notation.cpp>
#include <unicode/src/number_output.cpp>
#include <unicode/src/number_padding.cpp>
#include <unicode/src/number_patternmodifier.cpp>
#include <unicode/src/number_patternmodifier.h>
#include <unicode/src/number_patternstring.cpp>
#include <unicode/src/number_patternstring.h>
#include <unicode/src/number_rounding.cpp>
#include <unicode/src/number_roundingutils.h>
#include <unicode/src/number_scientific.cpp>
#include <unicode/src/number_scientific.h>
#include <unicode/src/number_simple.cpp>
// #include <unicode/src/number_skeletons.cpp>: fixme
#include <unicode/src/number_skeletons.h>
#include <unicode/src/number_symbolswrapper.cpp>
#include <unicode/src/number_types.h>
#include <unicode/src/number_usageprefs.cpp>
#include <unicode/src/number_usageprefs.h>
#include <unicode/src/number_utils.cpp>
#include <unicode/src/number_utils.h>
#include <unicode/src/number_utypes.h>
#define gService$2 gService$3 // avoid redefinition
#define gServiceInitOnce$1 gServiceInitOnce$2 // avoid redefinition
#undef getIndex // cancel macro in <unicode/src/number_compact.cpp>, because `ParsePosition::getIndex` cannot be renamed
#define kKeyValueLenMax kKeyValueLenMax$1 // avoid redefinition
#include <unicode/src/numfmt.cpp>
#include <unicode/src/numparse_affixes.cpp>
#include <unicode/src/numparse_affixes.h>
#include <unicode/src/numparse_compositions.cpp>
#include <unicode/src/numparse_compositions.h>
#include <unicode/src/numparse_currency.cpp>
#include <unicode/src/numparse_currency.h>
#undef COMMA // from src
#undef PERIOD // from src
#include <unicode/src/numparse_decimal.cpp>
#include <unicode/src/numparse_decimal.h>
#include <unicode/src/numparse_impl.cpp>
#include <unicode/src/numparse_impl.h>
#include <unicode/src/numparse_parsednumber.cpp>
#include <unicode/src/numparse_scientific.cpp>
#include <unicode/src/numparse_scientific.h>
#include <unicode/src/numparse_symbols.cpp>
#include <unicode/src/numparse_symbols.h>
#include <unicode/src/numparse_types.h>
#include <unicode/src/numparse_utils.h>
#include <unicode/src/numparse_validators.cpp>
#include <unicode/src/numparse_validators.h>
#include <unicode/src/numrange_capi.cpp>
#define NFS NFS$1 // avoid redefinition
#define LNF LNF$1 // avoid redefinition
#define UNF UNF$1 // avoid redefinition
namespace U_ICU_NAMESPACE { namespace number { namespace impl$ = impl; } } // create alias
#define impl impl$ // avoid adl, later cancelled in <unicode/src/scientificnumberformatter.cpp> 
#include <unicode/src/numrange_fluent.cpp>
#include <unicode/src/numrange_impl.cpp>
#include <unicode/src/numrange_impl.h>
#include <unicode/src/numsys_impl.h>
#define gNumberElements gNumberElements$1 // avoid redefinition
#define gLatn gLatn$1 // avoid redefinition
#include <unicode/src/numsys.cpp>
#include <unicode/src/olsontz.cpp>
#include <unicode/src/olsontz.h>
#define gSystemDefaultCenturyStart$7 gSystemDefaultCenturyStart$8 // avoid redefinition
#define gSystemDefaultCenturyStartYear$7 gSystemDefaultCenturyStartYear$8 // avoid redefinition
#define gSystemDefaultCenturyInit$7 gSystemDefaultCenturyInit$8 // avoid redefinition
#define initializeSystemDefaultCentury$7 initializeSystemDefaultCentury$8 // avoid redefinition
#include <unicode/src/persncal.cpp>
#include <unicode/src/persncal.h>
#include <unicode/src/pluralranges.cpp>
#include <unicode/src/pluralranges.h>
#include <unicode/src/plurfmt.cpp>
#include <unicode/src/plurrule_impl.h>
#undef NONE // from src
#include <unicode/src/plurrule.cpp>
#include <unicode/src/quant.cpp>
#include <unicode/src/quant.h>
#include <unicode/src/quantityformatter.cpp>
#include <unicode/src/quantityformatter.h>
#define SPACE$1 SPACE$2 // avoid redefinition
#undef QUOTE // from src
#undef ERROR // from src
#define COMMA COMMA$1 // avoid redefinition
#include <unicode/src/rbnf.cpp>
#include <unicode/src/rbt_data.cpp>
#include <unicode/src/rbt_data.h>
#undef DOT // from src
#include <unicode/src/rbt_pars.cpp>
#include <unicode/src/rbt_pars.h>
#include <unicode/src/rbt_rule.cpp>
#include <unicode/src/rbt_rule.h>
#include <unicode/src/rbt_set.cpp>
#include <unicode/src/rbt_set.h>
#include <unicode/src/rbt.cpp>
#include <unicode/src/rbt.h>
#include <unicode/src/rbtz.cpp>
#undef RBBIRPT_H // fixme: see pull request of icu, this will be recorvered soon.
#define kRuleSet_digit_char kRuleSet_digit_char$1 // avoid redefinition
#define kRuleSet_rule_char kRuleSet_rule_char$1 // avoid redefinition
#define doNOP doNOP$1 // avoid redefinition
#define doRuleError doRuleError$1 // avoid redefinition
#define doExit doExit$1 // avoid redefinition
#define doDotAny doDotAny$1 // avoid redefinition
#define rbbiLastAction rbbiLastAction$1 // avoid redefinition
#define gRuleParseStateTable gRuleParseStateTable$1 // avoid redefinition
#undef RBBISCAN_H // fixme: see pull request of icu, this will be recorvered soon.
#define chCR chCR$1 // avoid redefinition
#define chLF chLF$1 // avoid redefinition
#define chPound chPound$1 // avoid redefinition
#define chBackSlash chBackSlash$1 // avoid redefinition
#define chNEL chNEL$1 // avoid redefinition
#define chLS chLS$1 // avoid redefinition
#include <unicode/src/regexcmp.cpp>
#include <unicode/src/regexcmp.h>
#include <unicode/src/regexcst.h>
#include <unicode/src/regeximp.cpp>
#include <unicode/src/regeximp.h>
#include <unicode/src/regexst.cpp>
#include <unicode/src/regexst.h>
#include <unicode/src/regextxt.cpp>
#include <unicode/src/regextxt.h>
#include <unicode/src/region_impl.h>
#define RANGE_MARKER RANGE_MARKER$1 // avoid redefinition
#define cTypeBufMax cTypeBufMax$1 // avoid redefinition
#include <unicode/src/region.cpp>
#include <unicode/src/reldatefmt.cpp>
#include <unicode/src/reldtfmt.cpp>
#include <unicode/src/reldtfmt.h>
#undef BACKSLASH // from src
#define BACKSLASH BACKSLASH$1 // avoid redefinition
#include <unicode/src/rematch.cpp>
#include <unicode/src/remtrans.cpp>
#include <unicode/src/remtrans.h>
#include <unicode/src/repattrn.cpp>
#include <unicode/src/rulebasedcollator.cpp>
#undef impl // cancel macro in <unicode/src/numrange_fluent.cpp>, because `icu::numparse::impl` cannot be renamed
#include <unicode/src/scientificnumberformatter.cpp>
#include <unicode/src/scriptset.cpp>
#include <unicode/src/scriptset.h>
#include <unicode/src/search.cpp>
#undef DOT // from src
#undef BACKSLASH // from src
#undef SPACE // from src
#undef COMMA // from src
#undef HYPHEN // from src
#undef COLON // from src
#undef LOW_J // from src
#include <unicode/src/selfmt.cpp>
#include <unicode/src/selfmtimpl.h>
#include <unicode/src/sharedbreakiterator.cpp>
#include <unicode/src/sharedbreakiterator.h>
#include <unicode/src/sharedcalendar.h>
#include <unicode/src/shareddateformatsymbols.h>
#include <unicode/src/sharednumberformat.h>
#include <unicode/src/sharedpluralrules.h>
#include <unicode/src/simpletz.cpp>
#undef QUOTE // from src
#define QUOTE QUOTE$1 // avoid redefinition
#include <unicode/src/smpdtfmt.cpp>
#include <unicode/src/smpdtfst.cpp>
#include <unicode/src/smpdtfst.h>
#include <unicode/src/sortkey.cpp>
#define gZero gZero$1 // avoid redefinition
#include <unicode/src/standardplural.cpp>
#include <unicode/src/standardplural.h>
#include <unicode/src/string_segment.cpp>
#include <unicode/src/string_segment.h>
#include <unicode/src/strmatch.cpp>
#include <unicode/src/strmatch.h>
#include <unicode/src/strrepl.cpp>
#include <unicode/src/strrepl.h>
#include <unicode/src/stsearch.cpp>
#define kGregorianEpoch$1 kGregorianEpoch$2 // avoid redefinition
#define gSystemDefaultCenturyStart$8 gSystemDefaultCenturyStart$9 // avoid redefinition
#define gSystemDefaultCenturyStartYear$8 gSystemDefaultCenturyStartYear$9 // avoid redefinition
#define gSystemDefaultCenturyInit$8 gSystemDefaultCenturyInit$9 // avoid redefinition
#define initializeSystemDefaultCentury$8 initializeSystemDefaultCentury$9 // avoid redefinition
#include <unicode/src/taiwncal.cpp>
#include <unicode/src/taiwncal.h>
#undef MINUS // from src
#undef PLUS // from src
#undef COLON // from src
#include <unicode/src/timezone.cpp>
#include <unicode/src/titletrn.cpp>
#include <unicode/src/titletrn.h>
#include <unicode/src/tmunit.cpp>
#include <unicode/src/tmutamt.cpp>
#define gPluralCountOther gPluralCountOther$1 // avoid redefinition
#include <unicode/src/tmutfmt.cpp>
#include <unicode/src/tolowtrn.cpp>
#include <unicode/src/tolowtrn.h>
#include <unicode/src/toupptrn.cpp>
#include <unicode/src/toupptrn.h>
#define TARGET_SEP TARGET_SEP$1 // avoid redefinition
#define ID_DELIM ID_DELIM$1 // avoid redefinition
#define VARIANT_SEP VARIANT_SEP$1 // avoid redefinition
#include <unicode/src/translit.cpp>
#undef LOCALE_SEP // from src
#define ANY$1 ANY$2 // avoid redefinition
#include <unicode/src/transreg.cpp>
#include <unicode/src/transreg.h>
#define LOCK LOCK$1 // avoid redefinition
#include <unicode/src/tridpars.cpp>
#include <unicode/src/tridpars.h>
#undef PLUS // from src
#undef MINUS // from src
#include <unicode/src/tzfmt.cpp>
#define gLock gLock$1 // avoid redefinition
#include <unicode/src/tzgnames.cpp>
#include <unicode/src/tzgnames.h>
#define gZoneStrings gZoneStrings$1 // avoid redefinition
#define ZNameInfo ZNameInfo$1 // avoid redefinition
#define ZMatchInfo ZMatchInfo$1 // avoid redefinition
#include <unicode/src/tznames_impl.cpp>
#include <unicode/src/tznames_impl.h>
#define gAccessCount gAccessCount$1 // avoid redefinition
#define sweepCache sweepCache$1 // avoid redefinition
#include <unicode/src/tznames.cpp>
#include <unicode/src/tzrule.cpp>
#include <unicode/src/tztrans.cpp>
#define defaultKeywordValues defaultKeywordValues$1 // avoid redefinition
#include <unicode/src/ucal.cpp>
// #include <unicode/src/ucln_in.cpp>: this file can only be included once
#include <unicode/src/ucln_in.h>
#include <unicode/src/ucol_imp.h>
#define cache cache$1 // recorver macro in <unicode/src/measfmt.cpp>, because `CollationLoader::cache$1` cannot be renamed
#define defaultKeywordValues$1 defaultKeywordValues$2 // avoid redefinition
#include <unicode/src/ucol_res.cpp>
#include <unicode/src/ucol_sit.cpp>
#include <unicode/src/ucol.cpp>
#undef NEW_ARRAY // from src
#include <unicode/src/ucoleitr.cpp>
#undef NEW_ARRAY // from src
#include <unicode/src/ucsdet.cpp>
#include <unicode/src/udat.cpp>
#include <unicode/src/udateintervalformat.cpp>
#include <unicode/src/udatpg.cpp>
#include <unicode/src/ufieldpositer.cpp>
#include <unicode/src/uitercollationiterator.cpp>
#include <unicode/src/uitercollationiterator.h>
#include <unicode/src/ulistformatter.cpp>
#include <unicode/src/ulocdata.cpp>
#include <unicode/src/umsg_imp.h>
#include <unicode/src/umsg.cpp>
#define END END$1 // avoid redefinition
#include <unicode/src/unesctrn.cpp>
#include <unicode/src/unesctrn.h>
#define OPEN_DELIM OPEN_DELIM$1 // avoid redefinition
#include <unicode/src/uni2name.cpp>
#include <unicode/src/uni2name.h>
#include <unicode/src/units_complexconverter.cpp>
#include <unicode/src/units_complexconverter.h>
#include <unicode/src/units_converter.cpp>
#include <unicode/src/units_converter.h>
#include <unicode/src/units_data.cpp>
#include <unicode/src/units_data.h>
#include <unicode/src/units_router.cpp>
#include <unicode/src/units_router.h>
#include <unicode/src/unum.cpp>
#include <unicode/src/unumsys.cpp>
#include <unicode/src/upluralrules.cpp>
#include <unicode/src/uregex.cpp>
#include <unicode/src/uregexc.cpp>
#include <unicode/src/uregion.cpp>
#include <unicode/src/usearch.cpp>
#include <unicode/src/uspoof_build.cpp>
#include <unicode/src/uspoof_conf.cpp>
#include <unicode/src/uspoof_conf.h>
#include <unicode/src/uspoof_impl.cpp>
#include <unicode/src/uspoof_impl.h>
#include <unicode/src/uspoof.cpp>
#include <unicode/src/usrchimp.h>
#include <unicode/src/utf16collationiterator.cpp>
#include <unicode/src/utf16collationiterator.h>
#include <unicode/src/utf8collationiterator.cpp>
#include <unicode/src/utf8collationiterator.h>
#include <unicode/src/utmscale.cpp>
#include <unicode/src/utrans.cpp>
#include <unicode/src/vtzone.cpp>
#include <unicode/src/vzone.cpp>
#include <unicode/src/vzone.h>
#include <unicode/src/windtfmt.cpp>
#include <unicode/src/windtfmt.h>
#include <unicode/src/winnmfmt.cpp>
#include <unicode/src/winnmfmt.h>
#include <unicode/src/wintzimpl.cpp>
#include <unicode/src/wintzimpl.h>
#include <unicode/src/zonemeta.cpp>
#include <unicode/src/zonemeta.h>
#include <unicode/src/zrule.cpp>
#include <unicode/src/zrule.h>
#include <unicode/src/ztrans.cpp>
#include <unicode/src/ztrans.h>
#include <unicode/src/locbund.cpp>
#include <unicode/src/locbund.h>
#include <unicode/src/sprintf.cpp>
#include <unicode/src/sscanf.cpp>
#include <unicode/src/ucln_io.cpp>
#include <unicode/src/ucln_io.h>
#include <unicode/src/ufile.cpp>
#include <unicode/src/ufile.h>
#include <unicode/src/ufmt_cmn.cpp>
#include <unicode/src/ufmt_cmn.h>
#include <unicode/src/uprintf.cpp>
#include <unicode/src/uprintf.h>
#include <unicode/src/uprntf_p.cpp>
#include <unicode/src/uscanf_p.cpp>
#include <unicode/src/uscanf.cpp>
#include <unicode/src/uscanf.h>
#include <unicode/src/ustdio.cpp>
#include <unicode/src/ustream.cpp>

export module icu;

