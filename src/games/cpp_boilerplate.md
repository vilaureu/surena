### boilerplate code for games

//TODO general position for data_state_repr and a function to get a ref to it?

thegame.h
```cpp
#pragma once

#include "surena/game.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct thegame_options_s {
    uint32_t var;
} thegame_options;

typedef struct thegame_internal_methods_s {

    // docs for internal_call
    error_code (*internal_call)(game* self, int x);

    /* other exposed internals */

} thegame_internal_methods;

extern const game_methods thegame_gbe;

#ifdef __cplusplus
}
#endif
```

//TODO namespace isn't necessary, use at your own leisure

//USAGE:
// before using `#include "surena/game_decldef.h` to declare and set the game use these macros to setup parameters
// `SURENA_GDD_BNAME` for the name of the const game_methods struct
// `SURENA_GDD_{GNAME,VNAME,INAME,VERSION}` for game,variant,impl,version
// use `SURENA_GDD_FF_*` with the correct feature flag name to enable and declare this feature (order is irrelevant but readable)

// in this scheme the error codes are saved in the game.data2, use grerrorf(self, .....) to use it easily

// if you need legacy support a similar pattern to opts here works well

//TODO needs c boilerplate

thegame.cpp
```cpp
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "rosalia/semver.h"

#include "surena/game.h"

#include "surena/games/thegame.h" // this is your game header

// general purpose helpers for opts, data, bufs

//TODO use as much as you want, this is just meant to be an allocation tracking helper for impls that rewrite on call, if you want caching and lengths use something else
//TODO some better way to keep, access, alloc and free these buffers (by indices?)
struct export_buffers {
    char* options;
    char* state;
    uint8_t* serialize;
    player_id* players_to_move;
    move_data* concrete_moves;
    // float* move_probabilities;
    // move_data* ordered_moves;
    // move_data* actions;
    player_id* results;
    char* legacy;
    int32_t* scores;
    // sync_data* sync_data;
    move_data_sync move_out;
    char* move_str;
    char* print;
};

typedef thegame_options opts_repr;

struct state_repr {
    uint32_t state;
};

//TODO should probably just in general hold all creation info, i.e. legacy as well if exists
struct game_data {
    export_buffers bufs;
    opts_repr opts;
    state_repr state;
};

export_buffers& get_bufs(game* self)
{
    return ((game_data*)(self->data1))->bufs;
}

opts_repr& get_opts(game* self)
{
    return ((game_data*)(self->data1))->opts;
}

state_repr& get_repr(game* self)
{
    return ((game_data*)(self->data1))->state;
}

/* use these in your functions for easy access
export_buffers& bufs = get_bufs(self);
opts_repr& opts = get_opts(self);
state_repr& data = get_repr(self);
*/

#ifdef __cplusplus
extern "C" {
#endif

/* same for internals */

// impl internal declarations
// static error_code internal_call(game* self, int x);

// need internal function pointer struct here
// static const thegame_internal_methods thegame_gbe_internal_methods{
//     .internal_call = internal_call,
// };

// declare and form game
#define SURENA_GDD_BENAME thegame_standard_gbe
#define SURENA_GDD_GNAME "TheGame"
#define SURENA_GDD_VNAME "Standard"
#define SURENA_GDD_INAME "surena_default"
#define SURENA_GDD_VERSION ((semver){1, 0, 0})
#define SURENA_GDD_INTERNALS &thegame_gbe_internal_methods
#define SURENA_GDD_FF_ERROR_STRINGS
#define SURENA_GDD_FF_OPTIONS
#define SURENA_GDD_FF_SERIALIZABLE
#define SURENA_GDD_FF_ID
#define SURENA_GDD_FF_PRINT
#include "surena/game_decldef.h"

// implementation

//TODO only copy over the required functions

static const char* get_last_error(game* self)
{
    return (char*)self->data2;
}

static error_code create(game* self, game_init* init_info)
{
    //TODO
}

static error_code destroy(game* self)
{
    //TODO destroy state_repr
    free(self->data2);
    self->data2 = NULL;
    return ERR_OK;
}

static error_code clone(game* self, game* clone_target)
{
    //TODO
}

static error_code copy_from(game* self, game* other)
{
    //TODO
}

static error_code compare(game* self, game* other, bool* ret_equal)
{
    //TODO
}

static error_code export_options(game* self, player_id player, size_t* ret_size, const char** ret_str)
{
    //TODO
}

static error_code player_count(game* self, uint8_t* ret_count)
{
    //TODO
}

static error_code export_state(game* self, player_id player, size_t* ret_size, const char** ret_str)
{
    //TODO
}

static error_code import_state(game* self, const char* str)
{
    //TODO
}

static error_code serialize(game* self, player_id player, const blob** ret_blob)
{
    //TODO
}

static error_code players_to_move(game* self, uint8_t* ret_count, const player_id** ret_players)
{
    //TODO
}

static error_code get_concrete_moves(game* self, player_id player, uint32_t* ret_count, const move_data** ret_moves)
{
    //TODO
}

static error_code get_concrete_move_probabilities(game* self, player_id player, uint32_t* ret_count, const float** ret_move_probabilities)
{
    //TODO
}

static error_code get_concrete_moves_ordered(game* self, player_id player, uint32_t* ret_count, const move_data** ret_moves)
{
    //TODO
}

static error_code get_actions(game* self, player_id player, uint32_t* ret_count, const move_data** ret_moves)
{
    //TODO
}

static error_code is_legal_move(game* self, player_id player, move_data_sync move)
{
    //TODO
}

static error_code move_to_action(game* self, player_id player, move_data_sync move, move_data_sync** ret_action)
{
    //TODO
}

static error_code is_action(game* self, player_id player, move_data_sync move, bool* ret_is_action)
{
    //TODO
}

static error_code make_move(game* self, player_id player, move_data_sync move)
{
    //TODO
}

static error_code get_results(game* self, uint8_t* ret_count, const player_id** ret_players)
{
    //TODO
}

static error_code export_legacy(game* self, player_id player, size_t* ret_size, const char** ret_str)
{
    //TODO
}

static error_code get_scores(game* self, size_t* ret_count, player_id* players, const int32_t** ret_scores)
{
    //TODO
}

static error_code id(game* self, uint64_t* ret_id)
{
    //TODO
}

static error_code eval(game* self, player_id player, float* ret_eval)
{
    //TODO
}

static error_code discretize(game* self, uint64_t seed)
{
    //TODO
}

static error_code playout(game* self, uint64_t seed)
{
    //TODO
}

static error_code redact_keep_state(game* self, uint8_t count, const player_id* players)
{
    //TODO
}

static error_code export_sync_data(game* self, uint32_t* ret_count, const sync_data** ret_sync_data)
{
    //TODO
}

static error_code import_sync_data(game* self, blob b)
{
    //TODO
}

static error_code get_move_data(game* self, player_id player, const char* str, move_data_sync** ret_move)
{
    //TODO
}

static error_code get_move_str(game* self, player_id player, move_data_sync move, size_t* ret_size, const char** ret_str)
{
    //TODO
}

static error_code print(game* self, player_id player, size_t* ret_size, const char** ret_str)
{
    //TODO
}

//=====
// game internal methods

// static error_code internal_call(game* self, int x)
// {
//     //TODO
// }

#ifdef __cplusplus
}
#endif

```
