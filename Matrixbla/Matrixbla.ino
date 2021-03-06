// Matrixbla.ino
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define BLACK matrix.Color(0,0,0)

#define RATE 25
#define PWM 255
#define WAITTIME(factor) (((60000/RATE)*factor)/PWM)

int i =0;
int indx = 0;
#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 8, PIN,
NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
//NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
NEO_GRB            + NEO_KHZ800);

// Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 5, PIN,
// 	//NEO_MATRIX_TOP     + 
// 	NEO_MATRIX_LEFT +
// 	NEO_MATRIX_BOTTOM     + 
// 	//NEO_MATRIX_LEFT +
// 	NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
// 	NEO_GRB            + NEO_KHZ800);

const uint16_t vgaColors[] = {
  // acording to: 
  // http://commons.wikimedia.org/wiki/File:VGA_palette_with_black_borders.svg
  // 16 Standard Farben:  0 - 15
  // 16 Graustufen:	   16 - 31
  // 24 Farben:		   32 - 55

  matrix.Color(  0,  0,  0),  // colorNo: 001 index: 000 
  matrix.Color( 25, 25,167),  // colorNo: 002 index: 001 
  matrix.Color(  0,170,  0),  // colorNo: 003 index: 002 
  matrix.Color(  0,170,170),  // colorNo: 004 index: 003 
  matrix.Color(170,  0,  0),  // colorNo: 005 index: 004 
  matrix.Color(170,  0,170),  // colorNo: 006 index: 005 
  matrix.Color(170, 85,  0),  // colorNo: 007 index: 006 
  matrix.Color(170,170,170),  // colorNo: 008 index: 007 
  matrix.Color( 85, 85, 85),  // colorNo: 009 index: 008 
  matrix.Color( 85, 85,255),  // colorNo: 010 index: 009 
  matrix.Color( 85,255, 85),  // colorNo: 011 index: 010 
  matrix.Color( 85,255,255),  // colorNo: 012 index: 011 
  matrix.Color(255, 85, 85),  // colorNo: 013 index: 012 
  matrix.Color(255, 85,255),  // colorNo: 014 index: 013 
  matrix.Color(255,255, 85),  // colorNo: 015 index: 014 
  matrix.Color(255,255,255),  // colorNo: 016 index: 015 

  matrix.Color(  0,  0,  0),  // colorNo: 017 index: 016 
  matrix.Color( 16, 16, 16),  // colorNo: 018 index: 017 
  matrix.Color( 32, 32, 32),  // colorNo: 019 index: 018 
  matrix.Color( 53, 53, 53),  // colorNo: 020 index: 019 
  matrix.Color( 69, 69, 69),  // colorNo: 021 index: 020 
  matrix.Color( 85, 85, 85),  // colorNo: 022 index: 021 
  matrix.Color(101,101,101),  // colorNo: 023 index: 022 
  matrix.Color(117,117,117),  // colorNo: 024 index: 023 
  matrix.Color(138,138,138),  // colorNo: 025 index: 024 
  matrix.Color(154,154,154),  // colorNo: 026 index: 025 
  matrix.Color(170,170,170),  // colorNo: 027 index: 026 
  matrix.Color(186,186,186),  // colorNo: 028 index: 027 
  matrix.Color(202,202,202),  // colorNo: 029 index: 028 
  matrix.Color(223,223,223),  // colorNo: 030 index: 029 
  matrix.Color(239,239,239),  // colorNo: 031 index: 030 
  matrix.Color(255,255,255),  // colorNo: 032 index: 031 

  matrix.Color(  0,  0,255),  // colorNo: 033 index: 032 
  matrix.Color( 65,  0,255),  // colorNo: 034 index: 033 
  matrix.Color(130,  0,255),  // colorNo: 035 index: 034 
  matrix.Color(190,  0,255),  // colorNo: 036 index: 035 
  matrix.Color(255,  0,255),  // colorNo: 037 index: 036 
  matrix.Color(255,  0,190),  // colorNo: 038 index: 037 
  matrix.Color(255,  0,130),  // colorNo: 039 index: 038 
  matrix.Color(255,  0, 65),  // colorNo: 040 index: 039 
  matrix.Color(255,  0,  0),  // colorNo: 041 index: 040 
  matrix.Color(255, 65,  0),  // colorNo: 042 index: 041 
  matrix.Color(255,130,  0),  // colorNo: 043 index: 042 
  matrix.Color(255,190,  0),  // colorNo: 044 index: 043 
  matrix.Color(255,255,  0),  // colorNo: 045 index: 044 
  matrix.Color(190,255,  0),  // colorNo: 046 index: 045 
  matrix.Color(130,255,  0),  // colorNo: 047 index: 046 
  matrix.Color( 65,255,  0),  // colorNo: 048 index: 047 

  matrix.Color(  0,255,  0),  // colorNo: 049 index: 048 
  matrix.Color(  0,255, 65),  // colorNo: 050 index: 049 
  matrix.Color(  0,255,130),  // colorNo: 051 index: 050 
  matrix.Color(  0,255,190),  // colorNo: 052 index: 051 
  matrix.Color(  0,255,255),  // colorNo: 053 index: 052 
  matrix.Color(  0,190,255),  // colorNo: 054 index: 053 
  matrix.Color(  0,130,255),  // colorNo: 055 index: 054 
  matrix.Color(  0, 65,255),  // colorNo: 056 index: 055 
  matrix.Color(130,130,255),  // colorNo: 057 index: 056 
  matrix.Color(158,130,255),  // colorNo: 058 index: 057 
  matrix.Color(190,130,255),  // colorNo: 059 index: 058 
  matrix.Color(223,130,255),  // colorNo: 060 index: 059 
  matrix.Color(255,130,255),  // colorNo: 061 index: 060 
  matrix.Color(255,130,223),  // colorNo: 062 index: 061 
  matrix.Color(255,130,190),  // colorNo: 063 index: 062 
  matrix.Color(255,130,158),  // colorNo: 064 index: 063 

  matrix.Color(255,130,130),  // colorNo: 065 index: 064 
  matrix.Color(255,158,130),  // colorNo: 066 index: 065 
  matrix.Color(255,190,130),  // colorNo: 067 index: 066 
  matrix.Color(255,223,130),  // colorNo: 068 index: 067 
  matrix.Color(255,255,130),  // colorNo: 069 index: 068 
  matrix.Color(223,255,130),  // colorNo: 070 index: 069 
  matrix.Color(190,255,130),  // colorNo: 071 index: 070 
  matrix.Color(158,255,130),  // colorNo: 072 index: 071 
  matrix.Color(130,255,130),  // colorNo: 073 index: 072 
  matrix.Color(130,255,158),  // colorNo: 074 index: 073 
  matrix.Color(130,255,190),  // colorNo: 075 index: 074 
  matrix.Color(130,255,223),  // colorNo: 076 index: 075 
  matrix.Color(130,255,255),  // colorNo: 077 index: 076 
  matrix.Color(130,223,255),  // colorNo: 078 index: 077 
  matrix.Color(130,190,255),  // colorNo: 079 index: 078 
  matrix.Color(130,158,255),  // colorNo: 080 index: 079 

  matrix.Color(186,186,255),  // colorNo: 081 index: 080
  matrix.Color(202,186,255),  // colorNo: 082 index: 081 
  matrix.Color(223,186,255),  // colorNo: 083 index: 082 
  matrix.Color(239,186,255),  // colorNo: 084 index: 083 
  matrix.Color(255,186,255),  // colorNo: 085 index: 084 
  matrix.Color(255,186,239),  // colorNo: 086 index: 085 
  matrix.Color(255,186,223),  // colorNo: 087 index: 086 
  matrix.Color(255,186,202),  // colorNo: 088 index: 087 
  matrix.Color(255,186,186),  // colorNo: 089 index: 088 
  matrix.Color(255,202,186),  // colorNo: 090 index: 089 
  matrix.Color(255,223,186),  // colorNo: 091 index: 090 
  matrix.Color(255,239,186),  // colorNo: 092 index: 091 
  matrix.Color(255,255,186),  // colorNo: 093 index: 092 
  matrix.Color(239,255,186),  // colorNo: 094 index: 093 
  matrix.Color(223,255,186),  // colorNo: 095 index: 094 
  matrix.Color(202,255,186),  // colorNo: 096 index: 095 

  matrix.Color(186,255,186),  // colorNo: 097 index: 096
  matrix.Color(186,255,202),  // colorNo: 098 index: 097
  matrix.Color(186,255,223),  // colorNo: 099 index: 098
  matrix.Color(186,255,239),  // colorNo: 100 index: 099
  matrix.Color(186,255,255),  // colorNo: 101 index: 100
  matrix.Color(186,239,255),  // colorNo: 102 index: 101
  matrix.Color(186,223,255),  // colorNo: 103 index: 102
  matrix.Color(186,202,255),  // colorNo: 104 index: 103
  matrix.Color(  0,  0,113),  // colorNo: 105 index: 104
  matrix.Color( 28,  0,113),  // colorNo: 106 index: 105
  matrix.Color( 57,  0,113),  // colorNo: 107 index: 106
  matrix.Color( 85,  0,113),  // colorNo: 108 index: 107
  matrix.Color(113,  0,113),  // colorNo: 109 index: 108
  matrix.Color(113,  0, 85),  // colorNo: 110 index: 109
  matrix.Color(113,  0, 57),  // colorNo: 111 index: 110
  matrix.Color(113,  0, 28),  // colorNo: 112 index: 111

  matrix.Color(113,  0,  0),  // colorNo: 113 index: 112
  matrix.Color(113, 28,  0),  // colorNo: 114 index: 113
  matrix.Color(113, 57,  0),  // colorNo: 115 index: 114
  matrix.Color(113, 85,  0),  // colorNo: 116 index: 115
  matrix.Color(113,113,  0),  // colorNo: 117 index: 116
  matrix.Color( 85,113,  0),  // colorNo: 118 index: 117
  matrix.Color( 57,113,  0),  // colorNo: 119 index: 118
  matrix.Color( 28,113,  0),  // colorNo: 120 index: 119
  matrix.Color(  0,113,  0),  // colorNo: 121 index: 120
  matrix.Color(  0,113, 28),  // colorNo: 122 index: 121
  matrix.Color(  0,113, 57),  // colorNo: 123 index: 122
  matrix.Color(  0,113, 85),  // colorNo: 124 index: 123
  matrix.Color(  0,113,113),  // colorNo: 125 index: 124
  matrix.Color(  0, 85,113),  // colorNo: 126 index: 125
  matrix.Color(  0, 57,113),  // colorNo: 127 index: 126
  matrix.Color(  0, 28,113),  // colorNo: 128 index: 127

  matrix.Color( 57, 57,113),  // colorNo: 129 index: 128
  matrix.Color( 69, 57,113),  // colorNo: 130 index: 129 
  matrix.Color( 85, 57,113),  // colorNo: 131 index: 130 
  matrix.Color( 97, 57,113),  // colorNo: 132 index: 131 
  matrix.Color(113, 57,113),  // colorNo: 133 index: 132 
  matrix.Color(113, 57, 97),  // colorNo: 134 index: 133 
  matrix.Color(113, 57, 85),  // colorNo: 135 index: 134 
  matrix.Color(113, 57, 69),  // colorNo: 136 index: 135 
  matrix.Color(113, 57, 57),  // colorNo: 137 index: 136 
  matrix.Color(113, 69, 57),  // colorNo: 138 index: 137 
  matrix.Color(113, 85, 57),  // colorNo: 139 index: 138 
  matrix.Color(113, 97, 57),  // colorNo: 140 index: 139 
  matrix.Color(113,113, 57),  // colorNo: 141 index: 140 
  matrix.Color( 97,113, 57),  // colorNo: 142 index: 141 
  matrix.Color( 85,113, 57),  // colorNo: 143 index: 142 
  matrix.Color( 69,113, 57),  // colorNo: 144 index: 143 

  matrix.Color( 57,113, 57),  // colorNo: 145 index: 144
  matrix.Color( 57,113, 69),  // colorNo: 146 index: 145
  matrix.Color( 57,113, 85),  // colorNo: 147 index: 146
  matrix.Color( 57,113, 97),  // colorNo: 148 index: 147
  matrix.Color( 57,113,113),  // colorNo: 149 index: 148
  matrix.Color( 57, 97,113),  // colorNo: 150 index: 149
  matrix.Color( 57, 85,113),  // colorNo: 151 index: 150
  matrix.Color( 57, 69,113),  // colorNo: 152 index: 151
  matrix.Color( 81, 81,113),  // colorNo: 153 index: 152
  matrix.Color( 89, 81,113),  // colorNo: 154 index: 153
  matrix.Color( 97, 81,113),  // colorNo: 155 index: 154
  matrix.Color(105, 81,113),  // colorNo: 156 index: 155
  matrix.Color(113, 81,113),  // colorNo: 157 index: 156
  matrix.Color(113, 81,105),  // colorNo: 158 index: 157
  matrix.Color(113, 81, 97),  // colorNo: 159 index: 158
  matrix.Color(113, 81, 89),  // colorNo: 160 index: 159

    matrix.Color(113, 81, 81),  // colorNo: 161 index: 160
  matrix.Color(113, 89, 81),  // colorNo: 162 index: 161
  matrix.Color(113, 97, 81),  // colorNo: 163 index: 162
  matrix.Color(113,105, 81),  // colorNo: 164 index: 163
  matrix.Color(113,113, 81),  // colorNo: 165 index: 164
  matrix.Color(105,113, 81),  // colorNo: 166 index: 165
  matrix.Color( 97,113, 81),  // colorNo: 167 index: 166
  matrix.Color( 89,113, 81),  // colorNo: 168 index: 167
  matrix.Color( 81,113, 81),  // colorNo: 169 index: 168
  matrix.Color( 81,113, 89),  // colorNo: 170 index: 169
  matrix.Color( 81,113, 97),  // colorNo: 171 index: 170
  matrix.Color( 81,113,105),  // colorNo: 172 index: 171
  matrix.Color( 81,113,113),  // colorNo: 173 index: 172
  matrix.Color( 81,105,113),  // colorNo: 174 index: 173
  matrix.Color( 81, 97,113),  // colorNo: 175 index: 174
  matrix.Color( 81, 89,113),  // colorNo: 176 index: 175

  matrix.Color(  0,  0, 65),  // colorNo: 177 index: 176 
  matrix.Color( 16,  0, 65),  // colorNo: 178 index: 177 
  matrix.Color( 32,  0, 65),  // colorNo: 179 index: 178 
  matrix.Color( 49,  0, 65),  // colorNo: 180 index: 179 
  matrix.Color( 65,  0, 65),  // colorNo: 181 index: 180 
  matrix.Color( 65,  0, 49),  // colorNo: 182 index: 181 
  matrix.Color( 65,  0, 32),  // colorNo: 183 index: 182 
  matrix.Color( 65,  0, 16),  // colorNo: 184 index: 183 
  matrix.Color( 65,  0,  0),  // colorNo: 185 index: 184 
  matrix.Color( 65, 16,  0),  // colorNo: 186 index: 185 
  matrix.Color( 65, 32,  0),  // colorNo: 187 index: 186 
  matrix.Color( 65, 49,  0),  // colorNo: 188 index: 187 
  matrix.Color( 65, 65,  0),  // colorNo: 189 index: 188 
  matrix.Color( 49, 65,  0),  // colorNo: 190 index: 189 
  matrix.Color( 32, 65,  0),  // colorNo: 191 index: 190 
  matrix.Color( 16, 65,  0),  // colorNo: 192 index: 191 

  matrix.Color(  0, 65,  0),  // colorNo: 193 index: 192 
  matrix.Color(  0, 65, 16),  // colorNo: 194 index: 193 
  matrix.Color(  0, 65, 32),  // colorNo: 195 index: 194 
  matrix.Color(  0, 65, 49),  // colorNo: 196 index: 195 
  matrix.Color(  0, 65, 65),  // colorNo: 197 index: 196 
  matrix.Color(  0, 49, 65),  // colorNo: 198 index: 197 
  matrix.Color(  0, 32, 65),  // colorNo: 199 index: 198 
  matrix.Color(  0, 16, 65),  // colorNo: 200 index: 199 
  matrix.Color( 32, 32, 65),  // colorNo: 201 index: 200 
  matrix.Color( 40, 32, 65),  // colorNo: 202 index: 201 
  matrix.Color( 49, 32, 65),  // colorNo: 203 index: 202 
  matrix.Color( 57, 32, 65),  // colorNo: 204 index: 203 
  matrix.Color( 65, 32, 65),  // colorNo: 205 index: 204 
  matrix.Color( 65, 32, 57),  // colorNo: 206 index: 205 
  matrix.Color( 65, 32, 49),  // colorNo: 207 index: 206 
  matrix.Color( 65, 32, 40),  // colorNo: 208 index: 207 

  matrix.Color( 65, 32, 32),  // colorNo: 209 index: 208 
  matrix.Color( 65, 40, 32),  // colorNo: 210 index: 209 
  matrix.Color( 65, 49, 32),  // colorNo: 211 index: 210 
  matrix.Color( 65, 57, 32),  // colorNo: 212 index: 211 
  matrix.Color( 65, 65, 32),  // colorNo: 213 index: 212 
  matrix.Color( 57, 65, 32),  // colorNo: 214 index: 213 
  matrix.Color( 49, 65, 32),  // colorNo: 215 index: 214 
  matrix.Color( 40, 65, 32),  // colorNo: 216 index: 215 
  matrix.Color( 32, 65, 32),  // colorNo: 217 index: 216 
  matrix.Color( 32, 65, 40),  // colorNo: 218 index: 217 
  matrix.Color( 32, 65, 49),  // colorNo: 219 index: 218 
  matrix.Color( 32, 65, 57),  // colorNo: 220 index: 219 
  matrix.Color( 32, 65, 65),  // colorNo: 221 index: 220 
  matrix.Color( 32, 57, 65),  // colorNo: 222 index: 221 
  matrix.Color( 32, 49, 65),  // colorNo: 223 index: 222 
  matrix.Color( 32, 40, 65),  // colorNo: 224 index: 223 

  matrix.Color( 45, 45, 65),  // colorNo: 225 index: 224
  matrix.Color( 49, 45, 65),  // colorNo: 226 index: 225 
  matrix.Color( 53, 45, 65),  // colorNo: 227 index: 226 
  matrix.Color( 61, 45, 65),  // colorNo: 228 index: 227 
  matrix.Color( 65, 45, 65),  // colorNo: 229 index: 228 
  matrix.Color( 65, 45, 61),  // colorNo: 230 index: 229 
  matrix.Color( 65, 45, 53),  // colorNo: 231 index: 230 
  matrix.Color( 65, 45, 49),  // colorNo: 232 index: 231 
  matrix.Color( 65, 45, 45),  // colorNo: 233 index: 232 
  matrix.Color( 65, 49, 45),  // colorNo: 234 index: 233 
  matrix.Color( 65, 53, 45),  // colorNo: 235 index: 234 
  matrix.Color( 65, 61, 45),  // colorNo: 236 index: 235 
  matrix.Color( 65, 65, 45),  // colorNo: 237 index: 236 
  matrix.Color( 61, 65, 45),  // colorNo: 238 index: 237 
  matrix.Color( 53, 65, 45),  // colorNo: 239 index: 238 
  matrix.Color( 49, 65, 45),  // colorNo: 240 index: 239 

  matrix.Color( 45, 65, 45),  // colorNo: 241 index: 240
  matrix.Color( 45, 65, 49),  // colorNo: 242 index: 241
  matrix.Color( 45, 65, 53),  // colorNo: 243 index: 242
  matrix.Color( 45, 65, 61),  // colorNo: 244 index: 243
  matrix.Color( 45, 65, 65),  // colorNo: 245 index: 244
  matrix.Color( 45, 61, 65),  // colorNo: 246 index: 245
  matrix.Color( 45, 53, 65),  // colorNo: 247 index: 246
  matrix.Color( 45, 49, 65)   // colorNo: 248 index: 247
  };

