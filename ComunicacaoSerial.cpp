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

//Recebe dados através da entrada serial e as organiza em uma String. Para a versão final, sugere-se utilizar um readByte, pois o tamanho do pacote é bem conhecido
void ComunicacaoSerial::run(){  
    /*Declaração de variável
    String msg="";
    char letra='a';
    
    //Concatena todos os caracteres recebidos pela serial. NUNCA usar o readString, pois não funciona adequadamente.
    while(letra!='!')
    {
      if(Serial.available())
      {
        letra=(char)Serial.read();
  
        if(letra!='!')
          msg.concat(letra);
      }
    }

    //Tradução e envio da mensagem
    if(msg.length()>0)
    {
      msg=stringToCansat(msg);
      enviarDados(msg);
    }*/
}

//Envia os dados através da serial
void ComunicacaoSerial::enviarDados(String msg){
  Serial.print(msg);
}

