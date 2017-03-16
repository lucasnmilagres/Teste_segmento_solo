/* Communication Cpp
written by LucasNMilagres
*/
#include "ComunicacaoSerial.h"

ComunicacaoSerial::ComunicacaoSerial(void){}

//Responde a mensagem de conexão recebida
void ComunicacaoSerial::responderConexao(char msgResposta){
  //Verifica se a mensagem recebida contém o caractere de gatilho
  while (Serial.read()!='S');
    //Serial.print("No\n");

  //Envia a mensagem de resposta para o PC
  Serial.write(msgResposta); 

  //Limpa o buffer do serial
  while(Serial.available())
    Serial.read(); 
}

//Envia os dados através da serial
void ComunicacaoSerial::enviarDados(String msg){
  Serial.print(msg);
}

