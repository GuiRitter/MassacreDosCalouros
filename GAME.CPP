#include<dos.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream.h> // feito por Guilherme Alan Ritter m72642

#define A_agudo 181
#define A_circu 182
#define A_grave 183
#define A___til 199
#define A_trema 142
#define Angstro 143
#define ch___AE 146
#define E_agudo 144
#define E_circu 210
#define E_trema 211
#define I_agudo 214
#define I_circu 215
#define I_grave 222
#define I_trema 216
#define N___til 165
#define O_circu 226
#define O_grave 227
#define O___til 229
#define O_trema 153
#define U_agudo 233
#define U_circu 234
#define U_grave 235
#define U_trema 154
#define Y_agudo 237
#define ch___ae 145
#define a_agudo 160
#define a_circu 131
#define a_grave 133
#define a_super 166
#define a___til 198
#define a_trema 132
#define c_cedil 135
#define e_agudo 130
#define e_circu 136
#define e_trema 137
#define i_agudo 161
#define i_circu 140
#define i_grave 141
#define i_trema 139
#define n___til 164
#define o_agudo 162
#define o_circu 147
#define o_grave 149
#define o_super 167
#define o___til 228
#define o_trema 148
#define u_agudo 163
#define u_circu 150
#define u_grave 151
#define u_trema 129
#define y_agudo 236
#define y_trema 152
#define ch_1sup 251
#define ch_2sup 253
#define ch_3sup 252
#define ch_arro 64
#define ch_cent 189
#define ch_diam 155
#define ch_DIAM 157
#define ch_grau 248
#define ch_pont 250
#define ch___+- 241
#define ch_micr 230

#define ch_cedl 247
#define somb0 176 // 25%
#define somb1 177 // 50%
#define somb2 178 // 75%
#define somb3 219 // 100%
#define somb6 220
#define somb9 223
#define linha___lo 196 //  -
#define linha___ns 179 //      |
#define linha__nos 180 // -|
#define linha__lno 193 //     _|_
#define linha__lso 194 // '|'
#define linha__nls 195 //      |-
#define linha___so 191 // -,
#define linha___ls 218 //      ,-
#define linha___nl 192 //  '-
#define linha___on 217 //     -'
#define linha_lnos 197 //  +

struct time t;
long int atraso = 10;

void reseta_cprintf();
void seta_cprintf(unsigned char c,unsigned char b);

