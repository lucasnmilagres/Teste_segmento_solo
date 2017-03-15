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
    //Declaração de variável
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
    }
}

//Traduz do protocolo de string para o protocolo padrão do projeto. Aplicável somente ao teste
String ComunicacaoSerial::stringToCansat(String msg){
  unsigned int inicio, luminosidade, altitude;
  long int aceleracao;
  int longitude, latitude;
  char temp_externa, temp_interna, velocidade;
  byte pressao, hora, minuto, segundo, paridade;

  inicio=(unsigned int)(getValue(msg, ';', 0).toInt());
  luminosidade=(unsigned int)(getValue(msg, ';', 1).toInt()/0.153);
  temp_externa=(char)(getValue(msg, ';', 2).toInt()/0.472);
  temp_interna=(char)(getValue(msg, ';', 3).toInt()/0.276);
  pressao=(byte)(getValue(msg, ';', 4).toInt()/0.402);
  aceleracao=(long int)(getValue(msg, ';', 5).toInt()/0.153);
  longitude= (int)(getValue(msg, ';', 6).toInt()/0.153);
  latitude=(int)(getValue(msg, ';', 7).toInt()/0.153);
  altitude=(unsigned int)(getValue(msg, ';', 8).toInt()/0.611);
  hora=(byte)(getValue(msg, ';', 9).toInt());
  minuto=(byte)(getValue(msg, ';', 10).toInt());
  segundo=(byte)(getValue(msg, ';', 11).toInt());
  velocidade=(char)(getValue(msg, ';', 12).toInt()/0.079);
  paridade= (byte)(getValue(msg, ';', 13).toInt());

  msg="";
  msg.concat((char)highByte(inicio));
  msg.concat((char)lowByte(inicio));
  msg.concat((char)highByte(luminosidade));
  msg.concat((char)lowByte(luminosidade));
  msg.concat(temp_externa);
  msg.concat(temp_interna);
  msg.concat((char)pressao);
  msg.concat((char)highByte(aceleracao));
  msg.concat((char)lowByte(aceleracao));
  msg.concat((char)longitude);
  msg.concat((char)latitude);
  msg.concat((char)highByte(altitude));
  msg.concat((char)lowByte(altitude));
  msg.concat((char)hora);
  msg.concat((char)minuto);
  msg.concat((char)segundo);
  msg.concat(velocidade);
  msg.concat((char)paridade);

  return msg;
}

//Envia os dados através da serial
void ComunicacaoSerial::enviarDados(String msg){
  Serial.print(msg);
}

//Corta strings em caracteres específicos
String ComunicacaoSerial::getValue(String data, char separator, int index)
{
    int maxIndex = data.length() - 1;
    int j = 0;
    String chunkVal = "";

    for (int i = 0; i <= maxIndex && j <= index; i++)
    {
        if(data[i] != separator)
          chunkVal.concat(data[i]);

        if (data[i] == separator)
        {
            j++;

            if (j > index)
            {
                chunkVal.trim();
                return chunkVal;
            }

            chunkVal = "";
        }
        else if ((i == maxIndex) && (j < index)) {
            chunkVal = "";
            return chunkVal;
        }
    }   
}

