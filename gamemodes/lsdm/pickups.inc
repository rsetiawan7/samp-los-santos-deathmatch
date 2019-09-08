#define MAX_ARMOUR_REGENERATION   10
#define MAX_HEALTH_REGENERATION   10
#define TIME_TO_WAIT_REGENERATION 3

// Pickup model: 1240
new Float:gHealthPickupsLS[][4] = {
  { 2102.67603, -1808.99146, 13.65605 },
  { 2378.94116, -1909.22058, 13.41560 },
  { 2314.71021, -1631.99902, 14.51910 },
  { 2409.92114, -1489.33142, 23.83190 },
  { 2190.46387, -1152.57654, 33.54645 },
  { 1969.48730, -1177.15784, 19.92809 },
  { 2041.03748, -1410.63904, 17.16961 },
  { 1178.92285, -1330.34216, 13.82463 },
  { 1029.01086, -1363.66577, 13.47772 },
  {  905.76813, -1369.03430, 24.99121 },
  { 1193.47839,  -917.26776, 43.37333 },
  {  815.75641, -1092.93359, 25.59246 },
  {  672.96924, -1864.82739,  5.56469 },
  {  356.00241, -2026.47925,  7.64442 },
  {  501.96591, -1044.75806, 97.87703 },
  {  671.68878,  -458.17197, 16.84747 },
  {  218.94559,  -166.56998,  1.96889 },
  {  245.37750,   -43.74683,  1.69255 }
};

// Pickup model: 1242
new Float:gArmourPickupsLS[][4] = {
  { 2552.16040, -1733.91162,  6.40766 },
  { 2195.91260, -1152.74365, 33.63910 },
  { 1971.78943, -1222.89807, 19.92671 },
  { 1552.50452, -1637.67102,  6.01795 },
  { 1250.21753, -1505.65247, 10.15575 },
  {  815.77203, -1108.34778, 25.59046 },
  {  733.25549, -1358.27710, 23.50508 },
  {  673.43573, -1869.83459,  5.47446 },
  {  614.28522,  -584.11292, 17.73760 },
  {  674.30951,  -452.83090, 20.55672 },
  {  255.22401,  -163.48553,  1.68849 }
};

new
  BitArray:CanRegeneration<MAX_PLAYERS>,
  Iterator:ArmourPickups<MAX_PICKUPS>,
  Iterator:HealthPickups<MAX_PICKUPS>;

timer CooldownRegeneration[TIME_TO_WAIT_REGENERATION * 1000](playerid)
{
  SetRegenerationAbility(playerid, true);
}

SetRegenerationAbility(playerid, bool:status)
{
  if (status == true)
  {
    Bit_Let(CanRegeneration, playerid);
  }
  else
  {
    Bit_Vet(CanRegeneration, playerid);
  }

  P:4("Regeneration ability to PlayerID %i set to %s", playerid, (status == true ? "TRUE" : "FALSE"));
}

RegenerationPlayerArmour(playerid)
{
  new
    Float:armour,
    Float:newArmour,
    Float:regenAmount;

  GetPlayerArmour(playerid, armour);

  if (armour < 100.0)
  {
    SetRegenerationAbility(playerid, false);

    regenAmount = (armour + MAX_ARMOUR_REGENERATION);
    newArmour = regenAmount > 100.0 ? 100.0 : regenAmount;
    P:4("PlayerID %i set a new armour from regeneration to %.2f points.", playerid, newArmour);
    SetPlayerArmour(playerid, newArmour);

    defer CooldownRegeneration(playerid);
  }
}

RegenerationPlayerHealth(playerid)
{
  new
    Float:health,
    Float:newHealth,
    Float:regenAmount;

  GetPlayerHealth(playerid, health);

  if (health < 100.0)
  {
    SetRegenerationAbility(playerid, false);

    regenAmount = (health + MAX_HEALTH_REGENERATION);
    newHealth = regenAmount > 100.0 ? 100.0 : regenAmount;
    P:4("PlayerID %i set a new health from regeneration to %.2f points.", playerid, newHealth);
    SetPlayerHealth(playerid, newHealth >= 100.0 ? 100.0 : newHealth);

    defer CooldownRegeneration(playerid);
  }
}

hook OnGameModeInit()
{
  // Initialize iterator pickups.
  Iter_Init(ArmourPickups);
  Iter_Init(HealthPickups);

  // Iteration for armour pickups.
  for (new a = 0; a < sizeof(gArmourPickupsLS); a++)
  {
    new pickup = CreatePickup(1242, 1, gArmourPickupsLS[a][0], gArmourPickupsLS[a][1], gArmourPickupsLS[a][2], 0);
    Iter_Add(ArmourPickups, pickup);
  }

  // Iteration for health pickups.
  for (new h = 0; h < sizeof(gHealthPickupsLS); h++)
  {
    new pickup = CreatePickup(1240, 1, gHealthPickupsLS[h][0], gHealthPickupsLS[h][1], gHealthPickupsLS[h][2], 0);
    Iter_Add(HealthPickups, pickup);
  }

  return 1;
}

hook OnGameModeExit()
{
  foreach (new a : ArmourPickups)
  {
    DestroyPickup(a);
    Iter_Remove(ArmourPickups, a);
  }

  foreach (new h : HealthPickups)
  {
    DestroyPickup(h);
    Iter_Remove(HealthPickups, h);
  }

  Iter_Clear(ArmourPickups);
  Iter_Clear(HealthPickups);

  return 1;
}

hook OnPlayerConnect(playerid)
{
  SetRegenerationAbility(playerid, true);
}

// Callback for handle armour & health pickups.
hook OnPlayerPickUpPickup(playerid, pickupid)
{
  if (Bit_Get(CanRegeneration, playerid) == true)
  {
    if (Iter_Contains(ArmourPickups, pickupid)) 
    {
      RegenerationPlayerArmour(playerid);
    } 
    else if (Iter_Contains(HealthPickups, pickupid))
    {
      RegenerationPlayerHealth(playerid);
    }
  }

  return 1;
}

#include <YSI-Coding/y_hooks>