#ifndef __COUNTRY__H__
#define __COUNTRY__H__

#include "defines.h"

typedef struct
{
    int obj_count;
    char type[MAX_TYPE_LEN];
} excursion_t;

typedef struct
{
    char season[SEASON_LEN];
    int temp_air;
    int temp_water;
    int arriving_time;
} beach_t;

typedef struct
{
    char type[MAX_TYPE_LEN];
    int cost;
} sport_t;

typedef union
{
    excursion_t excursion;
    beach_t beach;
    sport_t sport;
} info_t;

typedef struct
{
    char name[MAX_NAME_LEN];
    int people;
    char capital[MAX_CAPITAL_LEN];
    char mainland[MAX_MAINLAND_LEN];
    int pcr;
    char type[MAX_TYPE_LEN];
    info_t info;
} country_t;

typedef struct
{
    country_t country[MAX_TABLE_LEN];
    size_t len;
} country_table_t;

typedef struct
{
    char name[MAX_NAME_LEN];
    int index;
} country_key_t;

typedef struct
{
    country_key_t key[MAX_TABLE_LEN];
    size_t len;
} country_key_table_t;

#endif
