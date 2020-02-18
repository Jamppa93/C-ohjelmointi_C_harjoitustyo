/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: Harjoitustyö- tavoitetaso-pääohjelma
 * Tekijä: Jan Saariniemi
 * Opiskelijanumero: 0443233
 * Päivämäärä: 12.7.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
/*		MODUULIT JA VAKIOT		*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define LEN 50

/*******************************************************************/
/*		PÄÄOHJELMA		*/

int main(void){
	int choice;
	WEATHER *WpStart = NULL;
	MONTH *MpStart = NULL;
	printf("Tämä ohjelma analysoi lämpötilatiedostoja.\n");
	do{
		choice = panel();

		if(choice==1){
			WpStart=FreeMemory(WpStart);
			WpStart = ReadDataList(WpStart);
		}
		else if(choice==2){
			SaveDataList(WpStart);
		}
		else if(choice==3){
			AnalyseDataList(WpStart);
		}

		else if(choice ==4){
			MpStart = AnalyseMonthDataList(WpStart,MpStart);
		
		}
		else if(choice ==5){
			PrintMonthDataList(MpStart);
		
		}
		else if(choice ==6){
			saveTemperatureDataPanel(MpStart);
		}
		else if(choice ==7){
			MpStart = MonthDataFreeMemory(MpStart);
		}	
		else if(choice==0){
			FreeMemory(WpStart);
			MpStart = MonthDataFreeMemory_end(MpStart);
			printf("Kiitos ohjelman käytöstä.\n");
			break;
		}
		else{
			printf("Tuntematon valinta, yritä uudestaan.\n");
		}

	} while(1 > 0);


	return(0);
}
/*******************************************************************/
/* eof */
