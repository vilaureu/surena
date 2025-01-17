# surena API design
The surena project provides powerful APIs and utilities for creating all kinds of board games.  
All manner of games can be described by the general purpose game methods provided in [`game.h`](../includes/surena/game.h). This includes, but is not limited to, games containing:
* setup options
* randomness
* simultaneous moves
* hidden information
* scores (reward based results)
* legacies carrying over to future games
* (planned) custom and dynamic timecontrol stages and staging
* (planned) teams
* (planned) non-trivial draw/resign voting

To facilitate general usage with game agnostic tooling (e.g. visualization / AI) many of the more advanced features of the game method api are guarded behind feature flags. Additionally the game methods can optionally be enriched with features aiding in automatic processing like state ids, board evals and further internal methods.  
For more information on the provided engine methods API see [`engine.h`](../includes/surena/engine.h).

## the game

### terminology
|term|description|example|
|---|---|---|
|random moves / randomness|Any type of event where the outcome is decided from a fixed set of results, by chance, offers random moves. This outcome may or may not be visible to all players.|Roll some dice in the open.|
|simultaneous moves|Any state from which more than one player can move offers simultaneous moves. These moves may or may not be commutative.|Chosen actions are revealed by both players at once.|
|hidden information|Any game where there exists any valid state in which any information is conceiled from any set of players contains hidden information.|A deck of cards shuffled at the start.||
|`player_id`|An 8-bit integer representing the id of a player participating in a game. For a game with N players, the ids are always numbered 1 to N. A maximum of 254 player ids can be assigned.||
|`PLAYER_NONE`|Special player id representing either none or all players. Never assigned to participants.||
|`PLAYER_RAND`|Special player id representing random chance. Non-discretized games use this to offer moves that decide the outcome of random events.||
|move|Moves represent state transitions on the game board and its internal state. A move that encodes an action is part of exactly that action set.|Moves as the union on actions and concrete moves.|
|action|Actions represent sets of moves, i.e. sets of concrete moves (action instances / informed moves). Every action can be encoded as a move.|Draw *some* card from a hidden pile. Roll the die (irrespective of outcome).|
|concrete move|For every action, the concrete moves it encompasses determine the outcome of the action move. Every concrete move can be encoded as a move or reduced to an action, i.e. a move.|Roll a specific number with a die.|
|options|Any information that the game requires to be available at time of creation, and which can not be changed for lifetime of the game.|Board sizes, player counts.|
|state|A set of facts that represents the current setup of the "board".|String equivalent of a screenshot of the board (and all players hands).|
|serialization|Comprehensive representation of the entire game as it exists. This includes options, legacy, state *and* any internal data that influences the game. I.e. a deserialized game has to behave *exactly* like the one it was serialized from would.|Raw binary stream.|
|legacy|Carry over information from a previous game of this type.|Parts of a card deck get replaced/changed/added/removed over the course of multiple games.|
|scores|Scoring mechanism, possibly used to determine single game results (winners). Accumulate over multiple games for multi-game results.|Victory/Penalty points.|

### game methods
Goals served by the game methods:
* enforce game rules (illegal moves can not be played)
* provide uniform access to common game actions (e.g. get moves and make moves until game is done)
* ability to replay (physical) games with and without hidden information and randomness
* api designed for easy use with general purpose game playing AI

//TODO

## examples
Examples for the more advanced features of the game methods api.

//TODO provide links to the example games that implement these features..

### options
Some games require information to be set up which can not change, easily or at all, after the set up. Among others this includes: board sizes, player counts, draft pools for components and (variant) rules.  
On creation a game that supports the options feature may be passed an options string containing game specific information about the set up. To make the game exchangeable a created game that supports options must always be able to export the ones it is using to a string.

### public randomness
Two modes of operation:
* Undiscretized (Open)
  * Random moves are decided by a move from PLAYER_RAND.
* Discretized (Closed)
  * Random move variety is eliminated because the game has a discretization seed. PLAYER_RAND still moves, but there is only one move left.

