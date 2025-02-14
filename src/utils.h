/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  Ack 2.2 improvements copyright (C) 1994 by Stephen Dooley              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *       _/          _/_/_/     _/    _/     _/    ACK! MUD is modified    *
 *      _/_/        _/          _/  _/       _/    Merc2.0/2.1/2.2 code    *
 *     _/  _/      _/           _/_/         _/    (c)Stephen Zepp 1998    *
 *    _/_/_/_/      _/          _/  _/             Version #: 4.3          *
 *   _/      _/      _/_/_/     _/    _/     _/                            *
 *                                                                         *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

#define DEC_UTILS_H 1

#ifndef DEC_TYPEDEFS_H
#include "typedefs.h"
#endif

#ifndef DEC_CONFIG_H
#include "config.h"
#endif

#if 0
#ifndef DEC_ACK_H
#include "ack.h"
#endif
#endif
/* Use these for bitvectors..saves having to recalculate each time :) Zen */

#define     BIT_0       0
#define     BIT_1       (1 <<  0)                           /*          1 */
#define     BIT_2       (1 <<  1)                           /*          2 */
#define     BIT_3       (1 <<  2)                           /*          4 */
#define     BIT_4       (1 <<  3)                           /*	    8 */
#define     BIT_5       (1 <<  4)                           /*         16 */
#define     BIT_6       (1 <<  5)                           /*	   32 */
#define     BIT_7       (1 <<  6)                           /*	   64 */
#define     BIT_8       (1 <<  7)                           /*	  128 */
#define     BIT_9       (1 <<  8)                           /*	  256 */
#define     BIT_10      (1 <<  9)                           /*	  512 */
#define     BIT_11      (1 << 10)                           /*	 1024 */
#define     BIT_12      (1 << 11)                           /*	 2048 */
#define     BIT_13      (1 << 12)                           /*	 4096 */
#define     BIT_14      (1 << 13)                           /*	 8192 */
#define     BIT_15      (1 << 14)                           /*	16384 */
#define     BIT_16      (1 << 15)                           /*	32768 */
#define     BIT_17      (1 << 16)                           /*	65536 */
#define     BIT_18      (1 << 17)                           /*     131072 */
#define     BIT_19      (1 << 18)                           /*     262144 */
#define     BIT_20      (1 << 19)                           /*     524288 */
#define     BIT_21      (1 << 20)                           /*    1048576 */
#define     BIT_22      (1 << 21)                           /*    2097152 */
#define     BIT_23      (1 << 22)                           /*    4194304 */
#define     BIT_24      (1 << 23)                           /*    8388608 */
#define     BIT_25      (1 << 24)                           /*   16777216 */
#define     BIT_26      (1 << 25)                           /*   33554432 */
#define     BIT_27      (1 << 26)                           /*   67108864 */
#define     BIT_28      (1 << 27)                           /*  134217728 */
#define     BIT_29      (1 << 28)                           /*  268435456 */
#define     BIT_30      (1 << 29)                           /*  536870912 */
#define     BIT_31      (1 << 30)                           /* 1073741824 */
#define     BIT_32      (1 << 31)                           /* 2147483648 */
#define     BIT_33      4294967296                          /* (1 << 32) */
/* BIT_32 commented, it is the sign bit - Wyn */

#define mreturn(msg,ch) \
    { \
        send_to_char(msg,ch); \
        return; \
    }

/*
 *  SSM stuff
 */

#define STR(x) #x
#define SX(x) STR(x)
#define _caller __FILE__ ":" SX(__LINE__)

#define fread_string(x) _fread_string((x), _caller)
char *_fread_string args((FILE * fp, const char *caller));
#define str_dup(x) _str_dup((x), _caller)
char *_str_dup args((const char *str, const char *caller));
#define fread_string_eol(x) _fread_string_eol((x), _caller)
char *_fread_string_eol args((FILE * fp, const char *caller));
#define free_string(x) _free_string((x), _caller)
void _free_string args((char *pstr, const char *caller));