class GFX{
   public:
      void desliga_cursor();
      void printa_moldura();
      void printa_mais_moldura();
      void printa_a(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_c(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_e(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_l(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_m(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_o(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_r(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_s(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_u(unsigned char x,unsigned char y,unsigned char c,unsigned char b);
      void printa_logo(unsigned char x,unsigned char y);
      void printa_splash();
      void apaga_tela();
      void relogio();
      void velo();
};

class Lancador{
   private:
      unsigned char x;
      int tmin,tsec;
      long int l,tf;
   public:
      Lancador();
      void printar();
      void apagar();
      void mover(char p);
      int f5tempo();
      unsigned char ret_x();
      void get_l(unsigned char p);
      int ret_l();
};

class Tomate{
   private:
      unsigned char x,y,hp;
      long int tf;
   public:
      Tomate();
      void printar();
      void apagar();
      void mover();
      unsigned char nascer(unsigned char p);
      void morrer();
      unsigned char ret_hp();
      unsigned char ret_x();
      unsigned char ret_y();
};

class Alvo{
   private:
      unsigned char x,y,s,hp,cor;
      long int tf;
   public:
      Alvo();
      void printar();
      void apagar();
      void mover();
      unsigned char testar(unsigned char px,unsigned char py);
      void machucar();
      void matar();
      unsigned char ret_hp();
};

long int tempo();
// retorna o tempo em centésimos de segundo

void main(){
   clrscr();
   GFX gfx;
   Tomate tomate;
   char ch1 = 1,ch2;
   unsigned char menu = 0,c,i;
   reseta_cprintf();
   gfx.desliga_cursor();
   gfx.printa_splash();
   gfx.printa_moldura();
   while(ch1 != 13 && ch1 != 27){
      if(kbhit()){ ch1 = getch(); if(ch1 == 0){ ch2 = getch(); } }
      gfx.relogio();
      gfx.velo();
      if(ch1 == 43 && atraso > 1){ // +
	 atraso--; ch1 = 1;
      }else if(ch1 == 45 && atraso < 100){ // -
	 atraso++; ch1 = 1;
      }else if(ch1 == 27){
	 menu = 1;
      }
   }
   gfx.apaga_tela();
   gfx.printa_mais_moldura();
   Lancador lancador;
   Alvo alvo[3];

   /* inicio parte principal */ while(menu == 0){

      gfx.relogio();
      gfx.velo();
      for(i = 0;i <= 2;i++){
	 alvo[i].mover();
	 alvo[i].printar();
      }
      tomate.mover(); tomate.printar();
      for(i = 0;i <= 2;i++){
	 if(tomate.ret_hp() && alvo[i].testar(tomate.ret_x(),tomate.ret_y()) && alvo[i].ret_hp() < 5 ){
	    tomate.morrer();
	    alvo[i].machucar();
	 }
      }
      if(ch1 == 43 && atraso > 1){ // +
	 atraso--; ch1 = 1;
      }else if(ch1 == 45 && atraso < 100){ // -
	 atraso++; ch1 = 1;
      }
      if(kbhit()){ ch1 = getch(); if(ch1 == 0){ ch2 = getch(); } }
      if(ch1 == 0 && ch2 == 75){
	 lancador.mover('e'); ch1 = 1;
      }else if(ch1 == 0 && ch2 == 77){
	 lancador.mover('d'); ch1 = 1;
      }else if(ch1 == 32){
	 lancador.get_l(tomate.nascer(lancador.ret_x())); ch1 = 1;
      }
      if(ch1 == 27){ menu = 1; }
      else if(lancador.f5tempo() == 0){ menu = 2; }
      else if(lancador.ret_l() == 0 && tomate.ret_hp() == 0){ menu = 3; }
      c = 0;
      for(i = 0;i <= 2;i++){
	 if(alvo[i].ret_hp() >= 5){ c++; }
      }
      if(c == 3){ menu = 4; }

   /*    fim parte principal */ }
   gotoxy(39,13);
   reseta_cprintf();
   cprintf("Tchau!");
   if(menu == 1){
      long int tfim;
      tfim = tempo() + 100;
      while(tfim >= tempo()){}
   }else if(menu == 2){
      gotoxy(33,12);
      cprintf("N%co h%c mais tempo!",a___til,a_agudo);
      getch();
   }else if(menu == 3){
      gotoxy(32,12);
      cprintf("N%co h%c mais tomates!",a___til,a_agudo);
      getch();
   }else if(menu == 4){
      gotoxy(24,12);
      cprintf("Parab%cns, voc%c derrotou os calouros!",e_agudo,e_circu);
      getch();
   }
}

// ~main
// class Lancador

Lancador::Lancador(){
   x = 40;
   l = 99999;
   tmin = 99;
   tsec = 59;
   tf = tempo() + 100;
   printar();
}

void Lancador::printar(){
   reseta_cprintf();
   gotoxy(x-1,20);
   cprintf("%c%c%c",linha__lso,linha__lso,linha__lso);
   gotoxy(x-5,21);
   cprintf("%c%c%c%c%c%c%c%c%c%c%c",linha___ls,linha___lo,linha___lo,linha___lo,linha__lno,linha__lno,linha__lno,linha___lo,linha___lo,linha___lo,linha___so);
   gotoxy(x-5,22);
   if(l != 0){
      cprintf("%cL.: %5.ld%c",linha___ns,l,linha___ns);
   }else{
      cprintf("%cL.:     0%c",linha___ns,linha___ns);
   }
   gotoxy(x-5,23);
   cprintf("%cT.: ",linha___ns);
   if(tmin != 0){
      cprintf("%2.d",tmin);
   }else{
      cprintf(" 0");
   }
   cprintf(":");
   if(tsec != 0){
      cprintf("%2.d",tsec);
   }else{
      cprintf(" 0");
   }
   cprintf("%c",linha___ns);
   gotoxy(x-5,24);
   cprintf("%c%c%c%c%c%c%c%c%c%c%c",linha__lno,linha___lo,linha___lo,linha___lo,linha___lo,linha___lo,linha___lo,linha___lo,linha___lo,linha___lo,linha__lno);
}

void Lancador::apagar(){
   reseta_cprintf();
   int i;
   gotoxy(x-1,20);
   cprintf("%c%c%c",linha___lo,linha___lo,linha___lo);
   gotoxy(x-5,21);
   cprintf("           ");
   gotoxy(x-5,22);
   cprintf("           ");
   gotoxy(x-5,23);
   cprintf("           ");
   gotoxy(x-5,24);
   for(i = 0;i <= 10;i++){
      cprintf("%c",linha___lo);
   }
}

void Lancador::mover(char p){
   if(p == 'd' && x < 74){
      apagar();
      x++;
      printar();
   }else if(p == 'e' && x > 7){
      apagar();
      x--;
      printar();
   }
}

int Lancador::f5tempo(){
   reseta_cprintf();
   if(tempo() >= tf){
      tsec--;
      if(tsec < 0){
	 tsec = 59;
	 tmin--;
      }
      tf = tempo() + 100;
   }
   gotoxy(x,23);
   if(tmin != 0){
      cprintf("%2.d",tmin);
   }else{
      cprintf(" 0");
   }
   cprintf(":");
   if(tsec != 0){
      cprintf("%2.d",tsec);
   }else{
      cprintf(" 0");
   }
   gotoxy(x,22);
   if(l != 0){
      cprintf("%5.ld",l);
   }else{
      cprintf("    0");
   }
   return !(tmin == 0 && tsec == 0);
}

unsigned char Lancador::ret_x(){ return x; }

void Lancador::get_l(unsigned char p){ if(p == 1){ l--; } }

int Lancador::ret_l(){ return l; }

// class ~Lancador
// class Tomate

Tomate::Tomate(){
   y = 19;
   hp = 0;
}

void Tomate::printar(){
   if(hp == 1){
      gotoxy(x,y);
      seta_cprintf(12,16); // vermelho
      cprintf("%c",ch_arro);
   }
}

void Tomate::apagar(){
   gotoxy(x,y);
   reseta_cprintf();
   cprintf(" ");
}

unsigned char Tomate::nascer(unsigned char p){
   unsigned int z;
   if(hp == 0){
      x = p;
      hp = 1;
      tf = tempo() + atraso;
      printar();
      z = 1;
   }else{
      z = 0;
   }
   return z;
}

void Tomate::morrer(){
   hp = 0;
   y = 19;
   apagar();
}

void Tomate::mover(){
   apagar();
   if(hp == 1 && tempo() >= tf){
      if(y != 2){
	 y--;
	 tf = tempo() + atraso;
      }else{
	 apagar();
	 morrer();
      }
   }
}

unsigned char Tomate::ret_hp(){ return hp; }

unsigned char Tomate::ret_x(){ return x; }

unsigned char Tomate::ret_y(){ return y; }

// class ~Tomate
// class Alvo

Alvo::Alvo(){
   x = 0;
   y = 0;
   s = 0;
   while(x == 0){
      s = rand() % 80;
      if(s >= 5 && s <= 76){
	 x = s;
      }
   }
   while(y == 0){
      s = rand() % 80;
      if(s >= 5 && s <= 21){
	 y = s;
      }
   }
   s = rand() % 4;
   hp = 0;
   cor = 10; // verde
   printar();
   tf = tempo() + atraso;
}

void Alvo::printar(){
   if(hp <= 4){
      gotoxy(x-3,y-2);
      textcolor(cor); // depende de hp
      cprintf(" xxxxx ");
      gotoxy(x-3,y-1);
      textcolor(6); // amarelo escuro
      cprintf(" %c   %c ",linha___ns,linha___ns);
      gotoxy(x-3,y);
      cprintf("(%c u %c)",linha___ns,linha___ns);
      gotoxy(x-3,y+1);
      cprintf(" %c   %c ",linha___ns,linha___ns);
      gotoxy(x-3,y+2);
      cprintf("  \\_/  ");
      gotoxy(x-1,y-1);
      textcolor(9); // azul
      cprintf("%c %c",o_circu,o_circu);
      gotoxy(x,y+1);
      textcolor(13); // magenta
      cprintf("%u",hp);
   }
}

void Alvo::apagar(){
   int i;
   for(i=y-2;i<=y+2;i++){
      gotoxy(x-3,i);
      cprintf("       ");
   }
}

void Alvo::mover(){
   if(hp <= 4 && tempo() >= tf){
      apagar();
      if(s == 0){
	 if(x == 76 && y == 4){ s = 2; }
	 else if(x == 76){ s = 1; }
	 else if(y == 4){ s = 3; }
      }else if(s == 1){
	 if(x == 5 && y == 4){ s = 3; }
	 else if(x == 5){ s = 0; }
	 else if(y == 4){ s = 2; }
      }else if(s == 2){
	 if(x == 5 && y == 17){ s = 0; }
	 else if(x == 5){ s = 3; }
	 else if(y == 17){ s = 1; }
      }else if(s == 3){
	 if(x == 76 && y == 17){ s = 1; }
	 else if(x == 76){ s = 2; }
	 else if(y == 17){ s = 0; }
      }
      if(s == 0){ x++; y--; }
      else if(s == 1){ x--; y--; }
      else if(s == 2){ x--; y++; }
      else if(s == 3){ x++; y++; }
      tf = tempo() + atraso;
   }
}

unsigned char Alvo::testar(unsigned char px,unsigned char py){
   return ( ( px >= x-2 && px <= x+2 && py >= y-2 && py <= y+2 ) || ( ( px == x-3 || px == x+3 ) && py == y ) );
} // retorna 1 se a checagem for verdadeira e o inverso; checa se o tomate acertou um quadrado de 5x5 ou as orelhas

void Alvo::machucar(){
   hp++;
   if(hp == 3){
      cor = 14; // amarelo
   }else if(hp == 4){
      cor = 12; // vermelho
   }else if(hp == 5){
      matar();
   }
}

void Alvo::matar(){
   apagar();
}

unsigned char Alvo::ret_hp(){ return hp; }

// class ~Alvo

long int tempo(){
   gettime(&t);
   long int a = t.ti_hour, b = t.ti_min, c = t.ti_sec, d = t.ti_hund;
   return a*60*60*100 + b*60*100 + c*100 + d;
}

// class GFX

void GFX::printa_moldura(){
   int x;
   textcolor(7);
   for(x=2;x<=79;x++){
      gotoxy(x,1);
      cprintf("%c",linha___lo);
      gotoxy(x,24);
      cprintf("%c",linha___lo);
      if(x <= 23){
	 gotoxy(1,x);
	 cprintf("%c",linha___ns);
	 gotoxy(80,x);
	 cprintf("%c",linha___ns);
      }
   }
   gotoxy(1,1);   cprintf("%c",linha___ls);
   gotoxy(80,1);  cprintf("%c",linha___so);
   gotoxy(1,24);  cprintf("%c",linha___nl);
   gotoxy(80,24); cprintf("%c",linha___on);
   gotoxy(1,25);  cprintf("Atraso: ");
}

void GFX::printa_mais_moldura(){
   gotoxy(1,20);
   cprintf("%c",linha__nls);
   int i;
   for(i = 0;i <= 77;i++){
      cprintf("%c",linha___lo);
   }
   cprintf("%c",linha__nos);
}

void GFX::desliga_cursor(){
      REGS regs;
      regs.h.ah=0x01;
      regs.h.ch=0x20;
      int86(0x10, &regs,&regs);
}

void reseta_cprintf(){
   textcolor(7);
   textbackground(0);
}

void seta_cprintf(unsigned char c,unsigned char b){
   if(c < 16){
      textcolor(c);
   }
   if(b < 8){
      textbackground(b);
   }
}

void GFX::printa_a(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf(" %c%c%c%c",somb9,somb9,somb9,somb6);
   gotoxy(x,y+2);
   cprintf("%c%c%c%c%c",somb6,somb9,somb9,somb9,somb3);
   gotoxy(x,y+3);
   cprintf(" %c%c%c%c",somb9,somb9,somb9,somb9);
}

void GFX::printa_c(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf("%c%c%c%c ",somb6,somb9,somb9,somb9);
   gotoxy(x,y+2);
   cprintf("%c   %c",somb3,somb6);
   gotoxy(x,y+3);
   cprintf(" %c%c%c ",somb9,somb9,somb9);
}

void GFX::printa_e(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf("%c%c%c%c%c",somb6,somb9,somb9,somb9,somb6);
   gotoxy(x,y+2);
   cprintf("%c%c%c%c%c",somb3,somb9,somb9,somb9,somb9);
   gotoxy(x,y+3);
   cprintf(" %c%c%c ",somb9,somb9,somb9);
}

void GFX::printa_l(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf(" %c%c  ",somb9,somb3);
   gotoxy(x,y+1);
   cprintf("  %c  ",somb3);
   gotoxy(x,y+2);
   cprintf("  %c  ",somb3);
   gotoxy(x,y+3);
   cprintf(" %c%c%c ",somb9,somb9,somb9);
}

void GFX::printa_m(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf("%c%c%c%c%c",somb3,somb9,somb6,somb9,somb6);
   gotoxy(x,y+2);
   cprintf("%c   %c",somb3,somb3);
   gotoxy(x,y+3);
   cprintf("%c   %c",somb9,somb9);
}

void GFX::printa_o(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf("%c%c%c%c%c",somb6,somb9,somb9,somb9,somb6);
   gotoxy(x,y+2);
   cprintf("%c   %c",somb3,somb3);
   gotoxy(x,y+3);
   cprintf(" %c%c%c ",somb9,somb9,somb9);
}

void GFX::printa_r(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf("%c%c%c%c%c",somb3,somb6,somb9,somb9,somb6);
   gotoxy(x,y+2);
   cprintf("%c    ",somb3);
   gotoxy(x,y+3);
   cprintf("%c    ",somb9);
}

void GFX::printa_s(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf("%c%c%c%c ",somb6,somb9,somb9,somb9);
   gotoxy(x,y+2);
   cprintf(" %c%c%c%c",somb9,somb9,somb9,somb6);
   gotoxy(x,y+3);
   cprintf("%c%c%c%c ",somb9,somb9,somb9,somb9);
}

void GFX::printa_u(unsigned char x,unsigned char y,unsigned char c,unsigned char b){
   seta_cprintf(c,b);
   gotoxy(x,y);
   cprintf("     ");
   gotoxy(x,y+1);
   cprintf("%c   %c",somb3,somb3);
   gotoxy(x,y+2);
   cprintf("%c  %c%c",somb3,somb6,somb3);
   gotoxy(x,y+3);
   cprintf(" %c%c %c",somb9,somb9,somb9);
}

void GFX::printa_logo(unsigned char x,unsigned char y){
   reseta_cprintf();
   seta_cprintf(12,16); // vermelho
   printa_m(x,y,16,16);
   printa_a(x+6,y,16,16);
   printa_s(x+12,y,16,16);
   printa_s(x+18,y,16,16);
   printa_a(x+24,y,16,16);
   printa_c(x+30,y,16,16);
   printa_r(x+36,y,16,16);
   printa_e(x+42,y,16,16);
   reseta_cprintf();
   gotoxy(x+22,y+4);
   cprintf("dos");
   seta_cprintf(10,16); // verde
   printa_c(x,y+5,16,16);
   printa_a(x+6,y+5,16,16);
   printa_l(x+12,y+5,16,16);
   printa_o(x+18,y+5,16,16);
   printa_u(x+24,y+5,16,16);
   printa_r(x+30,y+5,16,16);
   printa_o(x+36,y+5,16,16);
   printa_s(x+42,y+5,16,16);
}

void GFX::printa_splash(){
   printa_logo(17,1);
   reseta_cprintf();
   gotoxy(21,11);
   cprintf("%c um show de calouros e eles fracassaram",E_agudo);
   gotoxy(34,12);
   cprintf("Tomate neles!");
   gotoxy(7,13);
   cprintf("As setas do teclado movimentam o lan%cador e o espa%co atira um tomate",c_cedil,c_cedil);
   gotoxy(17,14);
   cprintf("Acerte cinco tomates em cada calouro para vencer");
   gotoxy(24,15);
   cprintf("Voc%c tem tempo e tomates limitados",e_circu);
   gotoxy(5,16);
   cprintf("Utilize as teclas + e - para trocar a velocidade do jogo e ESC para sair");
   gotoxy(8,18);
   cprintf("Obs: O criador deste jogo n%co se responsabiliza por danos causados",a___til);
   gotoxy(11,19);
   cprintf("ao seu computador, principalmente se jogado %c meia noite ...",a_grave);
   gotoxy(27,21);
   cprintf("Pressione Enter para come%car",c_cedil);
   gotoxy(9,23);
   cprintf("© Guilherme Alan Ritter 72642 - Engenharia de Computa%c%co - UNISC",c_cedil,a___til);
}

void GFX::apaga_tela(){
   int ix,iy;
   reseta_cprintf();
   for(ix = 2;ix <= 79;ix++){
      for(iy = 2;iy <= 23;iy++){
	 gotoxy(ix,iy);
	 cprintf(" ");
      }
   }
}

void GFX::relogio(){
   reseta_cprintf();
   gotoxy(72,25);
   tempo();
   if(t.ti_hour != 0){
      cprintf("%2.d",t.ti_hour);
   }else{
      cprintf(" 0");
   }
   cprintf(":");
   if(t.ti_min != 0){
      cprintf("%2.d",t.ti_min);
   }else{
      cprintf(" 0");
   }
   cprintf(":");
   if(t.ti_sec != 0){
      cprintf("%2.d",t.ti_sec);
   }else{
      cprintf(" 0");
   }
}

void GFX::velo(){
   gotoxy(9,25); cprintf("%3.d0 ms",atraso);
}

// class ~GFX