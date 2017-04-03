/* Data simulation Cpp
written by LucasNMilagres
*/
#include "SimulacaoDados.h"

SimulacaoDados::SimulacaoDados(void){hora=15; minuto=6;segundo=0;altitude=0;latitude=0;longitude=0;temp_externa=0;temp_interna=0;luminosidade=0;pressao=0;velocidade=0;aceleracao=0;}

//Calcula os dados de um pacote, de acordo com a função determinada para cada uma das variáveis
String SimulacaoDados::calcularDados(){   
  //Função de cálculo do tempo (Aproximação linear)
  if(segundo==59)
  {
    if(minuto==59)
    {
      hora++;
      minuto=0;
    }
    else
      minuto++;
      
    segundo=0;
  }
  else
    segundo++;
  
  //Função de cálculo da latitude (Aproximação linear)
  latitude+=1;

  //Função de cálculo da longitude (Aproximação linear)
  longitude+=2; 

  //Função de cálculo da altitude (Aproximação parábola)
  //altitude=-pow(hora*3600+minuto*60+segundo,2)+TEMPO_MAX_TRANS*(hora*3600+minuto*60+segundo);
  altitude+=3;
 
  //Função de cálculo da tempExterna (Aproximação parábola)
  //temp_externa=0.19*pow(altitude,2)-7.6*altitude+20; 
  temp_externa+=4;

  //Função de cálculo da tempInerna (Aproximação exponencial da externa)
  //temp_interna=temp_externa-(temp_externa-temp_interna)*exp(((float)-1)/((float)GROWTH_CONST_TEMP));  
  temp_interna+=5;

  //Função de cálculo da lumExterna (Constante)
  //luminosidade=43000; 
  luminosidade+=6;

  //Função de cálculo da pressaoAtm (Aproximação exponencial)
  //pressao=(101.325)*exp((-altitude)/((float)GROWTH_CONST_PRES)); 
  pressao+=7;

  //Função de cálculo da velocidade [Constante a partir da primeira derivada da altitude, desprezando o deslocamento horizontal (o qual ocorre em MRUA)]
  //velocidade=-2*(hora*3600+minuto*60+segundo)+TEMPO_MAX_TRANS;
  velocidade+=8;

  //Função de cálculo da aceleracao [Constante a partir da segunda derivada da altitude, desprezando o deslocamento horizontal (o qual ocorre em MRUA)]
  //aceleracao=-2;   
  aceleracao+=9;

  String msg=toCansat();
  return msg;
}

//Traduz do protocolo de string para o protocolo padrão do projeto. Aplicável somente ao teste
String SimulacaoDados::toCansat(){

  //Criar mensagem com os caracteres correspondentes aos bytes de cada dado
  String msg="";
  msg.concat((char)highByte(inicio));
  msg.concat((char)lowByte(inicio));
  msg.concat((char)lowByte(luminosidade));
  msg.concat((char)highByte(luminosidade));
  msg.concat(temp_externa);
  msg.concat(temp_interna);
  msg.concat((char)pressao);
  msg.concat((char)lowByte(aceleracao));
  msg.concat((char)highByte(aceleracao));
  msg.concat((char)lowByte(longitude));
  msg.concat((char)highByte(longitude));
  msg.concat((char)lowByte(latitude));
  msg.concat((char)highByte(latitude));
  msg.concat((char)lowByte(altitude));
  msg.concat((char)highByte(altitude));
  msg.concat((char)hora);
  msg.concat((char)minuto);
  msg.concat((char)segundo);
  msg.concat(velocidade);

  //Calcular a quantidade de bits setados na mensagem
  int bits_setados=0;
  for(int i=0;i<msg.length();i++){
    byte letra = (byte)msg.charAt(i);
    
    for(int j=0; j<8; j++)
      if(String(letra).charAt(j)=='1')
        bits_setados++;
  }

  //Determina a paridade
  if((bits_setados%2)==0)
    paridade=1;
  else
    paridade=0;
  
  msg.concat((char)paridade);

  return msg;
}
