/* Main Cpp
written by LucasNMilagres
*/
#include "ComunicacaoSerial.h"
#include "SimulacaoDados.h"

ComunicacaoSerial comunicacaoSerial;
SimulacaoDados dados;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Aguarda a recepção da solicitação de conexão
  comunicacaoSerial.responderConexao('K');

  while(!dados.encerrarExecucao()){
    //Aproxima o tempo simulado do tempo real
    delay(1000);

    //Roda a simulação
    dados.calcularDados();
    comunicacaoSerial.enviarDados(dados.toCansat());
  }
}