/*
 * Updated pointer referencing, curtesy of Spectrum, from Beyond the Veil
 *
 */

#define OBJ_NEXT          1
#define OBJ_NEXTCONTENT   2
#define OBJ_NULL          3

struct obj_ref_type
{
    bool inuse;
    struct obj_ref_type *next;
    OBJ_DATA **var;
    int type;                                               /* OBJ_xxxx */
};

#define CHAR_NEXT         1
#define CHAR_NEXTROOM     2
#define CHAR_NULL         3

struct char_ref_type
{
    bool inuse;
    struct char_ref_type *next;
    CHAR_DATA **var;
    int type;
};

#define OREF(v, type) do { \
        static struct obj_ref_type s={FALSE,NULL,NULL,type}; \
        s.var=&v; \
        obj_reference(&s); \
    } while(0)
#define OUREF(var) obj_unreference(&var);

#define CREF(v, type) do { \
        static struct char_ref_type s={FALSE,NULL,NULL,type}; \
        s.var=&v; \
        char_reference(&s); \
    } while(0)
#define CUREF(var) char_unreference(&var);

/*
 * Utility macros.
 */
#define UMIN(a, b)              ((a) < (b) ? (a) : (b))
#define UMAX(a, b)              ((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)         ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define LOWER(c)                ((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)                ((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define IS_SET(flag, bit)       ((flag) & (bit))
#define SET_BIT(var, bit)       ((var) = (var) | (bit))
#define REMOVE_BIT(var, bit)    ((var) &= ~(bit))
#define IS_LETTER(c)            ( ((c) >= 'A' && (c) <= 'Z' ) \
    ||((c) >= 'a' && (c) <= 'z' ) )

#define xMASK( bit )        ( 1 << ( ( bit ) & XBM ) )
#define xIS_SET( var, bit ) ( (var).bits[(bit) >> RSV] &   xMASK( bit ) )
#define xSET_BIT( var, bit )    ( (var).bits[(bit) >> RSV] |=  xMASK( bit ) )
#define xREMOVE_BIT( var, bit ) ( (var).bits[(bit) >> RSV] &= ~xMASK( bit ) )
#define xTOGGLE_BIT( var, bit ) ( (var).bits[(bit) >> RSV] ^=  xMASK( bit ) )
#define xIS_EMPTY( bit )     ( xbv_is_empty   ( &(bit) ) )
#define xSAME_BITS( var, bit )   ( xbv_same_bits  ( &(var), &(bit) ) )
#define xCLEAR_BITS( bit )   ( xbv_clear_bits ( &(bit) ) )
#define xSET_BITS( var, bit )    ( xbv_set_bits   ( &(var), &(bit) ) )
#define xREMOVE_BITS( var, bit ) ( xbv_remove_bits( &(var), &(bit) ) )

/*
 * Character macros.
 */

