/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: Harjoitustyö-tavoitetaso-aliohjelmat
 * Tekijä: Jan Saariniemi
 * Opiskelijanumero: 0443233
 * Päivämäärä: 12.7.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
/*		ALIOHJELMAT		*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define LEN 50

int panel(){
	int choice;
	printf("\nValitse haluamasi toiminto alla olevasta valikosta:\n");
	printf("1) Lue lämpötilatiedosto\n");
	printf("2) Tallenna listan tiedot\n");
	printf("3) Analysoi tiedot\n");
	printf("4) Suorita kuukausianalyysi\n");
	printf("5) Tulosta kaikki tulokset\n");
	printf("6) Tallenna tulokset tiedostoon\n");
	printf("7) Tyhjennä analyysilista\n");
	printf("0) Lopeta\n");

	printf("Valintasi: ");
	scanf("%d",&choice);
	getchar();
	return choice;
	
}

WEATHER *ReadDataList(WEATHER *pStart){
	FILE* file;
	WEATHER *ptr, *ptr_temp;
	char file_name[LEN];
	char line[LEN];
	char delim[] = ";";
	char *temperature;
	char *day;
	char *month;
	char *year;
	int count =0;



	printf("Anna luettavan tiedoston nimi: ");
	fgets(file_name,LEN,stdin);
	file_name[strcspn(file_name, "\n")] = 0;
	

	if ((file = fopen(file_name,"r")) == NULL){
		printf("Tiedoston lukeminen epäonnistui\n");
		return pStart;
	}

	else{
		printf("Luetaan tiedosto '%s'\n",file_name);

		while (fgets(line, LEN, file) != NULL) {

			/*MUUTTUJIEN ALUSTUS */
			year = strtok(line, delim);
			month = strtok(NULL,delim);
			day = strtok(NULL,delim);
			strtok(NULL,delim);	
			temperature = strtok(NULL,delim);
			count++;
			
			/* ALKION MUISTIN VARAUS*/
			if ((ptr_temp =(WEATHER*)malloc(sizeof(WEATHER))) == NULL){
				perror("Muistin varaus epäonnistui");
				exit(1);
			}

			/*ALKIOIDEN ALUSTUS*/

			ptr_temp->itemperature = atoi(temperature);
			ptr_temp->iday = atoi(day);
			ptr_temp->imonth = atoi(month);
			ptr_temp->iyear = atoi(year); 
			ptr_temp->pNext = NULL;
						

			if (pStart == NULL){
				pStart = ptr_temp;

			}

			else{
				ptr = pStart; 
				while (ptr ->pNext != NULL){
					ptr = ptr->pNext; 
				} 
				/*ALKIOIDEN VÄLINEN LINKITYS*/
				ptr-> pNext = ptr_temp; 				
			}
		}

	}
	fclose(file);
	printf("Tiedosto '%s' luettu, %d riviä.\n",file_name, count);
	return pStart;
}



void SaveDataList(WEATHER *pStart){
	FILE* file;
	WEATHER *ptr =pStart;
	
	if (pStart == NULL){
		printf("Lämpötilalista on tyhjä.\n");
		return;
	}

	else{
		if ((file = fopen("lampotiladata.txt","w")) == NULL){
		printf("Tiedostoon kirjoittaminen epäonnistui\n");
		return;
		}
	
		else{
			fprintf (file, "pvm lämpötila\n");
			while(ptr != NULL){
				fprintf(file,"%d.%d.%d %d C\n",ptr->iday,ptr->imonth,ptr->iyear,ptr->itemperature);
				ptr = ptr->pNext;
			}
		}
	}
	printf("Lämpötiladata tallennettu.\n");
	return;	
}


void AnalyseDataList(WEATHER *pStart){

	if (pStart == NULL){
		printf("Ei analysoitavaa, lue ensin lämpötilatiedosto.\n");
		return;
	} else {
		WEATHER *ptr =pStart;
		int total = 0;
		int count = 1;
		int min;
		int max;

		total = total + ptr->itemperature;
		min = ptr->itemperature;
		max = ptr->itemperature;
		ptr = ptr->pNext; 

		while(ptr != NULL){

			total = total + ptr->itemperature;
			count ++;
			if(min>ptr->itemperature){
				min = ptr->itemperature;
			}
		
			if(max<ptr->itemperature){
				max = ptr->itemperature;
			}
		
			ptr = ptr->pNext; 
		}
		printf("Lämpötila-analyysi, %d alkiota:\n",count);
 		printf("  Avg  Min  Max\n");
		printf("    %d  %d   %d\n", (total/count),min,max); 

	}
	return;
}




WEATHER *FreeMemory(WEATHER *pStart){
	WEATHER *ptr = pStart;
	while(ptr != NULL){
		pStart = ptr->pNext;
		free(ptr);
		ptr = pStart;
	}
	return pStart;
}


