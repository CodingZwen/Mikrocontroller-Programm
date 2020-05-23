  
  
  void main ()
  {
  
  
  
  
  
  
  }
  
  
  
  void Timer0_isr(void) interrupt 1 //timer 0
{
    TL0 = (65536-50000)%256; //high & low byte setzen
    TH0 = (65536-50000)/256;
    ms++; //20 inkrementiert ist 1s
    
    if(ms % 20 == 0){
        
    u.sekunden++;
    
    sprintf(buffer,"%d", u.sekunden);
    textlcd(buffer,1);
    }
}