#define IS_NPC(ch)              (IS_SET((ch)->act, ACT_IS_NPC))
#define IS_GUIDE(ch)            (get_trust(ch) == LEVEL_GUIDE)
#define IS_IMMORTAL(ch)         (get_trust(ch) >= LEVEL_IMMORTAL)
#define IS_HERO(ch)             (get_trust(ch) >= LEVEL_HERO)
#define NOT_IN_ROOM(ch, victim) ( ch->x != victim->x || ch->y != victim->y || ch->z != victim->z )
#define IS_OUTSIDE(ch)          ( ( get_char_building(ch) ) ? TRUE : FALSE )
#define IS_NEWBIE(ch)           ((my_get_hours(ch,TRUE) <= 4 ))
#define IS_LINKDEAD(ch)     ((ch->desc) == NULL && !ch->fake )
#define IN_PIT(ch)      (ch->x > PIT_BORDER_X && ch->y > PIT_BORDER_Y && ch->z == Z_PAINTBALL)
#define IS_BUSY(ch)          ( ( ch->desc && ch->desc->connected == CON_PLAYING && ch->c_sn > -1 ) )
#define TRANSPORT_VEHICLE(type) (type == VEHICLE_TRUCK || type == VEHICLE_CHINOOK || type == VEHICLE_STARBASE)
#define AIR_VEHICLE(type)   (type == VEHICLE_AIRCRAFT || type == VEHICLE_CHINOOK || type == VEHICLE_BOMBER || type == VEHICLE_BIO_FLOATER )
#define continual_flight(vhc)   (AIR_VEHICLE(vhc->type) && vhc->type != VEHICLE_CHINOOK)
#define SPACE_VESSAL(vhc)   (vhc->type == VEHICLE_SCOUT || vhc->type == VEHICLE_FIGHTER || vhc->type == VEHICLE_FRIGATE || vhc->type == VEHICLE_BATTLECRUISER || vhc->type == VEHICLE_DESTROYER || vhc->type == VEHICLE_STARBASE || vhc->type == VEHICLE_ALIEN_SCOUT )
#define CIVILIAN(bld)       (build_table[bld->type].militairy == FALSE)
#define IS_AWAKE(ch)            (ch->position > POS_SLEEPING)
#define WAIT_STATE(ch, npulse)  ((ch)->wait = UMAX((ch)->wait, (npulse)))
#define IS_IMPLANTED(ch,bit)    (IS_SET(ch->implants,bit))
#define IS_BUGGED_AREA(x,y) ((x<0))
#define practicing(ch)      (!IS_NPC(ch) && IS_SET(ch->pcdata->pflags,PFLAG_PRACTICE) && ch->c_sn != gsn_practice )
#define paintball(ch)       ((ch->z == Z_PAINTBALL && ch->x >= 200 && ch->y >= 200 && ch->x <= 300 && ch->y <= 300))
#define medal(ch)       ((ch->z == Z_PAINTBALL && ch->x >= 0 && ch->x <= 52 && ch->y >= 0 && ch->y <= 22))
#define COMBAT_LAG(ch)      ((ch->fighttimer > 480))
#define NUKEM(ch)       ((ch->z == Z_PAINTBALL && ch->x == 1 && ch->y == 0))
#define blind_player(ch)    ((IS_SET(ch->config,CONFIG_BLIND)))
#define allied(ch,vch)      (!IS_NPC(ch) && !IS_NPC(vch) && (ch->pcdata->alliance != -1 && ch->pcdata->alliance == vch->pcdata->alliance))
/*
 * Object macros.
 */
#define OBJ_CAN_LOAD(obj,bld)   ((obj->level <= ((bld->level*20)-1)))
#define CAN_WEAR(obj, part)     (IS_SET((obj)->wear_flags,  (part)))
#define IS_OBJ_STAT(obj, stat)  (IS_SET((obj)->extra_flags, (stat)))
#define IS_WEAPON(obj)      (obj != NULL && (obj)->item_type == ITEM_WEAPON)
#define IS_SHIELD(obj)      ((obj)->item_type == ITEM_ARMOR && CAN_WEAR( obj, ITEM_WEAR_HOLD_HAND ))
#define COUNTS_TOWARDS_OBJECT_LIMIT(obj)    ((obj->item_type != ITEM_FLAG && obj->item_type != ITEM_BOARD ))

#define WAREHOUSE(bld)      ((bld->type == BUILDING_WAREHOUSE || bld->type == BUILDING_SECURE_WAREHOUSE))
#define GUNNER(bld)     ((bld->type == BUILDING_GUNNER))
/*
 * Description macros.
 */
#define PERS(ch, looker) ( can_see( looker, (ch) ) ? ch->name : IS_IMMORTAL( ch ) ? get_trust(ch) >= 90 ? "THE Mystical Beanlord" : "A Mystical Bean" : "Someone" )

#define NAME(ch)        ( (ch)->name )

/* Added stuff - Flar */
#define CH(descriptor)  ((descriptor)->original ? \
    (descriptor)->original : (descriptor)->character)

