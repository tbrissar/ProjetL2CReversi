#ifndef __MULTI__
#define __MULTI__

  #include "reversi.h"

  int connectionclient(char *adress);
  int *connectionserver(joueur *tabjoueurs, int nbjoueurs, char *modejeu);
  void getMessage(int newsockfd, char **buffer);
  void sendMessage(int newsockfd, char *message);
  void error(const char *msg);
  void sendToAll(char *message, int nbjoueurs, joueur *tabjoueurs);

#endif
