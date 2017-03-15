/* Communication Cpp
written by LucasNMilagres
*/
#include "ComunicacaoSerial.h"

ComunicacaoSerial::ComunicacaoSerial(void){}

//Responde a mensagem de conexão recebida
void ComunicacaoSerial::responderConexao(char msgResposta){
  //Verifica se a mensagem recebida contém o caractere de gatilho
  while (Serial.read()!='S')
    Serial.print("No\n");

  //Envia a mensagem de resposta para o PC
  Serial.write(msgResposta); 
}

//Recebe dados através da entrada serial e as organiza em uma String
void ComunicacaoSerial::run(){  
    //Declaração de variável
    String msg="";

    //Concatena todos os caracteres recebidos pela serial. NUNCA usar o readString, pois não funciona adequadamente.
    while(Serial.available())
      msg.concat((char)Serial.read());

    //Tradução e envio da mensagem
    msg=stringToCansat(msg);
    enviarDados(msg);
}

//Traduz do protocolo de string para o protocolo padrão do projeto. Aplicável somente ao teste
String ComunicacaoSerial::stringToCansat(String msg){
  return msg;  
}

//Envia os dados através da serial
void ComunicacaoSerial::enviarDados(String msg){
  Serial.print(msg);
}