/*
 * Linked list macros, -- Altrag
 */
/* Regular linking of double-linked list */

#define LINK(link, first, last, next, prev) \
    do \
    { \
        if ( (link)->is_free == TRUE ) hang("LINK: link is FREE!"); \
        if ( (link)->is_free != FALSE ) hang("LINK: link is corrupted!"); \
        if ( (link)->prev || (link)->next ) hang("LINK: link already in list?"); \
        if ( (last) && (last)->next ) hang("LINK: last->next NON-NULL!"); \
        if ( !(first) ) \
        (first) = (link); \
        else \
        (last)->next = (link); \
        (link)->next = NULL; \
        (link)->prev = (last); \
        (last) = (link); \
    } while(0)

/* Link at the head of the list rather than the tail.  Double linked */
#define TOPLINK(link, first, last, next, prev) \
    do \
    { \
        if ( (link)->is_free == TRUE ) hang("TOPLINK: link is FREE!"); \
        if ( (link)->is_free != FALSE ) hang("TOPLINK: link is corrupted!"); \
        if ( (link)->prev || (link)->next ) hang("TOPLINK: link already in list?"); \
        if ( (first) && (first)->prev ) hang("TOPLINK: first->prev NON-NULL!"); \
        if ( !(last) ) \
        (last) = (link); \
        else \
        (first)->prev = (link); \
        (link)->prev = NULL; \
        (link)->next = (first); \
        (first) = (link); \
    } while(0)

/* Insert link before ref link */
#define LINK_BEFORE(link, ref, first, last, next, prev) \
    do \
    { \
        if ( (link)->is_free == TRUE ) hang("LINK_BEFORE: link is FREE!"); \
        if ( (link)->is_free != FALSE ) hang("LINK_BEFORE: link is corrupted!"); \
        if ( (link)->prev || (link)->next ) hang("LINK_BEFORE: link already in list?"); \
        if ( !(ref) ) hang("LINK_BEFORE: ref is NULL!"); \
        if ( (ref)->is_free == TRUE ) hang("LINK_BEFORE: ref is FREE!"); \
        if ( (ref)->is_free != FALSE ) hang("LINK_BEFORE: ref is corrupted!"); \
        (link)->next = (ref); \
        (link)->prev = (ref)->prev; \
        if ( !(ref)->prev ) \
        (first) = (link); \
        else \
        ((ref)->prev)->next = (link); \
        (ref)->prev = (link); \
    } while (0)

/* Insert link after ref link */
#define LINK_AFTER(link, ref, first, last, next, prev) \
    do \
    { \
        if ( (link)->is_free == TRUE ) hang("LINK_AFTER: link is FREE!"); \
        if ( (link)->is_free != FALSE ) hang("LINK_AFTER: link is corrupted!"); \
        if ( (link)->prev || (link)->next ) hang("LINK_AFTER: link already in list?"); \
        if ( !(ref) ) hang("LINK_AFTER: ref is NULL!"); \
        if ( (ref)->is_free == TRUE ) hang("LINK_AFTER: ref is FREE!"); \
        if ( (ref)->is_free != FALSE ) hang("LINK_AFTER: ref is corrupted!"); \
        (link)->prev = (ref); \
        (link)->next = (ref)->next; \
        if ( !(ref)->next ) \
        (last) = (link); \
        else \
        ((ref)->next)->prev = (link); \
        (ref)->next = (link); \
    } while (0)

/* Unlink a double linked list */
#define UNLINK(link, first, last, next, prev) \
    do \
    { \
        if ( (link)->is_free == TRUE ) hang("UNLINK: link is FREE!"); \
        if ( (link)->is_free != FALSE ) hang("UNLINK: link is corrupted!"); \
        if ( (link)->prev && (((link)->prev)->next != (link)) ) \
        hang("UNLINK: link->prev->next corrupted!"); \
        if ( (link)->next && (((link)->next)->prev != (link)) ) \
        hang("UNLINK: link->next->prev corrupted!"); \
        if ( !(link)->next ) \
        (last) = (link)->prev; \
        else \
        (link)->next->prev = (link)->prev; \
        if ( !(link)->prev ) \
        (first) = (link)->next; \
        else \
        (link)->prev->next = (link)->next; \
        (link)->prev = NULL; \
        (link)->next = NULL; \
    } while(0)
