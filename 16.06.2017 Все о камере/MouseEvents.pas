// Иллюстрация обработки событий мыши
uses GraphABC;
var xn,yn:integer;
procedure MouseDown(x,y,mb: integer);
begin

  MoveTo(x,y);
  setpixel(x,y,clred);
   
end;

procedure MouseMove(x,y,mb: integer);
begin
  if mb=1 then LineTo(x,y);
  xn :=x;
yn :=y;
 println(xn,yn);
end;

begin
setconsoleio;
  // Привязка обработчиков к событиям
  //writeln(OnMouseDown);
  OnMouseDown := MouseDown;
  println(xn,yn);
  OnMouseMove := MouseMove;
end.

