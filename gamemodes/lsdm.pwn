// SA-MP Core
#include <a_samp>

// Debug level. Comment line below to disable debugging.
#define _DEBUG 4

// Third-party includes
#include <sscanf2>
#include <YSI-Data/y_bit>
#include <YSI-Core/y_debug>
#include <YSI-Data/y_iterate>
#include <YSI-Server/y_colors>
#include <YSI-Coding/y_timers>
#include <YSI-Visual/y_commands>

// Account System
// #define MASTER 4
// #define YSI_IS_CLIENT
// #include <YSI-Core/y_master>
#include "../includes/account-system.inc"

// Enumerations
#include "lsdm/enumerations.inc"

// Variables
#include "lsdm/variables.inc"

// In-game stuffs
#include "lsdm/pickups.inc"
#include "lsdm/spawnpoints.inc"
#include "lsdm/vehicles.inc"

// Commands (for debugging purposes)
#include <YSI-Core/y_master>
#include "lsdm/commands.inc"

// Main Function
main()
{
  print("\n----------------------------------");
  print("   Los Santos Deathmatch\n");
  print("         Written by");
  print("         rsetiawan7");
  print("----------------------------------\n");
}

// Functions
#include "lsdm/functions.inc"

// Callbacks
#include "lsdm/callbacks.inc"

// Timers
#include "lsdm/timers.inc"