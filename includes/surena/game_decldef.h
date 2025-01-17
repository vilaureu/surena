#include "surena/game.h"

#ifndef SURENA_GDD_BENAME
#error "surena game decldef requires a backend name"
#endif

#ifndef SURENA_GDD_GNAME
#error "surena game decldef requires a game name"
#endif

#ifndef SURENA_GDD_VNAME
#error "surena game decldef requires a variant name"
#endif

#ifndef SURENA_GDD_INAME
#error "surena game decldef requires an implementation name"
#endif

#ifndef SURENA_GDD_VERSION
#error "surena game decldef requires a game version"
#endif

#ifndef SURENA_GDD_INTERNALS
#error "surena game decldef requires internals"
#endif

#ifdef SURENA_GDD_FFB_ERROR_STRINGS
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_ERROR_STRINGS"
#endif

#ifdef SURENA_GDD_FFB_OPTIONS
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_OPTIONS"
#endif

#ifdef SURENA_GDD_FFB_SERIALIZABLE
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_SERIALIZABLE"
#endif

#ifdef SURENA_GDD_FFB_LEGACY
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_LEGACY"
#endif

#ifdef SURENA_GDD_FFB_RANDOM_MOVES
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_RANDOM_MOVES"
#endif

#ifdef SURENA_GDD_FFB_HIDDEN_INFORMATION
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_HIDDEN_INFORMATION"
#endif

#ifdef SURENA_GDD_FFB_SIMULTANEOUS_MOVES
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_SIMULTANEOUS_MOVES"
#endif

#ifdef SURENA_GDD_FFB_BIG_MOVES
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_BIG_MOVES"
#endif

#ifdef SURENA_GDD_FFB_MOVE_ORDERING
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_MOVE_ORDERING"
#endif

#ifdef SURENA_GDD_FFB_SCORES
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_SCORES"
#endif

#ifdef SURENA_GDD_FFB_ID
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_ID"
#endif

#ifdef SURENA_GDD_FFB_EVAL
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_EVAL"
#endif

#ifdef SURENA_GDD_FFB_PLAYOUT
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_PLAYOUT"
#endif

#ifdef SURENA_GDD_FFB_PRINT
#error "surena gdd internal feature flag bool already defined: SURENA_GDD_FFB_PRINT"
#endif

#ifndef SURENA_GDD_FF_ERROR_STRINGS
#define SURENA_GDD_FFB_ERROR_STRINGS false
#else
#define SURENA_GDD_FFB_ERROR_STRINGS true
#endif

#ifndef SURENA_GDD_FF_OPTIONS
#define SURENA_GDD_FFB_OPTIONS false
#else
#define SURENA_GDD_FFB_OPTIONS true
#endif

#ifndef SURENA_GDD_FF_SERIALIZABLE
#define SURENA_GDD_FFB_SERIALIZABLE false
#else
#define SURENA_GDD_FFB_SERIALIZABLE true
#endif

#ifndef SURENA_GDD_FF_LEGACY
#define SURENA_GDD_FFB_LEGACY false
#else
#define SURENA_GDD_FFB_LEGACY true
#endif

#ifndef SURENA_GDD_FF_RANDOM_MOVES
#define SURENA_GDD_FFB_RANDOM_MOVES false
#else
#define SURENA_GDD_FFB_RANDOM_MOVES true
#endif

#ifndef SURENA_GDD_FF_HIDDEN_INFORMATION
#define SURENA_GDD_FFB_HIDDEN_INFORMATION false
#else
#define SURENA_GDD_FFB_HIDDEN_INFORMATION true
#endif

#ifndef SURENA_GDD_FF_SIMULTANEOUS_MOVES
#define SURENA_GDD_FFB_SIMULTANEOUS_MOVES false
#else
#define SURENA_GDD_FFB_SIMULTANEOUS_MOVES true
#endif

#ifndef SURENA_GDD_FF_BIG_MOVES
#define SURENA_GDD_FFB_BIG_MOVES false
#else
#define SURENA_GDD_FFB_BIG_MOVES true
#endif

#ifndef SURENA_GDD_FF_MOVE_ORDERING
#define SURENA_GDD_FFB_MOVE_ORDERING false
#else
#define SURENA_GDD_FFB_MOVE_ORDERING true
#endif

#ifndef SURENA_GDD_FF_SCORES
#define SURENA_GDD_FFB_SCORES false
#else
#define SURENA_GDD_FFB_SCORES true
#endif

