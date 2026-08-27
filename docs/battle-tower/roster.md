# Battle Tower - Pokemon Roster (Inventory)

> Source of truth: this build's own species data (`src/data/pokemon/species_info/gen_*_families.h`).
> Generated inventory - the rentable Pokemon pool for the new Battle Tower mode.

**Scope decisions (locked):** all fully-evolved Pokemon of every generation + Eviolite-viable NFE mons; 
legendaries/mythicals INCLUDED but tagged as a separate **Restricted tier**; all battle-distinct regional & alternate formes included as their own entries. 
Mega Evolutions, Primal Reversions, and Gigantamax forms are EXCLUDED (gimmicks are OFF per project direction). 
In-battle-only transformations (Aegislash Blade, Palafin Hero, Darmanitan Zen, etc.) and cosmetic-only variants (Vivillon patterns, Florges colors, etc.) are collapsed to a single representative entry.

## Summary counts

| Category | Count |
|---|---|
| Standard fully-evolved | 443 |
| Regional-form finals | 32 |
| Alternate battle formes | 24 |
| Restricted tier (legendary/mythical/paradox/UB) | 139 |
| **Fully-evolved total** | **638** |
| Eviolite NFE (curated) | 34 |
| **Grand total (approx)** | **672** |

## A. Standard fully-evolved (by generation)

### Gen 1 (Kanto)  (89)

Aerodactyl, Alakazam, Annihilape, Arbok, Arcanine, Beedrill, Bellossom, Blastoise, Blissey, Butterfree, Charizard, Clefable, Cloyster, Crobat, Dewgong, Ditto, Dodrio, Dragonite, Dugtrio, Electivire, Electrode, Espeon, Exeggutor, Farfetch'd, Fearow, Flareon, Gengar, Glaceon, Golduck, Golem, Gyarados, Hitmonchan, Hitmonlee, Hitmontop, Hypno, Jolteon, Jynx, Kabutops, Kangaskhan, Kingdra, Kingler, Kleavor, Lapras, Leafeon, Lickilicky, Machamp, Magmortar, Magnezone, Marowak, Mr. Mime, Mr. Rime, Muk, Nidoking, Nidoqueen, Ninetales, Omastar, Parasect, Perrserker, Persian, Pidgeot, Pinsir, Politoed, Poliwrath, Porygon-Z, Raichu, Rapidash, Raticate, Rhyperior, Sandslash, Scizor, Seaking, Sirfetch'd, Slowbro, Slowking, Snorlax, Starmie, Steelix, Sylveon, Tangrowth, Tauros, Tentacruel, Umbreon, Vaporeon, Venomoth, Venusaur, Victreebel, Vileplume, Weezing, Wigglytuff

### Gen 2 (Johto)  (48)

Ambipom, Ampharos, Ariados, Azumarill, Clodsire, Corsola, Cursola, Delibird, Donphan, Dudunsparce, Farigiraf, Feraligatr, Forretress, Furret, Gliscor, Granbull, Heracross, Honchkrow, Houndoom, Jumpluff, Lanturn, Ledian, Magcargo, Mamoswine, Mantine, Meganium, Miltank, Mismagius, Noctowl, Octillery, Overqwil, Quagsire, Qwilfish, Shuckle, Skarmory, Smeargle, Sneasler, Sudowoodo, Sunflora, Togekiss, Typhlosion, Tyranitar, Ursaluna, Weavile, Wobbuffet, Wyrdeer, Xatu, Yanmega

### Gen 3 (Hoenn)  (69)

Absol, Aggron, Altaria, Armaldo, Banette, Beautifly, Blaziken, Breloom, Cacturne, Camerupt, Castform, Chimecho, Claydol, Cradily, Crawdaunt, Delcatty, Dusknoir, Dustox, Exploud, Flygon, Froslass, Gallade, Gardevoir, Glalie, Gorebyss, Grumpig, Hariyama, Huntail, Illumise, Kecleon, Linoone, Ludicolo, Lunatone, Luvdisc, Manectric, Masquerain, Mawile, Medicham, Metagross, Mightyena, Milotic, Minun, Ninjask, Obstagoon, Pelipper, Plusle, Probopass, Relicanth, Roserade, Sableye, Salamence, Sceptile, Seviper, Sharpedo, Shedinja, Shiftry, Slaking, Solrock, Spinda, Swalot, Swampert, Swellow, Torkoal, Tropius, Volbeat, Wailord, Walrein, Whiscash, Zangoose

