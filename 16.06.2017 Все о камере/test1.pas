uses
  GraphABC;

var
  w, h, wbox, hbox, wlast, hlast,  xfirstinbox, yfirstinbox, xnbox, ynbox: integer;
  
  count: integer := 0;
  spacelbox: integer := 2;
  spacetbox: integer := 2;
  spacel{left} : integer := 0;
  spacer{right}: integer := 0;
  spaced{down}: integer := 0;
  spacet{top}: integer := 0;
  x0: integer := spacer;
  y0: integer := spacet;
  xbox := 128;
  ybox := 96;



//----------------------//
procedure MouseMove(x, y, mb: integer);
begin
  xnbox := x div wbox;
  ynbox := y div hbox;
  xfirstinbox := xnbox * wbox;
  yfirstinbox := ynbox * hbox;
  for j: integer := yfirstinbox + 1 to yfirstinbox + hbox - 1 do 
  begin
    for i: integer := xfirstinbox + 1 to xfirstinbox + wbox - 1 do
    begin
      if mb = 1 then
        setpixel(i, j, clred)
      else if mb = 2 then
        setpixel(i, j, clwhite);
    end;
  end;
  redraw;
end;
//-----------------------//


//------------------------------------------//  
procedure MouseDown(x, y, mb: integer);
begin
  MoveTo(x, y);
  xnbox := x div wbox;
  ynbox := y div hbox;
  xfirstinbox := xnbox * wbox;
  yfirstinbox := ynbox * hbox;
  for j: integer := yfirstinbox + 1 to yfirstinbox + hbox - 1 do 
  begin
    for i: integer := xfirstinbox + 1 to xfirstinbox + wbox - 1 do
    begin
      if mb = 1 then
        setpixel(i, j, clred)
      else if mb = 2 then
        setpixel(i, j, clwhite);
    end;
  end;
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
    w := w - spacel;
    h := h - spacet;
    
    
    
    while((h <> hlast) or (w <> wlast)) do
    begin
      
      hlast := h;
      wlast := w;
      clearwindow;
      lockdrawing;
      
      
      wbox := w div xbox;
      hbox := h div ybox;
      spacel := spacelbox * wbox;
      spacet := spacetbox * hbox;
      
      //draw vertical   
      while count < xbox + 1 do
      begin
        line(x0, y0, x0, y0 + ybox * hbox);
        x0 := x0 + wbox;
        count := count + 1;
        redraw;
      end;
      x0 := spacel;
      count := 0;
        //--------------//   
      
      
      //draw horizontal   
      while count < ybox + 1 do
      begin
        line(x0, y0, x0 + xbox * wbox, y0);
        y0 := y0 + hbox;
        count := count + 1;
        redraw;
      end;
      sleep(1000);
      y0 := spacet;
      count := 0;
      // line(0,0,xbox*wp,0);
      //line(5,0,5,ybox*hp);
      //redraw;
    end;
  end;
end.