/* Link to the end of a single-linked list */
#define SING_LINK(link, first, next, DATA_TYPE) \
    do \
    { \
        if ( !(first) ) \
        (first) = (link); \
        else \
        { \
            DATA_TYPE *last; \
            for ( last = (first); last->next; last = last->next ) \
            ; \
            last->next = (link); \
        } \
        (link)->next = NULL; \
    } while(0)

/* Link to head of a single-linked list (normal linking) */
#define SING_TOPLINK(link, first, next) \
    do \
    { \
        (link)->next = (first); \
        (first) = (link); \
    } while(0)

/* Unlink a single linked list */
#define SING_UNLINK(link, first, next, DATA_TYPE) \
    do \
    { \
        if ( (link) == (first) ) \
        (first) = (link)->next; \
        else \
        { \
            DATA_TYPE *prev; \
            for ( prev = (first); prev; prev = prev->next ) \
            if ( prev->next == (link) ) \
            break; \
            if ( prev != NULL ) \
            prev->next = (link)->next; \
            else \
            bug("Sing_unlink: link not in list.", 0); \
        } \
    } while(0)

/* Link to end of a half-linked list */
/* Half linked lists have a LAST pointer, but not a PREV pointer, making
   them approximately halfway between a single linked list and a double
   linked list. -- Altrag */
#define HALF_LINK(link, first, last, next) \
    do \
    { \
        if ( !(last) ) \
        (first) = (link); \
        else \
        (last)->next = (link); \
        (link)->next = NULL; \
        (last) = (link); \
    } while(0)

/* Link to head of a half-linked list. */
#define HALF_TOPLINK(link, first, last, next) \
    do \
    { \
        if ( (last) == (first) ) \
        (last) = (link); \
        (link)->next = (first); \
        (first) = (link); \
    } while(0)

/* Unlink a half-linked list. */
#define HALF_UNLINK(link, first, last, next, DATA_TYPE) \
    do \
    { \
        if ( (link) == (first) ) \
        { \
            (first) = (link)->next; \
            if ( (link) == (last) ) \
            (last) = NULL; \
        } \
        else \
        { \
            DATA_TYPE *prev; \
            for ( prev = (first); prev; prev = prev->next ) \
            if ( prev->next == (link) ) \
            break; \
            if ( prev != NULL ) \
            { \
                prev->next = (link)->next; \
                if ( (link) == (last) ) \
                (last) = prev; \
            } \
            else \
            bug("Half_unlink: link not in list.", 0); \
        } \
    } while(0)

/*
                                                                                                                                                                                                 * Miscellaneous macros.
                                                                                                                                                                                                 */

/* spec: macro-ised getmem as a wrapper around _getmem for mem_log handling */
#define getmem(size) _getmem(size,_caller,1)
#define qgetmem(size) _getmem(size,_caller,0)

/* This one goes as a #define in merc.h.. dont worry.. itll work.. :) */
/* spec: log all dispose's if mem_log==TRUE - also nuke trailing ; */
/* spec: add dispose override, too */
#define _dispose(mem,size,log) \
    do \
    { \
        if ( ! (mem) ) \
        { \
            bug("Disposing NULL memory",0); \
            return; \
        } \
        if (log&&mem_log) log_f("dispose(%p) from %s:%d", (mem), __FILE__, __LINE__); \
        free((mem)); \
        (mem) = NULL; \
    } while(0)

#define dispose(mem,size) _dispose(mem,size,1)
#define qdispose(mem,size) _dispose(mem,size,0)

/*
                                                                                                                                                                                                                                 * Miscellaneous macros.
                                                                                                                                                                                                                                 */
