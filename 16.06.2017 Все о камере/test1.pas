uses
  GraphABC;

var
  angl: real := -25;
  v: integer := 1;
  w, h, wp, hp, wlast, hlast, xn, yn, i, xx: integer;
  distance: integer := 50;
  x0: integer := 0;
  y0: integer := 0;
  count: integer := 0;
  px := 128;
  py := 96;
  wredblock: integer := 10;
  hredblock: integer := 10;
  
  
//----------------------//
procedure MouseMove(x, y, mb: integer);
begin
   drawRectangle(x,y,x+10,y+10);
   redraw;
end;
//-----------------------//


//------------------------------------------//  
procedure MouseDown(x, y, mb: integer);
begin
  MoveTo(x, y);
 { xx := x;
  for i: integer := 0 to hredblock do 
  begin
    for j: integer := 0 to wredblock do
    begin
      setpixel(xx, y, clred);
      xx := xx + 1;
    end;
    y := y + 1;
    xx := x;
  end;
  println(x, y);}
  redraw;
end;
//------------------------------------------//

begin
  while(true) do
  begin
    //------------------------//
    setconsoleio;
    OnMouseDown := MouseDown;
    OnMouseMove := MouseMove;
    //------------------------//
    
    w := Window.Width;
    h := Window.Height;
    while((h <> hlast) or (w <> wlast)) do
    begin
      
      hlast := h;
      wlast := w;
      clearwindow;
      lockdrawing;
      
      
      wp := w div px;
      hp := h div py;
      
      //draw vertical   
      while count < px + 1 do
      begin
        line(x0, y0, x0, y0 + py * hp);
        x0 := x0 + wp;
        count := count + 1;
        redraw;
      end;
      //--------------//   
      x0 := 0;
      y0 := 0;
      count := 0;
      //----------------//   
      //draw horizontal   
      while count < py + 1 do
      begin
        line(x0, y0, x0 + px * wp, y0);
        y0 := y0 + hp;
        count := count + 1;
        redraw;
      end;
      sleep(1000);
      
      
      x0 := 0;
      y0 := 0;
      count := 0;
      // line(0,0,px*wp,0);
      //line(5,0,5,py*hp);
      //redraw;
    end;
  end;
end.