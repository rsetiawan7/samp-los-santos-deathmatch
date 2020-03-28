#include <YSI_Coding\y_va>

SendInformationMessage(playerid, const string:text[], va_args<>)
{
  new str[160];
  va_format(str, sizeof(str), text, va_start<2>);
  return SendClientMessage(playerid, X11_WHITE, str);
}

SendErrorMessage(playerid, const string:text[], va_args<>)
{
  new str[160];
  va_format(str, sizeof(str), text, va_start<2>);
  return SendClientMessage(playerid, X11_RED, str);
}

ResetPlayerScoreEx(playerid)
{
  // Set player score to zero.
  gPlayerScore[playerid] = 0;
  UpdatePlayerScore(playerid);
}

AddPlayerScoreEx(playerid, score)
{
  // Add score by score amount given.
  gPlayerScore[playerid] += score;
  UpdatePlayerScore(playerid);
}

UpdatePlayerScore(playerid)
{
  // Update the scoreboard.
  SetPlayerScore(playerid, gPlayerScore[playerid]);
}

GivePlayerWeapons(playerid)
{
  // Give a Grenade with 500 ammunitions.
  GivePlayerWeapon(playerid, 16, 500);
  // Give a Desert Eagle with 500 ammunitions.
  GivePlayerWeapon(playerid, 24, 500);
  // Give a Shotgun with 500 ammunitions.
  GivePlayerWeapon(playerid, 25, 500);
  // Give a MP5 with 2,500 ammunitions.
  GivePlayerWeapon(playerid, 29, 2500);
  // Give a AK-47 with 1,500 ammunitions.
  GivePlayerWeapon(playerid, 30, 2500);
  // Give a Coutry Rifle (Rifle) with 500 ammunitions.
  GivePlayerWeapon(playerid, 33, 500);
}

SetPlayerWeaponSkills(playerid)
{
  // Set Desert Eagle's weapon skill to player with maximum skill point (Hitman level).
  SetPlayerSkillLevel(playerid, 2, 1000);
  // Set Shotgun's weapon skill to player with maximum skill point (Hitman level).
  SetPlayerSkillLevel(playerid, 3, 1000);
  // Set MP5's weapon skill to player with maximum skill point (Hitman level).
  SetPlayerSkillLevel(playerid, 7, 1000);
  // Set AK-47's weapon skill to player with maximum skill point (Hitman level).
  SetPlayerSkillLevel(playerid, 8, 1000);
}

CreateWeaponPickupFromPlayer(playerid, weaponid, ammo)
{
  // Variable to store player position. It used as pickup weapons.
  new
    PickupID = -1,
    Float:X,
    Float:Y,
    Float:Z;
  // Store player position
  GetPlayerPos(playerid, X, Y, Z);

  // Set random coordinate from player position to make sure the pickup not stacked.
  X = X + random(4) - random(4);
  Y = Y + random(4) - random(4);
  // Add a pickup with specific model, based on weapon IDs. This pickup placed above 0.3 point from playerid.
  Z = Z + 0.3;

  switch(weaponid)
  {
    case 16: PickupID = CreatePickup(342, gWeaponPickupType, X, Y, Z, 0);
    case 24: PickupID = CreatePickup(348, gWeaponPickupType, X, Y, Z, 0);
    case 25: PickupID = CreatePickup(349, gWeaponPickupType, X, Y, Z, 0);
    case 29: PickupID = CreatePickup(353, gWeaponPickupType, X, Y, Z, 0);
    case 30: PickupID = CreatePickup(355, gWeaponPickupType, X, Y, Z, 0);
    case 33: PickupID = CreatePickup(357, gWeaponPickupType, X, Y, Z, 0);
  }

  // Only drop a valid weapons.
  if (PickupID >= 0) {
    // Set the weapon ID.
    gPickupWeapons[PickupID][WeaponID] = weaponid;
    // Set the ammo. We just pick 10% of the total dropped ammo.
    gPickupWeapons[PickupID][Ammo] = ammo / 10;
    // Set timer pickup alive.
    gPickupWeapons[PickupID][Gone] = defer RemoveWeaponPickup(PickupID);
    // Add the information to the iterator.
    Iter_Add(PickupWeapons, PickupID);

    P:4("Drop --> Pickup ID: %d | Weapon ID: %d | Ammo: %d", PickupID, weaponid, ammo);
  } else {
    P:4("Not dropped --> Weapon ID: %d | Ammo: %d", weaponid, ammo);
  }
}

DropPlayerWeapons(playerid)
{
  for (new s = 0; s < sizeof(gAcknowledgeWeaponSlots); s++)
  {
    // Variable to store weapon ID and its ammo.
    new
      weaponid,
      ammo;
    // Get weapon ID and its ammo based on its slot. Actually, the ammo is not used right now.
    GetPlayerWeaponData(playerid, gAcknowledgeWeaponSlots[s], weaponid, ammo);

    // Loop each dropable weapons.
    for (new w = 0; w < sizeof(gDropableWeapons); w++)
    {
      // Check IF the Weapon ID is dropable and the ammo more than 0.
      // Read more: https://wiki.sa-mp.com/wiki/GetPlayerWeaponData
      if (weaponid == gDropableWeapons[w] && ammo > 0)
      {
        // Create the pickup and get to the next acknowledge weapon slot.
        CreateWeaponPickupFromPlayer(playerid, weaponid, ammo);
        break;
      }
    }
  }
}