#ifndef SURENA_GDD_FF_ID
#define SURENA_GDD_FFB_ID false
#else
#define SURENA_GDD_FFB_ID true
#endif

#ifndef SURENA_GDD_FF_EVAL
#define SURENA_GDD_FFB_EVAL false
#else
#define SURENA_GDD_FFB_EVAL true
#endif

#ifndef SURENA_GDD_FF_PLAYOUT
#define SURENA_GDD_FFB_PLAYOUT false
#else
#define SURENA_GDD_FFB_PLAYOUT true
#endif

#ifndef SURENA_GDD_FF_PRINT
#define SURENA_GDD_FFB_PRINT false
#else
#define SURENA_GDD_FFB_PRINT true
#endif

#if SURENA_GDD_FFB_ERROR_STRINGS
static get_last_error_gf_t get_last_error;
#endif
static create_gf_t create;
static destroy_gf_t destroy;
static clone_gf_t clone;
static copy_from_gf_t copy_from;
static compare_gf_t compare;
#if SURENA_GDD_FFB_OPTIONS
static export_options_gf_t export_options;
#endif
static player_count_gf_t player_count;
static export_state_gf_t export_state;
static import_state_gf_t import_state;
#if SURENA_GDD_FFB_SERIALIZABLE
static serialize_gf_t serialize;
#endif
static players_to_move_gf_t players_to_move;
static get_concrete_moves_gf_t get_concrete_moves;
#if SURENA_GDD_FFB_RANDOM_MOVES
static get_concrete_move_probabilities_gf_t get_concrete_move_probabilities;
#endif
#if SURENA_GDD_FFB_MOVE_ORDERING
static get_concrete_moves_ordered_gf_t get_concrete_moves_ordered;
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
static get_actions_gf_t get_actions;
#endif
static is_legal_move_gf_t is_legal_move;
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
static move_to_action_gf_t move_to_action;
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
static is_action_gf_t is_action;
#endif
static make_move_gf_t make_move;
static get_results_gf_t get_results;
#if SURENA_GDD_FFB_LEGACY
static export_legacy_gf_t export_legacy;
#endif
#if SURENA_GDD_FFB_SCORES
static get_scores_gf_t get_scores;
#endif
#if SURENA_GDD_FFB_ID
static id_gf_t id;
#endif
#if SURENA_GDD_FFB_EVAL
static eval_gf_t eval;
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
static discretize_gf_t discretize;
#endif
#if SURENA_GDD_FFB_PLAYOUT
static playout_gf_t playout;
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
static redact_keep_state_gf_t redact_keep_state;
#endif
#if SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
static export_sync_data_gf_t export_sync_data;
#endif
#if SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
static import_sync_data_gf_t import_sync_data;
#endif
static get_move_data_gf_t get_move_data;
static get_move_str_gf_t get_move_str;
#if SURENA_GDD_FFB_PRINT
static print_gf_t print;
#endif