### Gen 4 (Sinnoh)  (30)

Abomasnow, Bastiodon, Bibarel, Bronzong, Carnivine, Chatot, Cherrim, Drapion, Drifblim, Empoleon, Floatzel, Garchomp, Gastrodon, Hippowdon, Infernape, Kricketune, Lopunny, Lucario, Lumineon, Luxray, Pachirisu, Purugly, Rampardos, Rotom, Skuntank, Spiritomb, Staraptor, Torterra, Toxicroak, Vespiquen

### Gen 5 (Unova)  (70)

Accelgor, Alomomola, Amoonguss, Archeops, Audino, Basculin, Beartic, Beheeyem, Bouffalant, Braviary, Carracosta, Chandelure, Cinccino, Cofagrigus, Conkeldurr, Crustle, Cryogonal, Darmanitan, Druddigon, Durant, Eelektross, Emboar, Emolga, Escavalier, Excadrill, Ferrothorn, Galvantula, Garbodor, Gigalith, Golurk, Gothitelle, Haxorus, Heatmor, Hydreigon, Jellicent, Kingambit, Klinklang, Krookodile, Leavanny, Liepard, Lilligant, Mandibuzz, Maractus, Mienshao, Musharna, Reuniclus, Runerigus, Samurott, Sawk, Sawsbuck, Scolipede, Scrafty, Seismitoad, Serperior, Sigilyph, Simipour, Simisage, Simisear, Stoutland, Stunfisk, Swanna, Swoobat, Throh, Unfezant, Vanilluxe, Volcarona, Watchog, Whimsicott, Zebstrika, Zoroark

### Gen 6 (Kalos)  (28)

Aegislash, Aromatisse, Aurorus, Avalugg, Barbaracle, Carbink, Chesnaught, Clawitzer, Dedenne, Delphox, Diggersby, Dragalge, Florges, Gogoat, Goodra, Gourgeist, Greninja, Hawlucha, Heliolisk, Klefki, Malamar, Noivern, Pangoro, Pyroar, Slurpuff, Trevenant, Tyrantrum, Vivillon

### Gen 7 (Alola)  (32)

Araquanid, Bewear, Bruxish, Comfey, Crabominable, Decidueye, Dhelmise, Drampa, Golisopod, Gumshoos, Incineroar, Komala, Kommo-o, Lurantis, Lycanroc, Mimikyu, Mudsdale, Oranguru, Palossand, Passimian, Primarina, Pyukumuku, Ribombee, Salazzle, Shiinotic, Togedemaru, Toucannon, Toxapex, Tsareena, Turtonator, Vikavolt, Wishiwashi

### Gen 8 (Galar)  (37)

Appletun, Archaludon, Arctovish, Arctozolt, Barraskewda, Boltund, Centiskorch, Cinderace, Coalossal, Copperajah, Corviknight, Cramorant, Dracovish, Dracozolt, Dragapult, Drednaw, Dubwool, Eiscue, Eldegoss, Falinks, Flapple, Frosmoth, Grapploct, Greedent, Grimmsnarl, Hatterene, Hydrapple, Inteleon, Morpeko, Orbeetle, Pincurchin, Polteageist, Rillaboom, Sandaconda, Stonjourner, Thievul, Toxtricity

### Gen 9 (Paldea)  (40)

Arboliva, Armarouge, Baxcalibur, Bellibolt, Bombirdier, Brambleghast, Ceruledge, Cetitan, Cyclizar, Dachsbun, Dondozo, Espathra, Flamigo, Garganacl, Gholdengo, Glimmora, Grafaiai, Houndstone, Kilowattrel, Klawf, Lokix, Mabosstiff, Maushold, Meowscarada, Orthworm, Palafin, Pawmot, Quaquaval, Rabsca, Revavroom, Scovillain, Sinistcha, Skeledirge, Spidops, Squawkabilly, Tatsugiri, Tinkaton, Toedscruel, Veluza, Wugtrio

