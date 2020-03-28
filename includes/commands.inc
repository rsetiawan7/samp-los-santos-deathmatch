YCMD:dropweapon(playerid, params[], help) 
{
  DropPlayerWeapons(playerid);
  return 1;
}

YCMD:logout(playerid, params[], help)
{
  P:4("/logout -> called.");

  if (help)
  {
    SendInformationMessage(playerid, "* USAGE: /logout");
    SendInformationMessage(playerid, "* FUNCTION: Log out from this account.");
    return 1;
  }

  new logout = LogOutFromPlayerAccount(playerid);
  P:4("LogOutFromPlayerAccount -> called. Return: %i", logout);
  
  if (logout == E_PLAYER_NOT_LOGGED_IN)
  {
    SendErrorMessage(playerid, "You're not logged in right now.");
    return 1;
  }

  if (logout != 1) {
    P:E("LogOutPlayerAccount -> return unknown code: %i", logout);
    SendErrorMessage(playerid, "* ERROR: Something wrong happened while logging out from this account.");
    return 1;
  }

  SendInformationMessage(playerid, "* INFO: Log out successfully.");
  return 1;
}

YCMD:login(playerid, params[], help)
{
  P:4("/login -> called.");

  new
    username[25],
    password[65];

  if (help || sscanf(params, "s[24] s[64]", username, password))
  {
    SendInformationMessage(playerid, "* USAGE: /login [username] [password]");
    SendInformationMessage(playerid, "* FUNCTION: Log in to an account.");
    return 1;
  }

  new login = LogInPlayerAccount(playerid, username, password);
  P:4("LogInPlayerAccount -> called. Return: %i", login);

  if (login == E_PLAYER_ALREADY_LOGGED_IN)
  {
    SendErrorMessage(playerid, "* ERROR: You're alread logged in.");
    return 1;
  }

  if (login == E_INVALID_CREDENTIAL)
  {
    SendErrorMessage(playerid, "* ERROR: Invalid username or password.");
    return 1;
  }

  if (login != 1) {
    P:E("LogInPlayerAccount -> return unknown code: %i", login);
    SendErrorMessage(playerid, "* ERROR: Something wrong happened while logging in to an account.");
    return 1;
  }

  SendInformationMessage(playerid, "* INFO: Log in successfully.");
  return 1;
}

YCMD:register(playerid, params[], help)
{
  P:4("/register -> called.");

  new
    username[25],
    password[65];

  if (help || sscanf(params, "s[24] s[64]", username, password))
  {
    SendInformationMessage(playerid, "* USAGE: /register [username] [password]");
    SendInformationMessage(playerid, "* FUNCTION: Register a new account.");
    return 1;
  }

  // Register the account.
  new register = CreatePlayerAccount(username, password, "test@gmail.com");

  P:4("CreatePlayerAccount -> called. Return: %i", register);

  if (register == E_USERNAME_REQUIRED) {
    SendErrorMessage(playerid, "* ERROR: Username is required.");
    return 1;
  }

  if (register == E_PASSWORD_REQUIRED) {
    SendErrorMessage(playerid, "* ERROR: Password is required.");
    return 1;
  }

  if (register == E_EMAIL_REQUIRED) {
    SendErrorMessage(playerid, "* ERROR: E-mail address is required.");
    return 1;
  }

  if (register == E_INSUFFICIENT_PASSWORD_LENGTH) {
    SendErrorMessage(playerid, "* ERROR: Insufficient password length.");
    return 1;
  }

  if (register == E_EXCEED_PASSWORD_LENGTH) {
    SendErrorMessage(playerid, "* ERROR: Exceeded password length.");
    return 1;
  }

  if (register == E_USERNAME_EXIST) {
    SendErrorMessage(playerid, "* ERROR: Username already exists.");
    return 1;
  }

  if (register == E_EMAIL_EXIST) {
    SendErrorMessage(playerid, "* ERROR: E-mail address already exists.");
    return 1;
  }

  if (register != 1) {
    P:E("CreatePlayerAccount -> return unknown code: %i", register);
    SendErrorMessage(playerid, "* ERROR: Something wrong happened while creating a new account.");
    return 1;
  }

  SendInformationMessage(playerid, "* INFO: Account created successfully.");
  return 1;
}