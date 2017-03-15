/* Main Cpp
written by LucasNMilagres
*/
#include "ComunicacaoSerial.h"

ComunicacaoSerial comunicacaoSerial;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Aguarda a recepção da solicitação de conexão
  comunicacaoSerial.responderConexao('K');

  //Roda a atividade
  while(1)
    comunicacaoSerial.run();
}

