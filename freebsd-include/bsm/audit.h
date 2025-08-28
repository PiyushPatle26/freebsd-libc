/*-
 * bsm/audit.h - Minimal audit system compatibility header
 * FreeBSD Basic Security Module definitions
 */

#ifndef _BSM_AUDIT_H
#define _BSM_AUDIT_H

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/* Basic audit types - minimal for compatibility */
typedef uint32_t au_id_t;
typedef uint32_t au_asid_t;
typedef uint16_t au_event_t;
typedef uint16_t au_emod_t;
typedef uint32_t au_class_t;

/* Audit event structure */
struct auditinfo {
    au_id_t     ai_auid;        /* audit user id */
    au_id_t     ai_mask;        /* audit mask */
    au_id_t     ai_termid;      /* terminal id */  
    au_asid_t   ai_asid;        /* audit session id */
};

/* Minimal audit defines */
#define AU_DEFAUDITID   ((au_id_t)-1)

__END_DECLS

#endif /* _BSM_AUDIT_H */