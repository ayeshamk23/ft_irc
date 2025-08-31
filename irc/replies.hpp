#define once
#define CRLF "\r\n"
#define ERR_NOTENOUGHPARAMS(nickname), (": 461 " + nickname + ":Not enough parameters" + CRLF)
#define ERR_PASSWDMISMATCH(nickname), (": 464 " + nickname + ":Password incorrect" + CRLF)
#define ERR_ALREADYREGISTRED(nickname), (": 462 " + nickname + ":Unauthorized command (already registered)" + CRLF)