const uint16_t colors[] = {
  matrix.Color(255,0, 0),
  matrix.Color(255, 128, 0), 
  matrix.Color(128, 255, 0), 

  matrix.Color(0, 255 ,0), 
  matrix.Color(0,255,128),
  matrix.Color(0,128,255),

  matrix.Color(0, 0 ,255), 
  matrix.Color(128,0,255),
  matrix.Color(255,128,0),

  matrix.Color(255,0,255),
  matrix.Color(0,255,255),
  matrix.Color(255,255,0),

  matrix.Color(255,255,255),

  matrix.Color(0,0,0),
};





int x    = matrix.width();
int pass = 0;
uint32_t frame;
uint8_t delayt = 50;
String readString;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.fillScreen(BLACK);
}

// void showPict(char picture[8][5]){
// 	for(int y=0; y<8; y++){
// 	    for(int x=0; x<5; x++){
// 	        matrix.drawPixel(x,y,colors[picture[y][x]]);
// 	    }
// 	}
// 	matrix.show();
// }

// void showAnim(char pictures[][8][5],int delayt){
// 	for(int i=0; i<pictures.lenght(); i++){
// 	    showPict(pictures[i]);
// 	    delay(delayt);
// 	}
// }

void loop() {

// for(int c=32; c<54; c++){
// 	for(int i=0; i<8; i++){
// 		matrix.fillCircle(2,0,i,vgaColors[c]);
// 		matrix.show();
// 		delay(50);
// 	}
// }
 
 // --Herz
// for(i = 0; i < PWM; i++) {
//        matrix.setTextColor(vgaColors[40]);
// 	matrix.setBrightness(i);
// 	matrix.setCursor(0,0);
// 	matrix.print(char(259));
// 	matrix.show();
// 	delay(WAITTIME(.01));
// }
// for (i = PWM; i > 0; i--){
// 	matrix.setBrightness(i);
// 	matrix.setCursor(0,0);
// 	matrix.print(char(259));
// 	matrix.show();
// 	delay(WAITTIME(.2));
// }
// for(i = 0; i < PWM; i++) {
// 	matrix.setBrightness(i);
// 	matrix.setCursor(0,0);
// 	matrix.print(char(259));
// 	matrix.show();
// 	delay(WAITTIME(.1));
// }
// for (i = PWM; i > 0; i--){
// 	matrix.setBrightness(i);
// 	matrix.setCursor(0,0);
// 	matrix.print(char(259));
// 	matrix.show();
// 	delay(WAITTIME(.6));
//}

// ----- BITMAP ----
 char picture1[8][5] = {
  {10,10,10,10,10},
  {10, 0,10, 0,10},
  { 0, 0, 0, 0, 0},
  {10, 0, 0, 0,10},
  {10,10, 0,10,10},
  {10,10, 3,10,10},
  { 3,10, 3,10, 3},
  { 3, 3, 3, 3, 3},
 };

 char picture2[8][5] = {
  {10,10,10,10,10},
  {10,10,10,10,10},
  {10, 0,10, 0,10},
  { 0, 0, 0, 0, 0},
  {10, 0, 0, 0,10},
  {10,10, 0,10,10},
  { 3,10, 3,10, 3},
  { 3, 3, 3, 3, 3},
 };

char picture3[8][5] = {
  {10, 0,10, 0,10},
  { 0, 0, 0, 0, 0},
  {10, 0, 0, 0,10},
  {10,10,10,10,10},
  {10,10,10,10,10},
  {10,10, 0,10,10},
  { 3,10, 3,10, 3},
  { 3, 3, 3, 3, 3},
};
 // for(int y=0; y<8; y++){
 //     for(int x=0; x<5; x++){
 //         matrix.drawPixel(x,y,vgaColors[picture1[y][x]]);
 //     }
 // }
 // matrix.show();
 // delay(100);

 // for(int y=0; y<8; y++){
 // 		for(int x=0; x<5; x++){
 //         matrix.drawPixel(x,y,vgaColors[picture2[y][x]]);
 //     }
 // }
 // matrix.show();
 // delay(100);
 // for(int y=0; y<8; y++){
 //    for(int x=0; x<5; x++){
 //         matrix.drawPixel(x,y,vgaColors[picture3[y][x]]);
 //     }
 // }
 // matrix.show();
 // delay(100);


// -Binärpilot

// matrix.fillScreen(BLACK);
// matrix.drawPixel(frame%matrix.width(),0,vgaColors[1]);
// matrix.drawPixel(frame/2%matrix.width(),1,vgaColors[2]);
// matrix.drawPixel(frame/4%matrix.width(),2,vgaColors[3]);
// matrix.drawPixel(frame/8%matrix.width(),3,vgaColors[4]);
// matrix.drawPixel(frame/16%matrix.width(),4,vgaColors[5]);
// matrix.drawPixel(frame/32%matrix.width(),5,vgaColors[6]);
// matrix.drawPixel(frame/64%matrix.width(),6,vgaColors[7]);
// matrix.drawPixel(frame/128%matrix.width(),7,vgaColors[8]);

// matrix.show();
// frame++;
// delay(delayt);


//  ---"VIERECKE"
for(int i=0; i<3; i++){
	matrix.fillScreen(BLACK);
	matrix.drawRect(i,i,5-i*2,8-i*2,vgaColors[2]);
	matrix.show();
	delay(70);
}
for(int i=3; i>0; i--){
	matrix.fillScreen(BLACK);
	matrix.drawRect(i,i,5-i*2,8-i*2,vgaColors[5]);
	matrix.show();
	delay(70);
}

// --- "KITT"
//for(int i=0; i<9; i++){
//matrix.fillScreen(matrix.Color(0,0,0));
//	matrix.drawLine(0,i  ,5,i  ,vgaColors[i]);
//	matrix.drawLine(0,i-1,5,i-1,vgaColors[i]);
//	delay(70);
//	matrix.show();
//	}

// --- "WINDRAD"
//for(int i=0; i<9; i++){
//	matrix.fillScreen(matrix.Color(0,0,0));
//	matrix.drawLine(0,9-i,5,i,vgaColors[i]);
//	delay(70);
//	matrix.show();
//}

// -- "BUCHSTABEN"
// for(int j=0; j<255; j++){
// 	matrix.setTextColor(vgaColors[(j%24)+33]); 
// 	matrix.fillScreen(matrix.Color(0,0,0));
// 	matrix.setCursor(0,0);
// 	matrix.print(char(j));
// 	Serial.println(j);
// 	matrix.show();
// 	delay(200);
// }

// -- "BUCHSTABENSUPPE"
// matrix.setTextColor(vgaColors[random(32,55)]); 
// matrix.fillScreen(BLACK);
// matrix.setCursor(0,0);
// matrix.print(char(random(33, 300)));
// matrix.show();
// delay(150);

// --- CHRISTBAUM
// matrix.fillTriangle(0,2,4,2,2,7,vgaColors[2]);
// //matrix.drawTriangle(0,2,4,2,2,7,vgaColors[3]);
// matrix.drawLine(2,0,2,1,vgaColors[6]);
// matrix.drawPixel(1,2,vgaColors[4]);
// matrix.drawPixel(2,4,vgaColors[4]);
// matrix.drawPixel(4,4,vgaColors[4]);
// matrix.show();
// while(1){}

//----- "ANALYZER" 
//  matrix.fillScreen(matrix.Color(0,0,0));
//  for(int i=0; i<8; i++){
//    matrix.drawLine(0,i,random(5),i,vgaColors[i*5+33]);
//    delay(15);
//  }
//  matrix.show();

// // ---- "COLORTEST"
//	for(uint16_t i=0; i<matrix.width(); i++){
//		for(uint16_t j=0; j<matrix.height(); j++){
//	     	matrix.drawPixel(i,j,vgaColors[indx+j+i*matrix.height()]);
//	     	matrix.show();
//	    }
//	  	delay(20);
//	}
//	if(indx==207){
//		indx = -1;
//	}
//	indx++;

// --- "COLORTEST 2"
// for (int i=0; i<matrix.width(); i++){
// 	for(int j=0; j<matrix.height(); j++){
// 	    matrix.drawPixel(i,j,vgaColors[indx]);
// 	    matrix.show();
// 	    delay(20);
// 	}
// }
// if(indx==255){
//  	indx = -1;
// }
// indx++;
}


