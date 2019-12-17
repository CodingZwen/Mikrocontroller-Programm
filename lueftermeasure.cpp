


void main()
{

char buffer[20];

initlcd();
LEDS = 0x00;
TMOD 0x11;
TR1 =1;




while(1)
{

  if(luefter && !merker)
  {
   //steigende flanke
   merker = 1;
   TR1=1;
  }

    else if(!luefter && merker)
    {
    merker=0;
    TR1 =0;
    Zeit1 = 256*TH1 + TL1;
    TH1 = TL1 =0;
    
    sprintf(buffer,"Zeit: %5u %s     ",)
    textlcd(buffer,1);
    }
    
    if(TF1){ TF1=0;Ausgang=~Ausgang;}



}

}
