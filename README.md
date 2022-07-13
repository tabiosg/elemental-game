# Elemental Game

This is a turn-based game where two teams of fighters battle until one team remains standing.
It can be played on the terminal.

---

## Running the Game

Change your directory to the elemental-game. Then run make play.

```c++
cd /documents/elemental-game
make play
```

---

## Brawls

Brawls are fights between two teams of fighters.
By default, the brawl is a 3v3.

Fighters drop their weapons if they die during a brawl.
The actions include healing, attacking, picking up a dropped weapon, or skipping their turn.

Each weapon and fighter has an element.
Depending on elemental affinities, a weapon may wear down its user.
A weapon may be extremely effective against at attacking an opponent or healing an ally, at no downsides.

---

## Elements

The five elements are water, wood, fire, earth, and metal.
Wood is strengthened by water at the cost of wearing down water.
Fire is strengthened by wood at the cost of wearing down wood.
Earth is strengthened by fire at the cost of wearing down fire.
Metal is strengthened by earth at the cost of wearing down earth.
Water is strengthened by metal at the cost of wearing down metal.
This explains interactions between healers and the healed.
This also explains interactions between weapons and its user.

Wood is effective against earth.
Fire is effective against metal.
Earth is effective against water.
Metal is effective against wood.
Water is effective against fire.
This explains interactions between weapons and the target.

---

## Future plans

In order to expand the game, one could consider 
introducing more fighter types, weapon types, or an all 
new main file (by reworking World.cpp). 
It may be worth expanding the game to have better customization 
features and more players on a team.

---

## Documentation

You can read documentation on the source code in this [`README.md`](src/README.md).

---

## Work Done

Most of the work I did was in [`src/`](src/).
