YCMD:dropweapon(playerid, params[], help) 
{
  DropPlayerWeapons(playerid);
  return 1;
}

YCMD:register(playerid, params[], help) {
  P:4("/register -> called.");

  new
    username[25],
    password[65];

  if (help || sscanf(params, "s[24] s[64]", username, password))
  {
    SendClientMessage(playerid, X11_WHITE, "* USAGE: /register [username] [password]");
    SendClientMessage(playerid, X11_WHITE, "* FUNCTION: Register a new account.");
    return 1;
  }

  // Register the account.
  // new register = CallRemoteFunction("CreatePlayerAccount", "sss", username, password, "test@gmail.com");
  new register = broadcastfunc CreatePlayerAccount(username, password, "test@gmail.com");

  P:4("CreatePlayerAccount -> called. Return: %i", register);

  if (register == E_USERNAME_REQUIRED) {
    SendClientMessage(playerid, X11_RED, "* ERROR: Username is required.");
    return 1;
  }

  if (register == E_PASSWORD_REQUIRED) {
    SendClientMessage(playerid, X11_RED, "* ERROR: Password is required.");
    return 1;
  }

  if (register == E_EMAIL_REQUIRED) {
    SendClientMessage(playerid, X11_RED, "* ERROR: E-mail address is required.");
    return 1;
  }

  if (register == E_INSUFFICIENT_PASSWORD_LENGTH) {
    SendClientMessage(playerid, X11_RED, "* ERROR: Insufficient password length.");
    return 1;
  }

  if (register == E_EXCEED_PASSWORD_LENGTH) {
    SendClientMessage(playerid, X11_RED, "* ERROR: Exceeded password length.");
    return 1;
  }

  if (register == E_USERNAME_EXIST) {
    SendClientMessage(playerid, X11_RED, "* ERROR: Username already exists.");
    return 1;
  }

  if (register != 1) {
    P:E("CreatePlayerAccount -> return unknown code: %i", register);
    SendClientMessage(playerid, X11_RED, "* ERROR: Something wrong happen while creating a new account.");
    return 1;
  }

  SendClientMessage(playerid, X11_WHITE, "* INFO: Account created successfully.");
  return 1;
}