For replaying (physical) games, open games are used. Make the appropriate randomly selected result move as `PLAYER_RAND`.

#### example 1 (flip coin)
In this example a coin is flipped to decide which player goes first. However, the same working principle can be applied to all kinds of public randomness, like rolling dice at the start of a turn.

After creation the game is undiscretized by default. Because the coin flip is the first thing that happens in the game, `players_to_move` returns `{PLAYER_RAND}`. After discretization with a seed, all randomness is removed from the game, the results are then pre-determined.
* **Open**:
  Moves with `get_concrete_moves`: `{COIN_HEAD, COIN_TAIL}`.
* **Closed**:
  Moves with `get_concrete_moves`: `{COIN_TAIL}`.   (because the discretization collapsed to tail in this example).  
  Note that the random player still has to move, although only a single move is available for them. This assures that random events are still separated semantically from the rest of the gameplay. E.g. a possible frontend can separate and animate all moves.
When any move has been made the game proceeds as it normally would, using the move to determine which random result happened.

#### example 2 (roll dice)
In this example we assume a game where, among other things, a player may choose to roll a dice (the result of which is then somehow used in gameplay). We assume at least 1 player, with the id`P1`.

In both open and closed games we start with: `players_to_move` returns `{P1}` and `get_concrete_moves` returns `{MOVE_1, ..., ROLL_DIE, ..., MOVE_N}`.
When player `P1` makes the move `ROLL_DIE`, in both open and closed games, the next `players_to_move` are `{PLAYER_RAND}`. Just like the coin, the results for `get_concrete_moves` differ only slightly:
* **Open**: `{DIE_1, DIE_2, DIE_3, DIE_4, DIE_5, DIE_6}`
* **Closed**: `{DIE_4}`

### hidden randomness
This is the easiest form of hidden information.  
In this example a deck of cards is shuffled at the beginning of the game and players draw from it both faceup and facedown (into their hand).

//TODO need sync data events here too?, also explain sync data usage somewhere

#### example 1 (shuffle a deck)
Shuffling may work different ways, depending on the implementation, but is always representable by moves. Commonly the deck is either permuted in place (swap pairs of cards), or "drafted" from a start configuration to the shuffled deck (one by one).

Assuming N cards in the deck and a "draft" shuffle wherein the cards of the shuffled deck are selected one by one from an unshuffled initial deck. `PLAYER_RAND` moves N times.

**Open**  
Each time the available moves *include* all the remaining undrafted cards from the initial deck.  
*Additionally* at each choice point, there is also one more concrete move offered: `DRAFT_HIDDEN`.  
Drafting the hidden card semantically represents the *action* of the concrete moves drafting specific cards. I.e. drafting *any one* card but the spectator informing the game does not know which one was drafted.  
It is advisable to not make the digital shuffle implementation unneccessary complex, because if the game is replaying a "physical" game, then both shuffle methods should roughly match. Also, in an open game the shuffling process *may* be a mix between hidden drafts and known drafts. The game implementation *may* take advantage of this and track the possible state space for all players from there, but it does not have to, and could also just assume the deck as entirely unknown as soon as one hidden draft exists.

**Closed**  
Each time the only available move is the card pre-selected via the discretization seed. I.e. after making the only available move N times, the deck is "shuffled" according to the seed.  
If for example the closed board is a "server" board, that does not want to distribute the actually drafted cards to "clients", it only distributes the `move_to_action` result of the concrete draft move. I.e. it only distributes `DRAFT_HIDDEN` moves, because the action class of all concrete draft moves is `DRAFT_HIDDEN` the move for which does NOT show up in the `get_concrete_moves` list offered by the closed game.  
//TODO ideally want always applyable algo, e.g. where server ALWAYS distributes move->action actions

