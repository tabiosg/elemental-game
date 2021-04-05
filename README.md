# elemental-game

This is a turn-based RPG. 
Fighters form teams to battle one another in brawls. 
Users can customize their fighters outside of brawls.

## Brawls

Brawls are fights between two teams of fighters. 
Fighters are out once they lose all health and may not be revived until the brawl ends. 
The team left standing wins.
Each team and each member takes turns making an action.
Fighters drop their weapons if they lose during a brawl.
Downed fighters will get their weapons back at the end of the brawl.
The actions include healing, attacking, picking up a dropped weapon, or skipping their turn.

## Teams

Teams may have any number of players. 
Those in the same team may heal one another during a brawl.
Those in the same team may not attack one another.

## Fighters

A fighter may have various weapons, but they may only use one at a time.
Fighters can swap between weapons during combat.
Each fighter has an element.
Each fighter can strengthen their weapon.
Depending on elemental affinities, the weapon will be even stronger at the cost of wearing down the user.
Fighters can heal allies.
Depending on elemental affinities, the healing will be even stronger at the cost of wearing down the healer.

## Weapons

A weapon has an element.
Depending on elemental affinities, a weapon may wear down its user.
A weapon may be extremely effective against an opponent, at no downsides.

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

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
