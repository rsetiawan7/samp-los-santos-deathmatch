new 
  // For handle DB connection.
  DB:gVehicleConnection,
  // For static vehicles' iteration.
  Iterator:StaticVehicles<MAX_VEHICLES>;

hook OnGameModeInit()
{
  // Initialize static vehicles' iteration.
  Iter_Init(StaticVehicles);

  // Initialize to load static vehicles from database.
  LoadVehicleInit();
}

hook OnGameModeExit()
{
  // Unload some static vehicles.
  LoadVehicleExit();
}

LoadVehicleDatabase()
{
  P:4("LoadVehicleDatabase called");
  // Store query result.
  static 
    DBResult:result;

  // Get all vehicles in `los_santos` table. It means get all vehicle that located in Los Santos.
  result = db_query(gVehicleConnection, "SELECT * FROM `los_santos`");

// Debugger will return available vehicles in table.
  P:4("Query result (vehicles.db): %i rows.", db_num_rows(result));
  // Process to next step IF has the result.
  if (db_num_rows(result))
  {
    // Store some vehicle property, like model, position (x, y, z, a (angle/rotation)), and its colors.
    new
      TotalVehicles = db_num_rows(result),
      VID,
      model,
      Float:x,
      Float:y,
      Float:z,
      Float:r,
      color1,
      color2;

    do
    {
      // Get current row result, based on field name.
      model = db_get_field_assoc_int(result, "model");
      x = db_get_field_assoc_float(result, "x");
      y = db_get_field_assoc_float(result, "y");
      z = db_get_field_assoc_float(result, "z");
      r = db_get_field_assoc_float(result, "r");
      color1 = db_get_field_assoc_int(result, "color1");
      color2 = db_get_field_assoc_int(result, "color2");

      // Spawn the vehicle with max idle 1,800 seconds (30 minutes).
      VID = AddStaticVehicleEx(model, x, y, z, r, color1, color2, 1800, 0);
      P:4("Static vehicle: %i %.2f %.2f %.2f", model, x, y, z);

      // Add that vehicle to iterator.
      Iter_Add(StaticVehicles, VID);
    }
    // Read next row.
    while(db_next_row(result));

    // Free the result to avoid memory leakage.
    db_free_result(result);
    // Print amount of static vehicles spawned.
    printf("Total static vehicles: %i", TotalVehicles);
  }
}

LoadVehicleInit()
{
  // Read .db file.
  gVehicleConnection = db_open("lsdm/vehicles.db");

  if (gVehicleConnection == DB:0)
  {
    // There's something error IF the script cannot connect to DB file.
    print("Failed to open a connection to \"vehicles.db\".");
  }
  else {
    // Success connect to DB file.
    print("Successfully created a connection to \"vehicles.db\".");
    // Run some query to create tables IF not available.
    db_free_result(db_query(gVehicleConnection, "\
    CREATE TABLE IF NOT EXISTS los_santos \
    (id INTEGER PRIMARY KEY ASC AUTOINCREMENT NOT NULL,\
    model INTEGER (5) NOT NULL,\
    x FLOAT NOT NULL,\
    y FLOAT NOT NULL,\
    z FLOAT NOT NULL,\
    r FLOAT NOT NULL,\
    color1 TINYINT (3),\
    color2 TINYINT (3),\
    enabled BOOLEAN NOT NULL DEFAULT true);"));

    // Run function to load static vehicles from database.
    LoadVehicleDatabase();
  }

  return 1;
}

LoadVehicleExit()
{
  // Just close the DB connection IF its a valid connection.
  if (gVehicleConnection) db_close(gVehicleConnection);

  // Loop each StaticVehicle iterator.
  foreach (new v : StaticVehicles)
  {
    // Destroy the vehicle.
    DestroyVehicle(v);

    // Remove it from iterator.
    Iter_Remove(StaticVehicles, v);
  }
  return 1;
}

#include <YSI-Coding/y_hooks>