public OnGameModeInit()
{
  // Initialize a pickup weapon's iterator.
  Iter_Init(gPickupWeapons);

  // Show all player's markers.
  ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
  // Show player's name tags.
  ShowNameTags(1);
  // Set distance that player can see other player's name tags.
  SetNameTagDrawDistance(40.0);
  // Disabled stunt bonus like in Singleplayer.
  EnableStuntBonusForAll(0);
  // Disabled interior pickups for enter-exit building.
  DisableInteriorEnterExits();
  // Set a nice weather.
  SetWeather(2);

  // Add a class for player's skin.
  AddPlayerClass(1,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
  return 1;
}

public OnGameModeExit()
{
  print("Gamemode ended.");
  return 1;
}

public OnPlayerConnect(playerid)
{
  ResetPlayerScoreEx(playerid);
  return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
  return 1;
}

public OnPlayerSpawn(playerid)
{
  // Get a random spawn point from spawn points.
  new randSpawn = random(sizeof(gRandomSpawns_LosSantos));
  // Set player position to the selected spawn point.
  SetPlayerPos(playerid,
    gRandomSpawns_LosSantos[randSpawn][0],
    gRandomSpawns_LosSantos[randSpawn][1],
    gRandomSpawns_LosSantos[randSpawn][2]);
  // Set player facing angle (the ped, not the camera).
  SetPlayerFacingAngle(playerid, gRandomSpawns_LosSantos[randSpawn][3]);

  // Set player weapon's skills
  SetPlayerWeaponSkills(playerid);
  // Give some weapons to the player.
  GivePlayerWeapons(playerid);

  return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
  // Set victim's score to zero.
  ResetPlayerScoreEx(playerid);
  // Add score by 1 who killed a player.
  AddPlayerScoreEx(killerid, 1);
  // Drop player weapons.
  DropPlayerWeapons(playerid);

  return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
  // Just in case... We get the current weapon that player holds right now.
  new curWeapon = GetPlayerWeapon(playerid);

  // Loop each global pickup weapons.
  foreach(new p : PickupWeapons)
  {
    // Check the Pickup ID.
    if (p == pickupid)
    {
      P:4("Pick Up --> Pickup ID: %d | Weapon ID: %d | Ammo: %d", p, gPickupWeapons[p][WeaponID], gPickupWeapons[p][Ammo]);
      // Stop the timer.
      stop gPickupWeapons[p][Gone];
      // Remove the pickup.
      DestroyPickup(pickupid);

      // Give the weapon.
      GivePlayerWeapon(playerid, gPickupWeapons[p][WeaponID], gPickupWeapons[p][Ammo]);
      // Set the weapon back to current arming.
      GivePlayerWeapon(playerid, curWeapon, 0);

      // Remove the item from iterator.
      Iter_Remove(PickupWeapons, p);
      // Stop the loop.
      break;
    }
  }

  return 1;
}