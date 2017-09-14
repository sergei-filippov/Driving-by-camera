uses GraphABC;
var angl:real:=-25;
var v:integer:=1;
begin
Window.SetSize(800,600);
  setCoordinateorigin (330,500);
  Coordinate.SetMathematic;
     Coordinate.Angle := angl;
     SetPenWidth(130);
   // Line(0,0,0,800);
   SetConsoleIO;
  while True do
  begin
  
    LockDrawing;
    ClearWindow;
  
  //  Ellipse(-120,-70,120,70);
   // Line(0,0,200,0);
   // SetPenWidth(200);
    Line(0,0,0,600);
    Redraw;
    Coordinate.Angle := Coordinate.Angle + 1;
     Coordinate.Angle := angl;
     angl:= angl + (0.1 * v);
 if abs(angl) > 25 then v*=-1;
    //Redraw;
    print (angl);
  //  Sleep(0);
  end;
end.