## B. Regional-form finals (all included as separate entries)

**Alolan (10):** Dugtrio (Alolan), Exeggutor (Alolan), Golem (Alolan), Marowak (Alolan), Muk (Alolan), Ninetales (Alolan), Persian (Alolan), Raichu (Alolan), Raticate (Alolan), Sandslash (Alolan)

**Galarian (9):** Articuno (Galarian), Darmanitan (Galarian), Moltres (Galarian), Rapidash (Galarian), Slowbro (Galarian), Slowking (Galarian), Stunfisk (Galarian), Weezing (Galarian), Zapdos (Galarian)

**Hisuian (10):** Arcanine (Hisuian), Avalugg (Hisuian), Braviary (Hisuian), Decidueye (Hisuian), Electrode (Hisuian), Goodra (Hisuian), Lilligant (Hisuian), Samurott (Hisuian), Typhlosion (Hisuian), Zoroark (Hisuian)

**Paldean (3):** Tauros (Paldean Combat), Tauros (Paldean Blaze), Tauros (Paldean Aqua)

## C. Alternate battle formes (non-legendary)

Distinct type/stat/movepool formes kept as separate rentals; in-battle-only and cosmetic sisters collapsed.

Basculegion (Female), Basculegion (Male), Indeedee (Female), Indeedee (Male), Lycanroc (Dusk), Lycanroc (Midnight), Meowstic (Female), Meowstic (Male), Oinkologne (Female), Oinkologne (Male), Oricorio (Baile), Oricorio (Pa'u), Oricorio (Pom-Pom), Oricorio (Sensu), Rotom (Fan), Rotom (Frost), Rotom (Heat), Rotom (Mow), Rotom (Wash), Toxtricity (Low-Key), Ursaluna (Bloodmoon), Wormadam (Plant), Wormadam (Sandy), Wormadam (Trash)

## D. Restricted tier (gated to hard mode / capped per team - your call)

### Restricted Legendaries (box/uber)  (38)

Calyrex, Calyrex (Ice Rider), Calyrex (Shadow Rider), Dialga, Dialga (Origin), Eternatus, Giratina, Giratina (Origin), Groudon, Ho-Oh, Koraidon, Kyogre, Kyurem, Kyurem (White), Kyurem (Black), Lugia, Lunala, Mewtwo, Miraidon, Necrozma, Necrozma (Dusk Mane), Necrozma (Dawn Wings), Palkia, Palkia (Origin), Rayquaza, Reshiram, Solgaleo, Terapagos, Xerneas, Yveltal, Zacian, Zacian (Crowned), Zamazenta, Zamazenta (Crowned), Zekrom, Zygarde, Zygarde (10%), Zygarde (Complete)

### Sub-Legendaries  (45)

Articuno, Azelf, Chi-Yu, Chien-Pao, Cobalion, Cresselia, Enamorus, Enamorus (Therian), Entei, Fezandipiti, Glastrier, Heatran, Landorus, Landorus (Therian), Latias, Latios, Mesprit, Moltres, Munkidori, Okidogi, Raikou, Regice, Regidrago, Regieleki, Regigigas, Regirock, Registeel, Spectrier, Suicune, Tapu Bulu, Tapu Fini, Tapu Koko, Tapu Lele, Terrakion, Thundurus, Thundurus (Therian), Ting-Lu, Tornadus, Tornadus (Therian), Urshifu (Single Strike), Urshifu (Rapid Strike), Uxie, Virizion, Wo-Chien, Zapdos

### Mythicals  (26)

Celebi, Darkrai, Deoxys, Deoxys (Attack), Deoxys (Defense), Deoxys (Speed), Diancie, Hoopa, Hoopa (Unbound), Jirachi, Keldeo, Magearna, Manaphy, Marshadow, Melmetal, Meloetta, Meltan, Mew, Pecharunt, Phione, Shaymin, Shaymin (Sky), Victini, Volcanion, Zarude, Zeraora

### Paradox  (20)

Brute Bonnet, Flutter Mane, Gouging Fire, Great Tusk, Iron Boulder, Iron Bundle, Iron Crown, Iron Hands, Iron Jugulis, Iron Leaves, Iron Moth, Iron Thorns, Iron Treads, Iron Valiant, Raging Bolt, Roaring Moon, Sandy Shocks, Scream Tail, Slither Wing, Walking Wake

### Ultra Beasts  (10)

Blacephalon, Buzzwole, Celesteela, Guzzlord, Kartana, Naganadel, Nihilego, Pheromosa, Stakataka, Xurkitree

## E. Eviolite NFE (curated - not fully evolved, but viable with Eviolite)

Held-item **Eviolite** (exists in this build) boosts Def/SpDef of not-fully-evolved mons. Curated competitive picks:

| Pokemon | Intro | Typical role |
|---|---|---|
| Chansey | Gen 1 | Premier special wall + Wish/Seismic Toss cleric |
| Porygon2 | Gen 1 | Bulky Trace/Download pivot, Recover + BoltBeam |
| Dusclops | Gen 3 | Ghost wall, Will-O-Wisp/Night Shade/Pain Split |
| Gligar | Gen 4 | Bulky Ground/Flying, Roost + Defog/hazards |
| Scyther | Gen 1 | Technician/Swords Dance offensive pivot |
| Rhydon | Gen 1 | Physical Ground/Rock tank, Stealth Rock |
| Magneton | Gen 1 | Analytic/Magnet Pull trapper, special attacker |
| Doublade | Gen 6 | Steel/Ghost physical wall, Swords Dance |
| Type: Null | Gen 7 | Bulky Normal, Rest/Sleep-Talk pivot |
| Sneasel | Gen 2 | Fast physical Dark/Ice, Swords Dance |
| Sneasel (Hisuian) | Gen 8 | Fast Fighting/Poison, Gunk Shot/Close Combat |
| Piloswine | Gen 2 | Ice/Ground tank, Stealth Rock + Ice Shard |
| Gurdurr | Gen 5 | Guts/Iron Fist wall, Drain Punch/Mach Punch |
| Vullaby | Gen 5 | Bulky Dark/Flying, Roost + Foul Play/Defog |
| Bisharp | Gen 5 | Defiant/Swords Dance sweeper (NFE -> Kingambit) |
| Misdreavus | Gen 2 | Fast Ghost utility, Nasty Plot or screens |
| Murkrow | Gen 2 | Prankster support, Tailwind/Thunder Wave |
| Roselia | Gen 3 | Grass/Poison Spikes + Sludge Bomb, Natural Cure |
| Togetic | Gen 2 | Nasty Plot/Serene Grace support |
| Golbat | Gen 1 | Bulky Poison/Flying, Roost + Brave Bird/Defog |
| Haunter | Gen 1 | Fast special Ghost, Substitute + Hex |
| Pupitar | Gen 2 | Dragon Dance sweeper, Stealth Rock |
| Metang | Gen 3 | Steel/Psychic physical tank, Bullet Punch |
| Shelgon | Gen 3 | Dragon Dance / bulky Dragon |
| Fraxure | Gen 5 | Dragon Dance physical sweeper |
| Kadabra | Gen 1 | Fast special Psychic, Nasty Plot |
| Dragonair | Gen 1 | Dragon Dance / bulky utility, Wish |
| Electabuzz | Gen 1 | Fast special Electric pivot, Volt Switch |
| Magmar | Gen 1 | Special Fire pivot, Flamethrower/Focus Blast |
| Clefairy | Gen 1 | Magic Guard cleric, dual screens |
| Onix | Gen 1 | Sturdy Stealth Rock lead, physical wall |
| Duosion | Gen 5 | Regenerator/Magic Guard wall, Calm Mind |
| Rufflet | Gen 5 | Physical Flying, Bulk Up + Brave Bird |
| Kirlia | Gen 3 | Special Psychic/Fairy, Calm Mind |

## F. Moveset sources (for the next phase)

Movesets will be transcribed from these as-is (build-legality flagged later). **Platinum Kaizo dropped** - its moves are rebalanced and not representative of this build.

**Hard-hack docs (primary flavor for a hard-but-fair tower):**
- **Emerald Kaizo** - trainer/boss set documents (community moveset spreadsheets & the Kaizo doc)
- **Run & Bun** - the run's official set document (per-Pokemon movesets, items, spreads)

**Online set databases:**
- Smogon University - https://www.smogon.com/  (per-generation analyses & sets, Gen 1-9)
- Smogon sets data (raw) - https://pkmn.github.io/smogon/data/sets/
- Pokemon Showdown teambuilder / import-export - https://play.pokemonshowdown.com/
- Pikalytics (modern-meta usage sets) - https://www.pikalytics.com/
- Serebii Attackdex / learnsets - https://www.serebii.net/games/moveset.shtml
- Victory Road (VGC rental sets) - https://victoryroad.pro/sv-rental-teams/

## G. Excluded / collapsed (for transparency)

- **Gimmick formes (excluded entirely):** all `*_MEGA`, `*_PRIMAL`, `*_GMAX` (gimmicks OFF).
- **In-battle-only transforms (collapsed to base):** Aegislash Blade, Darmanitan Zen, Cramorant Gorging/Gulping, Eiscue Noice, Morpeko Hangry, Palafin Hero, Mimikyu Busted, Wishiwashi School, Meloetta Pirouette, Cherrim Sunshine, Castform weather forms, Xerneas Active, Terapagos Terastal/Stellar, Eternatus Eternamax, Necrozma Ultra.
- **Cosmetic-only variants (collapsed to one):** Vivillon patterns, Florges/Floette/Flabebe colors, Squawkabilly colors, Tatsugiri styles, Gastrodon/Sawsbuck/Gourgeist/Deerling variants, Pikachu costumes, Sinistcha/Polteageist authenticity, Maushold/Dudunsparce segments, Zarude Dada, Magearna Original, Greninja Ash/Battle Bond, Keldeo Resolute.

## Decisions locked

**Tower modes (restricted-tier gating):** three selectable modes -
- **Mode 1 - Standard:** 0 restricted mons per team (roster = standard + regional + alt formes + Eviolite NFE).
- **Mode 2 - Restricted x1:** up to 1 restricted-tier mon (legendary/mythical/paradox/UB) per team of 3.
- **Mode 3 - Restricted x2:** up to 2 restricted-tier mons per team of 3.

**Gendered formes:** keep both M/F as separate rentals (Indeedee, Meowstic, Basculegion, Oinkologne).

**Movesets per Pokemon:** aim for 2-3 distinct sets each; add more when a Pokemon genuinely supports more play styles that feel diverse from each other. Popular/versatile mons may reach 5-8 sets. Sets are transcribed from the sources as-is.

**Eviolite NFE:** keep all curated entries in.

**Moveset storage:** structured JSON data files (per generation / batch), converted into the tower's mon table later. Planned per-set schema:

```json
{
  "species": "SPECIES_GARCHOMP",
  "displayName": "Garchomp",
  "tier": "standard",
  "sets": [
    {
      "name": "Swords Dance sweeper",
      "role": "physical setup sweeper",
      "item": "ITEM_LIFE_ORB",
      "ability": "ABILITY_ROUGH_SKIN",
      "nature": "NATURE_JOLLY",
      "evs": { "hp": 0, "atk": 252, "def": 0, "spatk": 0, "spdef": 4, "speed": 252 },
      "ivs": {},
      "moves": ["MOVE_SWORDS_DANCE", "MOVE_EARTHQUAKE", "MOVE_SCALE_SHOT", "MOVE_FIRE_FANG"],
      "source": "Run & Bun",
      "notes": ""
    }
  ]
}
```

Constants (species/move/item/ability/nature) will be validated against this build during a later pass; sets are transcribed from the sources as-is first.

## Still needed to start the moveset phase

- The **Emerald Kaizo** and **Run & Bun** set documents (files or links) - these are transcribed as-is and cannot be reliably reproduced from memory.
- Confirmation of the batching approach (suggest one generation at a time, Standard roster first, then Regional/Alt, then Restricted tier, then Eviolite).