// clang-format off
const game_methods SURENA_GDD_BENAME
{
    .game_name = (SURENA_GDD_GNAME),
    .variant_name = (SURENA_GDD_VNAME),
    .impl_name = (SURENA_GDD_INAME),
    .version = (SURENA_GDD_VERSION),
    .features = game_feature_flags{
        .error_strings = SURENA_GDD_FFB_ERROR_STRINGS,
        .options = SURENA_GDD_FFB_OPTIONS,
        .serializable = SURENA_GDD_FFB_SERIALIZABLE,
        .legacy = SURENA_GDD_FFB_LEGACY,
        .random_moves = SURENA_GDD_FFB_RANDOM_MOVES,
        .hidden_information = SURENA_GDD_FFB_HIDDEN_INFORMATION,
        .simultaneous_moves = SURENA_GDD_FFB_SIMULTANEOUS_MOVES,
        .move_ordering = SURENA_GDD_FFB_MOVE_ORDERING,
        .scores = SURENA_GDD_FFB_SCORES,
        .id = SURENA_GDD_FFB_ID,
        .eval = SURENA_GDD_FFB_EVAL,
        .playout = SURENA_GDD_FFB_PLAYOUT,
        .print = SURENA_GDD_FFB_PRINT,
    },
    .internal_methods = (void*)(SURENA_GDD_INTERNALS),
#if SURENA_GDD_FFB_ERROR_STRINGS
    .get_last_error = get_last_error,
#else
    .get_last_error = NULL,
#endif
    .create = create,
    .destroy = destroy,
    .clone = clone,
    .copy_from = copy_from,
    .compare = compare,
#if SURENA_GDD_FFB_OPTIONS
    .export_options = export_options,
#else
    .export_options = NULL,
#endif
    .player_count = player_count,
    .export_state = export_state,
    .import_state = import_state,
#if SURENA_GDD_FFB_SERIALIZABLE
    .serialize = serialize,
#else
    .serialize = NULL,
#endif
    .players_to_move = players_to_move,
    .get_concrete_moves = get_concrete_moves,
#if SURENA_GDD_FFB_RANDOM_MOVES
    .get_concrete_move_probabilities = get_concrete_move_probabilities,
#else
    .get_concrete_move_probabilities = NULL,
#endif
#if SURENA_GDD_FFB_MOVE_ORDERING
    .get_concrete_moves_ordered = get_concrete_moves_ordered,
#else
    .get_concrete_moves_ordered = NULL,
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
    .get_actions = get_actions,
#else
    .get_actions = NULL,
#endif
    .is_legal_move = is_legal_move,
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
    .move_to_action = move_to_action,
#else
    .move_to_action = NULL,
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
    .is_action = is_action,
#else
    .is_action = NULL,
#endif
    .make_move = make_move,
    .get_results = get_results,
#if SURENA_GDD_FFB_LEGACY
    .export_legacy = export_legacy,
#else
    .export_legacy = NULL,
#endif
#if SURENA_GDD_FFB_SCORES
    .get_scores = get_scores,
#else
    .get_scores = NULL,
#endif
#if SURENA_GDD_FFB_ID
    .id = id,
#else
    .id = NULL,
#endif
#if SURENA_GDD_FFB_EVAL
    .eval = eval,
#else
    .eval = NULL,
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
    .discretize = discretize,
#else
    .discretize = NULL,
#endif
#if SURENA_GDD_FFB_PLAYOUT
    .playout = playout,
#else
    .playout = NULL,
#endif
#if SURENA_GDD_FFB_RANDOM_MOVES || SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
    .redact_keep_state = redact_keep_state,
#else
    .redact_keep_state = NULL,
#endif
#if SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
    .export_sync_data = export_sync_data,
#else
    .export_sync_data = NULL,
#endif
#if SURENA_GDD_FFB_HIDDEN_INFORMATION || SURENA_GDD_FFB_SIMULTANEOUS_MOVES
    .import_sync_data = import_sync_data,
#else
    .import_sync_data = NULL,
#endif
    .get_move_data = get_move_data,
    .get_move_str = get_move_str,
#if SURENA_GDD_FFB_PRINT
    .print = print,
#else
    .print = NULL,
#endif
};
    // clang-format on

#undef SURENA_GDD_BENAME
#undef SURENA_GDD_GNAME
#undef SURENA_GDD_VNAME
#undef SURENA_GDD_INAME
#undef SURENA_GDD_VERSION
#undef SURENA_GDD_INTERNALS

#undef SURENA_GDD_FF_ERROR_STRINGS
#undef SURENA_GDD_FFB_ERROR_STRINGS

#undef SURENA_GDD_FF_OPTIONS
#undef SURENA_GDD_FFB_OPTIONS

#undef SURENA_GDD_FF_SERIALIZABLE
#undef SURENA_GDD_FFB_SERIALIZABLE

#undef SURENA_GDD_FF_LEGACY
#undef SURENA_GDD_FFB_LEGACY

#undef SURENA_GDD_FF_RANDOM_MOVES
#undef SURENA_GDD_FFB_RANDOM_MOVES

#undef SURENA_GDD_FF_HIDDEN_INFORMATION
#undef SURENA_GDD_FFB_HIDDEN_INFORMATION

#undef SURENA_GDD_FF_SIMULTANEOUS_MOVES
#undef SURENA_GDD_FFB_SIMULTANEOUS_MOVES

#undef SURENA_GDD_FF_BIG_MOVES
#undef SURENA_GDD_FFB_BIG_MOVES

#undef SURENA_GDD_FF_MOVE_ORDERING
#undef SURENA_GDD_FFB_MOVE_ORDERING

#undef SURENA_GDD_FF_SCORES
#undef SURENA_GDD_FFB_SCORES

#undef SURENA_GDD_FF_ID
#undef SURENA_GDD_FFB_ID

#undef SURENA_GDD_FF_EVAL
#undef SURENA_GDD_FFB_EVAL

#undef SURENA_GDD_FF_PLAYOUT
#undef SURENA_GDD_FFB_PLAYOUT

#undef SURENA_GDD_FF_PRINT
#undef SURENA_GDD_FFB_PRINT