MONTH *AnalyseMonthDataList(WEATHER *WpStart, MONTH *MpStart){

	MONTH *Mptr = MpStart, *ptr_temp;
	WEATHER *Wptr =WpStart;

	char file_name[LEN];
	int month = 0;
	int total = 0;
	int count = 0;
	int min;
	int max;
	
	
	printf("Anna analysoitavalle datasetille nimi: ");
	fgets(file_name,LEN,stdin);
	file_name[strcspn(file_name, "\n")] = 0;

	if ((ptr_temp =(MONTH*)malloc(sizeof(MONTH))) == NULL){
			perror("Muistin varaus epäonnistui");
			exit(1);
	}

	/*TALLENUSLISTAN KELAUS*/

	if (MpStart == NULL){
		MpStart = ptr_temp;
	} else {
		Mptr = MpStart; 
		while (Mptr ->pNext != NULL){
			Mptr = Mptr->pNext; 
		}
		Mptr-> pNext = ptr_temp; 
	}


	if (WpStart == NULL){
		printf("Ei analysoitavaa, lue ensin lämpötilatiedosto.\n");
		return MpStart;
	}
	/*TALLENNNUSLISTAN ALKION ALUSTUS JA tallennus*/
	else{

		while(Wptr != NULL){
			if (month == 0){
				/*Annetaan vain kerran*/
				strcpy(ptr_temp ->iFileName,file_name);
				ptr_temp ->iyear = Wptr ->iyear;
				ptr_temp ->pNext = NULL;

				total = total + Wptr->itemperature;
				count ++;
				month = Wptr->imonth;
				min = Wptr->itemperature;
				max = Wptr->itemperature;
			}
			else{
				if (month != Wptr->imonth){
					/*tallenna kk-tiedot alkioiden listaan*/
					ptr_temp ->imin[month-1] = min;
					ptr_temp ->imax[month-1] = max;
					ptr_temp ->iavg[month-1] = (total/count);					

					/*nollaa mittarit*/
					total = Wptr->itemperature;
					count = 1;
					min = Wptr->itemperature;
					max = Wptr->itemperature;
					/*Vaihda kuukausi*/
					month = Wptr->imonth;
				}
				else{

					total = total + Wptr->itemperature;
					count ++;
					if(min>Wptr->itemperature){
						min = Wptr->itemperature;
					}
				
					if(max<Wptr->itemperature){
						max = Wptr->itemperature;
					}
				}
			

			
			}
			Wptr = Wptr->pNext;
	
		}
		ptr_temp ->imin[month-1] = min;
		ptr_temp ->imax[month-1] = max;
		ptr_temp ->iavg[month-1] = (total/count);
	}
	printf("Kuukausianalyysi valmis.\n");
	return MpStart;

}


void PrintMonthDataList(MONTH *MpStart){
	int i;
	MONTH *Mptr = MpStart;

	if (Mptr == NULL){
		printf("Tuloslista on tyhjä.\n");
		return;
	}		
	else{
		printf("Analyysilistan tulokset:\n");
		while(Mptr != NULL){
			printf("\n");
			printf("%s\n",Mptr->iFileName);
			printf("%d\tTammi\tHelmi\tMaalis\tHuhti\tTouko\tKesä\tHeinä\tElo\tSyys\tLoka\tMarras\tJoulu",Mptr->iyear);

			printf("\navg:");
			for(i = 0; i < 12; i++){
      				printf("\t%d", Mptr->iavg[i]);
			}

			printf("\nmin:");
			for(i = 0; i < 12; i++){
      				printf("\t%d", Mptr->imin[i]);
			}

			printf("\nmax:");
			for(i = 0; i < 12; i++){
      				printf("\t%d", Mptr->imax[i]);
			}			
			printf("\n");
			Mptr = Mptr->pNext;				
		}
	}
	return;
}



void saveTemperatureDataPanel(MONTH *MpStart){
	MONTH *Mptr =MpStart;
	int choice;

	printf("\nMikä kuukausianalyysi tallennetaan?\n");
	printf("1) Keskilämpötila\n");
	printf("2) Minimilämpötila\n");
	printf("3) Maksimilämpötila\n");
	printf("Valintasi: ");
	scanf("%d",&choice);
	saveTemperatureDataAction(MpStart,choice);
	return;
}

  

void saveTemperatureDataAction(MONTH *MpStart,int choice){

	FILE* file;
	MONTH *Mptr =MpStart;
	int i;

	if (MpStart == NULL){
		printf("Tuloslista on tyhjä.\n");
		return;
	}

	else{
		if ((file = fopen("tulostiedot.csv","w")) == NULL){
			printf("Tiedostoon kirjoittaminen epäonnistui\n");
			return;
		}
	
		else{
			fprintf (file,";Tammi;Helmi;Maalis;Huhti;Touko;Kesä;Heinä;Elo;Syys;Loka;Marras;Joulu\n");
			while(Mptr != NULL){
				if(choice==1) {
					fprintf(file,"%s - %d",Mptr->iFileName, Mptr->iyear);
					for(i = 0; i < 12; i++){
						fprintf(file,";");
						fprintf(file,"%d", Mptr->iavg[i]);

					}
					fprintf(file,"\n");
				} else if(choice==2) {
					fprintf(file,"%s - %d",Mptr->iFileName, Mptr->iyear);
					for(i = 0; i < 12; i++){
						fprintf(file,";");
						fprintf(file,"%d", Mptr->imin[i]);

					}
					fprintf(file,"\n");
				} else if(choice==3) {
					fprintf(file,"%s - %d",Mptr->iFileName, Mptr->iyear);
					for(i = 0; i < 12; i++){
						fprintf(file,";");
						fprintf(file,"%d", Mptr->imax[i]);
						
					}
					fprintf(file,"\n");
				} else{
					printf("Valintaa ei tunnistettu.\n");
					return;
				}
				Mptr = Mptr->pNext;
			}
		}
	}
	printf("Tiedot tallennettu tiedostoon: 'tulostiedot.csv'\n");
	return;	

}

MONTH *MonthDataFreeMemory(MONTH *MpStart){
	MONTH *Mptr = MpStart;
	while(Mptr != NULL){
		MpStart = Mptr->pNext;
		free(Mptr);
		Mptr = MpStart;
	}
	printf("Tuloslista tyhjennetty.\n");
	return MpStart;
}

MONTH *MonthDataFreeMemory_end(MONTH *MpStart){
	MONTH *Mptr = MpStart;
	while(Mptr != NULL){
		MpStart = Mptr->pNext;
		free(Mptr);
		Mptr = MpStart;
	}
	return MpStart;
}
/*******************************************************************/
/* eof */
