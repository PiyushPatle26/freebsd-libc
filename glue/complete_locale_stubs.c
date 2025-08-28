/*
 * Complete locale stubs for FreeBSD libc compatibility
 * Provides all missing locale symbols for Unikraft
 */

#include <locale.h>
#include <xlocale.h>
#include <runetype.h>

/* Global locale structures */
_RuneLocale _DefaultRuneLocale = {0};
_RuneLocale *_CurrentRuneLocale = &_DefaultRuneLocale;

/* Extended locale structures */
struct xlocale_component {
    char header;
    char *locale;
};

struct _xlocale {
    struct xlocale_component *components[_XLOCALE_COMPONENT_COUNT];
    int retain_count;
    int using_time_locale;
    int using_numeric_locale;
    int using_monetary_locale;
    int using_messages_locale;
    char _numeric_locale_changed_hint;
    char __mbs_mblen[128];
    char __mbs_mbtowc[128];
    char __mbs_wctomb[128];
};

static struct _xlocale __xlocale_global_locale_data = {0};
static struct _xlocale __xlocale_C_locale_data = {0};

struct _xlocale *__xlocale_global_locale = &__xlocale_global_locale_data;
struct _xlocale *__xlocale_C_locale = &__xlocale_C_locale_data;

/* Thread-local locale support */
int __has_thread_locale = 0;
struct _xlocale *__thread_locale = NULL;