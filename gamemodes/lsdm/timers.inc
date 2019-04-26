// This function will be executed after time to alive for weapon pickup is over.
timer RemoveWeaponPickup[MAXIMUM_PICKUP_TIME_ALIVE * 1000](pickupid)
{
  P:4("Pickup gone --> PickupID: %d", pickupid);
  
  // Remove from iterator.
  Iter_Remove(PickupWeapons, pickupid);
  // Destroy the pickup.
  DestroyPickup(pickupid);
}