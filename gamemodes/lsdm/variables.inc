// Time to alive for weapon pickups (in seconds).
new MAXIMUM_PICKUP_TIME_ALIVE = 30;

// Used for determine pickup type for weapon pickups (dropped from a dead player).
new gWeaponPickupType = 19;

// Dropable weapons (Weapon IDs) from a dead player.
new gDropableWeapons[6] = { 16, 24, 25, 29, 30, 33 };

// Slot weapon that acknowledged by script. Prevent someone to drop other slots.
new gAcknowledgeWeaponSlots[6] = { 2, 3, 4, 5, 6, 8 };

// Create an array to store pickup weapons.
new gPickupWeapons[MAX_PICKUPS][e_PickupWeapons];

// Create an iterator for store pickup weapons.
new Iterator:PickupWeapons<MAX_PICKUPS>;

// Store players' score.
new gPlayerScore[MAX_PLAYERS];