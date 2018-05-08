/*--------------------------------------------------------------------------*/
/*  hw1.cpp 																*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*  Created by Ahmet Mert Gülbahçe on 02.03.2017.							*/
/*																			*/
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

/*  ReadFromFile
	stringToFind: Dosyada aranacak string
	FileName: Stringin aranacağı dosya 
*/
void readFromFile(const char *stringToFind, const char *fileName);

int main(int argc, const char *argv[])
{
	if(argc != 3)
	{
		printf("Program adı - Aranacak öge - Dosya adı\nşeklinde olmalıdır.\n");
		return -1;
	}

	readFromFile(argv[1], argv[2]);

	return 0;
}

void readFromFile(const char *stringToFind, const char *fileName)
{
	FILE *fp;

	if( (fp = fopen(fileName,"r")) == NULL )
	{
		printf("Dosya açılamadı.\n");
		return;
	}

	char c;
	int length = strlen(stringToFind); /* bulunacak stringin uzunluğu */
	int rowCount = 1, columnCount = 1,  /* satır sütun için counter */
		foundRow, foundColomn, /* bulunduğu konum bilgileri */
		totalCount = 0, /* bulunan toplam string */
		skippedCharacters = 0; /* atlanan karakterler için counter */
	char *tmpStr; /* karşılaştırmak için kullanılan geçici string */
	int isEof = 0; /* eof kontrolcüsü */
	int strLength = 0;/* geçici stringin uzunluğu */

	while(isEof != 1) 
	{
		c = getc(fp);

		if(c == EOF)
			isEof = 1;;

		/* okunan karakter tab, new line ve space değilse */
		if (c != 9 && c != 10 && c != 32)
		{
			/* string boş ise yeni yer açılır ve bulunduğu konum kaydedilir */
			if(strLength == 0)
			{
				tmpStr = (char *) malloc(length*sizeof(char));
				foundRow = rowCount;
				foundColomn = columnCount;
			}
			tmpStr[strLength] = c;
			strLength++;
			columnCount++;
		}
		else
		{
			/* alt satıra geçtiyse */
			if(c == 10)
			{
				rowCount++;
				columnCount = 1;
			}
			else
				columnCount++;;

			if(strLength != 0)
				skippedCharacters++;
		}
		/* uzunluklar eşitse */
		if(strLength == length)
		{
			/* string kıyaslaması yapılır, eşitse konumlar yazılır */
			if(strcmp(tmpStr,stringToFind) == 0)
			{
				printf("[%d, %d] konumunda ilk karakter bulundu.\n",foundRow,foundColomn);
				totalCount++;
			}
			strLength = 0;
			
			/* bulunduğu konumdan sonra tekrar aramaya geri döner */
			fseek(fp, -1*sizeof(char)*(length+skippedCharacters-1), SEEK_CUR);
			
			if(columnCount <= length+skippedCharacters && rowCount != 1)
				rowCount = foundRow;
				
			columnCount = foundColomn+1;

			skippedCharacters = 0;
			free(tmpStr);
		}
	}
	
	printf("%d adet %s bulundu.\n",totalCount,stringToFind);

	fclose(fp);
}