**In general** pre-shuffling a deck in this rarely advantageous, and most of the time it is easier to just delay the resolution of the randomness to a point where it is public. I.e. do not pre-shuffle the deck but just keep a knowledge of what cards it contains and then on draw resolve the randomness of which card was actually drawn. (See example 2.)

#### example 2 (draw card faceup from "shuffled" deck)
In this example we assume the easier case of drawing a card from a deck that was not actually shuffled card by card using moves, but is just represented by a list of all contained cards. On the draw action the result of the randomness if resolved.  
On the players turn `get_concrete_moves` shows the draw action as `{..., DRAW_FACEUP, ...}`. When the `DRAW_FACEUP` move is made `PLAYER_RAND` is to move, to select the outcome of the draw.

**Open**: `PLAYER_RAND` offers all cards as concrete moves, choose one by random or select one to replay from physical.  
**Closed**: `PLAYER_RAND` offers the one card that is determined to be draw by using the discretization seed.

//TODO want to example the pre-shuffled case as well? what would be the use case even?

#### example 3 (draw card facedown from "shuffled" deck)
This can also be rephrased to drawing the card from the *not* pre-shuffled deck into the players secret hand. Or even not revealing the card to any player and just placing it on the table for later reveal.  
In this example we assume a *not* pre-shuffled deck, i.e. lazy resolution, and players drawing from it to their secret hand by way of a `DRAW_FACEDOWN` move on their turn.  
//TODO
this creates hidden info as well  
player chooses action to draw facedown  
open: player rand offers all the cards available (on client that is all* minus some that could be card counted away, but thats optional ;; on server it shows all that can actually be drawn)
close: ??
?? how is the chosen info distributed to the player in belongs to? sync data?

#### example 4 (flip coin in secret)
//TODO want this?

### revealing hidden information (e.g. play card from secret hand)
A more complicated form of hidden information.  
//TODO
how the move is done changes how this behaviour would work:
- player chooses action to play card from hand (e.g. by idx in their hand) -> somehow need to sync back to the other boards WHAT card had been played
- player makes move that includes info about the card they are playing -> just send the move to other boards

### transforming hidden information (e.g. play card from secret hand *facedown*)
The most complicated form of hidden information.  
//TODO

### simultaneous moves
A relatively uncomplicated form of hidden information, but still with some important insights with regard to syncing information across players.  
ABC //TODO (with/without moved indicator for opponent)  
//TODO types (no)sync,unordered,ordered,want_discard,reissue,never_discard

#### example 1 (gated)
//TODO all SM players have to move before game continues, no interplay between moves

**Basic Idea**: The game returns multiple players to move, and for each player their available moves. If a player makes a move up to a "barrier" at which all players need to resolve then they are removed from the players to move until all other players have done so as well. E.g. everyone plays a card simultaneously: everyone is to move, once a card is played they are no longer to move and the game buffers their move, once all have moved the game resolves the effect "as if everyone moved at once" now that it knows all the moves. Addendun: if e.g. all players play two cards at once: a player is only removed from the players to move once they have chosen both cards.

#### example 2 (synced)
//TODO interplay not allowed for now b/c total move order

**Basic Idea**: The game returns multiple players to move, and for each player their available moves. If a player makes a move in a synced SM scenario, they are likely still to move, as are the other players, but the available moves for the other players might have changed. This is what the sync counter is used for. I.e. simultaneous moves not interpreted as "all move at once", but as "everyone can start moving at any time, but only one can move at a time".

### scores
//TODO

### teams
//TODO

### legacy
//TODO

### timecontrol
//TODO

### draw/resign
//TODO

## utilities
For implementation convenience, some general purpose APIs are provided:
* **base64**: encode/decode bytes to base64 and back
* **fast_prng**: small and fast seeded pseudo random number generator
* **noise**: easy to use noise functions to generate pseudo random numbers without the need to remember anything
* **raw_stream**: very basic primitive / string / blob stream writer to quickly put data in a buffer and get it out again
* **serialization**: layout based descriptive serializer for zero/copy/(de-)serialize/destroy on dynamic objects
