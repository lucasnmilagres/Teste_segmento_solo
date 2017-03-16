/* Data simulation library
written by LucasNMilagres
*/
#ifndef SimulacaoDados_H
#define SimulacaoDados_H

#include "Arduino.h"

class SimulacaoDados
{ 
  private:
  const unsigned int inicio=65535;
  unsigned int luminosidade, altitude;
  long int aceleracao;
  int longitude, latitude;
  char temp_externa, temp_interna, velocidade;
  byte pressao, hora, minuto, segundo, paridade;

  public:
  SimulacaoDados(void);
  void calcularDados();
  String toCansat(); 
  bool encerrarExecucao();
};

#endif
