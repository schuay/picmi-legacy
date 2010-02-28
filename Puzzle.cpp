#include "Levels.cpp"
#include "Variables.cpp"

// Pusselmotorn
// CalcPuzzle(level) -- enkel svårighetsgrad 1-5, medel 5-10, svår 10--

void CalcPuzzle(int level) {
        int rows, i, j, x, y, col[100][20], col_len[100]; char row[100][100];
        char s[10];

        int level_size = 0;

	// Definera storleken på pusslet - 5x5, 10x10, 15x15

        if(level >= 1) level_size = 5;
        if(level >= 5) level_size = 10;
        if(level >= 10) level_size = 15;

        // Kalkylera horisontellt
	// Puzz_3 = char med pussel, se Levels.cpp

        for(i=0;i<level_size;i++) {
                int cnt = 0;
		count = 0;
                char *p=row[i];
                for(j=0;j<=level_size;j++) {
                        if (j<level_size && puzz_3[i][j]=='#') {
				cnt++;
				count++;
			}
                        else if (cnt) {
                                if (cnt>=10) *p++=cnt/10+'0';
                                *p++=cnt%10+'0';
                                cnt=0;
                        }
                        *p=0;
                }
        }

        // Kalkylera vertikalt

        for(i=0;i<level_size;i++) {
                col_len[i]=0; // antalet tal i den här kolumnen
                int cnt=0;
                for(j=0;j<=level_size;j++) {
                        if (j<level_size && puzz_3[j][i]=='#') cnt++;
                        else if (cnt) {
                               col[i][col_len[i]++]=cnt;
                                cnt=0;
                        }
                }
        }

        // Fixa till vertikalt och skriv ut

        for(i=0;i<level_size;i++) {
                if (!col_len[i]) col[i][col_len[i]++]=0;

                for(j=0;j<col_len[i];j++) {
                        char *p=s;

                        if (col[i][j]>=10) *p++=col[i][j]/10+'0';

                        *p++=col[i][j]%10+'0';
                        *p=0;
			if (col[i][j]>=10) {
				 x=Puzzle_PositionX+i*12-9;
			} else { x=Puzzle_PositionX+i*12-3;
			}

                        y=Puzzle_PositionY+j*12-col_len[i]*12-12;

		// TODO: Kolla ifall col[] innehåller nummer större än 10,
		// flytta numret aningen åt vänster och siffrorna ihop

                        GB_DrawText(s, x, y);
                }

        }

        // Om en rad är helt tom, skriv ut 0

        for(i=0;i<level_size;i++) {
        if (!row[i][0]) { row[i][0]='0'; row[i][1]=0; }
        }

        // Skriv ut horizontellt pussel


	for(i=0;i<level_size;i++) {
	// Om innehållet i row[] innehåller nummer som är större än 10,
	// skriv ut siffrorna närmre varandra -- Omvandla row till int för
	// att kika

		GB_DrawText(("%s\n",row[i]),Puzzle_PositionX-10*strlen(row[i])-12,Puzzle_PositionY+i*12-3);
	}
}

// Rita ut det kalkylerade pusslet
// DrawPuzzle(level)

void DrawPuzzle(int level) {
        int level_size = 0;
	tempcount = 0;

        // Rita ut alla block
	// Räkna ut vilken level det är och rita sedan ut bakgrund och nät

	if(level >= 10)
	{
		SIXTEEN.GB_SetXY(Puzzle_PositionX,Puzzle_PositionY);
		SIXTEEN.GB_ShowSprite(0,0);
	}

        for(int yy=0;yy<level_size;yy++) {
                for(int xx=0;xx<level_size;xx++) {

			// Kika in på låtsaskartan vart vi har slagit in
			// klossen och kika ifall vi träffat rätt

                        if(TEMPMAP[yy][xx] == '#') {
                                PushedBlock.GB_SetXY(Puzzle_PositionX+xx*12,Puzzle_PositionY+yy*12);
                                PushedBlock.GB_ShowSprite(0,0);
                        }

                        if(TEMPMAP[yy][xx] == 'X') {
                                CheckedBlock.GB_SetXY(Puzzle_PositionX+xx*12,Puzzle_PositionY+yy*12);
                                CheckedBlock.GB_ShowSprite(0,0);
                        }
                }

        }


}
