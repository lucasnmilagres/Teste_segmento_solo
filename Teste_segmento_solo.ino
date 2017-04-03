/* Main Cpp
written by LucasNMilagres
*/
#include "ComunicacaoSerial.h"
#include "SimulacaoDados.h"

ComunicacaoSerial comunicacaoSerial;

void setup() {
  Serial.begin(115200);
}

void loop() {
  //Aguarda a recepção da solicitação de conexão
  comunicacaoSerial.responderConexao('K');

  SimulacaoDados dados=SimulacaoDados();

  while(true){
    //Aproxima o tempo simulado do tempo real
    delay(54000);

    //Roda a simulação
    for(int i=0; i<120; i++)
    {
      delay(50);
      comunicacaoSerial.enviarDados(dados.calcularDados());
    }
  }
}

