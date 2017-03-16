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

  //Roda a atividade de simulação enquanto o tempo não superar o tempo máximo da simulação
  while(!dados.encerrarExecucao()){
    dados.calcularDados();
    comunicacaoSerial.enviarDados(dados.toCansat());

    //Aproxima o tempo simulado do tempo real
    delay(1000);
  }
}

