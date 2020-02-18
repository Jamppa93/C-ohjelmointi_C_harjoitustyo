/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot: Harjoitustyö- tavoitetaso-esittelytiedosto
 * Tekijä: Jan Saariniemi
 * Opiskelijanumero: 0443233
 * Päivämäärä: 12.7.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
/*		TIETORAKENTEET		*/
#define LEN 50

struct weather {
	
	int itemperature;
	int iday;
	int imonth;
	int iyear;
	struct weather *pNext;
};

typedef struct weather WEATHER;

struct MonthlyTemperature {

	char iFileName[LEN];
	int iyear;
	int imin[12];
	int imax[12];
	int iavg[12];
	struct MonthlyTemperature *pNext;

};

typedef struct MonthlyTemperature MONTH;
/*******************************************************************/
/*		ALIOHJELMAKUTSUT	*/

int panel();
WEATHER *ReadDataList(WEATHER *pStart);
void SaveDataList(WEATHER *pStart);
void AnalyseDataList(WEATHER *pStart);
WEATHER *FreeMemory(WEATHER *pStart);
MONTH *AnalyseMonthDataList(WEATHER *WpStart, MONTH *MpStart);
void PrintMonthDataList(MONTH *MpStart);
void saveTemperatureDataPanel(MONTH *MpStart);
void saveTemperatureDataAction(MONTH *MpStart,int choice);
MONTH *MonthDataFreeMemory(MONTH *MpStart);
MONTH *MonthDataFreeMemory_end(MONTH *MpStart);
/*******************************************************************/
/* eof */
