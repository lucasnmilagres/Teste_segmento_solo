/* Communication library
written by LucasNMilagres
*/
#ifndef ComunicacaoSerial_H
#define ComunicacaoSerial_H

#include "Arduino.h"

class ComunicacaoSerial
{ 
  public:
  ComunicacaoSerial(void);
  void responderConexao(char msgResposta);
  void run();
  String stringToCansat(String msg);
  void enviarDados(String msg);
};

#endif
