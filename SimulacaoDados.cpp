/* Data simulation Cpp
written by LucasNMilagres
*/
#include "SimulacaoDados.h"

//Defines
#define TEMPO_MAX_TRANS 30000 //Tempo máximo de transmissão [segundos]
#define GROWTH_CONST_TEMP 3000 //Taxa de tranferencia do calor [segundos]
#define GROWTH_CONST_PRES 7000 //Constante de crescimento da pressão [metros]

SimulacaoDados::SimulacaoDados(void){hora=21; minuto=48;}

//Calcula os dados de um pacote, de acordo com a função determinada para cada uma das variáveis
void SimulacaoDados::calcularDados(){
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
  latitude+=0.0001;

  //Função de cálculo da longitude (Aproximação linear)
  longitude+=0.0001; 

  //Função de cálculo da altitude (Aproximação parábola)
  altitude=-pow(hora*3600+minuto*60+segundo,2)+TEMPO_MAX_TRANS*(hora*3600+minuto*60+segundo);
 
  //Função de cálculo da tempExterna (Aproximação parábola)
  temp_externa=0.19*pow(altitude,2)-7.6*altitude+20; 

  //Função de cálculo da tempInerna (Aproximação exponencial da externa)
  temp_interna=temp_externa-(temp_externa-temp_interna)*exp(((float)-1)/((float)GROWTH_CONST_TEMP));  

  //Função de cálculo da lumExterna (Constante)
  luminosidade=43000; 

  //Função de cálculo da pressaoAtm (Aproximação exponencial)
  pressao=(101.325)*exp((-altitude)/((float)GROWTH_CONST_PRES)); 

  //Função de cálculo da velocidade [Constante a partir da primeira derivada da altitude, desprezando o deslocamento horizontal (o qual ocorre em MRUA)]
  velocidade=-2*(hora*3600+minuto*60+segundo)+TEMPO_MAX_TRANS;

  //Função de cálculo da aceleracao [Constante a partir da segunda derivada da altitude, desprezando o deslocamento horizontal (o qual ocorre em MRUA)]
  aceleracao=-2;   
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

//Verifica se o tempo máximo de execução foi atingido
bool SimulacaoDados::encerrarExecucao(){
  if(hora*3600+minuto*60+segundo>=TEMPO_MAX_TRANS)
    return true;
  else
    return false;
}

